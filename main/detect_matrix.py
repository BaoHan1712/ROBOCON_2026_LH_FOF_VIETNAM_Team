import customtkinter as ctk
import threading
from config_uart.sent_uart import build_packet, send_packet_once, ser

# ================= UI CONFIG (2025 STYLE) =================
ctk.set_appearance_mode("light")   # 🌞 sáng
ctk.set_default_color_theme("blue")


class ControlApp(ctk.CTk):
    def __init__(self):
        super().__init__()

        self.title("Manual Control Panel")
        self.geometry("420x250")
        self.configure(fg_color="#f5f7fb")  # nền sáng nhẹ

        # ================= TITLE =================
        self.title_label = ctk.CTkLabel(
            self,
            text="Select Position",
            font=("Segoe UI", 22, "bold"),
            text_color="#1e293b"
        )
        self.title_label.pack(pady=(25, 10))

        # ================= STATUS =================
        self.status_label = ctk.CTkLabel(
            self,
            text="Ready",
            font=("Segoe UI", 14),
            text_color="#64748b"
        )
        self.status_label.pack(pady=(0, 1))

        # ================= CARD FRAME =================
        self.card = ctk.CTkFrame(
            self,
            corner_radius=20,
            fg_color="#ffffff"
        )
        self.card.pack(padx=20, pady=10, fill="both", expand=True)

        # ================= BUTTON FRAME =================
        self.button_frame = ctk.CTkFrame(
            self.card,
            fg_color="transparent"
        )
        self.button_frame.pack(expand=True)

        # ================= BUTTON STYLE =================
        btn_style = {
            "width": 90,
            "height": 90,
            "corner_radius": 20,
            "font": ("Segoe UI", 20, "bold"),
            "fg_color": "#4f46e5",
            "hover_color": "#6366f1",
            "text_color": "white"
        }

        # ================= BUTTONS =================
        self.btn1 = ctk.CTkButton(
            self.button_frame,
            text="1",
            command=lambda: self.on_click(1),
            **btn_style
        )
        self.btn1.grid(row=0, column=0, padx=15, pady=25)

        self.btn2 = ctk.CTkButton(
            self.button_frame,
            text="2",
            command=lambda: self.on_click(2),
            **btn_style
        )
        self.btn2.grid(row=0, column=1, padx=15, pady=25)

        self.btn3 = ctk.CTkButton(
            self.button_frame,
            text="3",
            command=lambda: self.on_click(3),
            **btn_style
        )
        self.btn3.grid(row=0, column=2, padx=15, pady=25)

    # ================= ACTION =================
    def on_click(self, entry_id):
        threading.Thread(target=self.send_uart, args=(entry_id,), daemon=True).start()

    def send_uart(self, entry_id):
        try:
            packet = build_packet(2, 3, 3, 3, entry_id)
            send_packet_once(ser, packet)

            self.status_label.configure(
                text=f"Sent: {entry_id}",
                text_color="#16a34a"
            )

            print(f"[MANUAL] Sent: 2, 3, 3, 3, {entry_id}")

        except Exception as e:
            self.status_label.configure(
                text="UART Error",
                text_color="#dc2626"
            )
            print("UART Error:", e)


# # ================= RUN =================
if __name__ == "__main__":
    app = ControlApp()
    app.mainloop()