import tkinter as tk
import os
import subprocess
import tkinter.messagebox as messagebox
import threading
import time

# Biến toàn cục quản lý Server ngầm
server_process = None

HOTSPOT_SSID = "VTV 5G"
HOTSPOT_PASSWORD = "FOFvodich"
HOTSPOT_PROFILE_CANDIDATES = ("VTV_5G", "VTV 5G", "Hotspot")
DEFAULT_HOTSPOT_PROFILE = "Hotspot"


def run_nmcli(args, check=True, timeout=25):
    """Run nmcli and return stdout; raise a useful error when it fails."""
    cmd = ["nmcli", *args]
    try:
        completed = subprocess.run(
            cmd,
            check=False,
            text=True,
            capture_output=True,
            timeout=timeout,
        )
    except FileNotFoundError as exc:
        raise RuntimeError("Không tìm thấy lệnh nmcli. Máy cần NetworkManager để phát Wi-Fi.") from exc
    except subprocess.TimeoutExpired as exc:
        raise RuntimeError(f"Lệnh {' '.join(cmd)} bị quá thời gian chờ.") from exc

    if check and completed.returncode != 0:
        detail = (completed.stderr or completed.stdout or "").strip()
        raise RuntimeError(f"{' '.join(cmd)} thất bại: {detail}")

    return (completed.stdout or "").strip()


def get_wifi_device():
    output = run_nmcli(["-t", "-f", "DEVICE,TYPE", "device", "status"], check=True)
    for line in output.splitlines():
        parts = line.split(":")
        if len(parts) >= 2 and parts[1] == "wifi" and parts[0]:
            return parts[0]
    raise RuntimeError("Không tìm thấy card Wi-Fi.")


def connection_exists(profile_name):
    result = subprocess.run(
        ["nmcli", "connection", "show", profile_name],
        check=False,
        text=True,
        capture_output=True,
    )
    return result.returncode == 0


def get_connection_field(profile_name, field_name):
    return run_nmcli(
        ["-g", field_name, "connection", "show", profile_name],
        check=False,
    ).strip()


def find_hotspot_profile():
    for profile_name in HOTSPOT_PROFILE_CANDIDATES:
        if not connection_exists(profile_name):
            continue

        conn_type = get_connection_field(profile_name, "connection.type")
        ssid = get_connection_field(profile_name, "802-11-wireless.ssid")
        mode = get_connection_field(profile_name, "802-11-wireless.mode")
        if conn_type == "802-11-wireless" and (mode == "ap" or ssid == HOTSPOT_SSID):
            return profile_name

    output = run_nmcli(["-t", "-f", "NAME,TYPE", "connection", "show"], check=True)
    for line in output.splitlines():
        parts = line.rsplit(":", 1)
        if len(parts) != 2 or parts[1] != "802-11-wireless":
            continue

        profile_name = parts[0]
        ssid = get_connection_field(profile_name, "802-11-wireless.ssid")
        mode = get_connection_field(profile_name, "802-11-wireless.mode")
        if ssid == HOTSPOT_SSID and mode == "ap":
            return profile_name

    return None


def ensure_hotspot_profile(wifi_device):
    profile_name = find_hotspot_profile()
    if profile_name:
        return profile_name

    print(f">> [MẠNG] Chưa có profile Hotspot, đang tạo SSID {HOTSPOT_SSID}...")
    run_nmcli(
        [
            "device", "wifi", "hotspot",
            "ifname", wifi_device,
            "con-name", DEFAULT_HOTSPOT_PROFILE,
            "ssid", HOTSPOT_SSID,
            "password", HOTSPOT_PASSWORD,
        ],
        check=True,
        timeout=35,
    )
    return DEFAULT_HOTSPOT_PROFILE


def activate_hotspot():
    wifi_device = get_wifi_device()
    profile_name = ensure_hotspot_profile(wifi_device)

    profile_device = get_connection_field(profile_name, "connection.interface-name")
    if profile_device:
        wifi_device = profile_device

    print(f">> [MẠNG] Bật Wi-Fi AP bằng profile '{profile_name}' trên {wifi_device}...")
    run_nmcli(["radio", "wifi", "on"], check=False, timeout=10)
    run_nmcli(["device", "disconnect", wifi_device], check=False, timeout=10)
    time.sleep(0.5)
    run_nmcli(["connection", "up", profile_name, "ifname", wifi_device], check=True, timeout=35)
    return profile_name, wifi_device


def set_hotspot_button(btn_widget, text, bg):
    if btn_widget is None:
        return
    btn_widget.after(0, lambda: btn_widget.config(text=text, bg=bg))


