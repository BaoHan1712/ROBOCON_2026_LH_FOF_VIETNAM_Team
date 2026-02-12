#include <WiFi.h>
#include <esp_now.h>

/* ================= CONFIG ================= */

#define UART_BAUDRATE 115200
#define PACKET_SIZE   8

#define START_BYTE 0x02
#define END_BYTE   0x03

#define UART_PC_RX 3
#define UART_PC_TX 1

#define UART_STM_RX 16
#define UART_STM_TX 17

#define LED_PIN 2
#define QUEUE_SIZE 32


/* =================================================
   ================= STRUCT =================
   ================================================= */

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


struct PacketQueue {
  Packet buf[QUEUE_SIZE];
  volatile uint8_t head = 0;
  volatile uint8_t tail = 0;
};


/* ================= GLOBAL ================= */

PacketQueue q_toSTM;
PacketQueue q_toESPNow;
PacketQueue q_toPC;

bool led_on = false;
unsigned long led_start = 0;

uint8_t peerAddress[] = {0x68,0xFE,0x71,0xFA,0xC5,0xE4};
bool espnow_ready = true;


/* =================================================
   ================= LED =================
   ================================================= */

void triggerLED()
{
  digitalWrite(LED_PIN, HIGH);
  led_on = true;
  led_start = millis();
}

void updateLED()
{
  if (led_on && millis() - led_start > 100)
  {
    digitalWrite(LED_PIN, LOW);
    led_on = false;
  }
}


/* =================================================
   ================= QUEUE =================
   ================================================= */

bool qPush(PacketQueue &q, const Packet &p)
{
  uint8_t next = (q.head + 1) % QUEUE_SIZE;
  if (next == q.tail) return false;

  q.buf[q.head] = p;
  q.head = next;
  return true;
}

bool qPop(PacketQueue &q, Packet &p)
{
  if (q.head == q.tail) return false;

  p = q.buf[q.tail];
  q.tail = (q.tail + 1) % QUEUE_SIZE;
  return true;
}


/* =================================================
   ================= CHECK =================
   ================================================= */

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


/* =================================================
   ================= UART PARSER =================
   ================================================= */

bool readPacketUART(HardwareSerial &uart, Packet &pkt)
{
  static uint8_t buf[PACKET_SIZE];
  static uint8_t idx = 0;

  while (uart.available())
  {
    uint8_t b = uart.read();

    if (idx == 0 && b != START_BYTE) continue;

    buf[idx++] = b;

    if (idx == PACKET_SIZE)
    {
      idx = 0;
      memcpy(&pkt, buf, PACKET_SIZE);
      return true;
    }
  }
  return false;
}


/* =================================================
   ================= ESP NOW =================
   ================================================= */

void onDataSent(const wifi_tx_info_t*, esp_now_send_status_t s)
{
  espnow_ready = (s == ESP_NOW_SEND_SUCCESS);
}

void onDataRecv(const esp_now_recv_info* info,
                const uint8_t* data,
                int len)
{
  if (len == sizeof(Packet))
  {
    Packet p;
    memcpy(&p, data, sizeof(Packet));

    if (validatePacket(p))
      qPush(q_toPC, p);
  }
}


void initESPNow()
{
  esp_now_init();

  esp_now_register_send_cb(onDataSent);
  esp_now_register_recv_cb(onDataRecv);

  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, peerAddress, 6);
  esp_now_add_peer(&peer);
}


/* =================================================
   ================= SETUP =================
   ================================================= */

void setup()
{
  Serial.begin(UART_BAUDRATE);

  Serial1.begin(UART_BAUDRATE, SERIAL_8N1, UART_PC_RX, UART_PC_TX);
  Serial2.begin(UART_BAUDRATE, SERIAL_8N1, UART_STM_RX, UART_STM_TX);

  pinMode(LED_PIN, OUTPUT);

  WiFi.mode(WIFI_STA);
  initESPNow();
}


/* =================================================
   ================= LOOP (ROUTER) =================
   ================================================= */

void loop()
{
  Packet pkt;

  /* -------- PC -> Router -------- */
  if (readPacketUART(Serial1, pkt) && validatePacket(pkt))
  {
    triggerLED();

    if (pkt.id_rb == 1)
      qPush(q_toESPNow, pkt);
    else if (pkt.id_rb == 2)
      qPush(q_toSTM, pkt);
  }


  /* -------- STM -> Router -------- */
  if (readPacketUART(Serial2, pkt) && validatePacket(pkt))
  {
    triggerLED();
    qPush(q_toPC, pkt);
  }


  /* -------- SEND STM -------- */
  if (qPop(q_toSTM, pkt))
    Serial2.write((uint8_t*)&pkt, sizeof(Packet));


  /* -------- SEND ESP-NOW -------- */
  if (espnow_ready && qPop(q_toESPNow, pkt))
    esp_now_send(peerAddress, (uint8_t*)&pkt, sizeof(Packet));


  /* -------- SEND PC -------- */
  if (qPop(q_toPC, pkt))
    Serial1.write((uint8_t*)&pkt, sizeof(Packet));


  updateLED();
}
