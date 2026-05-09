import customtkinter as ctk
import heapq
import itertools
import time
import pyrealsense2 as rs
import cv2
import numpy as np
import socketio as client_sio      
import threading     
from pyzbar.pyzbar import decode
from tkinter import simpledialog, messagebox
from gui_tkinter import set_state, STATE_FOREST, STATE_IDLE 
from config_uart.sent_uart import build_packet, send_packet_once, ser
import socketio
import threading
from flask import Flask, render_template
from flask_socketio import SocketIO, emit
from flask_cors import CORS
import socket
import threading

SERVER_IP = "http://127.0.0.1:5001"
ctk.set_appearance_mode("System")
ctk.set_default_color_theme("blue")

ROWS = 4          # Số hàng sa bàn (không tính cửa)
COLS = 3
DOOR_ROW = ROWS   # Hàng cửa (row index = 4, phía dưới sa bàn)
CELL_SIZE = 100
width_cell = 90
height_cell = 70

app = Flask(__name__, static_folder='static', static_url_path='/static')
CORS(app)
socketio = SocketIO(app, cors_allowed_origins="*")

# Dữ liệu dùng chung cho cả Web và Giao diện máy tính
global_state = {str(i): 'EMPTY' for i in range(1, 13)}
global_team = 'R'

# --- CÁC XỬ LÝ SERVER (Bê từ test_server.py sang) ---
@app.route('/')
def home():
    return render_template('index.html')

@socketio.on('connect')
def handle_connect():
    emit('server_sync', {'state': global_state, 'team': global_team})

@socketio.on('client_click')
def handle_click(data):
    global global_state
    cell_id = str(data['id'])
    if cell_id != "0": # Tránh ID rác
        global_state[cell_id] = data['val']
    
    # Đã đổi socketio.emit thành emit chuẩn
    payload = {"team": global_team, "grid": get_algo_matrix_internal()}
    emit('server_sync', {'state': global_state, 'team': global_team}, broadcast=True)
    emit('sync_state', payload, broadcast=True)

@socketio.on('client_toggle_team')
def handle_toggle_team():
    global global_team, global_state
    mirror_map = {'12':'10','10':'12','9':'7','7':'9','6':'4','4':'6','3':'1','1':'3','11':'11','8':'8','5':'5','2':'2'}
    new_state = {mirror_map[old_id]: val for old_id, val in global_state.items()}
    global_state = new_state
    global_team = 'B' if global_team == 'R' else 'R'
    payload = {"team": global_team, "grid": get_algo_matrix_internal()}
    emit('server_sync', {'state': global_state, 'team': global_team}, broadcast=True)
    emit('sync_state', payload, broadcast=True)

@socketio.on('client_reset')
def handle_reset():
    global global_state
    global_state = {str(i): 'EMPTY' for i in range(1, 13)}
    payload = {"team": global_team, "grid": get_algo_matrix_internal()}
    emit('server_sync', {'state': global_state, 'team': global_team}, broadcast=True)
    emit('sync_state', payload, broadcast=True)

@socketio.on('client_trigger_algo')
def handle_trigger_algo():
    emit('trigger_algo', {}, broadcast=True)

def get_algo_matrix_internal():
    val_map = {'1': 1, '2': 2, 'Fake': 3, 'EMPTY': 0, None: 0}
    def get_v(cid): return val_map.get(global_state.get(str(cid)), 0)
    if global_team == 'R':
        return [[get_v(12), get_v(11), get_v(10)], [get_v(9), get_v(8), get_v(7)], [get_v(6), get_v(5), get_v(4)], [get_v(3), get_v(2), get_v(1)]]
    else:
        return [[get_v(10), get_v(11), get_v(12)], [get_v(7), get_v(8), get_v(9)], [get_v(4), get_v(5), get_v(6)], [get_v(1), get_v(2), get_v(3)]]

@socketio.on('client_toggle_mode')
def handle_toggle_mode():
    print(">> [WEB] Lệnh đổi Mode (Normal/Retry2)")
    emit('trigger_mode', {}, broadcast=True)

@socketio.on('client_toggle_strategy')
def handle_toggle_strategy():
    print(">> [WEB] Lệnh đổi Chiến thuật (Thang nhanh/Cay điểm)")
    emit('trigger_strategy', {}, broadcast=True)

@socketio.on('client_replay_cache')
def handle_replay_cache():
    print(">> [WEB] Lệnh Phát lại UART Cache")
    emit('trigger_replay', {}, broadcast=True)

@socketio.on('client_set_target')
def handle_set_target(data):
    print(f">> [WEB] Lệnh đổi TARGET: {data['target']} khối")
    emit('trigger_target', data, broadcast=True)

def get_local_ip():
    try:
        import subprocess
        # Lệnh ép Ubuntu đọc thẳng IP của card mạng (thường là wlan0)
        ip = subprocess.check_output("hostname -I", shell=True).decode().strip().split()[0]
        return ip
    except Exception:
        # Nếu lỗi thì trả về IP mặc định của Ubuntu Hotspot
        return "10.42.0.1"

def run_server():
    my_ip = get_local_ip()
    print("\n" + "★"*55)
    print("🚀 TRẠM CHỈ HUY (SERVER) ĐÃ KHỞI ĐỘNG CÙNG ALGO!")
    print(f"📱 Cầm điện thoại bắt WiFi và truy cập link này:")
    print(f"👉 http://{my_ip}:5001")
    print("★"*55 + "\n")
    # Tắt sạch log rác của Flask để Terminal sạch sẽ nhìn cho sướng
    import logging
    log = logging.getLogger('werkzeug')
    log.setLevel(logging.ERROR)
    
    socketio.run(app, host='0.0.0.0', port=5001, debug=False, use_reloader=False)

class SelectPlaceApp:
    def __init__(self):
        # --- CỜ CHIẾN THUẬT MẶC ĐỊNH ---
        self.is_fast_attack = True  # True = Thắng Nhanh, False = Cày Điểm
        self.target_blocks = 4      # MẶC ĐỊNH ĂN FULL 4 KHỐI <--- (THÊM DÒNG NÀY)
        self.root = ctk.CTk()
        self.root.title("Robot Pathfinding: Hybrid & UART Control")
        self.root.geometry("900x580")  # Đã nới rộng ra để chứa Tab cho đẹp

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
                #cell_frame.bind("<Double-Button-1>", lambda e, pos=(i, j): self.cell_double_clicked(pos))
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
                height=20,          # Ô cửa nhỏ hơn
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
        # 🕹️ CHỨC NĂNG ÉP CỬA RETRY (DÙNG NÚT BẤM TOGGLE)
        # =====================================================================
        self.forced_door_index = -1 # -1: Auto, 0: Cửa A, 1: Cửa B, 2: Cửa C
        self.door_buttons = []
        
        # Khung chứa 3 nút ngay dưới 3 cửa
        self.retry_frame = ctk.CTkFrame(self.tab_forest, fg_color="transparent")
        self.retry_frame.pack(pady=5)
        
        
        door_labels = ["EP A", "EP B", "EP C"]
        for j in range(COLS):
            btn = ctk.CTkButton(
                self.retry_frame, text=door_labels[j], 
                width=70, height=35, corner_radius=10,
                fg_color="#34495e", hover_color="#2c3e50", # Màu tối mặc định
                font=("DejaVu Sans", 12, "bold"),
                command=lambda x=j: self.toggle_door_selection(x)
            )
            btn.pack(side="left", padx=15)
            self.door_buttons.append(btn)
        
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
            self.bottom_frame, text="San: Đo (RED)", width=80, height=70,
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
        self.update_led_blink()
        # =====================================================================
        # THÊM DÒNG HIỆN IP SERVER ĐỂ ĐIỀU KHIỂN TỪ XA
        # =====================================================================
        my_ip = get_local_ip() 
        self.server_url_label = ctk.CTkLabel(
            self.root, 
            text=f"🌐 URL: http://{my_ip}:5001",
            font=("DejaVu Sans", 13, "bold"),
            text_color="black"
        )
        # Đặt sát về bên trái: relx=0.21, rely=0.015
        self.server_url_label.place(relx=0.21, rely=0.015, anchor="ne")
