import tkinter as tk
import os

# ===== STATE CONSTANTS =====
STATE_IDLE       = 0
STATE_SEE_R1     = 1
STATE_MATRIX     = 2
STATE_FOREST     = 3
STATE_PICK_BLOCK = 4

set_state = {"value": STATE_IDLE}


# ===== STATE FUNCTIONS =====
def set_see_r1():
    set_state["value"] = STATE_SEE_R1
    print(">> STATE = DETECT R1")

def set_matrix():
    set_state["value"] = STATE_MATRIX
    print(">> STATE = MATRIX DETECT")

def set_forest():
    set_state["value"] = STATE_FOREST
    print(">> STATE = FOREST DETECT")

def set_pick_block():
    set_state["value"] = STATE_PICK_BLOCK
    print(">> STATE = PICK BLOCK")

def set_idle():
    set_state["value"] = STATE_IDLE
    print(">> STATE = IDLE")

# ===== CLOSE =====
def on_close():
    print(">> GUI CLOSED → STOP ALL PROGRAM")
    os._exit(0)

# ===== GUI =====
def start_gui():
    root = tk.Tk()
    root.title("Robot Control Panel")
    root.geometry("420x730")
    root.resizable(False, False)
    root.configure(bg="#2b2b2b")

    root.protocol("WM_DELETE_WINDOW", on_close)

    # ----- TITLE -----
    tk.Label(
        root,
        text="ROBOT CONTROL",
        font=("Arial", 20, "bold"),
        fg="white",
        bg="#2b2b2b"
    ).pack(pady=25)

    btn_cfg = {
        "width": 18,
        "height": 2,
        "font": ("Arial", 14, "bold"),
        "bd": 0
    }

    tk.Button(
        root, text="R1 DETECT",
        command=set_see_r1,
        bg="#c0392b", fg="white",
        **btn_cfg
    ).pack(pady=10)

    tk.Button(
        root, text="MATRIX DETECT",
        command=set_matrix,
        bg="#2980b9", fg="white",
        **btn_cfg
    ).pack(pady=10)

    tk.Button(
        root, text="FOREST DETECT",
        command=set_forest,
        bg="#27ae60", fg="white",
        **btn_cfg
    ).pack(pady=10)

    tk.Button(
        root, text="PICK BLOCK",
        command=set_pick_block,
        bg="#f39c12", fg="white",
        **btn_cfg
    ).pack(pady=10)

    tk.Frame(root, height=2, bg="#555555", width=300).pack(pady=20)

    tk.Button(
        root, text="STOP / IDLE",
        command=set_idle,
        bg="#7f8c8d", fg="white",
        **btn_cfg
    ).pack(pady=10)

    root.mainloop()
