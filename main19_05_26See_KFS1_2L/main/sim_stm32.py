import serial
import time

# 🔥 CẤU HÌNH CỔNG VÀ TỐC ĐỘ (Baudrate mày tự chỉnh cho khớp với hệ thống nhé, thường là 115200)
PORT = '/dev/ttyUSB_MAP'
BAUD = 115200

def main():
    print(f">> [SIMULATOR] Đang khởi động STM32 Ảo trên cổng {PORT}...")
    try:
        # Mở cổng UART
        ser = serial.Serial(PORT, BAUD, timeout=1)
        print(">> [SIMULATOR] ✓ Mở cổng thành công! Đã sẵn sàng nã đạn.")
    except Exception as e:
        print(f">> [LỖI] Đéo mở được cổng {PORT}. (Kẹt cổng hoặc cắm lỏng cáp)\nLý do: {e}")
        return

    while True:
        print("\n" + "="*45)
        print("🎮 BẢNG ĐIỀU KHIỂN STM32 ẢO TỚI JETSON")
        print(" [1] Gửi lệnh 1 -> Ép mở SEE R1 (Lần 1)")
        print(" [5] Gửi lệnh 5 -> Ép mở CHECK R1 L2 (Né cản)")
        print(" [0] Thoát giả lập")
        print("="*45)

        choice = input(">> Nhập lệnh muốn bắn (1 hoặc 5): ").strip()

        if choice == '1':
            # Ép kiểu gửi đúng 1 byte raw (0x01) để file uart_listener.py đọc được số 1
            ser.write(bytes([1])) 
            print(">> 🚀 [BÙM] Đã bắn lệnh: 1 (0x01) vào dây UART!")
            
        elif choice == '5':
            # Ép kiểu gửi đúng 1 byte raw (0x05)
            ser.write(bytes([5])) 
            print(">> 🚀 [BÙM] Đã bắn lệnh: 5 (0x05) vào dây UART!")
            
        elif choice == '0':
            print(">> Tắt giả lập STM32.")
            ser.close()
            # =======================================================
        # 🔥 TEST CASE 6: KỊCH BẢN LỤM QUÀ LẦN 2 (SÂN XANH)
        # =======================================================
        elif choice == '6':
            print("\n>> [STM32] Bắn lệnh 6: KÍCH HOẠT NHẶT QUÀ (SÂN XANH)!")
            
            # Gửi số 6 dạng byte thô (tùy code uart_listener của mày nhận kiểu gì)
            ser.write(bytes([6]))  
            # Nếu code của sếp nhận String thì dùng: ser.write(b'6')
            
            print(">> [STM32] Đang chờ Jetson soi sàn (Dự kiến 1.5s)...")
            print(">> [STM32] Vui lòng đưa hộp màu Xanh vào Camera!")

        # =======================================================
        # 🔥 TEST CASE 7: KỊCH BẢN LỤM QUÀ LẦN 2 (SÂN ĐỎ)
        # =======================================================
        elif choice == '7':
            print("\n>> [STM32] Bắn lệnh 7: KÍCH HOẠT NHẶT QUÀ (SÂN ĐỎ)!")
            
            ser.write(bytes([7]))
            
            print(">> [STM32] Đang chờ Jetson soi sàn (Dự kiến 1.5s)...")
            print(">> [STM32] Vui lòng đưa hộp màu Đỏ vào Camera!")
            break
        else:
            print(">> Đéo có lệnh này, nhập 1 hoặc 5 thôi sếp ơi!")

        time.sleep(0.5)

if __name__ == "__main__":
    main()