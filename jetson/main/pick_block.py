import cv2
import numpy as np
import pyrealsense2 as rs
import customtkinter as ctk
import time
import threading

from ultralytics import YOLO
from config_uart.sent_uart import build_packet, ser
from gui_tkinter import set_state, STATE_IDLE, STATE_PICK_BLOCK

# ================= CONFIG =================
MODEL_PATH = r"cover\models\nhathop.pt"
CONF_THRES = 0.5
MAX_DISTANCE_CM = 250
SEND_INTERVAL = 0.01

# ===== LOCK CONFIG =====
locked_id = None
lost_count = 0
MAX_LOST = 10

selected_mode = None
running = False
camera_busy = False  # <=== PHẢI THÊM DÒNG NÀY VÀO ĐÂY NHÉ!
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
    elif norm > 95: return norm - 95
    else: return 0

def create_roi_mask(img):
    mask = np.zeros(img.shape[:2], dtype=np.uint8)
    cv2.fillPoly(mask, [ROI_POINTS], 255)
    return mask

# ================= CAMERA =================
def run_camera(mode, team_color="RED", use_state=True):
    global running, selected_mode, roi_mask
    global locked_id, lost_count

    selected_mode = mode
    running = True

    # 🎯 LOGIC TÌM CLASS THEO MÀU SÂN
    # {0: 'XR1', 1: 'XR2', 2: 'DR1', 3: 'DR2'}
    if team_color == "RED":
        target_class_id = 2 if mode == 1 else 3
        target_name = "DR1" if mode == 1 else "DR2"
    else: # BLUE
        target_class_id = 0 if mode == 1 else 1
        target_name = "XR1" if mode == 1 else "XR2"

    print(f"\n>> [Pick Block] BẮT ĐẦU SĂN: Sân {team_color} | Tìm kiếm: {target_name} (ID: {target_class_id})")

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
    import time
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
            time.sleep(1.5) 

    align = rs.align(rs.stream.color)

    # =========================================================================
    # >>> ĐẺ RA TÊN CỬA SỔ ĐỘC NHẤT ĐỂ ĐÁNH LỪA UBUNTU CHỐNG TÀNG HÌNH <<<
    # =========================================================================
    win_name = f"Vision_Camera_{int(time.time())}"
    
    # 1. ÉP OPENCV PHẢI TẠO KHUNG GIAO DIỆN TRƯỚC KHI VẼ HÌNH
    cv2.namedWindow(win_name, cv2.WINDOW_AUTOSIZE)
    
    # 2. VŨ KHÍ TỐI THƯỢNG: ÉP CỬA SỔ NỔI LÊN TRÊN CÙNG (CHỐNG NÚP LÙM DƯỚI TKINTER)
    try:
        cv2.setWindowProperty(win_name, cv2.WND_PROP_TOPMOST, 1)
    except: 
        pass

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
                        
                        # 🎯 CHỈ NHÌN MỤC TIÊU CỦA ĐỘI MÌNH
                        if cls_id != target_class_id: continue
                        
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
                            print(f">> KHÓA MỤC TIÊU: {target_name} | ID: {locked_id}")
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
                            print(">> MẤT DẤU MỤC TIÊU -> Đang tìm lại...")
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
                
                # Vẽ thêm cái nhãn tên mục tiêu
                cv2.putText(img, f"Target: {target_name} | ID: {locked_id}", (x1, y1-50), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255,255,0), 2)
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
            print(">> ✓ Đã nhả luồng RealSense!")
        except Exception as e:
            pass
            
        try: del pipeline
        except: pass

        # Sát thủ diệt window của OpenCV Linux (Phải lặp 20 lần nó mới chết hẳn)
        cv2.destroyAllWindows()
        for _ in range(20): cv2.waitKey(1)
            
        # ÉP ĐỢI 1.5 GIÂY ĐỂ USB XẢ ĐIỆN HOÀN TOÀN TRƯỚC KHI CHO MỞ LẠI
        time.sleep(1.5) 

        locked_id = None
        lost_count = 0

        if use_state:
            try: set_state["value"] = STATE_IDLE
            except: pass

        # Mở khóa cho phép lần bấm tiếp theo
        global camera_busy
        camera_busy = False
        print(">>> Pick Block OFF | STATE -> IDLE | SẴN SÀNG LẦN MỞ TIẾP THEO!\n")
