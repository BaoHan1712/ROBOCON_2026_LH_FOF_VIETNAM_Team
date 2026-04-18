import cv2
import numpy as np
import pyrealsense2 as rs
import customtkinter as ctk
import time

from ultralytics import YOLO
from config_uart.sent_uart import build_packet, ser
from gui_tkinter import set_state, STATE_IDLE, STATE_PICK_BLOCK

# ================= CONFIG =================
MODEL_PATH = r"cover/models/nhathop.onnx"
CONF_THRES = 0.3
MAX_DISTANCE_CM = 250
SEND_INTERVAL = 0.01

# ===== LOCK CONFIG =====
locked_id = None
lost_count = 0
MAX_LOST = 10

selected_mode = None
running = False
last_send_time = 0

# ================= ROI =================
ROI_POINTS = np.array([
    (1, 283),
    (637, 269),
    (636, 455),
    (4, 446)
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
    if d == 0: return None
    return d

def calc_offset(cx):
    norm = int(cx / 640 * 200)
    if norm < 85: return norm - 85
    elif norm > 103: return norm - 103
    else: return 0

def create_roi_mask(img):
    mask = np.zeros(img.shape[:2], dtype=np.uint8)
    cv2.fillPoly(mask, [ROI_POINTS], 255)
    return mask

# ================= CAMERA =================
def run_camera(mode, use_state=True):
    global running, selected_mode, roi_mask
    global locked_id, lost_count

    selected_mode = mode
    running = True

    # 1. ÉP RESET PHẦN CỨNG NẾU CAM BỊ KẸT TỪ TRƯỚC
    try:
        ctx = rs.context()
        if len(ctx.devices) > 0:
            print(">> [Pick Block] Phát hiện Camera, đang dọn dẹp cổng USB...")
    except Exception as e:
        print(">> [Pick Block] Không tìm thấy thiết bị RealSense.")

    pipeline = None
    align = None

    print(">> [Pick Block] Đang mở Camera...")
    while True:
        try:
            pipeline = rs.pipeline()
            config = rs.config()
            config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)
            config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)

            pipeline.start(config)
            print(">> [Pick Block] ✓ Camera mở THÀNH CÔNG!")
            break
        except Exception as e:
            print(f">> [LỖI] Camera kẹt ({e}). Đang ép Hardware Reset...")
            try:
                del pipeline
                ctx = rs.context()
                if len(ctx.devices) > 0:
                    ctx.devices[0].hardware_reset()
            except:
                pass
            time.sleep(3) 

    align = rs.align(rs.stream.color)

    # >>> ĐẺ RA TÊN CỬA SỔ ĐỘC NHẤT <<<
    win_name = f"YOLO RS LOCK [{int(time.time())}]"

    try:
        while running:
            if use_state and set_state["value"] != STATE_PICK_BLOCK:
                break

            try:
                frames = pipeline.wait_for_frames(timeout_ms=1000)
            except:
                print(">> [Cảnh báo] Camera timeout → Đang khởi động lại luồng...")
                try: pipeline.stop()
                except: pass
                time.sleep(0.5)
                try: pipeline.start(config)
                except: pass
                continue

            frames = align.process(frames)
            color_frame = frames.get_color_frame()
            depth_frame = frames.get_depth_frame()

            if not color_frame or not depth_frame:
                continue

            img = np.asanyarray(color_frame.get_data())

            if roi_mask is None:
                roi_mask = create_roi_mask(img)

            # ===== YOLO TRACK =====
            results = model.track(img, conf=CONF_THRES, verbose=False, tracker="cover/models/bytetrack.yaml")

            best_box = None
            h, w = img.shape[:2]

            if results[0].boxes is not None:
                boxes = results[0].boxes
                if locked_id is None:
                    min_dist = 9999
                    for b in boxes:
                        if b.id is None: continue
                        cls_id = int(b.cls[0])
                        if cls_id != 1: continue
                        track_id = int(b.id[0])

                        x1, y1, x2, y2 = map(int, b.xyxy[0])
                        x1, y1 = clamp(x1, 0, w-1), clamp(y1, 0, h-1)
                        x2, y2 = clamp(x2, 0, w-1), clamp(y2, 0, h-1)
                        cx, cy = int((x1 + x2) / 2), int((y1 + y2) / 2)

                        if roi_mask[cy, cx] == 0: continue

                        dist = get_distance(depth_frame, cx, cy)
                        if dist is None: continue

                        if dist < min_dist:
                            min_dist = dist
                            best_box = (x1, y1, x2, y2, cx, cy, dist)
                            locked_id = track_id
                else:
                    found = False
                    for b in boxes:
                        if b.id is None: continue
                        track_id = int(b.id[0])
                        if track_id == locked_id:
                            found = True
                            x1, y1, x2, y2 = map(int, b.xyxy[0])
                            cx, cy = int((x1 + x2) / 2), int((y1 + y2) / 2)
                            dist = get_distance(depth_frame, cx, cy)
                            if dist is None: continue

                            best_box = (x1, y1, x2, y2, cx, cy, dist)
                            lost_count = 0
                            break

                    if not found:
                        lost_count += 1
                        if lost_count > MAX_LOST:
                            locked_id = None
                            lost_count = 0

            # ===== PROCESS =====
            if best_box is not None:
                x1, y1, x2, y2, cx, cy, distance = best_box
                if distance > MAX_DISTANCE_CM: distance = MAX_DISTANCE_CM

                dolech = calc_offset(cx)
                send_uart_limited(dolech, distance, selected_mode)

                color = (0,255,0) if locked_id else (0,0,255)
                cv2.rectangle(img, (x1, y1), (x2, y2), color, 2)
                cv2.circle(img, (cx, cy), 5, (0,0,255), -1)
                cv2.putText(img, f"ID: {locked_id}", (x1, y1-50), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255,255,0), 2)
                cv2.putText(img, f"D: {int(distance)} cm", (x1, y1-30), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0,255,0), 2)
                cv2.putText(img, f"Offset: {dolech}", (x1, y1-10), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255,0,0), 2)

            cv2.polylines(img, [ROI_POINTS], True, (0,255,255), 2)
            
            # >>> HIỂN THỊ CỬA SỔ THEO TÊN BIẾN ĐỘNG <<<
            cv2.imshow(win_name, img)

            if cv2.waitKey(1) & 0xFF == 27:
                running = False
                break
            
            try: del color_frame, depth_frame, frames
            except: pass

    finally:
        print("\n>> --- TIẾN HÀNH DỌN DẸP CAMERA ---")
        try:
            pipeline.stop()
            print(">> ✓ Đã nhả cổng USB thành công!")
        except Exception as e:
            pass
            
        try: del pipeline
        except: pass

        cv2.destroyAllWindows()
        for _ in range(10): cv2.waitKey(1)
            
        time.sleep(2) 

        locked_id = None
        lost_count = 0

        if use_state:
            set_state["value"] = STATE_IDLE

        print(">>> Pick Block OFF | STATE -> IDLE | SẴN SÀNG LẦN MỞ TIẾP THEO!\n")

