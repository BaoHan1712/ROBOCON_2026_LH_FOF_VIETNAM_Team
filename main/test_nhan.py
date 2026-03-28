import serial

ser = serial.Serial(
    port="COM3",   # sửa lại nếu khác
    baudrate=115200,
    timeout=1
)

print("Listening from ESP32...")

while True:
    data = ser.read(1)   # đọc 1 byte

    if data:
        byte = data[0]
        print(f"da nhan Byte: {byte} (0x{byte:02X})")