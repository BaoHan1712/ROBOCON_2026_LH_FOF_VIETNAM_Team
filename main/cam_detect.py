import cv2
import numpy as np
import time
from gui_tkinter import set_state, STATE_IDLE

def weapon_camera_loop():
    # Tham số cấu hình
    V_UPPER = 116
    MIN_DIST = 135
    PARAM2 = 36
    MIN_R = 30
    MAX_R = 90
    BLACK_THRESHOLD = 0.4  # Ít nhất 40% pixel trong vòng tròn phải là màu đen

    cap = cv2.VideoCapture(0)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

    print(">> Camera WEAPON started (Shape-First Mode)")

    prev_time = time.time()
    kernel = np.ones((3, 3), np.uint8)

    while True:
        ret, frame = cap.read()
        if not ret: break

        h, w, _ = frame.shape
        cam_cx, cam_cy = w // 2, h // 2

        # 1. TIỀN XỬ LÝ ẢNH XÁM (ĐỂ TÌM CẠNH TRÒN)
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        gray = cv2.medianBlur(gray, 7) # Tăng mức Blur để làm mượt cạnh

        # 2. TÌM TẤT CẢ HÌNH TRÒN TRƯỚC
        circles = cv2.HoughCircles(
            gray, 
            cv2.HOUGH_GRADIENT, dp=1.2, 
            minDist=MIN_DIST,
            param1=50, param2=PARAM2, 
            minRadius=MIN_R, maxRadius=MAX_R
        )

        # 3. TẠO MASK MÀU ĐEN ĐỂ XÉT SAU
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        lower_black = np.array([0, 0, 0])
        upper_black = np.array([180, 255, V_UPPER])
        mask_black = cv2.inRange(hsv, lower_black, upper_black)
        mask_black = cv2.morphologyEx(mask_black, cv2.MORPH_OPEN, kernel)

        # Vẽ đường trung tâm
        cv2.line(frame, (cam_cx, 0), (cam_cx, h), (0, 0, 255), 1)

        # 4. KIỂM TRA MÀU SẮC TRONG CÁC HÌNH TRÒN TÌM ĐƯỢC
        if circles is not None:
            circles = np.uint16(np.around(circles))
            for i in circles[0, :]:
                cx, cy, r = i[0], i[1], i[2]
                
                # Tạo một mặt nạ hình tròn tạm thời để tính toán
                circle_mask = np.zeros_like(mask_black)
                cv2.circle(circle_mask, (cx, cy), r, 255, -1)
                
                # Kết hợp với mask màu đen để xem có bao nhiêu pixel đen trong hình tròn này
                black_in_circle = cv2.bitwise_and(mask_black, circle_mask)
                black_pixel_count = cv2.countNonZero(black_in_circle)
                total_circle_pixels = np.pi * (r ** 2)

                # Nếu tỷ lệ pixel đen đủ cao, thì mới xác nhận là vật thể
                if (black_pixel_count / total_circle_pixels) > BLACK_THRESHOLD:
                    dx = int(cx - cam_cx)
                    dy = int(cy - cam_cy)

                    # Vẽ Tracking
                    cv2.circle(frame, (cx, cy), r, (0, 255, 0), 2)
                    cv2.circle(frame, (cx, cy), 5, (0, 255, 0), -1)
                    cv2.putText(frame, f"dx: {dx}px", (cx - r, cy - r - 10),
                                cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
                    
                    # Thêm nhãn "BLACK OBJ" để xác nhận
                    cv2.putText(frame, "CONFIRMED", (cx - r, cy + r + 20),
                                cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 1)
                    break # Ưu tiên vật thể đầu tiên đạt chuẩn

        # 5. UI & FPS
        curr_time = time.time()
        fps = 1 / (curr_time - prev_time)
        prev_time = curr_time

        cv2.circle(frame, (cam_cx, cam_cy), 5, (0, 0, 255), -1)
        cv2.putText(frame, "SHAPE-FIRST MODE", (20, 40),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
        cv2.putText(frame, f"FPS: {int(fps)}", (20, 70),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 0), 2)

        cv2.imshow("Weapon Camera", frame)

        if set_state["value"] != 1: break
        if cv2.waitKey(1) & 0xFF == 27:
            set_state["value"] = STATE_IDLE
            break

    cap.release()
    cv2.destroyAllWindows()