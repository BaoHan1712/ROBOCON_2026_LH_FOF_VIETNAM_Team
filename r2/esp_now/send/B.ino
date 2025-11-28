#include <WiFi.h>
#include <esp_now.h>

#define DEVICE_NAME "ESP32-B"

// ================== UART Nextion ==================
#define NEXT_RX 18
#define NEXT_TX 17
#define NEXT_BAUD 9600

HardwareSerial nex(1);

// ================== MAC ESP32-A ===================
uint8_t peerMAC[] = {0xE4, 0x65, 0xB8, 0x75, 0x3C, 0x20};

// ===================================================
// ========== CALLBACK GỬI ESPNOW ====================
// ===================================================
void onDataSent(const wifi_tx_info_t *info, esp_now_send_status_t status) {
  Serial.print("📤 ESP-NOW → A: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "OK" : "FAIL");
}

// ===================================================
// ============ NHẬN TỪ ESP-A (GỬI XUỐNG NEXTION) ====
// ===================================================
void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
  if (len <= 0) return;

  Serial.print("📡 From ESP-A → Nextion: ");
  for (int i = 0; i < len; i++) Serial.write(incomingData[i]);
  Serial.println();

  // gửi xuống Nextion
  nex.write(incomingData, len);
  nex.write(0xFF);
  nex.write(0xFF);
  nex.write(0xFF);
}

// ===================================================
// === ONLY RECEIVE NUMBER VALUE (0x71) FROM NEXTION =
// ===================================================
void readFromNextion() {
  static uint8_t buf[8];
  static uint8_t idx = 0;

  while (nex.available()) {
    uint8_t c = nex.read();

    // Frame number start
    if (c == 0x71 && idx == 0) {
      buf[idx++] = c;
      continue;
    }

    // Collect frame bytes
    if (idx > 0) {
      buf[idx++] = c;

      // Full frame: 71 + 4 byte + FF FF FF = 8 bytes
      if (idx == 8) {

        int value = (buf[4] << 24) | (buf[3] << 16) | (buf[2] << 8) | buf[1];

        Serial.printf("🔢 Number from Nextion = %d\n", value);

        // Send NUMBER via ESP-NOW (raw 4 bytes)
        esp_now_send(peerMAC, (uint8_t*)&value, sizeof(value));

        idx = 0;  // reset for next frame
      }
    }
  }
}

// ===================================================
// ====================== SETUP =======================
// ===================================================
void setup() {
  Serial.begin(115200);
  nex.begin(NEXT_BAUD, SERIAL_8N1, NEXT_RX, NEXT_TX);

  WiFi.mode(WIFI_STA);
  Serial.printf("[%s] MAC: %s\n", DEVICE_NAME, WiFi.macAddress().c_str());

  if (esp_now_init() != ESP_OK) {
    Serial.println("❌ ESP-NOW init fail!");
    return;
  }

  esp_now_register_send_cb(onDataSent);
  esp_now_register_recv_cb(onDataRecv);

  // Add peer
  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, peerMAC, 6);
  peer.channel = 0;
  peer.encrypt = false;
  peer.ifidx = WIFI_IF_STA;

  if (esp_now_add_peer(&peer) != ESP_OK) {
    Serial.println("❌ Add peer fail!");
  }

  Serial.println("🚀 ESP32-B READY (Nextion NUMBER MODE)");
}

// ===================================================
// ====================== LOOP ========================
// ===================================================
void loop() {
  readFromNextion();
}
