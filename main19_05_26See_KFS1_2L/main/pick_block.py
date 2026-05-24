import cv2
import numpy as np
import pyrealsense2 as rs
import customtkinter as ctk
import time
import threading

from config_uart.sent_uart import build_packet, ser
from gui_tkinter import set_state, STATE_IDLE, STATE_PICK_BLOCK
from gui_tkinter import pick_block_data
# ================= CONFIG =================
CONF_THRES = 0.2
MAX_DISTANCE_CM = 500
SEND_INTERVAL = 0.01
CAMERA_OPEN_RETRIES = 5
CAMERA_RESTART_RETRIES = 3
FRAME_TIMEOUT_MS = 2500
CAMERA_RELEASE_DELAY = 2.5
HARDWARE_RESET_DELAY = 4.0

# ===== LOCK CONFIG =====
locked_center = None  # Đổi từ locked_id sang locked_center
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

        if ser is not None and not ser.is_open:
            try: ser.open()
            except: pass

        try:
            packet = build_packet(2, 4, move, action, block_id)
            ser.write(packet)
            
            # 🔥 IN CHUẨN ĐỊNH DẠNG ĐÃ THỐNG NHẤT LÊN TERMINAL CHO SẾP KIỂM TRA:
            print(f">> [UART CMD] GỬI LỆNH: (2, 4, {move}, {action}, {block_id})")
            
        except Exception as e:
            print(f">> [LỖI TRUYỀN UART] {e}")
            
        last_send_time = now

def get_distance(depth_frame, x, y): 
    x = int(clamp(x, 0, 639))
    y = int(clamp(y, 0, 479))
    d = depth_frame.get_distance(x, y) * 100
    if d == 0: return None
    return d

def calc_offset(cx):
    norm = int(cx / 640 * 200)
    if norm < 80: return norm - 80
    elif norm > 98: return norm - 98
    else: return 0

def create_roi_mask(img):
    mask = np.zeros(img.shape[:2], dtype=np.uint8)
    cv2.fillPoly(mask, [ROI_POINTS], 255)
    return mask

# ================= CAMERA =================
def start_realsense_pipeline():
    pipeline = rs.pipeline()
    config = rs.config()
    config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)
    config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)
    pipeline.start(config)
    return pipeline, config


def stop_realsense_pipeline(pipeline):
    if pipeline is None:
        return
    try:
        pipeline.stop()
        print(">> ✓ Đã nhả luồng RealSense!")
    except Exception as e:
        print(f">> [Pick Block] Pipeline đã dừng hoặc không thể dừng: {e}")


def hardware_reset_realsense():
    try:
        ctx = rs.context()
        if len(ctx.devices) > 0:
            print(">> [Pick Block] Đang hardware reset RealSense...")
            ctx.devices[0].hardware_reset()
            time.sleep(HARDWARE_RESET_DELAY)
            return True
    except Exception as e:
        print(f">> [Pick Block] Không hardware reset được RealSense: {e}")
    return False


def reset_pick_block_state():
    global locked_id, lost_count, roi_mask, last_send_time
    locked_id = None
    lost_count = 0
    roi_mask = None
    last_send_time = 0

