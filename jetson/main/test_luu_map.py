import customtkinter as ctk
import heapq
import itertools
import time
import pyrealsense2 as rs
import cv2
import numpy as np
import socketio      
import threading     
from pyzbar.pyzbar import decode
from tkinter import simpledialog, messagebox
from gui_tkinter import set_state, STATE_FOREST, STATE_IDLE 
from config_uart.sent_uart import build_packet, send_packet_once, ser
import socketio
import threading
SERVER_IP = "http://192.168.50.120:5000"
ctk.set_appearance_mode("System")
ctk.set_default_color_theme("blue")

ROWS = 4          # Số hàng sa bàn (không tính cửa)
COLS = 3
DOOR_ROW = ROWS   # Hàng cửa (row index = 4, phía dưới sa bàn)
CELL_SIZE = 250
width_cell = 90
height_cell = 90

class SelectPlaceApp:
    def __init__(self):
        self.root = ctk.CTk()
        self.root.title("Robot Pathfinding: Hybrid & UART Control")
        self.root.geometry("980x680")  # Đã nới rộng ra để chứa Tab cho đẹp

        self.team_color = "RED"  
        self.root.protocol("WM_DELETE_WINDOW", self.on_closing)

        self.last_received_grid = None  # Lưu mảng cũ để so sánh
        self.calc_session_id = 0        # Mã đánh dấu luồng tính toán

        # =====================================================================
        # 1. TẠO HỆ THỐNG TAB VIEW (GỘP RỪNG & MATRIX)
        # =====================================================================
        self.tabview = ctk.CTkTabview(self.root)
        self.tabview.pack(padx=10, pady=5, expand=True, fill="both")

        # Tạo 2 cái thẻ (Tab)
        self.tab_forest = self.tabview.add("🌲 Sa Bàn (Forest)")
        self.tab_matrix = self.tabview.add("🔢 Vùng 3 (Matrix)")

        # --- CỜ TRẠNG THÁI LẮNG NGHE ---
        self.is_listening = False
        try:
            # Ép tắt lắng nghe khi mới mở giao diện để đồng bộ với nút
            from uart_listener import uart_enable
            uart_enable["value"] = False
        except:
            pass

        # Nút Bật/Tắt Lắng Nghe (Gắn cố định góc phải)
        self.listen_btn = ctk.CTkButton(
            self.root, text="🎧 BẬT LẮNG NGHE (MAIN)", width=180, height=30,
            fg_color="#8e44ad", hover_color="#732d91", 
            command=self.toggle_main_listener # <--- Đổi tên hàm gọi
        )
        self.listen_btn.place(relx=0.98, rely=0.015, anchor="ne")

        # Gọi hàm setup Tab Matrix (Hàm này tao viết ở Bước 3)
        self.setup_matrix_tab()

        # =====================================================================
        # 2. KHỞI TẠO LƯỚI SA BÀN (NHÉT VÀO TAB FOREST)
        # =====================================================================
        # CHÚ Ý: Chữ self.root ở đây đã được đổi thành self.tab_forest
        self.main_frame = ctk.CTkFrame(self.tab_forest)
        self.main_frame.pack(padx=8, pady=5, expand=True, fill="both")

        # =====================================================================
        # KHỞI TẠO LƯỚI SA BÀN (ROWS hàng x COLS cột)
        # =====================================================================
        self.grid_cells = []
        for i in range(ROWS):
            row = []
            for j in range(COLS):
                cell_frame = ctk.CTkFrame(
                    self.main_frame,
                    width=CELL_SIZE,
                    height=CELL_SIZE,
                    border_width=2
                )
                cell_frame.grid(row=i, column=j*2, padx=3, pady=3)
                cell_frame.grid_propagate(False)

                block_buttons = []
                for k in range(3):
                    num = k + 1
                    if num == 1:
                        btn_text = "1"
                    elif num == 2:
                        btn_text = "2"
                    else:
                        btn_text = "Fake"
                        
                    btn = ctk.CTkButton(
                        cell_frame,
                        text=btn_text,
                        width=width_cell,
                        height=height_cell,
                        fg_color="gray75",       # Màu xám trung tính nhã nhặn
                        text_color="black",      # Chữ đen dễ đọc
                        hover_color="#a0a0a0",   # Hover xám đậm hơn tí
                        corner_radius=8,
                        font=("DejaVu Sans", 16, "bold"),
                        command=lambda n=num, pos=(i, j): self.place_block(n, pos)
                    )
                    btn.pack(side="left", expand=True, padx=2, pady=2)
                    block_buttons.append(btn)

                id_label = ctk.CTkLabel(
                    cell_frame, 
                    text="", 
                    width=24, 
                    height=24,
                    corner_radius=6,
                    font=("DejaVu Sans", 12, "bold")
                )
                id_label.place(relx=0.02, rely=0.02, anchor="nw")
                
                cell_frame.bind("<Button-1>", lambda e, pos=(i, j): self.cell_clicked(pos))
                cell_frame.bind("<Double-Button-1>", lambda e, pos=(i, j): self.cell_double_clicked(pos))
                row.append({
                    "frame": cell_frame,
                    "content": None,
                    "overlays": [],
                    "buttons": block_buttons,
                    "id_label": id_label,
                    "selected": False
                })
            self.grid_cells.append(row)

        # =====================================================================
        # ĐƯỜNG KẺ PHÂN CÁCH (Cột giữa các lane)
        # =====================================================================
        sep1 = ctk.CTkFrame(self.main_frame, width=2, fg_color="#d32f2f")
        sep1.grid(row=0, column=1, rowspan=ROWS+1, sticky="ns", pady=3)
        
        sep2 = ctk.CTkFrame(self.main_frame, width=2, fg_color="#d32f2f") 
        sep2.grid(row=0, column=3, rowspan=ROWS+1, sticky="ns", pady=3)

        # =====================================================================
        # HÀNG CỬA (DOOR_ROW) — 3 ô đặc biệt, không có nút đặt khối
        # =====================================================================
        self.door_cells = []
        door_labels = ["Cửa A\n(dưới ID 1)", "Cửa B\n(dưới ID 2)", "Cửa C\n(dưới ID 3)"]
        for j in range(COLS):
            door_frame = ctk.CTkFrame(
                self.main_frame,
                width=CELL_SIZE,
                height=40,          # Ô cửa nhỏ hơn
                border_width=2,
                fg_color="#1e3a5f"  # Màu xanh đậm để phân biệt
            )
            door_frame.grid(row=ROWS, column=j*2, padx=3, pady=(0, 3))
            door_frame.grid_propagate(False)

            door_label = ctk.CTkLabel(
                door_frame,
                text=door_labels[j],
                font=("DejaVu Sans", 13, "bold"),
                text_color="#7ec8e3",
                justify="center"
            )
            door_label.place(relx=0.5, rely=0.5, anchor="center")

            door_id_label = ctk.CTkLabel(
                door_frame,
                text=f"D{j+1}",
                width=28, height=20,
                corner_radius=4,
                font=("DejaVu Sans", 10, "bold"),
                fg_color="#3a6186",
                text_color="#ffffff"
            )
            door_id_label.place(relx=0.02, rely=0.05, anchor="nw")

            self.door_cells.append({
                "frame": door_frame,
                "col": j,
                "overlays": []
            })

        # =====================================================================
        # THANH CÔNG CỤ
        # =====================================================================
        self.bottom_frame = ctk.CTkFrame(self.tab_forest)
        self.bottom_frame.pack(side="bottom", padx=10, pady=5, fill="x")
      
        self.reset_btn = ctk.CTkButton(
            self.bottom_frame, text="Reset", width=80, height=70,
            fg_color="#d9534f", hover_color="#c9302c",
            command=self.reset_grid
        )
        self.reset_btn.pack(side="left", padx=3)

        self.team_btn = ctk.CTkButton(
            self.bottom_frame, text="Sân: ĐỎ (RED)", width=80, height=70,
            fg_color="#d32f2f", hover_color="#b71c1c",
            command=self.toggle_team
        )
        self.team_btn.pack(side="left", padx=3)

        self.mode_btn = ctk.CTkButton(
            self.bottom_frame, text="Mode: Normal", width=80, height=70,
            fg_color="#5bc0de", hover_color="#31b0d5",
            command=self.toggle_forest_mode
        )
        self.mode_btn.pack(side="left", padx=3)       

        # =====================================================================
        # ĐÈN LED BÁO KẾT NỐI SERVER (NHÁY XANH/ĐỎ) - CHUYỂN LÊN GÓC TRÊN
        # =====================================================================
        self.is_server_connected = False 
        self.led_on = True               
        
        # Đổi parent thành self.root (thay vì self.bottom_frame) để nó nổi lên trên cùng
        self.status_led = ctk.CTkLabel(
            self.root, text="● SERVER", font=("DejaVu Sans", 12, "bold"),
            text_color="gray", width=100
        )
        
        # Nút Lắng nghe đang ở relx=0.98. Tao đặt đèn ở relx=0.78 để nó đứng ngay sát bên trái nút
        self.status_led.place(relx=0.78, rely=0.015, anchor="ne")

        # Bắt đầu vòng lặp nháy đèn
        self.update_led_blink()
