#include <WiFi.h>
#include <esp_now.h>

/* ===================== CONFIG ===================== */

#define UART_BAUDRATE 115200
#define PACKET_SIZE 8
#define LED_PIN 2   // LED 2 ESP32

bool ledBlinking = false;
unsigned long ledTimestamp = 0;
#define LED_BLINK_TIME 1000   // ms


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

/* ===================== FUNCTION DECLARE ===================== */

void initUART();
void initESPNow();
void blinkLED();
void onDataRecv(const esp_now_recv_info_t *recv_info,
                const uint8_t *incomingData,
                int len);

void printPacket(const Packet &pkt);

/* ===================== SETUP ===================== */

void setup() {
  Serial.begin(UART_BAUDRATE);   // UART xuống STM32
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  initUART();
  initESPNow();
}

/* ===================== LOOP ===================== */

void loop() {
updateLED();
}

/* ===================== FUNCTION IMPLEMENT ===================== */

// --- UART INIT ---
void initUART() {
  // KHÔNG print – UART để gửi binary
}

// --- ESP-NOW INIT ---
void initESPNow() {
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    return;
  }

  esp_now_register_recv_cb(onDataRecv);
}

// --- ESP-NOW RECEIVE CALLBACK ---
void onDataRecv(const esp_now_recv_info_t *recv_info,
                const uint8_t *incomingData,
                int len) {

  if (len != PACKET_SIZE) {
    Serial.println("RX ERROR: Wrong packet size");
    return;
  }

  Packet pkt;
  memcpy(&pkt, incomingData, PACKET_SIZE);

  // Blink LED báo nhận gói
  blinkLED();

  // ===== DEBUG PRINT =====
  printPacket(pkt);

  // ===== (OPTIONAL) GỬI XUỐNG STM32 =====
  // Nếu đang debug ESP-NOW thì có thể comment dòng này
  Serial.write((uint8_t*)&pkt, PACKET_SIZE);
}
// --- LED BLINK ---
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

void printPacket(const Packet &pkt) {
  Serial.println("---- ESP-NOW RX PACKET ----");
  Serial.print("start    = 0x"); Serial.println(pkt.start, HEX);
  Serial.print("id_rb    = ");   Serial.println(pkt.id_rb);
  Serial.print("state    = ");   Serial.println(pkt.state);
  Serial.print("move     = ");   Serial.println(pkt.move);
  Serial.print("action   = ");   Serial.println(pkt.action);
  Serial.print("block_id = ");   Serial.println(pkt.block_id);
  Serial.print("checksum = 0x"); Serial.println(pkt.checksum, HEX);
  Serial.print("end      = 0x"); Serial.println(pkt.end, HEX);
  Serial.println("---------------------------");
}