def run_camera(mode, team_color="RED", use_state=True):
    global running, selected_mode, roi_mask
    global locked_center, lost_count  # Thay locked_id bằng locked_center

    selected_mode = mode
    running = True

    if team_color in ["RED", "0", 0]:
        target_class_id = 0  
        target_name = "R2_red"
    else: 
        target_class_id = 1  
        target_name = "R2_blue"

    print(f"\n>> [Pick Block] BẮT ĐẦU SĂN: Sân {team_color} | ID Khối: {mode}")

    # 🔥 ĐÃ XÓA SẠCH PHẦN HARDWARE RESET 2.5 GIÂY! MỞ THẲNG LUÔN!
    import time
    pipeline = None
    align = None

    while True:
        try:
            pipeline = rs.pipeline()
            config = rs.config()
            config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)
            config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)

            pipeline.start(config)
            align = rs.align(rs.stream.color)
            
            # 🔥 CHỈ ÉP XẢ NHANH 3 KHUNG HÌNH (Tốn 0.1s) ĐỂ CHỐNG CRASH LUỒNG C++, ĐÉO CẦN 15 KHUNG NHƯ CŨ!
            for _ in range(3):
                try: pipeline.wait_for_frames(timeout_ms=300)
                except: pass
                
            print(">> [Pick Block] ⚡ CAMERA MỞ SIÊU TỐC THÀNH CÔNG!")
            break
        except Exception as e:
            print(f">> [LỖI] Kẹt Cam ({e}). Thử lại sau 0.5s...")
            time.sleep(0.5) 

    win_name = f"Vision_Camera_{int(time.time())}"
    cv2.namedWindow(win_name, cv2.WINDOW_AUTOSIZE)
    try: cv2.setWindowProperty(win_name, cv2.WND_PROP_TOPMOST, 1)
    except: pass

    try:
        while running:
            if use_state and set_state["value"] != STATE_PICK_BLOCK:
                break

            try:
                frames = pipeline.wait_for_frames(timeout_ms=1000)
            except Exception as e:
                print(f">> [Cảnh báo] Mất kết nối USB ({e}) -> Khởi động lại luồng...")
                try: pipeline.stop()
                except: pass
                time.sleep(0.5)
                try: 
                    pipeline.start(config)
                    align = rs.align(rs.stream.color)
                except: pass
                continue

            try:
                frames = align.process(frames)
            except Exception:
                continue

            color_frame = frames.get_color_frame()
            depth_frame = frames.get_depth_frame()

            if not color_frame or not depth_frame:
                continue
                
            img = np.asanyarray(color_frame.get_data())

            if roi_mask is None:
                roi_mask = create_roi_mask(img)

            if roi_mask is None:
                roi_mask = create_roi_mask(img)

            # =========================================================================
            # CÔNG NGHỆ LÕI MỚI: OPENCV COLOR TRACKING + DEPTH MASK + ROI POLYGON
            # =========================================================================
            hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
            depth_img = np.asanyarray(depth_frame.get_data())

            # 1. LỌC MÀU THÔNG MINH (HSV)
            if target_class_id == 0:  # Nếu là Sân ĐỎ (Màu đỏ chạy ngang qua đỉnh 180 của HSV)
                mask1 = cv2.inRange(hsv, np.array([0, 120, 70]), np.array([10, 255, 255]))
                mask2 = cv2.inRange(hsv, np.array([170, 120, 70]), np.array([180, 255, 255]))
                color_mask = cv2.bitwise_or(mask1, mask2)
            else:  # Nếu là Sân XANH DƯƠNG
                color_mask = cv2.inRange(hsv, np.array([90, 120, 50]), np.array([130, 255, 255]))

            # 2. BỨC TƯỜNG CHIỀU SÂU: Chém đứt mọi thứ ở xa hơn 2 mét (2000mm)
            # Chỉ lấy các pixel có depth từ 10mm đến 2000mm. Ai mặc áo đỏ ở xa vứt hết!
            depth_mask_8u = np.where((depth_img > 10) & (depth_img < 5000), 255, 0).astype(np.uint8)

            # 3. KẾT HỢP ÁO GIÁP 3 LỚP: Màu + Chiều Sâu + Góc Nhìn Sa Bàn (ROI)
            final_mask = cv2.bitwise_and(color_mask, roi_mask)
            final_mask = cv2.bitwise_and(final_mask, depth_mask_8u)

            # 4. CHÀ NHÁM XÓA NHIỄU (Morphology mở và đóng)
            kernel = np.ones((5, 5), np.uint8)
            final_mask = cv2.morphologyEx(final_mask, cv2.MORPH_OPEN, kernel)
            final_mask = cv2.morphologyEx(final_mask, cv2.MORPH_CLOSE, kernel)

            # 5. ĐI TÌM KHỐI VUÔNG
            contours, _ = cv2.findContours(final_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
            
            best_box = None
            valid_targets = []
            h, w = img.shape[:2]

            for cnt in contours:
                area = cv2.contourArea(cnt)
                if area > 400:  # Diện tích đủ to mới tính là cục R2, bỏ nhiễu hạt tiêu
                    x_box, y_box, w_box, h_box = cv2.boundingRect(cnt)
                    x1, y1 = clamp(x_box, 0, w-1), clamp(y_box, 0, h-1)
                    x2, y2 = clamp(x_box + w_box, 0, w-1), clamp(y_box + h_box, 0, h-1)
                    cx, cy = int((x1 + x2) / 2), int((y1 + y2) / 2)

                    dist = get_distance(depth_frame, cx, cy)
                    if dist is not None:
                        valid_targets.append((x1, y1, x2, y2, cx, cy, dist))

            # 6. LOGIC KHÓA MỤC TIÊU BẰNG TỌA ĐỘ (CHỐNG NHẢY HỘP)
            if not valid_targets:
                lost_count += 1
                if lost_count > MAX_LOST:
                    locked_center = None
                    lost_count = 0
            else:
                if locked_center is None:
                    # Đang rảnh rang -> Bám luôn cục R2 nằm GẦN XE NHẤT
                    best_box = min(valid_targets, key=lambda t: t[6])
                    locked_center = (best_box[4], best_box[5])
                else:
                    # Đang bám mục tiêu rồi -> Đi tìm cục R2 NẰM GẦN TÂM ĐÃ KHÓA NHẤT
                    prev_cx, prev_cy = locked_center
                    best_box = min(valid_targets, key=lambda t: (t[4]-prev_cx)**2 + (t[5]-prev_cy)**2)
                    locked_center = (best_box[4], best_box[5])
                    lost_count = 0

            if best_box is not None:
                x1, y1, x2, y2, cx, cy, distance = best_box
                if distance > MAX_DISTANCE_CM: distance = MAX_DISTANCE_CM

                if distance < 25.0: 
                    dolech = 0      
                    cv2.putText(img, "CLOSE RANGE: STRAIGHT LUCK!", (x1, y1-70), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0,0,255), 2)
                else:
                    dolech = calc_offset(cx) 

                # Bắn gói tin UART cuối cùng báo cho mạch biết khoảng cách hiện tại
                send_uart_limited(dolech, distance, selected_mode)

                # =====================================================================
                # 🔥 CÔNG TẮC HÀNH TRÌNH 30CM: TỰ ĐỘNG CẮT LUỒNG TRẢ VỀ MAIN
                # =====================================================================
                if distance <= 30.0:
                    print(f"\n>> [PICK BLOCK] TẦM NHÌN ĐÃ ĐẠT {distance:.1f} CM (<= 30cm)!")
                    print(">> BÀN GIAO QUYỀN LỰC CHO STM32! ĐANG TỰ ĐỘNG THOÁT CAM...")
                    running = False
                    break  # Phá vỡ vòng lặp while, nhảy thẳng xuống hàm finally để tắt Cam
                # =====================================================================

                color = (0,255,0) if locked_center else (0,0,255)
                cv2.rectangle(img, (x1, y1), (x2, y2), color, 2)
                cv2.circle(img, (cx, cy), 5, (0,0,255), -1)
                
                cv2.putText(img, f"Target: {target_name} | Track: {locked_center != None}", (x1, y1-50), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255,255,0), 2)
                cv2.putText(img, f"D: {int(distance)} cm", (x1, y1-30), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0,255,0), 2)
                cv2.putText(img, f"Offset: {dolech}", (x1, y1-10), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255,0,0), 2)

            cv2.polylines(img, [ROI_POINTS], True, (0,255,255), 2)
            cv2.imshow(win_name, img)

            if cv2.waitKey(1) & 0xFF == 27:
                running = False
                break
            
            try: del color_frame, depth_frame, frames
            except: pass

    finally:
        print("\n>> --- TIẾN HÀNH DỌN DẸP SẠCH SẼ CAMERA ---")
        try:
            for _ in range(2): pipeline.poll_for_frames() # Ép nhả nhanh 2 frames
        except: pass

        try: pipeline.stop()
        except: pass
            
        try: del align, pipeline
        except: pass

        try: cv2.destroyWindow(win_name)
        except: pass
        for _ in range(5): cv2.waitKey(1)
            
        # 🔥 ĐÃ RÚT CỤC TẠ 2.0 GIÂY XUỐNG CÒN 0.3 GIÂY!!! Vừa đủ để Thread kết thúc.
        time.sleep(0.3) 

        locked_id = None
        lost_count = 0

        if use_state:
            try: set_state["value"] = STATE_IDLE
            except: pass

        global camera_busy
        camera_busy = False
        print(">>> Pick Block OFF | STATE -> IDLE | ĐÃ SẴN SÀNG NHÁY TIẾP!\n")