# --- NÚT TÌM ĐƯỜNG ---
# --- CỜ CHIẾN THUẬT MẶC ĐỊNH ---
        self.is_fast_attack = True  # True = Thắng Nhanh, False = Cày Điểm

        # --- NÚT CHIẾN THUẬT (THẮNG NHANH / CÀY ĐIỂM) ---
        self.run_btn = ctk.CTkButton(
            self.bottom_frame, text="TÌM ĐƯỜNG", width=80, height=70,
            fg_color="#5cb85c", hover_color="#449d44",
            command=self.smart_run
        )
        self.run_btn.pack(side="left", padx=3)

        self.info_label = ctk.CTkLabel(
            self.tab_forest,            text="Chế độ: Đặt khối.\nBấm 'TÌM ĐƯỜNG' để tìm đường, sau đó 'GỬI UART' để truyền.",
            width=250, height=50, wraplength=600, justify="left", font=("DejaVu Sans", 9)
        )
        self.send_uart_btn = ctk.CTkButton(self.bottom_frame, text="GỬI UART", width=80, height=70, fg_color="#9c27b0", hover_color="#7b1fa2", command=self.sent_and_close)
        self.send_uart_btn.pack(side="left", padx=3)

        self.strategy_btn = ctk.CTkButton(
            self.bottom_frame, text="🔥 THẮNG NHANH", width=80, height=70,
            fg_color="#f59e0b", hover_color="#d97706",
            command=self.toggle_strategy
        )
        self.strategy_btn.pack(side="left", padx=5)

        # --- CỜ TRẠNG THÁI & KHỞI TẠO KẾT NỐI SOCKET ---
        self.sync_mode = False  # MẶC ĐỊNH LÀ TẮT (Cho mày rảnh tay xếp hình)
        self.sio = socketio.Client() 
        self.connect_server_thread() 

        # --- NÚT TOGGLE LIVE (THAY THẾ NÚT QUÉT QR CŨ) ---
        self.toggle_sync_live_btn = ctk.CTkButton(
            self.bottom_frame, text="📡 BẬT NHẬN LIVE", width=80, height=70,
            fg_color="#00bcd4", hover_color="#0097a7",
            command=self.handle_sync_toggle
        )
        self.toggle_sync_live_btn.pack(side="left", padx=5)
    # --- CỜ & NÚT CHIẾN THUẬT ---



        self.info_label.pack(pady=3)
        self.mode = "PLACE" #
        self.active_button = None #
        self.selected_targets = [] #
        self.simulation_path = None #
        self.stop_qr = False #
        self.best_targets_set = None #
        self.best_ignored_set = [] #
        self.forest_mode = "normal" #
        self.refresh_grid_ids() #
        
        import os
        cache_ready = "normal" if os.path.exists("last_packet_cache.json") else "disabled" #

        self.replay_cache_btn = ctk.CTkButton(
            self.bottom_frame, text="PHÁT LẠI CACHE", width=80, height=70,
            fg_color="#00838f", hover_color="#006064",
            state=cache_ready,
            command=self.action_replay_cache #
        )
        self.replay_cache_btn.pack(side="left", padx=3)


    # =========================================================================
    # 📡 MODULE: SOCKET & LIVE MAP
    # =========================================================================
    def connect_server_thread(self):
        @self.sio.on('connect')
        def on_connect():
            self.is_server_connected = True
            print("[SOCKET] Kết nối Server thành công!")

        @self.sio.on('disconnect')
        def on_disconnect():
            self.is_server_connected = False
            print("[SOCKET] Mất kết nối Server!")

        @self.sio.on('connect_error')
        def on_error(data):
            self.is_server_connected = False

        @self.sio.on('sync_state')
        def on_sync_state(data):
            if self.sync_mode:
                new_grid = data.get('grid')
                
                if new_grid == self.last_received_grid:
                    return
                
                self.last_received_grid = new_grid
                
                self.calc_session_id += 1
                current_session = self.calc_session_id
                
                # SỬA DÒNG NÀY: Truyền explicitly current_session vào
                self.root.after(0, lambda s=current_session: self.apply_server_state(data, s))

        def attempt_connect():
            try:
                # Ép dùng websocket cho nhanh như anh em mình đã bàn
                self.sio.connect(SERVER_IP, transports=['websocket'])
            except Exception:
                self.is_server_connected = False

        threading.Thread(target=attempt_connect, daemon=True).start()      
    def apply_server_state(self, state, session_id):
        # --- CHỐT CHẶN: GIẾT LUỒNG CŨ ---
        if session_id != self.calc_session_id:
            return # Khai tử ngay để nhường chỗ cho mảng mới nhất

        team_server = state.get("team", "R")
        grid_data = state.get("grid", [])

        # --- BỘ LỌC CHỐNG SPAM ---
        if hasattr(self, 'last_team') and self.last_team == team_server:
            if hasattr(self, 'last_grid_data') and self.last_grid_data == grid_data:
                return  # Đéo có gì mới thì nghỉ!

        self.last_team = team_server
        self.last_grid_data = grid_data

        # Đổi sân
        if team_server == 'R' and self.team_color != "RED":
            self.toggle_team()
        elif team_server == 'B' and self.team_color != "BLUE":
            self.toggle_team()

        # ==========================================================
        # CẬP NHẬT CỤC BỘ (CHỈ VẼ LẠI Ô BỊ THAY ĐỔI)
        # ==========================================================
        for r in range(min(ROWS, len(grid_data))):
            for c in range(min(COLS, len(grid_data[r]))):
                new_val = grid_data[r][c]
                cell = self.grid_cells[r][c]
                
                # Kiểm tra xem ô hiện tại đang chứa khối số mấy (0 là trống)
                current_val = cell["content"]["number"] if cell["content"] else 0
                
                # NẾU GIỐNG HỆT NHAU -> BỎ QUA KHÔNG VẼ LẠI CHO ĐỠ LAG!
                if current_val == new_val:
                    continue
                    
                # NẾU CÓ THAY ĐỔI -> Xóa khối cũ đi trước
                if cell["content"]:
                    cell["content"]["widget"].destroy()
                    cell["content"] = None
                    for btn in cell["buttons"]:
                        btn.pack(side="left", expand=True, padx=2, pady=2)
                    cell["id_label"].lift()
                
                # Rồi đặt khối mới vào
                if new_val in [1, 2, 3]:
                    self.place_block(new_val, (r, c))
        # ==========================================================
                    
        self.info_label.configure(text=f"✓ Nhận MAP LIVE siêu tốc! (Sân {team_server}). Đang tự động tìm đường...", text_color="green")

        # ==============================================================
        # KÍCH HOẠT TỰ ĐỘNG TÌM ĐƯỜNG NGAY KHI CÓ DATA TỪ SERVER
        # ==============================================================
        self.smart_run()

    def toggle_sync_qr(self):
        # Chuyển sang chế độ Quét QR (Tắt Live)
        self.sync_mode = False
        self.toggle_sync_qr_btn.configure(text="📸 ĐANG QUÉT QR", fg_color="#f39c12", hover_color="#d68910")
        self.root.update()
        
        self.open_qr_scanner() # Mở Camera quét QR
        
        # Sau khi xong, tự động quay lại nhận Live
        self.sync_mode = True
        self.toggle_sync_qr_btn.configure(text="📡 ĐANG NHẬN LIVE", fg_color="#00bcd4", hover_color="#0097a7")    
    def handle_sync_toggle(self):
        # Đảo trạng thái cờ
        self.sync_mode = not self.sync_mode
        
        if self.sync_mode:
            # ==============================================================
            # BÍ QUYẾT ĐÂY: Xóa cmn trí nhớ cũ đi để ép nó vẽ lại ngay lập tức!
            # ==============================================================
            if hasattr(self, 'last_grid_data'):
                self.last_grid_data = None 
                
            self.toggle_sync_live_btn.configure(
                text="📡 ĐANG NHẬN LIVE", 
                fg_color="#27ae60", hover_color="#219150" # Màu xanh lá
            )
            self.info_label.configure(text="ĐÃ BẬT LIVE: Đang nhận dữ liệu từ Camera...", text_color="green")
        else:
            self.toggle_sync_live_btn.configure(
                text="📡 BẬT NHẬN LIVE", 
                fg_color="#00bcd4", hover_color="#0097a7" # Màu xanh lơ
            )
            self.info_label.configure(text="ĐÃ TẮT LIVE: Đang ở chế độ xếp tay.", text_color="black")
        self.root.update()
    # =========================================================================
    # HELPER: Lấy ID cửa (Door row) theo cột
    # =========================================================================
    def get_door_id(self, col):
        return -(col + 1)  # Cửa A=-1, B=-2, C=-3

    def is_door_pos(self, r, c):
        return r == DOOR_ROW and 0 <= c < COLS

    # =========================================================================
    # TOGGLE FOREST MODE
    # =========================================================================
    def toggle_forest_mode(self):
        if self.forest_mode == "normal":
            self.forest_mode = "retry2"
            self.mode_btn.configure(text="Mode: Retry2", fg_color="#f39c12", hover_color="#d68910")
            self.info_label.configure(text="Chuyển sang Mode: Retry2")
        else:
            self.forest_mode = "normal"
            self.mode_btn.configure(text="Mode: Normal", fg_color="#5bc0de", hover_color="#31b0d5")
            self.info_label.configure(text="Chuyển sang Mode: Normal")
        print(f">> Forest Mode: {self.forest_mode.upper()}")
