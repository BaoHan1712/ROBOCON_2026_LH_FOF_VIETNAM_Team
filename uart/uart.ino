/****************************************************
 *  ESP32 → STM32 : Gửi packet dạng 
 *  Start(0x02) | Data(1 byte) | End(0x03)
 ****************************************************/

// ================= UART CONFIG =====================
#define UART_BAUD 115200

// ================= FUNCTION PROTOTYPES =============
void buildPacket(uint8_t dataByte, uint8_t *packet, size_t &packetSize);
void sendPacket(uint8_t *packet, size_t packetSize);

// ===================================================
void setup() {
    Serial.begin(UART_BAUD);   // UART gửi xuống STM32
    delay(1000);
    Serial.println("ESP32 Ready...");

    randomSeed(esp_random());  // dùng RNG của ESP32
}

// ===================================================
void loop() {

    // Random từ 1 đến 100
    uint8_t dataToSend = random(1, 101);   // random(min, max) → max không bao gồm

    uint8_t packet[10];
    size_t packetSize;

    // Tạo packet
    buildPacket(dataToSend, packet, packetSize);

    // Gửi xuống STM32
    sendPacket(packet, packetSize);

    delay(500);   // gửi mỗi 0.5 giây
}

// ===================================================
// =============== BUILD PACKET =======================
// ===================================================
void buildPacket(uint8_t dataByte, uint8_t *packet, size_t &packetSize) {
    packet[0] = 0x02;        // Start byte
    packet[1] = dataByte;    // Payload (1 byte)
    packet[2] = 0x03;        // End byte

    packetSize = 3;          // tổng số byte
}

// ===================================================
// ================= SEND PACKET =====================
// ===================================================
void sendPacket(uint8_t *packet, size_t packetSize) {
    Serial.write(packet, packetSize);
}
