#include <WiFi.h>
#include <esp_now.h>

/* ===================== CONFIG ===================== */

uint8_t peerAddress[] = {0x68, 0xFE, 0x71, 0xF8, 0x20, 0x8C};


// uint8_t peerAddress[] = {0x68, 0xFE, 0x71, 0xFA, 0xC5, 0xE4};


#define UART_BAUDRATE 115200
#define PACKET_SIZE  8

#define START_BYTE 0x02
#define END_BYTE   0x03

#define LED_PIN 2
#define LED_BLINK_TIME 100

#define UART1_RX 3
#define UART1_TX 1
#define UART2_RX 16
#define UART2_TX 17

/* ===================== ESP-NOW RETRY CONFIG ===================== */

#define ESPNOW_MAX_RETRY     5
#define ESPNOW_RETRY_DELAY  1000  // ms

uint8_t espnow_fail_count = 0;
bool espnow_ready = false;
unsigned long last_retry_time = 0;

/* ===================== DATA STRUCT ===================== */

typedef struct __attribute__((packed)) {
  uint8_t start;
  uint8_t id_rb;
  uint8_t state;
  uint8_t move;
  uint8_t action;
  uint8_t block_id;
  uint8_t checksum;
  uint8_t end;
} Packet;

/* ===================== LED ===================== */

bool ledBlinking = false;
unsigned long ledTimestamp = 0;

/* ===================== FUNCTION DECLARE ===================== */

bool readPacketUART(HardwareSerial &uart, Packet &pkt);
bool validatePacket(const Packet &pkt);
uint8_t calcChecksum(const Packet &pkt);

void blinkLED();
void updateLED();

void initESPNow();
void retryESPNow();

/* ===================== ESP-NOW CALLBACK ===================== */

void OnDataSent(const wifi_tx_info_t *tx_info, esp_now_send_status_t status)
{
  if (status == ESP_NOW_SEND_SUCCESS) {
    espnow_fail_count = 0;
    espnow_ready = true;
  } else {
    espnow_fail_count++;
    espnow_ready = false;
  }
}


/* ===================== ESP-NOW INIT ===================== */

void initESPNow()
{
  esp_now_deinit();

  if (esp_now_init() != ESP_OK) {
    espnow_ready = false;
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, peerAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    espnow_ready = false;
    return;
  }

  espnow_fail_count = 0;
  espnow_ready = true;

  Serial.println("ESP-NOW reinitialized");
}

/* ===================== ESP-NOW RETRY ===================== */

void retryESPNow()
{
  if (espnow_ready) return;

  if (millis() - last_retry_time < ESPNOW_RETRY_DELAY)
    return;

  last_retry_time = millis();

  Serial.println("ESP-NOW retry...");
  initESPNow();
}

/* ===================== SETUP ===================== */

void setup() {
  Serial.begin(115200);
  Serial1.begin(UART_BAUDRATE, SERIAL_8N1, UART1_RX, UART1_TX);
  Serial2.begin(UART_BAUDRATE, SERIAL_8N1, UART2_RX, UART2_TX);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  initESPNow();
}

/* ===================== LOOP ===================== */

void loop() {
  Packet pkt;

  // Retry ESP-NOW nếu mất
  if (espnow_fail_count >= ESPNOW_MAX_RETRY) {
    espnow_ready = false;
    retryESPNow();
  }

  // 👉 NHẬN TỪ SERIAL1
  if (readPacketUART(Serial1, pkt)) {
    blinkLED();

    if (!validatePacket(pkt)) return;

    if (pkt.id_rb == 1) {
      // ➜ ESP-NOW
      if (espnow_ready) {
        esp_now_send(peerAddress, (uint8_t*)&pkt, sizeof(Packet));
      }
    }
    else if (pkt.id_rb == 2) {
      // ➜ UART2
      Serial2.write((uint8_t*)&pkt, sizeof(Packet));
    }
  }

  updateLED();
}

/* ===================== UART PARSER ===================== */

bool readPacketUART(HardwareSerial &uart, Packet &pkt) {
  static uint8_t buffer[PACKET_SIZE];
  static uint8_t index = 0;

  while (uart.available()) {
    uint8_t b = uart.read();

    if (index == 0 && b != START_BYTE) continue;

    buffer[index++] = b;

    if (index == PACKET_SIZE) {
      index = 0;
      memcpy(&pkt, buffer, PACKET_SIZE);

      if (pkt.start != START_BYTE) return false;
      if (pkt.end   != END_BYTE)   return false;

      return true;
    }
  }
  return false;
}

/* ===================== CHECKSUM ===================== */

bool validatePacket(const Packet &pkt) {
  return pkt.checksum == calcChecksum(pkt);
}

uint8_t calcChecksum(const Packet &pkt) {
  return (pkt.start +
          pkt.id_rb +
          pkt.state +
          pkt.move +
          pkt.action +
          pkt.block_id) & 0xFF;
}

/* ===================== LED ===================== */

void blinkLED() {
  digitalWrite(LED_PIN, HIGH);
  ledBlinking = true;
  ledTimestamp = millis();
}

void updateLED() {
  if (ledBlinking && millis() - ledTimestamp > LED_BLINK_TIME) {
    digitalWrite(LED_PIN, LOW);
    ledBlinking = false;
  }
}
