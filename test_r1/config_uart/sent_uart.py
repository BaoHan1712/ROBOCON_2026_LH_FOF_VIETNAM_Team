import struct
import time
import serial
import random

# --- Hàm đóng gói ---
def build_packet(id_rb, state, move, action, block_id):
    start = 0x02
    end = 0x03
    checksum = (start + id_rb + state + move + action + block_id) & 0xFF
    packet = struct.pack('8B', start, id_rb, state, move, action, block_id, checksum, end)
    return packet

def send_packet_once(port , baudrate, packet):
    ser = None
    try:
        ser = serial.Serial(
            port=port,
            baudrate=baudrate,
        )
        ser.write(packet)
        ser.flush()             
        time.sleep(0.05)
    finally:
        if ser and ser.is_open:
            ser.close()          # GIẢI PHÓNG PORT


# # # --- Gửi liên tục ---
# while True:
#     move     = random.randint(1, 100)
#     action   = random.randint(1, 100)
#     block_id = random.randint(1, 100)

#     packet = build_packet(move, action, block_id)

#     ser.write(packet)
#     print(f"Đã gửi → move={move}, action={action}, id={block_id}, packet={packet}")

#     time.sleep(0.3)
