import tkinter as tk
import os
import sys

STATE_IDLE = 0
STATE_WEAPON = 1
STATE_MATRIX = 2
STATE_FOREST = 3

set_state = {"value": STATE_IDLE}


def set_weapon():
    set_state["value"] = STATE_WEAPON
    print(">> STATE = WEAPON DETECT")


def set_matrix():
    set_state["value"] = STATE_MATRIX
    print(">> STATE = MATRIX DETECT")


def set_idle():
    set_state["value"] = STATE_IDLE
    print(">> STATE = IDLE")


def set_forest():
    set_state["value"] = STATE_FOREST
    print(">> STATE = FOREST DETECT")


def on_close():
    print(">> GUI CLOSED → STOP ALL PROGRAM")
    os._exit(0)  


def start_gui():
    root = tk.Tk()
    root.title("Robot Control Panel")
    root.geometry("300x200")

    root.protocol("WM_DELETE_WINDOW", on_close)  # 🔴 QUAN TRỌNG

    tk.Button(root, text="Weapon Detect", command=set_weapon, width=20).pack(pady=10)
    tk.Button(root, text="Matrix Detect", command=set_matrix, width=20).pack(pady=10)
    tk.Button(root, text="Forest Detect", command=set_forest, width=20).pack(pady=10)
    tk.Button(root, text="Idle", command=set_idle, width=20).pack(pady=10)

    root.mainloop()