def turn_on_hotspot(btn_widget):
    set_hotspot_button(btn_widget, "ĐANG BẬT WIFI...", "#d35400")

    def worker():
        print(">> [MẠNG] Đang bật Hotspot VTV 5G từ giao diện...")
        try:
            profile_name, wifi_device = activate_hotspot()
            print(f">> [OK] Đã phát Wi-Fi VTV 5G bằng profile '{profile_name}' trên {wifi_device}!")
            set_hotspot_button(btn_widget, "ĐÃ BẬT VTV 5G", "#27ae60")
            btn_widget.after(
                0,
                lambda: messagebox.showinfo(
                    "Mạng đã lên sóng",
                    "Đã phát Wi-Fi thành công!\n\nTên mạng: VTV 5G\nMật khẩu: FOFvodich\nIP: 10.42.0.1",
                ),
            )
        except Exception as e:
            print(f">> [LỖI MẠNG] Không bật được Hotspot: {e}")
            set_hotspot_button(btn_widget, "LỖI PHÁT WIFI", "#c0392b")
            btn_widget.after(
                0,
                lambda: messagebox.showerror(
                    "Lỗi Hệ Thống",
                    f"Không thể bật Hotspot. Có thể Jetson chưa nhận Card Wi-Fi hoặc profile Wi-Fi bị lỗi.\n\nChi tiết lỗi: {e}",
                ),
            )

    threading.Thread(target=worker, daemon=True).start()


def auto_turn_on_hotspot(btn_widget):
    set_hotspot_button(btn_widget, "ĐANG TỰ BẬT WIFI...", "#d35400")

    def worker():
        print(">> [HỆ THỐNG] Đang tự động bật Hotspot VTV 5G...")
        try:
            profile_name, wifi_device = activate_hotspot()
            print(f">> [OK] AUTO-HOTSPOT đã lên sóng bằng profile '{profile_name}' trên {wifi_device}!")
            set_hotspot_button(btn_widget, "ĐÃ BẬT VTV 5G", "#27ae60")
        except Exception as e:
            print(f">> [LỖI MẠNG] Auto-Hotspot lỗi: {e}")
            set_hotspot_button(btn_widget, "LỖI PHÁT WIFI", "#c0392b")

    threading.Thread(target=worker, daemon=True).start()
    
def start_web_server(btn_widget):
    global server_process
    
    # Chống bấm đúp
    if server_process is not None:
        messagebox.showinfo("Báo cáo", "Server đang chạy rồi ní ơi! Lấy điện thoại quét IP đi!")
        return
        
    current_dir = os.path.dirname(os.path.abspath(__file__))
    server_file = os.path.join(current_dir, "server_app.py")
    python_path = "/home/robot/miniconda3/envs/pyenv/bin/python"
    
    # KIỂM TRA TẬN RĂNG: XEM MÀY ĐÃ TẠO FILE CHƯA!
    if not os.path.exists(server_file):
        messagebox.showerror("Lỗi Chí Mạng", f"Đéo tìm thấy file:\n{server_file}\n\nMày đã tạo file server_app.py chưa???")
        btn_widget.config(text="❌ THIẾU FILE", bg="#c0392b")
        return
        
    try:
        print(">> Đang kích hoạt Server Web độc lập...")
        
        # Mở một file log để nếu Server chết, nó ói lý do vào đây
        log_path = os.path.join(current_dir, "server_error.log")
        log_file = open(log_path, "w")
        
        server_process = subprocess.Popen(
            [python_path, server_file], 
            cwd=current_dir,
            stdout=log_file,
            stderr=subprocess.STDOUT
        )
        print(">> [OK] Lệnh bật Server đã được bắn đi!")
        btn_widget.config(text="✅ SERVER OK", bg="#27ae60")
        
    except Exception as e:
        messagebox.showerror("Lỗi Subprocess", f"Không thể kích hoạt luồng ngầm:\n{e}")
        btn_widget.config(text="❌ LỖI HỆ THỐNG", bg="#c0392b")

# ===== STATE CONSTANTS =====
STATE_IDLE       = 0
STATE_SEE_R1     = 1
STATE_MATRIX     = 2
STATE_FOREST     = 3
STATE_PICK_BLOCK = 4
STATE_SEE_R1_L2  = 5
STATE_SEE_FLOOR_BLUE = 6  # STM32 gửi 6 -> Quét sàn + đặt ma trận Sân Xanh
STATE_SEE_FLOOR_RED  = 7  # STM32 gửi 7 -> Quét sàn + đặt ma trận Sân Đỏ

