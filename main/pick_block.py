import cv2
import numpy as np
import pyrealsense2 as rs
import customtkinter as ctk
import threading
import time

from ultralytics import YOLO

from config_uart.sent_uart import build_packet, ser
from gui_tkinter import set_state, STATE_IDLE, STATE_PICK_BLOCK

# ================= CONFIG =================
MODEL_PATH = "cover/models/kfs_2.onnx"

CONF_THRES = 0.1
IOU_THRES = 0.4
MAX_DISTANCE_CM = 250
SEND_INTERVAL = 0.01

selected_mode = None
running = False
last_send_time = 0

# ================= ROI =================
ROI_POINTS = np.array([
    (2, 99),
    (637, 91),
    (635, 425),
    (1, 420)
], dtype=np.int32)

roi_mask = None

# ================= YOLO =================
model = YOLO(MODEL_PATH, task='detect')

# ================= HELPER =================
def clamp(val, min_v, max_v):
    return max(min_v, min(max_v, val))

def encode_dolech(dolech):
    dolech = clamp(dolech, -100, 100)
    return int(dolech + 100)

def encode_distance(distance):
    return int(clamp(distance, 0, 250))

def send_uart_limited(dolech, distance, mode):
    global last_send_time

    now = time.monotonic()

    if now - last_send_time >= SEND_INTERVAL:
        move = encode_dolech(dolech)
        action = encode_distance(distance)
        block_id = int(clamp(mode, 0, 255))

        ser.write(build_packet(2, 4, move, action, block_id))
        print("Send:", move, action, block_id)

        last_send_time = now

def get_distance(depth_frame, x, y):
    x = int(clamp(x, 0, 639))
    y = int(clamp(y, 0, 479))

    d = depth_frame.get_distance(x, y) * 100

    if d == 0:
        return None

    return d

def calc_offset(cx):
    norm = int(cx / 640 * 200)

    if norm < 85:
        return norm - 85
    elif norm > 103:
        return norm - 103
    else:
        return 0

def create_roi_mask(img):
    mask = np.zeros(img.shape[:2], dtype=np.uint8)
    cv2.fillPoly(mask, [ROI_POINTS], 255)
    return mask

# ================= CAMERA =================
def run_camera(mode, use_state=True):
    global running, selected_mode, roi_mask

    selected_mode = mode
    running = True

    pipeline = rs.pipeline()
    config = rs.config()

    config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)
    config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)

    # ===== start camera =====
    while True:
        try:
            pipeline.start(config)
            break
        except:
            print("Retry start camera...")
            time.sleep(1)

    align = rs.align(rs.stream.color)

    try:
        while running:

            if use_state and set_state["value"] != STATE_PICK_BLOCK:
                break

            # ===== lấy frame =====
            try:
                frames = pipeline.wait_for_frames(timeout_ms=1000)
            except:
                print("Camera timeout → restart")
                pipeline.stop()
                time.sleep(0.5)
                pipeline.start(config)
                continue

            frames = align.process(frames)

            color_frame = frames.get_color_frame()
            depth_frame = frames.get_depth_frame()

            if not color_frame or not depth_frame:
                continue

            img = np.asanyarray(color_frame.get_data())

            # ===== ROI mask =====
            if roi_mask is None:
                roi_mask = create_roi_mask(img)

            # ===== YOLO =====
            results = model(img, conf=CONF_THRES, iou=IOU_THRES, verbose=False)

            best_box = None
            min_dist = 9999

            h, w = img.shape[:2]

            if results[0].boxes is not None:
                for b in results[0].boxes:
                    # Lấy class_id của đối tượng hiện tại
                    cls_id = int(b.cls[0])
                    
                    # CHỈ XỬ LÝ NẾU LÀ R2 (Class ID = 1)
                    if cls_id != 1:
                        continue

                    x1, y1, x2, y2 = map(int, b.xyxy[0])

                    # ===== clamp bbox =====
                    x1 = clamp(x1, 0, w-1)
                    y1 = clamp(y1, 0, h-1)
                    x2 = clamp(x2, 0, w-1)
                    y2 = clamp(y2, 0, h-1)

                    cx = int((x1 + x2) / 2)
                    cy = int((y1 + y2) / 2)

                    # ===== bỏ nếu ngoài ROI =====
                    if roi_mask[cy, cx] == 0:
                        continue

                    dist = get_distance(depth_frame, cx, cy)

                    if dist is None:
                        continue

                    # Logic chọn khối R2 gần nhất để gắp
                    if dist < min_dist:
                        min_dist = dist
                        best_box = (x1, y1, x2, y2, cx, cy, dist)

            # ===== PROCESS =====
            if best_box is not None:
                x1, y1, x2, y2, cx, cy, distance = best_box

                if distance > MAX_DISTANCE_CM:
                    distance = MAX_DISTANCE_CM

                dolech = calc_offset(cx)

                send_uart_limited(dolech, distance, selected_mode)

                cv2.rectangle(img, (x1, y1), (x2, y2), (0,255,0), 2)
                cv2.circle(img, (cx, cy), 5, (0,0,255), -1)

                cv2.putText(img, f"D: {int(distance)} cm", (x1, y1-30),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0,255,0), 2)

                cv2.putText(img, f"Offset: {dolech}", (x1, y1-10),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255,0,0), 2)

            # ===== DRAW ROI =====
            cv2.polylines(img, [ROI_POINTS], True, (0,255,255), 2)

            cv2.imshow("YOLO RS", img)

            if cv2.waitKey(1) & 0xFF == 27:
                running = False
                break

    finally:
        pipeline.stop()
        cv2.destroyAllWindows()

        if use_state:
            set_state["value"] = STATE_IDLE

        print(">>> Pick Block OFF | STATE -> IDLE")


# ================= MAIN FUNCTION WITH STATE SUPPORT =================
def run_pick_block_loop(mode=1, use_state=True):
    """
    Hàm chạy pick block với hỗ trợ state management.
    - mode: 1, 2, hoặc 3 (mặc định là 1)
    - use_state: nếu True, sẽ check state để thoát khi state thay đổi
    """
    global running
    
    print(">>> Pick Block ON")
    running = True
    
    thread = threading.Thread(target=run_camera, args=(mode, use_state))
    thread.start()
    thread.join()


# ================= GUI =================
def start_with_mode(mode):
    global selected_mode
    selected_mode = mode
    app.destroy()
    threading.Thread(target=run_camera, args=(mode, False)).start()

def start_with_mode(mode):
    global selected_mode
    selected_mode = mode
    app.destroy()
    threading.Thread(target=run_camera, args=(mode, False)).start()

def on_closing():
    global running
    running = False       # dừng vòng lặp camera nếu đang chạy
    app.destroy()         # đóng cửa sổ GUI

# ================= ENTRY POINT KHI CHẠY TRỰC TIẾP =================
if __name__ == "__main__":
    ctk.set_appearance_mode("dark")
    ctk.set_default_color_theme("blue")

    app = ctk.CTk()
    app.title("Chọn chế độ truyền")
    app.geometry("300x250")
    app.protocol("WM_DELETE_WINDOW", on_closing)  # <-- gắn vào đây

    ctk.CTkLabel(app, text="Chọn Mode (1-3)", font=("Arial", 20)).pack(pady=20)

    ctk.CTkButton(app, text="Mode 1", command=lambda: start_with_mode(1)).pack(pady=10)
    ctk.CTkButton(app, text="Mode 2", command=lambda: start_with_mode(2)).pack(pady=10)
    ctk.CTkButton(app, text="Mode 3", command=lambda: start_with_mode(3)).pack(pady=10)

    app.mainloop()