# =========================================================================
    # ĐỔI CHIẾN THUẬT (CHỈ LƯU TRẠNG THÁI VÀ ĐỔI UI, KHÔNG GỬI MẠCH)
    # =========================================================================
    def toggle_strategy(self):
        self.is_fast_attack = not self.is_fast_attack
        
        if self.is_fast_attack:
            self.strategy_btn.configure(
                text="🔥 THẮNG NHANH", 
                fg_color="#f59e0b", 
                hover_color="#d97706"
            )
            self.info_label.configure(text="Đã gài chiến thuật: THẮNG NHANH. Bấm 'GỬI UART' để chốt lệnh.", text_color="#d97706")
        else:
            self.strategy_btn.configure(
                text="🎯 CÀY ĐIỂM", 
                fg_color="#8b5cf6", 
                hover_color="#7c3aed"
            )
            self.info_label.configure(text="Đã gài chiến thuật: CÀY ĐIỂM. Bấm 'GỬI UART' để chốt lệnh.", text_color="#8b5cf6")
    # =========================================================================
    # TOGGLE TEAM & REFRESH
    # =========================================================================
    def toggle_team(self):
        if self.team_color == "RED":
            self.team_color = "BLUE"
            self.team_btn.configure(text="Sân: XANH (BLUE)", fg_color="#1e88e5", hover_color="#1565c0")
        else:
            self.team_color = "RED"
            self.team_btn.configure(text="Sân: ĐỎ (RED)", fg_color="#d32f2f", hover_color="#b71c1c")
        
        self.refresh_grid_ids()
        self.info_label.configure(text=f"Đã chuyển sang sân {self.team_color}. ID các ô đã được cập nhật.")
        self.simulation_path = None 
        for r in range(ROWS):
            for c in range(COLS):
                for ov in self.grid_cells[r][c]["overlays"]: ov.destroy()
                self.grid_cells[r][c]["overlays"].clear()

    def refresh_grid_ids(self):
        for r in range(ROWS):
            for c in range(COLS):
                cell_id = self.get_cell_id(r, c)
                is_finish = cell_id in [10, 11, 12]
                is_entry = cell_id in [1, 2, 3]
                
                if is_finish:
                    id_bg_color = "#ffeb3b"
                    id_text_color = "#d32f2f"
                elif is_entry:
                    id_bg_color = "#ff9800"
                    id_text_color = "#ffffff"
                else:
                    id_bg_color = "#dddddd"
                    id_text_color = "#555555"
                
                lbl = self.grid_cells[r][c]["id_label"]
                lbl.configure(
                    text=f"ID:{cell_id}" if is_finish else str(cell_id),
                    text_color=id_text_color,
                    fg_color=id_bg_color,
                    width=24 if not is_finish else 45
                )

    def get_cell_id(self, r, c):
        row_factor = (ROWS - 1 - r) * COLS 
        if self.team_color == "RED":
            col_offset = (COLS - 1 - c)
        else:
            col_offset = c
        return row_factor + col_offset + 1

    def on_closing(self):
        print(">> Closing Forest App...")
        set_state["value"] = STATE_IDLE
        print("Đã quay về trạng thái IDLE.")
        self.root.quit()
        self.root.destroy()

    def sent_and_close(self):
        print(f"\n>> FOREST MODE: {self.forest_mode.upper()} - Gửi gói tin...")
        
        if self.forest_mode == "normal":
            print(">> Mode: Normal - Gửi packet (2, 10, 1, 1, 1)")
            packet = build_packet(2, 10, 1, 1, 1)
        else:
            print(">> Mode: Retry2 - Gửi packet (2, 10, 2, 2, 2)")
            packet = build_packet(2, 10, 2, 2, 2)
        
        try:
            send_packet_once(ser, packet)
            print("[FOREST] Gửi packet mode thành công")
        except Exception as e:
            print(f"[FOREST] Lỗi gửi packet: {e}")
        
        self.send_uart()
        print(">> Đã truyền UART thành công!")
        self.info_label.configure(text="✓ Đã gửi UART thành công! Bạn có thể đóng cửa sổ bằng nút X.")

    # =========================================================================
    # UI: TOGGLE MODE, CELL CLICK, PLACE BLOCK, RESET
    # =========================================================================
    def toggle_mode(self, new_mode, button):
        if self.mode == new_mode:
            self.mode = "PLACE"
            if self.active_button:
                self.active_button.configure(fg_color=self.active_button.default_color)
            self.active_button = None
            self.info_label.configure(text="Trở lại chế độ Đặt khối.")
        else:
            self.mode = new_mode
            if self.active_button:
                self.active_button.configure(fg_color=self.active_button.default_color)
            self.active_button = button
            button.default_color = button.cget("fg_color")
            button.configure(fg_color="yellow")
            
            if new_mode == "DELETE":
                self.info_label.configure(text="Chế độ XÓA: Click vào nút số hoặc ô để xóa.")
            elif new_mode == "SELECT":
                self.info_label.configure(text="Chế độ CHỌN: Click vào ô để chọn làm mục tiêu.")

    def cell_clicked(self, position):
        r, c = position
        cell = self.grid_cells[r][c]

        # 1. NẾU ĐANG Ở CHẾ ĐỘ XÓA (Bật nút Xóa màu cam)
        if self.mode == "DELETE":
            if cell["content"]:
                cell["content"]["widget"].destroy()
                cell["content"] = None
                for btn in cell["buttons"]:
                    btn.pack(side="left", expand=True, padx=2, pady=2)
                cell["id_label"].lift()
                self.info_label.configure(text=f"Đã xóa tại ({r},{c})")
                
                # THÊM DÒNG NÀY
                if getattr(self, 'auto_update_path', False):
                    self.smart_run()
            return

        # 2. NẾU ĐANG VẼ ĐƯỜNG MÀ CLICK LẠI VÀO Ô ĐÃ CHỌN -> XÓA NHANH ĐƯỜNG ĐÓ
        elif self.mode == "SELECT":
            if cell["selected"]:
                cell["frame"].configure(fg_color="transparent")
                cell["selected"] = False
                if position in self.selected_targets:
                    self.selected_targets.remove(position)
                for ov in cell["overlays"]:
                    ov.destroy()
                cell["overlays"].clear()
                self.info_label.configure(text=f"Đã BỎ CHỌN đường tại ({r},{c})")
                return

            if self.selected_targets:
                last_r, last_c = self.selected_targets[-1]
                dist = abs(r - last_r) + abs(c - last_c)
                if dist != 1:
                    self.info_label.configure(text=f"LỖI: Ô ({r},{c}) không nằm cạnh ô trước đó!", text_color="red")
                    return

            self.selected_targets.append((r, c))
            cell["selected"] = True
            cell["frame"].configure(fg_color="#4caf50")
            
            step_idx = len(self.selected_targets) - 1
            lbl_step = ctk.CTkLabel(
                cell["frame"], text=str(step_idx),
                width=28, height=28, fg_color="#444444", text_color="white",
                corner_radius=14, font=("DejaVu Sans", 12, "bold")
            )
            lbl_step.place(relx=0.85, rely=0.85, anchor="center")
            cell["overlays"].append(lbl_step)
            self.info_label.configure(text=f"Bước {step_idx}: Đã chọn ({r},{c}). Tiếp tục...", text_color="black")
            return

        # 3. NẾU Ở CHẾ ĐỘ BÌNH THƯỜNG MÀ CLICK VÀO KHỐI TO -> BỐC HƠI NHANH
        if cell["content"]:
            cell["content"]["widget"].destroy()
            cell["content"] = None
            # Trả lại 3 nút xám nhỏ
            for btn in cell["buttons"]:
                btn.pack(side="left", expand=True, padx=2, pady=2)
            cell["id_label"].lift()
            self.info_label.configure(text=f"Đã XÓA nhanh khối tại ({r},{c}) bằng 1 Click")
            if getattr(self, 'auto_update_path', False):
                self.smart_run()
            
    def place_block(self, number, position):
        r, c = position
        cell = self.grid_cells[r][c]
        if self.mode == "DELETE":
            self.cell_clicked(position)
            return
        if self.mode == "SELECT":
            self.cell_clicked(position)
            return
        if cell["content"]:
            self.info_label.configure(text="Ô đã có khối, hãy xóa trước.")
            return

        # --- GÁN MÀU VÀ TÊN LÊN GIAO DIỆN THEO ĐÚNG Ý ANH ---
        if number == 1:
            bg_color = "#3498db"  # Xanh da trời
            txt_color = "white"
            display_text = "1"
        elif number == 2:
            bg_color = "#f1c40f"  # Vàng
            txt_color = "black"
            display_text = "2"
        elif number == 3:
            bg_color = "#e74c3c"  # Đỏ đỏ
            txt_color = "white"
            display_text = "Fake"
        else:
            bg_color = "#79b8ff"
            txt_color = "black"
            display_text = str(number)

        new_label = ctk.CTkLabel(
            cell["frame"], text=display_text, text_color=txt_color,
            width=90, height=90, fg_color=bg_color,
            corner_radius=12, font=("DejaVu Sans", 22, "bold")
        )
        new_label.place(relx=0.5, rely=0.5, anchor="center")
        new_label.bind("<Button-1>", lambda e, pos=position: self.cell_clicked(pos))        # Vẫn giữ nguyên logic lưu data là `number` (1,2,3) để thuật toán chạy đúng!
        cell["content"] = {"widget": new_label, "number": number}
        
        for btn in cell["buttons"]:
            btn.pack_forget()
            
        cell["id_label"].lift()
        self.info_label.configure(text=f"Đặt khối {display_text} tại ({r},{c})")
        if getattr(self, 'auto_update_path', False):
            self.smart_run()

    def reset_grid(self):
        for r in range(ROWS):
            for c in range(COLS):
                cell = self.grid_cells[r][c]
                if cell["content"]:
                    cell["content"]["widget"].destroy()
                    cell["content"] = None
                for ov in cell["overlays"]:
                    ov.destroy()
                cell["overlays"].clear()
                cell["selected"] = False
                cell["frame"].configure(fg_color="transparent")
                for btn in cell["buttons"]:
                    btn.pack(side="left", expand=True, padx=5, pady=5)
                cell["id_label"].lift()
        
        for door in self.door_cells:
            for ov in door["overlays"]:
                ov.destroy()
            door["overlays"].clear()

        self.mode = "PLACE"
        self.selected_targets.clear()
        if self.active_button:
            self.active_button.configure(fg_color=self.active_button.default_color)
            self.active_button = None
        self.info_label.configure(text="Lưới đã reset. Mời chọn lại chế độ.")
        self.auto_update_path = False
        
        # =======================================================
        # BƠM THÊM ĐOẠN NÀY ĐỂ TẨY NÃO, CHỐNG BỆNH "ĐIẾC" MAP
        # =======================================================
        self.last_received_grid = None
        if hasattr(self, 'last_grid_data'):
            self.last_grid_data = None
        self.calc_session_id += 1 # Hủy luôn các tính toán tìm đường đang chạy dở
    # =========================================================================
    # ENGINE: PATHFINDING
    # =========================================================================
    def check_traversable_rules(self, r, c, virtual_grid=None, target_pos=None):
        if not (0 <= r < ROWS and 0 <= c < COLS): return False
        
        if target_pos and (r, c) == target_pos:
            if r == 3 or r == 0: return True
            
        if virtual_grid:
            status = virtual_grid[r][c]
            if status == "EMPTY" or status == "IGNORED": return True
            
        cell = self.grid_cells[r][c]
        if cell["content"] and cell["content"]["number"] == 3: return False
        if cell["content"] and cell["content"]["number"] == 2: return False
        return True

    def get_access_points(self, target_pos, virtual_grid=None):
        r, c = target_pos
        points = []
        
        if r == 3 or r == 0:
            if self.check_traversable_rules(r, c, virtual_grid, target_pos=target_pos):
                points.append((r, c))
        elif self.check_traversable_rules(r, c, virtual_grid):
            points.append((r, c))

        dirs = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        for dr, dc in dirs:
            nr, nc = r + dr, c + dc
            if self.check_traversable_rules(nr, nc, virtual_grid):
                points.append((nr, nc))
                
        return points
    
    def neighbors(self, pos, direction, virtual_grid=None, target_pos=None):
        r, c = pos
        dirs = [(-1,0),(0,-1),(0,1),(1,0)]
        for ndir, (dr, dc) in enumerate(dirs):
            nr, nc = r+dr, c+dc
            if self.check_traversable_rules(nr, nc, virtual_grid, target_pos):
                priority = 0 if (direction == -1 or ndir == direction) else 500
                yield (nr, nc, ndir, priority)

    def is_adjacent(self, pos1, pos2):
        return abs(pos1[0] - pos2[0]) + abs(pos1[1] - pos2[1]) == 1

    def h_score(self, current, target):
        return abs(current[0] - target[0]) + abs(current[1] - target[1])

    def min_h_score(self, pos, targets):
        if not targets: return 0
        return min(self.h_score(pos, target) for target in targets)

    def cost(self, r, c, virtual_grid=None):
        if not (0 <= r < ROWS and 0 <= c < COLS): return float('inf')
        cell = self.grid_cells[r][c]
        if cell["content"] and cell["content"]["number"] == 1:
            return 2  
        if cell["content"] and cell["content"]["number"] == 3:
            return float('inf')
        return 2  

    def dijkstra_astar(self, starts, targets, use_arm=False, virtual_grid=None):
        g_score = [[float("inf")]*COLS for _ in range(ROWS)]
        parent = [[None]*COLS for _ in range(ROWS)]
        pq = []
        goal_map = {} 
        
        specific_target = targets[0] if targets and len(targets) == 1 else None

        if use_arm:
            for t in targets:
                aps = self.get_access_points(t, virtual_grid)
                for p in aps:
                    if p not in goal_map: goal_map[p] = t
        else:
            for t in targets: goal_map[t] = t 
            
        if not goal_map: return None, None
        
        for start in starts:
            r, c = start
            g_score[r][c] = 0
            heapq.heappush(pq, (0, 0, -1, start))  
            
        found_node = None
        picked_target = None
        
        while pq:
            f, g, direction, cur = heapq.heappop(pq)
            r, c = cur
            if g > g_score[r][c]: continue
            if cur in goal_map:
                found_node = cur
                picked_target = goal_map[cur]
                break
            
            for nr, nc, ndir, priority in self.neighbors(cur, direction, virtual_grid, target_pos=specific_target):
                move_cost = self.cost(nr, nc, virtual_grid)
                turn_cost = 0.5 if priority > 0 else 0
                tentative_g = g + move_cost + turn_cost
                if tentative_g < g_score[nr][nc]:
                    parent[nr][nc] = cur
                    g_score[nr][nc] = tentative_g
                    h = self.min_h_score((nr, nc), list(goal_map.keys()))
                    heapq.heappush(pq, (tentative_g + h + priority, tentative_g, ndir, (nr, nc)))
                    
        if not found_node: return None, None
        path = []
        p = found_node
        while p is not None:
            path.append(p)
            p = parent[p[0]][p[1]]
        path.reverse()
        return path, picked_target

    def simulate_sequence(self, start_candidates, ordered_targets, ignored_blocks):
        virtual_grid = [[None]*COLS for _ in range(ROWS)]
        for r, c in ignored_blocks:
            virtual_grid[r][c] = "IGNORED"
            
        full_simulation_path = []
        total_steps = 0
        current_starts = start_candidates
        last_target_pos = None
        combo_bonus = 0
        
        for idx, target in enumerate(ordered_targets):
            if last_target_pos and self.is_adjacent(last_target_pos, target):
                combo_bonus += 5 
            path, picked = self.dijkstra_astar(current_starts, [target], use_arm=True, virtual_grid=virtual_grid)
            if not path: return float('inf'), []
            segment_cost = 0
            for r, c in path:
                segment_cost += self.cost(r, c, virtual_grid)
            total_steps += segment_cost
            full_simulation_path.append((path, picked))
            last_pos = path[-1]
            last_target_pos = picked
            current_starts = [last_pos]
            tr, tc = picked
            virtual_grid[tr][tc] = "EMPTY"
            
        final_goals = [(0, c) for c in range(COLS)] 
        for c in range(COLS):
            virtual_grid[0][c] = "EMPTY"

        path_home, _ = self.dijkstra_astar(current_starts, final_goals, use_arm=False, virtual_grid=virtual_grid)
        
        if not path_home: return float('inf'), []
        for r, c in path_home:
            total_steps += self.cost(r, c, virtual_grid)
        full_simulation_path.append((path_home, "FINISH"))
        final_score = total_steps - combo_bonus
        return final_score, full_simulation_path

    def send_uart(self):
        if not self.simulation_path:
            self.info_label.configure(text="Chưa có đường đi. Hãy tìm đường trước.")
            return
        try:
            import json
            current_blocks = []
            for r in range(ROWS):
                for c in range(COLS):
                    content = self.grid_cells[r][c]["content"]
                    if content:
                        # Lưu: [hàng, cột, loại_khối]
                        current_blocks.append([r, c, content["number"]])

            cache_data = {
                "team_color": self.team_color,
                "blocks": current_blocks,      # Lưu danh sách khối
                "path": self.simulation_path,   # Lưu bản vẽ đường đi
                "ignored": getattr(self, 'best_ignored_set', [])
            }
            
            with open("map_cache_ui.json", "w") as f:
                json.dump(cache_data, f)
            
            if hasattr(self, 'replay_cache_btn'):
                self.replay_cache_btn.configure(state="normal")
        except Exception as e:
            print(f"Lỗi lưu cache: {e}")

        # --- 2. GỬI UART NHƯ BÌNH THƯỜNG ---
        self.info_label.configure(text=f"Đang gửi UART (Sân {self.team_color})...")
        self.process_and_send_uart(self.simulation_path)
