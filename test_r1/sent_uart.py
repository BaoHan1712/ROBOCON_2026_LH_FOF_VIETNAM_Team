import struct
import time
import serial
import random

# --- Hàm đóng gói ---
def build_packet(id_rb, move, action, block_id):
    start = 0x02
    end   = 0x03

    checksum = (id_rb + move + action + block_id) & 0xFF

    packet = struct.pack(
        '7B',
        start,
        id_rb,
        move,
        action,
        block_id,
        checksum,
        end
    )
    return packet

# --- Mở UART ---
ser = serial.Serial(
    port='COM3',       # đổi theo máy bạn
    baudrate=115200
)

print("UART opened")

# # --- Gửi liên tục ---
while True:
    id_rb = random.randint(1, 100)
    move     = random.randint(1, 100)
    action   = random.randint(1, 100)
    block_id = random.randint(1, 100)

    packet = build_packet(id_rb, move, action, block_id)

    ser.write(packet)
    print(f"Đã gửi → id_robot ={id_rb} ,move={move}, action={action}, id={block_id}, packet={packet}")

    time.sleep(0.1)
