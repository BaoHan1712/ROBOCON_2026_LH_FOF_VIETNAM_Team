#include <WiFi.h>
#include <esp_now.h>

/* ================= CONFIG ================= */

#define UART_BAUDRATE 115200
#define PACKET_SIZE   8

#define START_BYTE 0x02
#define END_BYTE   0x03

#define LED_PIN 2

/* ================= STRUCT ================= */

struct Packet {
  uint8_t start;
  uint8_t id_rb;
  uint8_t state;
  uint8_t move;
  uint8_t action;
  uint8_t block_id;
  uint8_t checksum;
  uint8_t end;
} __attribute__((packed));

struct UARTParser {
  uint8_t buf[PACKET_SIZE];
  uint8_t idx = 0;
};

UARTParser parser;

/* ================= ESP NOW ================= */

uint8_t peerAddress[] = {0x68, 0xFE, 0x71, 0xF8, 0x20, 0x8C};

void onDataSent(const wifi_tx_info_t*, esp_now_send_status_t status) {}

/* ================= LED NON-BLOCK ================= */

bool ledState = false;
unsigned long ledTimer = 0;

void triggerLED()
{
  digitalWrite(LED_PIN, HIGH);
  ledState = true;
  ledTimer = millis();
}

void updateLED()
{
  if (ledState && (millis() - ledTimer >= 500))
  {
    digitalWrite(LED_PIN, LOW);
    ledState = false;
  }
}

/* ================= CHECK ================= */

uint8_t calcChecksum(const Packet &p)
{
  return (p.start + p.id_rb + p.state +
          p.move + p.action + p.block_id) & 0xFF;
}

bool validatePacket(const Packet &p)
{
  return p.start == START_BYTE &&
         p.end   == END_BYTE &&
         p.checksum == calcChecksum(p);
}

/* ================= UART PARSER ================= */

bool readPacketUART(HardwareSerial &uart, UARTParser &parser, Packet &pkt)
{
  while (uart.available())
  {
    uint8_t b = uart.read();

    if (parser.idx == 0 && b != START_BYTE)
      continue;

    parser.buf[parser.idx++] = b;

    if (parser.idx == PACKET_SIZE)
    {
      parser.idx = 0;

      if (parser.buf[PACKET_SIZE - 1] != END_BYTE)
        return false;

      memcpy(&pkt, parser.buf, PACKET_SIZE);
      return true;
    }
  }
  return false;
}

/* ================= SETUP ================= */

void setup()
{
  Serial.begin(UART_BAUDRATE);   // UART0: RX=3, TX=1

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.mode(WIFI_STA);
  esp_now_init();
  esp_now_register_send_cb(onDataSent);

  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, peerAddress, 6);
  esp_now_add_peer(&peer);
}

/* ================= LOOP ================= */

void loop()
{
  Packet pkt;

  // nhận UART từ STM32
  if (readPacketUART(Serial, parser, pkt))
  {
    if (validatePacket(pkt))
    {
      // bật LED không delay
      triggerLED();

      // gửi ESP-NOW
      esp_now_send(peerAddress, (uint8_t*)&pkt, sizeof(Packet));
    }
  }

  // cập nhật LED (tắt sau 500ms)
  updateLED();
}