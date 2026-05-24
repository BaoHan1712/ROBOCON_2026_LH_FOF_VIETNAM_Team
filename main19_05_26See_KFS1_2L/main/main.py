import threading
import time
from gui_tkinter import (
    activate_hotspot,
    set_state,
    start_gui,
    STATE_FOREST,
    STATE_SEE_R1,
    STATE_IDLE,
    STATE_MATRIX,
    STATE_PICK_BLOCK,
    STATE_SEE_R1_L2,
)
from uart_listener import *
from config_uart.sent_uart import ser

from detect_matrix import ControlApp
from algo_forest import SelectPlaceApp, run_server
from see_R1 import detect_r1_snapshot_loop
from pick_block import run_pick_block_loop
from see_floor import detect_floor_loop

current_state = STATE_IDLE

# =========================================================================
# VŨ KHÍ TỐI THƯỢNG: RESET TOÀN BỘ HỆ THỐNG (Gọi từ nút STOP của GUI)
# =========================================================================
def force_reset_system():
    print("\n" + "🛑"*20)
    print(">> [MAIN] ĐÃ NHẤN NÚT STOP! ĐANG RESET KHẨN CẤP VỀ IDLE...")

    # 1. ÉP MỞ LẠI VÀ THÔNG TẮC CỔNG UART
    try:
        if ser is not None:
            if not ser.is_open:
                try: ser.open()
                except: pass
            if ser.is_open:
                ser.reset_input_buffer()
                ser.reset_output_buffer()
                print(">> [MAIN] Đã thông tắc và cạy mở van UART thành công!")
    except Exception as e:
        print(f">> [LỖI UART MAIN] {e}")

    # 2. ĐÁNH THỨC THẰNG LẮNG NGHE LÊN LÀM VIỆC
    try:
        from uart_listener import uart_enable
        uart_enable["value"] = True
        print(">> [MAIN] Đã mở khóa màng nhĩ cho luồng UART Listener!")
    except: 
        pass

    # 3. CHỐT HẠ TRẠNG THÁI VỀ IDLE
    try:
        from gui_tkinter import set_state, STATE_IDLE
        set_state["value"] = STATE_IDLE
        print(">> [MAIN] HỆ THỐNG ĐÃ SẴN SÀNG TRỞ LẠI TRẠNG THÁI ĐỢI (IDLE).")
    except: 
        pass
    print("🛑"*20 + "\n")

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

