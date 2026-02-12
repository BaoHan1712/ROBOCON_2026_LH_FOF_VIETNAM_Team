import cv2
import time
from ultralytics import YOLO
# from config_uart.sent_uart import ser, build_packet
from gui_tkinter import set_state, STATE_IDLE, STATE_SEE_R1


# ================= UART =================
# def send_packet():
#     pkt = build_packet(2, 2, 5, 5, 5)
#     ser.write(pkt)
#     print(">>> SENT Robot Stop")


# ================= YOLO =================
model = YOLO(r"cover\models\kfs.onnx", task='detect')

CLASS_R1 = "R1"
class_names = model.names
R1_INDEX = [k for k, v in class_names.items() if v == CLASS_R1][0]


# =================================================
# MAIN (REALTIME TRACK VERSION)
# =================================================
def detect_r1_snapshot_loop(use_state=True):

    cap = cv2.VideoCapture(0)

    if not cap.isOpened():
        print("Camera open failed")
        return

    print(">>> Camera ON")

    r1_start_time = None
    DETECT_TIME = 1.5

    prev_tick = cv2.getTickCount()

    try:
        while True:

            # ===== state change → thoát =====
            if use_state and set_state["value"] != STATE_SEE_R1:
                break

            ret, frame = cap.read()
            if not ret:
                break

            frame = cv2.resize(frame, (640, 480))

            # ================= YOLO TRACK =================
            results = model.track(
                frame,
                imgsz=640,
                conf=0.5,
                classes=[R1_INDEX],        # chỉ R1
                tracker=r'cover\models\bytetrack.yaml',             # tracking
                verbose=False
            )

            found_r1 = False

            for r in results:
                for box in r.boxes:
                    found_r1 = True

                    x1, y1, x2, y2 = map(int, box.xyxy[0])
                    conf = float(box.conf[0])

                    cv2.rectangle(frame, (x1, y1), (x2, y2), (255, 0, 255), 2)
                    cv2.putText(frame,
                                f"R1 {conf:.2f}",
                                (x1, y1-8),
                                cv2.FONT_HERSHEY_SIMPLEX,
                                0.7,
                                (0, 255, 255), 2)

            now = time.time()

            # =================================================
            # TIMER LOGIC (duy trì 1.5s)
            # =================================================
            if found_r1:

                if r1_start_time is None:
                    r1_start_time = now

                duration = now - r1_start_time

                cv2.putText(frame, f"HOLD: {duration:.2f}s",
                            (10, 60),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.8,
                            (0, 255, 0), 2)

                if duration >= DETECT_TIME:
                    print(">>> R1 HOLD OK -> SEND")
                    # send_packet()
                    break
            else:
                r1_start_time = None

            # ================= FPS =================
            tick = cv2.getTickCount()
            fps = cv2.getTickFrequency() / (tick - prev_tick)
            prev_tick = tick

            cv2.putText(frame, f"FPS: {int(fps)}",
                        (10, 30),
                        cv2.FONT_HERSHEY_SIMPLEX,
                        0.8,
                        (0, 255, 0), 2)

            cv2.imshow("R1 Tracking", frame)

            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

    finally:
        cap.release()
        cv2.destroyAllWindows()

        if use_state:
            set_state["value"] = STATE_IDLE

        print(">>> Camera OFF | STATE -> IDLE")


# if __name__ == "__main__":
#     detect_r1_snapshot_loop(use_state=False)