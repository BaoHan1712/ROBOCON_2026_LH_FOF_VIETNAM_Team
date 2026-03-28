#include <WiFi.h>
#include <esp_now.h>

/* =========================================================
    CONFIG
   ========================================================= */
uint8_t targetMAC[] = {0x68, 0xFE, 0x71, 0xF8, 0x20, 0x8C};

#define UART_BAUDRATE 115200
#define PACKET_SIZE    8
#define START_BYTE     0x02
#define END_BYTE       0x03
#define LED_PIN        2
#define LED_BLINK_TIME 500 // Giảm xuống để dễ quan sát tín hiệu

/* =========================================================
    DATA STRUCT
   ========================================================= */
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

QueueHandle_t tx_queue;
#define QUEUE_LEN 50
volatile bool espnow_busy = false;

/* =========================================================
    CALLBACK - FIX CHO PHIÊN BẢN MỚI NHẤT (v5.5+)
   ========================================================= */
// Chú ý: Tham số đầu tiên phải là const wifi_tx_info_t *
void OnDataSent(const wifi_tx_info_t *info, esp_now_send_status_t status) {
  espnow_busy = false; 
}

/* =========================================================
    UTILITIES
   ========================================================= */
uint8_t calcChecksum(const Packet &pkt) {
  return (pkt.start + pkt.id_rb + pkt.state + pkt.move + 
          pkt.action + pkt.block_id) & 0xFF;
}

bool validatePacket(const Packet &pkt) {
  return (pkt.start == START_BYTE && 
          pkt.end == END_BYTE && 
          pkt.checksum == calcChecksum(pkt));
}

void initESPNow() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    ESP.restart();
  }

  // Đăng ký callback (Ép kiểu về esp_now_send_cb_t nếu cần, nhưng định nghĩa trên là chuẩn)
  esp_now_register_send_cb(OnDataSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, targetMAC, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
  }
}

bool parseSerial(Packet &pkt) {
  static uint8_t buf[PACKET_SIZE];
  static uint8_t idx = 0;

  while (Serial.available()) {
    uint8_t b = Serial.read();
    if (idx == 0 && b != START_BYTE) continue;
    buf[idx++] = b;
    if (idx == PACKET_SIZE) {
      idx = 0;
      memcpy(&pkt, buf, PACKET_SIZE);
      if (validatePacket(pkt)) return true;
    }
  }
  return false;
}

/* =========================================================
    MAIN
   ========================================================= */
void setup() {
  // Serial này nhận dữ liệu từ USB
  Serial.begin(UART_BAUDRATE);
  pinMode(LED_PIN, OUTPUT);
  
  tx_queue = xQueueCreate(QUEUE_LEN, sizeof(Packet));
  
  initESPNow();
  Serial.println("System Ready - Fixed for IDF 5.5");
}

void loop() {
  Packet pkt;

  // 1. Nhận dữ liệu từ USB Serial
  if (parseSerial(pkt)) {
    if (xQueueSend(tx_queue, &pkt, 0) == pdPASS) {
      digitalWrite(LED_PIN, HIGH);
    }
  }

  // 2. Tắt LED (non-blocking)
  static uint32_t ledTimer = 0;
  if (digitalRead(LED_PIN) == HIGH) {
    if (millis() - ledTimer > LED_BLINK_TIME) {
      digitalWrite(LED_PIN, LOW);
      ledTimer = millis();
    }
  }

  // 3. Gửi dữ liệu từ Queue qua ESP-NOW
  if (!espnow_busy && uxQueueMessagesWaiting(tx_queue) > 0) {
    Packet toSend;
    if (xQueueReceive(tx_queue, &toSend, 0) == pdTRUE) {
      espnow_busy = true;
      esp_err_t result = esp_now_send(targetMAC, (uint8_t *)&toSend, sizeof(Packet));
      if (result != ESP_OK) {
        espnow_busy = false; // Reset cờ nếu gọi hàm gửi thất bại
      }
    }
  }
}