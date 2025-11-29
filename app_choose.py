import customtkinter as ctk
import heapq
import itertools # Thư viện quan trọng để tạo tổ hợp và hoán vị

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
        self.root.title("Robot Pathfinding: Hybrid (Auto + Manual) + AU Logic")
        self.root.geometry("1000x700") # Mở rộng window để dễ nhìn

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
                cell_frame.grid(row=i, column=j, padx=8, pady=8)
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
                
                # Binding click cho ô (để chọn target thủ công)
                cell_frame.bind("<Button-1>", lambda e, pos=(i, j): self.cell_clicked(pos))

                row.append({
                    "frame": cell_frame,
                    "content": None,
                    "overlays": [],
                    "buttons": block_buttons,
                    "id_label": id_label,
                    "selected": False # Trạng thái chọn thủ công
                })
            self.grid_cells.append(row)

        # THANH CÔNG CỤ
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
            self.bottom_frame, text="CHẠY (Auto/Manual)", width=160, height=40,
            fg_color="#5cb85c", hover_color="#449d44",
            command=self.smart_run
        )
        self.run_btn.pack(side="left", padx=5)

        self.info_label = ctk.CTkLabel(
            self.root,
            text="Chế độ: Đặt khối.\nBấm 'Chọn ô' để chọn thủ công hoặc bấm 'CHẠY' để Auto.",
            width=250, height=60, wraplength=600, justify="left"
        )
        self.info_label.pack(pady=8)

        self.mode = "PLACE" # PLACE / DELETE / SELECT
        self.active_button = None
        self.selected_targets = [] # Danh sách các ô được chọn thủ công

    def get_cell_id(self, r, c):
        return (ROWS - 1 - r) * COLS + (COLS - 1 - c) + 1

    # --- HÀM XỬ LÝ CÔNG THỨC AU (MỚI THÊM) ---
    def calculate_au_step(self, current_pos, next_pos):
        """
        Tính toán bước đi dựa trên công thức AU:
        index = n - 1
        r = floor(index / 3)
        c = index % 3
        dx, dy, steps, rotations, Hướng
        """
        # 1. Lấy ID (n) của vị trí hiện tại và tiếp theo
        n1 = self.get_cell_id(current_pos[0], current_pos[1])
        n2 = self.get_cell_id(next_pos[0], next_pos[1])

        # 2. Tính Index và toạ độ Au (r, c) cho vị trí hiện tại (1)
        index1 = n1 - 1
        r_au1 = index1 // 3  # Tương đương floor(index / 3)
        c_au1 = index1 % 3   # Tương đương index % 3

        # 3. Tính Index và toạ độ Au (r, c) cho vị trí tiếp theo (2)
        index2 = n2 - 1
        r_au2 = index2 // 3
        c_au2 = index2 % 3

        # 4. Tính vector di chuyển dx, dy
        dx = c_au2 - c_au1
        dy = r_au2 - r_au1

        # 5. Tính Steps và Rotations
        steps = abs(dx) + abs(dy)
        total_rotations = steps * 500

        # 6. Xác định hướng văn bản
        directions = []
        if dx > 0: directions.append("Trái")
        if dx < 0: directions.append("Phải")
        if dy > 0: directions.append("Lên")
        if dy < 0: directions.append("Xuống")
        
        dir_str = " + ".join(directions) if directions else "Đứng yên"

        return {
            "n1": n1, "n2": n2,
            "r_au1": r_au1, "c_au1": c_au1,
            "r_au2": r_au2, "c_au2": c_au2,
            "dx": dx, "dy": dy,
            "steps": steps,
            "rotations": total_rotations,
            "direction_str": dir_str
        }

    def toggle_mode(self, new_mode, button):
        if self.mode == new_mode:
            # Tắt chế độ hiện tại -> Về PLACE
            self.mode = "PLACE"
            if self.active_button:
                self.active_button.configure(fg_color=self.active_button.default_color)
            self.active_button = None
            self.info_label.configure(text="Trở lại chế độ Đặt khối.")
        else:
            # Bật chế độ mới
            self.mode = new_mode
            if self.active_button:
                self.active_button.configure(fg_color=self.active_button.default_color)
            self.active_button = button
            button.default_color = button.cget("fg_color")
            button.configure(fg_color="yellow") # Highlight nút đang active
            
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
                self.info_label.configure(text=f"Đã xóa tại ({r},{c})")
        
        elif self.mode == "SELECT":
            # Logic chọn ô thủ công
            if not cell["selected"]:
                cell["frame"].configure(fg_color="orange")
                cell["selected"] = True
                self.selected_targets.append((r, c))
                self.info_label.configure(text=f"Đã chọn ID: {self.get_cell_id(r,c)}")
            else:
                cell["frame"].configure(fg_color="transparent")
                cell["selected"] = False
                if (r, c) in self.selected_targets:
                    self.selected_targets.remove((r, c))
                self.info_label.configure(text=f"Bỏ chọn ID: {self.get_cell_id(r,c)}")

    def place_block(self, number, position):
        r, c = position
        cell = self.grid_cells[r][c]
        
        # Nếu đang ở chế độ Xóa hoặc Chọn -> Không đặt khối (hoặc xử lý theo mode)
        if self.mode == "DELETE":
            self.cell_clicked(position) # Gọi hàm xóa
            return
        
        if self.mode == "SELECT":
            self.cell_clicked(position) # Gọi hàm chọn
            return

        # Chế độ PLACE
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
                
                # Reset trạng thái chọn
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

    # --- CÁC HÀM LOGIC TÌM ĐƯỜNG (ENGINE) ---

    def check_traversable_rules(self, r, c, virtual_grid=None):
        if not (0 <= r < ROWS and 0 <= c < COLS): return False
        
        if virtual_grid:
            status = virtual_grid[r][c]
            if status == "EMPTY" or status == "IGNORED":
                return True

        cell = self.grid_cells[r][c]
        if cell["content"] and cell["content"]["number"] == 3:
            return False
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
        dirs = [(-1,0),(0,-1),(0,1),(1,0)]
        for ndir, (dr, dc) in enumerate(dirs):
            nr, nc = r+dr, c+dc
            if self.check_traversable_rules(nr, nc, virtual_grid):
                priority = 0 if ndir == direction else 1
                yield (nr, nc, ndir, priority)

    def is_adjacent(self, pos1, pos2):
        return abs(pos1[0] - pos2[0]) + abs(pos1[1] - pos2[1]) == 1

    def h_score(self, current, target):
        return abs(current[0] - target[0]) + abs(current[1] - target[1])

    def min_h_score(self, pos, targets):
        if not targets: return 0
        return min(self.h_score(pos, target) for target in targets)

    def cost(self, r, c, virtual_grid=None):
        # Flat cost = 1 để ưu tiên đường ngắn nhất tuyệt đối
        return 1 

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

            for nr, nc, ndir, priority in self.neighbors(cur, direction, virtual_grid):
                move_cost = self.cost(nr, nc, virtual_grid)
                tentative_g = g + move_cost

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
            # Combo Logic: Thưởng nếu gắp liên tiếp 2 ô kề nhau
            if last_target_pos and self.is_adjacent(last_target_pos, target):
                combo_bonus += 2.5 

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
        path_home, _ = self.dijkstra_astar(current_starts, final_goals, use_arm=False, virtual_grid=virtual_grid)
        if not path_home: return float('inf'), []
        
        for r, c in path_home:
            total_steps += self.cost(r, c, virtual_grid)
            
        full_simulation_path.append((path_home, "FINISH"))
        final_score = total_steps - combo_bonus
        return final_score, full_simulation_path

    # --- HÀM CHẠY THÔNG MINH (HYBRID) ---
    def smart_run(self):
        # 1. Reset Overlays
        for r in range(ROWS):
            for c in range(COLS):
                for ov in self.grid_cells[r][c]["overlays"]: ov.destroy()
                self.grid_cells[r][c]["overlays"].clear()

        # 2. Xác định Input
        # Nếu người dùng đã chọn ô thủ công (Selected Mode)
        if self.selected_targets:
            print("\n>>> CHẾ ĐỘ THỦ CÔNG (MANUAL) <<<")
            self.solve_manual_targets()
        else:
            # Nếu không chọn gì -> Chế độ Tự động tìm R2
            print("\n>>> CHẾ ĐỘ TỰ ĐỘNG (AUTO) <<<")
            self.solve_auto_targets()

    def solve_manual_targets(self):
        # Logic: Dùng thuật toán tối ưu để đi qua các điểm đã chọn thủ công
        
        perms = list(itertools.permutations(self.selected_targets))
        
        best_cost = float('inf')
        best_sim = None
        best_perm = None

        for perm in perms:
            # LOGIC MỚI: Bắt buộc xuất phát từ cột của mục tiêu đầu tiên
            first_target_col = perm[0][1]
            forced_start = (ROWS - 1, first_target_col)
            
            # Ở chế độ thủ công, ta không tự ý loại bỏ khối nào (ignored = [])
            cost, sim_data = self.simulate_sequence([forced_start], perm, [])
            
            if cost < best_cost:
                best_cost = cost
                best_sim = sim_data
                best_perm = perm
        
        if best_sim:
            final_ids = [self.get_cell_id(*p) for p in best_perm]
            print(f"-> Manual Order: {final_ids}")
            self.visualize_result(best_sim, [])
            self.info_label.configure(text=f"Thủ công: Gắp theo thứ tự {final_ids}.")
        else:
            self.info_label.configure(text="Không tìm được đường đi cho các ô đã chọn.")

    def solve_auto_targets(self):
        # Logic: Tự tìm 2 khối 2 và loại 1 khối 1
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

        combos_2 = list(itertools.combinations(list_2s, 2))
        potential_discards = [None] + list_1s

        best_cost = float('inf')
        best_sim = None
        best_targets_set = None
        best_ignored_set = []

        for c2 in combos_2:
            active_targets = list(c2)
            for discard_r1 in potential_discards:
                current_ignored = [discard_r1] if discard_r1 else []
                permutations = list(itertools.permutations(active_targets))
                
                for perm in permutations:
                    # LOGIC MỚI: Bắt buộc xuất phát từ cột của mục tiêu đầu tiên
                    first_target_col = perm[0][1]
                    forced_start = (ROWS - 1, first_target_col)
                    
                    cost, sim_data = self.simulate_sequence([forced_start], perm, current_ignored)
                    if cost < best_cost:
                        best_cost = cost
                        best_sim = sim_data
                        best_targets_set = perm
                        best_ignored_set = current_ignored

        if best_sim:
            final_ids = [self.get_cell_id(*p) for p in best_targets_set]
            ignored_ids = [self.get_cell_id(*p) for p in best_ignored_set]
            print(f"-> Auto Pick: {final_ids}, Ignore: {ignored_ids}")
            self.visualize_result(best_sim, best_ignored_set)
            self.info_label.configure(text=f"Auto: Chọn {final_ids}. Loại {ignored_ids}.")
        else:
            self.info_label.configure(text="Không tìm thấy đường đi khả thi.")

    def visualize_result(self, simulation_path, ignored_blocks):
        # 1. Vẽ dấu X cho block bị loại
        for r, c in ignored_blocks:
            lbl_ignore = ctk.CTkLabel(self.grid_cells[r][c]["frame"], text="✖",
                               width=40, height=40, fg_color="#aaaaaa", text_color="white",
                               corner_radius=20, font=("Arial", 20, "bold"))
            lbl_ignore.place(relx=0.5, rely=0.5, anchor="center")
            self.grid_cells[r][c]["overlays"].append(lbl_ignore)

        # 2. Vẽ hành trình
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

        print("\n" + "="*60)
        print(" BẮT ĐẦU MÔ PHỎNG VÀ TÍNH TOÁN (AU FORMULA) ")
        print("="*60)

        for segment_path, segment_action in simulation_path:
            path_ids = [self.get_cell_id(r,c) for r,c in segment_path]
            
            if segment_action == "FINISH":
                print(f"\n>> PHÂN ĐOẠN: VỀ ĐÍCH")
                print(f"Path IDs: {path_ids}")
            else:
                picked_id = self.get_cell_id(segment_action[0], segment_action[1])
                standing_id = self.get_cell_id(segment_path[-1][0], segment_path[-1][1])
                print(f"\n>> PHÂN ĐOẠN {step_counter+1}: ĐI ĐẾN ĐIỂM GẮP")
                print(f"Path IDs: {path_ids}")
                print(f"Action: Đứng tại ID {standing_id} -> Gắp ID {picked_id}")
                draw_pick(segment_action, segment_path[-1], step_counter)
                step_counter += 1

            # --- IN RA CHI TIẾT CÔNG THỨC AU CHO PHÂN ĐOẠN NÀY ---
            print("   --- Chi tiết kỹ thuật (Au Formula) ---")
            for i in range(len(segment_path) - 1):
                curr = segment_path[i]
                next_node = segment_path[i+1]
                
                # Gọi hàm tính toán AU mới thêm
                au_data = self.calculate_au_step(curr, next_node)
                
                # Format output chuẩn kỹ thuật
                print(f"   [Step] ID:{au_data['n1']}->{au_data['n2']} | "
                      f"Idx:{au_data['n1']-1}->{au_data['n2']-1} | "
                      f"Au(r,c):({au_data['r_au1']},{au_data['c_au1']})->({au_data['r_au2']},{au_data['c_au2']}) | "
                      f"d({au_data['dx']:>2},{au_data['dy']:>2}) | "
                      f"Rot:{au_data['rotations']} | Hướng: {au_data['direction_str']}")
            # -----------------------------------------------------

            if not full_path_display: full_path_display.extend(segment_path)
            else: full_path_display.extend(segment_path[1:])

        print("="*60)
        
        # Vẽ số thứ tự bước đi lên GUI
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

    def run(self):
        self.root.mainloop()

if __name__ == "__main__":
    app = SelectPlaceApp()
    app.run()