# ================= MAIN FUNCTION & CHỐT CHẶN (BẢN BỌC THÉP V2) =================
def stop_camera():
    """Hàm khẩn cấp để tắt Camera từ xa"""
    global running
    running = False
    # Tuyệt đối ĐÉO SET camera_busy = False ở đây!
    # Phải bắt luồng mới đứng ngoài chờ luồng cũ dọn rác xong mới nhả khóa!
    print(">> [VISION] 🛑 ĐÃ NHẬN LỆNH TẮT CAMERA KHẨN CẤP! Đang chờ dọn rác USB...")

def run_pick_block_loop(mode=1, team_color="RED", use_state=True):
    global running, camera_busy
    
    # 🔥 VŨ KHÍ TỐI THƯỢNG: HÀNG RÀO XẾP HÀNG CHỐNG ĐÂM XE
    # Kiểm tra xem có luồng cũ nào đang dọn rác không, nếu có thì đứng chờ tối đa 4 giây!
    wait_time = 0
    while globals().get('camera_busy', False):
        print(">> [ĐỢI LUỒNG] Camera cũ đang xả điện USB, chờ 1 xíu...")
        time.sleep(0.5)
        wait_time += 0.5
        if wait_time > 4.0:
            print(">> [CẢNH BÁO] Kẹt khóa luồng! Bỏ qua lệnh mở Camera.")
            return
            
    print(f">>> Pick Block ON (Mode: {mode} | Team: {team_color})")
    camera_busy = True
    running = True
    
    try:
        run_camera(mode, team_color, use_state)
    except Exception as e:
        print(f">> [LỖI FATAL KHỞI ĐỘNG CAMERA] {e}")
    finally:
        # Bắt buộc phải đặt cái nhả khóa ở tận cùng này để không thằng nào đè thằng nào!
        camera_busy = False
        running = False
        print(">> [VISION] Đã tháo ổ khóa Camera, sẵn sàng mở lại an toàn tuyệt đối!")

