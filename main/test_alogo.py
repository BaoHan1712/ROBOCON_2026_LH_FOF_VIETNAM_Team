import customtkinter as ctk
import heapq
import itertools
import time
from tkinter import simpledialog, messagebox
from gui_tkinter import set_state, STATE_FOREST, STATE_IDLE 
from config_uart.sent_uart import build_packet, send_packet_once, ser

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
        self.root.geometry("880x580")  # Compact layout

        self.team_color = "RED"  

        self.root.protocol("WM_DELETE_WINDOW", self.on_closing)

        self.main_frame = ctk.CTkFrame(self.root)
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
                    btn.pack(side="left", expand=True, padx=2, pady=2)
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
                font=("Arial", 13, "bold"),
                text_color="#7ec8e3",
                justify="center"
            )
            door_label.place(relx=0.5, rely=0.5, anchor="center")

            door_id_label = ctk.CTkLabel(
                door_frame,
                text=f"D{j+1}",
                width=28, height=20,
                corner_radius=4,
                font=("Arial", 10, "bold"),
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
        self.bottom_frame = ctk.CTkFrame(self.root)
        self.bottom_frame.pack(side="bottom", padx=10, pady=5, fill="x")

        self.team_btn = ctk.CTkButton(
            self.bottom_frame, text="Sân: ĐỎ (RED)", width=120, height=40,
            fg_color="#d32f2f", hover_color="#b71c1c",
            command=self.toggle_team
        )
        self.team_btn.pack(side="left", padx=3)

        self.reset_btn = ctk.CTkButton(
            self.bottom_frame, text="Reset", width=80, height=40,
            fg_color="#d9534f", hover_color="#c9302c",
            command=self.reset_grid
        )
        self.reset_btn.pack(side="left", padx=3)

        self.delete_btn = ctk.CTkButton(
            self.bottom_frame, text="Xóa", width=80, height=40,
            fg_color="#f0ad4e", hover_color="#ec971f",
            command=lambda: self.toggle_mode("DELETE", self.delete_btn)
        )
        self.delete_btn.pack(side="left", padx=3)

        self.select_btn = ctk.CTkButton(
            self.bottom_frame, text="Chọn ô", width=100, height=40,
            fg_color="#5bc0de", hover_color="#31b0d5",
            command=lambda: self.toggle_mode("SELECT", self.select_btn)
        )
        self.select_btn.pack(side="left", padx=3)

        self.run_btn = ctk.CTkButton(
            self.bottom_frame, text="TÌM ĐƯỜNG", width=120, height=40,
            fg_color="#5cb85c", hover_color="#449d44",
            command=self.smart_run
        )
        self.run_btn.pack(side="left", padx=3)

        self.send_btn = ctk.CTkButton(
            self.bottom_frame, text="GỬI UART", width=120, height=40,
            fg_color="#f0ad4e", hover_color="#ec971f",
            command=self.sent_and_close, 
        )
        self.send_btn.pack(side="left", padx=3)

        self.mode_btn = ctk.CTkButton(
            self.bottom_frame, text="Mode: Normal", width=120, height=40,
            fg_color="#5bc0de", hover_color="#31b0d5",
            command=self.toggle_forest_mode
        )
        self.mode_btn.pack(side="left", padx=3)

        self.info_label = ctk.CTkLabel(
            self.root,
            text="Chế độ: Đặt khối.\nBấm 'TÌM ĐƯỜNG' để tìm đường, sau đó 'GỬI UART' để truyền.",
            width=250, height=50, wraplength=600, justify="left", font=("Arial", 9)
        )
        self.info_label.pack(pady=3)

        self.mode = "PLACE"
        self.active_button = None
        self.selected_targets = []
        self.simulation_path = None
        self.best_targets_set = None
        self.best_ignored_set = []
        self.forest_mode = "normal"  # Mode gửi packet (normal hoặc retry2)

        self.refresh_grid_ids()

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

        if self.mode == "DELETE":
            if cell["content"]:
                cell["content"]["widget"].destroy()
                cell["content"] = None
                for btn in cell["buttons"]:
                    btn.pack(side="left", expand=True, padx=5, pady=5)
                cell["id_label"].lift()
                self.info_label.configure(text=f"Đã xóa tại ({r},{c})")
            return

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
        self.info_label.configure(text=f"Đang gửi UART (Sân {self.team_color})...")
        self.process_and_send_uart(self.simulation_path)

    # =========================================================================
    # SMART RUN
    # =========================================================================
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
            is_blocked = any(
                self.grid_cells[r][c]["content"] and self.grid_cells[r][c]["content"]["number"] == 3
                for r in range(ROWS)
            )
            if is_blocked:
                continue
            score = sum(
                1 for r in range(ROWS) for dc in [0, -1, 1]
                if 0 <= c + dc < COLS and (r, c + dc) in list_2s
            )
            if score > max_score:
                max_score = score
                best_col = c

        if best_col == -1:
            self.info_label.configure(text="LỖI: Tất cả các cột đều bị chặn bởi Khối 3.")
            return

        print(f">>> Chọn cột đi thẳng: {best_col}")

        # --- 2. XÂY DỰNG SIM_PATH ---
        sim_path = []
        remaining_entry = list(list_2s_at_entry)

        # === TỐI ƯU HÓA THỨ TỰ GẮP BỤC BẰNG HOÁN VỊ TẤT CẢ TRƯỜNG HỢP ===
        # Chọn thứ tự gắp bục sao cho quãng đường (đi ngang + quay về best_col) là ngắn nhất.
        if remaining_entry:
            best_perm = None
            min_dist = float('inf')
            
            for perm in itertools.permutations(remaining_entry):
                dist = 0
                curr_col = perm[0][1]
                for target in perm[1:]:
                    dist += abs(target[1] - curr_col)
                    curr_col = target[1]
                # Thêm khoảng cách từ điểm gắp cuối cùng đến best_col để chuẩn bị leo lên sa bàn
                dist += abs(best_col - curr_col)
                
                if dist < min_dist:
                    min_dist = dist
                    best_perm = perm
                    
            ordered_entry = list(best_perm)
            door_start_col = ordered_entry[0][1]
        else:
            ordered_entry = []
            door_start_col = best_col

        current_door_col = door_start_col

        # --- 2a. Các segment gắp khối ở bục (từ cửa, không leo) ---
        for target in ordered_entry:
            target_col = target[1]

            # Đường đi ngang trong cửa từ current_door_col đến target_col
            door_path = [(DOOR_ROW, current_door_col)]
            c = current_door_col
            while c != target_col:
                c += 1 if target_col > c else -1
                door_path.append((DOOR_ROW, c))

            sim_path.append((door_path, target))
            current_door_col = target_col

        # --- 2b. Segment leo lên sa bàn ---
        climb_door_path = [(DOOR_ROW, current_door_col)]
        c = current_door_col
        while c != best_col:
            c += 1 if best_col > c else -1
            climb_door_path.append((DOOR_ROW, c))
        # Thêm điểm leo lên bục (ROWS-1, best_col) = điểm đầu tiên trên sa bàn
        climb_door_path.append((ROWS - 1, best_col))

        # --- 2c. Đường đi thẳng trên sa bàn ---
        board_entry = (ROWS - 1, best_col)
        board_accumulated = [board_entry] 

        for r in range(ROWS - 1, -1, -1):
            if r < ROWS - 1:
                board_accumulated.append((r, best_col))

            if (r, best_col) in list_2s_on_board:
                if not any(a not in ("FINISH",) and isinstance(a, tuple) and a[0] < ROWS - 1
                           for _, a in sim_path):
                    full_seg = climb_door_path + board_accumulated[1:]
                else:
                    full_seg = list(board_accumulated)

                sim_path.append((full_seg, (r, best_col)))
                board_accumulated = [(r, best_col)]
                climb_door_path = [] 

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
        entry_ids = [self.get_cell_id(*p) for p in list_2s_at_entry]

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
        for r, c in ignored_blocks:
            lbl = ctk.CTkLabel(self.grid_cells[r][c]["frame"], text="✖",
                               width=40, height=40, fg_color="#aaaaaa", text_color="white",
                               corner_radius=20, font=("Arial", 20, "bold"))
            lbl.place(relx=0.5, rely=0.5, anchor="center")
            self.grid_cells[r][c]["overlays"].append(lbl)

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
                                        font=("Arial", 12, "bold"),
                                        text_color="#00ff88", fg_color="transparent")
                lbl_start.place(relx=0.5, rely=0.25, anchor="center")
                door["overlays"].append(lbl_start)
            
            if col in door_movements:
                lbl_dir = ctk.CTkLabel(door["frame"], text=door_movements[col],
                                      font=("Arial", 16, "bold"),
                                      text_color="#ffaa00", fg_color="transparent")
                lbl_dir.place(relx=0.5, rely=0.65, anchor="center")
                door["overlays"].append(lbl_dir)
        
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

                if 0 <= pr < ROWS and 0 <= pc < COLS:
                    lbl_picked = ctk.CTkLabel(self.grid_cells[pr][pc]["frame"], text="✓",
                                       width=24, height=24, fg_color="#ff5555",
                                       corner_radius=12, font=("Arial", 14, "bold"))
                    lbl_picked.place(relx=0.85, rely=0.15, anchor="center")
                    self.grid_cells[pr][pc]["overlays"].append(lbl_picked)

                if 0 <= lr < ROWS and 0 <= lc < COLS:
                    lbl_step = ctk.CTkLabel(self.grid_cells[lr][lc]["frame"], text=str(step_counter),
                                       width=24, height=24, fg_color="#444", text_color="white",
                                       corner_radius=12, font=("Arial", 11, "bold"))
                    lbl_step.place(relx=0.85, rely=0.85, anchor="center")
                    self.grid_cells[lr][lc]["overlays"].append(lbl_step)

                step_counter += 1
                ext = segment_path[1:] if full_path_display else segment_path
                full_path_display.extend(ext)

        sa_ban_path = [(r, c) for r, c in full_path_display if 0 <= r < ROWS and 0 <= c < COLS]

        for idx, (r, c) in enumerate(sa_ban_path):
            cell = self.grid_cells[r][c]
            if cell["content"] and cell["content"]["number"] == 1:
                if not any(isinstance(x, ctk.CTkLabel) and x.cget("text") == "🔨" for x in cell["overlays"]):
                    lbl_b = ctk.CTkLabel(cell["frame"], text="🔨", width=30, height=30,
                                         fg_color="#d35400", text_color="white",
                                         corner_radius=15, font=("Arial", 18, "bold"))
                    lbl_b.place(relx=0.8, rely=0.5, anchor="center")
                    cell["overlays"].append(lbl_b)

            color = "#7be495"
            if idx == 0: color = "#3498db"
            if idx == len(sa_ban_path) - 1: color = "#f1c40f"

            lbl = ctk.CTkLabel(cell["frame"], text=str(idx), width=28, height=28,
                               fg_color=color, corner_radius=8, font=("Arial", 12, "bold"))
            has_important = any(isinstance(x, ctk.CTkLabel) and x.cget("text") in ["✖", "✓"]
                                for x in cell["overlays"])
            lbl.place(relx=0.2, rely=0.2 if has_important else 0.85, anchor="center")
            cell["overlays"].append(lbl)

        if hasattr(self, '_best_col'):
            door = self.door_cells[self._best_col]
            lbl_d = ctk.CTkLabel(door["frame"], 
                                 font=("Arial", 13, "bold"),
                                 text_color="#00ff88", fg_color="transparent")
            lbl_d.place(relx=0.5, rely=0.5, anchor="center")
            door["overlays"].append(lbl_d)

    # =========================================================================
    # PROCESS AND SEND UART
    # =========================================================================
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
            last_r, last_c = traveled_path[-1]
            if 0 <= last_r < ROWS and 0 <= last_c < COLS:
                last_id = self.get_cell_id(last_r, last_c)
                if last_id in [10, 11, 12]:
                    print(f"\n  ├─ [END PACKET] Gửi: (2, 2, 20, 20, {last_id})")
                    ser.write(build_packet(2, 2, 20, 20, last_id))
                    time.sleep(0.1)

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

# if __name__ == "__main__":
#     app = SelectPlaceApp()
#     app.run_algothism_forest()