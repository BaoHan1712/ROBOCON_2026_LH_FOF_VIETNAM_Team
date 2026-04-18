import time
from gui_tkinter import STATE_SEE_R1, set_state, STATE_IDLE, STATE_MATRIX, STATE_FOREST

uart_enable = {"value": True}

def uart_state_listener(ser):
    print(">> UART LISTENER STARTED")

    while True:
        # ❌ Không nghe khi không cho phép
        if not uart_enable["value"]:
            time.sleep(0.02)
            continue

        # ❌ Chỉ nghe khi IDLE
        if set_state["value"] != STATE_IDLE:
            time.sleep(0.02)
            continue

        # ===== đọc 1 byte =====
        if ser.in_waiting:
            data = ser.read(1)[0]  

            # ===== xử lý =====
            if data == 1:
                set_state["value"] = STATE_SEE_R1
            elif data == 2:
                set_state["value"] = STATE_MATRIX
            elif data == 3:
                set_state["value"] = STATE_FOREST
            else:
                continue

            print(f">> UART → STATE {data}")

            # 🔴 khóa UART sau khi nhận
            uart_enable["value"] = False

        time.sleep(0.005)