import threading
import time
from gui_tkinter import set_state, STATE_FOREST
from uart_listener import *
from config_uart.sent_uart import ser

from gui_tkinter import start_gui, set_state
# from cam_detect import weapon_camera_loop
from detect_matrix import matrix_camera_loop
from algo_forest import SelectPlaceApp


# ===== STATE DEFINE =====
STATE_IDLE = 0
STATE_WEAPON = 1
STATE_MATRIX = 2
STATE_FOREST = 3

current_state = STATE_IDLE

def run_algothism_forest():
    print(">> STARTING FOREST UI...")
    app = SelectPlaceApp()
    app.run_algothism_forest()
    
    # Sau khi cửa sổ đóng, đảm bảo trạng thái về IDLE 
    if set_state["value"] == STATE_FOREST:
        set_state["value"] = STATE_IDLE
    
    print(">> FOREST UI CLOSED.")

def state_manager():
    while True:
        state = set_state["value"]

        if state == STATE_IDLE:
            time.sleep(0.02)
            continue

        # if state == STATE_WEAPON:
        #     weapon_camera_loop()

        elif state == STATE_MATRIX:
            matrix_camera_loop()

        elif state == STATE_FOREST:
            run_algothism_forest()

        # 🔁 QUAY VỀ IDLE
        set_state["value"] = STATE_IDLE

        # 🔓 MỞ LẠI UART
        uart_enable["value"] = True

        time.sleep(0.01)

if __name__ == "__main__":
    gui_thread = threading.Thread(target=start_gui, daemon=True)
    gui_thread.start()

    uart_thread = threading.Thread(
        target=uart_state_listener,
        args=(ser,),
        daemon=True
    )
    uart_thread.start()

    state_manager()


