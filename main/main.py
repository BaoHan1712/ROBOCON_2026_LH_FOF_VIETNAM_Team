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

    mode_result = {"value": None}

    def show_mode_dialog():
        import customtkinter as ctk

        ctk.set_appearance_mode("light")
        ctk.set_default_color_theme("blue")

        dialog = ctk.CTk()
        dialog.title("Chọn Mode")
        dialog.geometry("450x400")
        dialog.configure(fg_color="#f5f7fb")

        selected = {i: False for i in range(1, 7)}
        buttons = {}

        # ===== TITLE =====
        ctk.CTkLabel(
            dialog,
            text="Select Blocks",
            font=("Segoe UI", 22, "bold"),
            text_color="#1e293b"
        ).pack(pady=(20, 5))

        status_label = ctk.CTkLabel(
            dialog,
            text="Ready",
            font=("Segoe UI", 14),
            text_color="#64748b"
        )
        status_label.pack(pady=(0, 5))

        # ===== CARD =====
        card = ctk.CTkFrame(dialog, corner_radius=20, fg_color="#ffffff")
        card.pack(padx=20, pady=5, fill="both", expand=True)

        btn_frame = ctk.CTkFrame(card, fg_color="transparent")
        btn_frame.pack(expand=True, pady=15)

        btn_style = {
            "width": 80,
            "height": 80,
            "corner_radius": 16,
            "font": ("Segoe UI", 22, "bold"),
            "text_color": "white"
        }

        def toggle(n):
            selected[n] = not selected[n]
            if selected[n]:
                buttons[n].configure(fg_color="#f59e0b", hover_color="#d97706")
            else:
                buttons[n].configure(fg_color="#4f46e5", hover_color="#6366f1")

        # 4 5 6 hàng trên, 1 2 3 hàng dưới
        for i in range(1, 7):
            row = 1 if i <= 3 else 0
            col = (i - 1) % 3

            btn = ctk.CTkButton(
                btn_frame,
                text=str(i),
                fg_color="#4f46e5",
                hover_color="#6366f1",
                command=lambda n=i: toggle(n),
                **btn_style
            )
            btn.grid(row=row, column=col, padx=12, pady=8)
            buttons[i] = btn

        # ===== BOTTOM BUTTONS =====
        bottom_frame = ctk.CTkFrame(dialog, fg_color="transparent")
        bottom_frame.pack(pady=(5, 15))

        def on_confirm():
            # Lấy số nào được chọn (có thể chọn 1 trong mỗi cột)
            # Ưu tiên hàng trên (4-6) nếu cùng cột
            col_map = {1: 1, 2: 2, 3: 3, 4: 1, 5: 2, 6: 3}
            entry = [0, 0, 0]
            for n in range(1, 7):
                if selected[n]:
                    idx = col_map[n] - 1
                    entry[idx] = n

            mode_result["value"] = entry  # [e1, e2, e3]
            dialog.destroy()

        def on_reset():
            for i in range(1, 7):
                selected[i] = False
                buttons[i].configure(fg_color="#4f46e5", hover_color="#6366f1")
            status_label.configure(text="Reset", text_color="#64748b")

        def on_close():
            mode_result["value"] = None
            dialog.destroy()

        dialog.protocol("WM_DELETE_WINDOW", on_close)

        ctk.CTkButton(
            bottom_frame,
            text="✔ Confirm",
            width=180, height=45,
            corner_radius=14,
            font=("Segoe UI", 16, "bold"),
            fg_color="#16a34a",
            hover_color="#15803d",
            command=on_confirm
        ).grid(row=0, column=0, padx=10)

        ctk.CTkButton(
            bottom_frame,
            text="↺ Reset",
            width=120, height=45,
            corner_radius=14,
            font=("Segoe UI", 16, "bold"),
            fg_color="#dc2626",
            hover_color="#b91c1c",
            command=on_reset
        ).grid(row=0, column=1, padx=10)

        dialog.mainloop()

    t = threading.Thread(target=show_mode_dialog)
    t.start()
    t.join()

    if mode_result["value"] is None:
        print(">> Người dùng không chọn mode, hủy Pick Block.")
        set_state["value"] = STATE_IDLE
        return

    e1, e2, e3 = mode_result["value"]
    print(f">> Mode được chọn: entry1={e1} entry2={e2} entry3={e3}")

    # Truyền e1 làm mode chính (hoặc tuỳ logic bạn)
    run_pick_block_loop(mode=e1 or e2 or e3, use_state=True)

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


