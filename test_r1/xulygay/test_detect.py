import cv2
import numpy as np

def nothing(x):
    pass

# Khởi tạo cửa sổ điều khiển
cv2.namedWindow("Settings")
cv2.createTrackbar("V_Upper", "Settings", 106, 255, nothing)     # Ngưỡng sáng tối
cv2.createTrackbar("Min_Dist", "Settings", 130, 500, nothing)   # Khoảng cách giữa các tâm
cv2.createTrackbar("Param2", "Settings", 25, 100, nothing)      # Độ nhạy (càng nhỏ càng dễ nhận)
cv2.createTrackbar("Min_R", "Settings", 20, 200, nothing)       # Bán kính tối thiểu
cv2.createTrackbar("Max_R", "Settings", 150, 400, nothing)      # Bán kính tối đa

def test_with_trackbars(image_path):
    img = cv2.imread(image_path)
    img = cv2.resize(img, (640, 480))
    if img is None:
        print("Không tìm thấy ảnh!")
        return

    while True:
        output = img.copy()
        h, w = img.shape[:2]
        cam_cx, cam_cy = w // 2, h // 2

        # 1. Đọc thông số từ Trackbar
        v_upper = cv2.getTrackbarPos("V_Upper", "Settings")
        min_dist = cv2.getTrackbarPos("Min_Dist", "Settings")
        param2 = cv2.getTrackbarPos("Param2", "Settings")
        min_r = cv2.getTrackbarPos("Min_R", "Settings")
        max_r = cv2.getTrackbarPos("Max_R", "Settings")
        
        # Đảm bảo các thông số không bằng 0 để tránh lỗi hàm Hough
        min_dist = max(1, min_dist)
        param2 = max(1, param2)

        # 2. Xử lý màu sắc & Lọc nhiễu
        hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
        lower_black = np.array([0, 0, 0])
        upper_black = np.array([180, 255, v_upper])
        mask = cv2.inRange(hsv, lower_black, upper_black)

        # Sử dụng giải thuật Morphological để xóa nhiễu hạt (Erode sau đó Dilate)
        kernel = np.ones((5, 5), np.uint8)
        mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)

        # 3. Kết hợp Mask với ảnh xám để tăng cường cạnh
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        gray_filtered = cv2.GaussianBlur(gray, (9, 9), 2)
        processed_img = cv2.bitwise_and(gray_filtered, mask)

        # 4. Nhận diện hình tròn
        circles = cv2.HoughCircles(
            processed_img, 
            cv2.HOUGH_GRADIENT, dp=1.2, 
            minDist=min_dist,
            param1=50, param2=param2, 
            minRadius=min_r, maxRadius=max_r
        )

        # 5. Tính toán và Hiển thị
        if circles is not None:
            circles = np.uint16(np.around(circles))
            for i in circles[0, :]:
                obj_x, obj_y, r = i[0], i[1], i[2]
                
                # Tính toán độ lệch (Offset) từ tâm camera
                dx = int(obj_x - cam_cx)
                dy = int(obj_y - cam_cy)

                # Vẽ kết quả
                cv2.circle(output, (obj_x, obj_y), r, (0, 255, 0), 2)
                cv2.circle(output, (obj_x, obj_y), 2, (0, 0, 255), 3)
                
                # Hiển thị tọa độ lệch
                cv2.putText(output, f"dx:{dx} dy:{dy}", (obj_x - r, obj_y - r - 10),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 0), 1)

        # Hiển thị tâm camera (Mục tiêu ngắm)
        cv2.line(output, (cam_cx - 10, cam_cy), (cam_cx + 10, cam_cy), (0, 0, 255), 2)
        cv2.line(output, (cam_cx, cam_cy - 10), (cam_cx, cam_cy + 10), (0, 0, 255), 2)

        cv2.imshow("Original with Detection", output)
        cv2.imshow("Processed Mask", processed_img)

        if cv2.waitKey(1) & 0xFF == 27: # Nhấn ESC để thoát
            break

    cv2.destroyAllWindows()

# Chạy test
test_with_trackbars(r'data_train2\fr_4.jpg')