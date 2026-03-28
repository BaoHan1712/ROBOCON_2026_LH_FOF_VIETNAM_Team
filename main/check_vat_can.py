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

# ================= POLYGON POINTS =================
points = np.array([
    (27,340),
    (639,327),
    (630,187),
    (7,193)
], dtype=np.int32)

while True:
    frames = pipeline.wait_for_frames()
    aligned_frames = align.process(frames)

    depth_frame = aligned_frames.get_depth_frame()
    color_frame = aligned_frames.get_color_frame()

    if not depth_frame or not color_frame:
        continue

    color_image = np.asanyarray(color_frame.get_data())
    depth_image = np.asanyarray(depth_frame.get_data())

    # ================= MASK =================
    mask = np.zeros(depth_image.shape, dtype=np.uint8)
    cv2.fillPoly(mask, [points], 255)

    roi_depth = depth_image[mask == 255]

    # ================= FILTER =================
    valid_depth = roi_depth[roi_depth > 0]
    close_points = valid_depth[valid_depth < 1500]

    if len(close_points) > 30:
        min_dist = np.min(close_points)
        has_object = True
    else:
        min_dist = 0
        has_object = False

    # ================= DRAW =================
    color = (0,255,0) if has_object else (0,0,255)

    # Vẽ polygon
    cv2.polylines(color_image, [points], True, color, 2)

    # Text trạng thái
    text = "OBJECT DETECTED" if has_object else "NO OBJECT < 1000mm"
    cv2.putText(color_image, text, (20, 40),
                cv2.FONT_HERSHEY_SIMPLEX, 1, color, 2)

    # Min distance
    if min_dist > 0:
        dist_text = f"Min: {min_dist} mm"
    else:
        dist_text = "Min: N/A"

    # đặt text gần điểm đầu
    cv2.putText(color_image, dist_text,
                (points[0][0], points[0][1] - 10),
                cv2.FONT_HERSHEY_SIMPLEX, 0.7, color, 2)

    # ================= SHOW =================
    depth_vis = cv2.convertScaleAbs(depth_image, alpha=0.03)
    depth_vis = cv2.applyColorMap(depth_vis, cv2.COLORMAP_JET)

    cv2.imshow("Color", color_image)
    cv2.imshow("Depth", depth_vis)

    if cv2.waitKey(1) & 0xFF == 27:
        break

pipeline.stop()
cv2.destroyAllWindows()