# --- NÚT TÌM ĐƯỜNG ---
# --- CỜ CHIẾN THUẬT MẶC ĐỊNH ---
        self.is_fast_attack = True  # True = Thắng Nhanh, False = Cày Điểm

        # --- NÚT CHIẾN THUẬT (THẮNG NHANH / CÀY ĐIỂM) ---
        self.run_btn = ctk.CTkButton(
            self.bottom_frame, text="TIM DUONG", width=80, height=65,
            fg_color="#5cb85c", hover_color="#449d44",
            command=self.smart_run
        )
        self.run_btn.pack(side="left", padx=3)

        self.info_label = ctk.CTkLabel(
            self.tab_forest,            text="Che do: Dat khoi.\nBam 'TIM DUONG' de tim duong, sau do 'GUI UART' de truyen.",
            width=250, height=50, wraplength=600, justify="left", font=("DejaVu Sans", 9)
        )
        self.send_uart_btn = ctk.CTkButton(self.bottom_frame, text="GUI UART", width=90, height=70, fg_color="#9c27b0", hover_color="#7b1fa2", command=self.sent_and_close)
        self.send_uart_btn.pack(side="left", padx=3)

        self.strategy_btn = ctk.CTkButton(
            self.bottom_frame, text="THANG NHANH", width=80, height=70,
            fg_color="#f59e0b", hover_color="#d97706",
            command=self.toggle_strategy
        )
        self.strategy_btn.pack(side="left", padx=5)
        # --- CỜ TRẠNG THÁI & KHỞI TẠO KẾT NỐI SOCKET ---
        self.sync_mode = False  

        # 1. BẬT SERVER CHẠY NGẦM
        threading.Thread(target=run_server, daemon=True).start()
        
        # 2. CHỜ 1 GIÂY CHO SERVER LÊN MÂM
        import time
        time.sleep(1)

        # 3. KẾT NỐI ALGO VÀO SERVER NỘI BỘ
        self.sio = client_sio.Client()
        
        # =======================================================
        # LẮNG NGHE LỆNH TỪ WEB (ĐÃ BỔ SUNG LỖ TAI ĐỒNG BỘ MAP)
        # =======================================================
        @self.sio.on('trigger_target')
        def on_trigger_target(data=None):
            if data and 'target' in data:
                self.target_blocks = data['target'] # Lưu biến vào class
                print(f"\n>> [CHIẾN THUẬT] ĐÃ CHỐT MỤC TIÊU: Chỉ ăn {self.target_blocks} khối R2!")

        @self.sio.on('connect')
        def on_connect():
            self.is_server_connected = True

        @self.sio.on('disconnect')
        def on_disconnect():
            self.is_server_connected = False

        # Lỗ tai đồng bộ màu sắc sa bàn (Chỗ bị thiếu lúc nãy)
        @self.sio.on('sync_state')
        def on_sync_state(data):
            if self.sync_mode:
                # Ép tăng ID luồng để gọi hàm cập nhật
                self.calc_session_id += 1
                current_session = self.calc_session_id
                self.root.after(0, lambda s=current_session: self.apply_server_state(data, s))
        @self.sio.on('trigger_algo')
        def on_trigger_algo(data=None):
            print("\n" + "🚀"*20)
            print(">> [WEB] ĐÃ NHẬN LỆNH BÓP CÒ: Đang tính toán và bắn UART...")
            self.root.after(0, self.smart_run)
            # Chờ 1 giây để Algo vẽ xong đường rồi mới vả UART
            self.root.after(1000, self.sent_and_close)

        @self.sio.on('trigger_mode')
        def on_trigger_mode(data=None):
            self.root.after(0, self.toggle_forest_mode)

        @self.sio.on('trigger_strategy')
        def on_trigger_strategy(data=None):
            self.root.after(0, self.toggle_strategy)

        @self.sio.on('trigger_replay')
        def on_trigger_replay(data=None):
            self.root.after(0, self.action_replay_cache)

        # =======================================================
        # === NHÉT THÊM CỤC LỖ TAI NÀY VÀO ===
        # =======================================================
        @self.sio.on('trigger_reset')
        def on_trigger_reset(data=None):
            print("\n>> [WEB] ĐÃ NHẬN LỆNH XÓA MAP: Đang dọn dẹp sa bàn...")
            self.root.after(0, self.reset_grid)

        # 4. KẾT NỐI SAU KHI ĐÃ GẮN ĐỦ LỖ TAI
        try:
            self.sio.connect('http://127.0.0.1:5001', transports=['websocket'])
            print(">> 🟢 ALGO ĐÃ KẾT NỐI VỚI SERVER THÀNH CÔNG!")
        except Exception as e:
            print(">> 🔴 LỖI KẾT NỐI SERVER NỘI BỘ:", e)

        # 5. TỰ ĐỘNG BẬT "NHẬN LIVE" ĐỂ MÀY KHỎI PHẢI BẤM BẰNG TAY!
        self.root.after(1000, self.handle_sync_toggle)

        # --- NÚT TOGGLE LIVE (THAY THẾ NÚT QUÉT QR CŨ) ---
        self.toggle_sync_live_btn = ctk.CTkButton(
            self.bottom_frame, text="📡 BAT NHAN LIVE", width=70, height=70,
            fg_color="#00bcd4", hover_color="#0097a7",
            command=self.handle_sync_toggle
        )
        self.toggle_sync_live_btn.pack(side="left", padx=5)

        
        # --- NÚT CHỌN KPI (GẮP 2, 3, 4 CỤC) NẰM CHUNG HÀNG VỚI NÚT ÉP CỬA ---
        self.target_blocks = 3 # Mặc định là 3

        # Đục một cái vách ngăn (Separator) giữa Nút Ép Cửa và Nút KPI cho đẹp
        ctk.CTkLabel(self.retry_frame, text=" ║ ", font=("DejaVu Sans", 20, "bold"), text_color="gray").pack(side="left", padx=10)

        # Đổi parent thành self.retry_frame và bóp height=35 cho bằng với nút Ép cửa
        self.btn_kpi_2 = ctk.CTkButton(self.retry_frame, text="✌️ 2 KHOI", width=70, height=35, corner_radius=10,
                                       fg_color="#34495e", hover_color="#c0392b", command=lambda: self.set_kpi(2))
        self.btn_kpi_2.pack(side="left", padx=5)

        self.btn_kpi_3 = ctk.CTkButton(self.retry_frame, text="🤟 3 KHOI", width=70, height=35, corner_radius=10,
                                       fg_color="#27ae60", hover_color="#2ecc71", command=lambda: self.set_kpi(3))
        self.btn_kpi_3.pack(side="left", padx=5)

        self.btn_kpi_4 = ctk.CTkButton(self.retry_frame, text="🖖 4 KHOI", width=70, height=35, corner_radius=10,
                                       fg_color="#34495e", hover_color="#5c4f61", command=lambda: self.set_kpi(4))
        self.btn_kpi_4.pack(side="left", padx=5)
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
            self.bottom_frame, text="PHAT CACHE", width=90, height=70,
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
            return 

        team_server = state.get("team", "R")
        grid_data = state.get("grid", [])

        # --- BỘ LỌC CHỐNG SPAM CHUẨN MỰC ---
        # Chỉ từ chối nếu CẢ SÂN VÀ MAP đều giống y xì đúc lần trước
        if hasattr(self, 'last_team') and self.last_team == team_server:
            if hasattr(self, 'last_grid_data') and self.last_grid_data == grid_data:
                return  

        self.last_team = team_server
        self.last_grid_data = grid_data

        # ==========================================================
        # 1. XỬ LÝ ĐỔI SÂN (RED <-> BLUE) ƯU TIÊN SỐ 1
        # ==========================================================
        if team_server == 'R' and self.team_color != "RED":
            self.toggle_team()
        elif team_server == 'B' and self.team_color != "BLUE":
            self.toggle_team()

        # ==========================================================
        # 2. CẬP NHẬT CỤC BỘ MAP (CHỈ VẼ LẠI Ô BỊ THAY ĐỔI)
        # ==========================================================
        for r in range(min(ROWS, len(grid_data))):
            for c in range(min(COLS, len(grid_data[r]))):
                new_val = grid_data[r][c]
                cell = self.grid_cells[r][c]
                
                current_val = cell["content"]["number"] if cell["content"] else 0
                
                # NẾU GIỐNG HỆT NHAU -> BỎ QUA CHO ĐỠ LAG!
                if current_val == new_val:
                    continue
                    
                # NẾU CÓ THAY ĐỔI -> Xóa khối cũ
                if cell["content"]:
                    cell["content"]["widget"].destroy()
                    cell["content"] = None
                    for btn in cell["buttons"]:
                        btn.pack(side="left", expand=True, padx=2, pady=2)
                    cell["id_label"].lift()
                
                # Đặt khối mới vào
                if new_val in [1, 2, 3]:
                    self.place_block(new_val, (r, c))
                    
        self.info_label.configure(text=f"Da đong bo San ({team_server}) & Map. Chờ lệnh GỬI.", text_color="blue")


    def toggle_sync_qr(self):
        # Chuyển sang chế độ Quét QR (Tắt Live)
        self.sync_mode = False
        self.toggle_sync_qr_btn.configure(text="DANG QUET QR", fg_color="#f39c12", hover_color="#d68910")
        self.root.update()
        
        self.open_qr_scanner() # Mở Camera quét QR
        
        # Sau khi xong, tự động quay lại nhận Live
        self.sync_mode = True
        self.toggle_sync_qr_btn.configure(text="LIVE", fg_color="#00bcd4", hover_color="#0097a7")    
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
                text="LIVE", 
                fg_color="#27ae60", hover_color="#219150" # Màu xanh lá
            )
            self.info_label.configure(text="DA BAT LIVE: Dang nhan du lieu tu Camera...", text_color="green")
        else:
            self.toggle_sync_live_btn.configure(
                text="LIVE", 
                fg_color="#00bcd4", hover_color="#0097a7" # Màu xanh lơ
            )
            self.info_label.configure(text="Đa TaT LIVE: Đang ở che đo xep tay.", text_color="black")
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
            self.info_label.configure(text="Chuyen sang Mode: Retry2")
        else:
            self.forest_mode = "normal"
            self.mode_btn.configure(text="Mode: Normal", fg_color="#5bc0de", hover_color="#31b0d5")
            self.info_label.configure(text="Chuyen sang Mode: Normal")
        print(f">> Forest Mode: {self.forest_mode.upper()}")
