import pyrealsense2 as rs
import numpy as np
import cv2

pipeline = rs.pipeline()
config = rs.config()

config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)
config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)

pipeline.start(config)

while True:
    frames = pipeline.wait_for_frames()

    depth = frames.get_depth_frame()
    color = frames.get_color_frame()

    if not depth or not color:
        continue

    depth_image = np.asanyarray(depth.get_data())
    color_image = np.asanyarray(color.get_data())

    # hiển thị
    depth_vis = cv2.convertScaleAbs(depth_image, alpha=0.03)

    cv2.imshow("color", color_image)
    cv2.imshow("depth", depth_vis)

    if cv2.waitKey(1) == 27:
        break

pipeline.stop()
cv2.destroyAllWindows()