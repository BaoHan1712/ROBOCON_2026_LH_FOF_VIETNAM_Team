#include <WiFi.h>
#include <esp_now.h>

#define DEVICE_NAME "ESP32-A"

// ===================== UART STM32 =====================
#define STM_TX 18
#define STM_RX 17
#define STM_BAUD 921600

HardwareSerial stmSerial(1);

// ===================== MAC ESP32-B =====================
uint8_t peerMAC_B[] = {0x34, 0x5F, 0x45, 0xAA, 0x05, 0xEC};

// ===================== MAP 12 Ô (TRONG RỪNG) ==========================
// cellMap[i] = 0       → chưa set, mặc định free
// cellMap[i] = 10..13  → ô 1  (state 0..3)
// cellMap[i] = 20..23  → ô 2
// ...
// cellMap[i] = 120..123 → ô 12
int cellMap[13];   // dùng từ 1..12

// Đếm R2 theo từng cột 1..3 (trong rừng)
int r2col[4] = {0, 0, 0, 0};

// ===================== HÀM CHUYỂN ĐỔI INDEX ======================
// Bố trí 4x3 (12 ô):
//  |10|11|12|  ← row 1  (PAD OUT)
//  |7 |8 |9 |
//  |4 |5 |6 |
//  |1 |2 |3 |  ← row 4 (PAD IN)
//
// v: 1..12
int toRow(int v) { return 4 - ((v - 1) / 3); }           // 1..12 → row 1..4
int toCol(int v) { return ((v - 1) % 3) + 1; }           // 1..12 → col 1..3
int toIndex(int r, int c) { return (4 - r) * 3 + c; }    // row,col → 1..12

// ===================== QUY TẮC ĐI QUA Ô ======================
// 0 (chưa set) hoặc state 0/1/2 đi được, state 3 (RF) cấm
bool canEnterValue(int value) {
  if (value == 0) return true;
  int state = value % 10;
  return (state != 3);
}

// ===================== COST Ô & COST QUAY HƯỚNG ======================
// state 0 hoặc chưa set: 10s
// state 1 (R1), 2 (R2): 20s
// state 3 (RF): không đi được
int getCellCost(int cell) {
  if (cell < 1 || cell > 12) return 1000000000; // lỗi
  if (cellMap[cell] == 0) return 10;

  int state = cellMap[cell] % 10;
  if (state == 0) return 10;
  if (state == 1 || state == 2) return 20;
  return 1000000000; // RF → xem như vô cực
}

// prevDir, newDir: 0=UP,1=DOWN,2=LEFT,3=RIGHT
int rotationCost(int prevDir, int newDir) {
  if (prevDir < 0 || prevDir > 3) return 0;     // bước đầu tiên: không tính quay
  if (prevDir == newDir) return 0;
  return 3;  // quay hướng mất 3s
}

// ===================== R2 THEO CỘT ======================
void computeR2Columns() {
  for (int c = 1; c <= 3; c++) r2col[c] = 0;

  for (int cell = 1; cell <= 12; cell++) {
    int state = cellMap[cell] % 10;
    if (state == 2) {
      int col = toCol(cell);
      r2col[col]++;
    }
  }
}

// Hàng 2 & 3 của PAD (1–3) có RF không?
bool hasRF_on_row2_3(int pad) {
  // pad: 1,2,3  (hàng 4)
  // hàng 3: pad+3, hàng 2: pad+6
  int s2 = cellMap[pad + 3] % 10; // hàng 3
  int s3 = cellMap[pad + 6] % 10; // hàng 2
  return (s2 == 3 || s3 == 3);
}

// Điều kiện R2 theo luật "2 cột"
bool r2Condition(int pad) {
  if (pad == 1) {
    // PAD1: cột 1 + cột 2 >= 2
    return (r2col[1] + r2col[2] >= 2);
  }
  if (pad == 3) {
    // PAD3: cột 2 + cột 3 >= 2
    return (r2col[2] + r2col[3] >= 2);
  }
  if (pad == 2) {
    // PAD2: (1+2) hoặc (2+3) >= 2
    return ((r2col[1] + r2col[2] >= 2) ||
            (r2col[2] + r2col[3] >= 2));
  }
  return false;
}

