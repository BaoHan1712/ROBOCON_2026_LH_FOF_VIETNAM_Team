import pyrealsense2 as rs
import numpy as np
import cv2

# Cấu hình pipeline
pipeline = rs.pipeline()
config = rs.config()

# Cấu hình độ phân giải (Sử dụng 640x480 cho ổn định trên thiết bị nhúng)
W, H = 640, 480
config.enable_stream(rs.stream.color, W, H, rs.format.bgr8, 30)
config.enable_stream(rs.stream.depth, W, H, rs.format.z16, 30)

# Bắt đầu streaming
pipeline.start(config)

recording = False
video_writer = None
fps = 30

print("Nhấn 'Space' để bắt đầu/dừng quay video.")
print("Nhấn 'q' để thoát.")

try:
    while True:
        frames = pipeline.wait_for_frames()
        color_frame = frames.get_color_frame()
        if not color_frame:
            continue

        color_image = np.asanyarray(color_frame.get_data())

        # Logic ghi video
        if recording:
            if video_writer is None:
                # Lấy kích thước thực tế từ ảnh để tránh lỗi lệch resolution
                h, w = color_image.shape[:2]
                fourcc = cv2.VideoWriter_fourcc(*'XVID')
                video_writer = cv2.VideoWriter('output_capture.avi', fourcc, fps, (w, h))
                print(f"--- Đang quay video ở độ phân giải {w}x{h}... ---")
            
            video_writer.write(color_image)
            # Hiển thị chấm đỏ thông báo đang record
            cv2.circle(color_image, (30, 30), 10, (0, 0, 255), -1)

        cv2.imshow('RealSense D435', color_image)
        key = cv2.waitKey(1)

        if key == ord(' '):
            recording = not recording
            if not recording and video_writer:
                video_writer.release()
                video_writer = None
                print("--- Đã dừng và lưu video. ---")

        elif key == ord('q'):
            break

finally:
    if video_writer:
        video_writer.release()
    pipeline.stop()
    cv2.destroyAllWindows()