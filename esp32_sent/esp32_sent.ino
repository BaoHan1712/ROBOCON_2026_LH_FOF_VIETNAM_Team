#include <WiFi.h>
#include <esp_now.h>

/* ===================== CONFIG ===================== */

uint8_t peerAddress[] = {0x30, 0xC9, 0x22, 0x32, 0xD4, 0xA8};

#define UART_BAUDRATE 115200
#define PACKET_SIZE 6
#define START_BYTE 0x02
#define END_BYTE   0x03

#define LED_PIN 2
#define LED_BLINK_TIME 100  // ms

/* ===================== DATA STRUCT ===================== */

typedef struct {
  uint8_t start;
  uint8_t move;
  uint8_t action;
  uint8_t block_id;
  uint8_t checksum;
  uint8_t end;
} Packet;

/* ===================== LED STATE ===================== */

bool ledBlinking = false;
bool ledState = false;
unsigned long ledTimestamp = 0;

/* ===================== FUNCTION DECLARE ===================== */

void initUART();
void initESPNow();
bool readPacketUART(Packet &pkt);
bool validatePacket(const Packet &pkt);
void sendPacketESPNow(const Packet &pkt);
uint8_t calcChecksum(const Packet &pkt);

void triggerBlink();
void updateLED();

void onDataSent(const wifi_tx_info_t *tx_info, esp_now_send_status_t status);

/* ===================== SETUP ===================== */

void setup() {
  Serial.begin(UART_BAUDRATE);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  initUART();
  initESPNow();
}

/* ===================== LOOP ===================== */

void loop() {
  Packet pkt;

  if (readPacketUART(pkt)) {
    if (validatePacket(pkt)) {
      triggerBlink();          // 👈 kích hoạt blink
      sendPacketESPNow(pkt);
    }
  }

  updateLED();                // 👈 update LED bằng millis
}

/* ===================== FUNCTION IMPLEMENT ===================== */

void initUART() {
}

void initESPNow() {
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) return;

  esp_now_register_send_cb(onDataSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, peerAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  esp_now_add_peer(&peerInfo);
}

// --- UART PACKET ---
bool readPacketUART(Packet &pkt) {
  static uint8_t buffer[PACKET_SIZE];
  static uint8_t index = 0;

  while (Serial.available()) {
    uint8_t b = Serial.read();

    if (index == 0 && b != START_BYTE) continue;

    buffer[index++] = b;

    if (index == PACKET_SIZE) {
      memcpy(&pkt, buffer, PACKET_SIZE);
      index = 0;
      return pkt.end == END_BYTE;
    }
  }
  return false;
}

bool validatePacket(const Packet &pkt) {
  return pkt.checksum == calcChecksum(pkt);
}

uint8_t calcChecksum(const Packet &pkt) {
  return (pkt.start + pkt.move + pkt.action + pkt.block_id) & 0xFF;
}

void sendPacketESPNow(const Packet &pkt) {
  esp_now_send(peerAddress, (uint8_t*)&pkt, sizeof(Packet));
}

/* ===================== LED NON-BLOCKING ===================== */

void triggerBlink() {
  ledBlinking = true;
  ledState = true;
  ledTimestamp = millis();
  digitalWrite(LED_PIN, HIGH);
}

void updateLED() {
  if (!ledBlinking) return;

  if (millis() - ledTimestamp >= LED_BLINK_TIME) {
    if (ledState) {
      digitalWrite(LED_PIN, LOW);
      ledState = false;
      ledTimestamp = millis();
    } else {
      ledBlinking = false; // blink xong
    }
  }
}

/* ===================== ESP-NOW CALLBACK ===================== */

void onDataSent(const wifi_tx_info_t *tx_info, esp_now_send_status_t status) {
  // không log
}