set_state = {"value": STATE_IDLE}

# ===== STATE FUNCTIONS =====
def set_see_r1():
    set_state["value"] = STATE_SEE_R1
    print(">> STATE = DETECT R1")

def set_matrix():
    set_state["value"] = STATE_MATRIX
    print(">> STATE = MATRIX DETECT")

def set_forest():
    set_state["value"] = STATE_FOREST
    print(">> STATE = FOREST DETECT")

pick_block_data = {"team": "0", "block_id": 1}

# ====================================================================
# 1. HÀM PICK BLOCK (GỌI BẢNG TÍM CHỌN KHỐI 1-6)
# ====================================================================
def set_pick_block():
    print(">> [GUI] Đang mở Bảng Tím chọn Sân và Khối...")
    # 🔥 BÁO ĐỘNG ĐỎ TRÊN UI: Ép LED nhảy sang 98 (Main đứng đợi!)
    set_state["value"] = 98 
    
    popup = tk.Toplevel()
    popup.title("Cấu hình PICK BLOCK")
    popup.geometry("550x360")
    popup.configure(bg="#2b2b2b")
    popup.resizable(False, False)
    popup.attributes("-topmost", True)
    
    # Hủy ngang thì trả về IDLE xanh
    def on_close_popup():
        print(">> [GUI] Đã hủy chọn khối, quay về IDLE.")
        set_state["value"] = STATE_IDLE
        popup.destroy()
        
    popup.protocol("WM_DELETE_WINDOW", on_close_popup)
    
    tk.Label(popup, text="1. CHỌN SÂN THI ĐẤU", font=("Arial", 12, "bold"), fg="#00f2ff", bg="#2b2b2b").pack(pady=(15, 5))
    team_var = tk.StringVar(value="0") 
    frame_team = tk.Frame(popup, bg="#2b2b2b")
    frame_team.pack()
    
    tk.Label(popup, text="2. CHỌN ID KHỐI ĐỂ GẮP", font=("Arial", 12, "bold"), fg="#f59e0b", bg="#2b2b2b").pack(pady=(15, 10))
    frame_blocks = tk.Frame(popup, bg="#2b2b2b")
    frame_blocks.pack()
    
    def launch_camera(block_id):
        team_code = team_var.get()
        print(f">> [GUI] Đã chốt -> Mã Sân: {team_code} | ID Khối: {block_id}")
        
        pick_block_data["team"] = team_code
        pick_block_data["block_id"] = block_id
        
        popup.protocol("WM_DELETE_WINDOW", lambda: None)
        popup.destroy()
        
        # 🔥 CHỐT HẠ: Trả về ID 4 để Main nổ máy chạy Camera Picker!
        set_state["value"] = STATE_PICK_BLOCK 

    def update_block_buttons():
        for widget in frame_blocks.winfo_children():
            widget.destroy()
            
        current_team = team_var.get()
        row_top = [4, 5, 6]
        row_bottom = [1, 2, 3]
        btn_color = "#2980b9"
        btn_active = "#3498db"
        
        if current_team == "0":
            row_top = [6, 5, 4]
            row_bottom = [3, 2, 1]
            btn_color = "#d4332d" 
            btn_active = "#ff006a"

        for r_idx, row_data in enumerate([row_top, row_bottom]):
            for c_idx, val in enumerate(row_data):
                btn = tk.Button(frame_blocks, text=str(val), font=("Arial", 14, "bold"), 
                                bg=btn_color, fg="white", width=4, height=1, bd=0,
                                activebackground=btn_active, activeforeground="white",
                                command=lambda v=val: launch_camera(v))
                btn.grid(row=r_idx, column=c_idx, padx=6, pady=6)

    tk.Radiobutton(frame_team, text="ID 0: SÂN ĐỎ", variable=team_var, value="0", 
                   font=("Arial", 11, "bold"), bg="#c0392b", fg="white", selectcolor="#e74c3c", 
                   indicatoron=0, width=15, height=2, command=update_block_buttons).pack(side="left", padx=10)
    tk.Radiobutton(frame_team, text="ID 1: SÂN XANH", variable=team_var, value="1", 
                   font=("Arial", 11, "bold"), bg="#2980b9", fg="white", selectcolor="#3498db", 
                   indicatoron=0, width=15, height=2, command=update_block_buttons).pack(side="left", padx=10)
    
    update_block_buttons()

