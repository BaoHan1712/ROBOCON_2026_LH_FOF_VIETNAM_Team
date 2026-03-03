import cv2
import pyrealsense2 as rs
import numpy as np
from ultralytics import YOLO
from config_uart.sent_uart import ser, build_packet
import time

# Tải mô hình YOLO
model = YOLO(r"cover\models\kfs.onnx", task="detect")
class_names = model.names

W = 640
H = 480

# ================= UART =================
last_send_time = 0

def send_packet(deviation_byte):
    global last_send_time

    now = time.time()

    # gửi mỗi 2 giây
    if now - last_send_time >= 1.0:
        pkt = build_packet(2, 1, 10, deviation_byte, 10)
        ser.write(pkt)

        print(f">>> SENT Deviation byte: {deviation_byte}")

        last_send_time = now

# Cấu hình RealSense
pipeline = rs.pipeline()
config = rs.config()
config.enable_stream(rs.stream.depth, W, H, rs.format.z16, 30)
config.enable_stream(rs.stream.color, W, H, rs.format.bgr8, 30)
profile = pipeline.start(config)

depth_scale = profile.get_device().first_depth_sensor().get_depth_scale()
align_to = rs.stream.color
align = rs.align(align_to)

prev_time = time.time()

def map_deviation(obj_center_x, frame_width):
    frame_center = frame_width // 2
    delta = obj_center_x - frame_center

    # Deadzone ±15 px
    if abs(delta) <= 50:
        return 100, delta

    norm = delta / frame_center  # [-1, 1]

    if norm < 0:
        # Lệch trái: [-1,0] → [0,98]
        value = int(np.interp(norm, [-1, 0], [0, 50]))
    else:
        # Lệch phải: [0,1] → [102,200]
        value = int(np.interp(norm, [0, 1], [150, 200]))

    return value, delta

while True:
    frames = pipeline.wait_for_frames()
    aligned_frames = align.process(frames)
    depth_frame = aligned_frames.get_depth_frame()
    color_frame = aligned_frames.get_color_frame()

    current_time = time.time()
    delta = current_time - prev_time
    fps = 1.0 / delta if delta > 0 else 0
    prev_time = current_time

    if not depth_frame or not color_frame:
        continue

    frame = np.asanyarray(color_frame.get_data())
    results = model.predict(source=frame, imgsz=640, conf=0.5, verbose=False, max_det=1)

    for info in results:
        boxes = info.boxes
        for box in boxes:
            x1, y1, x2, y2 = map(int, box.xyxy[0])
            conf = float(box.conf[0])
            classindex = int(box.cls[0])
            classname = class_names[classindex] if classindex in class_names else f"ID{classindex}"

            # Clamp biên an toàn
            x1 = max(0, min(W - 1, x1))
            y1 = max(0, min(H - 1, y1))
            x2 = max(0, min(W - 1, x2))
            y2 = max(0, min(H - 1, y2))

            # ===============================
            # TÍNH TÂM
            # ===============================
            center_x = (x1 + x2) // 2
            center_y = (y1 + y2) // 2

            # ===============================
            # MAP LỆCH
            # ===============================
            deviation_byte, delta_pixel = map_deviation(center_x, W)

            print(f"Delta pixel: {delta_pixel} | Deviation byte: {deviation_byte}")
            send_packet(deviation_byte)

            # ===============================
            # DEPTH MEDIAN
            # ===============================
            x1_crop = max(x1, 0)
            y1_crop = max(y1, 0)
            x2_crop = min(x2, W - 1)
            y2_crop = min(y2, H - 1)

            depth_image = np.asanyarray(depth_frame.get_data())
            depth_roi = depth_image[y1_crop:y2_crop, x1_crop:x2_crop].astype(float)
            depth_roi = depth_roi * depth_scale * 1000

            valid_depth = depth_roi[(depth_roi > 0) & (depth_roi < 6000)]
            distance = int(np.median(valid_depth)) if len(valid_depth) > 0 else 0

            # ===============================
            # VẼ BBOX
            # ===============================
            cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)

            # ===== VẼ TÂM ĐỎ =====
            cv2.circle(frame, (center_x, center_y), 6, (0, 0, 255), -1)

            # ===== VẼ LINE từ tâm frame tới tâm object =====
            frame_center_x = W // 2
            cv2.line(frame, (frame_center_x, 0), (frame_center_x, H), (255, 0, 0), 1)
            cv2.line(frame, (frame_center_x, center_y), (center_x, center_y), (0, 255, 255), 2)

            # ===============================
            # LABEL
            # ===============================
            if distance > 0:
                label = f"{classname} {distance}mm DEV:{deviation_byte}"
            else:
                label = f"{classname} DEV:{deviation_byte}"

            cv2.putText(frame,
                        label,
                        (x1, y1 - 10),
                        cv2.FONT_HERSHEY_SIMPLEX,
                        0.6,
                        (0, 0, 255),
                        2)

    fps_text = f'FPS: {int(fps)}'
    cv2.putText(frame, fps_text, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.4, (0, 255, 0), 1)
    cv2.imshow('Object Detection', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

pipeline.stop()
cv2.destroyAllWindows()