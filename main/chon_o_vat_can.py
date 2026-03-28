import pyrealsense2 as rs
import numpy as np
import cv2

# ================= INIT CAMERA =================
pipeline = rs.pipeline()
config = rs.config()

config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)
config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)

pipeline.start(config)

align = rs.align(rs.stream.color)

# ================= STATE =================
points = []
selecting = False
frozen = False
frozen_color = None
polygon_ready = False

# ================= MOUSE =================
def mouse_event(event, x, y, flags, param):
    global points, polygon_ready

    if selecting:
        if event == cv2.EVENT_LBUTTONDOWN:
            if len(points) < 4:
                points.append((x, y))
                print(f"Point {len(points)}: ({x},{y})")

        if len(points) == 4:
            polygon_ready = True

cv2.namedWindow("Color")
cv2.setMouseCallback("Color", mouse_event)

# ================= LOOP =================
while True:
    if not frozen:
        frames = pipeline.wait_for_frames()
        aligned_frames = align.process(frames)

        depth_frame = aligned_frames.get_depth_frame()
        color_frame = aligned_frames.get_color_frame()

        if not depth_frame or not color_frame:
            continue

        color_image = np.asanyarray(color_frame.get_data())
        depth_image = np.asanyarray(depth_frame.get_data())
    else:
        color_image = frozen_color.copy()

    display = color_image.copy()

    # ================= DRAW POINTS =================
    for p in points:
        cv2.circle(display, p, 5, (0, 255, 255), -1)

    # Vẽ polygon nếu đủ điểm
    if polygon_ready:
        pts = np.array(points, np.int32)
        cv2.polylines(display, [pts], True, (255, 0, 0), 2)

        # ================= MASK =================
        mask = np.zeros(depth_image.shape, dtype=np.uint8)
        cv2.fillPoly(mask, [pts], 255)

        roi_depth = depth_image[mask == 255]

        valid_depth = roi_depth[roi_depth > 0]
        close_points = valid_depth[valid_depth < 1000]

        if len(close_points) > 30:
            min_dist = np.min(close_points)
            has_object = True
        else:
            min_dist = 0
            has_object = False

        # ================= DRAW RESULT =================
        color = (0,255,0) if has_object else (0,0,255)

        if min_dist > 0:
            text = f"Min: {min_dist} mm"
        else:
            text = "Min: N/A"

        cv2.putText(display, text, (points[0][0], points[0][1] - 10),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, color, 2)

    # ================= SHOW =================
    cv2.imshow("Color", display)

    key = cv2.waitKey(1) & 0xFF

    # ESC
    if key == 27:
        break

    # S → chụp frame và bắt đầu chọn
    elif key == ord('s'):
        frozen = True
        selecting = True
        points = []
        polygon_ready = False

        frames = pipeline.wait_for_frames()
        aligned_frames = align.process(frames)
        frozen_color = np.asanyarray(aligned_frames.get_color_frame().get_data())
        depth_image = np.asanyarray(aligned_frames.get_depth_frame().get_data())

        print("=== SELECT 4 POINTS ===")

    # R → reset
    elif key == ord('r'):
        points = []
        polygon_ready = False
        selecting = False
        frozen = False
        print("RESET")

    # SPACE → in tọa độ
    elif key == 32:
        if polygon_ready:
            print("==== POLYGON POINTS ====")
            for i, p in enumerate(points):
                print(f"P{i+1}: {p}")

pipeline.stop()
cv2.destroyAllWindows()