// Đếm R1 ở hàng 2 & 3 của PAD (để tối thiểu R1)
int countR1_row2_3(int pad) {
  int r1 = 0;
  // pad+3 → hàng 3, pad+6 → hàng 2
  if (cellMap[pad + 3] % 10 == 1) r1++;
  if (cellMap[pad + 6] % 10 == 1) r1++;
  return r1;
}

// Kiểm tra "hàng 2 & 3 đều là R2"
bool hasBothR2_row2_3(int pad) {
  int s2 = cellMap[pad + 3] % 10;  // hàng 3
  int s3 = cellMap[pad + 6] % 10;  // hàng 2
  return (s2 == 2 && s3 == 2);
}

// ===================== CHỌN PAD IN ======================
//
// PAD IN = 1,2,3 (hàng 4 trong rừng) tương ứng 3 cổng:
//  cổng thật robot đi: 13,14,15 do STM32 xử lý theo cột
//
// Ưu tiên:
// 0) Nếu 1/2/3 có R2 → phải lấy R2 trước (3→2→1)
// 1) (bỏ) – ưu tiên hàng 1 có R2 không dùng ở đây
// 2) Hàng 2 & 3 (pad+3,pad+6) đều là R2
// 3) Đủ R2 theo 2 cột (r2Condition)
// 4) Ít R1 nhất (hàng 2 & 3)
// 5) Ưu tiên 3 → 2 → 1
//
int choosePadIn() {
  computeR2Columns();

  int padPriority[3] = {3, 2, 1}; // phải → trái

  // 0️⃣ ƯU TIÊN TUYỆT ĐỐI: HÀNG 4 (1–3) CÓ R2 PHẢI LẤY TRƯỚC
  int forcedPad = -1;

  if (cellMap[3] % 10 == 2) forcedPad = 3;
  else if (cellMap[2] % 10 == 2) forcedPad = 2;
  else if (cellMap[1] % 10 == 2) forcedPad = 1;

  if (forcedPad != -1) {
    Serial.printf("🔥 ƯU TIÊN HÀNG 4 CÓ R2 → PAD IN = %d\n", forcedPad);
    return forcedPad;
  }

  // 2️⃣ Ưu tiên hàng 2 & 3 đều là R2
  for (int i = 0; i < 3; i++) {
    int pad = padPriority[i];
    if (hasRF_on_row2_3(pad)) continue;
    if (hasBothR2_row2_3(pad)) {
      Serial.printf("🎯 PAD IN (2 R2 hàng 2/3) = %d\n", pad);
      return pad;
    }
  }

  // 3️⃣ Lọc các PAD hợp lệ theo R2 theo 2 cột + không RF
  int candidates[3];
  int candCount = 0;

  for (int i = 0; i < 3; i++) {
    int pad = padPriority[i];

    if (hasRF_on_row2_3(pad)) continue;
    if (!r2Condition(pad)) continue;

    candidates[candCount++] = pad;
  }

  if (candCount == 0) {
    Serial.println("❌ Không có PAD IN nào hợp lệ!");
    return -1;
  }

  // 4️⃣ Chọn PAD có ít R1 nhất (trong hàng 2 & 3)
  int bestPad = -1;
  int bestR1 = 999;

  for (int i = 0; i < candCount; i++) {
    int pad = candidates[i];
    int r1 = countR1_row2_3(pad);

    if (r1 < bestR1) {
      bestR1 = r1;
      bestPad = pad;
    }
    // nếu r1 bằng nhau → giữ bestPad hiện tại vì padPriority là 3→2→1
  }

  if (bestPad != -1) {
    Serial.printf("🎯 PAD IN (ít R1 nhất, ưu tiên phải→trái) = %d\n", bestPad);
    return bestPad;
  }

  Serial.println("❌ Không tìm được PAD IN sau khi lọc!");
  return -1;
}