# =========================================================================
    # ĐỔI CHIẾN THUẬT (CHỈ LƯU TRẠNG THÁI VÀ ĐỔI UI, KHÔNG GỬI MẠCH)
    # =========================================================================
    def toggle_strategy(self):
        self.is_fast_attack = not self.is_fast_attack
        
        if self.is_fast_attack:
            self.strategy_btn.configure(
                text="🔥 THANG NHANH", 
                fg_color="#f59e0b", 
                hover_color="#d97706"
            )
            self.info_label.configure(text="Đa gai chien thuat: THANG NHANH. Bam 'GUI UART' de gui lenh.", text_color="#d97706")
        else:
            self.strategy_btn.configure(
                text="🎯 CAY ĐIEM", 
                fg_color="#8b5cf6", 
                hover_color="#7c3aed"
            )
            self.info_label.configure(text="Đa gai chien thuat: CAY ĐIEM. Bam 'GUI UART' đe chot lenh.", text_color="#8b5cf6")
    # =========================================================================
    # TOGGLE TEAM & REFRESH
    # =========================================================================
    def toggle_team(self):
        # Dùng .after(10) để vứt toàn bộ lệnh xử lý ra khỏi luồng Click Chuột. 
        # Click xong là nút bấm được giải phóng ngay, đéo bao giờ lo đơ App!
        self.root.after(10, self._execute_toggle_team)

    def _execute_toggle_team(self):
        try:
            # 1. Đổi màu nút Sân
            if self.team_color == "RED":
                self.team_color = "BLUE"
                self.team_btn.configure(text="San: XANH (BLUE)", fg_color="#1e88e5", hover_color="#1565c0")
            else:
                self.team_color = "RED"
                self.team_btn.configure(text="San: ĐO (RED)", fg_color="#d32f2f", hover_color="#b71c1c")
            
            self.simulation_path = None 
            
            # 2. Dọn rác
            for r in range(ROWS):
                for c in range(COLS):
                    for ov in self.grid_cells[r][c]["overlays"]: 
                        ov.destroy()
                    self.grid_cells[r][c]["overlays"].clear()
                    
            for door in self.door_cells:
                for ov in door["overlays"]:
                    ov.destroy()
                door["overlays"].clear()

            # 3. Lật ngược ID Cửa
            if hasattr(self, 'forced_door_index') and self.forced_door_index != -1:
                self.forced_door_index = 2 - self.forced_door_index
                for i, btn in enumerate(self.door_buttons):
                    if i == self.forced_door_index:
                        btn.configure(fg_color="#e74c3c", hover_color="#c0392b") 
                    else:
                        btn.configure(fg_color="#34495e", hover_color="#2c3e50")

            # 4. Refresh lại ID (Bản đã sửa ở Bước 1)
            self.refresh_grid_ids()

            # ... (Các đoạn trên giữ nguyên) ...

            # 5. ĐỒNG BỘ TAB VISION (TUYỆT ĐỐI KHÔNG DÙNG STRING_VAR NỮA)
            if hasattr(self, 'vision_seg_btn'):
                # Kiểm tra xem nút đang ở màu gì, nếu khác thì ép nó nảy màu trực tiếp
                if self.vision_seg_btn.get() != self.team_color:
                    self.vision_seg_btn.set(self.team_color)
            
            self.info_label.configure(text=f"Đã chuyển sang sân {self.team_color}.", text_color="blue")

            # 6. Tính đường (Nếu đang bật Live)
            if getattr(self, 'auto_update_path', False):
                self.smart_run()

        except Exception as e:
            # Nếu có lỗi ngầm, in ra màn hình chứ đéo cho phép treo App!
            print(f">>> [LỖI FATAL KHI ĐỔI SÂN]: {e}")
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
                # Đã loại bỏ lệnh ép kích thước width để chống Tkinter tự bóp dái (Deadlock đồ họa)
                lbl.configure(
                    text=f"ID:{cell_id}" if is_finish else str(cell_id),
                    text_color=id_text_color,
                    fg_color=id_bg_color
                )

    def get_cell_id(self, r, c):
        row_factor = (ROWS - 1 - r) * COLS 
        if self.team_color == "RED":
            col_offset = (COLS - 1 - c)
        else:
            col_offset = c
        return row_factor + col_offset + 1
    
    def on_closing(self):
        print("\n" + "🛑"*20)
        print(">> [ALGO] ĐANG DỌN DẸP ĐỂ QUAY VỀ MAIN...")
        
        # 1. Dừng quét QR
        self.stop_qr = True
        
        # 2. GIỮ NGUYÊN CỔNG UART (TUYỆT ĐỐI KHÔNG CLOSE!)
        try:
            from config_uart.sent_uart import ser
            if ser and not ser.is_open:
                ser.open() # Đảm bảo cổng luôn mở để Main còn nghe
                print(">> [OK] Đã đảm bảo thông van UART cho Main.")
            
            # Súc rửa bồn cầu: Xóa rác cũ để gói tin sau không bị kẹt
            if ser and ser.is_open:
                ser.reset_input_buffer()
                ser.reset_output_buffer()
        except: 
            pass

        # 3. KÍCH HOẠT LẠI TRẠNG THÁI CHỜ CHO MAIN
        try:
            from gui_tkinter import set_state, STATE_IDLE
            from uart_listener import uart_enable
            
            # Bật STATE_IDLE để Main biết là đang rảnh
            set_state["value"] = STATE_IDLE
            
            # QUAN TRỌNG: Mở khóa màng nhĩ cho luồng Lắng nghe
            uart_enable["value"] = True 
            print(">> [OK] Đã bật trạng thái IDLE và MỞ KHÓA lắng nghe UART.")
        except Exception as e:
            print(f">> [LỖI] Không thể reset trạng thái: {e}")

        # 4. Tắt Giao diện Algo
        try:
            self.root.quit()
            self.root.destroy()
            print(">> [OK] Đã đóng Giao Diện Algo.")
        except: 
            pass

        print(">> [HỆ THỐNG] ALGO ĐÃ RÚT LUI. MAIN ĐANG TRONG TRẠNG THÁI CHỜ... 🎧")
        print("🛑"*20 + "\n")
        
        # (ĐÃ XÓA SẠCH os._exit(0) ĐỂ KHÔNG BỊ CHẾT CHÙM FILE MAIN)

    def sent_and_close(self):
        # Bọc toàn bộ logic gửi UART vào một hàm con chạy ngầm
        def _send_task():
            # 1. Tự động tìm đường nếu chưa có
            if not getattr(self, 'simulation_path', None):
                print(">> [HỆ THỐNG] Chưa có đường đi, tự động chạy TÌM ĐƯỜNG...")
                self.root.after(0, self.smart_run)
                import time
                time.sleep(0.5)

            # =========================================================
            # 🛡️ BỘ XÀ BENG UART: CHỐNG CÂM SAU KHI STOP/IDLE
            # =========================================================
            try:
                from config_uart.sent_uart import ser
                if ser is not None:
                    if not ser.is_open:
                        try:
                            ser.open() # Tự động cạy van nếu lỡ bị đóng
                            print(">> [ALGO] Van UART đang đóng -> Đã tự động cạy mở thành công!")
                        except Exception as e:
                            print(f">> [ALGO ERROR] Cổng kẹt cứng đéo cạy được: {e}")
                    
                    if ser.is_open:
                        # Súc rửa bồn cầu: Xóa sạch rác cũ (slop) để gói tin mới không bị lỗi
                        ser.reset_input_buffer()
                        ser.reset_output_buffer()
                        print(">> [ALGO] Đã súc rửa đường ống UART sạch sẽ!")
            except Exception as e:
                print(f">> [UART FATAL] Lỗi xử lý cổng Serial: {e}")

            # =========================================================
            # 2. GỬI GÓI MODE RỪNG (MÃ 10)
            # =========================================================
            mode_val = 1 if self.forest_mode == "normal" else 2
            mode_name = "BÌNH THƯỜNG" if mode_val == 1 else "RETRY ZONE 2"
            
            print(f"   GỬI GÓI MODE RỪNG (ĐẦU TIÊN): {mode_name}")
            packet_mode = build_packet(2, 10, mode_val, 2, 2)
            
            try:
                send_packet_once(ser, packet_mode)
            except: pass
                
            import time
            time.sleep(0.5) 
                
            # 3. Gửi toàn bộ mảng đường đi
            self.send_uart()
            import time
            time.sleep(0.5) 

            # =========================================================
            # 4. GỬI GÓI CHIẾN THUẬT (MÃ 9)
            # =========================================================
            strat_val = 2 if self.is_fast_attack else 1
            strat_name = "THANG NHANH" if self.is_fast_attack else "CAY ĐIEM"
            
            print(f"   GUI GOI CHIEN THUAT (CUOI CUNG): {strat_name}")
            packet_strat = build_packet(2, 9, strat_val, 2, 2)
            
            try:
                send_packet_once(ser, packet_strat)
            except: pass
            
            # Cập nhật UI an toàn từ luồng ngầm
            def update_ui():
                self.info_label.configure(
                    text=f"Đa truyen Mode ({mode_name}) & Chien thuat ({strat_name}) thanh cong!", 
                    text_color="green"
                )
            self.root.after(0, update_ui)

        # Đẻ ra luồng ngầm để chạy (Tránh làm đơ App Tkinter)
        import threading
        threading.Thread(target=_send_task, daemon=True).start()

    # =========================================================================
    # UI: TOGGLE MODE, CELL CLICK, PLACE BLOCK, RESET
    # =========================================================================
    def toggle_mode(self, new_mode, button):
        if self.mode == new_mode:
            self.mode = "PLACE"
            if self.active_button:
                self.active_button.configure(fg_color=self.active_button.default_color)
            self.active_button = None
            self.info_label.configure(text="Tro lai che đo Dat khoi.")
        else:
            self.mode = new_mode
            if self.active_button:
                self.active_button.configure(fg_color=self.active_button.default_color)
            self.active_button = button
            button.default_color = button.cget("fg_color")
            button.configure(fg_color="yellow")
            
            if new_mode == "DELETE":
                self.info_label.configure(text="Che đo Xoa: Click vao nut so hoac o de xoa.")
            elif new_mode == "SELECT":
                self.info_label.configure(text="Che đo CHON: Click vào o de chon lam muc tieu.")

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
                self.info_label.configure(text=f"Da xoa tai ({r},{c})")
                
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
                self.info_label.configure(text=f"Đa BO CHON duong tai ({r},{c})")
                return

            if self.selected_targets:
                last_r, last_c = self.selected_targets[-1]
                dist = abs(r - last_r) + abs(c - last_c)
                if dist != 1:
                    self.info_label.configure(text=f"Loi: Ô ({r},{c}) không nằm cạnh ô trước đó!", text_color="red")
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

    def cost(self, r, c, virtual_grid=None):
        if not (0 <= r < ROWS and 0 <= c < COLS): return float('inf')
        cell = self.grid_cells[r][c]
        if cell["content"] and cell["content"]["number"] == 1:
            return 2  
        if cell["content"] and cell["content"]["number"] == 3:
            return float('inf')
        return 2  

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
            print(f"Loi luu cache: {e}")

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
            print(f"\n[CACHE] Đa luu cung {len(self.packets_cache)} goi tin vao Local!")
            
            # Mở khóa cho phép nhấn nút Phát Lại
            if hasattr(self, 'replay_cache_btn'):
                self.replay_cache_btn.configure(state="normal")
                
        except Exception as e:
            print(f"\n[CACHE ERROR] Không the luu file cache: {e}")
        # =====================================================================
    # =========================================================================
    # SMART RUN
    # =========================================================================
    def smart_run(self):
        self.auto_update_path = True 

        # Xóa rác trên Sa bàn
        for r in range(ROWS):
            for c in range(COLS):
                for ov in self.grid_cells[r][c]["overlays"]: 
                    ov.destroy()
                self.grid_cells[r][c]["overlays"].clear()
                
        # [VÁ LỖI MEMORY LEAK] BẮT BUỘC PHẢI DỌN SẠCH CẢ 3 Ô CỬA TẠI ĐÂY
        for door in self.door_cells:
            for ov in door["overlays"]:
                ov.destroy()
            door["overlays"].clear()

        if self.selected_targets:
            print("\n>>> CHẾ ĐỘ THỦ CÔNG (MANUAL) <<<")
            self.solve_manual_targets()
        else:
            print("\n>>> CHẾ ĐỘ TỰ ĐỘNG (AUTO) <<<")
            self.solve_auto_targets()

    # def solve_auto_targets(self):
    #     # 1. QUÉT MAP VÀ GOM KHỐI
    #     list_1s = []
    #     list_2s = []
    #     list_2s_at_entry = []   
    #     list_2s_on_board = []   

    #     for r in range(ROWS):
    #         for c in range(COLS):
    #             content = self.grid_cells[r][c]["content"]
    #             if content:
    #                 num = content["number"]
    #                 if num == 1:
    #                     list_1s.append((r, c))
    #                 elif num == 2:
    #                     list_2s.append((r, c))
    #                     if r == ROWS - 1:
    #                         list_2s_at_entry.append((r, c))
    #                     else:
    #                         list_2s_on_board.append((r, c))

    #     if not list_2s:
    #         if hasattr(self, 'forced_door_index') and self.forced_door_index != -1:
    #             self.solve_retry_empty(self.forced_door_index)
    #         else:
    #             self.info_label.configure(text="LỖI: Không có khối R2 nào trên sân.", text_color="red")
    #         return

    #     total_target = getattr(self, 'target_blocks', 4)
    #     print(f">>> Khối 2: {len(list_2s_at_entry)} tại bục, {len(list_2s_on_board)} trên sa bàn")

    #     # =========================================================================
    #     # 🎯 QUÉT ĐA VŨ TRỤ: MÔ PHỎNG TẤT CẢ CỬA VÀ MỌI CÚ LÁCH NGANG
    #     # =========================================================================
    #     allowed_starts = [self.forced_door_index] if (hasattr(self, 'forced_door_index') and self.forced_door_index != -1) else [0, 1, 2]
    #     valid_solutions = []

    #     for start_col in allowed_starts:
    #         # --- Xử lý gắp bục cho từng Cửa ---
    #         door_picked = None
    #         sim_list_2s = list(list_2s_on_board)

    #         if list_2s_at_entry:
    #             door_picked = min(list_2s_at_entry, key=lambda x: abs(x[1] - start_col))
    #             for entry in list_2s_at_entry:
    #                 if entry != door_picked:
    #                     sim_list_2s.append(entry)

    #         # Tính toán quỹ đạo chạy dưới gầm bàn
    #         door_path_segs = []
    #         current_door_col = door_picked[1] if door_picked else start_col

    #         if door_picked:
    #             target_col = door_picked[1]
    #             dp = [(DOOR_ROW, current_door_col)]
    #             door_path_segs.append((dp, door_picked))
    #             current_door_col = target_col

    #         # Đường leo lên sa bàn
    #         climb_dp = [(DOOR_ROW, current_door_col)]
    #         c = current_door_col
    #         while c != start_col:
    #             c += 1 if start_col > c else -1
    #             climb_dp.append((DOOR_ROW, c))
    #         climb_dp.append((ROWS - 1, start_col))

    #         # --- Sinh ra 9 con đường vật lý bắt đầu từ Cửa này ---
    #         all_paths = []
            
    #         # 1. Ủi thẳng
    #         p = []
    #         for r in range(ROWS - 1, -2, -1): p.append((r, start_col))
    #         all_paths.append(p)
            
    #         # 2. Tạt ngang (Max 1 lần bẻ lái)
    #         for shift_dir in [-1, 1]:
    #             shifted_col = start_col + shift_dir
    #             if 0 <= shifted_col < COLS:
    #                 for shift_row in range(ROWS - 1, -1, -1):
    #                     p = []
    #                     curr_c = start_col
    #                     for r in range(ROWS - 1, -2, -1):
    #                         p.append((r, curr_c))
    #                         # Thực hiện cua ngang (Crab Walk) tại hàng này
    #                         if r == shift_row:
    #                             curr_c = shifted_col
    #                             p.append((r, curr_c)) 
    #                     all_paths.append(p)

    #         # --- Chạy mô phỏng trên từng con đường ---
    #         for path_coords in all_paths:
    #             # 🚨 LUẬT GIAO THÔNG THỰC TẾ: CHỈ KIỂM TRA LÊN CÁI BÁNH XE!
    #             is_valid = True
    #             r1_stepped = 0 # Đếm số khối R1 thực tế mà bánh xe dẫm lên

    #             for r, c in path_coords:
    #                 if r == -1: continue
    #                 cell = self.grid_cells[r][c]["content"]
    #                 if not cell: continue
                    
    #                 # 1. Bánh xe cán trúng Khối Fake -> Rớt đài -> Bỏ đường này!
    #                 if cell["number"] == 3: 
    #                     is_valid = False
    #                     break
                        
    #                 # 2. Bánh xe cán trúng R1 -> Cộng dồn. Dẫm >= 2 cục R1 trên quỹ đạo -> Kẹt -> BỎ!
    #                 if cell["number"] == 1: 
    #                     r1_stepped += 1
    #                     if r1_stepped >= 2:
    #                         is_valid = False
    #                         break

    #             if not is_valid: continue # Chỉ vứt đường đi, đéo vứt nguyên cái cột

    #             picked = []
    #             sim_path_temp = []
    #             current_segment = [path_coords[0]]
    #             path_failed = False
    #             # target_blocks_on_board = total_target - (1 if door_picked else 0)

    #             # for i in range(len(path_coords) - 1):
    #             #     curr_r, curr_c = path_coords[i]
    #             #     next_r, next_c = path_coords[i+1]

    #             #     # Quét tay Trước, Trái, Phải
    #             #     for dr, dc in [(-1, 0), (0, -1), (0, 1)]:
    #             #         tr, tc = curr_r + dr, curr_c + dc
    #             #         if (tr, tc) in sim_list_2s and (tr, tc) not in picked:
    #             #             if len(picked) < target_blocks_on_board:
    #             #                 picked.append((tr, tc))
    #             #                 sim_path_temp.append((current_segment.copy(), (tr, tc)))
    #             #                 current_segment = [(curr_r, curr_c)]

    #             #     # Húc phải R2 thì gắp, đầy túi mà húc thì Rớt đài
    #             #     if next_r != -1 and (next_r, next_c) in sim_list_2s and (next_r, next_c) not in picked:
    #             #         if len(picked) < target_blocks_on_board:
    #             #             picked.append((next_r, next_c))
    #             #             sim_path_temp.append((current_segment.copy(), (next_r, next_c)))
    #             #             current_segment = [(curr_r, curr_c)]
    #             #         else:
    #             #             path_failed = True # Lỗi Húc Khối
    #             #             break
    #             #     # =====================================================
    #             #     # 💡 LUẬT KHÓA MỎM & SINH TỒN (2, 3, 4 CỤC)
    #             #     # =====================================================
    #             #     desired_target = getattr(self, 'target_blocks', 4) # Lấy KPI từ UI
    #             #     bag_capacity = 4 # Sức chứa vật lý của xe
                    
    #             #     door_count = 1 if door_picked else 0
    #             #     max_reach_limit = desired_target - door_count   # Giới hạn vươn tay gắp
    #             #     max_survive_limit = bag_capacity - door_count   # Giới hạn há mỏm nuốt để sống

    #             #     for i in range(len(path_coords) - 1):
    #             #         curr_r, curr_c = path_coords[i]
    #             #         next_r, next_c = path_coords[i+1]

    #             #         # 1. QUÉT TAY: Chỉ vươn tay nếu chưa đủ KPI (desired_target)
    #             #         for dr, dc in [(-1, 0), (0, -1), (0, 1)]:
    #             #             tr, tc = curr_r + dr, curr_c + dc
    #             #             if (tr, tc) in sim_list_2s and (tr, tc) not in picked:
    #             #                 if len(picked) < max_reach_limit:
    #             #                     picked.append((tr, tc))
    #             #                     sim_path_temp.append((current_segment.copy(), (tr, tc)))
    #             #                     current_segment = [(curr_r, curr_c)]

    #             #         # 2. BƯỚC LÊN KHỐI: Nếu dẫm phải khối trên đường -> Bắt buộc nuốt để sống
    #             #         if next_r != -1 and (next_r, next_c) in sim_list_2s and (next_r, next_c) not in picked:
    #             #             if len(picked) < max_survive_limit:
    #             #                 picked.append((next_r, next_c))
    #             #                 sim_path_temp.append((current_segment.copy(), (next_r, next_c)))
    #             #                 current_segment = [(curr_r, curr_c)]
    #             #             else:
    #             #                 path_failed = True # Bụng đã chứa 4 cục mà vẫn dẫm -> Tông khối!
    #             #                 break
    #             #     current_segment.append((next_r, next_c))

                
                
    #             sim_path_temp.append((current_segment.copy(), "FINISH"))

    #             # Tính Cost & Ưu Tiên Rẽ Muộn (Late Turn)
    #             shifts = 0
    #             shift_row_val = 0
    #             for i in range(len(path_coords)-1):
    #                 if path_coords[i][1] != path_coords[i+1][1]:
    #                     shifts += 1
    #                     shift_row_val = path_coords[i][0]
    #                     break

    #             team_bonus = 0
    #             if shifts == 0: 
    #                 if self.team_color == "RED" and start_col == 2: team_bonus = -5
    #                 elif self.team_color == "BLUE" and start_col == 0: team_bonus = -5

    #             cost = len(path_coords) * 10 + shifts * 15 + shift_row_val + team_bonus
    #             total_picked_this_path = len(picked) + (1 if door_picked else 0)

    #             valid_solutions.append({
    #                 "start_col": start_col,
    #                 "door_picked": door_picked,
    #                 "door_path_segs": door_path_segs,
    #                 "climb_dp": climb_dp,
    #                 "picked_count": total_picked_this_path,
    #                 "cost": cost,
    #                 "sim_path": sim_path_temp,
    #                 "ordered_entry": [door_picked] if door_picked else []
    #             })

    #     if not valid_solutions:
    #         self.info_label.configure(text="LỖI: Rừng bít bùng, đéo lách được hoặc húc khối!", text_color="red")
    #         return

        # =========================================================================
        # 🚨 ĐẢM BẢO YÊU CẦU "BUỘC PHẢI TÌM ĐƯỜNG PICK >= 2 CỤC" 
        # =========================================================================
        # max_possible_picks = min(total_target, len(list_2s))
        # if max_possible_picks >= 2:
        #     filtered_sols = [s for s in valid_solutions if s["picked_count"] >= 2]
        #     if filtered_sols:
        #         valid_solutions = filtered_sols 
        #     else:
        #         print(">>> [CẢNH BÁO] Các ngõ lách đều kẹt, không thể ăn >=2 cục an toàn!")

        # # 🏆 CHỐT ĐƠN
        # valid_solutions.sort(key=lambda x: (-x["picked_count"], x["cost"]))
        # best_solution = valid_solutions[0]
        
        # forest_path = best_solution["sim_path"]
        # door_path_segs = best_solution["door_path_segs"]
        # climb_dp = best_solution["climb_dp"]
        # best_col = best_solution["start_col"]
        # ordered_entry = best_solution["ordered_entry"]

        # sim_path = []
        # sim_path.extend(door_path_segs)
        
        # if forest_path:
        #     first_seg_path, first_seg_act = forest_path[0]
        #     merged_path = climb_dp[:-1] + first_seg_path
        #     forest_path[0] = (merged_path, first_seg_act)
            
        # sim_path.extend(forest_path)

        # # --- LƯU KẾT QUẢ ---
        # self.simulation_path = sim_path
        # self.best_ignored_set = []
        # self._best_col = best_col

        # picked_ids = [self.get_cell_id(*a) for _, a in sim_path if isinstance(a, tuple) and 0 <= a[0] < ROWS]
        # entry_ids = [self.get_cell_id(*p) for p in ordered_entry]

        # print(f"-> Chọn Cửa: Cột {best_col} (Team {self.team_color})")
        # print(f"-> Gắp bục: {entry_ids} | Gắp sa bàn: {[i for i in picked_ids if i not in entry_ids]}")
        # self.visualize_result(sim_path, [])
        # self.info_label.configure(text=f"AUTO: Bò -> Cửa {best_col} -> Vét máng gắp {picked_ids}.")

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
    # =========================================================================
    # 🧠 BỘ NÃO SỐ 1: TÌM ĐƯỜNG ĐA VŨ TRỤ (CHỌN LỐI THOÁT TỐI ƯU)
    # =========================================================================
    def solve_auto_targets(self):
        list_1s = []
        list_2s = []
        list_2s_at_entry = []   
        list_2s_on_board = []   
        col_r1_counts = {0: 0, 1: 0, 2: 0}

        for r in range(ROWS):
            for c in range(COLS):
                content = self.grid_cells[r][c]["content"]
                if content:
                    num = content["number"]
                    if num == 1:
                        list_1s.append((r, c))
                        col_r1_counts[c] += 1
                    elif num == 2:
                        list_2s.append((r, c))
                        if r == ROWS - 1:
                            list_2s_at_entry.append((r, c))
                        else:
                            list_2s_on_board.append((r, c))

        if not list_2s:
            if hasattr(self, 'forced_door_index') and self.forced_door_index != -1:
                self.solve_retry_empty(self.forced_door_index)
            else:
                self.info_label.configure(text="LỖI: Không có khối R2 nào trên sân.", text_color="red")
            return

        total_target = getattr(self, 'target_blocks', 4)
        print(f">>> Khối 2: {len(list_2s_at_entry)} tại bục, {len(list_2s_on_board)} trên sa bàn")

        allowed_starts = [self.forced_door_index] if (hasattr(self, 'forced_door_index') and self.forced_door_index != -1) else [0, 1, 2]
        valid_solutions = []

        for start_col in allowed_starts:
            
            # CHỈ SỬA ĐÚNG CHỖ NÀY: Dùng vòng lặp quét qua tất cả các cục dưới bục
            # Không thêm thắt bất cứ biến rác nào khác!
            possible_door_picks = list_2s_at_entry if list_2s_at_entry else [None]
            
            for door_picked in possible_door_picks:
                sim_list_2s = list(list_2s_on_board)

                if list_2s_at_entry:
                    for entry in list_2s_at_entry:
                        if entry != door_picked:
                            sim_list_2s.append(entry)

                door_path_segs = []
                current_door_col = door_picked[1] if door_picked else start_col

                if door_picked:
                    target_col = door_picked[1]
                    dp = [(DOOR_ROW, current_door_col)]
                    c = current_door_col
                    while c != target_col:
                        c += 1 if target_col > c else -1
                        dp.append((DOOR_ROW, c))
                    door_path_segs.append((dp, door_picked))
                    current_door_col = target_col

                climb_dp = [(DOOR_ROW, current_door_col)]
                c = current_door_col
                while c != start_col:
                    c += 1 if start_col > c else -1
                    climb_dp.append((DOOR_ROW, c))
                climb_dp.append((ROWS - 1, start_col))

                all_paths = []
                
                p = []
                for r in range(ROWS - 1, -2, -1): p.append((r, start_col))
                all_paths.append(p)
                
                for shift_dir in [-1, 1]:
                    shifted_col = start_col + shift_dir
                    if 0 <= shifted_col < COLS:
                        for shift_row in range(ROWS - 1, -1, -1):
                            p = []
                            curr_c = start_col
                            for r in range(ROWS - 1, -2, -1):
                                p.append((r, curr_c))
                                if r == shift_row:
                                    curr_c = shifted_col
                                    p.append((r, curr_c)) 
                            all_paths.append(p)

                for path_coords in all_paths:
                    is_valid = True
                    r1_stepped = 0 

                    for r, c in path_coords:
                        if r == -1: continue
                        cell = self.grid_cells[r][c]["content"]
                        if not cell: continue
                        
                        if cell["number"] == 3: 
                            is_valid = False; break
                        if cell["number"] == 1: 
                            r1_stepped += 1
                            if r1_stepped >= 2:
                                is_valid = False; break

                    if not is_valid: continue 

                    picked = []
                    sim_path_temp = []
                    current_segment = [path_coords[0]]
                    path_failed = False
                    
                    # CỤC NÀY CỦA MÀY GIỮ NGUYÊN 100%, ĐÉO SỬA GÌ HẾT
                    # =====================================================
                    # 💡 LUẬT KHÓA MỎM & SINH TỒN (NỐI VỚI NÚT BẤM)
                    # =====================================================
                    desired_target = getattr(self, 'target_blocks', 3) # Đọc mục tiêu từ Nút bấm
                    bag_capacity = 4 # Sức chứa tối đa của bụng xe
                    
                    door_count = 1 if door_picked else 0
                    max_reach_limit = desired_target - door_count   # Giới hạn vươn tay gắp
                    max_survive_limit = bag_capacity - door_count   # Giới hạn há mỏm nuốt để sống sót

                    for i in range(len(path_coords) - 1):
                        curr_r, curr_c = path_coords[i]
                        next_r, next_c = path_coords[i+1]

                        # 1. QUÉT TAY: Chỉ vươn tay nếu chưa đủ KPI (max_reach_limit)
                        # 🔥 CHỈNH ƯU TIÊN: Trái (0,-1) -> Phải (0,1) -> Trước (-1,0)
                        for dr, dc in [(0, -1), (0, 1), (-1, 0)]:
                            tr, tc = curr_r + dr, curr_c + dc
                            if (tr, tc) in sim_list_2s and (tr, tc) not in picked:
                                if len(picked) < max_reach_limit:
                                    picked.append((tr, tc))
                                    sim_path_temp.append((current_segment.copy(), (tr, tc)))
                                    current_segment = [(curr_r, curr_c)]

                        # 2. BƯỚC LÊN KHỐI: Lỡ dẫm trúng cản đường -> Nuốt để sống (max_survive_limit)
                        if next_r != -1 and (next_r, next_c) in sim_list_2s and (next_r, next_c) not in picked:
                            if len(picked) < max_survive_limit:
                                picked.append((next_r, next_c))
                                sim_path_temp.append((current_segment.copy(), (next_r, next_c)))
                                current_segment = [(curr_r, curr_c)]
                            else:
                                path_failed = True # Đầy túi (4) mà vẫn dẫm trúng -> Húc khối phạm luật!
                                break

                        current_segment.append((next_r, next_c))

                    if path_failed: continue
                    sim_path_temp.append((current_segment.copy(), "FINISH"))

                    shifts = 0
                    shift_row_val = 0
                    for i in range(len(path_coords)-1):
                        if path_coords[i][1] != path_coords[i+1][1]:
                            shifts += 1
                            shift_row_val = path_coords[i][0]
                            break

                    cost = len(path_coords) * 10 + shifts * 15 + shift_row_val
                    
                    total_picked_this_path = len(picked) + (1 if door_picked else 0)
                    end_col = path_coords[-1][1] 

                    valid_solutions.append({
                        "start_col": start_col,
                        "end_col": end_col,
                        "door_picked": door_picked,
                        "door_path_segs": door_path_segs,
                        "climb_dp": climb_dp,
                        "picked_count": total_picked_this_path,
                        "cost": cost,
                        "sim_path": sim_path_temp,
                        "ordered_entry": [door_picked] if door_picked else []
                    })

        if not valid_solutions:
            self.info_label.configure(text="LỖI: Rừng bít bùng, đéo lách được hoặc húc khối!", text_color="red")
            return

        max_possible_picks = min(total_target, len(list_2s))
        if max_possible_picks >= 2:
            filtered_sols = [s for s in valid_solutions if s["picked_count"] >= 2]
            if filtered_sols:
                valid_solutions = filtered_sols 
            else:
                print(">>> [CẢNH BÁO] Các ngõ lách đều kẹt, không thể ăn >=2 cục an toàn!")

        # =========================================================================
        # 🏆 CHỐT ĐƠN: THUẬT TOÁN PHÂN XỬ TỐI THƯỢNG (SÂN ĐỎ VÀ SÂN XANH)
        # =========================================================================
        def get_sort_key(sol):
            if self.team_color == "RED":
                dist_to_exit = abs(sol["end_col"] - 2) # Sân Đỏ: Ép dạt Cột 2
            else:
                dist_to_exit = abs(sol["end_col"] - 0) # Sân Xanh: Ép dạt Cột 0
                
            # ĐÂY LÀ CHÌA KHÓA: Phạt điểm thằng nào gắp sai số lượng KPI!
            pick_penalty = abs(sol["picked_count"] - desired_target)

            return (
                pick_penalty,         # Ưu tiên 1: Lệch KPI thì Penalty cao -> RỚT HẠNG!
                -sol["picked_count"], # Ưu tiên 2: Nếu kẹt đường buộc phải Penalty, thì thà gắp nhiều hơn
                sol["cost"],          # Ưu tiên 3: Đường lách mượt nhất
                dist_to_exit          # Ưu tiên 4: Góc thoát Vùng 3 gần nhất
            )

        valid_solutions.sort(key=get_sort_key)
        best_solution = valid_solutions[0]
        
        forest_path = best_solution["sim_path"]
        door_path_segs = best_solution["door_path_segs"]
        climb_dp = best_solution["climb_dp"]
        best_col = best_solution["start_col"]
        ordered_entry = best_solution["ordered_entry"]

        sim_path = []
        sim_path.extend(door_path_segs)
        
        if forest_path:
            first_seg_path, first_seg_act = forest_path[0]
            merged_path = climb_dp[:-1] + first_seg_path
            forest_path[0] = (merged_path, first_seg_act)
            
        sim_path.extend(forest_path)

        self.simulation_path = sim_path
        self.best_ignored_set = []
        self._best_col = best_col

        picked_ids = [self.get_cell_id(*a) for _, a in sim_path if isinstance(a, tuple) and 0 <= a[0] < ROWS]
        entry_ids = [self.get_cell_id(*p) for p in ordered_entry]

        print(f"-> Chọn Cửa: Cột {best_col} (Team {self.team_color})")
        print(f"-> Gắp bục: {entry_ids} | Gắp sa bàn: {[i for i in picked_ids if i not in entry_ids]}")
        self.visualize_result(sim_path, [])
        self.info_label.configure(text=f"AUTO: Bò -> Cửa {best_col} -> Vét máng gắp {picked_ids}.")


    # =========================================================================
    # 📡 BỘ NÃO SỐ 2: XỬ LÝ VÀ BẮN UART (CHUẨN VỚI CƠ KHÍ STM32)
    # =========================================================================
    def process_and_send_uart(self, simulation_path):
        if not ser or not ser.is_open:
            print(f"\n[UART ERROR] UART port không sẵn sàng")
            self.info_label.configure(text="Lỗi UART: Port không mở")
            return
            
        intended_targets = []
        for seg_path, seg_act in simulation_path:
            if isinstance(seg_act, tuple):
                intended_targets.append(self.get_cell_id(seg_act[0], seg_act[1]))
        
        first_col_temp = None
        for seg_path, seg_act in simulation_path:
            for pos in seg_path:
                if pos[0] == DOOR_ROW:
                    first_col_temp = pos[1]
                    break
            if first_col_temp is not None: break
            
        if first_col_temp is None: first_col_temp = self._best_col if hasattr(self, '_best_col') else 1
        intended_targets.append(self.get_cell_id(ROWS - 1, first_col_temp))
        
        print("=" * 60)
        print(f"BẮT ĐẦU GỬI UART — TEAM {self.team_color}")
        print("=" * 60)

        # =====================================================================
        # 1. GỬI GÓI MODE RỪNG TRƯỚC TIÊN (MÃ 10)
        # =====================================================================
        mode_val = 1 if getattr(self, 'forest_mode', 'normal') == "normal" else 2
        mode_name = "BÌNH THƯỜNG" if mode_val == 1 else "RETRY ZONE 2"
        print(f"\n  ├─ [MODE PACKET] Gửi: (2, 10, {mode_val}, 2, 2) — {mode_name}")
        ser.write(build_packet(2, 10, mode_val, 2, 2))
        time.sleep(0.3)

        # =====================================================================
        # 2. GỬI GÓI CHIẾN THUẬT (MÃ 9)
        # =====================================================================
        strat_val = 2 if getattr(self, 'is_fast_attack', True) else 1
        strat_name = "THẮNG NHANH" if strat_val == 2 else "CÀY ĐIỂM"
        print(f"  ├─ [STRAT PACKET] Gửi: (2, 9, {strat_val}, 2, 2) — {strat_name}")
        ser.write(build_packet(2, 9, strat_val, 2, 2))
        time.sleep(0.3)

        has_sent_start = False
        has_climbed    = False
        traveled_path  = []
        picked_blocks  = []
        count_rb2      = 2 # Tính 2 gói Mode và Strat ở trên

        first_door_col = None
        for seg_path, seg_act in simulation_path:
            for pos in seg_path:
                if pos[0] == DOOR_ROW:
                    first_door_col = pos[1]
                    break
            if first_door_col is not None: break

        if first_door_col is None:
            first_door_col = self._best_col if hasattr(self, '_best_col') else 1

        start_block_id = self.get_cell_id(ROWS - 1, first_door_col)

        start_packet_str = f"(2, 2, 10, 10, {start_block_id})"
        print(f"\n>>> GÓI TIN BẮT ĐẦU: {start_packet_str}")
        
        self.info_label.configure(
            text=f"GÓI BẮT ĐẦU: {start_packet_str}\nRobot đi thẳng tới cửa ID={start_block_id}"
        )
        self.root.update()

        # =====================================================================
        # 3. GỬI GÓI START VÀO CỬA (MÃ 2, P1=10)
        # =====================================================================
        print(f"\n  ├─ [START PACKET] Gửi: {start_packet_str}")
        ser.write(build_packet(2, 2, 10, 10, start_block_id))
        count_rb2 += 1
        time.sleep(0.3)
        has_sent_start = True

        for seg_idx, (segment_path, segment_action) in enumerate(simulation_path):
            print(f"\n[SEGMENT {seg_idx}] Action={segment_action} | Path={segment_path}")

            if not traveled_path:
                traveled_path.extend(segment_path)
            else:
                last_pos = traveled_path[-1]
                first_pos = segment_path[0]
                if last_pos != first_pos:
                    segment_path.insert(0, last_pos)
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
                        
                    elif cell_entry["content"] and cell_entry["content"]["number"] == 2:
                        if entry_id in intended_targets and entry_id not in picked_blocks:
                            print(f"  ├─ [KHỐI 2 BỤC] Gửi: (2, 2, 0, 1, {entry_id}) — Gắp thẳng trước khi leo")
                            time.sleep(0.3)
                            ser.write(build_packet(2, 2, 0, 1, entry_id))
                            count_rb2 += 1
                            picked_blocks.append(entry_id)
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
                    
                    if dr == -1 and dc == 0: move_cmd = 1  
                    elif dr == 0 and dc == -1: move_cmd = 2  
                    elif dr == 0 and dc == 1: move_cmd = 3  
                    else: continue

                    cell_next = self.grid_cells[next_r][next_c]

                    if cell_next["content"] and cell_next["content"]["number"] == 1:
                        print(f"  │  ├─ [KHỐI 1] Gửi: (1, 2, 0, 0, {step_id}) — Phá khối")
                        time.sleep(0.3)
                        ser.write(build_packet(1, 2, 0, 0, step_id))
                        time.sleep(0.3)

                    elif cell_next["content"] and cell_next["content"]["number"] == 2:
                        if step_id in intended_targets and step_id not in picked_blocks:
                            print(f"  │  ├─ [KHỐI 2] Gửi: (2, 2, 0, {move_cmd}, {step_id}) — Gắp trước khi đi")
                            time.sleep(0.3)
                            ser.write(build_packet(2, 2, 0, move_cmd, step_id))
                            count_rb2 += 1
                            picked_blocks.append(step_id)
                            time.sleep(0.5)

                    time.sleep(0.3)
                    ser.write(build_packet(2, 2, move_cmd, 4, step_id))
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
                continue

            r_end, c_end = segment_path[-1]
            dr_act = tr - r_end
            dc_act = tc - c_end

            if r_end == DOOR_ROW and tr == ROWS - 1 and c_end == tc:
                print(f"  └─ [PICK DOOR] Gửi: (2, 2, 0, 1, {action_id}) — Vươn lên gắp từ cửa")
                time.sleep(0.3)
                ser.write(build_packet(2, 2, 0, 1, action_id))
                count_rb2 += 1
                time.sleep(0.3)
                picked_blocks.append(action_id)
                continue

            if dr_act == -1 and dc_act == 0: action_cmd = 1 
            elif dr_act == 0 and dc_act == -1: action_cmd = 2 
            elif dr_act == 0 and dc_act == 1: action_cmd = 3 
            elif dr_act == 0 and dc_act == 0: action_cmd = 1 
            else: action_cmd = 1

            desc = ["?", "Thẳng", "Trái", "Phải", "0 Gắp"][action_cmd]
            print(f"  └─ [PICK]      Gửi: (2, 2, 0, {action_cmd}, {action_id}) — Gắp {desc}")
            time.sleep(0.3)
            ser.write(build_packet(2, 2, 0, action_cmd, action_id))
            count_rb2 += 1
            time.sleep(0.3)
            picked_blocks.append(action_id)

        # =====================================================================
        # 4. GỬI GÓI KẾT THÚC (MÃ 20) ĐỂ XE BIẾT ĐƯỜNG LÙI XUỐNG VÙNG 3
        # Lỗi cũ là do dính tọa độ r = -1 nên đéo in ra. Đã lọc rác tọa độ!
        # =====================================================================
        if traveled_path:
            # Lọc vứt mẹ cái hàng r = -1 đi, chỉ lấy tọa độ còn nằm trong Sa Bàn
            valid_path = [p for p in traveled_path if 0 <= p[0] < ROWS and 0 <= p[1] < COLS]
            if valid_path:
                last_r, last_c = valid_path[-1]
                last_id = self.get_cell_id(last_r, last_c)
                if last_id in [10, 11, 12]:
                    print(f"\n  ├─ [END PACKET] Gửi: (2, 2, 20, 20, {last_id}) — Hoàn thành!")
                    ser.write(build_packet(2, 2, 20, 20, last_id))
                    count_rb2 += 1
                    time.sleep(0.1)

        print("\n" + "=" * 60)
        print(f"HOÀN THÀNH — {count_rb2} gói tin (id_rb=2)")
        print("=" * 60)
        self.info_label.configure(
            text=f"✓ Gửi xong ({self.team_color}): {count_rb2} gói\n"
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
            self.info_label.configure(text="[LỖI] Chua có goi tin Cache UI nao!")
            return
            
        try:
            with open(cache_file, "r") as f:
                data = json.load(f)
            
            # --- 1. DỌN SẠCH SÂN TRƯỚC KHI DỰNG LẠI ---
            self.reset_grid()
            
            # --- 2. KHÔI PHỤC TEAM COLOR VÀ ID Ô ---
            self.team_color = data.get("team_color", "RED")
            if self.team_color == "RED":
                self.team_btn.configure(text="San: ĐO (RED)", fg_color="#d32f2f")
            else:
                self.team_btn.configure(text="San: XANH (BLUE)", fg_color="#1e88e5")
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
    def solve_retry_empty(self, col):
        """Hàm mới: Ép chạy thẳng ra khỏi rừng khi không có khối"""
        print(f">>> [RETRY] ĐƯỜNG TRỐNG -> ỦI THẲNG RA KHỎI RỪNG TẠI CỘT {col}")
        
        # Vẽ đường đi thẳng 1 lèo từ Cửa lên đỉnh sa bàn
        path = [(DOOR_ROW, col)]
        for r in range(ROWS - 1, -1, -1):
            path.append((r, col))
        
        # Cấu trúc y hệt Algo cũ, action là "FINISH"
        self.simulation_path = [(path, "FINISH")]
        self._best_col = col
        self.best_ignored_set = []
        
        # Gọi hàm hiển thị giao diện cũ
        self.visualize_result(self.simulation_path, [])
        self.info_label.configure(
            text=f"RETRY: Ép cửa {chr(65+col)} ➔ Ủi thẳng không gắp. Sẵn sàng bắn UART.", 
            text_color="#e74c3c"
        )       
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
    # def setup_matrix_tab(self):
    #     self.matrix_selected = {i: False for i in range(1, 7)}
    #     self.matrix_buttons = {}

    #     ctk.CTkLabel(
    #         self.tab_matrix, text="Bảng Điều Khiển Gắp Khối Vùng 3",
    #         font=("Segoe UI", 22, "bold"), text_color="#1e293b"
    #     ).pack(pady=(20, 5))

    #     self.matrix_status = ctk.CTkLabel(self.tab_matrix, text="Sẵn sàng gửi UART", font=("Segoe UI", 14), text_color="#64748b")
    #     self.matrix_status.pack(pady=(0, 5))

    #     card = ctk.CTkFrame(self.tab_matrix, corner_radius=20, fg_color="#ffffff")
    #     card.pack(padx=20, pady=5, fill="both", expand=True)

    #     btn_frame = ctk.CTkFrame(card, fg_color="transparent")
    #     btn_frame.pack(expand=True, pady=15)

    #     for i in range(1, 7):
    #         row = 1 if i <= 3 else 0   
    #         col = (i - 1) % 3
    #         btn = ctk.CTkButton(
    #             btn_frame, text=str(i), width=90, height=90, corner_radius=16,
    #             font=("Segoe UI", 26, "bold"), text_color="white",
    #             fg_color="#4f46e5", hover_color="#6366f1",
    #             command=lambda n=i: self.toggle_matrix(n)
    #         )
    #         btn.grid(row=row, column=col, padx=15, pady=10)
    #         self.matrix_buttons[i] = btn

    #     bottom_frame = ctk.CTkFrame(self.tab_matrix, fg_color="transparent")
    #     bottom_frame.pack(pady=(5, 15))

    #     ctk.CTkButton(
    #         bottom_frame, text="✔ CHỐT GỬI LỆNH", width=180, height=45, corner_radius=14,
    #         font=("Segoe UI", 16, "bold"), fg_color="#16a34a", hover_color="#15803d",
    #         command=self.on_matrix_confirm
    #     ).grid(row=0, column=0, padx=10)

    #     ctk.CTkButton(
    #         bottom_frame, text="↺ Reset", width=120, height=45, corner_radius=14,
    #         font=("Segoe UI", 16, "bold"), fg_color="#dc2626", hover_color="#b91c1c",
    #         command=self.on_matrix_reset
    #     ).grid(row=0, column=1, padx=10)

    # def toggle_matrix(self, n):
    #     self.matrix_selected[n] = not self.matrix_selected[n]
    #     if self.matrix_selected[n]:
    #         self.matrix_buttons[n].configure(fg_color="#f59e0b", hover_color="#d97706")
    #     else:
    #         self.matrix_buttons[n].configure(fg_color="#4f46e5", hover_color="#6366f1")

    # def on_matrix_reset(self):
    #     for i in range(1, 7):
    #         self.matrix_selected[i] = False
    #         self.matrix_buttons[i].configure(fg_color="#4f46e5", hover_color="#6366f1")
    #     self.matrix_status.configure(text="Đã Reset lựa chọn", text_color="#64748b")

    # def on_matrix_confirm(self):
    #     col_map = {1: 1, 2: 2, 3: 3, 4: 1, 5: 2, 6: 3}
    #     entry = [0, 0, 0]
    #     for n in range(1, 7):
    #         if self.matrix_selected[n]:
    #             idx = col_map[n] - 1
    #             entry[idx] = n

    #     threading.Thread(
    #         target=self.send_uart_matrix,
    #         args=(entry[0], entry[1], entry[2]),
    #         daemon=True
    #     ).start()

    # def send_uart_matrix(self, e1, e2, e3):
    #     try:
    #         packet = build_packet(2, 3, e1, e2, e3)
    #         send_packet_once(ser, packet)
    #         self.matrix_status.configure(text=f"Đã gửi UART Vùng 3: {e1} - {e2} - {e3}", text_color="#16a34a")
    #         print(f"[MATRIX] Đã gửi lệnh Vùng 3: 2, 3, {e1}, {e2}, {e3}")
    #     except Exception as e:
    #         self.matrix_status.configure(text="LỖI UART: Kiểm tra cáp kết nối", text_color="#dc2626")
    #         print("UART Error:", e)

    # # =========================================================================
    # # CÔNG TẮC BẬT/TẮT LẮNG NGHE UART (KHÔNG ĐẺ LUỒNG MỚI CHỐNG CRASH)
    # # =========================================================================
    # def toggle_main_listener(self):
    #     try:
    #         # Import cờ điều khiển từ file uart_listener của mày
    #         from uart_listener import uart_enable
            
    #         # Đảo trạng thái công tắc
    #         self.is_listening = not self.is_listening
            
    #         if self.is_listening:
    #             # TRẠNG THÁI 1: BẬT
    #             uart_enable["value"] = True
    #             self.listen_btn.configure(
    #                 text="🎧 ĐANG LẮNG NGHE...", 
    #                 fg_color="#27ae60", hover_color="#2ecc71"
    #             )
    #             self.info_label.configure(text="✓ Đã MỞ kết nối Lắng nghe UART!", text_color="green")
    #             print(">> [UART Algo] Đã MỞ van lắng nghe.")
    #         else:
    #             # TRẠNG THÁI 2: TẮT
    #             uart_enable["value"] = False
    #             self.listen_btn.configure(
    #                 text="🎧 BẬT LẮNG NGHE (MAIN)", 
    #                 fg_color="#8e44ad", hover_color="#732d91"
    #             )
    #             self.info_label.configure(text="⏸ Đã TẠM DỪNG Lắng nghe UART.", text_color="#f39c12")
    #             print(">> [UART Algo] Đã ĐÓNG van lắng nghe.")
                
    #     except Exception as e:
    #         self.info_label.configure(text=f"LỖI Công tắc Lắng Nghe: {e}", text_color="red")
    #         print(f">> LỖI: {e}")
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

    def toggle_door_selection(self, index):
        """Hàm xử lý nhấn nút Ép Cửa: Nhấn 1 lần để chọn, nhấn lại để hủy"""
        if self.forced_door_index == index:
            self.forced_door_index = -1
            print(f">> [RETRY] Đã BỎ ÉP CỬA. Quay về chế độ AUTO.")
        else:
            self.forced_door_index = index
            print(f">> [RETRY] Đã ÉP CỬA {['A','B','C'][index]}.")

        # Cập nhật màu sắc nút để mày nhìn cho rõ
        for i, btn in enumerate(self.door_buttons):
            if i == self.forced_door_index:
                btn.configure(fg_color="#e74c3c", hover_color="#c0392b") # Màu Đỏ rực khi chọn
            else:
                btn.configure(fg_color="#34495e", hover_color="#2c3e50") # Màu tối khi không chọn
        
        # Nếu đang bật 'Nhận Live', ép nó vẽ lại đường đi luôn cho sướng mắt
        if getattr(self, 'auto_update_path', False):
            self.smart_run()
    def set_kpi(self, val):
        """Xử lý khi bấm 3 nút KPI"""
        self.target_blocks = val
        
        # Đổi màu: Nút nào được bấm thì sáng lên, 2 nút kia tối đi
        self.btn_kpi_2.configure(fg_color="#e74c3c" if val == 2 else "#34495e")
        self.btn_kpi_3.configure(fg_color="#27ae60" if val == 3 else "#34495e")
        self.btn_kpi_4.configure(fg_color="#8e44ad" if val == 4 else "#34495e")
        
        self.info_label.configure(text=f"Đã chốt mục tiêu: Săn {val} khối!", text_color="blue")
        print(f">> [CHIẾN THUẬT] Chuyển sang chế độ: SĂN {val} KHỐI")
        
        # Nếu đang nhận Live Camera thì bắt nó vẽ lại đường ngay lập tức
        if getattr(self, 'auto_update_path', False):
            self.smart_run()

    def solve_retry_empty(self, col):
        """Trường hợp đặc biệt: Ép cửa nhưng cột đó sạch bóng khối -> Chạy thẳng"""
        print(f">>> [RETRY] CỘT {col} TRỐNG -> VẼ ĐƯỜNG ỦI THẲNG RA KHỎI RỪNG!")
        # Vẽ đường thẳng tắp từ Cửa lên đỉnh
        path = [(DOOR_ROW, col)]
        for r in range(ROWS - 1, -1, -1):
            path.append((r, col))
        
        self.simulation_path = [(path, "FINISH")]
        self._best_col = col
        self.best_ignored_set = []
        
        # Vẽ đường lên màn hình
        self.visualize_result(self.simulation_path, [])
        self.info_label.configure(
            text=f"RETRY: Ep cua {['A','B','C'][col]} ➔ Cột trống, ủi thẳng.", 
            text_color="#e67e22"
        )

# if __name__ == "__main__":
#     app = SelectPlaceApp()
#     app.run_algothism_forest()
    