import customtkinter as ctk
import heapq

ctk.set_appearance_mode("System")
ctk.set_default_color_theme("blue")

ROWS = 4
COLS = 3
CELL_SIZE = 160

class SelectPlaceApp:
    def __init__(self):
        self.root = ctk.CTk()
        self.root.title("Chọn khối và đặt vào lưới")
        self.root.geometry("720x720")

        # Khung chính chứa lưới
        self.main_frame = ctk.CTkFrame(self.root)
        self.main_frame.pack(padx=20, pady=20, expand=True, fill="both")

        # Lưới 4x3
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
                        width=45,
                        height=45,
                        fg_color="gray75",
                        corner_radius=8,
                        font=("Arial", 18),
                        command=lambda n=num, pos=(i, j): self.place_block(n, pos)
                    )
                    btn.pack(side="left", expand=True, padx=5, pady=5)
                    block_buttons.append(btn)

                cell_frame.bind("<Button-1>", lambda e, pos=(i, j): self.cell_clicked(pos))

                row.append({
                    "frame": cell_frame,
                    "content": None,
                    "overlays": [],
                    "selected": False,
                    "buttons": block_buttons
                })
            self.grid_cells.append(row)

        # Thanh công cụ bên dưới
        self.bottom_frame = ctk.CTkFrame(self.root)
        self.bottom_frame.pack(side="bottom", padx=20, pady=10, fill="x")

        self.reset_btn = ctk.CTkButton(
            self.bottom_frame, text="Reset", width=110, height=40,
            fg_color="#d9534f", hover_color="#c9302c",
            command=self.reset_grid
        )
        self.reset_btn.pack(side="left", padx=10)

        self.delete_btn = ctk.CTkButton(
            self.bottom_frame, text="Xóa", width=110, height=40,
            fg_color="#f0ad4e", hover_color="#ec971f",
            command=lambda: self.toggle_mode("DELETE", self.delete_btn)
        )
        self.delete_btn.pack(side="left", padx=10)

        self.select_cells_btn = ctk.CTkButton(
            self.bottom_frame, text="Chọn các ô", width=110, height=40,
            fg_color="#5bc0de", hover_color="#31b0d5",
            command=lambda: self.toggle_mode("SELECT", self.select_cells_btn)
        )
        self.select_cells_btn.pack(side="left", padx=10)

        self.find_multi_target_btn = ctk.CTkButton(
            self.bottom_frame, text="Tìm tới đích", width=110, height=40,
            fg_color="#5cb85c", hover_color="#449d44",
            command=self.find_path_multi_targets
        )
        self.find_multi_target_btn.pack(side="left", padx=10)

        self.info_label = ctk.CTkLabel(
            self.root,
            text="Click trực tiếp vào khối 1, 2, 3 trong mỗi ô để đặt.\nHoặc click vào ô để xóa/chọn khi ở chế độ tương ứng.",
            width=160, height=60, wraplength=600, justify="left"
        )
        self.info_label.pack(pady=8)

        self.mode = "PLACE"   # PLACE / DELETE / SELECT
        self.selected_targets = []
        self.active_button = None  # theo dõi nút đang sáng

    def toggle_mode(self, new_mode, button):
        if self.mode == new_mode:
            # tắt chế độ, quay lại PLACE
            self.mode = "PLACE"
            if self.active_button:
                self.active_button.configure(fg_color=self.active_button.default_color)
            self.active_button = None
            self.info_label.configure(text="Trở lại chế độ đặt khối.")
        else:
            # bật chế độ mới
            self.mode = new_mode
            if self.active_button:
                self.active_button.configure(fg_color=self.active_button.default_color)
            self.active_button = button
            button.default_color = button.cget("fg_color")
            button.configure(fg_color="yellow")
            if new_mode == "DELETE":
                self.info_label.configure(text="Chế độ XÓA: Click ô để xóa khối.")
            elif new_mode == "SELECT":
                self.info_label.configure(text="Chế độ CHỌN: Click ô để chọn làm mục tiêu.")

    def cell_clicked(self, position):
        r, c = position
        cell = self.grid_cells[r][c]
        if self.mode == "DELETE":
            if cell["content"]:
                cell["content"]["widget"].destroy()
                cell["content"] = None
                for btn in cell["buttons"]:
                    btn.pack(side="left", expand=True, padx=5, pady=5)
                self.info_label.configure(text=f"Đã xóa tại ({r},{c})")
        elif self.mode == "SELECT":
            if not cell["selected"]:
                cell["frame"].configure(fg_color="orange")
                cell["selected"] = True
                self.selected_targets.append((r, c))
                self.info_label.configure(text=f"Đã chọn ({r},{c}) làm mục tiêu.")
            else:
                cell["frame"].configure(fg_color="transparent")
                cell["selected"] = False
                self.selected_targets.remove((r, c))
                self.info_label.configure(text=f"Bỏ chọn ({r},{c}).")
   
    def place_block(self, number, position):
        r, c = position
        cell = self.grid_cells[r][c]
        if self.mode == "DELETE":
            if cell["content"]:
                cell["content"]["widget"].destroy()
                cell["content"] = None
                for btn in cell["buttons"]:
                    btn.pack(side="left", expand=True, padx=5, pady=5)
                self.info_label.configure(text=f"Đã xóa tại ({r},{c})")
            return
        if self.mode == "PLACE":
            if cell["content"]:
                self.info_label.configure(text="Ô đã có khối, không ghi đè.")
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
            self.info_label.configure(text=f"Đặt khối {number} tại ({r},{c})")
            return
        if self.mode == "SELECT":
            if not cell["selected"]:
                cell["frame"].configure(fg_color="orange")
                cell["selected"] = True
                self.selected_targets.append((r, c))
                self.info_label.configure(text=f"Đã chọn ({r},{c}) làm mục tiêu.")
            else:
                cell["frame"].configure(fg_color="transparent")
                cell["selected"] = False
                self.selected_targets.remove((r, c))
                self.info_label.configure(text=f"Bỏ chọn ({r},{c}).")

    def activate_delete_mode(self):
        self.mode = "DELETE"
        self.info_label.configure(text="Chế độ XÓA: Click nút trong ô để xóa khối.")

    def activate_select_cells(self):
        self.mode = "SELECT"
        self.info_label.configure(text="Chế độ chọn ô: Click vào nút trong ô để chọn làm mục tiêu.")

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
        self.mode = "PLACE"
        self.selected_targets.clear()
        self.info_label.configure(text="Lưới đã reset.")
        if self.active_button:
            self.active_button.configure(fg_color=self.active_button.default_color)
            self.active_button = None

    def neighbors(self, pos, direction):
        r, c = pos
        # thứ tự: đi thẳng trước, rồi trái/phải, cuối cùng đi ngược
        dirs = [(-1,0),(0,-1),(0,1),(1,0)]  # lên, trái, phải, xuống
        for ndir, (dr, dc) in enumerate(dirs):
            nr, nc = r+dr, c+dc
            if 0 <= nr < ROWS and 0 <= nc < COLS:
                # nếu ndir == direction => đi thẳng, ưu tiên cao hơn 
                priority = 0 if ndir == direction else 1
                yield (nr, nc, ndir, priority)

    def h_score(self, current, target):
        return abs(current[0] - target[0]) + abs(current[1] - target[1])

    def min_h_score(self, pos, targets):
        return min(self.h_score(pos, target) for target in targets)

    def cost(self, r, c):
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
        if not self.selected_targets:
            self.info_label.configure(text="Chưa chọn ô nào.")
            return

        for r in range(ROWS):
            for c in range(COLS):
                for ov in self.grid_cells[r][c]["overlays"]:
                    ov.destroy()
                self.grid_cells[r][c]["overlays"].clear()

        starts = [(ROWS-1,c) for c in range(COLS)]
        targets = list(self.selected_targets)
        full_path = []
        cur_starts = starts

        while targets:
            path = self.dijkstra_astar(cur_starts, targets)
            if not path:
                self.info_label.configure(text="Không tìm được đường đi qua tất cả mục tiêu.")
                return

            if not full_path:
                full_path.extend(path)
            else:
                full_path.extend(path[1:])
            last = path[-1]
            cur_starts = [last]
            targets.remove(last)

        final_targets = [(0,c) for c in range(COLS)]
        path = self.dijkstra_astar(cur_starts, final_targets)
        if not path:
            self.info_label.configure(text="Không tìm được đường lên đích.")
            return
        full_path.extend(path[1:])

        for idx,(r,c) in enumerate(full_path):
            lbl = ctk.CTkLabel(self.grid_cells[r][c]["frame"], text=str(idx),
                               width=28,height=28,
                               fg_color="#7be495" if idx not in (0,len(full_path)-1) else "#ffcc66",
                               corner_radius=8,font=("Arial",12,"bold"))
            lbl.place(relx=0.12,rely=0.12,anchor="center")
            self.grid_cells[r][c]["overlays"].append(lbl)
        self.info_label.configure(text=f"Tìm đường qua {len(self.selected_targets)} ô tới hàng 0.\nTổng {len(full_path)-1} bước.")


    def run(self):
        self.root.mainloop()


if __name__ == "__main__":
    app = SelectPlaceApp()
    app.run()
