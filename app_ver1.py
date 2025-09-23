import customtkinter as ctk
from collections import deque
import heapq

ctk.set_appearance_mode("System")
ctk.set_default_color_theme("blue")

ROWS = 4
COLS = 3


class SelectPlaceApp:
    def __init__(self):
        self.root = ctk.CTk()
        self.root.title("Chọn khối và đặt vào lưới")
        self.root.geometry("720x720")

        # Khung bên trái (lưới 4x3)
        self.left_frame = ctk.CTkFrame(self.root)
        self.left_frame.pack(side="left", padx=20, pady=20, expand=True, fill="both")

        # Khung bên phải
        self.right_frame = ctk.CTkFrame(self.root)
        self.right_frame.pack(side="right", padx=20, pady=20, fill="y")

        # Lưới 4x3
        self.grid_cells = []
        for i in range(ROWS):
            row = []
            for j in range(COLS):
                cell_frame = ctk.CTkFrame(self.left_frame, width=120, height=120, border_width=2)
                cell_frame.grid(row=i, column=j, padx=8, pady=8)
                cell_frame.grid_propagate(False)
                cell_frame.bind("<Button-1>", lambda e, pos=(i, j): self.cell_clicked(pos))
                row.append({"frame": cell_frame, "content": None, "overlays": [], "selected": False})
            self.grid_cells.append(row)

        # Các khối 1..3
        self.blocks = []
        for i in range(3):
            num = i + 1
            block = ctk.CTkLabel(
                self.right_frame,
                text=str(num),
                width=90,
                height=90,
                fg_color="gray75",
                corner_radius=12,
                font=("Arial", 28)
            )
            block.pack(pady=12)
            block.bind("<Button-1>", lambda e, n=num: self.select_block(n))
            self.blocks.append(block)

        # Nút Reset
        self.reset_btn = ctk.CTkButton(
            self.right_frame, text="Reset", width=110, height=40,
            fg_color="#d9534f", hover_color="#c9302c",
            command=self.reset_grid
        )
        self.reset_btn.pack(pady=(12, 6))

        # Nút Xóa
        self.delete_btn = ctk.CTkButton(
            self.right_frame, text="Xóa", width=110, height=40,
            fg_color="#f0ad4e", hover_color="#ec971f",
            command=self.activate_delete_mode
        )
        self.delete_btn.pack(pady=(6, 6))


        # Nút chọn các ô
        self.select_cells_btn = ctk.CTkButton(
            self.right_frame, text="Chọn các ô", width=110, height=40,
            fg_color="#5bc0de", hover_color="#31b0d5",
            command=self.activate_select_cells
        )
        self.select_cells_btn.pack(pady=(6, 6))

        # Nút tìm tới đích qua các ô đã chọn
        self.find_multi_target_btn = ctk.CTkButton(
            self.right_frame, text="Tìm tới đích", width=110, height=40,
            fg_color="#5cb85c", hover_color="#449d44",
            command=self.find_path_multi_targets
        )
        self.find_multi_target_btn.pack(pady=(6, 6))

        # Label thông báo
        self.info_label = ctk.CTkLabel(
            self.right_frame,
            text="Chọn khối, hoặc chọn các ô.\nKhông được ghi đè ô đã có.",
            width=160, height=80, wraplength=150, justify="left"
        )
        self.info_label.pack(pady=8)

        # Biến trạng thái
        self.selected_block = None
        self.mode = "PLACE"   # PLACE / DELETE / SELECT
        self.selected_targets = []  # các ô chọn thủ công

    def select_block(self, number):
        self.mode = "PLACE"
        self.selected_block = number
        for i, block in enumerate(self.blocks, start=1):
            if i == number:
                block.configure(fg_color="orange", font=("Arial", 32, "bold"))
            else:
                block.configure(fg_color="gray75", font=("Arial", 28))
        self.delete_btn.configure(fg_color="#f0ad4e")
        self.select_cells_btn.configure(fg_color="#5bc0de")
        self.info_label.configure(text=f"Đang chọn khối {number}")

    def activate_delete_mode(self):
        self.mode = "DELETE"
        self.selected_block = None
        self.info_label.configure(text="Chế độ XÓA: Click để xóa khối.")
        self.delete_btn.configure(fg_color="orange")
        self.select_cells_btn.configure(fg_color="#5bc0de")
        for block in self.blocks:
            block.configure(fg_color="gray75", font=("Arial", 28))

    def activate_select_cells(self):
        self.mode = "SELECT"
        self.info_label.configure(text="Chế độ chọn ô: Click vào ô để chọn làm mục tiêu.")
        self.select_cells_btn.configure(fg_color="orange")
        self.delete_btn.configure(fg_color="#f0ad4e")
        for block in self.blocks:
            block.configure(fg_color="gray75", font=("Arial", 28))

    def cell_clicked(self, position):
        r, c = position
        cell = self.grid_cells[r][c]

        if self.mode == "DELETE":
            if cell["content"]:
                cell["content"]["widget"].destroy()
                cell["content"] = None
                self.info_label.configure(text=f"Đã xóa tại ({r},{c})")
            return

        if self.mode == "PLACE":
            if not self.selected_block: return
            if cell["content"]:
                self.info_label.configure(text="Ô đã có khối, không ghi đè.")
                return
            new_label = ctk.CTkLabel(
                cell["frame"], text=str(self.selected_block),
                width=90, height=90, fg_color="#79b8ff",
                corner_radius=12, font=("Arial", 24, "bold")
            )
            new_label.place(relx=0.5, rely=0.5, anchor="center")
            cell["content"] = {"widget": new_label, "number": self.selected_block}
            self.info_label.configure(text=f"Đặt khối {self.selected_block} tại ({r},{c})")
            return

        if self.mode == "SELECT":
            if not cell["selected"]:
                cell["frame"].configure(fg_color="orange")
                cell["selected"] = True
                self.selected_targets.append((r, c))
                self.info_label.configure(text=f"Đã chọn ({r},{c}) làm mục tiêu.")
            else:
                cell["frame"].configure(fg_color="transparent")  # đặt về màu mặc định
                cell["selected"] = False
                self.selected_targets.remove((r, c))
                self.info_label.configure(text=f"Bỏ chọn ({r},{c}).")

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
                cell["frame"].configure(fg_color="transparent")  # đặt về màu mặc định
        self.selected_block = None
        self.mode = "PLACE"
        self.selected_targets.clear()
        for block in self.blocks:
            block.configure(fg_color="gray75", font=("Arial", 28))
        self.delete_btn.configure(fg_color="#f0ad4e")
        self.select_cells_btn.configure(fg_color="#5bc0de")
        self.info_label.configure(text="Lưới đã reset.")

    # --- các hàm tìm đường ---
    def neighbors(self, pos, direction):
        r, c = pos
        # thứ tự: đi thẳng trước, rồi trái/phải, cuối cùng đi ngược
        dirs = [(-1,0),(0,-1),(0,1),(1,0)]  # lên, trái, phải, xuống
        for ndir, (dr, dc) in enumerate(dirs):
            nr, nc = r+dr, c+dc
            if 0 <= nr < ROWS and 0 <= nc < COLS:
                # nếu ndir == direction => đi thẳng, ưu tiên cao hơn (priority thấp hơn)
                priority = 0 if ndir == direction else 1
                yield (nr, nc, ndir, priority)


    def h_score(self, current, target):
        """Hàm heuristic: Khoảng cách Manhattan từ điểm hiện tại đến đích"""
        return abs(current[0] - target[0]) + abs(current[1] - target[1])

    def min_h_score(self, pos, targets):
        """Tính khoảng cách Manhattan nhỏ nhất đến bất kỳ target nào"""
        return min(self.h_score(pos, target) for target in targets)

    def cost(self, r, c):
        """Chi phí di chuyển qua ô (r,c)
        Ô trống hoặc ô được chọn: cost = 1
        Ô bị chặn: cost = 2
        """
        cell = self.grid_cells[r][c]
        if cell["content"] is None or cell["selected"]:
            return 1
        return 2

    def dijkstra_astar(self, starts, targets):
        target_set = set(targets)
        g_score = [[float("inf")]*COLS for _ in range(ROWS)]
        parent = [[None]*COLS for _ in range(ROWS)]

        pq = []

        for start in starts:
            r, c = start
            g_score[r][c] = 0
            heapq.heappush(pq, (0, 0, -1, start))  # (f_score, g_score, direction, pos)

        found = None

        while pq:
            f, g, direction, cur = heapq.heappop(pq)
            r, c = cur

            if g > g_score[r][c]:
                continue

            if cur in target_set:
                found = cur
                break

            for nr, nc, ndir, priority in self.neighbors(cur, direction):
                move_cost = self.cost(nr, nc)
                tentative_g = g + move_cost

                if tentative_g < g_score[nr][nc]:
                    parent[nr][nc] = cur
                    g_score[nr][nc] = tentative_g
                    h = self.min_h_score((nr, nc), targets)
                    heapq.heappush(pq, (tentative_g + h + priority, tentative_g, ndir, (nr, nc)))

        if not found:
            return None

        path = []
        p = found
        while p is not None:
            path.append(p)
            p = parent[p[0]][p[1]]
        path.reverse()
        return path

    
    def find_path_multi_targets(self):
        """Tìm đường qua tất cả ô đã chọn rồi lên hàng 0"""
        if not self.selected_targets:
            self.info_label.configure(text="Chưa chọn ô nào.")
            return
        # Xóa overlay cũ
        for r in range(ROWS):
            for c in range(COLS):
                for ov in self.grid_cells[r][c]["overlays"]:
                    ov.destroy()
                self.grid_cells[r][c]["overlays"].clear()

        starts = [(ROWS-1,c) for c in range(COLS)]
        targets = list(self.selected_targets)
        full_path = []
        cur_starts = starts
        empty_cells = 0
        blocked_cells = 0
        
        # đi lần lượt qua từng target
        while targets:
            path = self.dijkstra_astar(cur_starts, targets)
            if not path:
                self.info_label.configure(text="Không tìm được đường đi qua tất cả mục tiêu.")
                return
            
            # Đếm số ô trống và ô bị chặn trong đoạn đường này
            for r, c in path:
                if self.cost(r, c) == 1:
                    empty_cells += 1
                else:
                    blocked_cells += 1
                    
            if not full_path:
                full_path.extend(path)
            else:
                full_path.extend(path[1:])
            last = path[-1]
            cur_starts = [last]
            targets.remove(last)

        # cuối cùng: đi lên hàng 0
        final_targets = [(0,c) for c in range(COLS)]
        path = self.dijkstra_astar(cur_starts, final_targets)
        if not path:
            self.info_label.configure(text="Không tìm được đường lên đích.")
            return
        
        # Đếm số ô trống và bị chặn trong đoạn đường cuối
        for r, c in path[1:]:
            if self.cost(r, c) == 1:
                empty_cells += 1
            else:
                blocked_cells += 1
                
        full_path.extend(path[1:])

        # Vẽ overlay
        for idx,(r,c) in enumerate(full_path):
            lbl = ctk.CTkLabel(self.grid_cells[r][c]["frame"], text=str(idx),
                               width=28,height=28,
                               fg_color="#7be495" if idx not in (0,len(full_path)-1) else "#ffcc66",
                               corner_radius=8,font=("Arial",12,"bold"))
            lbl.place(relx=0.12,rely=0.12,anchor="center")
            self.grid_cells[r][c]["overlays"].append(lbl)
        self.info_label.configure(text=f"Tìm đường qua {len(self.selected_targets)} ô tới hàng 0.\n" + 
                                        f"Tổng {len(full_path)-1} bước ({empty_cells} ô trống, {blocked_cells} ô bị chặn).")

    def run(self):
        self.root.mainloop()


if __name__ == "__main__":
    app = SelectPlaceApp()
    app.run()
