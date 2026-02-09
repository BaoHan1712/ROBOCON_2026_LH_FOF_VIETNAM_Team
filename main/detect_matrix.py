import cv2
import numpy as np
from ultralytics import YOLO
from config_uart.sent_uart import build_packet, send_packet_once, ser
from gui_tkinter import set_state, STATE_IDLE
import time


# ================== CONFIG ==================
MODEL_PATH = r"cover\models\kfs.onnx"

ROWS = 3
COLS = 3
CONF_THRES = 0.43

PTS = np.float32([
    [139, 112],
    [449, 123],
    [449, 518],
    [142, 521]
])

model = YOLO(MODEL_PATH, task="detect")


# =================================================
# HELPER
# =================================================
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


# =================================================
# UART
# =================================================
def send_row_2_packet(cell_has_square):
    id_robot = 2
    state = 3
    row = 1

    row_detect = ROWS - 1 - row

    col_data = []
    for c in range(COLS):
        has_obj = cell_has_square[row_detect][c]
        col_data.append([4, 5, 6][c] if has_obj else [14, 15, 16][c])

    packet = build_packet(id_robot, state, *col_data)
    send_packet_once(ser, packet)

    print("Sent packet:", list(packet))


# =================================================
# MAIN (IMAGE ONLY + STATE SAFE)
# =================================================
def matrix_camera_loop():

    # chỉ chạy khi state = 2
    if set_state["value"] != 2:
        return

    TL, TR, BR, BL = PTS

    # ================= CAPTURE 1 FRAME =================
    cap = cv2.VideoCapture(0)

    ret, img = cap.read()
    cap.release()   # QUAN TRỌNG: đóng cam ngay

    if not ret:
        print("Camera read failed")
        set_state["value"] = STATE_IDLE
        return

    img = cv2.resize(img, (640, 640))
    draw = img.copy()

    cell_has_square = np.zeros((ROWS, COLS), dtype=bool)

    # ================= YOLO DETECT 1 LẦN =================
    results = model(img, imgsz=640, conf=CONF_THRES, verbose=False)

    centers = []

    for r in results:
        for box in r.boxes:
            x1, y1, x2, y2 = map(int, box.xyxy[0])

            cls_id = int(box.cls[0])
            class_name = model.names[cls_id]
            conf = float(box.conf[0])

            cx = (x1 + x2) // 2
            cy = (y1 + y2) // 2
            centers.append((cx, cy))

            cv2.rectangle(draw, (x1, y1), (x2, y2), (255, 0, 255), 2)
            cv2.circle(draw, (cx, cy), 5, (0, 0, 255), -1)

            label = f"{class_name} {conf:.2f}"
            cv2.putText(draw, label, (x1, y1 - 8),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.6,
                        (0, 255, 255), 2)

    # ================= GRID CHECK =================
    for r in range(ROWS):
        for c in range(COLS):
            cell_poly = get_cell_polygon(TL, TR, BR, BL, r, c, ROWS, COLS)

            for (cx, cy) in centers:
                if cv2.pointPolygonTest(cell_poly, (cx, cy), False) >= 0:
                    cell_has_square[r][c] = True
                    break

            color = (0, 0, 255) if cell_has_square[r][c] else (0, 255, 0)
            cv2.polylines(draw, [cell_poly], True, color, 2)

    # ================= SEND 1 LẦN =================
    send_row_2_packet(cell_has_square)

    # ================= DEBUG SHOW (tuỳ chọn) =================
    cv2.imshow("YOLO Snapshot Detect", draw)
    cv2.waitKey(5000)  # xem 5s cho debug
    cv2.destroyAllWindows()

    # ================= BACK TO IDLE =================
    set_state["value"] = STATE_IDLE
    print(">>> DONE -> STATE_IDLE")



# # =================================================
# if __name__ == "__main__":
#     matrix_image_once()