# ================= MAIN FUNCTION WITH STATE SUPPORT =================
def run_pick_block_loop(mode=1, use_state=True):
    """
    Hàm chạy pick block (Bỏ Thread ảo để tương thích hoàn toàn với OpenCV Linux)
    """
    global running
    print(f">>> Pick Block ON (Mode: {mode})")
    running = True
    
    # Chạy trực tiếp
    run_camera(mode, use_state)

# ================= GUI TEST =================
def start_with_mode(mode):
    global selected_mode, running
    selected_mode = mode
    running = True
    app.destroy()
    run_camera(mode, False)

def on_closing():
    global running
    running = False
    app.destroy()

if __name__ == "__main__":
    ctk.set_appearance_mode("dark")
    ctk.set_default_color_theme("blue")
    app = ctk.CTk()
    app.title("Chọn chế độ truyền")
    app.geometry("300x250")
    app.protocol("WM_DELETE_WINDOW", on_closing)

    ctk.CTkLabel(app, text="Chọn Mode (1-3)", font=("Arial", 20)).pack(pady=20)
    ctk.CTkButton(app, text="Mode 1", command=lambda: start_with_mode(1)).pack(pady=10)
    ctk.CTkButton(app, text="Mode 2", command=lambda: start_with_mode(2)).pack(pady=10)
    ctk.CTkButton(app, text="Mode 3", command=lambda: start_with_mode(3)).pack(pady=10)

    app.mainloop()