#include <WiFi.h>
#include <esp_now.h>

/* ===================== CONFIG ===================== */

uint8_t peerAddress[] = {0x68, 0xFE, 0x71, 0xFA, 0xC5, 0xE4};

#define UART_BAUDRATE 115200
#define PACKET_SIZE  8

#define START_BYTE 0x02
#define END_BYTE   0x03

#define LED_PIN 2
#define LED_BLINK_TIME 100

// UART pin mapping (đổi nếu cần)
#define UART1_RX 3
#define UART1_TX 1
#define UART2_RX 16
#define UART2_TX 17

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

/* ===================== LED STATE ===================== */

bool ledBlinking = false;
unsigned long ledTimestamp = 0;

/* ===================== FUNCTION DECLARE ===================== */

bool readPacketUART(HardwareSerial &uart, Packet &pkt);
bool validatePacket(const Packet &pkt);
uint8_t calcChecksum(const Packet &pkt);

void blinkLED();
void updateLED();

/* ===================== SETUP ===================== */

void setup() {
  Serial.begin(115200);   // debug
  Serial1.begin(UART_BAUDRATE, SERIAL_8N1, UART1_RX, UART1_TX);
  Serial2.begin(UART_BAUDRATE, SERIAL_8N1, UART2_RX, UART2_TX);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) return;

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, peerAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);

  Serial.println("ESP32 ROUTER READY");
}

/* ===================== LOOP ===================== */

void loop() {
  Packet pkt;

  // 👉 NHẬN TỪ SERIAL1
  if (readPacketUART(Serial1, pkt)) {
    blinkLED();

    if (!validatePacket(pkt)) {
      Serial.println("Checksum error");
      return;
    }

    // ===== ROUTING =====
    if (pkt.id_rb == 1) {
      // ➜ ESP-NOW → RB1
      esp_now_send(peerAddress, (uint8_t*)&pkt, sizeof(Packet));
      Serial.println("Route: Serial1 → ESP-NOW (RB1)");
    }
    else if (pkt.id_rb == 2) {
      // ➜ Serial2 → RB2
      Serial2.write((uint8_t*)&pkt, sizeof(Packet));
      Serial.println("Route: Serial1 → Serial2 (RB2)");
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