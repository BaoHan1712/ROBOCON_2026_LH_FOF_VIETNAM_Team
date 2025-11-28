#include <WiFi.h>
#include <esp_now.h>

#define DEVICE_NAME "ESP32-A"

//================ UART PINS STM32 ==================
#define RXD1 18  // RX từ STM32 TX
#define TXD1 17  // TX về STM32 RX (nếu cần)
#define BAUD_RATE 921600  // tốc độ STM32 → ESP32-A

//================ MAC của ESP32-B ==================
uint8_t peerMAC[] = { 0x34, 0x5F, 0x45, 0xAA, 0x05, 0xEC };  // Sửa đúng MAC ESP-B

//================ BUFFER TỪ STM32 ==================
#define STM_BUF_MAX 200
char stmBuf[STM_BUF_MAX];
uint16_t stmIdx = 0;
uint8_t stmFFCount = 0;

//================ CALLBACK GỬI ESP-NOW ==================
void onDataSent(const esp_now_send_info_t *info, esp_now_send_status_t status) {
  const uint8_t *mac = info->des_addr;
  Serial.printf("SENT → %02X:%02X:%02X:%02X:%02X:%02X [%s]\n",
                mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
                status == ESP_NOW_SEND_SUCCESS ? "OK" : "FAIL");
}

//================ NHẬN TỪ ESP-B (lệnh từ Nextion) ==================
void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  char recvMsg[200];
  if (len >= 200) len = 199;
  memcpy(recvMsg, data, len);
  recvMsg[len] = '\0';

  Serial.printf("📩 From ESP-B → STM32: %s\n", recvMsg);

  // Forward xuống STM32 (tuỳ bạn, ở đây mình kết thúc bằng '\n')
  Serial1.print(recvMsg);
  Serial1.write('\n');
}

//================ HÀM TÁCH GÓI TỪ STM32 (FF FF FF) ==================
void readFromSTM32() {
  while (Serial1.available()) {
    uint8_t c = Serial1.read();

    if (c == 0xFF) {
      // gặp 0xFF → tăng đếm
      stmFFCount++;

      if (stmFFCount == 3) {
        // Kết thúc 1 gói
        stmBuf[stmIdx] = '\0';

        // Lọc ký tự in được (loại bỏ rác ���)
        char clean[STM_BUF_MAX];
        uint16_t j = 0;
        for (uint16_t i = 0; i < stmIdx; i++) {
          char ch = stmBuf[i];
          if (ch >= 32 && ch <= 126) {  // chỉ giữ ASCII printable
            if (j < STM_BUF_MAX - 1) clean[j++] = ch;
          }
        }
        clean[j] = '\0';

        if (j > 0) {
          Serial.print("📥 From STM32 (CLEAN): ");
          Serial.println(clean);

          // GỬI 1 GÓI SẠCH SANG ESP-B
          esp_now_send(peerMAC, (uint8_t*)clean, strlen(clean));
          delayMicroseconds(200);  // giảm stress ESP-NOW
        }

        // reset buffer cho gói mới
        stmIdx = 0;
        stmFFCount = 0;
      }
    } else {
      // ký tự thường → reset FF counter
      stmFFCount = 0;

      // chỉ lưu ký tự ASCII (loại bỏ control, ngoại trừ FF đã xử lý ở trên)
      if (c >= 32 && c <= 126) {
        if (stmIdx < STM_BUF_MAX - 1) {
          stmBuf[stmIdx++] = (char)c;
        }
      }
      // các ký tự khác (0x0A, 0x00...) bỏ qua, không lưu
    }
  }
}

//================ SETUP ==================
void setup() {
  Serial.begin(115200);
  Serial1.begin(BAUD_RATE, SERIAL_8N1, RXD1, TXD1);

  WiFi.mode(WIFI_STA);
  Serial.printf("[%s] MAC: %s\n", DEVICE_NAME, WiFi.macAddress().c_str());

  if (esp_now_init() != ESP_OK) {
    Serial.println("❌ ESP-NOW init failed!");
    return;
  }

  esp_now_register_send_cb(onDataSent);
  esp_now_register_recv_cb(onDataRecv);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, peerMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  peerInfo.ifidx = WIFI_IF_STA;
  esp_now_add_peer(&peerInfo);

  Serial.println("✅ ESP32-A READY (STM32 921600 → ESP-NOW)!");
}

//================ LOOP ==================
void loop() {
  readFromSTM32();   // đọc liên tục, tách gói FF FF FF
}
