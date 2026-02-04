#include <Arduino.h>

/* ===================== CONFIG ===================== */

#define UART_BAUDRATE 115200
#define PACKET_SIZE   8

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

/* ===================== LED FUNCTION ===================== */

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

/* ===================== CHECKSUM ===================== */
// XOR checksum
uint8_t calcChecksum(const Packet &p) {
  return p.id_rb ^
         p.state ^
         p.move ^
         p.action ^
         p.block_id;
}

/* ===================== UART RECEIVE (USB) ===================== */

void handlePacket(const Packet &p) {
  Serial.println("Packet OK:");
  Serial.printf(
    "id_rb=%d state=%d move=%d action=%d block=%d\n",
    p.id_rb, p.state, p.move, p.action, p.block_id
  );

  blinkLED();
}

void readUSBSerial() {
  static uint8_t buffer[PACKET_SIZE];
  static uint8_t index = 0;

  while (Serial.available()) {
    uint8_t byteIn = Serial.read();

    // Sync START_BYTE
    if (index == 0 && byteIn != START_BYTE) {
      continue;
    }

    buffer[index++] = byteIn;

    if (index == PACKET_SIZE) {
      Packet p;
      memcpy(&p, buffer, PACKET_SIZE);
      index = 0;

      if (p.end != END_BYTE) {
        Serial.println("ERR: END byte");
        return;
      }

      if (p.checksum != calcChecksum(p)) {
        Serial.println("ERR: Checksum");
        return;
      }

      handlePacket(p);
    }
  }
}

/* ===================== SETUP ===================== */

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(UART_BAUDRATE);
  while (!Serial);   // đợi USB CDC (quan trọng với ESP32-S3)

  Serial.println("ESP32 USB UART Receiver Ready");
}

/* ===================== LOOP ===================== */

void loop() {
  readUSBSerial();
  updateLED();
}
