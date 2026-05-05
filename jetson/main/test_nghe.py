import time
from gui_tkinter import STATE_SEE_R1, set_state, STATE_IDLE, STATE_MATRIX, STATE_FOREST
from config_uart.sent_uart import ser

def uart_state_listener(ser):
    print(">> UART LISTENER RUNNING (CONTINUOUS)")

    while True:
        try:
            # đọc tất cả dữ liệu có sẵn
            if ser.in_waiting > 0:
                data = ser.read(ser.in_waiting)

                for byte in data:
                    if byte == 1:
                        set_state["value"] = STATE_SEE_R1
                        print(">> UART → STATE SEE_R1")

                    elif byte == 2:
                        set_state["value"] = STATE_MATRIX
                        print(">> UART → STATE MATRIX")

                    elif byte == 3:
                        set_state["value"] = STATE_FOREST
                        print(">> UART → STATE FOREST")

                    else:
                        print(f">> UART UNKNOWN: {byte}")

            time.sleep(0.001)  # giảm latency

        except Exception as e:
            print("UART ERROR:", e)
            time.sleep(0.1)

uart_state_listener(ser)