import customtkinter as ctk
import heapq
import itertools
import time
import os       
import json     
from tkinter import simpledialog, messagebox
from gui_tkinter import set_state, STATE_FOREST, STATE_IDLE 
from config_uart.sent_uart import build_packet, send_packet_once, ser

try:
    from PIL import ImageGrab
except ImportError:
    ImageGrab = None


ctk.set_appearance_mode("System")
ctk.set_default_color_theme("blue")


ROWS = 4
COLS = 3
CELL_SIZE = 210
width_cell = 72
height_cell = 72


class SelectPlaceApp:
    def __init__(self):
        self.root = ctk.CTk()
        self.root.title("Robot Pathfinding: Hybrid & UART Control")
        self.root.geometry("890x550") 

        # --- Cấu hình Sân ---
        self.team_color = "RED"  

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

        # >>> THÊM 2 NÚT SO SÁNH & LƯU MAP TẠI ĐÂY <<<
        self.compare_btn = ctk.CTkButton(
            self.bottom_frame, text="So sánh", width=80, height=40,
            fg_color="#8e44ad", hover_color="#732d91",
            command=self.compare_saved_maps
        )
        self.compare_btn.pack(side="left", padx=5)

        self.save_map_btn = ctk.CTkButton(
            self.bottom_frame, text="Lưu map", width=80, height=40,
            fg_color="#2c3e50", hover_color="#1a252f",
            command=self.save_custom_map
        )
        self.save_map_btn.pack(side="left", padx=5)
        # >>> KẾT THÚC THÊM NÚT <<<

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
        self.best_targets_set = None
        self.best_ignored_set = []

        # >>> THÊM BIẾN CHO TÍNH NĂNG LƯU MAP <<<
        self.matched_custom_packets = None
        os.makedirs("saved_maps", exist_ok=True)  # Tạo thư mục nếu chưa có
        os.makedirs(os.path.join("saved_maps", "images"), exist_ok=True)  # Tạo thư mục images

        

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

        # --- Logic XÓA (Giữ nguyên) ---
        if self.mode == "DELETE":
            if cell["content"]:
                cell["content"]["widget"].destroy()
                cell["content"] = None
                for btn in cell["buttons"]:
                    btn.pack(side="left", expand=True, padx=5, pady=5)
                cell["id_label"].lift()
                self.info_label.configure(text=f"Đã xóa tại ({r},{c})")
            return # Kết thúc hàm nếu là xóa

        # --- Logic SELECT MỚI (Vẽ đường thủ công) ---
        elif self.mode == "SELECT":
            # 1. Kiểm tra xem ô đã chọn chưa (Không cho chọn lại ô cũ để tránh vòng lặp phức tạp)
            if cell["selected"]:
                self.info_label.configure(text=f"Ô ({r},{c}) đã có trong đường đi!")
                return

            # 2. Logic kiểm tra liền kề (Adjacency Rule)
            if not self.selected_targets:
                # Nếu là ô đầu tiên được chọn
                pass # Luôn cho phép chọn điểm xuất phát
            else:
                last_r, last_c = self.selected_targets[-1]
                # Tính khoảng cách Manhattan (chỉ cho phép đi ngang hoặc dọc 1 ô)
                dist = abs(r - last_r) + abs(c - last_c)
                if dist != 1:
                    self.info_label.configure(text=f"LỖI: Ô ({r},{c}) không nằm cạnh ô trước đó!", text_color="red")
                    return # Không làm gì cả

            # 3. Thêm vào đường đi và đổi màu
            self.selected_targets.append((r, c))
            cell["selected"] = True
            cell["frame"].configure(fg_color="#4caf50") # Màu xanh lá cho đường đi
            
            # 4. Hiển thị số bước ngay lập tức
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
        self.matched_custom_packets = None
        for r in range(ROWS):
            for c in range(COLS):
                cell = self.grid_cells[r][c]
                if cell["content"]:
                    cell["content"]["widget"].destroy()
                    cell["content"] = None
                for ov in cell["overlays"]:
                    ov.destroy()
                cell["overlays"].clear()
                
                # Reset trạng thái
                cell["selected"] = False
                cell["frame"].configure(fg_color="transparent") # Trả lại màu nền
                
                for btn in cell["buttons"]:
                    btn.pack(side="left", expand=True, padx=5, pady=5)
                cell["id_label"].lift()
        
        self.mode = "PLACE"
        self.selected_targets.clear() # Xóa danh sách đường vẽ tay
        if self.active_button:
            self.active_button.configure(fg_color=self.active_button.default_color)
            self.active_button = None
        self.info_label.configure(text="Lưới đã reset. Mời chọn lại chế độ.")

    # --- ENGINE ---
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
        
        # 1. Kiểm tra chính ô mục tiêu (Target)
        # Nếu là hàng 0 hoặc 3, được phép đi vào chính ô đó (Logic cũ)
        if r == 3 or r == 0:
            if self.check_traversable_rules(r, c, virtual_grid, target_pos=target_pos):
                points.append((r, c))
            # --- SỬA LỖI: ĐÃ XÓA DÒNG 'return points' TẠI ĐÂY ---
            # Để code chạy tiếp xuống dưới và tìm thêm các ô hàng xóm
        
        # Nếu không phải hàng 0,3 (hoặc logic chung), kiểm tra xem có đi vào được không
        elif self.check_traversable_rules(r, c, virtual_grid):
            points.append((r, c))

        # 2. Kiểm tra 4 ô xung quanh (Neighbors) để đứng gắp bằng tay
        # Code cũ không chạy phần này cho hàng 0 và 3, nên robot buộc phải đi vào ô mục tiêu
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

    # --- HÀM CHẠY THÔNG MINH ---
    def smart_run(self):
        for r in range(ROWS):
            for c in range(COLS):
                for ov in self.grid_cells[r][c]["overlays"]: ov.destroy()
                self.grid_cells[r][c]["overlays"].clear()

        # >>> THÊM LOGIC CHẶN NẾU ĐÃ TÌM THẤY MAP TUỲ CHỈNH <<<
        if self.matched_custom_packets is not None:
            print("\n>>> TÌM THẤY MAP ĐÃ LƯU: BỎ QUA TÌM ĐƯỜNG, ĐANG GỬI GÓI TIN ĐÃ CÀI <<<")
            self.send_custom_uart_packets()
            return

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
        
        # Đóng gói đường đi thủ công thành format cho UART
        manual_simulation = [(self.selected_targets, "FINISH")]
        
        self.simulation_path = manual_simulation
        
        # Hiển thị thông báo sẵn sàng
        final_ids = [self.get_cell_id(*p) for p in self.selected_targets]
        print(f"-> Path IDs: {final_ids}")
        self.info_label.configure(text=f"Đã lưu đường đi thủ công ({len(self.selected_targets)} bước). Sẵn sàng GỬI UART.")
    
    #Hàm tính toán chạy tự động
    #Hàm tính toán chạy tự động (ĐÃ SỬA THEO CHIẾN THUẬT ĐI THẲNG & GẮP 2 BÊN)
    def solve_auto_targets(self):
        list_1s = []
        list_2s = []
        # Lấy danh sách vị trí các khối
        for r in range(ROWS):
            for c in range(COLS):
                content = self.grid_cells[r][c]["content"]
                if content:
                    if content["number"] == 1: list_1s.append((r, c))
                    elif content["number"] == 2: list_2s.append((r, c))
        
        if not list_2s:
            self.info_label.configure(text=f"Lỗi: Không có khối số 2 nào trên sân.")
            return

        print(f">>> Có {len(list_2s)} khối 2. Bắt đầu phân tích chiến thuật AUTO ĐI THẲNG...")

        # --- 1. TÌM CỘT DỌC TỐT NHẤT ---
        # Ưu tiên cột: 1. Không có khối 3 chặn đường. 2. Ăn được nhiều khối 2 nhất (gồm cả trái/phải)
        best_col = -1
        max_score = -1

        for c in range(COLS):
            # Kiểm tra xem cột này có bị khối 3 (tường) chặn không
            is_blocked = False
            for r in range(ROWS):
                if self.grid_cells[r][c]["content"] and self.grid_cells[r][c]["content"]["number"] == 3:
                    is_blocked = True
                    break
            
            if is_blocked:
                continue # Bỏ qua cột này nếu bị chặn bởi khối 3

            # Tính điểm (số khối 2 có thể gắp được nếu đi dọc cột này)
            score = 0
            for r in range(ROWS):
                # Khối nằm ngay trên đường đi
                if (r, c) in list_2s: score += 1
                # Khối nằm bên trái
                if c - 1 >= 0 and (r, c - 1) in list_2s: score += 1
                # Khối nằm bên phải
                if c + 1 < COLS and (r, c + 1) in list_2s: score += 1

            if score > max_score:
                max_score = score
                best_col = c

        if best_col == -1:
            self.info_label.configure(text="LỖI: Tất cả các cột thẳng đều bị chặn bởi Khối 3. Không thể auto đi thẳng.")
            return

        print(f">>> Chọn cột đi thẳng: {best_col} (Có thể gắp tối đa {max_score} khối 2)")

        # --- 2. TẠO HÀNH TRÌNH ĐI THẲNG VÀ GẮP ---
        sim_path = []
        path_accumulated = [(3, best_col)] # Bắt buộc xuất phát từ hàng đáy (hàng 3) của cột được chọn

        # Đi từ dưới lên trên (Hàng 3 -> 0)
        for r in range(3, -1, -1):
            if r < 3: 
                # Cập nhật tọa độ đi thẳng lên
                path_accumulated.append((r, best_col))

            # a. Xử lý gắp khối nằm chính giữa đường (nếu có)
            if (r, best_col) in list_2s:
                sim_path.append((list(path_accumulated), (r, best_col)))
                path_accumulated = [(r, best_col)] # Reset chặng

            # b. Quét 2 bên (Trái, Phải) xem có khối 2 không để thò tay ra gắp
            for dc in [-1, 1]:
                c_adj = best_col + dc
                if 0 <= c_adj < COLS: # Đảm bảo không quét vọt ra ngoài bàn cờ
                    if (r, c_adj) in list_2s:
                        sim_path.append((list(path_accumulated), (r, c_adj)))
                        path_accumulated = [(r, best_col)] # Reset chặng

        # --- 3. CHẠY THẲNG LÊN ĐÍCH (HÀNG 0) ---
        if path_accumulated[-1] != (0, best_col):
            while path_accumulated[-1][0] > 0:
                next_r = path_accumulated[-1][0] - 1
                path_accumulated.append((next_r, best_col))
                
        # Cắm cờ FINISH
        sim_path.append((list(path_accumulated), "FINISH"))

        # --- 4. GHI NHẬN VÀ XUẤT KẾT QUẢ ---
        self.simulation_path = sim_path
        self.best_ignored_set = []
        
        # Trích xuất ID các ô đã gắp để hiển thị text
        final_ids = []
        for segment, action in sim_path:
            if action != "FINISH":
                final_ids.append(self.get_cell_id(*action))

        print(f"-> AUTO ĐI THẲNG ({self.team_color}): {final_ids}")
        
        # Vẽ giao diện
        self.visualize_result(sim_path, [])
        self.info_label.configure(text=f"AUTO ĐI THẲNG. Đã chọn các ô: {final_ids}. Sẵn sàng gửi UART.")
            
    # --- HÀM VẼ GIAO DIỆN KẾT QUẢ (ĐÃ CẬP NHẬT VẼ BÚA) ---
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

        # --- VÒNG LẶP VẼ ĐƯỜNG ĐI VÀ CÁI BÚA ---
        for idx, (r, c) in enumerate(full_path_display):
            # 1. Vẽ cái búa nếu đi qua Khối 1
            cell = self.grid_cells[r][c]
            if cell["content"] and cell["content"]["number"] == 1:
                # Kiểm tra để tránh vẽ trùng
                if not any(isinstance(x, ctk.CTkLabel) and x.cget("text") == "🔨" for x in cell["overlays"]):
                    lbl_break = ctk.CTkLabel(cell["frame"], text="🔨",
                                           width=30, height=30, fg_color="#d35400", text_color="white",
                                           corner_radius=15, font=("Arial", 18, "bold"))
                    lbl_break.place(relx=0.8, rely=0.5, anchor="center") # Đặt bên phải
                    cell["overlays"].append(lbl_break)

            # 2. Vẽ số bước đi
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
        has_climbed = False # Cờ theo dõi: Robot đã leo lên bậc hay chưa
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
                    print(f"  │  ├─ Phát hiện KHỐI 1. Gửi lệnh PHÁ trước và check khối 1 đã được phá chưa.")
                    time.sleep(0.3)
                    packet = build_packet(1, 2, 0, 0, entry_id)
                    print(f"  │  └─ [BREAK BLOCK] id_rb=1, Move=2, Act=0, BlockID={entry_id}")
                    ser.write(packet)
                    time.sleep(0.3)
                    packet_check = build_packet(2, 2, 5, 5, entry_id) 
                    ser.write(packet_check)
                
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

                # ĐÃ XÓA LỆNH TỰ ĐỘNG LEO BẬC (2,2,1,4) TẠI ĐÂY ĐỂ CHỜ QUYẾT ĐỊNH
                is_first_entry = False

            # --- KIỂM TRA LEO BẬC THỰC SỰ ---
            # Chỉ leo bậc (Act=4) khi đường đi thực sự chuyển từ hàng 3 (đất) lên hàng 2 (bậc)
            if not has_climbed:
                if len(segment_path) > 1 and segment_path[0][0] == 3 and segment_path[1][0] < 3:
                    entry_id = self.get_cell_id(segment_path[0][0], segment_path[0][1])
                    print(f"  ├─ [CLIMB STEP] Bắt đầu leo vào sa bàn tại ID={entry_id}")
                    time.sleep(0.3)
                    packet = build_packet(2, 2, 1, 4, entry_id)
                    count_rb2 += 1
                    ser.write(packet)
                    has_climbed = True
                    time.sleep(0.3)

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

                # Nếu di chuyển dọc theo cửa (Cùng hàng 3), thì dùng Act=10 thay vì Act=4
                act_cmd = 4 
                if curr_pos[0] == 3 and next_pos[0] == 3:
                    act_cmd = 10
                    print(f"  │  ├─ [LATERAL DOOR] Di chuyển ngang ở cửa! Chuyển Act thành 10.")
                
                nr, nc = next_pos
                cell_next = self.grid_cells[nr][nc]
                
                if cell_next["content"] and cell_next["content"]["number"] == 1:
                    print(f"  │  ├─ ⚠ KHỐI 1 chắn đường tại ID={step_block_id}. Gửi lệnh PHÁ và check.")
                    time.sleep(0.3)
                    packet = build_packet(1, 2, 0, 0, step_block_id)
                    ser.write(packet)
                    time.sleep(0.3)
                    packet_check = build_packet(2, 2, 5, 5, step_block_id) 
                    ser.write(packet_check)
                    
                    if not any(isinstance(x, ctk.CTkLabel) and x.cget("text") == "🔨" for x in cell_next["overlays"]):
                        lbl_break = ctk.CTkLabel(cell_next["frame"], text="🔨", width=30, height=30, fg_color="#d35400", corner_radius=15)
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

                        lbl_picked = ctk.CTkLabel(cell_next["frame"], text="✓", width=24, height=24, fg_color="#ff5555", corner_radius=12)
                        lbl_picked.place(relx=0.85, rely=0.15, anchor="center")
                        cell_next["overlays"].append(lbl_picked)
                        time.sleep(0.5)

                time.sleep(0.3)
                packet = build_packet(2, 2, move_cmd, act_cmd, step_block_id)
                count_rb2 += 1
                ser.write(packet)
                move_desc = ["?", "Đi thẳng", "Rẽ trái", "Rẽ phải"][move_cmd]
                print(f"  │  ├─ [MOVE] id_rb=2, Move={move_cmd} ({move_desc}), Act={act_cmd}, BlockID={step_block_id}")
                time.sleep(0.1) 
            
            # --- ACTION PHASE (CUỐI SEGMENT) ---
            if segment_action != "FINISH":
                target_pos = segment_action
                action_block_id = self.get_cell_id(target_pos[0], target_pos[1])
                
                if action_block_id in picked_blocks:
                    print(f"  └─ [SKIP ACTION] BlockID={action_block_id} đã được gắp.")
                else:
                    print(f"  └─ [ACTION PHASE] Xử lý gắp tại đích...")
                    robot_pos = segment_path[-1] 
                    
                    dr_act = target_pos[0] - robot_pos[0]
                    dc_act = target_pos[1] - robot_pos[1]
                    act_vec = (dr_act, dc_act)
                    
                    action_cmd = 4 
                    if act_vec != (0,0):
                        if act_vec == current_facing: action_cmd = 1 
                        elif act_vec == left_turn_map[current_facing]: action_cmd = 2 
                        elif act_vec == right_turn_map[current_facing]: action_cmd = 3 
                    
                    # LOGIC QUAN TRỌNG NHẤT CHO YÊU CẦU CỦA BẠN NẰM TẠI ĐÂY:
                    if not has_climbed and robot_pos[0] == 3 and target_pos[0] == 3 and robot_pos != target_pos:
                        # Nếu robot chưa leo (còn ở cửa) và cần lấy khối trái/phải -> Gửi lệnh chạy ngang Act=10
                        lateral_cmd = 2 if action_cmd == 2 else 3
                        
                        time.sleep(0.3)
                        packet = build_packet(2, 2, lateral_cmd, 10, action_block_id)
                        count_rb2 += 1
                        ser.write(packet)
                        
                        desc = "Ngang Trái (Ở Cửa)" if lateral_cmd == 2 else "Ngang Phải (Ở Cửa)"
                        print(f"     └─ [ACTION SPECIAL] id_rb=2, Move={lateral_cmd}, Act=10 ({desc}), BlockID={action_block_id}")
                        time.sleep(0.3)
                    else:
                        # Hành động gắp bình thường khi đã ở trên sa bàn
                        time.sleep(0.3)
                        packet = build_packet(2, 2, 0, action_cmd, action_block_id)
                        count_rb2 += 1
                        ser.write(packet)
                        
                        act_desc = ["?", "Gắp thẳng", "Gắp trái", "Gắp phải", "Gắp tại chỗ"][action_cmd]
                        print(f"     └─ [ACTION NORMAL] id_rb=2, Move=0, Act={action_cmd} ({act_desc}), BlockID={action_block_id}")
                        time.sleep(0.3)
                        
                    picked_blocks.append(action_block_id)

        # --- SEND END PACKET IF EXITED AT GATE 10/11/12 ---
        if traveled_path:
            last_pos = traveled_path[-1]
            last_id = self.get_cell_id(last_pos[0], last_pos[1])
            if last_id in [10, 11, 12]:
                print(f"  ├─ [END PACKET] Gửi gói END (2,2,20,20) tới ID={last_id}")
                end_packet = build_packet(2, 2, 20, 20, last_id)
                ser.write(end_packet)
                time.sleep(0.1)

        print("\n" + "=" * 60)
        print("HOÀN THÀNH GỬI UART")
        print(f"Tổng packet với id_rb=2 đã gửi: {count_rb2}")
        print("=" * 60)
        self.info_label.configure(text=f"Đã gửi xong ({self.team_color}). Tổng id_rb=2: {count_rb2}")
        
    def get_map_signature(self, team_color=None):
        """Lấy sơ đồ hiện tại của map để lưu trữ và so sánh chính xác 100%"""
        if team_color is None:
            team_color = self.team_color
        signature = {
            "team": team_color,
            "blocks_1": [],
            "blocks_2": [],
            "blocks_3": [],
            "selected_path": list(self.selected_targets)
        }
        for r in range(ROWS):
            for c in range(COLS):
                content = self.grid_cells[r][c]["content"]
                if content:
                    num = content["number"]
                    signature[f"blocks_{num}"].append((r, c))
                    
        # Sort lại để dù đặt khối theo thứ tự nào thì so sánh vẫn ra kết quả giống nhau
        for key in ["blocks_1", "blocks_2", "blocks_3"]:
            signature[key].sort()
        return signature

    def capture_screenshot(self, filename):
        if ImageGrab is None:
            messagebox.showerror("Lỗi", "Cần cài đặt PIL để lưu hình ảnh. Chạy: pip install pillow")
            return
        try:
            x = self.root.winfo_rootx()
            y = self.root.winfo_rooty()
            width = self.root.winfo_width()
            height = self.root.winfo_height()
            img = ImageGrab.grab(bbox=(x, y, x + width, y + height))
            img.save(filename)
        except Exception as e:
            messagebox.showerror("Lỗi", f"Không thể lưu hình ảnh: {e}")

    def get_mirrored_packet(self, pkt):
        """
        Đổi ID (vị trí thứ 5 trong mảng) sang vị trí đối xứng của sân kia.
        Ví dụ: 1 <-> 3, 4 <-> 6, 7 <-> 9, 10 <-> 12. Ở giữa (2, 5, 8, 11) giữ nguyên.
        """
        new_pkt = list(pkt)
        if len(new_pkt) >= 5:
            target_id = new_pkt[4] # val5 (ID của ô)
            if 1 <= target_id <= 12:
                # Thuật toán lật ID đối xứng theo hàng
                row_start = ((target_id - 1) // 3) * 3 + 1
                offset = (target_id - 1) % 3
                new_pkt[4] = row_start + (2 - offset)
        return new_pkt

    def save_custom_map(self):
        # 1. Vòng lặp yêu cầu cài gói tin
        packets_to_save = []
        messagebox.showinfo("Cài đặt Map", "Bắt đầu cài đặt gói tin cho map này.\nNhập từng gói tin, nhấn Cancel hoặc để trống để hoàn thành.")
        
        while True:
            pkt_str = simpledialog.askstring(
                "Cài đặt gói tin UART", 
                "Nhập gói tin định dạng: val1,val2,val3,val4,val5\n(Ví dụ: 2,1,11,11,11)\n\nNhấn OK để thêm gói tiếp.\nĐể trống hoặc nhấn Cancel để HOÀN THÀNH."
            )
            
            if not pkt_str: # Nếu người dùng ấn Cancel hoặc để trống
                break
                
            try:
                parts = [int(x.strip()) for x in pkt_str.split(',')]
                if len(parts) == 5:
                    packets_to_save.append(parts)
                    print(f">>> Đã thêm vào hàng đợi gói: {parts}")
                else:
                    messagebox.showerror("Lỗi", "Gói tin phải bao gồm đúng 5 chữ số cách nhau bằng dấu phẩy!")
            except ValueError:
                messagebox.showerror("Lỗi", "Chỉ chấp nhận số nguyên và dấu phẩy!")

        # 2. Lưu cho cả hai team nếu có packets
        if packets_to_save:
            timestamp = int(time.time())
            saved_teams = []
            for team in ["RED", "BLUE"]:
                current_sig = self.get_map_signature(team)

                # >>> TỰ ĐỘNG ĐỔI ID GÓI TIN CHO SÂN ĐỐI DIỆN <<<
                team_packets = []
                if team != self.team_color:
                    for pkt in packets_to_save:
                        team_packets.append(self.get_mirrored_packet(pkt))
                else:
                    team_packets = packets_to_save
                # >>> KẾT THÚC ĐỔI ID <<<

                # Kiểm tra chống trùng lặp map cho team này
                duplicate = False
                for filename in os.listdir("saved_maps"):
                    if filename.endswith(".json"):
                        try:
                            with open(os.path.join("saved_maps", filename), "r") as f:
                                data = json.load(f)
                                saved_sig = data.get("signature", {})
                                for k in ["blocks_1", "blocks_2", "blocks_3", "selected_path"]:
                                    if k in saved_sig:
                                        saved_sig[k] = [tuple(x) for x in saved_sig[k]]
                                if saved_sig == current_sig:
                                    messagebox.showwarning("Cảnh báo", f"Map cho {team} trùng lặp với {filename}!")
                                    duplicate = True
                                    break
                        except Exception as e:
                            print(f"Lỗi đọc file {filename}: {e}")
                
                if not duplicate:
                    map_data = {
                        "signature": current_sig,
                        "packets": team_packets  # <--- Lưu mảng gói tin đã xử lý ID
                    }
                    save_path = os.path.join("saved_maps", f"map_team{team}_{timestamp}.json")
                    with open(save_path, "w") as f:
                        json.dump(map_data, f)
                    
                    # Lưu hình ảnh
                    img_path = os.path.join("saved_maps", "images", f"map_team{team}_{timestamp}.png")
                    self.capture_screenshot(img_path)
                    
                    saved_teams.append(team)
            
            if saved_teams:
                messagebox.showinfo("Thành công", f"Đã lưu map cho {', '.join(saved_teams)} với {len(packets_to_save)} gói tin và hình ảnh!")
            else:
                messagebox.showinfo("Đã hủy", "Tất cả map đều trùng lặp, không lưu gì.")
        else:
            messagebox.showinfo("Đã hủy", "Bạn chưa nhập gói tin nào nên Map không được lưu.")

    def compare_saved_maps(self):
        current_sig = self.get_map_signature()
        self.matched_custom_packets = None

        for filename in os.listdir("saved_maps"):
            if filename.endswith(".json"):
                try:
                    with open(os.path.join("saved_maps", filename), "r") as f:
                        data = json.load(f)
                        saved_sig = data.get("signature", {})
                        
                        for k in ["blocks_1", "blocks_2", "blocks_3", "selected_path"]:
                            if k in saved_sig:
                                saved_sig[k] = [tuple(x) for x in saved_sig[k]]
                        
                        if saved_sig == current_sig:
                            self.matched_custom_packets = data.get("packets", [])
                            print(f"\n>>> [SO SÁNH] Map của bạn TRÙNG KHỚP với: {filename}")
                            self.info_label.configure(text=f"Đã so sánh giống map đã lưu!\nBấm 'TÌM ĐƯỜNG' để gửi {len(self.matched_custom_packets)} gói cài sẵn.", text_color="green")
                            messagebox.showinfo("Khớp Map!", "Đã nhận diện được map!\nNhấn TÌM ĐƯỜNG để truyền các gói tin đã cài đặt.")
                            return
                except Exception as e:
                    print(f"Lỗi đọc file {filename}: {e}")
        
        self.info_label.configure(text="Không tìm thấy map đã lưu nào khớp với bàn cờ này.", text_color="red")
        messagebox.showinfo("Không khớp", "Bàn cờ hiện tại chưa từng được lưu trong hệ thống.")

    def send_custom_uart_packets(self):
        if not ser or not ser.is_open:
            print("[UART ERROR] Cổng UART không mở!")
            self.info_label.configure(text="Lỗi UART: Port chưa kết nối")
            return
            
        print("\n" + "=" * 60)
        print("BẮT ĐẦU GỬI GÓI TIN ĐƯỢC CÀI ĐẶT RIÊNG (TỪ MAP LƯU TRỮ)")
        print("=" * 60)
        
        for idx, pkt in enumerate(self.matched_custom_packets):
            packet_bytes = build_packet(*pkt)
            ser.write(packet_bytes)
            print(f"  ├─ [CUSTOM PACKET {idx+1}] Đã gửi: {pkt}")
            time.sleep(0.3) # Giãn cách một chút giữa các gói tự do
            
        print("=" * 60)
        print("HOÀN THÀNH GỬI UART TUỲ CHỈNH")
        print("=" * 60)
        
        self.info_label.configure(text=f"✓ Đã gửi thành công {len(self.matched_custom_packets)} gói tin cài sẵn!", text_color="black")
        self.matched_custom_packets = None # Reset cờ sau khi gửi xong

    def run_algothism_forest(self):
        self.root.mainloop()


if __name__ == "__main__":
    app = SelectPlaceApp()
    app.run_algothism_forest()