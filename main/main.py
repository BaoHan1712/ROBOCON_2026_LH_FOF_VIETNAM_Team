import threading
import time
from gui_tkinter import set_state, STATE_FOREST, STATE_SEE_R1, STATE_IDLE, STATE_MATRIX, STATE_PICK_BLOCK
from uart_listener import *
from config_uart.sent_uart import ser

from gui_tkinter import start_gui, set_state
from detect_matrix import ControlApp
from algo_forest import SelectPlaceApp
from see_R1 import detect_r1_snapshot_loop
from pick_block import run_pick_block_loop

current_state = STATE_IDLE

def run_algothism_forest():
    print(">> STARTING FOREST UI...")
    app = SelectPlaceApp()
    app.run_algothism_forest()
    
    # Sau khi cửa sổ đóng, đảm bảo trạng thái về IDLE 
    if set_state["value"] == STATE_FOREST:
        set_state["value"] = STATE_IDLE
    
    print(">> FOREST UI CLOSED.")

def retry_zone3():
    print(">> STARTING retry zone 3...")
    retry3 = ControlApp()
    retry3.mainloop()
    
    # Sau khi cửa sổ đóng, đảm bảo trạng thái về IDLE 
    if set_state["value"] == STATE_FOREST:
        set_state["value"] = STATE_IDLE
    
    print(">> FOREST UI CLOSED.")

def run_pick_block():
    print(">> STARTING PICK BLOCK...")
    
    # Lấy mode từ set_state nếu có, mặc định là 1
    mode = set_state.get("pick_mode", 1)
    run_pick_block_loop(mode=mode, use_state=True)
    
    if set_state["value"] == STATE_PICK_BLOCK:
        set_state["value"] = STATE_IDLE
    
    print(">> PICK BLOCK CLOSED.")
    
def state_manager():
    while True:
        state = set_state["value"]

        if state == STATE_IDLE:
            time.sleep(0.02)
            continue

        if state == STATE_SEE_R1:
            detect_r1_snapshot_loop()

        elif state == STATE_MATRIX:
            retry_zone3()

        elif state == STATE_FOREST:
            run_algothism_forest()

        elif state == STATE_PICK_BLOCK:
            run_pick_block()

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


