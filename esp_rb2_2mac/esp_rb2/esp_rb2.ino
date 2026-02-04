#include <WiFi.h>
#include <esp_now.h>

/* =========================================================
   CONFIG
========================================================= */

uint8_t peerAddress1[] = {0x68, 0xFE, 0x71, 0xF8, 0x20, 0x8C};
uint8_t peerAddress2[] = {0x68, 0xFE, 0x71, 0xFA, 0xC5, 0xE4};

#define UART_BAUDRATE 115200
#define PACKET_SIZE   8

#define START_BYTE 0x02
#define END_BYTE   0x03

#define UART1_RX 3
#define UART1_TX 1
#define UART2_RX 16
#define UART2_TX 17

#define LED_PIN 2
#define LED_BLINK_TIME 100

/* =========================================================
   ESPNOW CONFIG
========================================================= */

#define TX_QUEUE_SIZE 50

volatile bool espnow_tx_busy = false;
bool espnow_ready = false;

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


/* =========================================================
   TX QUEUE (RING BUFFER)
========================================================= */

typedef struct {
  uint8_t mac[6];
  Packet pkt;
} TxItem;

TxItem tx_queue[TX_QUEUE_SIZE];

volatile uint16_t tx_head = 0;
volatile uint16_t tx_tail = 0;
volatile uint16_t tx_count = 0;


/* =========================================================
   LED
========================================================= */

bool ledBlinking = false;
unsigned long ledTimestamp = 0;


/* =========================================================
   QUEUE FUNCTIONS
========================================================= */

bool txQueuePush(uint8_t *mac, const Packet &pkt)
{
  if (tx_count >= TX_QUEUE_SIZE) return false;

  memcpy(tx_queue[tx_head].mac, mac, 6);
  tx_queue[tx_head].pkt = pkt;

  tx_head = (tx_head + 1) % TX_QUEUE_SIZE;
  tx_count++;

  return true;
}

bool txQueuePop(TxItem &out)
{
  if (tx_count == 0) return false;

  out = tx_queue[tx_tail];

  tx_tail = (tx_tail + 1) % TX_QUEUE_SIZE;
  tx_count--;

  return true;
}


/* =========================================================
   SEND NEXT (CORE LOGIC)
========================================================= */

void sendNextFromQueue()
{
  if (!espnow_ready) return;
  if (espnow_tx_busy) return;

  TxItem item;

  if (!txQueuePop(item)) return;

  espnow_tx_busy = true;

  esp_now_send(item.mac, (uint8_t*)&item.pkt, sizeof(Packet));
}


/* =========================================================
   CALLBACK
========================================================= */

void OnDataSent(const wifi_tx_info_t *, esp_now_send_status_t status)
{
  espnow_tx_busy = false;

  // gửi tiếp packet tiếp theo
  sendNextFromQueue();
}


/* =========================================================
   ESPNOW INIT
========================================================= */

void addPeer(uint8_t *mac)
{
  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, mac, 6);
  peer.channel = 0;
  peer.encrypt = false;

  esp_now_add_peer(&peer);
}

void initESPNow()
{
  if (esp_now_init() != ESP_OK) {
    espnow_ready = false;
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  addPeer(peerAddress1);
  addPeer(peerAddress2);

  espnow_ready = true;

  Serial.println("ESP-NOW ready");
}


/* =========================================================
   UART PARSER
========================================================= */

bool readPacketUART(HardwareSerial &uart, Packet &pkt)
{
  static uint8_t buffer[PACKET_SIZE];
  static uint8_t index = 0;

  while (uart.available())
  {
    uint8_t b = uart.read();

    if (index == 0 && b != START_BYTE)
      continue;

    buffer[index++] = b;

    if (index == PACKET_SIZE)
    {
      index = 0;
      memcpy(&pkt, buffer, PACKET_SIZE);

      return true;
    }
  }

  return false;
}

uint8_t calcChecksum(const Packet &pkt)
{
  return (pkt.start +
          pkt.id_rb +
          pkt.state +
          pkt.move +
          pkt.action +
          pkt.block_id) & 0xFF;
}

bool validatePacket(const Packet &pkt)
{
  return pkt.start == START_BYTE &&
         pkt.end   == END_BYTE &&
         pkt.checksum == calcChecksum(pkt);
}


/* =========================================================
   LED
========================================================= */

void blinkLED()
{
  digitalWrite(LED_PIN, HIGH);
  ledBlinking = true;
  ledTimestamp = millis();
}

void updateLED()
{
  if (ledBlinking && millis() - ledTimestamp > LED_BLINK_TIME)
  {
    digitalWrite(LED_PIN, LOW);
    ledBlinking = false;
  }
}


/* =========================================================
   SETUP
========================================================= */

void setup()
{
  Serial.begin(115200);

  Serial1.begin(UART_BAUDRATE, SERIAL_8N1, UART1_RX, UART1_TX);
  Serial2.begin(UART_BAUDRATE, SERIAL_8N1, UART2_RX, UART2_TX);

  pinMode(LED_PIN, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  initESPNow();
}


/* =========================================================
   LOOP
========================================================= */

void loop()
{
  Packet pkt;

  if (readPacketUART(Serial1, pkt))
  {
    if (!validatePacket(pkt)) return;

    blinkLED();

    switch (pkt.id_rb)
    {
      case 1:
        txQueuePush(peerAddress1, pkt);
        break;

      case 2:
        txQueuePush(peerAddress2, pkt);
        break;

      default:
        Serial2.write((uint8_t*)&pkt, sizeof(Packet));
        break;
    }

    // thử gửi nếu rảnh
    sendNextFromQueue();
  }

  updateLED();
}
