#include <WiFi.h>
#include <esp_now.h>

/* ===================== CONFIG ===================== */

uint8_t peerAddress[] = {0x30, 0xC9, 0x22, 0x32, 0xD4, 0xA8};

#define UART_BAUDRATE 115200
#define PACKET_SIZE  8  

#define START_BYTE 0x02
#define END_BYTE   0x03

#define LED_PIN 2
#define LED_BLINK_TIME 100

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

/* ===================== SETUP ===================== */

void setup() {
  Serial.begin(UART_BAUDRATE);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) return;

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, peerAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);
}

/* ===================== LOOP ===================== */

void loop() {
  Packet pkt;

  if (readPacketUART(pkt)) {
    blinkLED();

    if (!validatePacket(pkt)) return;

    // ===== ROUTING THEO id_rb =====
    if (pkt.id_rb == 1) {
      // ➜ GỬI QUA ESP-NOW CHO RB1
      esp_now_send(peerAddress, (uint8_t*)&pkt, sizeof(Packet));
    }
    else if (pkt.id_rb == 2) {
      // ➜ GỬI XUỐNG STM32 QUA UART
      Serial.write((uint8_t*)&pkt, sizeof(Packet));
    }
    // id khác → bỏ
  }

  updateLED();
} 

/* ===================== UART PARSER ===================== */

bool readPacketUART(Packet &pkt) {
  static uint8_t buffer[PACKET_SIZE];
  static uint8_t index = 0;

  while (Serial.available()) {
    uint8_t b = Serial.read();

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