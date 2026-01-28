#include <WiFi.h>
#include <esp_now.h>

/* ===================== CONFIG ===================== */

#define UART_BAUDRATE   115200
#define PACKET_SIZE     8

#define START_BYTE      0x02
#define END_BYTE        0x03

#define LED_PIN         2
#define LED_BLINK_TIME  100   // ms

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

/* ===================== FUNCTION PROTOTYPE ===================== */

void blinkLED();
void updateLED();

bool validatePacket(const Packet &pkt);
uint8_t calcChecksum(const Packet &pkt);
bool checkPacketFromESPNow(const Packet &pkt);

/* ===================== SETUP ===================== */

void setup() {
  Serial.begin(UART_BAUDRATE);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    return;
  }

  esp_now_register_recv_cb(onDataRecv);
}

/* ===================== LOOP ===================== */

void loop() {
  updateLED();
}

/* ===================== ESP-NOW RX ===================== */

void onDataRecv(const esp_now_recv_info_t *recv_info,
                const uint8_t *incomingData,
                int len) {

  if (len != PACKET_SIZE) return;

  Packet pkt;
  memcpy(&pkt, incomingData, PACKET_SIZE);

  if (pkt.start != START_BYTE) return;
  if (pkt.end   != END_BYTE)   return;

  if (!validatePacket(pkt)) return;

  // ⭐ LỌC ROBOT THEO id_rb
  if (!checkPacketFromESPNow(pkt)) return;

  // ✅ GÓI HỢP LỆ
  blinkLED();

  // Gửi nguyên 8 byte xuống STM32
  Serial.write((uint8_t*)&pkt, PACKET_SIZE);
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

/* ===================== FILTER PACKET ===================== */
// Chỉ nhận robot có id_rb == 1
bool checkPacketFromESPNow(const Packet &pkt) {
  return (pkt.id_rb == 1);
}

/* ===================== LED ===================== */

void blinkLED() {
  digitalWrite(LED_PIN, HIGH);
  ledBlinking = true;
  ledTimestamp = millis();
}

void updateLED() {
  if (!ledBlinking) return;

  if (millis() - ledTimestamp >= LED_BLINK_TIME) {
    digitalWrite(LED_PIN, LOW);
    ledBlinking = false;
  }
}