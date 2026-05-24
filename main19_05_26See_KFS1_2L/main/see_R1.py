import pyrealsense2 as rs
import numpy as np
import cv2
import time
from config_uart.sent_uart import build_packet, send_packet_once, ser

from gui_tkinter import set_state, STATE_IDLE, STATE_SEE_R1

# ================= POLYGON =================
points = np.array([
    (5,335),
    (632,325),
    (631,127),
    (1,138)
], dtype=np.int32)

# ================= HẰNG SỐ =================
DEPTH_THRESHOLD = 900  # mm - ngưỡng phát hiện vật cản
DETECT_TIME = 0.8  # giây - thời gian giữ để confirm
MIN_POINTS = 20  # số điểm tối thiểu để coi là có vật cản

# ================= MAIN =================
def detect_r1_snapshot_loop(use_state=True):
    """
    Hàm chạy vòng lặp phát hiện vật cản bằng RealSense D435i
    """
    print(">>> RealSense [SEE R1] ON")

    pipeline = None
    align = None

    print(">> [SEE R1] Đang kết nối Camera...")
    while True:
        try:
            # 👉 Bắt buộc phải đẻ ra Pipeline mới tinh mỗi lần kết nối
            pipeline = rs.pipeline()
            config = rs.config()
            config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)
            config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)

            pipeline.start(config)
            align = rs.align(rs.stream.color)
            
            print(">> [SEE R1] ✓ Camera mở THÀNH CÔNG!")
            break # Mở ngon lành thì thoát vòng lặp để chạy tiếp
            
        except Exception as e:
            print(f">> [SEE R1] LỖI USB BUSY ({e}). Đang vả Hardware Reset...")
            try:
                # Xóa pipeline lỗi đi để nhả RAM
                del pipeline
                
                ctx = rs.context()
                if len(ctx.devices) > 0:
                    ctx.devices[0].hardware_reset()
            except:
                pass
            
            print(">> [SEE R1] Đợi 5 giây cho Jetson nạp lại Driver USB...")
            time.sleep(2) # Chờ 5s để USB kịp nhận lại thiết bị

    # Chờ 1s để camera ổn định ánh sáng
    time.sleep(1)

    r1_start_time = None
    prev_tick = cv2.getTickCount()
    sent_clear = False

    try:
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

                if not has_object:  # KHÔNG có vật cản
                    if r1_start_time is None:
                        r1_start_time = now

                    duration = now - r1_start_time

                    cv2.putText(color_image, f"CLEAR: {duration:.2f}s",
                                (10, 60),
                                cv2.FONT_HERSHEY_SIMPLEX, 0.8,
                                (0, 255, 0), 2)

                    # ===== ĐỦ THỜI GIAN → GỬI UART =====
                    if duration >= DETECT_TIME and not sent_clear:
                        print(">>> NO OBJECT DETECTED -> SEND PACKET")

                        start_packet = build_packet(2, 1, 10, 10, 10)
                        ser.write(start_packet)

                        sent_clear = True

                        # ===== THOÁT NGAY SAU KHI GỬI =====
                        break

                else:
                    r1_start_time = None
                    sent_clear = False   # reset lại khi có vật cản

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
                    
                # Xóa rác RealSense mỗi vòng lặp
                try:
                    del frames
                    del color_frame
                    del depth_frame
                except:
                    pass

            except RuntimeError as e:
                print(f"Frame processing error: {e}")
                time.sleep(0.1)
                continue

    except Exception as e:
        print(f"RealSense runtime error: {e}")
    
    finally:
        print(">> [SEE R1] Đang nhả cổng USB cho thằng khác xài...")
        try:
            pipeline.stop()
        except:
            pass
            
        # Xóa sạch biến nhớ
        try: 
            del pipeline
        except: 
            pass
            
        try: 
            ctx = rs.context()
            del ctx
        except: 
            pass
        
        cv2.destroyAllWindows()
        for _ in range(5):
            cv2.waitKey(1)
            
        print(">> [SEE R1] Đã tắt sạch Camera! Chuyển về IDLE.")

# if __name__ == "__main__":
#     detect_r1_snapshot_loop(use_state=False)