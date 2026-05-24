import cv2
import numpy as np
import pyrealsense2 as rs

# ===== ROI =====
points = []

def mouse_callback(event, x, y, flags, param):
    global points

    if event == cv2.EVENT_LBUTTONDOWN:
        if len(points) < 4:
            points.append((x, y))
            print(f"Point {len(points)}: ({x}, {y})")

# ===== REALSENSE =====
pipeline = rs.pipeline()
config = rs.config()

config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)

pipeline.start(config)

cv2.namedWindow("Camera")
cv2.setMouseCallback("Camera", mouse_callback)

try:
    while True:
        frames = pipeline.wait_for_frames()
        color_frame = frames.get_color_frame()

        if not color_frame:
            continue

        img = np.asanyarray(color_frame.get_data())

        # ===== DRAW POINTS =====
        for p in points:
            cv2.circle(img, p, 5, (0, 255, 255), -1)

        # ===== DRAW POLYGON =====
        if len(points) == 4:
            pts = np.array(points, np.int32)
            cv2.polylines(img, [pts], True, (0, 255, 255), 2)

        cv2.imshow("Camera", img)

        key = cv2.waitKey(1) & 0xFF

        # ===== PRINT COORD =====
        if key == 32:  # SPACE
            if len(points) == 4:
                print("\n=== ROI COORDINATES ===")
                for i, p in enumerate(points):
                    print(f"P{i+1}: {p}")
            else:
                print("Chưa đủ 4 điểm")

        # ===== RESET =====
        if key == ord('r'):
            points.clear()
            print("Reset ROI")

        # ===== EXIT =====
        if key == 27:
            break

finally:
    pipeline.stop()
    cv2.destroyAllWindows()