# ================= MAIN FUNCTION & CHỐT CHẶN =================
def run_pick_block_loop(mode=1, team_color="RED", use_state=True):
    global running, camera_busy
    
    # Ổ KHÓA CHỐNG NGHIỆP VỤ: Đang bận đéo cho mở luồng mới!
    if camera_busy:
        print(">> [CẢNH BÁO] Camera đang xả cổng USB hoặc đang chạy. Chờ 2 giây rồi thử lại!")
        return
        
    print(f">>> Pick Block ON (Mode: {mode} | Team: {team_color})")
    camera_busy = True
    running = True
    
    # Chạy trực tiếp
    run_camera(mode, team_color, use_state)

# ================= MAIN FUNCTION & CHỐT CHẶN (BẢN BỌC THÉP 2 LỚP) =================
def stop_camera():
    """Hàm khẩn cấp để tắt Camera từ xa (Cấp quyền tối thượng)"""
    global running, camera_busy
    running = False
    
    # BÚA TẠ: Đập nát ổ khóa ngầm ngay lập tức, không cần biết đang kẹt ở đâu!
    camera_busy = False  
    print(">> [VISION] 🛑 ĐÃ NHẬN LỆNH TẮT CAMERA KHẨN CẤP! (Đã ép nhả khóa USB)")

def run_pick_block_loop(mode=1, team_color="RED", use_state=True):
    global running, camera_busy
    
    # Kiểm tra biến khóa (dùng globals để chống lỗi chưa khai báo)
    if globals().get('camera_busy', False):
        print(">> [CẢNH BÁO] Bị kẹt khóa luồng! Hãy bấm nút '🛑 TẮT CAM' trên giao diện để Reset!")
        return
        
    print(f">>> Pick Block ON (Mode: {mode} | Team: {team_color})")
    camera_busy = True
    running = True
    
    # BẢO HIỂM LỚP NGOÀI CÙNG: Bắt mọi lỗi tử thần của RealSense
    try:
        run_camera(mode, team_color, use_state)
    except Exception as e:
        print(f">> [LỖI FATAL KHỞI ĐỘNG CAMERA] {e}")
    finally:
        # CHỐT CHẶN CUỐI CÙNG: Dù trời có sập, sấm có đánh thì luồng kết thúc LÀ PHẢI NHẢ KHÓA!
        camera_busy = False
        running = False
        print(">> [VISION] Đã dọn dẹp và tháo ổ khóa Camera, sẵn sàng mở lại!")
        
# ================= MAIN TRIGGER (CẤP QUYỀN CHẠY TIẾN TRÌNH ĐỘC LẬP) =================
if __name__ == "__main__":
    import sys
    run_mode = 1
    run_team = "RED"
    
    # Bắt tham số từ Algo ném sang
    if len(sys.argv) >= 3:
        run_mode = int(sys.argv[1])
        run_team = sys.argv[2]
        
    print(f"\n🚀 [TIẾN TRÌNH ĐỘC LẬP] Đang mở Camera - Mode: {run_mode} | Sân: {run_team}")
    try:
        run_pick_block_loop(run_mode, run_team, False)
    except KeyboardInterrupt:
        print(">> Đã nhận lệnh thoát khẩn cấp từ Algo!")

        
# ================= GUI TEST DÙNG RIÊNG (Nếu cần test độc lập) =================
# def start_with_mode(mode, team):
#     global selected_mode, running
#     selected_mode = mode
#     running = True
#     try: app.destroy()
#     except: pass
#     run_camera(mode, team, False)

# def on_closing():
#     global running
#     running = False
#     app.destroy()

# if __name__ == "__main__":
#     ctk.set_appearance_mode("dark")
#     ctk.set_default_color_theme("blue")
#     app = ctk.CTk()
#     app.title("Test Nhận Diện")
#     app.geometry("300x320")
#     app.protocol("WM_DELETE_WINDOW", on_closing)
#     
#     ctk.CTkLabel(app, text="CHỌN SÂN (RED/BLUE)", font=("Arial", 16, "bold")).pack(pady=10)
#     
#     team_var = ctk.StringVar(value="RED")
#     ctk.CTkSegmentedButton(app, values=["RED", "BLUE"], variable=team_var).pack(pady=5)
#     
#     ctk.CTkButton(app, text="📸 TEST TÌM R1", command=lambda: start_with_mode(1, team_var.get())).pack(pady=15)
#     ctk.CTkButton(app, text="📸 TEST TÌM R2", command=lambda: start_with_mode(2, team_var.get())).pack(pady=5)
#
#     app.mainloop()