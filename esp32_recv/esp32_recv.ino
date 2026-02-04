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
    return;   // bỏ gói sai kích thước
  }

  // Nhấp nháy LED báo nhận data
  blinkLED();

  // GỬI NGUYÊN GÓI XUỐNG STM32 (RAW BINARY)
  Serial.write(incomingData, PACKET_SIZE);
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

