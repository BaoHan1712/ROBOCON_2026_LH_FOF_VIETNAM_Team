import pyrealsense2 as rs
import numpy as np
import cv2
import time

from gui_tkinter import set_state, STATE_IDLE, STATE_SEE_R1

# ================= POLYGON =================
points = np.array([
    (27,340),
    (639,327),
    (630,187),
    (7,193)
], dtype=np.int32)

# ================= HẰNG SỐ =================
DEPTH_THRESHOLD = 1500  # mm - ngưỡng phát hiện vật cản
DETECT_TIME = 3  # giây - thời gian giữ để confirm
MIN_POINTS = 30  # số điểm tối thiểu để coi là có vật cản

# ================= MAIN =================
def detect_r1_snapshot_loop(use_state=True):
    """
    Hàm chạy vòng lặp phát hiện vật cản bằng RealSense D435i
    - Nếu có vật cản < 1700mm trong vùng polygon → màu xanh (GREEN)
    - Nếu không có → màu đỏ (RED)
    """
    print(">>> RealSense ON")

    # ================= INIT CAMERA =================
    pipeline = None
    align = None
    
    try:
        # Tạo pipeline mới cho mỗi lần gọi hàm
        pipeline = rs.pipeline()
        config = rs.config()

        config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)
        config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)

        pipeline.start(config)
        align = rs.align(rs.stream.color)

        # Chờ 1s để camera ổn định
        time.sleep(1)

        r1_start_time = None
        prev_tick = cv2.getTickCount()

        while True:
            # ===== state change → thoát =====
            if use_state and set_state["value"] != STATE_SEE_R1:
                break

            try:
                # ===== lấy frame =====
                frames = pipeline.wait_for_frames()
                
                # ===== Check frames trước khi align =====
                if not frames:
                    continue
                
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
                close_points = valid_depth[valid_depth < DEPTH_THRESHOLD]

                if len(close_points) > MIN_POINTS:
                    min_dist = int(np.median(close_points))
                    has_object = True
                else:
                    min_dist = 0
                    has_object = False

                # ================= TIMER LOGIC =================
                now = time.time()

                if not has_object:  # KHÔNG có vật < threshold
                    if r1_start_time is None:
                        r1_start_time = now

                    duration = now - r1_start_time

                    cv2.putText(color_image, f"CLEAR: {duration:.2f}s",
                                (10, 60),
                                cv2.FONT_HERSHEY_SIMPLEX, 0.8,
                                (0, 255, 0), 2)

                    if duration >= DETECT_TIME:
                        print(">>> NO OBJECT 5s -> DONE")
                        break
                else:
                    r1_start_time = None

                # ================= DRAW =================
                color = (0, 255, 0) if has_object else (0, 0, 255)  # GREEN if object, RED if not

                cv2.polylines(color_image, [points], True, color, 2)

                text = f"OBJECT DETECTED" if has_object else f"NO OBJECT < {DEPTH_THRESHOLD}mm"
                cv2.putText(color_image, text, (20, 40),
                            cv2.FONT_HERSHEY_SIMPLEX, 1, color, 2)

                if min_dist > 0:
                    dist_text = f"Min: {min_dist} mm"
                else:
                    dist_text = "Min: N/A"

                cv2.putText(color_image, dist_text,
                            (points[0][0], points[0][1] - 10),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.7, color, 2)

                # ================= FPS =================
                tick = cv2.getTickCount()
                fps = cv2.getTickFrequency() / (tick - prev_tick)
                prev_tick = tick

                cv2.putText(color_image, f"FPS: {int(fps)}",
                            (10, 30),
                            cv2.FONT_HERSHEY_SIMPLEX,
                            0.8,
                            (0, 255, 0), 2)

                # ================= SHOW =================
                depth_vis = cv2.convertScaleAbs(depth_image, alpha=0.03)
                depth_vis = cv2.applyColorMap(depth_vis, cv2.COLORMAP_JET)

                cv2.imshow("RealSense - Color", color_image)
                cv2.imshow("RealSense - Depth", depth_vis)

                if cv2.waitKey(1) & 0xFF == ord('q'):
                    break

            except RuntimeError as e:
                print(f"Frame processing error: {e}")
                # Tiếp tục vòng lặp thay vì crash
                time.sleep(0.1)
                continue

    except Exception as e:
        print(f"RealSense initialization error: {e}")
    
    finally:
        # ================= CLEANUP =================
        if pipeline:
            pipeline.stop()
        
        cv2.destroyAllWindows()

        if use_state:
            set_state["value"] = STATE_IDLE

        print(">>> RealSense OFF | STATE -> IDLE")


if __name__ == "__main__":
    detect_r1_snapshot_loop(use_state=False)