import customtkinter as ctk
import heapq
import itertools
import time
from gui_tkinter import set_state, STATE_FOREST, STATE_IDLE 
from config_uart.sent_uart import build_packet, send_packet_once, ser

# --- Cấu hình giao diện ---
ctk.set_appearance_mode("System")
ctk.set_default_color_theme("blue")

ROWS = 4
COLS = 3
CELL_SIZE = 200
width_cell = 70
height_cell = 70

class SelectPlaceApp:
    def __init__(self):
        self.root = ctk.CTk()
        self.root.title("Robot Pathfinding: Hybrid & UART Control (Logic Fixed)")
        self.root.geometry("850x580") 

        # --- Cấu hình Sân ---
        self.team_color = "RED"  # Mặc định là RED (Phải -> Trái)

        # --- Xử lý khi bấm nút X trên cửa sổ ---
        self.root.protocol("WM_DELETE_WINDOW", self.on_closing)

        self.main_frame = ctk.CTkFrame(self.root)
        self.main_frame.pack(padx=20, pady=20, expand=True, fill="both")

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
                
                cell_frame.grid(row=i, column=j*2, padx=8, pady=8)
                cell_frame.grid_propagate(False)

                block_buttons = []
            
                for k in range(3):
                    num = k + 1
                    btn = ctk.CTkButton(
                        cell_frame,
                        text=str(num),
                        width=width_cell,
                        height=height_cell,
                        fg_color="gray75",
                        corner_radius=8,
                        font=("Arial", 18),
                        command=lambda n=num, pos=(i, j): self.place_block(n, pos)
                    )
                    btn.pack(side="left", expand=True, padx=5, pady=5)
                    block_buttons.append(btn)


                id_label = ctk.CTkLabel(
                    cell_frame, 
                    text="", 
                    width=24, 
                    height=24,
                    corner_radius=6,
                    font=("Arial", 12, "bold")
                )
                id_label.place(relx=0.02, rely=0.02, anchor="nw")
                
                cell_frame.bind("<Button-1>", lambda e, pos=(i, j): self.cell_clicked(pos))

                row.append({
                    "frame": cell_frame,
                    "content": None,
                    "overlays": [],
                    "buttons": block_buttons,
                    "id_label": id_label,
                    "selected": False
                })
            self.grid_cells.append(row)

        sep1 = ctk.CTkFrame(self.main_frame, width=4, fg_color="#d32f2f")
        sep1.grid(row=0, column=1, rowspan=ROWS, sticky="ns", pady=10)
        
        sep2 = ctk.CTkFrame(self.main_frame, width=4, fg_color="#d32f2f") 
        sep2.grid(row=0, column=3, rowspan=ROWS, sticky="ns", pady=10)

        # THANH CÔNG CỤ
        self.bottom_frame = ctk.CTkFrame(self.root)
        self.bottom_frame.pack(side="bottom", padx=20, pady=10, fill="x")

        # NÚT ĐỔI SÂN
        self.team_btn = ctk.CTkButton(
            self.bottom_frame, text="Sân: ĐỎ (RED)", width=120, height=40,
            fg_color="#d32f2f", hover_color="#b71c1c",
            command=self.toggle_team
        )
        self.team_btn.pack(side="left", padx=5)

        self.reset_btn = ctk.CTkButton(
            self.bottom_frame, text="Reset", width=80, height=40,
            fg_color="#d9534f", hover_color="#c9302c",
            command=self.reset_grid
        )
        self.reset_btn.pack(side="left", padx=5)

        self.delete_btn = ctk.CTkButton(
            self.bottom_frame, text="Xóa", width=80, height=40,
            fg_color="#f0ad4e", hover_color="#ec971f",
            command=lambda: self.toggle_mode("DELETE", self.delete_btn)
        )
        self.delete_btn.pack(side="left", padx=5)

        self.select_btn = ctk.CTkButton(
            self.bottom_frame, text="Chọn ô", width=100, height=40,
            fg_color="#5bc0de", hover_color="#31b0d5",
            command=lambda: self.toggle_mode("SELECT", self.select_btn)
        )
        self.select_btn.pack(side="left", padx=5)

        self.run_btn = ctk.CTkButton(
            self.bottom_frame, text="TÌM ĐƯỜNG", width=120, height=40,
            fg_color="#5cb85c", hover_color="#449d44",
            command=self.smart_run
        )
        self.run_btn.pack(side="left", padx=5)

        self.send_btn = ctk.CTkButton(
            self.bottom_frame, text="GỬI UART", width=120, height=40,
            fg_color="#f0ad4e", hover_color="#ec971f",
            command=self.sent_and_close, 
        )
        self.send_btn.pack(side="left", padx=5)

        self.info_label = ctk.CTkLabel(
            self.root,
            text="Chế độ: Đặt khối.\nBấm 'TÌM ĐƯỜNG' để tìm đường, sau đó 'GỬI UART' để truyền.",
            width=250, height=60, wraplength=600, justify="left"
        )
        self.info_label.pack(pady=8)

        self.mode = "PLACE"
        self.active_button = None
        self.selected_targets = []
        self.simulation_path = None
        self.best_targets_set = None
        self.best_ignored_set = []

        # Cập nhật hiển thị ID lần đầu
        self.refresh_grid_ids()

    # --- Xử lý Đổi Sân ---
    def toggle_team(self):
        if self.team_color == "RED":
            self.team_color = "BLUE"
            self.team_btn.configure(text="Sân: XANH (BLUE)", fg_color="#1e88e5", hover_color="#1565c0")
        else:
            self.team_color = "RED"
            self.team_btn.configure(text="Sân: ĐỎ (RED)", fg_color="#d32f2f", hover_color="#b71c1c")
        
        self.refresh_grid_ids()
        self.info_label.configure(text=f"Đã chuyển sang sân {self.team_color}. ID các ô đã được cập nhật.")
        
        # Reset đường đi cũ vì ID đã thay đổi
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
                
                id_bg_color = "#ffeb3b" if is_finish else "#dddddd"
                id_text_color = "#d32f2f" if is_finish else "#555555"
                
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
        self.send_uart()
        print(">> Đã truyền UART thành công!")
        self.info_label.configure(text="✓ Đã gửi UART thành công! Bạn có thể đóng cửa sổ bằng nút X.")

    # --- CÁC HÀM UI CƠ BẢN ---
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

        # --- Logic XÓA ---
        if self.mode == "DELETE":
            if cell["content"]:
                cell["content"]["widget"].destroy()
                cell["content"] = None
                for btn in cell["buttons"]:
                    btn.pack(side="left", expand=True, padx=5, pady=5)
                cell["id_label"].lift()
                self.info_label.configure(text=f"Đã xóa tại ({r},{c})")
            return

        # --- Logic SELECT MỚI (Vẽ đường thủ công) ---
        elif self.mode == "SELECT":
            if cell["selected"]:
                self.info_label.configure(text=f"Ô ({r},{c}) đã có trong đường đi!")
                return

            if not self.selected_targets:
                pass 
            else:
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
                corner_radius=14, font=("Arial", 12, "bold")
            )
            lbl_step.place(relx=0.85, rely=0.85, anchor="center")
            cell["overlays"].append(lbl_step)

            self.info_label.configure(text=f"Bước {step_idx}: Đã chọn ({r},{c}). Tiếp tục chọn ô cạnh bên...", text_color="black")

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

        new_label = ctk.CTkLabel(
            cell["frame"], text=str(number),
            width=90, height=90, fg_color="#79b8ff",
            corner_radius=12, font=("Arial", 24, "bold")
        )
        new_label.place(relx=0.5, rely=0.5, anchor="center")
        cell["content"] = {"widget": new_label, "number": number}
        for btn in cell["buttons"]:
            btn.pack_forget()
        cell["id_label"].lift()
        self.info_label.configure(text=f"Đặt khối {number} tại ({r},{c})")

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
        
        self.mode = "PLACE"
        self.selected_targets.clear()
        if self.active_button:
            self.active_button.configure(fg_color=self.active_button.default_color)
            self.active_button = None
        self.info_label.configure(text="Lưới đã reset. Mời chọn lại chế độ.")

    # --- ENGINE & LOGIC (MODIFIED FOR STRICT RULES) ---
    def check_traversable_rules(self, r, c, virtual_grid=None, target_pos=None):
        """Kiểm tra xem ô (r,c) có đi vào được không."""
        if not (0 <= r < ROWS and 0 <= c < COLS): return False
        
        # Nếu ô này là đích đến của Arm, ta cho phép 'nhìn thấy' nó để đứng cạnh
        if target_pos and (r, c) == target_pos:
            if r == 3 or r == 0: return True
            
        # Kiểm tra virtual grid (Trạng thái giả lập sau khi phá/gắp)
        if virtual_grid:
            status = virtual_grid[r][c]
            # Nếu đã phá (IGNORED) hoặc đã gắp (EMPTY), thì đi được
            if status == "EMPTY" or status == "IGNORED": return True
            
        cell = self.grid_cells[r][c]
        
        # --- LOGIC QUAN TRỌNG: CHẶN TUYỆT ĐỐI CÁC KHỐI CHƯA ĐƯỢC XỬ LÝ ---
        if cell["content"]:
            num = cell["content"]["number"]
            if num == 3: return False # Tường cứng
            if num == 2: return False # Khối 2 chưa gắp -> Tường
            
            # >>> LOGIC THÊM MỚI: Chỉ đi qua Block 1 nếu nó đã được phá (nằm trong virtual_grid) <<<
            # Nếu code chạy đến dòng này nghĩa là virtual_grid không chứa ô này (hoặc virtual_grid=None)
            if num == 1: 
                return False # Coi Block 1 chưa phá là TƯỜNG -> A* sẽ không bao giờ duyệt qua
                
        return True

    def get_access_points(self, target_pos, virtual_grid=None):
        r, c = target_pos
        points = []
        
        # Nếu là hàng 0 hoặc 3, có thể đi thẳng vào ô đó (Robot thiết kế đặc biệt)
        if r == 3 or r == 0:
            if self.check_traversable_rules(r, c, virtual_grid, target_pos=target_pos):
                points.append((r, c))
        
        # Nếu ô đó đi vào được thì thêm vào (Logic chung)
        elif self.check_traversable_rules(r, c, virtual_grid):
            points.append((r, c))

        # Kiểm tra 4 ô xung quanh để đứng gắp
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

    def count_unique_columns(self, pos1, pos2, pos3):
        cols = {pos1[1], pos2[1], pos3[1]}
        return len(cols)

    def h_score(self, current, target):
        return abs(current[0] - target[0]) + abs(current[1] - target[1])

    def min_h_score(self, pos, targets):
        if not targets: return 0
        return min(self.h_score(pos, target) for target in targets)

    def cost(self, r, c, virtual_grid=None):
        """Tính chi phí đi vào ô (r,c)."""
        if not (0 <= r < ROWS and 0 <= c < COLS): return float('inf')
        
        is_virtually_empty = False
        if virtual_grid:
            status = virtual_grid[r][c]
            if status == "EMPTY" or status == "IGNORED":
                is_virtually_empty = True

        cell = self.grid_cells[r][c]
        
        # Logic chi phí cho Khối 1
        if cell["content"] and cell["content"]["number"] == 1:
            if is_virtually_empty:
                return 2  # Nếu đã phá (theo kế hoạch), tốn chút sức để đi qua
            else:
                return float('inf')  # CẤM TUYỆT ĐỐI nếu chưa phá
        
        if cell["content"] and cell["content"]["number"] == 3:
            return float('inf')
            
        return 2  # Chi phí di chuyển bình thường

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
        # Chỉ đánh dấu các khối trong danh sách ignored_blocks là IGNORED
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
            
            # Nếu không tìm thấy đường (do bị chặn bởi Block 1 thứ 2 hoặc tường), trả về vô cực
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
        self.info_label.configure(text=f"Đang gửi UART (Sân {self.team_color})...")
        self.process_and_send_uart(self.simulation_path)

    # --- HÀM CHẠY THÔNG MINH ---
    def smart_run(self):
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

    def solve_manual_targets(self):
        if not self.selected_targets:
            self.info_label.configure(text="Bạn chưa vẽ đường đi nào!")
            return

        print(f"\n>>> XỬ LÝ ĐƯỜNG ĐI THỦ CÔNG: {self.selected_targets}")
        
        manual_simulation = [(self.selected_targets, "FINISH")]
        self.simulation_path = manual_simulation
        
        final_ids = [self.get_cell_id(*p) for p in self.selected_targets]
        print(f"-> Path IDs: {final_ids}")
        self.info_label.configure(text=f"Đã lưu đường đi thủ công ({len(self.selected_targets)} bước). Sẵn sàng GỬI UART.")
    
    #Hàm tính toán chạy tự động
    def solve_auto_targets(self):
        list_1s = []
        list_2s = []
        for r in range(ROWS):
            for c in range(COLS):
                content = self.grid_cells[r][c]["content"]
                if content:
                    if content["number"] == 1: list_1s.append((r, c))
                    elif content["number"] == 2: list_2s.append((r, c))
        
        if len(list_2s) < 2:
            self.info_label.configure(text=f"Lỗi: Cần ít nhất 2 khối số 2 để chạy Auto.")
            return

        print(f">>> Có {len(list_2s)} khối 2. Bắt đầu phân tích...")

        priority_2s = [pos for pos in list_2s if pos[0] == 3]
        has_priority = len(priority_2s) > 0

        target_sequences = []
        
        # 1. CHIẾN THUẬT QUÉT CỘT DỌC
        best_col_sequence = None
        max_2s_in_col = 0
        min_1s_in_col = float('inf')

        for c in range(COLS):
            col_2s = []
            col_1_count = 0
            for r in range(ROWS - 1, -1, -1):
                content = self.grid_cells[r][c]["content"]
                if content:
                    if content["number"] == 2:
                        col_2s.append((r, c))
                    elif content["number"] == 1:
                        col_1_count += 1
            
            if len(col_2s) >= 2:
                if len(col_2s) > max_2s_in_col:
                    max_2s_in_col = len(col_2s)
                    min_1s_in_col = col_1_count
                    best_col_sequence = col_2s
                elif len(col_2s) == max_2s_in_col:
                    if col_1_count < min_1s_in_col:
                        min_1s_in_col = col_1_count
                        best_col_sequence = col_2s

        if best_col_sequence and has_priority:
            start_node = best_col_sequence[0]
            if start_node[0] != 3: 
                best_col_sequence = None

        if best_col_sequence:
            main_col_idx = best_col_sequence[0][1]
            print(f">>> [CHIẾN THUẬT CỘT] Cột {main_col_idx} có {len(best_col_sequence)} khối.")

            adjacent_r2s = []
            for blk in list_2s:
                if blk not in best_col_sequence: 
                    r, c = blk
                    if abs(c - main_col_idx) == 1:
                        adjacent_r2s.append(blk)
            
            combined_sequence = list(best_col_sequence) + adjacent_r2s

            def sort_key(pos):
                row = pos[0]
                col = pos[1]
                dist_to_main = abs(col - main_col_idx)
                return (row, -dist_to_main)

            combined_sequence.sort(key=sort_key, reverse=True)
            
            if len(combined_sequence) > 3:
                combined_sequence = combined_sequence[:3]
                
            target_sequences.append(tuple(combined_sequence))

        else:
            print(f">>> Tìm đường tự do (Tổ hợp 2 và 3 khối)...")
            raw_sequences = []
            if len(list_2s) >= 3:
                raw_sequences.extend(list(itertools.permutations(list_2s, 3)))
            if len(list_2s) >= 2:
                raw_sequences.extend(list(itertools.permutations(list_2s, 2)))
            
            if has_priority:
                print(f">>> BẮT BUỘC: Phải lấy khối ở hàng đáy (ID 1,2,3) đầu tiên!")
                target_sequences = [s for s in raw_sequences if s[0] in priority_2s]
            else:
                target_sequences = raw_sequences

        # --- LOGIC QUAN TRỌNG: CHỈ CHO PHÉP PHÁ 0 HOẶC 1 KHỐI ---
        # potential_discards là danh sách các khối 1 CÓ THỂ bị phá.
        # Vòng lặp này sẽ thử lần lượt: 
        #   - Không phá khối nào (None)
        #   - Phá khối 1 tại vị trí A
        #   - Phá khối 1 tại vị trí B
        # ...
        # NÓ KHÔNG BAO GIỜ THỬ TRƯỜNG HỢP PHÁ 2 KHỐI CÙNG LÚC.
        # Kết hợp với check_traversable_rules chặn các khối 1 khác, 
        # ta đảm bảo Robot không bao giờ đi qua khối 1 thứ 2.
        
        potential_discards = [None] + list_1s 
        best_cost = float('inf')
        best_sim = None
        best_targets_set = None
        best_ignored_set = []
        
        for ordered_targets in target_sequences:
            active_targets = list(ordered_targets)
            
            for discard_r1 in potential_discards:
                # Tạo list chỉ chứa tối đa 1 phần tử
                current_ignored = [discard_r1] if discard_r1 else []
                
                first_target_col = active_targets[0][1]
                forced_start = (3, first_target_col)
                
                cost, sim_data = self.simulate_sequence([forced_start], active_targets, current_ignored)
                
                if cost < best_cost:
                    best_cost = cost
                    best_sim = sim_data
                    best_targets_set = active_targets
                    best_ignored_set = current_ignored

        if best_sim:
            final_ids = [self.get_cell_id(*p) for p in best_targets_set]
            ignored_ids = [self.get_cell_id(*p) for p in best_ignored_set]
            
            mode_str = "AUTO (MAX 3)"
            print(f"-> {mode_str} ({self.team_color}): {final_ids}, Ignore: {ignored_ids}")
            self.visualize_result(best_sim, best_ignored_set)
            self.simulation_path = best_sim
            self.best_targets_set = best_targets_set
            self.best_ignored_set = best_ignored_set
            self.info_label.configure(text=f"Đã tìm thấy đường (Max 3 khối): {final_ids}. Phá khối: {ignored_ids}")
        else:
            self.info_label.configure(text="Không tìm thấy đường đi khả thi (Do bị chặn bởi >1 khối 1).")
            
    # --- HÀM VẼ GIAO DIỆN KẾT QUẢ ---
    def visualize_result(self, simulation_path, ignored_blocks):
        for r, c in ignored_blocks:
            lbl_ignore = ctk.CTkLabel(self.grid_cells[r][c]["frame"], text="✖",
                                       width=40, height=40, fg_color="#aaaaaa", text_color="white",
                                       corner_radius=20, font=("Arial", 20, "bold"))
            lbl_ignore.place(relx=0.5, rely=0.5, anchor="center")
            self.grid_cells[r][c]["overlays"].append(lbl_ignore)

        full_path_display = []
        step_counter = 0
        
        def draw_pick(p_pos, r_pos, s_count):
            pr, pc = p_pos
            lr, lc = r_pos
            lbl_step = ctk.CTkLabel(self.grid_cells[lr][lc]["frame"], text=str(s_count),
                                   width=24, height=24, fg_color="#444", text_color="white",
                                   corner_radius=12, font=("Arial", 11, "bold"))
            lbl_step.place(relx=0.85, rely=0.85, anchor="center")
            if not any(isinstance(x, ctk.CTkLabel) and x.cget("text") == str(s_count) for x in self.grid_cells[lr][lc]["overlays"]):
                    self.grid_cells[lr][lc]["overlays"].append(lbl_step)
            
            lbl_picked = ctk.CTkLabel(self.grid_cells[pr][pc]["frame"], text="✓",
                                   width=24, height=24, fg_color="#ff5555",
                                   corner_radius=12, font=("Arial", 14, "bold"))
            lbl_picked.place(relx=0.85, rely=0.15, anchor="center")
            self.grid_cells[pr][pc]["overlays"].append(lbl_picked)

        for segment_path, segment_action in simulation_path:
            if segment_action == "FINISH":
                full_path_display.extend(segment_path[1:] if full_path_display else segment_path)
            else:
                draw_pick(segment_action, segment_path[-1], step_counter)
                step_counter += 1
                if not full_path_display: full_path_display.extend(segment_path)
                else: full_path_display.extend(segment_path[1:])

        for idx, (r, c) in enumerate(full_path_display):
            cell = self.grid_cells[r][c]
            if cell["content"] and cell["content"]["number"] == 1:
                if not any(isinstance(x, ctk.CTkLabel) and x.cget("text") == "🔨" for x in cell["overlays"]):
                    lbl_break = ctk.CTkLabel(cell["frame"], text="🔨",
                                             width=30, height=30, fg_color="#d35400", text_color="white",
                                             corner_radius=15, font=("Arial", 18, "bold"))
                    lbl_break.place(relx=0.8, rely=0.5, anchor="center") 
                    cell["overlays"].append(lbl_break)

            existing = cell["overlays"]
            important_overlay = any(x.cget("text") in ["✖", "✓"] for x in existing)
            has_step = any(x.cget("text").isdigit() for x in existing)
            
            color = "#7be495"
            if idx == 0: color = "#3498db"
            if idx == len(full_path_display) - 1: color = "#f1c40f"
            
            lbl = ctk.CTkLabel(cell["frame"], text=str(idx),
                               width=28, height=28, fg_color=color,
                               corner_radius=8, font=("Arial", 12, "bold"))
            if important_overlay:
                 lbl.place(relx=0.2, rely=0.2, anchor="center")
            elif has_step:
                 lbl.place(relx=0.2, rely=0.85, anchor="center")
            else:
                 lbl.place(relx=0.2, rely=0.85, anchor="center")
            cell["overlays"].append(lbl)

    # --- LOGIC GỬI UART ---
    def process_and_send_uart(self, simulation_path):
        if not ser or not ser.is_open:
            print(f"\n[UART ERROR] UART port không sẵn sàng")
            self.info_label.configure(text=f"Lỗi UART: Port không mở")
            return

        current_facing = (-1, 0) 
        right_turn_map = {(-1,0):(0,1), (0,1):(1,0), (1,0):(0,-1), (0,-1):(-1,0)}
        left_turn_map = {(-1,0):(0,-1), (0,-1):(1,0), (1,0):(0,1), (0,1):(-1,0)}

        print("=" * 60)
        print(f"BẮT ĐẦU GỬI UART (NO REDUNDANT PACKETS) - TEAM {self.team_color}")
        print("=" * 60)
        
        is_first_entry = True
        traveled_path = []
        picked_blocks = []
        count_rb2 = 0 

        for segment_idx, (segment_path, segment_action) in enumerate(simulation_path):
            print(f"\n[SEGMENT {segment_idx}] Action: {segment_action}")
            
            if not traveled_path:
                traveled_path.extend(segment_path)
            else:
                traveled_path.extend(segment_path[1:])
            
            # --- XỬ LÝ CỬA VÀO (ENTRY) ---
            if is_first_entry:
                entry_pos = segment_path[0]
                entry_id = self.get_cell_id(entry_pos[0], entry_pos[1])
                entry_cell = self.grid_cells[entry_pos[0]][entry_pos[1]]
                
                print(f"  ├─ [ENTRY START] Kiểm tra ô ID={entry_id} (R:{entry_pos[0]}, C:{entry_pos[1]})")

                if entry_id in [1, 2, 3]:
                    print(f"  │  ├─ [START PACKET] Gửi gói START (2,2,10,10) tới ID={entry_id}")
                    start_packet = build_packet(2, 2, 10, 10, entry_id)
                    ser.write(start_packet)
                    time.sleep(0.1)

                if entry_cell["content"] and entry_cell["content"]["number"] == 1:
                    print(f"  │  ├─ Phát hiện KHỐI 1. Gửi lệnh PHÁ trước.")
                    time.sleep(0.3)
                    packet = build_packet(1, 2, 0, 0, entry_id)
                    print(f"  │  └─ [BREAK BLOCK] id_rb=1, Move=2, Act=0, BlockID={entry_id}")
                    ser.write(packet)
                    
                    if not any(isinstance(x, ctk.CTkLabel) and x.cget("text") == "🔨" for x in entry_cell["overlays"]):
                        lbl_break = ctk.CTkLabel(entry_cell["frame"], text="🔨",
                                                 width=30, height=30, fg_color="#d35400", text_color="white",
                                                 corner_radius=15, font=("Arial", 18, "bold"))
                        lbl_break.place(relx=0.8, rely=0.5, anchor="center")
                        entry_cell["overlays"].append(lbl_break)
                    
                    time.sleep(0.3)
                
                if entry_cell["content"] and entry_cell["content"]["number"] == 2:
                    print(f"  │  ├─ Phát hiện KHỐI 2 tại cửa vào. Gửi lệnh GẮP trước khi vào.")
                    time.sleep(0.3)
                    packet = build_packet(2, 2, 0, 1, entry_id) 
                    count_rb2 += 1
                    ser.write(packet)
                    print(f"  │  └─ [PICK BLOCK] id_rb=2, Move=0, Act=1, BlockID={entry_id}")
                    picked_blocks.append(entry_id) 
                    
                    lbl_picked = ctk.CTkLabel(entry_cell["frame"], text="✓",
                                           width=24, height=24, fg_color="#ff5555",
                                           corner_radius=12, font=("Arial", 14, "bold"))
                    lbl_picked.place(relx=0.85, rely=0.15, anchor="center")
                    entry_cell["overlays"].append(lbl_picked)
                    time.sleep(0.5)

                time.sleep(0.3)
                packet = build_packet(2, 2, 1, 4, entry_id)
                count_rb2 += 1
                ser.write(packet)
                print(f"  ├─ [ENTRY MOVE] id_rb=2, Move=1, Act=4, BlockID={entry_id}")
                time.sleep(0.1)
                is_first_entry = False

            # --- XỬ LÝ DI CHUYỂN TRONG SEGMENT ---
            print(f"  ├─ [MOVE PHASE]")
            for i in range(len(segment_path) - 1):
                curr_pos = segment_path[i]
                next_pos = segment_path[i+1]
                step_block_id = self.get_cell_id(next_pos[0], next_pos[1])
                
                dr = next_pos[0] - curr_pos[0]
                dc = next_pos[1] - curr_pos[1]
                move_vec = (dr, dc)
                
                move_cmd = 0 
                if move_vec == current_facing:
                    move_cmd = 1 
                elif move_vec == left_turn_map[current_facing]:
                    move_cmd = 2 
                    current_facing = move_vec 
                elif move_vec == right_turn_map[current_facing]:
                    move_cmd = 3 
                    current_facing = move_vec 
                else:
                    print(f"  │  ├─ [Warn] Yêu cầu quay 180 độ không hỗ trợ.")
                    continue 
                
                nr, nc = next_pos
                cell_next = self.grid_cells[nr][nc]
                
                if cell_next["content"] and cell_next["content"]["number"] == 1:
                    print(f"  │  ├─ ⚠ KHỐI 1 chắn đường tại ID={step_block_id}. Gửi lệnh PHÁ.")
                    print(f"      └─ [BREAK] id_rb=1, Move=2, Act=0, BlockID={step_block_id}")
                    time.sleep(0.3)
                    packet = build_packet(1, 2, 0, 0, step_block_id)
                    ser.write(packet)
                    
                    if not any(isinstance(x, ctk.CTkLabel) and x.cget("text") == "🔨" for x in cell_next["overlays"]):
                        lbl_break = ctk.CTkLabel(cell_next["frame"], text="🔨",
                                                 width=30, height=30, fg_color="#d35400", text_color="white",
                                                 corner_radius=15, font=("Arial", 18, "bold"))
                        lbl_break.place(relx=0.8, rely=0.5, anchor="center")
                        cell_next["overlays"].append(lbl_break)

                    time.sleep(0.3)
                    
                elif cell_next["content"] and cell_next["content"]["number"] == 2:
                    if step_block_id not in picked_blocks:
                        print(f"  │  ├─ ⚠ KHỐI 2 chắn đường tại ID={step_block_id}. Gửi lệnh GẮP trước.")
                        pick_act = move_cmd 
                        time.sleep(0.3)
                        packet = build_packet(2, 2, 0, pick_act, step_block_id)
                        count_rb2 += 1
                        ser.write(packet)
                        picked_blocks.append(step_block_id)

                        lbl_picked = ctk.CTkLabel(cell_next["frame"], text="✓",
                                               width=24, height=24, fg_color="#ff5555",
                                               corner_radius=12, font=("Arial", 14, "bold"))
                        lbl_picked.place(relx=0.85, rely=0.15, anchor="center")
                        cell_next["overlays"].append(lbl_picked)
                        time.sleep(0.5)

                time.sleep(0.3)
                packet = build_packet(2, 2, move_cmd, 4, step_block_id)
                count_rb2 += 1
                ser.write(packet)
                move_desc = ["?", "Đi thẳng", "Rẽ trái", "Rẽ phải"][move_cmd]
                print(f"  │  ├─ [MOVE] id_rb=2, Move={move_cmd} ({move_desc}), Act=4, BlockID={step_block_id}")
                time.sleep(0.1) 
            
            # --- ACTION PHASE (CUỐI SEGMENT) ---
            if segment_action != "FINISH":
                target_pos = segment_action
                action_block_id = self.get_cell_id(target_pos[0], target_pos[1])
                
                if action_block_id in picked_blocks:
                    print(f"  └─ [SKIP ACTION] BlockID={action_block_id} đã được gắp trong quá trình di chuyển.")
                else:
                    print(f"  └─ [ACTION PHASE] Gắp tại đích (Chưa được gắp trước đó)")
                    robot_pos = segment_path[-1] 
                    
                    dr_act = target_pos[0] - robot_pos[0]
                    dc_act = target_pos[1] - robot_pos[1]
                    act_vec = (dr_act, dc_act)
                    
                    action_cmd = 4 
                    if act_vec != (0,0):
                        if act_vec == current_facing: action_cmd = 1 
                        elif act_vec == left_turn_map[current_facing]: action_cmd = 2 
                        elif act_vec == right_turn_map[current_facing]: action_cmd = 3 
                    
                    time.sleep(0.3)
                    packet = build_packet(2, 2, 0, action_cmd, action_block_id)
                    count_rb2 += 1
                    ser.write(packet)
                    picked_blocks.append(action_block_id)
                    
                    act_desc = ["?", "Gắp thẳng", "Gắp trái", "Gắp phải", "Gắp tại chỗ"][action_cmd]
                    print(f"    └─ [ACTION] id_rb=2, Move=0, Act={action_cmd} ({act_desc}), BlockID={action_block_id}")
                    time.sleep(0.3)

        # --- SEND END PACKET IF EXITED AT GATE 10/11/12 ---
        if traveled_path:
            last_pos = traveled_path[-1]
            last_id = self.get_cell_id(last_pos[0], last_pos[1])
            if last_id in [10, 11, 12]:
                print(f"  ├─ [END PACKET] Gửi gói END (2,2,10,20) tới ID={last_id}")
                end_packet = build_packet(2, 2, 20, 20, last_id)
                ser.write(end_packet)
                time.sleep(0.1)

        print("\n" + "=" * 60)
        print("HOÀN THÀNH GỬI UART")
        print(f"Tổng packet với id_rb=2 đã gửi: {count_rb2}")
        print("=" * 60)
        self.info_label.configure(text=f"Đã gửi xong ({self.team_color}). Tổng id_rb=2: {count_rb2}")

    def run_algothism_forest(self):
        self.root.mainloop()

if __name__ == "__main__":
    app = SelectPlaceApp()
    app.run_algothism_forest()