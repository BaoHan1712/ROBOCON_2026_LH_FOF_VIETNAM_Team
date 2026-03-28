import cv2
import numpy as np
from ultralytics import YOLO


# ================== CONFIG ==================
MODEL_PATH = r"cover\models\kfs_2.onnx"
img_path = r"main\matrix\real.jpg"

ROWS = 3
COLS = 3
CONF_THRES = 0.4 # Ngưỡng phát hiện

PTS = np.float32([
    [142, 86],
    [447, 92],
    [448, 386],
    [138, 390],
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
# UART (KHÔNG STATE)
# =================================================
def send_row_2_packet(cell_has_square):
    id_robot = 2
    row = 1   # row giữa

    row_detect = ROWS - 1 - row

    col_data = []
    for c in range(COLS):
        has_obj = cell_has_square[row_detect][c]
        col_data.append([4, 5, 6][c] if has_obj else [14, 15, 16][c])


# =================================================
# MAIN (IMAGE INPUT ONLY)
# =================================================
def process_image_and_send(img):
    """
    img: numpy image (cv2.imread hoặc frame)
    """

    img = cv2.resize(img, (640, 480))
    draw = img.copy()

    TL, TR, BR, BL = PTS

    cell_has_square = np.zeros((ROWS, COLS), dtype=bool)

    # ================= YOLO =================
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

    # ================= UART SEND =================
    send_row_2_packet(cell_has_square)

    return draw


# =================================================
# RUN EXAMPLE
# =================================================
if __name__ == "__main__":
    img = cv2.imread(img_path)
    out = process_image_and_send(img)

    cv2.imshow("Result", out)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