# 1. Mày dán cái hàm nhận dữ liệu từ bảng Tím này đè vào vị trí hàm run_pick_block() cũ:
def run_pick_block():
    print(">> [MAIN] Đang chờ người dùng chọn khối trên bảng Tím...")
    from gui_tkinter import pick_block_target
    
    # Vòng lặp chờ luồng GUI chọn xong khối hoặc người dùng bấm X hủy bỏ
    while not pick_block_target["ready"]:
        if set_state["value"] != STATE_PICK_BLOCK:
            print(">> [MAIN] Hủy trạng thái Pick Block từ bên ngoài.")
            return
        time.sleep(0.05)
        
    # Lấy ID khối thực tế (1-6) và mã sân ra để chuẩn bị bắn Camera
    block_id = pick_block_target["mode"]
    team_color = pick_block_target["team"]
    print(f">> [MAIN] Nhận lệnh kích hoạt: Khối ID = {block_id} | Mã Sân = {team_color}")

    # Gọi vòng lặp Camera (Ép use_state=False để chạy độc lập mượt mà, không kẹt luồng)
    run_pick_block_loop(mode=block_id, team_color=team_color, use_state=False)

    print(">> PICK BLOCK CLOSED.")

    def show_mode_dialog():
        import customtkinter as ctk

        ctk.set_appearance_mode("light")
        ctk.set_default_color_theme("blue")

        dialog = ctk.CTk()
        dialog.title("Chọn Mode")
        # Mở rộng chiều ngang để chứa 2 cột
        dialog.geometry("550x300")
        dialog.configure(fg_color="#f5f7fb")

        selected = {i: False for i in range(1, 7)}
        buttons = {}

        # ===== TITLE =====
        ctk.CTkLabel(
            dialog,
            text="Select Blocks",
            font=("Segoe UI", 22, "bold"),
            text_color="#1e293b"
        ).pack(pady=(15, 5))

        status_label = ctk.CTkLabel(
            dialog,
            text="Ready",
            font=("Segoe UI", 14),
            text_color="#64748b"
        )
        status_label.pack(pady=(0, 5))

        # ===== CARD (CHỨA 2 CỘT) =====
        card = ctk.CTkFrame(dialog, corner_radius=20, fg_color="#ffffff")
        card.pack(padx=20, pady=5, fill="both", expand=True)

        # Cột 1 (Trái): Chứa các nút số
        left_col = ctk.CTkFrame(card, fg_color="transparent")
        left_col.pack(side="left", expand=True, fill="both", padx=(10, 5))

        # Cột 2 (Phải): Chứa các nút chức năng
        right_col = ctk.CTkFrame(card, fg_color="transparent")
        right_col.pack(side="right", expand=True, fill="both", padx=(5, 10))

        # --- XỬ LÝ CỘT TRÁI (Nút 1-6) ---
        btn_frame = ctk.CTkFrame(left_col, fg_color="transparent")
        btn_frame.pack(expand=True, pady=10)

        btn_style = {
            "width": 60,
            "height": 60,
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

        # --- XỬ LÝ CỘT PHẢI (Nút Confirm/Reset) ---
        action_frame = ctk.CTkFrame(right_col, fg_color="transparent")
        action_frame.pack(expand=True)

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

        # Nút Confirm nằm trên
        ctk.CTkButton(
            action_frame,
            text="✔ Confirm",
            width=140, height=45,
            corner_radius=14,
            font=("Segoe UI", 16, "bold"),
            fg_color="#16a34a",
            hover_color="#15803d",
            command=on_confirm
        ).pack(pady=(0, 15))

        # Nút Reset nằm dưới
        ctk.CTkButton(
            action_frame,
            text="↺ Reset",
            width=140, height=45,
            corner_radius=14,
            font=("Segoe UI", 16, "bold"),
            fg_color="#dc2626",
            hover_color="#b91c1c",
            command=on_reset
        ).pack(pady=0)

        dialog.mainloop()

    show_mode_dialog()
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

    
# =========================================================================
# CHỈ CẦN DUY NHẤT HÀM STATE_MANAGER, XÓA SẠCH MỌI HÀM GIAO DIỆN CŨ!!!
# =========================================================================
def state_manager():
    while True:
        state = set_state["value"]

        if state == STATE_IDLE:
            time.sleep(0.02)
            continue
            
        # 🔥 CHỐT CHẶN SỐ 98: Đứng im đợi Bảng Tím chọn khối
        # TUYỆT ĐỐI KHÔNG SỬA THÀNH SỐ 4 NHÉ!
        if state == 98:
            time.sleep(0.02)
            continue

        if state == STATE_SEE_R1:
            detect_r1_snapshot_loop()
            print(">> [MAIN] Chờ 1.5s để Jetson xả điện cổng USB Camera...")
            time.sleep(0.5) 
            if set_state["value"] == STATE_SEE_R1:
                set_state["value"] = STATE_IDLE

        elif state == STATE_MATRIX:
            retry_zone3()
            if set_state["value"] == STATE_MATRIX:
                set_state["value"] = STATE_IDLE

        elif state == STATE_FOREST:
            run_algothism_forest()
            if set_state["value"] == STATE_FOREST:
                set_state["value"] = STATE_IDLE

        # 🔥 TRẠNG THÁI ID = 4 (PICK BLOCK TỐC ĐỘ CAO)
        elif state == STATE_PICK_BLOCK:
            from gui_tkinter import pick_block_data
            
            team = pick_block_data["team"]
            mode = pick_block_data["block_id"]
            
            print(f">> [MAIN] BẮT ĐẦU GẮP: SÂN {team} | KHỐI ID: {mode}")
            
            # Kích thẳng Camera, đéo cần chờ xả điện gì hết!
            run_pick_block_loop(mode=mode, team_color=team, use_state=False)
            
            # 🔥 ĐÃ CHẶT BỎ time.sleep(1.5) TRÓI CHÂN Ở ĐÂY! Rút Cam phát là nhả về IDLE luôn!
            if set_state["value"] == STATE_PICK_BLOCK:
                set_state["value"] = STATE_IDLE

        # 🔥 CẮM THÊM CỤC NÀY VÀO ĐỂ GỌI FILE MỚI CỦA SẾP!
        elif state == STATE_SEE_R1_L2:
            # Tao giả sử mày sẽ tạo 1 file tên là 'see_R1_L2.py' chứa hàm 'detect_r1_l2_loop'
            from see_R1_L2 import detect_r1_l2_loop 
            
            print(">> [MAIN] ĐANG GỌI FILE MỚI: QUÉT R1 LẦN 2 (TRÁNH VẬT CẢN)!")
            detect_r1_l2_loop() 
            
            print(">> [MAIN] Chờ 1.5s để Jetson xả điện cổng USB Camera...")
            time.sleep(1.5) 
            if set_state["value"] == STATE_SEE_R1_L2:
                set_state["value"] = STATE_IDLE
        # 🔥 ĐỤC LỖ CẮM THÊM 2 NHÁNH NÀY VÀO TRƯỚC PHẦN MỞ VAN MÀNG NHĨ UART:
        elif state == 6:
            # Nhận số 6 -> Chạy combo quét sàn sân XANH
            detect_floor_loop(team_color="BLUE")
            if set_state["value"] == 6:
                set_state["value"] = STATE_IDLE

        elif state == 7:
            # Nhận số 7 -> Chạy combo quét sàn sân ĐỎ
            detect_floor_loop(team_color="RED")
            if set_state["value"] == 7:
                set_state["value"] = STATE_IDLE
        # 🔓 MỞ LẠI VAN MÀNG NHĨ UART LISTENER
        try:
            uart_enable["value"] = True
        except: 
            pass

        time.sleep(0.01)

if __name__ == "__main__":
    import subprocess
    import os
    import sys
    import time
    import threading

    # =======================================================
    # 1. TỰ ĐỘNG BẬT SERVER WEB NGAY KHI CHẠY MAIN.PY
    # =======================================================
    current_dir = os.path.dirname(os.path.abspath(__file__))
    server_file = os.path.join(current_dir, "server_app.py")
    python_path = "/home/robot/miniconda3/envs/pyenv/bin/python"
    
    log_path = os.path.join(current_dir, "server_error.log")
    log_file = open(log_path, "w")

    print(">> [HỆ THỐNG] Đang tự động gọi Server Web chạy ngầm...")
    server_process = subprocess.Popen(
        [python_path, server_file],
        cwd=current_dir,
        stdout=log_file,
        stderr=subprocess.STDOUT
    )
    print(">> [OK] TRẠM CHỈ HUY ĐÃ LÊN SÓNG Ở CỔNG 5001!")

    # =======================================================
    # 2. LẮNG NGHE UART & QUẢN LÝ TRẠNG THÁI (CHẠY NGẦM)
    # =======================================================
    # Đẩy thằng lắng nghe UART ra thread riêng chạy ngầm
    uart_thread = threading.Thread(
        target=uart_state_listener,
        args=(ser,),
        daemon=True
    )
    uart_thread.start()

    # Đẩy thằng quản lý trạng thái máy Cam ra thread riêng chạy ngầm
    state_thread = threading.Thread(
        target=state_manager,
        daemon=True
    )
    state_thread.start()

    # =======================================================
    # 3. LUỒNG CHÍNH ĐỘC QUYỀN: BẬT GIAO DIỆN CHÍNH (MAIN THREAD)
    # =======================================================
    print(">> [HỆ THỐNG] Đang kích hoạt giao diện chính Robot Control Panel...")
    try:
        # Ép thằng GUI chạy trên Luồng Chủ để khóa cấu hình đệ quy, đéo cho phân thân!
        start_gui()
    except KeyboardInterrupt:
        print(">> Đang tắt hệ thống...")
    finally:
        # Dọn dẹp rác khi tắt app
        if 'server_process' in locals():
            server_process.terminate()
        log_file.close()
        print(">> Đã tiêu diệt Server ngầm sạch sẽ. HỆ THỐNG OFFLINE!")