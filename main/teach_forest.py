import customtkinter as ctk
import json
import os
import time
import hashlib
from config_uart.sent_uart import build_packet, ser

# --- CẤU HÌNH ---
DATA_FILE = "robot_paths_manual.json"
ROWS = 4
COLS = 3
CELL_SIZE = 110

ctk.set_appearance_mode("System")
ctk.set_default_color_theme("blue")

class ManualPathApp:
    def __init__(self):
        self.root = ctk.CTk()
        self.root.title("Teach-in Robot: Thủ công hoàn toàn")
        self.root.geometry("1100x750")

        # Variables
        self.team_color = "RED"  # RED hoặc BLUE
        self.grid_data = [[0]*COLS for _ in range(ROWS)] 
        self.recorded_steps = [] 
        self.robot_pos = None    
        self.saved_db = self.load_database()
        self.current_tool = "MOVE" # MOVE | PICK | BREAK
        self.mode = "SETUP"        # SETUP | RECORD

        self.setup_ui()
        self.refresh_grid_ids() # Cập nhật ID lần đầu

    def setup_ui(self):
        # --- KHUNG CHÍNH ---
        self.main_frame = ctk.CTkFrame(self.root)
        self.main_frame.pack(fill="both", expand=True, padx=10, pady=10)

        # --- BÊN TRÁI: SÂN LƯỚI ---
        self.grid_frame = ctk.CTkFrame(self.main_frame)
        self.grid_frame.pack(side="left", fill="both", expand=True, padx=10, pady=10)
        
        self.cells = []
        for r in range(ROWS):
            row_cells = []
            for c in range(COLS):
                frm = ctk.CTkFrame(self.grid_frame, width=CELL_SIZE, height=CELL_SIZE, 
                                   border_width=2, border_color="#555")
                frm.grid(row=r, column=c, padx=5, pady=5)
                frm.grid_propagate(False)
                
                # ID Label (Góc trái trên)
                lbl_id = ctk.CTkLabel(frm, text="", font=("Arial", 11, "bold"), text_color="#aaa")
                lbl_id.place(relx=0.05, rely=0.05, anchor="nw")
                
                # Content Label (Chính giữa - Hiển thị khối 1,2,3)
                lbl_content = ctk.CTkLabel(frm, text="", font=("Arial", 32, "bold"))
                lbl_content.place(relx=0.5, rely=0.5, anchor="center")

                # Step Label (Góc phải dưới - Hiển thị bước đi/hành động)
                lbl_step = ctk.CTkLabel(frm, text="", font=("Arial", 14, "bold"), text_color="#00ff00")
                lbl_step.place(relx=0.9, rely=0.9, anchor="se")

                # Bind Click
                frm.bind("<Button-1>", lambda e, pos=(r,c): self.on_cell_click(pos))
                lbl_content.bind("<Button-1>", lambda e, pos=(r,c): self.on_cell_click(pos))
                
                row_cells.append({
                    "frame": frm, "lbl_id": lbl_id, 
                    "lbl_content": lbl_content, "lbl_step": lbl_step
                })
            self.cells.append(row_cells)

        # --- BÊN PHẢI: BẢNG ĐIỀU KHIỂN ---
        self.ctrl_frame = ctk.CTkFrame(self.main_frame, width=320)
        self.ctrl_frame.pack(side="right", fill="y", padx=10, pady=10)
        
        # 1. Chọn Sân
        ctk.CTkLabel(self.ctrl_frame, text="1. CẤU HÌNH SÂN", font=("Arial", 16, "bold")).pack(pady=(10,5))
        self.btn_team = ctk.CTkButton(self.ctrl_frame, text="SÂN: ĐỎ (RED)", fg_color="#c0392b", 
                                      command=self.toggle_team)
        self.btn_team.pack(fill="x", padx=20, pady=5)

        # 2. Setup Vật cản
        ctk.CTkLabel(self.ctrl_frame, text="2. ĐẶT VẬT CẢN (SETUP)", font=("Arial", 16, "bold")).pack(pady=(20,5))
        self.block_var = ctk.IntVar(value=2)
        
        frm_blocks = ctk.CTkFrame(self.ctrl_frame)
        frm_blocks.pack(fill="x", padx=10)
        ctk.CTkRadioButton(frm_blocks, text="Khối 2 (Gắp)", variable=self.block_var, value=2, text_color="#3498db").grid(row=0, column=0, pady=5, padx=5)
        ctk.CTkRadioButton(frm_blocks, text="Khối 1 (Phá)", variable=self.block_var, value=1, text_color="#e67e22").grid(row=0, column=1, pady=5, padx=5)
        ctk.CTkRadioButton(frm_blocks, text="Khối 3 (Cấm)", variable=self.block_var, value=3, text_color="#95a5a6").grid(row=1, column=0, pady=5, padx=5)
        ctk.CTkRadioButton(frm_blocks, text="Xóa ô", variable=self.block_var, value=0).grid(row=1, column=1, pady=5, padx=5)
        
        ctk.CTkButton(self.ctrl_frame, text="Xóa sạch sân", fg_color="gray", height=24, command=self.clear_grid).pack(pady=10)

        # 3. Chế độ Ghi (Công cụ)
        ctk.CTkLabel(self.ctrl_frame, text="3. GHI HÀNH TRÌNH", font=("Arial", 16, "bold")).pack(pady=(20,5))
        
        self.btn_record = ctk.CTkButton(self.ctrl_frame, text="BẮT ĐẦU GHI (REC)", fg_color="green", command=self.toggle_record_mode)
        self.btn_record.pack(fill="x", padx=20, pady=5)

        # Công cụ thao tác (Radio Buttons hoặc Segmented Button)
        self.frm_tools = ctk.CTkFrame(self.ctrl_frame)
        self.frm_tools.pack(fill="x", padx=10, pady=10)
        
        ctk.CTkLabel(self.frm_tools, text="Chọn hành động click:").pack(anchor="w", padx=5)
        self.tool_var = ctk.StringVar(value="MOVE")
        
        r_move = ctk.CTkRadioButton(self.frm_tools, text="DI CHUYỂN ROBOT", variable=self.tool_var, value="MOVE", text_color="#2ecc71")
        r_move.pack(anchor="w", padx=10, pady=5)
        
        r_pick = ctk.CTkRadioButton(self.frm_tools, text="GẮP (Tại chỗ)", variable=self.tool_var, value="PICK", text_color="#3498db")
        r_pick.pack(anchor="w", padx=10, pady=5)
        
        r_break = ctk.CTkRadioButton(self.frm_tools, text="PHÁ (Tại chỗ)", variable=self.tool_var, value="BREAK", text_color="#e67e22")
        r_break.pack(anchor="w", padx=10, pady=5)

        self.btn_undo = ctk.CTkButton(self.ctrl_frame, text="Undo (Quay lại)", command=self.undo_step, state="disabled", fg_color="#7f8c8d")
        self.btn_undo.pack(fill="x", padx=40, pady=5)

        # 4. Save & Run
        ctk.CTkLabel(self.ctrl_frame, text="4. XỬ LÝ & UART", font=("Arial", 16, "bold")).pack(pady=(20,5))
        self.lbl_status = ctk.CTkLabel(self.ctrl_frame, text="...", text_color="gray", wraplength=280)
        self.lbl_status.pack(pady=5)
        
        self.btn_save = ctk.CTkButton(self.ctrl_frame, text="LƯU DỮ LIỆU", command=self.save_current_path, state="disabled")
        self.btn_save.pack(fill="x", padx=20, pady=5)
        
        self.btn_send = ctk.CTkButton(self.ctrl_frame, text="GỬI UART", fg_color="#d35400", height=50, font=("Arial", 14, "bold"), 
                                      command=self.send_uart_sequence, state="disabled")
        self.btn_send.pack(fill="x", padx=20, pady=10)

    # --- LOGIC ID & COLOR ---
    def toggle_team(self):
        if self.mode == "RECORD": return # Không đổi màu khi đang ghi
        
        if self.team_color == "RED":
            self.team_color = "BLUE"
            self.btn_team.configure(text="SÂN: XANH (BLUE)", fg_color="#2980b9")
        else:
            self.team_color = "RED"
            self.btn_team.configure(text="SÂN: ĐỎ (RED)", fg_color="#c0392b")
        
        self.refresh_grid_ids()
        self.check_database_match()

    def get_cell_id(self, r, c):
        row_factor = (ROWS - 1 - r) * COLS 
        if self.team_color == "RED": col_offset = (COLS - 1 - c)
        else: col_offset = c
        return row_factor + col_offset + 1

    def refresh_grid_ids(self):
        for r in range(ROWS):
            for c in range(COLS):
                cell_id = self.get_cell_id(r, c)
                self.cells[r][c]["lbl_id"].configure(text=f"ID:{cell_id}")

    # --- CLICK EVENT HANDLER ---
    def on_cell_click(self, pos):
        r, c = pos
        
        if self.mode == "SETUP":
            val = self.block_var.get()
            self.grid_data[r][c] = val
            self.refresh_cell_view(r, c)
            self.check_database_match()

        elif self.mode == "RECORD":
            tool = self.tool_var.get()
            self.process_record_step(r, c, tool)

    def refresh_cell_view(self, r, c):
        val = self.grid_data[r][c]
        cell = self.cells[r][c]
        
        text = ""
        content_color = "black"
        bg_color = "transparent" # Default
        
        if val == 1: 
            text = "1"; content_color = "#d35400" # Cam đậm
        elif val == 2: 
            text = "2"; content_color = "#2980b9" # Xanh
        elif val == 3: 
            text = "3"; content_color = "#7f8c8d" # Xám
            
        cell["lbl_content"].configure(text=text, text_color=content_color)
        
        # Reset border nếu không phải là vị trí robot
        if self.robot_pos != (r,c):
            cell["frame"].configure(border_color="#555", border_width=2)

    def clear_grid(self):
        self.grid_data = [[0]*COLS for _ in range(ROWS)]
        self.recorded_steps = []
        self.robot_pos = None
        for r in range(ROWS):
            for c in range(COLS):
                self.refresh_cell_view(r, c)
                self.cells[r][c]["lbl_step"].configure(text="")
        self.mode = "SETUP"
        self.btn_record.configure(text="BẮT ĐẦU GHI (REC)", fg_color="green")
        self.btn_send.configure(state="disabled")
        self.lbl_status.configure(text="Sân đã xóa.")

    # --- LOGIC RECORDING (QUAN TRỌNG) ---
    def toggle_record_mode(self):
        if self.mode == "SETUP":
            self.mode = "RECORD"
            self.btn_record.configure(text="DỪNG / HỦY GHI", fg_color="red")
            self.recorded_steps = []
            self.robot_pos = None
            self.lbl_status.configure(text="CHỌN Ô XUẤT PHÁT!", text_color="blue")
            
            # Khóa các nút setup
            self.btn_team.configure(state="disabled")
            
            # Clear visual cũ
            for r in range(ROWS):
                for c in range(COLS):
                    self.cells[r][c]["lbl_step"].configure(text="")
        else:
            self.mode = "SETUP"
            self.btn_record.configure(text="BẮT ĐẦU GHI (REC)", fg_color="green")
            self.btn_team.configure(state="normal")
            self.update_ui_state()

    def process_record_step(self, r, c, tool):
        # 1. Nếu chưa có Robot -> Click đầu tiên là ĐẶT ROBOT (START)
        if self.robot_pos is None:
            self.robot_pos = (r, c)
            self.add_step("START", r, c)
            self.lbl_status.configure(text=f"Xuất phát tại ID:{self.get_cell_id(r,c)}")
            return

        curr_r, curr_c = self.robot_pos
        dist = abs(r - curr_r) + abs(c - curr_c)

        if dist != 1:
            self.lbl_status.configure(text="❌ Chỉ được chọn ô liền kề!", text_color="red")
            return

        # 2. Xử lý theo Tool
        if tool == "MOVE":
            # Robot di chuyển sang ô mới
            self.robot_pos = (r, c)
            self.add_step("MOVE", r, c)
            self.lbl_status.configure(text=f"Di chuyển sang ({r},{c})")
            
        elif tool == "PICK":
            # Robot đứng yên, gắp ô (r,c)
            # Kiểm tra: ô đó phải có khối? (Không bắt buộc, cho phép gắp mù nếu bạn muốn)
            self.add_step("PICK", r, c, stand_at=(curr_r, curr_c))
            self.lbl_status.configure(text=f"Gắp tại ({r},{c}) (Đứng tại chỗ)")
            
        elif tool == "BREAK":
            self.add_step("BREAK", r, c, stand_at=(curr_r, curr_c))
            self.lbl_status.configure(text=f"Phá tại ({r},{c}) (Đứng tại chỗ)")

    def add_step(self, action_type, r, c, stand_at=None):
        step_data = {
            "type": action_type, 
            "r": r, "c": c,
            "team": self.team_color # Lưu màu team vào step để debug
        }
        if stand_at:
            step_data["stand_r"] = stand_at[0]
            step_data["stand_c"] = stand_at[1]
            
        self.recorded_steps.append(step_data)
        
        # --- VISUAL FEEDBACK ---
        cell = self.cells[r][c]
        
        if action_type == "START":
            cell["frame"].configure(border_color="#00ff00", border_width=4)
            cell["lbl_step"].configure(text="S", text_color="#00ff00")
            
        elif action_type == "MOVE":
            # Xóa border ô cũ
            if len(self.recorded_steps) > 1:
                prev = self.recorded_steps[-2]
                if prev["type"] == "MOVE" or prev["type"] == "START":
                    self.cells[prev["r"]][prev["c"]]["frame"].configure(border_color="#555", border_width=2)
            
            # Highlight ô mới
            cell["frame"].configure(border_color="#00FFFF", border_width=4)
            idx = sum(1 for s in self.recorded_steps if s["type"] == "MOVE")
            cell["lbl_step"].configure(text=str(idx), text_color="white")
            
        elif action_type == "PICK":
            cell["lbl_step"].configure(text="✓", text_color="red")
            
        elif action_type == "BREAK":
            cell["lbl_step"].configure(text="🔨", text_color="orange")

        self.update_ui_state()

    def undo_step(self):
        if not self.recorded_steps: return
        
        last = self.recorded_steps.pop()
        r, c = last["r"], last["c"]
        
        # Xóa visual
        self.cells[r][c]["lbl_step"].configure(text="")
        self.cells[r][c]["frame"].configure(border_color="#555", border_width=2)
        
        # Khôi phục vị trí robot
        # Tìm step MOVE hoặc START gần nhất
        for s in reversed(self.recorded_steps):
            if s["type"] in ["MOVE", "START"]:
                self.robot_pos = (s["r"], s["c"])
                # Vẽ lại border cho vị trí hiện tại
                self.cells[s["r"]][s["c"]]["frame"].configure(border_color="#00FFFF" if s["type"]=="MOVE" else "#00ff00", border_width=4)
                break
        else:
            self.robot_pos = None # Nếu xóa hết sạch

        self.update_ui_state()

    def update_ui_state(self):
        has_steps = len(self.recorded_steps) > 0
        self.btn_undo.configure(state="normal" if has_steps else "disabled")
        self.btn_save.configure(state="normal" if has_steps else "disabled")
        self.btn_send.configure(state="normal" if has_steps else "disabled")

    # --- SAVE / LOAD SYSTEM ---
    def get_hash(self):
        # Hash bao gồm: Vị trí khối + Màu Sân
        items = [f"TEAM:{self.team_color}"]
        for r in range(ROWS):
            for c in range(COLS):
                val = self.grid_data[r][c]
                if val in [1, 2]:
                    items.append(f"R{r}C{c}:{val}")
        s = "|".join(sorted(items))
        return hashlib.md5(s.encode()).hexdigest()

    def load_database(self):
        if not os.path.exists(DATA_FILE): return {}
        try:
            with open(DATA_FILE, 'r') as f: return json.load(f)
        except: return {}

    def save_current_path(self):
        if not self.recorded_steps: return
        h = self.get_hash()
        self.saved_db[h] = self.recorded_steps
        with open(DATA_FILE, 'w') as f: json.dump(self.saved_db, f, indent=4)
        self.lbl_status.configure(text="ĐÃ LƯU DỮ LIỆU!", text_color="green")

    def check_database_match(self):
        if self.mode != "SETUP": return
        h = self.get_hash()
        if h in self.saved_db:
            self.lbl_status.configure(text="✅ TÌM THẤY DỮ LIỆU CŨ!", text_color="green")
            self.recorded_steps = self.saved_db[h]
            self.btn_send.configure(state="normal")
            
            # Vẽ lại đường đi cũ để view
            self.mode = "RECORD" # Ảo
            self.btn_record.configure(text="RESET ĐỂ RECORD MỚI", fg_color="orange")
            
            move_idx = 1
            for s in self.recorded_steps:
                r, c = s["r"], s["c"]
                t = s["type"]
                cell = self.cells[r][c]
                if t == "START": 
                    cell["lbl_step"].configure(text="S", text_color="#00ff00")
                elif t == "MOVE":
                    cell["lbl_step"].configure(text=str(move_idx), text_color="white")
                    move_idx += 1
                elif t == "PICK":
                    cell["lbl_step"].configure(text="✓", text_color="red")
                elif t == "BREAK":
                    cell["lbl_step"].configure(text="🔨", text_color="orange")
        else:
            self.lbl_status.configure(text="Chưa có dữ liệu cho thế bài này.", text_color="gray")
            self.btn_send.configure(state="disabled")

    # --- UART SENDING LOGIC (THEO TOOL) ---
    def send_uart_sequence(self):
        if not self.recorded_steps: return
        print(f"\n>>> SENDING UART ({self.team_color}) <<<")
        
        # Giả định hướng đầu robot (Thường là hướng lên trên -1, 0)
        # Nếu robot thực tế khác, bạn cần sửa dòng này
        current_facing = (-1, 0) 

        # Map hướng tương đối
        # Input: Vector hướng đi (dr, dc)
        # Output: Hướng cần quay so với current_facing
        def get_turn_cmd(vec, facing):
            left_map = {(-1,0):(0,-1), (0,-1):(1,0), (1,0):(0,1), (0,1):(-1,0)}
            right_map = {(-1,0):(0,1), (0,1):(1,0), (1,0):(0,-1), (0,-1):(-1,0)}
            
            if vec == facing: return 1 # Thẳng (Front)
            if vec == left_map[facing]: return 2 # Trái (Left)
            if vec == right_map[facing]: return 3 # Phải (Right)
            return 1 # Default fallback

        # 1. Gửi gói START
        start = self.recorded_steps[0]
        start_id = self.get_cell_id(start["r"], start["c"])
        
        # Giả lập đi vào ô Start
        ser.write(build_packet(2, 2, 10, 10, start_id))
        time.sleep(0.2)
        ser.write(build_packet(2, 2, 1, 4, start_id)) # Move Straight vào ô Start
        time.sleep(0.5)
        
        last_robot_pos = (start["r"], start["c"])

        # 2. Duyệt các bước
        for i in range(1, len(self.recorded_steps)):
            step = self.recorded_steps[i]
            target_pos = (step["r"], step["c"])
            target_id = self.get_cell_id(*target_pos)
            
            # --- CASE 1: DI CHUYỂN (MOVE) ---
            if step["type"] == "MOVE":
                dr = target_pos[0] - last_robot_pos[0]
                dc = target_pos[1] - last_robot_pos[1]
                move_vec = (dr, dc)
                
                cmd = get_turn_cmd(move_vec, current_facing)
                
                # Cập nhật hướng mặt robot
                if cmd == 2: # Left
                    left_map = {(-1,0):(0,-1), (0,-1):(1,0), (1,0):(0,1), (0,1):(-1,0)}
                    current_facing = left_map[current_facing]
                elif cmd == 3: # Right
                    right_map = {(-1,0):(0,1), (0,1):(1,0), (1,0):(0,-1), (0,-1):(-1,0)}
                    current_facing = right_map[current_facing]
                
                print(f"MOVE to {target_id}: Cmd={cmd}")
                ser.write(build_packet(2, 2, cmd, 4, target_id))
                last_robot_pos = target_pos
                time.sleep(0.5)

            # --- CASE 2: GẮP HOẶC PHÁ (PICK/BREAK) ---
            elif step["type"] in ["PICK", "BREAK"]:
                # Robot đứng yên tại last_robot_pos
                # Tính hướng tới ô mục tiêu
                dr = target_pos[0] - last_robot_pos[0]
                dc = target_pos[1] - last_robot_pos[1]
                act_vec = (dr, dc)
                
                # Tính hướng tay gắp tương đối với mặt robot
                act_dir = get_turn_cmd(act_vec, current_facing)
                
                act_code = 1 if step["type"] == "PICK" else 0
                rb_id = 2 if step["type"] == "PICK" else 1
                
                print(f"ACTION {step['type']} on {target_id}: Dir={act_dir}")
                # Move = 0 (Đứng yên), Act = act_code, Dir = act_dir
                ser.write(build_packet(rb_id, 2, 0, act_dir, target_id))
                time.sleep(0.6)

        # 3. Kết thúc
        last_id = self.get_cell_id(*last_robot_pos)
        if last_id in [10, 11, 12]:
            print("FINISH")
            ser.write(build_packet(2, 2, 20, 20, last_id))

        self.lbl_status.configure(text="Đã gửi UART xong!", text_color="green")

if __name__ == "__main__":
    app = ManualPathApp()
    app.root.mainloop()