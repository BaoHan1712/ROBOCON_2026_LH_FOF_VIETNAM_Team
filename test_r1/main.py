import threading
import time
from gui_tkinter import set_state, STATE_FOREST
import cv2

from gui_tkinter import start_gui, set_state
from cam_detect import weapon_camera_loop
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
    global current_state
    while True:
        state = set_state["value"]

        if state == STATE_WEAPON:
            weapon_camera_loop()

        elif state == STATE_MATRIX:
            matrix_camera_loop()

        elif state == STATE_FOREST:
            run_algothism_forest()

        time.sleep(0.01)


if __name__ == "__main__":
    # chạy GUI ở thread riêng
    gui_thread = threading.Thread(target=start_gui)
    gui_thread.daemon = True
    gui_thread.start()

    # chạy state manager
    state_manager()




