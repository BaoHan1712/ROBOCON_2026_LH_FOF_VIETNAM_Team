import pyrealsense2 as rs
import numpy as np
import cv2
import time
from config_uart.sent_uart import build_packet, ser
from gui_tkinter import set_state, STATE_IDLE, pick_block_data

# Link các hàm tính toán của file pick_block sang để dùng chung, đéo thèm viết lại cho rác file
from pick_block import clamp, calc_offset, get_distance, send_uart_limited, create_roi_mask, ROI_POINTS

# ================= HẰNG SỐ & TỌA ĐỘ =================
DEPTH_THRESHOLD_FLOOR = 2300   
DETECT_TIME_FLOOR = 1.5        
DETECT_TIME_MATRIX = 3.0       
MIN_AREA_FLOOR = 800           

# Tọa độ cắt khuôn dưới sàn (Hồi 1)
FLOOR_ROI = np.array([
    (38, 259), (596, 239), (608, 440), (44, 442)
], dtype=np.int32)

# Tọa độ khuôn Ma trận lúc ngóc lên (Hồi 3 - Sếp cấp)
MATRIX_ROI = np.array([
    (133, 2), (511, 46), (553, 416), (113, 432)
], dtype=np.float32)

FLAT_SIZE = 300
CELL_SIZE = 100

