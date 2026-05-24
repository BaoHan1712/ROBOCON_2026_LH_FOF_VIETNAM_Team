import pyrealsense2 as rs
import numpy as np
import cv2
import time

# ================= BIẾN TOÀN CỤC =================
points = []
mode = "LIVE"  # Trạng thái: "LIVE" (quay video) hoặc "EDIT" (đóng băng để chấm điểm)
snapshot = None

# ================= HÀM BẮT SỰ KIỆN CHUỘT =================
def mouse_handler(event, x, y, flags, param):
    global points
    
    # Chỉ cho phép chấm điểm khi đang ở chế độ EDIT (ảnh tĩnh)
    if mode == "EDIT" and event == cv2.EVENT_LBUTTONDOWN:
        if len(points) < 4:
            points.append((x, y))
            print(f">> [ROI] Đã chấm điểm {len(points)}: ({x}, {y})")
            
            # Khi chọt đủ 4 điểm -> Nội suy in ra code Numpy luôn!
            if len(points) == 4:
                print("\n" + "🔥"*20)
                print("COPY ĐOẠN CODE NÀY DÁN ĐÈ VÀO FILE CỦA SẾP:")
                print("points = np.array([")
                for i, p in enumerate(points):
                    comma = "," if i < 3 else ""
                    print(f"    ({p[0]}, {p[1]}){comma}")
                print("], dtype=np.int32)")
                print("🔥"*20 + "\n")
                print(">> Bấm 'R' để chấm lại, hoặc 'C' để quay video tiếp.")

# ================= HÀM MAIN =================
def main():
    global mode, snapshot, points
    
    print("==================================================")
    print("🚀 TOOL LẤY TỌA ĐỘ VÙNG NHÌN CAMERA (ROI EXTRACTOR)")
    print("==================================================")
    
    # Khởi động RealSense
    pipeline = rs.pipeline()
    config = rs.config()
    config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)

    print(">> Đang mở Camera...")
    try:
        pipeline.start(config)
        print(">> ✅ Camera đã lên sóng!")
    except Exception as e:
        print(f">> ❌ Lỗi kết nối Camera: {e}")
        return

    win_name = "LHU - ROI TOOL"
    cv2.namedWindow(win_name, cv2.WINDOW_AUTOSIZE)
    # Gắn ngàm bắt chuột vào cửa sổ
    cv2.setMouseCallback(win_name, mouse_handler)

    try:
        while True:
            if mode == "LIVE":
                # Đang quay Live
                frames = pipeline.wait_for_frames()
                color_frame = frames.get_color_frame()
                if not color_frame:
                    continue
                
                # Cập nhật khung hình liên tục
                current_frame = np.asanyarray(color_frame.get_data())
                display_img = current_frame.copy()
                
                # Chữ hướng dẫn trên màn hình
                cv2.putText(display_img, "LIVE MODE", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 0), 2)
                cv2.putText(display_img, "Bam 'C' de chup anh!", (10, 60), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 255), 2)
            
            elif mode == "EDIT":
                # Đã chụp ảnh, đóng băng khung hình
                display_img = snapshot.copy()
                
                cv2.putText(display_img, "EDIT MODE (Anh Tinh)", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 165, 255), 2)
                cv2.putText(display_img, "Click chuot đe cham 4 goc", (10, 60), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 255), 2)
                
                # Vẽ các điểm đã chấm
                for p in points:
                    cv2.circle(display_img, p, 5, (0, 0, 255), -1)
                
                # Nếu đã có từ 2 điểm trở lên, vẽ đường thẳng nối chúng lại
                if len(points) > 1:
                    cv2.polylines(display_img, [np.array(points)], isClosed=(len(points)==4), color=(0, 255, 0), thickness=2)
                
                # Tạo mặt nạ mờ (Overlay) khi chọt đủ 4 điểm cho dễ nhìn
                if len(points) == 4:
                    overlay = display_img.copy()
                    cv2.fillPoly(overlay, [np.array(points)], (0, 255, 0))
                    cv2.addWeighted(overlay, 0.3, display_img, 0.7, 0, display_img)
                    cv2.putText(display_img, "DA XONG! Xem Terminal đe copy Code.", (10, 90), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 255), 2)

            cv2.imshow(win_name, display_img)

            # Lắng nghe phím bấm
            key = cv2.waitKey(1) & 0xFF
            
            if key == ord('q') or key == 27:  # Bấm Q hoặc ESC để thoát
                print(">> Đã thoát Tool.")
                break
                
            elif key == ord('c'):
                if mode == "LIVE":
                    # Đang quay -> Bấm C -> Chụp ảnh và chuyển sang EDIT
                    snapshot = current_frame.copy()
                    mode = "EDIT"
                    points = [] # Xóa sạch điểm cũ
                    print(">> [CHỤP] Đã đóng băng khung hình. Mời sếp chấm 4 điểm!")
                else:
                    # Đang EDIT -> Bấm C -> Hủy, quay lại quay Live
                    mode = "LIVE"
                    print(">> [QUAY LẠI] Đã trở về Camera LIVE.")
                    
            elif key == ord('r'):
                # Bấm R để xóa điểm chấm lại (chỉ tác dụng khi đang EDIT)
                if mode == "EDIT":
                    points = []
                    print(">> [RESET] Đã xóa các điểm. Mời chấm lại!")

    finally:
        # Dọn rác
        pipeline.stop()
        cv2.destroyAllWindows()

if __name__ == "__main__":
    main()