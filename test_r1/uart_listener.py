import time
from gui_tkinter import set_state
from main import STATE_IDLE, STATE_WEAPON, STATE_MATRIX, STATE_FOREST

uart_enable = {"value": True}

def uart_state_listener(ser):
    buffer = bytearray()
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

        if ser.in_waiting:
            buffer += ser.read(ser.in_waiting)

        while len(buffer) >= 2:
            data = buffer.pop(0)
            checksum = buffer.pop(0)

            if checksum != (data ^ 0xFF):
                continue

            if data == 1:
                set_state["value"] = STATE_WEAPON
            elif data == 2:
                set_state["value"] = STATE_MATRIX
            elif data == 3:
                set_state["value"] = STATE_FOREST
            else:
                continue

            print(f">> UART → STATE {data}")

            # 🔴 KHÓA UART sau khi nhận
            uart_enable["value"] = False
            break

        time.sleep(0.005)