// ===================== CHỌN PAD OUT ======================
// PAD OUT = ô hàng 1 (10/11/12) cùng cột với PAD IN
int choosePadOut(int padIn) {
  int col = toCol(padIn);
  int padOut = toIndex(1, col); // row=1 → 10/11/12
  Serial.printf("📌 PAD OUT = %d\n", padOut);
  return padOut;
}

// ===================== DIJKSTRA (CELL + DIR) ======================
//
// dirs: 0=UP(-1,0), 1=DOWN(+1,0), 2=LEFT(0,-1), 3=RIGHT(0,+1)
//

String runDijkstra(int start, int target) {
  const int INF = 1000000000;

  int dist[13][4];
  bool used[13][4];
  int parentCell[13][4];
  int parentDir[13][4];

  for (int i = 0; i <= 12; i++) {
    for (int d = 0; d < 4; d++) {
      dist[i][d] = INF;
      used[i][d] = false;
      parentCell[i][d] = -1;
      parentDir[i][d] = -1;
    }
  }

  // Nếu start == target: trả về chính nó
  if (start == target) {
    String s = String(start);
    return s;
  }

  // ====== KHỞI TẠO: từ start, bước đầu tiên không tính quay hướng ======
  int sr = toRow(start);
  int sc = toCol(start);

  // 4 hướng khả dụng từ start
  const int dr4[4] = {-1, 1, 0, 0};
  const int dc4[4] = {0, 0, -1, 1};

  for (int dir = 0; dir < 4; dir++) {
    int nr = sr + dr4[dir];
    int nc = sc + dc4[dir];
    if (nr < 1 || nr > 4 || nc < 1 || nc > 3) continue;

    int nextCell = toIndex(nr, nc);
    if (!canEnterValue(cellMap[nextCell])) continue;

    int cost = getCellCost(nextCell); // bước đầu: không + rotationCost
    dist[nextCell][dir] = cost;
    parentCell[nextCell][dir] = start;
    parentDir[nextCell][dir] = -1;
  }

  // ====== DIJKSTRA ======
  while (true) {
    int bestCell = -1;
    int bestDir = -1;
    int bestDist = INF;

    // chọn state chưa dùng có dist nhỏ nhất
    for (int cell = 1; cell <= 12; cell++) {
      for (int d = 0; d < 4; d++) {
        if (!used[cell][d] && dist[cell][d] < bestDist) {
          bestDist = dist[cell][d];
          bestCell = cell;
          bestDir = d;
        }
      }
    }

    if (bestCell == -1) {
      // không còn state nào
      break;
    }

    used[bestCell][bestDir] = true;

    // nếu đã tới target: dừng
    if (bestCell == target) {
      break;
    }

    int r = toRow(bestCell);
    int c = toCol(bestCell);

    for (int newDir = 0; newDir < 4; newDir++) {
      int nr = r + dr4[newDir];
      int nc = c + dc4[newDir];
      if (nr < 1 || nr > 4 || nc < 1 || nc > 3) continue;

      int nextCell = toIndex(nr, nc);
      if (!canEnterValue(cellMap[nextCell])) continue;

      int moveCost = getCellCost(nextCell) + rotationCost(bestDir, newDir);
      int nd = dist[bestCell][bestDir] + moveCost;

      if (nd < dist[nextCell][newDir]) {
        dist[nextCell][newDir] = nd;
        parentCell[nextCell][newDir] = bestCell;
        parentDir[nextCell][newDir] = bestDir;
      }
    }
  }

  // chọn hướng tốt nhất tại target
  int finalDir = -1;
  int finalDist = INF;

  for (int d = 0; d < 4; d++) {
    if (dist[target][d] < finalDist) {
      finalDist = dist[target][d];
      finalDir = d;
    }
  }

  if (finalDir == -1) {
    Serial.println("❌ DIJKSTRA: không tìm được đường!");
    return "NO_PATH";
  }

  // ====== reconstruct path ======
  int route[50];
  int count = 0;

  int curCell = target;
  int curDir = finalDir;

  while (curCell != start && curCell != -1) {
    route[count++] = curCell;
    int pc = parentCell[curCell][curDir];
    int pd = parentDir[curCell][curDir];
    curCell = pc;
    curDir = pd;
  }

  // thêm start
  route[count++] = start;

  // tạo string từ start → target
  String out = "";
  for (int i = count - 1; i >= 0; i--) {
    out += String(route[i]);
    if (i > 0) out += " ";
  }

  Serial.print("🧭 Dijkstra route = ");
  Serial.println(out);
  Serial.print("⏱ Tổng thời gian (unit) = ");
  Serial.println(finalDist);

  return out;
}

