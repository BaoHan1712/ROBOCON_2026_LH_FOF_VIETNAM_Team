import customtkinter as ctk
import heapq
import itertools
import struct
import serial
import time

# --- Cấu hình Serial ---
UART_PORT = 'COM3' 
BAUD_RATE = 115200

ctk.set_appearance_mode("System")
ctk.set_default_color_theme("blue")

ROWS = 4
COLS = 3
CELL_SIZE = 200
width_cell = 70
height_cell = 70

# --- Hàm đóng gói gói tin ---
def build_packet(id_rb, move, action, block_id):
    start = 0x02
    end = 0x03
    checksum = (start + id_rb + move + action + block_id) & 0xFF
    packet = struct.pack('7B', start, id_rb, move, action, block_id, checksum, end)
    return packet

class SelectPlaceApp:
    def __init__(self):
        self.root = ctk.CTk()
        self.root.title("Robot: Straight Line Optimization")
        self.root.geometry("850x580") 

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

                # Cell ID Display
                cell_id = (ROWS - 1 - i) * COLS + (COLS - 1 - j) + 1
                is_finish = cell_id in [10, 11, 12]
                id_bg_color = "#ffeb3b" if is_finish else "#dddddd"
                id_text_color = "#d32f2f" if is_finish else "#555555"
                
                id_label = ctk.CTkLabel(
                    cell_frame, 
                    text=f"ID:{cell_id}" if is_finish else str(cell_id), 
                    text_color=id_text_color, 
                    fg_color=id_bg_color,
                    width=24 if not is_finish else 45, 
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

        self.bottom_frame = ctk.CTkFrame(self.root)
        self.bottom_frame.pack(side="bottom", padx=20, pady=10, fill="x")

        self.reset_btn = ctk.CTkButton(
            self.bottom_frame, text="Reset", width=100, height=40,
            fg_color="#d9534f", hover_color="#c9302c",
            command=self.reset_grid
        )
        self.reset_btn.pack(side="left", padx=5)

        self.delete_btn = ctk.CTkButton(
            self.bottom_frame, text="Xóa", width=100, height=40,
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
            self.bottom_frame, text="CHẠY & GỬI UART", width=160, height=40,
            fg_color="#5cb85c", hover_color="#449d44",
            command=self.smart_run
        )
        self.run_btn.pack(side="left", padx=5)

        self.info_label = ctk.CTkLabel(
            self.root,
            text="Chế độ: Đặt khối.\nLogic: Ưu tiên Hàng cuối + Tối ưu đi thẳng (Hạn chế rẽ ngang).",
            width=250, height=60, wraplength=600, justify="left"
        )
        self.info_label.pack(pady=8)

        self.mode = "PLACE"
        self.active_button = None
        self.selected_targets = []

    # --- UI Helpers ---
    def get_cell_id(self, r, c):
        return (ROWS - 1 - r) * COLS + (COLS - 1 - c) + 1

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
        if self.mode == "DELETE":
            if cell["content"]:
                cell["content"]["widget"].destroy()
                cell["content"] = None
                for btn in cell["buttons"]:
                    btn.pack(side="left", expand=True, padx=5, pady=5)
                cell["id_label"].lift()
        elif self.mode == "SELECT":
            if not cell["selected"]:
                cell["frame"].configure(fg_color="orange")
                cell["selected"] = True
                self.selected_targets.append((r, c))
            else:
                cell["frame"].configure(fg_color="transparent")
                cell["selected"] = False
                if (r, c) in self.selected_targets:
                    self.selected_targets.remove((r, c))

    def place_block(self, number, position):
        r, c = position
        cell = self.grid_cells[r][c]
        if self.mode in ["DELETE", "SELECT"]:
            self.cell_clicked(position)
            return
        if cell["content"]: return

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
        self.info_label.configure(text="Lưới đã reset.")

    # --- LOGIC TÌM ĐƯỜNG ---
    def check_traversable_rules(self, r, c, virtual_grid=None):
        if not (0 <= r < ROWS and 0 <= c < COLS): return False
        if virtual_grid:
            status = virtual_grid[r][c]
            if status == "EMPTY" or status == "IGNORED": return True
        cell = self.grid_cells[r][c]
        if cell["content"] and cell["content"]["number"] == 3: return False
        return True

    def get_access_points(self, target_pos, virtual_grid=None):
        r, c = target_pos
        points = []
        if self.check_traversable_rules(r, c, virtual_grid):
            points.append((r, c))
        dirs = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        for dr, dc in dirs:
            nr, nc = r + dr, c + dc
            if self.check_traversable_rules(nr, nc, virtual_grid):
                points.append((nr, nc))
        return points

    def neighbors(self, pos, direction, virtual_grid=None):
        r, c = pos
        # 0: Up, 1: Left, 2: Right, 3: Down
        dirs = [(-1,0),(0,-1),(0,1),(1,0)]
        for ndir, (dr, dc) in enumerate(dirs):
            nr, nc = r+dr, c+dc
            if self.check_traversable_rules(nr, nc, virtual_grid):
                priority = 0 if ndir == direction else 5
                yield (nr, nc, ndir, priority)

    def is_adjacent(self, pos1, pos2):
        return abs(pos1[0] - pos2[0]) + abs(pos1[1] - pos2[1]) == 1

    def count_unique_columns(self, pos1, pos2, pos3):
        cols = {pos1[1], pos2[1], pos3[1]}
        return len(cols)

    def calculate_group_proximity_score(self, pos1, pos2, pos3):
        unique_cols = self.count_unique_columns(pos1, pos2, pos3)
        if unique_cols == 1:
            total_dist = abs(pos1[0] - pos2[0]) + abs(pos1[0] - pos3[0])
            return 5000 - total_dist * 10
        if unique_cols == 2:
            total_dist = abs(pos1[0] - pos2[0]) + abs(pos1[0] - pos3[0]) + abs(pos1[1] - pos2[1]) + abs(pos1[1] - pos3[1])
            return 2000 - total_dist * 5
        if pos1[0] == pos2[0] == pos3[0]:
            total_dist = abs(pos1[1] - pos2[1]) + abs(pos1[1] - pos3[1])
            return 1500 - total_dist * 5
        
        dist_12 = abs(pos1[0] - pos2[0]) + abs(pos1[1] - pos2[1])
        dist_13 = abs(pos1[0] - pos3[0]) + abs(pos1[1] - pos3[1])
        dist_23 = abs(pos2[0] - pos3[0]) + abs(pos2[1] - pos3[1])
        total_dist = dist_12 + dist_13 + dist_23
        
        adj_12 = 1 if self.is_adjacent(pos1, pos2) else 0
        adj_13 = 1 if self.is_adjacent(pos1, pos3) else 0
        adj_23 = 1 if self.is_adjacent(pos2, pos3) else 0
        adjacent_count = adj_12 + adj_13 + adj_23
        
        col_penalty = (unique_cols - 1) * 1000
        return adjacent_count * 100 - total_dist * 10 - col_penalty

    # --- ĐIỀU CHỈNH 1: Heuristic phạt nặng khoảng cách ngang ---
    def h_score(self, current, target):
        # Nhân khoảng cách ngang (dc) với 3.0 để thuật toán thấy "lệch cột" là rất xa
        return abs(current[0] - target[0]) + abs(current[1] - target[1]) * 3.0

    def min_h_score(self, pos, targets):
        if not targets: return 0
        return min(self.h_score(pos, target) for target in targets)

    def dijkstra_astar(self, starts, targets, use_arm=False, virtual_grid=None):
        g_score = [[float("inf")]*COLS for _ in range(ROWS)]
        parent = [[None]*COLS for _ in range(ROWS)]
        pq = []
        goal_map = {} 
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
            
            # ndir: 0=Up, 1=Left, 2=Right, 3=Down
            for nr, nc, ndir, priority in self.neighbors(cur, direction, virtual_grid):
                
                # --- ĐIỀU CHỈNH 2: Phạt nặng hành động đi ngang ---
                is_horizontal_move = (ndir == 1 or ndir == 2)
                
                if is_horizontal_move:
                    step_cost = 4.0 # Phạt nặng: Đi ngang tốn gấp 4 lần đi dọc
                else:
                    step_cost = 1.0 # Đi dọc bình thường
                
                turn_cost = 0.5 if priority > 0 else 0
                tentative_g = g + step_cost + turn_cost
                
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
                combo_bonus += 2.5 
            path, picked = self.dijkstra_astar(current_starts, [target], use_arm=True, virtual_grid=virtual_grid)
            if not path: return float('inf'), []
            
            # Tính toán chi phí thực tế cho segment (để so sánh)
            segment_cost = 0
            for k in range(len(path) - 1):
                p1 = path[k]
                p2 = path[k+1]
                # Nếu khác cột -> move ngang -> cost cao
                if p1[1] != p2[1]: segment_cost += 4.0
                else: segment_cost += 1.0
                
            total_steps += segment_cost
            full_simulation_path.append((path, picked))
            last_pos = path[-1]
            last_target_pos = picked
            current_starts = [last_pos]
            tr, tc = picked
            virtual_grid[tr][tc] = "EMPTY"
            
        final_goals = [(0, c) for c in range(COLS)]
        path_home, _ = self.dijkstra_astar(current_starts, final_goals, use_arm=False, virtual_grid=virtual_grid)
        if not path_home: return float('inf'), []
        
        for k in range(len(path_home) - 1):
            p1 = path_home[k]
            p2 = path_home[k+1]
            if p1[1] != p2[1]: total_steps += 4.0
            else: total_steps += 1.0
            
        full_simulation_path.append((path_home, "FINISH"))
        final_score = total_steps - combo_bonus
        return final_score, full_simulation_path

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
        perms = list(itertools.permutations(self.selected_targets))
        best_cost = float('inf')
        best_sim = None
        best_perm = None
        for perm in perms:
            first_target_col = perm[0][1]
            forced_start = (ROWS - 1, first_target_col)
            cost, sim_data = self.simulate_sequence([forced_start], perm, [])
            if cost < best_cost:
                best_cost = cost
                best_sim = sim_data
                best_perm = perm
        if best_sim:
            final_ids = [self.get_cell_id(*p) for p in best_perm]
            print(f"-> Manual Order: {final_ids}")
            self.visualize_result(best_sim, [])
            self.info_label.configure(text=f"Thủ công: {final_ids}. Đang gửi UART...")
            self.process_and_send_uart(best_sim)
        else:
            self.info_label.configure(text="Không tìm được đường đi cho các ô đã chọn.")

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
        
        # Sort key: Ưu tiên có Row 3 trước, sau đó là điểm proximity
        def combo_sort_key(combo):
            has_row3 = any(p[0] == ROWS - 1 for p in combo)
            score = 0
            if len(combo) == 3:
                score = self.calculate_group_proximity_score(combo[0], combo[1], combo[2])
            else:
                score = self.calculate_group_proximity_score(combo[0], combo[1], combo[0])
            return (has_row3, score)

        combos_target = []
        if len(list_2s) >= 3:
            print(f">>> Có {len(list_2s)} khối 2. Tìm 3 khối.")
            all_combos_3 = list(itertools.combinations(list_2s, 3))
            all_combos_3.sort(key=combo_sort_key, reverse=True)
            combos_target = all_combos_3
        else:
            print(f">>> Chỉ có {len(list_2s)} khối 2. Lấy 2 khối.")
            all_combos_2 = list(itertools.combinations(list_2s, 2))
            all_combos_2.sort(key=combo_sort_key, reverse=True)
            combos_target = all_combos_2
        
        potential_discards = [None] + list_1s
        best_cost = float('inf')
        best_sim = None
        best_targets_set = None
        best_ignored_set = []
        best_combo_idx = float('inf')
        
        for combo_idx, c2 in enumerate(combos_target):
            active_targets = list(c2)
            row3_blocks_in_combo = [p for p in active_targets if p[0] == ROWS - 1]
            
            for discard_r1 in potential_discards:
                current_ignored = [discard_r1] if discard_r1 else []
                raw_perms = list(itertools.permutations(active_targets))
                valid_permutations = []

                if row3_blocks_in_combo:
                    for perm in raw_perms:
                        if perm[0] in row3_blocks_in_combo:
                            valid_permutations.append(perm)
                    if not valid_permutations: valid_permutations = raw_perms
                else:
                    valid_permutations = raw_perms

                for perm in valid_permutations:
                    first_target_col = perm[0][1]
                    forced_start = (ROWS - 1, first_target_col)
                    cost, sim_data = self.simulate_sequence([forced_start], perm, current_ignored)
                    
                    if best_sim is None:
                        best_cost = cost
                        best_sim = sim_data
                        best_targets_set = perm
                        best_ignored_set = current_ignored
                        best_combo_idx = combo_idx
                    elif combo_idx < best_combo_idx:
                        best_cost = cost
                        best_sim = sim_data
                        best_targets_set = perm
                        best_ignored_set = current_ignored
                        best_combo_idx = combo_idx
                    elif combo_idx == best_combo_idx and cost < best_cost:
                        best_cost = cost
                        best_sim = sim_data
                        best_targets_set = perm
                        best_ignored_set = current_ignored

        if best_sim:
            final_ids = [self.get_cell_id(*p) for p in best_targets_set]
            ignored_ids = [self.get_cell_id(*p) for p in best_ignored_set]
            print(f"-> Auto Pick: {final_ids}, Ignore: {ignored_ids}")
            
            if best_targets_set[0][0] == ROWS - 1:
                print("   (Đã ưu tiên xuất phát từ khối ở ID 1/2/3)")

            self.visualize_result(best_sim, best_ignored_set)
            self.info_label.configure(text=f"Auto: {final_ids}. Đang gửi UART...")
            self.process_and_send_uart(best_sim)
        else:
            self.info_label.configure(text="Không tìm thấy đường đi khả thi.")

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
            existing = self.grid_cells[r][c]["overlays"]
            important_overlay = any(x.cget("text") in ["✖", "✓"] for x in existing)
            has_step = any(x.cget("text").isdigit() for x in existing)
            
            color = "#7be495"
            if idx == 0: color = "#3498db"
            if idx == len(full_path_display) - 1: color = "#f1c40f"
            
            lbl = ctk.CTkLabel(self.grid_cells[r][c]["frame"], text=str(idx),
                               width=28, height=28, fg_color=color,
                               corner_radius=8, font=("Arial", 12, "bold"))
            if important_overlay:
                 lbl.place(relx=0.2, rely=0.2, anchor="center")
            elif has_step:
                 lbl.place(relx=0.2, rely=0.85, anchor="center")
            else:
                 lbl.place(relx=0.2, rely=0.85, anchor="center")
            self.grid_cells[r][c]["overlays"].append(lbl)

    def process_and_send_uart(self, simulation_path):
        try:
            ser = serial.Serial(UART_PORT, BAUD_RATE, timeout=1)
            print(f"\n[UART] Connected to {UART_PORT}")
        except Exception as e:
            print(f"\n[UART ERROR] Không thể mở cổng {UART_PORT}: {e}")
            self.info_label.configure(text=f"Lỗi UART: Không mở được {UART_PORT}")
            return

        current_facing = (-1, 0) # North
        right_turn_map = {(-1,0):(0,1), (0,1):(1,0), (1,0):(0,-1), (0,-1):(-1,0)}
        left_turn_map = {(-1,0):(0,-1), (0,-1):(1,0), (1,0):(0,1), (0,1):(-1,0)}

        print("=" * 60)
        print("BẮT ĐẦU GỬI UART (SEQUENTIAL)")
        print("=" * 60)
        
        is_first_entry = True
        traveled_path = []

        for segment_idx, (segment_path, segment_action) in enumerate(simulation_path):
            print(f"\n[SEGMENT {segment_idx}] Action: {segment_action}")
            
            if segment_action != "FINISH":
                if not traveled_path:
                    traveled_path.extend(segment_path)
                else:
                    traveled_path.extend(segment_path[1:])
            
            if is_first_entry:
                entry_pos = segment_path[0]
                entry_id = self.get_cell_id(entry_pos[0], entry_pos[1])
                
                entry_cell = self.grid_cells[entry_pos[0]][entry_pos[1]]
                if entry_cell["content"] and entry_cell["content"]["number"] == 1:
                    print(f"  ├─ [ENTRY CHECK] Phát hiện KHỐI 1 tại entry point {entry_pos}")
                    packet = build_packet(1, 0, 0, entry_id)
                    ser.write(packet)
                    time.sleep(0.3)
                
                packet = build_packet(2, 1, 4, entry_id)
                ser.write(packet)
                print(f"  ├─ [ENTRY] id_rb=2, Move=1, Act=4, BlockID={entry_id}")
                time.sleep(0.1)
                is_first_entry = False

            if segment_action == "FINISH":
                print(f"  ├─ [FINISH PHASE] Checking obstacles on return path...")
                blocks_to_remove = []
                for check_pos in traveled_path:
                    cr, cc = check_pos
                    cell = self.grid_cells[cr][cc]
                    if cell["content"] and cell["content"]["number"] == 1:
                        if check_pos not in blocks_to_remove:
                            blocks_to_remove.append(check_pos)
                
                if blocks_to_remove:
                    for block_1_to_remove in blocks_to_remove:
                        remove_block_id = self.get_cell_id(*block_1_to_remove)
                        packet = build_packet(1, 0, 0, remove_block_id)
                        ser.write(packet)
                        print(f"  ├─ [REMOVE] id_rb=1, BlockID={remove_block_id}")
                        r, c = block_1_to_remove
                        lbl_remove = ctk.CTkLabel(self.grid_cells[r][c]["frame"], text="✖",
                                           width=40, height=40, fg_color="#ff5555", text_color="white",
                                           corner_radius=20, font=("Arial", 20, "bold"))
                        lbl_remove.place(relx=0.5, rely=0.5, anchor="center")
                        self.grid_cells[r][c]["overlays"].append(lbl_remove)
                        time.sleep(0.3)

            print(f"  ├─ [MOVE PHASE]")
            for i in range(len(segment_path) - 1):
                curr_pos = segment_path[i]
                next_pos = segment_path[i+1]
                step_block_id = self.get_cell_id(next_pos[0], next_pos[1])

                dr = next_pos[0] - curr_pos[0]
                dc = next_pos[1] - curr_pos[1]
                move_vec = (dr, dc)
                
                move_cmd = 0 
                if move_vec == current_facing: move_cmd = 1
                elif move_vec == left_turn_map[current_facing]:
                    move_cmd = 2
                    current_facing = move_vec 
                elif move_vec == right_turn_map[current_facing]:
                    move_cmd = 3
                    current_facing = move_vec 
                else: continue 
                
                nr, nc = next_pos
                cell_next = self.grid_cells[nr][nc]
                if cell_next["content"] and cell_next["content"]["number"] == 1:
                    print(f"  │  ├─ Obstacle ahead at {next_pos}, removing...")
                    lbl_obstacle = ctk.CTkLabel(
                        self.grid_cells[nr][nc]["frame"], text="⚠",
                        width=40, height=40, fg_color="#ff9800", text_color="white",
                        corner_radius=20, font=("Arial", 20, "bold")
                    )
                    lbl_obstacle.place(relx=0.5, rely=0.5, anchor="center")
                    self.grid_cells[nr][nc]["overlays"].append(lbl_obstacle)
                    
                    packet = build_packet(1, 0, 0, step_block_id)
                    ser.write(packet)
                    time.sleep(0.3)

                packet = build_packet(2, move_cmd, 4, step_block_id)
                ser.write(packet)
                print(f"  │  ├─ Move={move_cmd}, BlockID={step_block_id}")
                time.sleep(0.1) 
            
            if segment_action != "FINISH":
                print(f"  └─ [ACTION PHASE]")
                robot_pos = segment_path[-1]
                target_pos = segment_action
                action_block_id = self.get_cell_id(target_pos[0], target_pos[1])
                
                dr_act = target_pos[0] - robot_pos[0]
                dc_act = target_pos[1] - robot_pos[1]
                act_vec = (dr_act, dc_act)
                
                action_cmd = 4 
                if act_vec == current_facing: action_cmd = 1 
                elif act_vec == left_turn_map[current_facing]: action_cmd = 2 
                elif act_vec == right_turn_map[current_facing]: action_cmd = 3 
                
                if action_cmd != 4:
                    packet = build_packet(2, 0, action_cmd, action_block_id)
                    ser.write(packet)
                    print(f"     └─ Act={action_cmd}, BlockID={action_block_id}")
                    time.sleep(0.5)

        ser.close()
        print("\n" + "=" * 60)
        print("HOÀN THÀNH GỬI UART")
        print("=" * 60)
        self.info_label.configure(text=f"Đã gửi xong.")

    def run(self):
        self.root.mainloop()

if __name__ == "__main__":
    app = SelectPlaceApp()
    app.run()