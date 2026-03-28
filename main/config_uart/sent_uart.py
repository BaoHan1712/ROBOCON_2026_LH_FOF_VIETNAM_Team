import struct
import time
import serial
import random

ser = serial.Serial(port="COM3", baudrate=115200)

# --- Hàm đóng gói ---
def build_packet(id_rb, state, move, action, block_id):
    start = 0x02
    end = 0x03
    checksum = (start + id_rb + state + move + action + block_id) & 0xFF
    packet = struct.pack('8B', start, id_rb, state, move, action, block_id, checksum, end)
    return packet

def send_packet_once(ser, packet):
    try:
        if not ser or not ser.is_open:
            print("UART port not open.")
            return
        ser.write(packet)
        ser.flush()             
        time.sleep(2)
    except Exception as e:
        print(f"UART send error: {e}")
    # Removed ser.close() to keep port open for shared use


# # # # # # # --- Gửi liên tục ---
# while True:
#     id_rb    = 1 
#     state     = 2
#     move     = random.randint(0, 3)
#     action   = random.randint(1, 2)
#     block_id = 1

#     packet = build_packet(id_rb, state, move, action, block_id)
#     ser.write(packet)

#     print(f"Đã gửi → move={move}, action={action}, id={block_id}, packet={packet}")

#     time.sleep(1)


# # [2, 2, 10, 10, 1], [2, 2, 0, 1, 1], [2, 2, 3, 10, 2], [2, 2, 0, 1, 2]


# packet = build_packet(2, 2, 10, 10, 1)
# ser.write(packet)
# print(f"Đã gửi")
# time.sleep(0.3)


# packet = build_packet(2, 2, 0, 1, 1)
# ser.write(packet)
# print(f"Đã gửi")
# time.sleep(0.3)

# packet = build_packet(2, 2, 3, 10, 2)
# ser.write(packet)
# print(f"Đã gửi")
# time.sleep(0.3)

# packet = build_packet(2, 2, 3, 10, 3)
# ser.write(packet)
# print(f"Đã gửi")
# time.sleep(0.3)

# # # # leo bac
# # packet = build_packet(2, 2, 1, 4, 2)
# # ser.write(packet)
# # print(f"Đã gửi")
# # time.sleep(0.3)

# # packet = build_packet(2, 2, 2, 10, 1)
# # ser.write(packet)
# # print(f"Đã gửi")
# # time.sleep(0.3)

# packet = build_packet(2, 2, 0, 1, 3)
# ser.write(packet)
# print(f"Đã gửi")
# time.sleep(0.3)

