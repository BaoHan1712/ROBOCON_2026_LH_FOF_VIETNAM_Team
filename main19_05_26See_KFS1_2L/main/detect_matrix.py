import customtkinter as ctk
import threading
from config_uart.sent_uart import build_packet, send_packet_once, ser

ctk.set_appearance_mode("light")
ctk.set_default_color_theme("blue")


class ControlApp(ctk.CTk):
    def __init__(self):
        super().__init__()

        self.title("Manual Control Panel")
        self.geometry("450x400")
        self.configure(fg_color="#f5f7fb")

        self.selected = {i: False for i in range(1, 7)}
        self.buttons = {}

        # ================= TITLE =================
        ctk.CTkLabel(
            self,
            text="Select Blocks",
            font=("Segoe UI", 22, "bold"),
            text_color="#1e293b"
        ).pack(pady=(20, 5))

        # ================= STATUS =================
        self.status_label = ctk.CTkLabel(
            self,
            text="Ready",
            font=("Segoe UI", 14),
            text_color="#64748b"
        )
        self.status_label.pack(pady=(0, 5))

        # ================= CARD =================
        card = ctk.CTkFrame(self, corner_radius=20, fg_color="#ffffff")
        card.pack(padx=20, pady=5, fill="both", expand=True)

        btn_frame = ctk.CTkFrame(card, fg_color="transparent")
        btn_frame.pack(expand=True, pady=15)

        btn_style = {
            "width": 80,
            "height": 80,
            "corner_radius": 16,
            "font": ("Segoe UI", 22, "bold"),
            "text_color": "white"
        }

        for i in range(1, 7):
            row = 1 if i <= 3 else 0   
            col = (i - 1) % 3

            btn = ctk.CTkButton(
                btn_frame,
                text=str(i),
                fg_color="#4f46e5",
                hover_color="#6366f1",
                command=lambda n=i: self.toggle(n),
                **btn_style
            )
            btn.grid(row=row, column=col, padx=12, pady=8)
            self.buttons[i] = btn

        # ================= BOTTOM BUTTONS =================
        bottom_frame = ctk.CTkFrame(self, fg_color="transparent")
        bottom_frame.pack(pady=(5, 15))

        ctk.CTkButton(
            bottom_frame,
            text="✔ Confirm",
            width=180,
            height=45,
            corner_radius=14,
            font=("Segoe UI", 16, "bold"),
            fg_color="#16a34a",
            hover_color="#15803d",
            command=self.on_confirm
        ).grid(row=0, column=0, padx=10)

        ctk.CTkButton(
            bottom_frame,
            text="↺ Reset",
            width=120,
            height=45,
            corner_radius=14,
            font=("Segoe UI", 16, "bold"),
            fg_color="#dc2626",
            hover_color="#b91c1c",
            command=self.on_reset
        ).grid(row=0, column=1, padx=10)

    # ================= TOGGLE =================
    def toggle(self, n):
        self.selected[n] = not self.selected[n]

        if self.selected[n]:
            self.buttons[n].configure(fg_color="#f59e0b", hover_color="#d97706")
        else:
            self.buttons[n].configure(fg_color="#4f46e5", hover_color="#6366f1")

    # ================= RESET =================
    def on_reset(self):
        for i in range(1, 7):
            self.selected[i] = False
            self.buttons[i].configure(fg_color="#4f46e5", hover_color="#6366f1")
        self.status_label.configure(text="Reset", text_color="#64748b")

    # ================= CONFIRM =================
    def on_confirm(self):
        col_map = {1: 1, 2: 2, 3: 3, 4: 1, 5: 2, 6: 3}
        entry = [0, 0, 0]

        for n in range(1, 7):
            if self.selected[n]:
                idx = col_map[n] - 1
                entry[idx] = n

        threading.Thread(
            target=self.send_uart,
            args=(entry[0], entry[1], entry[2]),
            daemon=True
        ).start()

    # ================= SEND =================
    def send_uart(self, e1, e2, e3):
        try:
            # --- XÀ BENG CẠY CỬA UART ---
            if ser is not None:
                if not ser.is_open:
                    try: ser.open()
                    except: pass
                if ser.is_open:
                    ser.reset_input_buffer()
                    ser.reset_output_buffer()
            # ----------------------------

            packet = build_packet(2, 3, e1, e2, e3)
            send_packet_once(ser, packet)

            self.status_label.configure(
                text=f"Sent: {e1}  {e2}  {e3}",
                text_color="#16a34a"
            )
            print(f"[MANUAL] Sent: 2, 3, {e1}, {e2}, {e3}")

        except Exception as e:
            self.status_label.configure(text="UART Error: Cổng bị kẹt cứng", text_color="#dc2626")
            print("UART Error:", e)

# if __name__ == "__main__":
#     app = ControlApp()
#     app.mainloop()