# ====================================================================
# 2. HÀM CHECK R1 LẦN 2 (NÉ VẬT CẢN - KÍCH HOẠT CỜ SỐ 5)
# ====================================================================
def set_see_r1_l2():
    set_state["value"] = STATE_SEE_R1_L2
    print(">> STATE = CHECK R1 LẦN 2 (NÉ VẬT CẢN)")

# (Giữ nguyên hàm def set_idle(): ở bên dưới của mày)
def set_idle():
    print("\n" + "🛑"*20)
    print(">> [GUI] ĐÃ NHẤN NÚT STOP! ĐANG RESET KHẨN CẤP VỀ IDLE...")

    # 1. Ép hệ thống về trạng thái ĐỢI LỆNH
    set_state["value"] = STATE_IDLE

    # 2. BÓP CỔ CAMERA NHẬN DIỆN (Dùng hàm stop_camera bọc thép tao đã viết cho mày)
    try:
        import pick_block
        pick_block.stop_camera()
        print(">> [GUI] Đã vung búa tạ tắt Camera AI!")
    except Exception as e:
        pass

    # 3. THÔNG TẮC ĐƯỜNG ỐNG UART (XÀ BENG)
    try:
        from config_uart.sent_uart import ser
        if ser is not None:
            if not ser.is_open:
                try: ser.open()
                except: pass
            if ser.is_open:
                ser.reset_input_buffer()
                ser.reset_output_buffer()
                print(">> [GUI] Đã thông tắc và cạy mở van UART thành công!")
    except Exception as e:
        print(f">> [LỖI UART GUI] Không thể reset van UART: {e}")

    # 4. ĐÁNH THỨC THẰNG LẮNG NGHE LÊN LÀM VIỆC LẠI
    try:
        # Nếu đang ở file GUI thì import biến từ file uart_listener
        from uart_listener import uart_enable
        uart_enable["value"] = True
        print(">> [GUI] Đã mở khóa màng nhĩ cho luồng UART Listener!")
    except Exception as e:
        print(f">> [LỖI LẮNG NGHE] {e}")

    print(">> [GUI] RESET THÀNH CÔNG! HỆ THỐNG ĐÃ TRỞ LẠI TRẠNG THÁI ĐỢI.")
    print("🛑"*20 + "\n")

# ===== CLOSE =====
def on_close():
    global server_process
    # Bóp cổ giết Server ngầm trước khi sập nguồn toàn bộ
    if server_process is not None:
        print(">> Đang tiêu diệt Server ngầm trước khi thoát...")
        server_process.terminate()
    print(">> GUI CLOSED → STOP ALL PROGRAM")
    os._exit(0)

# ===== LỆNH ÉP NHẢ QUẢ TRÊN TAY =====
def action_nha_qua():
    print("\n>> [GUI] ĐÃ BẤM NÚT NHẢ QUẢ TRÊN TAY! Đang bắn gói tin UART...")
    try:
        from config_uart.sent_uart import build_packet, ser
        if ser is not None:
            if not ser.is_open:
                try: ser.open()
                except Exception: pass
            
            if ser.is_open:
                packet = build_packet(3, 3, 3, 3, 3)
                ser.write(packet)
                
                # 🔥 SOI MÃ HEX CỦA LỆNH NHẢ QUẢ
                hex_str = " ".join([f"{b:02X}" for b in packet])
                print(f">> [UART GUI] BÙM! NHẢ QUẢ: (3, 3, 3, 3, 3) | GÓI HEX: [{hex_str}]")
            else:
                print(">> [LỖI UART] Cổng chưa mở, đéo bắn được!")
    except Exception as e:
        print(f">> [LỖI UART] Gửi gói tin thất bại: {e}")
        import tkinter.messagebox as messagebox
        messagebox.showerror("Lỗi UART", f"Đéo bắn được gói tin nhả quả.\nLỗi: {e}")