# ================= GUI TEST DÙNG RIÊNG (ĐÃ MỞ KHÓA VÀ ĐỘ MIRROR) =================
def start_with_mode(mode, team):
    global selected_mode, running
    selected_mode = mode
    running = True
    try: app.destroy()
    except: pass
    
    # Gọi thẳng vào luồng Camera, data UART sẽ lấy 'mode' làm 'block_id'
    run_pick_block_loop(mode, team, use_state=False)

def on_closing():
    global running
    running = False
    try: app.destroy()
    except: pass

if __name__ == "__main__":
    import sys
    import time
    
    # LUỒNG 1: Nếu gọi bằng CMD (VD từ file main)
    if len(sys.argv) >= 3:
        run_mode = int(sys.argv[1])
        run_team = sys.argv[2]
        print(f"\n🚀 [TIẾN TRÌNH ĐỘC LẬP] - Mode: R{run_mode} | Sân: {run_team}")
        try:
            run_pick_block_loop(run_mode, run_team, use_state=False)
        except KeyboardInterrupt:
            print("\n>> Đã nhận lệnh thoát khẩn cấp!")
        finally:
            cv2.destroyAllWindows()
            for _ in range(10): cv2.waitKey(1)
            time.sleep(1.5)
            
    # LUỒNG 2: Chạy trực tiếp file này -> Bật Giao Diện CTk Như Cũ
    else:
        ctk.set_appearance_mode("dark")
        ctk.set_default_color_theme("blue")
        
        app = ctk.CTk()
        app.title("LHU - PICK BLOCK TESTER")
        app.geometry("450x320")
        app.protocol("WM_DELETE_WINDOW", on_closing)
        
        ctk.CTkLabel(app, text="CHỌN SÂN (RED/BLUE)", font=("Arial", 16, "bold")).pack(pady=(15, 5))
        
        team_var = ctk.StringVar(value="RED")
        
        # Khung chứa 6 nút
        frame_btns = ctk.CTkFrame(app, fg_color="transparent")
        
# 2. Cuộn xuống TẬN CÙNG FILE pick_block.py, tìm hàm update_mirror_ui() của phần TEST độc lập, dán đè đoạn này để đổi dải nút thành 1-6:
        def update_mirror_ui(*args):
            for widget in frame_btns.winfo_children():
                widget.destroy()
                
            current_team = team_var.get()
            
            # Quy hoạch chuẩn dải từ 1 đến 6 cho đồng bộ sa bàn
            row_1 = [4, 5, 6] 
            row_2 = [1, 2, 3]
            
            if current_team == "RED":
                row_1 = row_1[::-1] # Lật ngược thành 6, 5, 4
                row_2 = row_2[::-1] # Lật ngược thành 3, 2, 1
                
            for r_idx, row_data in enumerate([row_1, row_2]):
                for c_idx, block_id in enumerate(row_data):
                    btn = ctk.CTkButton(
                        frame_btns, 
                        text=f"KHỐI {block_id}", 
                        font=("Arial", 14, "bold"),
                        width=80, height=45,
                        fg_color="#8e44ad" if current_team == "RED" else "#2980b9",
                        hover_color="#9b59b6" if current_team == "RED" else "#3498db",
                        command=lambda b=block_id: start_with_mode(b, current_team)
                    )
                    btn.grid(row=r_idx, column=c_idx, padx=8, pady=8)

        # Thanh chọn Sân, khi bấm sẽ tự gọi hàm vẽ lại UI đảo gương
        seg_btn = ctk.CTkSegmentedButton(
            app, values=["RED", "BLUE"], 
            variable=team_var,
            font=("Arial", 14, "bold"),
            command=update_mirror_ui
        )
        seg_btn.pack(pady=5)
        
        frame_btns.pack(pady=10)
        
        # Khởi tạo lần đầu
        update_mirror_ui()

        app.mainloop()