// ================================================================
// ========== CALLBACK NHẬN DỮ LIỆU TỪ ESP32-B ====================
// ================================================================
void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  if (len != 4) return;  // chỉ xử lý đúng 4 byte int

  int value = 0;
  memcpy(&value, data, 4);

  Serial.printf("📥 Number from ESP32-B = %d\n", value);

  // 🔄 RESET MAP khi nhận được 1
  if (value == 1) {
    Serial.println("🔄 RESET MAP (value = 1)");

    for (int i = 1; i <= 12; i++) {
      cellMap[i] = 0;
    }

    // Nếu muốn báo cho STM32 biết đã reset map thì mở dòng dưới:
    // stmSerial.print("RESET\r\n");

    return;
  }

  // START = 0 → chọn PAD IN/OUT & chạy Dijkstra
  if (value == 0) {
    Serial.println("⚡ START RECEIVED → CHỌN PAD & TÌM ĐƯỜNG (Dijkstra)");

    int padIn = choosePadIn();
    if (padIn < 1) {
      Serial.println("❌ PAD IN không hợp lệ, hủy tìm đường");
      return;
    }

    int padOut = choosePadOut(padIn);

    Serial.printf("🚀 Dijkstra từ %d → %d\n", padIn, padOut);
    String route = runDijkstra(padIn, padOut);

    Serial.print("📌 Route (cells): ");
    Serial.println(route);

    // gửi route xuống STM32 (danh sách chỉ số ô)
    stmSerial.print(route);
    stmSerial.print("\r\n");
    return;
  }

  // MAP VALUE: 10..123
  if (value >= 10 && value <= 123) {
    int cell = value / 10;         // 1..12
    int state = value % 10;        // 0..3

    if (cell >= 1 && cell <= 12) {
      cellMap[cell] = value;
      Serial.printf("📌 MAP[%d] = %d (state=%d)\n", cell, value, state);
    }
    return;
  }

  // giá trị khác → bỏ qua
}

// ================================================================
// ========== CALLBACK GỬI ESPNOW (KHÔNG BẮT BUỘC) ================
// ================================================================
void onDataSent(const wifi_tx_info_t *info, esp_now_send_status_t status) {
  Serial.print("📤 ESP-NOW → B: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "OK" : "FAIL");
}

// ================================================================
// ============================== SETUP ===========================
// ================================================================
void setup() {
  Serial.begin(115200);
  stmSerial.begin(STM_BAUD, SERIAL_8N1, STM_RX, STM_TX);

  // khởi tạo map mặc định = 0 (free)
  for (int i = 1; i <= 12; i++) cellMap[i] = 0;

  WiFi.mode(WIFI_STA);
  Serial.println("🚀 ESP32-A READY (Dijkstra + PAD logic + cost thời gian)");

  if (esp_now_init() != ESP_OK) {
    Serial.println("❌ ESP-NOW init failed!");
    return;
  }

  esp_now_register_recv_cb(onDataRecv);
  esp_now_register_send_cb(onDataSent);

  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, peerMAC_B, 6);
  peer.channel = 0;
  peer.encrypt = false;
  peer.ifidx = WIFI_IF_STA;
  esp_now_add_peer(&peer);
}

// ================================================================
void loop() {
  // mọi thứ xử lý trong callback
}