# ===== GUI =====
def start_gui():
    root = tk.Tk()
    root.title("Robot Control Panel")
    # Thay đổi sang kích thước ngang để nhét đủ 3 cột (Tăng chiều cao lên 450)
    root.geometry("850x450") 
    root.resizable(False, False)
    root.configure(bg="#2b2b2b")

    root.protocol("WM_DELETE_WINDOW", on_close)

    # ----- TITLE -----
    tk.Label(
        root,
        text="ROBOT CONTROL",
        font=("Arial", 16, "bold"),
        fg="white",
        bg="#2b2b2b"
    ).pack(pady=(15, 5))

    # =========================================================
    # LẮP BẢNG LED BÁO TRẠNG THÁI
    # =========================================================
    status_label = tk.Label(
        root,
        text="🎧 HỆ THỐNG: ĐANG ĐỢI LỆNH (IDLE)...",
        font=("Arial", 12, "bold"),
        fg="#2ecc71", # Xanh lá
        bg="#1e293b",
        width=50, pady=8
    )
    status_label.pack(pady=(0, 10))

    def auto_update_status():
        try:
            current_state = set_state["value"]
            if current_state == STATE_IDLE:
                status_label.config(text="🎧 HỆ THỐNG: ĐANG ĐỢI LỆNH (IDLE)...", fg="#2ecc71")
            else:
                status_label.config(text=f"⚙️ HỆ THỐNG: ĐANG BẬN (MÃ TRẠNG THÁI: {current_state})", fg="#e74c3c")
        except:
            pass
        # Radar quét liên tục 200ms/lần
        root.after(200, auto_update_status)

    auto_update_status() # Khởi động Radar
    # =========================================================

    # Khung (Frame) chứa các nút xếp dạng lưới
    main_frame = tk.Frame(root, bg="#2b2b2b")
    main_frame.pack(pady=10)

    btn_cfg = {
        "width": 16, 
        "height": 2,
        "font": ("Arial", 7, "bold"),
        "bd": 0
    }

    # ================= CỘT 1, 2, 3 (HÀNG 1) =================
    tk.Button(
        main_frame, text="R1 DETECT",
        command=set_see_r1,
        bg="#c0392b", fg="white",
        **btn_cfg
    ).grid(row=0, column=0, padx=12, pady=12)

    tk.Button(
        main_frame, text="MATRIX DETECT",
        command=set_matrix,
        bg="#2980b9", fg="white",
        **btn_cfg
    ).grid(row=0, column=1, padx=12, pady=12)

    tk.Button(
        main_frame, text="FOREST DETECT",
        command=set_forest,
        bg="#27ae60", fg="white",
        **btn_cfg
    ).grid(row=0, column=2, padx=12, pady=12)

    # ================= CỘT 1, 2, 3 (HÀNG 2) =================
    tk.Button(
        main_frame, text="PICK BLOCK",
        command=set_pick_block,
        bg="#f39c12", fg="white",
        **btn_cfg
    ).grid(row=1, column=0, padx=12, pady=12)

    btn_server = tk.Button(
        main_frame, text="BẬT SERVER WEB",
        bg="#8e44ad", fg="white",
        **btn_cfg
    )
    btn_server.config(command=lambda: start_web_server(btn_server))
    btn_server.grid(row=1, column=1, padx=12, pady=12)

    tk.Button(
        main_frame, text="STOP / IDLE",
        command=set_idle,
        bg="#7f8c8d", fg="white",
        **btn_cfg
    ).grid(row=1, column=2, padx=12, pady=12)

    # Đường kẻ ngang chia cách phần chức năng mạng
    tk.Frame(main_frame, height=2, bg="#555555").grid(row=2, column=0, columnspan=3, sticky="ew", pady=(20, 20))

    # ================= HÀNG 3: NHẢ QUẢ VÀ BẬT WIFI =================
    
    # 1. NÚT NHẢ QUẢ (ĐẶT Ở CỘT BÊN TRÁI)
    btn_nha_qua = tk.Button(
        main_frame, text="⏬ NHẢ QUẢ",
        command=action_nha_qua,
        bg="#d35400", fg="white", # Màu cam đậm cháy phố
        **btn_cfg
    )
    btn_nha_qua.grid(row=3, column=0, padx=12, pady=5)

    # 2. NÚT WIFI (GIỮ NGUYÊN BẢN GỐC CỦA MÀY, Ở CỘT GIỮA)
    btn_hotspot = tk.Button(
        main_frame, text="📡 BẬT WIFI (VTV 5G)",
        bg="#e67e22", fg="white",
        **btn_cfg
    )
    btn_hotspot.config(command=lambda: turn_on_hotspot(btn_hotspot))
    # Chỉnh cột 1 (chính giữa) để nút nằm cân đối
    btn_hotspot.grid(row=3, column=1, padx=12, pady=5)

    # 3. NÚT CHECK R1 LẦN 2 (ĐẶT Ở CỘT BÊN PHẢI CÙNG CỦA HÀNG 3)
    tk.Button(
        main_frame, text="CHECK R1 L2",
        command=set_see_r1_l2,
        bg="#16a085", fg="white", # Màu xanh ngọc cho nó khác bọt
        **btn_cfg
    ).grid(row=3, column=2, padx=12, pady=5)

    root.mainloop()

# if __name__ == "__main__":
#     start_gui()