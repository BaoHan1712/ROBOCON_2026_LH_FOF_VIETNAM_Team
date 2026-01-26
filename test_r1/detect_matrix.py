import cv2
import numpy as np
import time
from config_uart.sent_uart import build_packet, ser
from gui_tkinter import set_state, STATE_IDLE

# ================== CONFIG ==================
IMAGE_PATH = r"test_r1\matrix\image.png"
ROWS = 3
COLS = 3
MIN_OBJECT_AREA = 1550
SQUARE_RATIO_TOL = 0.5
MIN_CELL_FILL_RATIO = 0.25
time_sent_uart = 2000

PTS = np.float32([
    [245, 252],
    [421, 252],
    [431, 492],
    [242, 499]
])

# ================== HELPER ==================
def lerp(p1, p2, t):
    return (1 - t) * p1 + t * p2

def get_cell_polygon(TL, TR, BR, BL, r, c, rows, cols):
    t1 = r / rows
    t2 = (r + 1) / rows
    s1 = c / cols
    s2 = (c + 1) / cols

    left_top = lerp(TL, BL, t1)
    left_bottom = lerp(TL, BL, t2)
    right_top = lerp(TR, BR, t1)
    right_bottom = lerp(TR, BR, t2)

    p1 = lerp(left_top, right_top, s1)
    p2 = lerp(left_top, right_top, s2)
    p3 = lerp(left_bottom, right_bottom, s2)
    p4 = lerp(left_bottom, right_bottom, s1)

    return np.array([p1, p2, p3, p4], dtype=np.int32)

# ================== COLOR MASK ==================
def get_red_blue_mask(hsv):
    lower_blue = np.array([90, 80, 40])
    upper_blue = np.array([140, 255, 255])

    lower_red1 = np.array([0, 153, 69])
    upper_red1 = np.array([5, 255, 255])
    lower_red2 = np.array([170, 153, 69])
    upper_red2 = np.array([180, 255, 255])

    blue_mask = cv2.inRange(hsv, lower_blue, upper_blue)
    red_mask = cv2.bitwise_or(
        cv2.inRange(hsv, lower_red1, upper_red1),
        cv2.inRange(hsv, lower_red2, upper_red2)
    )

    return cv2.bitwise_or(blue_mask, red_mask)

def denoise_mask(mask):
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))
    mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel, iterations=1)
    mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel, iterations=2)
    return mask

# ================== SHAPE CHECK ==================
def detect_square_object(hsv, cell_mask, cell_area):
    color_mask = get_red_blue_mask(hsv)
    color_mask = cv2.bitwise_and(color_mask, color_mask, mask=cell_mask)
    color_mask = denoise_mask(color_mask)

    contours, _ = cv2.findContours(
        color_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE
    )

    for cnt in contours:
        area = cv2.contourArea(cnt)
        if area < MIN_OBJECT_AREA:
            continue
        if area / cell_area < MIN_CELL_FILL_RATIO:
            continue

        peri = cv2.arcLength(cnt, True)
        approx = cv2.approxPolyDP(cnt, 0.04 * peri, True)
        if len(approx) != 4:
            continue

        x, y, w, h = cv2.boundingRect(approx)
        if abs(w / float(h) - 1.0) > SQUARE_RATIO_TOL:
            continue

        return True

    return False

# ================== SEND PACKETS ==================
def send_row_2_packet(cell_has_square, ser):
    id_robot = 2
    state = 3
    row = 1

    row_detect = ROWS - 1 - row

    col_data = []
    for c in range(COLS):
        has_square = cell_has_square[row_detect][c]
        col_data.append([4, 5, 6][c] if has_square else [40, 50, 60][c])

    packet = build_packet(id_robot, state, *col_data)
    ser.write(packet)
    print("Sent packet ROW 2:", list(packet))

# ================== MAIN ==================
def matrix_camera_loop():
    img = cv2.imread(IMAGE_PATH)
    if img is None:
        print("Khong tim thay anh")
        return

    img = cv2.resize(img, (640, 640))
    draw = img.copy()
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

    TL, TR, BR, BL = PTS
    cell_has_square = np.zeros((ROWS, COLS), dtype=bool)

    # ===== Detect 1 lần =====
    for r in range(ROWS):
        for c in range(COLS):
            cell_poly = get_cell_polygon(TL, TR, BR, BL, r, c, ROWS, COLS)
            cell_mask = np.zeros(img.shape[:2], dtype=np.uint8)
            cv2.fillPoly(cell_mask, [cell_poly], 255)

            cell_area = cv2.contourArea(cell_poly)
            has_square = detect_square_object(hsv, cell_mask, cell_area)
            cell_has_square[r][c] = has_square

            color = (0,0,255) if has_square else (0,255,0)
            cv2.polylines(draw, [cell_poly], True, color, 2)

            cx = int(np.mean(cell_poly[:, 0]))
            cy = int(np.mean(cell_poly[:, 1]))
            cell_id = (ROWS - 1 - r) * COLS + (c + 1)
            cv2.putText(draw, str(cell_id), (cx - 10, cy),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.7, color, 2)

    # ===== HIỂN THỊ + STATE + TIMER =====
    start_ms = time.time() * 1000
    sent = False

    while True:
        if set_state["value"] != 2:
            break

        # ESC → IDLE
        if cv2.waitKey(1) & 0xFF == 27:
            set_state["value"] = STATE_IDLE
            break

        now_ms = time.time() * 1000

        # Sau 5 giây mới gửi
        if not sent and now_ms - start_ms >= time_sent_uart:
            send_row_2_packet(cell_has_square, ser)
            sent = True
            set_state["value"] = STATE_IDLE # gửi xong về gốc
            break

        cv2.imshow("Grid + Square Detection", draw)

    cv2.destroyAllWindows()
