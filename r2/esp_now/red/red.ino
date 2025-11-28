#include <WiFi.h>
#include <esp_now.h>

#define DEVICE_NAME "ESP32-B"

// ================== UART Nextion ==================
#define NEXTION_TX 17   // ESP32 TX1 → Nextion RX
#define NEXTION_RX 18   // ESP32 RX1 → Nextion TX
#define NEXTION_BAUD 9600

HardwareSerial nextionSerial(1);

// ================== MAC ESP32-A ===================
uint8_t peerMAC[] = { 0xC4, 0xDD, 0x57, 0x7B, 0xA7, 0x30 };  // Sửa đúng MAC ESP-A

// ================== BUFFER NHẬN TỪ NEXTION ==================
#define NEX_BUF_MAX 200
char nexInBuf[NEX_BUF_MAX];
uint16_t nexIdx = 0;
uint8_t nexFFCount = 0;

// ================== GỬI RAW LỆNH VÀO NEXTION ==================
void sendRawToNextion(const char *cmd) {
  nextionSerial.print(cmd);
  nextionSerial.write(0xFF);
  nextionSerial.write(0xFF);
  nextionSerial.write(0xFF);

  Serial.print("📤 To Nextion: ");
  Serial.println(cmd);
}

// ================== ĐỌC EVENT TỪ NEXTION (FF FF FF) ==================
void readFromNextion() {
  while (nextionSerial.available()) {
    uint8_t c = nextionSerial.read();

    if (c == 0xFF) {
      nexFFCount++;

      if (nexFFCount == 3) {
        nexInBuf[nexIdx] = '\0';

        // lọc ký tự in được
        char clean[NEX_BUF_MAX];
        uint16_t j = 0;
        for (uint16_t i = 0; i < nexIdx; i++) {
          char ch = nexInBuf[i];
          if (ch >= 32 && ch <= 126) {
            if (j < NEX_BUF_MAX - 1) clean[j++] = ch;
          }
        }
        clean[j] = '\0';

        if (j > 0) {
          Serial.print("📥 From Nextion (CLEAN): ");
          Serial.println(clean);

          // Gửi lệnh Nextion (như H_KEP, MENU1, ...) sang ESP-A
          esp_now_send(peerMAC, (uint8_t*)clean, strlen(clean));
          delayMicroseconds(200);
          Serial.printf("📤 SENT TO ESP-A: %s\n", clean);
        }

        nexIdx = 0;
        nexFFCount = 0;
      }
    } else {
      nexFFCount = 0;

      if (c >= 32 && c <= 126) {
        if (nexIdx < NEX_BUF_MAX - 1) {
          nexInBuf[nexIdx++] = (char)c;
        }
      }
      // bỏ qua các control khác
    }
  }
}

// ================== CALLBACK NHẬN TỪ ESP-A ==================
void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
  char recvMsg[200];
  if (len >= 200) len = 199;
  memcpy(recvMsg, incomingData, len);
  recvMsg[len] = '\0';

  Serial.printf("📡 From ESP-A → %s\n", recvMsg);

  // Chuỗi recvMsg đã là lệnh kiểu t5.txt="Lazer trai 19"
  // → Gửi thẳng vào Nextion + FF FF FF
  sendRawToNextion(recvMsg);
}

// ================== SETUP ==================
void setup() {
  Serial.begin(115200);
  nextionSerial.begin(NEXTION_BAUD, SERIAL_8N1, NEXTION_RX, NEXTION_TX);

  WiFi.mode(WIFI_STA);
  Serial.printf("[%s] MAC: %s\n", DEVICE_NAME, WiFi.macAddress().c_str());

  if (esp_now_init() != ESP_OK) {
    Serial.println("❌ ESP-NOW init failed!");
    return;
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, peerMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  peerInfo.ifidx = WIFI_IF_STA;
  esp_now_add_peer(&peerInfo);

  esp_now_register_recv_cb(onDataRecv);

  Serial.println("✅ ESP32-B READY (ESP-NOW ↔ Nextion 9600)!");
}

// ================== LOOP ==================
void loop() {
  readFromNextion();  // đọc event từ Nextion, gửi sang ESP-A
}