# =====================================================================
# LƯU FILE VÀ MỞ KHÓA NÚT PHÁT LẠI
# =====================================================================
        try:
            import json
            with open("last_packet_cache.json", "w") as f:
                json.dump(self.packets_cache, f)
            print(f"\n[CACHE] Đã lưu cứng {len(self.packets_cache)} gói tin vào Local!")
            
            # Mở khóa cho phép nhấn nút Phát Lại
            if hasattr(self, 'replay_cache_btn'):
                self.replay_cache_btn.configure(state="normal")
                
        except Exception as e:
            print(f"\n[CACHE ERROR] Không thể lưu file cache: {e}")
        # =====================================================================
    # =========================================================================
    # SMART RUN
    # =========================================================================
    def smart_run(self):
        # THÊM DÒNG NÀY ĐỂ BẬT TÍNH NĂNG TỰ ĐỘNG CẬP NHẬT
        self.auto_update_path = True 

        for r in range(ROWS):
            for c in range(COLS):
                for ov in self.grid_cells[r][c]["overlays"]: ov.destroy()
                self.grid_cells[r][c]["overlays"].clear()

        if self.selected_targets:
            print("\n>>> CHẾ ĐỘ THỦ CÔNG (MANUAL) <<<")
            self.solve_manual_targets()
        else:
            print("\n>>> CHẾ ĐỘ TỰ ĐỘNG (AUTO) <<<")
            self.solve_auto_targets()

    def solve_auto_targets(self):
        list_1s = []
        list_2s = []
        list_2s_at_entry = []   
        list_2s_on_board = []   

        for r in range(ROWS):
            for c in range(COLS):
                content = self.grid_cells[r][c]["content"]
                if content:
                    if content["number"] == 1:
                        list_1s.append((r, c))
                    elif content["number"] == 2:
                        list_2s.append((r, c))
                        if r == ROWS - 1:
                            list_2s_at_entry.append((r, c))
                        else:
                            list_2s_on_board.append((r, c))

        if not list_2s:
            self.info_label.configure(text="Lỗi: Không có khối số 2 nào trên sân.")
            return

        print(f">>> Khối 2: {len(list_2s_at_entry)} tại bục ID1-3, {len(list_2s_on_board)} trên sa bàn")

        # --- 1. TÌM CỘT ĐI THẲNG TỐT NHẤT ---
        best_col = -1
        max_score = -1
        for c in range(COLS):
            # Kiểm tra Khối 3 chặn
            is_blocked = any(
                self.grid_cells[r][c]["content"] and self.grid_cells[r][c]["content"]["number"] == 3
                for r in range(ROWS)
            )
            if is_blocked:
                continue

            # Kiểm tra R1: Cấm đi nếu cột có từ 2 cục R1 trở lên
            r1_count = sum(
                1 for r in range(ROWS)
                if self.grid_cells[r][c]["content"] and self.grid_cells[r][c]["content"]["number"] == 1
            )
            if r1_count >= 2:
                continue

            # Tính điểm: Tổng R2 có thể gắp trên cột này và 2 cột kế bên
            score = sum(
                1 for r in range(ROWS) for dc in [0, -1, 1]
                if 0 <= c + dc < COLS and (r, c + dc) in list_2s
            )
            
            # =========================================================
            # LOGIC CHỌN CỘT & ƯU TIÊN SÂN ĐẤU KHI BẰNG ĐIỂM
            # =========================================================
            if score > max_score:
                max_score = score
                best_col = c
            elif score == max_score and best_col != -1:
                # Điểm bằng nhau -> Phân xử theo màu sân
                if self.team_color == "RED":
                    # ĐỎ ưu tiên cột C (Index lớn nhất)
                    if c > best_col:
                        best_col = c
                elif self.team_color == "BLUE":
                    # XANH ưu tiên cột A (Index nhỏ nhất) -> Không làm gì cả vì best_col cũ đã nhỏ hơn rồi
                    pass 
            # =========================================================

        if best_col == -1:
            self.info_label.configure(text="LỖI: Tất cả các cột đều bị chặn (Bởi Khối 3 hoặc có >= 2 Khối 1).")
            return

        print(f">>> Chọn cột đi thẳng: {best_col} (Max score: {max_score}, Team: {self.team_color})")

        # --- 2. XÂY DỰNG SIM_PATH ---
        sim_path = []
        remaining_entry = list(list_2s_at_entry)

        # =========================================================================
        # LUẬT CỬA BỤC: BẮT BUỘC CHỈ LẤY 1 CỤC DUY NHẤT RỒI LÊN RỪNG
        # =========================================================================
        if remaining_entry:
            # Lấy cục R2 nằm gần cột best_col nhất
            best_entry = min(remaining_entry, key=lambda x: abs(x[1] - best_col))
            ordered_entry = [best_entry] # Ép mảng chỉ còn 1 mục tiêu
            door_start_col = ordered_entry[0][1]
            print(f">>> Luật gắp bục: CHỈ CHỐT GẮP 1 CỤC tại {best_entry}")
            
            # Đẩy các cục không được gắp ở bục vào list trên rừng
            # Để khi xe leo lên sa bàn nó tự động thò tay sang gắp
            for entry in remaining_entry:
                if entry != best_entry:
                    list_2s_on_board.append(entry)
        else:
            ordered_entry = []
            door_start_col = best_col
        # =========================================================================

        current_door_col = door_start_col

        # --- 2a. Các segment gắp khối ở bục (từ cửa, không leo) ---
        for target in ordered_entry:
            target_col = target[1]

            door_path = [(DOOR_ROW, current_door_col)]
            c = current_door_col
            while c != target_col:
                c += 1 if target_col > c else -1
                door_path.append((DOOR_ROW, c))

            sim_path.append((door_path, target))
            current_door_col = target_col

        # --- 2b. Segment leo lên sa bàn (Lên rừng) ---
        climb_door_path = [(DOOR_ROW, current_door_col)]
        c = current_door_col
        while c != best_col:
            c += 1 if best_col > c else -1
            climb_door_path.append((DOOR_ROW, c))
        # Leo lên ô đầu tiên của sa bàn
        climb_door_path.append((ROWS - 1, best_col))

        # --- 2c. Đường đi thẳng trên sa bàn & thò tay gắp ---
        board_entry = (ROWS - 1, best_col)
        board_accumulated = [board_entry] 

        for r in range(ROWS - 1, -1, -1):
            if r < ROWS - 1:
                board_accumulated.append((r, best_col))

            # Nếu có R2 nằm ngay trên cột đang đi
            if (r, best_col) in list_2s_on_board:
                if not any(a not in ("FINISH",) and isinstance(a, tuple) and a[0] < ROWS - 1
                           for _, a in sim_path):
                    full_seg = climb_door_path + board_accumulated[1:]
                else:
                    full_seg = list(board_accumulated)

                sim_path.append((full_seg, (r, best_col)))
                board_accumulated = [(r, best_col)]
                climb_door_path = [] 

            # Quét tay sang gắp ở cột trái hoặc cột phải
            for dc in [-1, 1]:
                c_adj = best_col + dc
                if 0 <= c_adj < COLS and (r, c_adj) in list_2s_on_board:
                    if not any(a not in ("FINISH",) and isinstance(a, tuple) and a[0] < ROWS - 1
                               for _, a in sim_path):
                        full_seg = climb_door_path + board_accumulated[1:]
                    else:
                        full_seg = list(board_accumulated)

                    sim_path.append((full_seg, (r, c_adj)))
                    board_accumulated = [(r, best_col)]
                    climb_door_path = []

        # Đi nốt quãng đường còn lại về đích
        while board_accumulated[-1][0] > 0:
            board_accumulated.append((board_accumulated[-1][0] - 1, best_col))

        if climb_door_path:
            finish_seg = climb_door_path + board_accumulated[1:]
        else:
            finish_seg = list(board_accumulated)

        sim_path.append((finish_seg, "FINISH"))

        # --- 3. LƯU KẾT QUẢ ---
        self.simulation_path = sim_path
        self.best_ignored_set = []
        self._best_col = best_col

        picked_ids = [self.get_cell_id(*a) for _, a in sim_path
                      if isinstance(a, tuple) and 0 <= a[0] < ROWS]
        entry_ids = [self.get_cell_id(*p) for p in ordered_entry]

        print(f"-> Gắp bục: {entry_ids} | Gắp sa bàn: {[i for i in picked_ids if i not in entry_ids]}")
        print(f"-> Segments: {len(sim_path)}")
        for i, (seg, act) in enumerate(sim_path):
            print(f"   [{i}] path={seg} action={act}")

        self.visualize_result(sim_path, [])
        self.info_label.configure(
            text=f"AUTO: Gắp bục {entry_ids} → Cột {best_col} → Gắp {picked_ids}. Sẵn sàng UART."
        )

    def solve_manual_targets(self):
        pass

    # =========================================================================
    # VISUALIZE
    # =========================================================================
    def visualize_result(self, simulation_path, ignored_blocks):
        # =====================================================================
        # 1. VẼ CÁC Ô BỊ BỎ QUA (IGNORED)
        # =====================================================================
        for r, c in ignored_blocks:
            lbl = ctk.CTkLabel(self.grid_cells[r][c]["frame"], text="BỎ",
                               width=30, height=30, fg_color="#7f8c8d", text_color="white",
                               corner_radius=15, font=("DejaVu Sans", 12, "bold"))
            lbl.place(relx=0.5, rely=0.5, anchor="center")
            self.grid_cells[r][c]["overlays"].append(lbl)

        # =====================================================================
        # 2. VẼ KÝ HIỆU VÀO CỬA (DOOR)
        # =====================================================================
        start_door_col = None
        door_movements = {}
        
        for seg_idx, (segment_path, segment_action) in enumerate(simulation_path):
            if segment_path and segment_path[0][0] == DOOR_ROW:
                if start_door_col is None:
                    start_door_col = segment_path[0][1]
                
                if len(segment_path) > 1:
                    for i in range(len(segment_path) - 1):
                        curr_r, curr_c = segment_path[i]
                        next_r, next_c = segment_path[i + 1]
                        if curr_r == DOOR_ROW and next_r == DOOR_ROW:
                            direction = "→" if next_c > curr_c else "←"
                            door_movements[next_c] = direction
        
        for col in range(COLS):
            door = self.door_cells[col]
            if col == start_door_col:
                lbl_start = ctk.CTkLabel(door["frame"], text="★ START",
                                        font=("DejaVu Sans", 12, "bold"),
                                        text_color="#00ff88", fg_color="transparent")
                lbl_start.place(relx=0.5, rely=0.25, anchor="center")
                door["overlays"].append(lbl_start)
            
            if col in door_movements:
                lbl_dir = ctk.CTkLabel(door["frame"], text=door_movements[col],
                                      font=("DejaVu Sans", 16, "bold"),
                                      text_color="#ffaa00", fg_color="transparent")
                lbl_dir.place(relx=0.5, rely=0.65, anchor="center")
                door["overlays"].append(lbl_dir)
        
        # =====================================================================
        # 3. LỌC ĐƯỜNG ĐI TRÊN SA BÀN VÀ ĐÁNH DẤU GẮP
        # =====================================================================
        full_path_display = []
        step_counter = 0

        for segment_path, segment_action in simulation_path:
            if segment_action == "FINISH":
                ext = segment_path[1:] if full_path_display else segment_path
                full_path_display.extend(ext)
            elif isinstance(segment_action, tuple):
                pr, pc = segment_action
                robot_pos = segment_path[-1]
                lr, lc = robot_pos

                # CHỮ "GẮP" ĐẶT Ở GÓC TRÊN BÊN PHẢI (Top-Right)
                if 0 <= pr < ROWS and 0 <= pc < COLS:
                    lbl_picked = ctk.CTkLabel(self.grid_cells[pr][pc]["frame"], text="GẮP",
                                       width=36, height=24, fg_color="#e74c3c", text_color="white",
                                       corner_radius=6, font=("DejaVu Sans", 10, "bold"))
                    lbl_picked.place(relx=0.82, rely=0.15, anchor="center")
                    self.grid_cells[pr][pc]["overlays"].append(lbl_picked)

                step_counter += 1
                ext = segment_path[1:] if full_path_display else segment_path
                full_path_display.extend(ext)

        # =====================================================================
        # 4. ĐÁNH SỐ BƯỚC ĐI VÀ LỆNH PHÁ KHỐI
        # =====================================================================
        sa_ban_path = [(r, c) for r, c in full_path_display if 0 <= r < ROWS and 0 <= c < COLS]

        for idx, (r, c) in enumerate(sa_ban_path):
            cell = self.grid_cells[r][c]
            
            # CHỮ "PHÁ" ĐẶT Ở GÓC DƯỚI BÊN PHẢI (Bottom-Right)
            if cell["content"] and cell["content"]["number"] == 1:
                if not any(isinstance(x, ctk.CTkLabel) and x.cget("text") == "PHÁ" for x in cell["overlays"]):
                    lbl_b = ctk.CTkLabel(cell["frame"], text="PHÁ", width=36, height=24,
                                         fg_color="#e67e22", text_color="white",
                                         corner_radius=6, font=("DejaVu Sans", 10, "bold"))
                    lbl_b.place(relx=0.82, rely=0.85, anchor="center")
                    cell["overlays"].append(lbl_b)

            # MÀU ĐƯỜNG ĐI: Điểm đầu (Xanh biển), Điểm cuối (Vàng), Đi dọc đường (Xanh lá)
            color = "#2ecc71"
            if idx == 0: color = "#3498db"
            if idx == len(sa_ban_path) - 1: color = "#f1c40f"

            # SỐ THỨ TỰ BƯỚC ĐI ĐẶT Ở GÓC DƯỚI BÊN TRÁI (Bottom-Left)
            lbl = ctk.CTkLabel(cell["frame"], text=str(idx), width=28, height=28,
                               fg_color=color, text_color="black",
                               corner_radius=14, font=("DejaVu Sans", 12, "bold"))
            lbl.place(relx=0.18, rely=0.85, anchor="center")
            cell["overlays"].append(lbl)
            self.root.update_idletasks()
        # =====================================================================
        # 5. FIX LỖI CTKLABEL Ở CỬA
        # =====================================================================
        if hasattr(self, '_best_col'):
            door = self.door_cells[self._best_col]
            lbl_d = ctk.CTkLabel(door["frame"], 
                                 text="★ VÀO ĐÂY",  # ĐÃ THÊM TEXT ĐỂ FIX LỖI
                                 font=("DejaVu Sans", 12, "bold"),
                                 text_color="#00ff88", fg_color="transparent")
            lbl_d.place(relx=0.5, rely=0.85, anchor="center")
            door["overlays"].append(lbl_d)
    def process_and_send_uart(self, simulation_path):
        if not ser or not ser.is_open:
            print(f"\n[UART ERROR] UART port không sẵn sàng")
            self.info_label.configure(text="Lỗi UART: Port không mở")
            return

        current_facing = (-1, 0)
        right_turn_map = {(-1,0):(0,1), (0,1):(1,0), (1,0):(0,-1), (0,-1):(-1,0)}
        left_turn_map  = {(-1,0):(0,-1), (0,-1):(1,0), (1,0):(0,1), (0,1):(-1,0)}

        print("=" * 60)
        print(f"BẮT ĐẦU GỬI UART — TEAM {self.team_color}")
        print("=" * 60)
        
        # =====================================================================
        # >>> BẮN GÓI TIN CHỌN MODE (STATE = 10) TRƯỚC KHI CHẠY <<<
        # =====================================================================
        # Dịch cái biến chữ của anh thành số cho STM32 hiểu
        mode_val = 1 if hasattr(self, 'forest_mode') and self.forest_mode == "normal" else 2
        
        print(f"\n>>> [CONFIG MODE] Gửi lệnh cài đặt: (2, 10, {mode_val}, 2, 2)")
        ser.write(build_packet(2, 10, mode_val, 2, 2))
        time.sleep(0.3) # Nghỉ 0.3s cho STM32 kịp load não trước khi bắn lệnh chạy
        # =====================================================================
        strat_val = 2 if getattr(self, 'is_fast_attack', True) else 1
        strat_name = "THẮNG NHANH" if strat_val == 2 else "CÀY ĐIỂM"
        
        print(f">>> [CHIẾN THUẬT] Gửi lệnh: (2, 9, {strat_val}, 2, 2) - {strat_name}")
        ser.write(build_packet(2, 9, strat_val, 2, 2))
        time.sleep(0.3) 
        # ===============

        self.packets_cache = []
        has_sent_start = False
        has_climbed    = False
        traveled_path  = []
        picked_blocks  = []
        count_rb2      = 0

        first_door_col = None
        for seg_path, seg_act in simulation_path:
            for pos in seg_path:
                if pos[0] == DOOR_ROW:
                    first_door_col = pos[1]
                    break
            if first_door_col is not None:
                break

        if first_door_col is None:
            first_door_col = self._best_col if hasattr(self, '_best_col') else 1

        start_block_id = self.get_cell_id(ROWS - 1, first_door_col)

        assert 1 <= start_block_id <= 3, f"START ID sai: {start_block_id} (col={first_door_col})"

        start_packet_str = f"(2, 2, 10, 10, {start_block_id})"
        print(f"\n>>> GÓI TIN BẮT ĐẦU: {start_packet_str}")
        print(f"    Robot đi thẳng tới cửa ID={start_block_id} (cột {first_door_col})")

        self.info_label.configure(
            text=f"GÓI BẮT ĐẦU: {start_packet_str}\n"
                 f"Robot đi thẳng tới cửa ID={start_block_id} (Sân {self.team_color})"
        )
        self.root.update()

        print(f"\n  ├─ [START PACKET] Gửi: {start_packet_str}")
        ser.write(build_packet(2, 2, 10, 10, start_block_id))
        self.packets_cache.append([2, 2, 10, 10, start_block_id])
        time.sleep(0.3)
        has_sent_start = True

        for seg_idx, (segment_path, segment_action) in enumerate(simulation_path):
            print(f"\n[SEGMENT {seg_idx}] Action={segment_action} | Path={segment_path}")

            if not traveled_path:
                traveled_path.extend(segment_path)
            else:
                traveled_path.extend(segment_path[1:])

            for i in range(len(segment_path) - 1):
                curr_r, curr_c = segment_path[i]
                next_r, next_c = segment_path[i + 1]
                dc = next_c - curr_c
                dr = next_r - curr_r

                if curr_r == DOOR_ROW and next_r == DOOR_ROW:
                    move_cmd = 3 if dc > 0 else 2
                    door_id  = self._get_door_block_id(next_c)
                    time.sleep(0.3)
                    ser.write(build_packet(2, 2, move_cmd, 10, door_id))
                    count_rb2 += 1
                    desc = "→ Phải" if dc > 0 else "← Trái"
                    print(f"  ├─ [DOOR LATERAL] Gửi: (2, 2, {move_cmd}, 10, {door_id}) — {desc}")
                    time.sleep(0.1)
                    continue

                if curr_r == DOOR_ROW and next_r == ROWS - 1:
                    entry_id = self.get_cell_id(next_r, next_c)
                    
                    cell_entry = self.grid_cells[next_r][next_c]
                    if cell_entry["content"] and cell_entry["content"]["number"] == 1:
                        print(f"  ├─ [KHỐI 1 BỤC] Gửi: (1, 2, 0, 0, {entry_id}) — Phá khối tại bục")
                        time.sleep(0.3)
                        ser.write(build_packet(1, 2, 0, 0, entry_id))
                        time.sleep(0.3)
  
                    time.sleep(0.3)
                    ser.write(build_packet(2, 2, 1, 4, entry_id))
                    count_rb2 += 1
                    has_climbed = True
                    print(f"  ├─ [CLIMB] Gửi: (2, 2, 1, 4, {entry_id}) — Leo bục thẳng")
                    time.sleep(0.3)
                    continue

                if 0 <= curr_r < ROWS and 0 <= next_r < ROWS:
                    step_id  = self.get_cell_id(next_r, next_c)
                    move_vec = (dr, dc)

                    if move_vec == current_facing:
                        move_cmd = 1
                    elif move_vec == left_turn_map[current_facing]:
                        move_cmd = 2
                        current_facing = move_vec
                    elif move_vec == right_turn_map[current_facing]:
                        move_cmd = 3
                        current_facing = move_vec
                    else:
                        print(f"  │  ├─ [Warn] 180° không hỗ trợ tại ID={step_id}")
                        continue

                    cell_next = self.grid_cells[next_r][next_c]

                    if cell_next["content"] and cell_next["content"]["number"] == 1:
                        print(f"  │  ├─ [KHỐI 1] Gửi: (1, 2, 0, 0, {step_id}) — Phá khối")
                        time.sleep(0.3)
                        ser.write(build_packet(1, 2, 0, 0, step_id))
                        time.sleep(0.3)

                    elif cell_next["content"] and cell_next["content"]["number"] == 2:
                        if step_id not in picked_blocks:
                            print(f"  │  ├─ [KHỐI 2] Gửi: (2, 2, 0, {move_cmd}, {step_id}) — Gắp trước khi đi")
                            time.sleep(0.3)
                            ser.write(build_packet(2, 2, 0, move_cmd, step_id))
                            count_rb2 += 1
                            picked_blocks.append(step_id)
                            time.sleep(0.5)

                    time.sleep(0.3)
                    ser.write(build_packet(2, 2, move_cmd, 4, step_id))
                    self.packets_cache.append([2, 2, move_cmd, 4, step_id])
                    count_rb2 += 1
                    desc = ["?", "Thẳng", "Trái", "Phải"][move_cmd]
                    print(f"  │  ├─ [MOVE]   Gửi: (2, 2, {move_cmd}, 4, {step_id}) — {desc}")
                    time.sleep(0.1)

            if segment_action == "FINISH":
                continue
            if not isinstance(segment_action, tuple):
                continue

            tr, tc = segment_action
            action_id = self.get_cell_id(tr, tc)

            if action_id in picked_blocks:
                print(f"  └─ [SKIP] ID={action_id} đã gắp rồi")
                continue

            robot_r, robot_c = segment_path[-1]
            dr_act = tr - robot_r
            dc_act = tc - robot_c

            if robot_r == DOOR_ROW and tr == ROWS - 1 and robot_c == tc:
                print(f"  └─ [PICK DOOR] Gửi: (2, 2, 0, 1, {action_id}) — Vươn lên gắp từ cửa")
                time.sleep(0.3)
                ser.write(build_packet(2, 2, 0, 1, action_id))
                count_rb2 += 1
                time.sleep(0.3)
                picked_blocks.append(action_id)
                continue

            action_cmd = 4
            if (dr_act, dc_act) == (0, 0):
                action_cmd = 4
            elif (dr_act, dc_act) == current_facing:
                action_cmd = 1
            elif (dr_act, dc_act) == left_turn_map[current_facing]:
                action_cmd = 2
            elif (dr_act, dc_act) == right_turn_map[current_facing]:
                action_cmd = 3

            desc = ["?", "Thẳng", "Trái", "Phải", "Tại chỗ"][action_cmd]
            print(f"  └─ [PICK]      Gửi: (2, 2, 0, {action_cmd}, {action_id}) — Gắp {desc}")
            time.sleep(0.3)
            ser.write(build_packet(2, 2, 0, action_cmd, action_id))
            count_rb2 += 1
            time.sleep(0.3)
            picked_blocks.append(action_id)

        if traveled_path:
            last_pos = traveled_path[-1]
            last_id = self.get_cell_id(last_pos[0], last_pos[1])
            if last_id in [10, 11, 12]:
                print(f"  ├─ [END PACKET] Gửi gói END (2,2,20,20) tới ID={last_id}")
                end_packet = build_packet(2, 2, 20, 20, last_id)
                ser.write(end_packet)
                self.packets_cache.append([2, 2, 20, 20, last_id]) # <--- LƯU GÓI CUỐI
                time.sleep(0.1)
        try:
            import json
            with open("last_packet_cache.json", "w") as f:
                json.dump(self.packets_cache, f)
            print(f"\n[CACHE] Đã lưu cứng {len(self.packets_cache)} gói tin vào Local Jetson!")
        except Exception as e:
            print(f"\n[CACHE ERROR] Không thể lưu file cache: {e}")      

        print("\n" + "=" * 60)
        print(f"HOÀN THÀNH — {count_rb2} gói tin (id_rb=2)")
        print("=" * 60)
        self.info_label.configure(
            text=f"✓ Gửi xong ({self.team_color}): {count_rb2} gói\n"
                 f"Gói bắt đầu: {start_packet_str}"
        )

    def _get_door_block_id(self, col):
        return self.get_cell_id(ROWS - 1, col)
    
    def run_algothism_forest(self):
        self.root.mainloop()
        
    def action_replay_cache(self):
        import json
        import os
        
        cache_file = "map_cache_ui.json"
        
        if not os.path.exists(cache_file):
            self.info_label.configure(text="[LỖI] Chưa có gói tin Cache UI nào!")
            return
            
        try:
            with open(cache_file, "r") as f:
                data = json.load(f)
            
            # --- 1. DỌN SẠCH SÂN TRƯỚC KHI DỰNG LẠI ---
            self.reset_grid()
            
            # --- 2. KHÔI PHỤC TEAM COLOR VÀ ID Ô ---
            self.team_color = data.get("team_color", "RED")
            if self.team_color == "RED":
                self.team_btn.configure(text="Sân: ĐỎ (RED)", fg_color="#d32f2f")
            else:
                self.team_btn.configure(text="Sân: XANH (BLUE)", fg_color="#1e88e5")
            self.refresh_grid_ids()

            # --- 3. TẠM TẮT AUTO UPDATE ĐỂ XẾP MAP ĐỠ LAG ---
            self.auto_update_path = False

            # --- 4. TỰ ĐỘNG ĐẶT LẠI CÁC KHỐI TỪ CACHE ---
            for r, c, num in data.get("blocks", []):
                self.place_block(num, (r, c))

            self.info_label.configure(text="Đang tải lại map từ Cache và tính toán đường đi...", text_color="blue")
            self.root.update()

            # --- 5. TỰ ĐỘNG TÌM ĐƯỜNG LẠI (NHƯNG KHÔNG BẮN UART) ---
            # Gọi smart_run để tính toán và sinh list CMD, sau đó hiển thị lên UI chờ mày xác nhận
            self.smart_run()
            
            self.info_label.configure(
                text="✓ Tải Cache & Tìm đường xong! Hãy kiểm tra và nhấn [GỬI LỆNH] khi sẵn sàng.",
                text_color="green"
            )

        except Exception as e:
            print(f"[CACHE ERROR] Lỗi: {e}")
            self.info_label.configure(text=f"Lỗi khôi phục Cache: {e}", text_color="red")
