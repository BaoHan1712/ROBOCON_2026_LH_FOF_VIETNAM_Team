import serial

ser = serial.Serial(
    port="COM3",
    baudrate=115200,
    timeout=1
)

print("Listening...")

while True:

    if ser.in_waiting >= 2:      # đợi đủ 2 byte
        data = ser.read(2)       # đọc 2 byte

        byte1 = data[0]
        byte2 = data[1]

        print("Byte1:", byte1, "Byte2:", byte2)