# ================= HÀM BĂM Ô & TƯ DUY CARO TÍCH HỢP ĐỒ HỌA DEBUG =================
def get_empty_cell(warped_img, team_color):
    hsv = cv2.cvtColor(warped_img, cv2.COLOR_BGR2HSV)
    board = [0] * 9 
    
    # Ánh xạ index (0-8) ra ID thực tế trên sa bàn
    id_map = {0:4, 1:5, 2:6, 3:1, 4:2, 5:3, 6:7, 7:8, 8:9}
    allowed_indices = [0, 1, 2, 3, 4, 5] # Chỉ 2 hàng trên
    
    idx = 0
    for row in range(3):
        for col in range(3):
            y_start, y_end = row * CELL_SIZE, (row + 1) * CELL_SIZE
            x_start, x_end = col * CELL_SIZE, (col + 1) * CELL_SIZE
            
            # 🔥 VẼ LƯỚI 3x3 LÊN ẢNH DEBUG
            cv2.rectangle(warped_img, (x_start, y_start), (x_end, y_end), (255, 255, 255), 1)
            
            cell_hsv = hsv[y_start:y_end, x_start:x_end]
            mask_blue = cv2.inRange(cell_hsv, np.array([90, 120, 50]), np.array([130, 255, 255]))
            mask_red1 = cv2.inRange(cell_hsv, np.array([0, 100, 40]), np.array([10, 255, 255]))
            mask_red2 = cv2.inRange(cell_hsv, np.array([165, 100, 40]), np.array([180, 255, 255]))
            mask_red = cv2.bitwise_or(mask_red1, mask_red2)
            
            is_blue = cv2.countNonZero(mask_blue) > 1000
            is_red = cv2.countNonZero(mask_red) > 1000
            
            status_text = "TRONG"
            color_text = (0, 255, 0) # Xanh lá cho ô trống
            
            if team_color == "BLUE":
                if is_blue: 
                    board[idx] = 1; status_text = "TA"; color_text = (255, 255, 0)
                elif is_red: 
                    board[idx] = -1; status_text = "DICH"; color_text = (0, 0, 255)
            else: # RED
                if is_red: 
                    board[idx] = 1; status_text = "TA"; color_text = (0, 0, 255)
                elif is_blue: 
                    board[idx] = -1; status_text = "DICH"; color_text = (255, 255, 0)
            
            # 🔥 IN CHỮ ID VÀ TRẠNG THÁI VÀO TỪNG Ô ĐỂ SẾP DEBUG
            cv2.putText(warped_img, f"ID:{id_map[idx]}", (x_start + 5, y_start + 25), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255,255,255), 2)
            cv2.putText(warped_img, status_text, (x_start + 5, y_start + 65), cv2.FONT_HERSHEY_SIMPLEX, 0.6, color_text, 2)
            
            # 🔥 VẼ DẤU X KHÓA MÕM HÀNG DƯỚI (R1 ONLY)
            if idx not in allowed_indices:
                cv2.line(warped_img, (x_start, y_start), (x_end, y_end), (100, 100, 100), 2)
                cv2.line(warped_img, (x_start, y_end), (x_end, y_start), (100, 100, 100), 2)
                cv2.putText(warped_img, "R1 ONLY", (x_start + 15, y_start + 90), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (100,100,100), 1)

            idx += 1

    # ================= LOGIC TƯ DUY CHIẾN THUẬT (BẢN ĐỘ CƠ KHÍ & LUẬT MỚI) =================
    # 🔥 ĐÃ XÓA SẠCH CÁC ĐƯỜNG NGANG! CHỈ CÒN LẠI DỌC VÀ CHÉO THEO LUẬT SẾP
    win_lines = [
        (0,3,6), (1,4,7), (2,5,8), # 3 Dọc
        (0,4,8), (2,4,6)           # 2 Chéo
    ]

    chosen_idx = None
    reason = ""

    # 🛠️ MÀNG LỌC TỐI ƯU CƠ KHÍ: ƯU TIÊN TẦNG 2 TRƯỚC TẦNG 3
    # Tầng 3 (Hàng trên): index 0, 1, 2
    # Tầng 2 (Hàng giữa): index 3, 4, 5
    def pick_best_physical_row(candidate_list):
        valid_cands = [i for i in candidate_list if i in allowed_indices]
        if not valid_cands: return None
        
        # Moi móc xem có ô nào thuộc Tầng 2 (index 3, 4, 5) không?
        tang_2_cands = [i for i in valid_cands if i in [3, 4, 5]]
        if tang_2_cands: 
            return tang_2_cands[0] # Thấy Tầng 2 là HÚP LUÔN CHO NHANH!
            
        return valid_cands[0] # Đéo có Tầng 2 thì đành ngóc lên Tầng 3 vậy!

    # Ưu tiên 1: KẾT LIỄU
    kill_candidates = []
    for line in win_lines:
        line_vals = [board[i] for i in line]
        if sum(line_vals) == 2: 
            kill_candidates.append(line[line_vals.index(0)])
            
    chosen_idx = pick_best_physical_row(kill_candidates)
    if chosen_idx is not None:
        reason = "KET LIEU (UU TIEN T2)"

    # Ưu tiên 2: CHẶN HỌNG
    if chosen_idx is None:
        block_candidates = []
        for line in win_lines:
            line_vals = [board[i] for i in line]
            if sum(line_vals) == -2: 
                block_candidates.append(line[line_vals.index(0)])
                
        chosen_idx = pick_best_physical_row(block_candidates)
        if chosen_idx is not None:
            reason = "CHAN HONG (UU TIEN T2)"

    # Ưu tiên 3: CHIẾM CHỖ ĐẮC ĐỊA
    # Đã cấu hình lại để nó vã sạch Tầng 2 rồi mới ngóc lên Tầng 3
    # Trật tự quét: Tâm Tầng 2(4) -> Trái/Phải Tầng 2(3,5) -> Tâm Tầng 3(1) -> Trái/Phải Tầng 3(0,2)
    if chosen_idx is None:
        priority_indices = [4, 3, 5, 1, 0, 2] 
        for p_idx in priority_indices:
            if board[p_idx] == 0:
                chosen_idx = p_idx
                reason = "CHIEM CHO"
                break

    # 🔥 VẼ KHUNG XANH LÁ CHỐT HẠ ĐỂ SẾP NHÌN THẤY NÓ CHỌN Ô NÀO
    if chosen_idx is not None:
        row, col = divmod(chosen_idx, 3)
        y_start, y_end = row * CELL_SIZE, (row + 1) * CELL_SIZE
        x_start, x_end = col * CELL_SIZE, (col + 1) * CELL_SIZE
        
        cv2.rectangle(warped_img, (x_start, y_start), (x_end, y_end), (0, 255, 0), 4)
        cv2.putText(warped_img, f"-> {reason}", (x_start + 5, y_start + 90), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
        
        return [id_map[chosen_idx]]
            
    return []

# ================= VÒNG LẶP COMBO CHUỖI LIÊN HOÀN =================
def detect_floor_loop(team_color="BLUE"):
    print(f"\n>>> [COMBO VISION] KHỞI CHẠY CHUỖI LIÊN HOÀN LỤM QUÀ LẦN 2 ({team_color})")
    
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
            for _ in range(3): pipeline.wait_for_frames()
            print(">> [COMBO VISION] ✓ Đã giữ chặt luồng RealSense. Không tắt Cam!")
            break
        except Exception as e:
            print(f">> Kẹt Cam: {e}. Thử lại sau 0.5s...")
            time.sleep(0.5)

    win_name = "LHU - ROBOCON SYSTEM"
    cv2.namedWindow(win_name, cv2.WINDOW_AUTOSIZE)
    
    current_phase = "SCAN_FLOOR" 
    timer_start = None
    wait_time_start = 0
    locked_center = None
    lost_count = 0
    
    pts_dst = np.array([[0, 0], [FLAT_SIZE - 1, 0], [FLAT_SIZE - 1, FLAT_SIZE - 1], [0, FLAT_SIZE - 1]], dtype=np.float32)
    perspective_matrix = cv2.getPerspectiveTransform(MATRIX_ROI, pts_dst)
    pick_roi_mask = None

    try:
        while True:
            frames = pipeline.wait_for_frames(timeout_ms=1000)
            aligned_frames = align.process(frames)
            color_frame = aligned_frames.get_color_frame()
            depth_frame = aligned_frames.get_depth_frame()
            if not color_frame or not depth_frame: continue

            img = np.asanyarray(color_frame.get_data())
            depth_img = np.asanyarray(depth_frame.get_data())
            
            # ----------------------------------------------------------
            # HỒI 1: QUÉT SÀN NHÌN VẬT RƠI
            # ----------------------------------------------------------
            if current_phase == "SCAN_FLOOR":
                hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
                # ...
                if team_color == "RED":
                    # 🔥 CẬP NHẬT LUÔN Ở ĐÂY CHO ĐỒNG BỘ NÈ SẾP!
                    color_mask = cv2.inRange(hsv, np.array([0, 100, 40]), np.array([10, 255, 255])) 
                    mask2 = cv2.inRange(hsv, np.array([165, 100, 40]), np.array([180, 255, 255]))
                    color_mask = cv2.bitwise_or(color_mask, mask2)
                    color_mask = cv2.bitwise_or(color_mask, mask2)

                depth_mask = np.where((depth_img > 10) & (depth_img < DEPTH_THRESHOLD_FLOOR), 255, 0).astype(np.uint8)
                final_mask = cv2.bitwise_and(color_mask, depth_mask)

                roi_mask = np.zeros(img.shape[:2], dtype=np.uint8)
                cv2.fillPoly(roi_mask, [FLOOR_ROI], 255)
                final_mask = cv2.bitwise_and(final_mask, roi_mask)

                contours, _ = cv2.findContours(final_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
                has_object = any(cv2.contourArea(cnt) > MIN_AREA_FLOOR for cnt in contours)

                cv2.polylines(img, [FLOOR_ROI], True, (0, 255, 255), 2)
                if has_object:
                    if timer_start is None: timer_start = time.time()
                    duration = time.time() - timer_start
                    cv2.putText(img, f"FLOOR CONFIRMING: {duration:.2f}s/{DETECT_TIME_FLOOR}s", (10, 40), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 255), 2)
                    
                    if duration >= DETECT_TIME_FLOOR:
                        print(f"\n>> [HỒI 1 OK] -> Gửi gói START Ngước Trời: (2, 5, 1, 1, 1)")
                        if ser and ser.is_open: ser.write(build_packet(2, 5, 1, 1, 1))
                        current_phase = "WAIT_LIFT"
                        wait_time_start = time.time()
                else:
                    timer_start = None
                    cv2.putText(img, "SEARCHING BOX ON FLOOR...", (10, 40), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 0, 255), 2)
                cv2.imshow(win_name, img)

            # ----------------------------------------------------------
            # HỒI 2: ĐỢI CƠ KHÍ BẢO NGÓC ĐẦU LÊN XONG
            # ----------------------------------------------------------
            elif current_phase == "WAIT_LIFT":
                time_waited = time.time() - wait_time_start
                cv2.putText(img, f"WAITING MECHANIC LIFT UP: {time_waited:.1f}s/{DETECT_TIME_MATRIX}s", (10, 50), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 165, 255), 2)
                cv2.imshow(win_name, img)
                if time_waited >= DETECT_TIME_MATRIX:
                    current_phase = "SNAPSHOT_MATRIX"

            # ----------------------------------------------------------
            # HỒI 3: CHỤP ẢNH TĨNH TỰ ĐỘNG BĂM Ô TRỐNG MA TRẬN VÀ HIỂN THỊ DEBUG
            # ----------------------------------------------------------
            elif current_phase == "SNAPSHOT_MATRIX":
                warped = cv2.warpPerspective(img, perspective_matrix, (FLAT_SIZE, FLAT_SIZE))
                
                # Hàm này bây giờ sẽ tự động vẽ UI AI lên ảnh warped cho sếp xem
                empty_cells = get_empty_cell(warped, team_color)
                
                # Show ảnh lên ngay lập tức để mắt sếp nhìn thấy
                cv2.polylines(img, [MATRIX_ROI.astype(np.int32)], True, (0, 255, 255), 2)
                cv2.imshow(win_name, img)
                cv2.imshow("Warped Matrix (DEBUG AI)", warped)
                cv2.waitKey(1) # Ép OpenCV xuất hình ra màn hình
                
                if empty_cells:
                    target_id = empty_cells[0]
                    print(f"\n>> [HỒI 3 OK] -> AI QUYẾT ĐỊNH ĐÁNH Ô SỐ: {target_id}")
                    
                    pick_block_data["block_id"] = target_id
                    
                    print(f">> [UART] Tự động bắn gói kết thúc đặt hộp: (2, 5, 2, 2, {target_id})")
                    if ser and ser.is_open: ser.write(build_packet(2, 5, 2, 2, target_id))
                    
                    # 🔥 ĐÓNG BĂNG 3 GIÂY ĐỂ SẾP SOI KẾT QUẢ TRÊN MÀN HÌNH!
                    print(">> 🛑 [DEBUG] Đang dừng hình 3 giây cho sếp soi Radar AI...")
                    time.sleep(1.5)
                    
                    current_phase = "WAIT_FOR_PICK_BLOCK"
                    wait_time_start = time.time()
                else:
                    cv2.putText(img, "MATRIX FULL! RETRYING...", (10, 40), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 0, 255), 2)
                    cv2.imshow(win_name, img)
                    # Quay lại đợi nửa giây rồi chụp tiếp nếu không thấy
                    current_phase = "WAIT_LIFT"
                    wait_time_start = time.time() - (DETECT_TIME_MATRIX - 0.5)

            # ----------------------------------------------------------
            # HỒI 4: ĐỢI 2 GIÂY TỰ ĐỘNG QUAY LẠI FILE PICK BLOCK (THEO ẢNH)
            # ----------------------------------------------------------
            elif current_phase == "WAIT_FOR_PICK_BLOCK":
                time_waited = time.time() - wait_time_start
                
                # Dọn rác cái cửa sổ Debug cho gọn
                try: cv2.destroyWindow("Warped Matrix (DEBUG AI)")
                except: pass
                
                cv2.putText(img, f"SWITCHING TO PICK_BLOCK IN: {2.0 - time_waited:.1f}s", (10, 50), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (255, 0, 255), 2)
                cv2.imshow(win_name, img)
                if time_waited >= 2.0:
                    print("\n>> [HỒI 4 OK] -> Tự động kích hoạt luồng gắp PICK_BLOCK!")
                    current_phase = "PICK_BLOCK_TRACKING"

            # ----------------------------------------------------------
            # HỒI 5: LUỒNG GẮP TỐC ĐỘ CAO OPENCV (TỪ FILE PICK_BLOCK)
            # ----------------------------------------------------------
            elif current_phase == "PICK_BLOCK_TRACKING":
                target_class_id = 0 if team_color == "RED" else 1
                current_mode = pick_block_data["block_id"]

                hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
                if target_class_id == 0:
                    m1 = cv2.inRange(hsv, np.array([0, 120, 70]), np.array([10, 255, 255]))
                    m2 = cv2.inRange(hsv, np.array([170, 120, 70]), np.array([180, 255, 255]))
                    c_mask = cv2.bitwise_or(m1, m2)
                else:
                    c_mask = cv2.inRange(hsv, np.array([90, 120, 50]), np.array([130, 255, 255]))

                d_mask = np.where((depth_img > 10) & (depth_img < 2000), 255, 0).astype(np.uint8)
                if pick_roi_mask is None: pick_roi_mask = create_roi_mask(img)
                
                f_mask = cv2.bitwise_and(c_mask, pick_roi_mask)
                f_mask = cv2.bitwise_and(f_mask, d_mask)
                
                kernel = np.ones((5, 5), np.uint8)
                f_mask = cv2.morphologyEx(f_mask, cv2.MORPH_OPEN, kernel)
                f_mask = cv2.morphologyEx(f_mask, cv2.MORPH_CLOSE, kernel)

                contours, _ = cv2.findContours(f_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
                valid_targets = []
                h_p, w_p = img.shape[:2]

                for cnt in contours:
                    if cv2.contourArea(cnt) > 400:
                        xb, yb, wb, hb = cv2.boundingRect(cnt)
                        x1, y1 = clamp(xb, 0, w_p-1), clamp(yb, 0, h_p-1)
                        x2, y2 = clamp(xb + wb, 0, w_p-1), clamp(yb + hb, 0, h_p-1)
                        cx, cy = int((x1 + x2) / 2), int((y1 + y2) / 2)
                        dist = get_distance(depth_frame, cx, cy)
                        if dist is not None: valid_targets.append((x1, y1, x2, y2, cx, cy, dist))

                best_box = None
                if not valid_targets:
                    lost_count += 1
                    if lost_count > 10: locked_center = None; lost_count = 0
                else:
                    if locked_center is None:
                        best_box = min(valid_targets, key=lambda t: t[6])
                        locked_center = (best_box[4], best_box[5])
                    else:
                        best_box = min(valid_targets, key=lambda t: (t[4]-locked_center[0])**2 + (t[5]-locked_center[1])**2)
                        locked_center = (best_box[4], best_box[5])
                        lost_count = 0

                if best_box is not None:
                    x1, y1, x2, y2, cx, cy, distance = best_box
                    dolech = 0 if distance < 25.0 else calc_offset(cx)
                    
                    send_uart_limited(dolech, distance, current_mode)

                    if distance <= 30.0:
                        print(f">> [CHẠM NGƯỠNG 30CM] Bàn giao cú đấm gắp cho STM32 tự xử! Tắt Cam!")
                        break

                    cv2.rectangle(img, (x1, y1), (x2, y2), (0, 255, 0), 2)
                    cv2.putText(img, f"GAP ID: {current_mode} | D: {int(distance)}cm", (x1, y1-10), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)

                cv2.polylines(img, [ROI_POINTS], True, (0, 255, 255), 2)
                cv2.imshow(win_name, img)

            if cv2.waitKey(1) & 0xFF == 27: break

    finally:
        print("\n>> [COMBO VISION] Đang giải phóng luồng, tắt sạch Camera...")
        try: pipeline.stop()
        except: pass
        cv2.destroyAllWindows()
        for _ in range(5): cv2.waitKey(1)
        print(">> [COMBO VISION] CHUỖI LIÊN HOÀN KẾT THÚC! SẴN SÀNG CHO PHÁT TIẾP THEO!\n")

if __name__ == "__main__":
    detect_floor_loop("BLUE")