# ========================================================
    # >>> KHỐI LOGIC: QUÉT VÀ GIẢI MÃ QR TỰ ĐỘNG
    # ========================================================
    def process_qr_payload(self, payload):
        print(f"\n>>> [QR SCANNER] Bắt được chuỗi dữ liệu: {payload}")
        parts = payload.split('|')
        if len(parts) != 4:
            print(">>> [LỖI] Mã QR đéo đúng định dạng hệ thống!")
            return False

        team_qr, b1_str, b2_str, b3_str = parts

        # 1. Đồng bộ Sân (Đỏ / Xanh) theo mã QR
        if team_qr == 'R' and self.team_color != "RED":
            self.toggle_team()
        elif team_qr == 'B' and self.team_color != "BLUE":
            self.toggle_team()

        # 2. Xóa sạch rác trên sa bàn cũ
        self.reset_grid()

        # 3. Hàm dò ngược: Từ ID QR -> Map ra tọa độ (Row, Col) trên UI
        def place_by_ids(id_string, block_num):
            if not id_string: return
            ids = [int(x) for x in id_string.split(',') if x.strip()]
            for target_id in ids:
                for r in range(ROWS):
                    for c in range(COLS):
                        # Lấy ID thực tế tại ô này ở thời điểm hiện tại
                        current_id = self.get_cell_id(r, c)
                        if current_id == target_id:
                            self.place_block(block_num, (r, c))

        # 4. Trải thảm khối 1, 2, 3 lên sa bàn
        place_by_ids(b1_str, 1)
        place_by_ids(b2_str, 2)
        place_by_ids(b3_str, 3)

        print(f">>> [QR SCANNER] Nạp Map thành công cho đội {team_qr}!")
        return True

    def cancel_qr(self):
        """Hàm con để bật cờ dừng quét"""
        print(">> [HỆ THỐNG] Đã nhận lệnh HỦY QUÉT từ người dùng.")
        self.stop_qr = True

    def open_qr_scanner(self):
        self.stop_qr = False # Reset cờ trước khi bắt đầu
        self.info_label.configure(text="Đang mở Cam... Đưa mã QR vào hoặc bấm 'DỪNG QUÉT'", text_color="blue")
        
        # 1. TẠO NÚT HỦY TẠM THỜI TRÊN GIAO DIỆN
        self.btn_stop_scan = ctk.CTkButton(
            self.bottom_frame, text="🛑 DỪNG QUÉT", width=120, height=40,
            fg_color="#f44336", hover_color="#d32f2f",
            command=self.cancel_qr
        )
        self.btn_stop_scan.pack(side="left", padx=5)
        self.root.update()

        # 2. KHỞI ĐỘNG CAMERA
        pipeline = rs.pipeline()
        config = rs.config()
        config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)

        try:
            pipeline.start(config)
        except Exception as e:
            self.info_label.configure(text=f"Lỗi mở Cam: {e}", text_color="red")
            self.btn_stop_scan.pack_forget()
            return

        win_name = f"QR SCANNER [{int(time.time())}]"
        cv2.namedWindow(win_name, cv2.WINDOW_AUTOSIZE)
        success = False
        frame_counter = 0

        try:
            while True:
                # 👉 KIỂM TRA LỆNH THOÁT TỪ NÚT BẤM HOẶC PHÍM ESC
                self.root.update() # Rất quan trọng: Giúp Tkinter nhận lệnh bấm nút
                if self.stop_qr: 
                    print(">> Thoát quét QR theo lệnh người dùng.")
                    break

                frames = pipeline.wait_for_frames(timeout_ms=1000)
                color_frame = frames.get_color_frame()
                if not color_frame: continue

                img = np.asanyarray(color_frame.get_data())
                frame_counter += 1

                # Quét QR (Skip frame để giảm tải CPU Jetson)
                if frame_counter % 5 == 0:
                    decoded_objs = decode(img)
                    for obj in decoded_objs:
                        qr_data = obj.data.decode("utf-8")
                        cv2.putText(img, "CHECKING...", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
                        cv2.imshow(win_name, img)
                        cv2.waitKey(300)

                        if self.process_qr_payload(qr_data):
                            success = True
                        break

                cv2.imshow(win_name, img)

                # Thoát nếu quét thành công hoặc bấm ESC trên cửa sổ Cam
                if success or (cv2.waitKey(1) & 0xFF == 27): 
                    break
        finally:
            # 3. DỌN DẸP SẠCH SẼ
            try: pipeline.stop()
            except: pass
            
            cv2.destroyWindow(win_name)
            for _ in range(5): cv2.waitKey(1)
            
            # Xóa nút Dừng Quét khỏi giao diện để trả lại chỗ cũ
            self.btn_stop_scan.pack_forget()
            self.root.update()

            if success:
                self.info_label.configure(text="✓ Nạp Map thành công!", text_color="green")
            else:
                self.info_label.configure(text="Đã đóng quét QR.", text_color="black")
    # =========================================================================
    # TAB 2: VÙNG 3 (MATRIX DETECT) - TÍCH HỢP TỪ MAIN
    # =========================================================================
    def setup_matrix_tab(self):
        self.matrix_selected = {i: False for i in range(1, 7)}
        self.matrix_buttons = {}

        ctk.CTkLabel(
            self.tab_matrix, text="Bảng Điều Khiển Gắp Khối Vùng 3",
            font=("Segoe UI", 22, "bold"), text_color="#1e293b"
        ).pack(pady=(20, 5))

        self.matrix_status = ctk.CTkLabel(self.tab_matrix, text="Sẵn sàng gửi UART", font=("Segoe UI", 14), text_color="#64748b")
        self.matrix_status.pack(pady=(0, 5))

        card = ctk.CTkFrame(self.tab_matrix, corner_radius=20, fg_color="#ffffff")
        card.pack(padx=20, pady=5, fill="both", expand=True)

        btn_frame = ctk.CTkFrame(card, fg_color="transparent")
        btn_frame.pack(expand=True, pady=15)

        for i in range(1, 7):
            row = 1 if i <= 3 else 0   
            col = (i - 1) % 3
            btn = ctk.CTkButton(
                btn_frame, text=str(i), width=90, height=90, corner_radius=16,
                font=("Segoe UI", 26, "bold"), text_color="white",
                fg_color="#4f46e5", hover_color="#6366f1",
                command=lambda n=i: self.toggle_matrix(n)
            )
            btn.grid(row=row, column=col, padx=15, pady=10)
            self.matrix_buttons[i] = btn

        bottom_frame = ctk.CTkFrame(self.tab_matrix, fg_color="transparent")
        bottom_frame.pack(pady=(5, 15))

        ctk.CTkButton(
            bottom_frame, text="✔ CHỐT GỬI LỆNH", width=180, height=45, corner_radius=14,
            font=("Segoe UI", 16, "bold"), fg_color="#16a34a", hover_color="#15803d",
            command=self.on_matrix_confirm
        ).grid(row=0, column=0, padx=10)

        ctk.CTkButton(
            bottom_frame, text="↺ Reset", width=120, height=45, corner_radius=14,
            font=("Segoe UI", 16, "bold"), fg_color="#dc2626", hover_color="#b91c1c",
            command=self.on_matrix_reset
        ).grid(row=0, column=1, padx=10)

    def toggle_matrix(self, n):
        self.matrix_selected[n] = not self.matrix_selected[n]
        if self.matrix_selected[n]:
            self.matrix_buttons[n].configure(fg_color="#f59e0b", hover_color="#d97706")
        else:
            self.matrix_buttons[n].configure(fg_color="#4f46e5", hover_color="#6366f1")

    def on_matrix_reset(self):
        for i in range(1, 7):
            self.matrix_selected[i] = False
            self.matrix_buttons[i].configure(fg_color="#4f46e5", hover_color="#6366f1")
        self.matrix_status.configure(text="Đã Reset lựa chọn", text_color="#64748b")

    def on_matrix_confirm(self):
        col_map = {1: 1, 2: 2, 3: 3, 4: 1, 5: 2, 6: 3}
        entry = [0, 0, 0]
        for n in range(1, 7):
            if self.matrix_selected[n]:
                idx = col_map[n] - 1
                entry[idx] = n

        threading.Thread(
            target=self.send_uart_matrix,
            args=(entry[0], entry[1], entry[2]),
            daemon=True
        ).start()

    def send_uart_matrix(self, e1, e2, e3):
        try:
            packet = build_packet(2, 3, e1, e2, e3)
            send_packet_once(ser, packet)
            self.matrix_status.configure(text=f"Đã gửi UART Vùng 3: {e1} - {e2} - {e3}", text_color="#16a34a")
            print(f"[MATRIX] Đã gửi lệnh Vùng 3: 2, 3, {e1}, {e2}, {e3}")
        except Exception as e:
            self.matrix_status.configure(text="LỖI UART: Kiểm tra cáp kết nối", text_color="#dc2626")
            print("UART Error:", e)

    # =========================================================================
    # CÔNG TẮC BẬT/TẮT LẮNG NGHE UART (KHÔNG ĐẺ LUỒNG MỚI CHỐNG CRASH)
    # =========================================================================
    def toggle_main_listener(self):
        try:
            # Import cờ điều khiển từ file uart_listener của mày
            from uart_listener import uart_enable
            
            # Đảo trạng thái công tắc
            self.is_listening = not self.is_listening
            
            if self.is_listening:
                # TRẠNG THÁI 1: BẬT
                uart_enable["value"] = True
                self.listen_btn.configure(
                    text="🎧 ĐANG LẮNG NGHE...", 
                    fg_color="#27ae60", hover_color="#2ecc71"
                )
                self.info_label.configure(text="✓ Đã MỞ kết nối Lắng nghe UART!", text_color="green")
                print(">> [UART Algo] Đã MỞ van lắng nghe.")
            else:
                # TRẠNG THÁI 2: TẮT
                uart_enable["value"] = False
                self.listen_btn.configure(
                    text="🎧 BẬT LẮNG NGHE (MAIN)", 
                    fg_color="#8e44ad", hover_color="#732d91"
                )
                self.info_label.configure(text="⏸ Đã TẠM DỪNG Lắng nghe UART.", text_color="#f39c12")
                print(">> [UART Algo] Đã ĐÓNG van lắng nghe.")
                
        except Exception as e:
            self.info_label.configure(text=f"LỖI Công tắc Lắng Nghe: {e}", text_color="red")
            print(f">> LỖI: {e}")
    def update_led_blink(self):
        """Hàm tạo hiệu ứng nháy đèn dựa trên trạng thái kết nối"""
        self.led_on = not self.led_on # Đảo trạng thái sáng/tối
        
        if self.is_server_connected:
            # NẾU CÓ KẾT NỐI: Nháy màu Xanh lá
            color = "#2ecc71" if self.led_on else "#145a32" # Sáng xanh / Tối xanh
            txt = "● SERVER OK"
        else:
            # NẾU MẤT KẾT NỐI: Nháy màu Đỏ rực
            color = "#e74c3c" if self.led_on else "#641e16" # Sáng đỏ / Tối đỏ
            txt = "● NO SERVER"

        # Cập nhật lên giao diện
        try:
            self.status_led.configure(text=txt, text_color=color)
        except:
            return # Tránh lỗi khi đóng app

        # Lặp lại sau mỗi 500ms (0.5 giây nháy 1 lần)
        self.root.after(500, self.update_led_blink)
        
if __name__ == "__main__":
    app = SelectPlaceApp()
    app.run_algothism_forest()