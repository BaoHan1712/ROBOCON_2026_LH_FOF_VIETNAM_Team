import time
import threading
# 🔥 BƯỚC 1: THÊM CÁI STATE_SEE_R1_L2 VÀO DÒNG IMPORT NÀY!
from gui_tkinter import STATE_SEE_R1, set_state, STATE_IDLE, STATE_MATRIX, STATE_FOREST, STATE_SEE_R1_L2

uart_enable = {"value": True}
_listener_thread = None

def uart_state_listener(ser):
    print("\n>> [UART MAIN] 🎧 LUỒNG LẮNG NGHE ĐÃ KHỞI ĐỘNG CHỜ LỆNH TỪ STM32!")

    # 1. BƠM ĐIỆN LẠI CHO UART (Vì thằng Algo vừa tắt đã đóng van)
    if ser is not None and not ser.is_open:
        try:
            ser.open()
            print(">> [UART MAIN] ✓ Đã tự động mở lại van UART thành công!")
        except Exception as e:
            print(f">> [UART MAIN] ❌ Lỗi đéo mở được cổng: {e}")
            return

    while True:
        # ❌ Không nghe khi không cho phép
        if not uart_enable["value"]:
            time.sleep(0.02)
            continue

        # ❌ Chỉ nghe khi IDLE (Trạng thái chờ)
        if set_state["value"] != STATE_IDLE:
            time.sleep(0.02)
            continue

        try:
            # ===== đọc 1 byte =====
            if ser.in_waiting:
                data = ser.read(1)[0]  

                # ===== xử lý =====
                if data == 1:
                    set_state["value"] = STATE_SEE_R1
                    print(">> [UART MAIN] Bắt được lệnh 1 -> Yêu cầu mở Cam R1")
                elif data == 2:
                    set_state["value"] = STATE_MATRIX
                    print(">> [UART MAIN] Bắt được lệnh 2 -> Yêu cầu mở Vùng 3 Matrix")
                elif data == 3:
                    set_state["value"] = STATE_FOREST
                    print(">> [UART MAIN] Bắt được lệnh 3 -> Yêu cầu mở Sa Bàn Rừng Algo")
                
                # 🔥 CHỈ CẮM THÊM ĐÚNG CHỖ NÀY ĐỂ BẮT LỆNH SỐ 5 (CHECK R1 LẦN 2)
                elif data == 5:
                    set_state["value"] = STATE_SEE_R1_L2
                    print(">> [UART MAIN] Bắt được lệnh 5 -> Yêu cầu mở Cam CHECK R1 LẦN 2 (NÉ VẬT CẢN)")

                # =========================================================
                # 🔥 ĐOẠN CẦN BỔ SUNG TRONG UART_LISTENER ĐỂ THÔNG MẠCH VỚI MAIN
                # =========================================================
                # Giả sử biến 'data' là dữ liệu raw byte hoặc mã lệnh đọc được từ STM32
                if data == 6:
                    print(">> [UART LISTENER] Bắt được tín hiệu số 6 từ STM32! Chuyển trạng thái sang SCAN FLOOR BLUE.")
                    set_state["value"] = 6  # 🎯 Gạt công tắc gọi Main dậy!
                
                elif data == 7:
                    print(">> [UART LISTENER] Bắt được tín hiệu số 7 từ STM32! Chuyển trạng thái sang SCAN FLOOR RED.")
                    set_state["value"] = 7  # 🎯 Gạt công tắc gọi Main dậy!    

                else:
                    continue

                print(f">> UART → CHUYỂN TRẠNG THÁI (STATE) THÀNH: {data}")

                # 🔴 khóa UART sau khi nhận để đéo bị trôi lệnh liên tục
                uart_enable["value"] = False
        except Exception as e:
            print(f">> [UART MAIN] Lỗi đọc tín hiệu: {e}")

        time.sleep(0.005)

# =========================================================================
# VŨ KHÍ GỌI LUỒNG: Hàm này dùng để Main.py hoặc Algo gọi một cách an toàn
# =========================================================================
def start_listening_background(ser):
    global _listener_thread
    
    # Chống đẻ nhiều luồng đâm nhau gây crash App
    if _listener_thread is not None and _listener_thread.is_alive():
        print(">> [UART MAIN] Luồng lắng nghe đang chạy sẵn rồi, mở khóa cho nghe tiếp!")
        uart_enable["value"] = True # Chỉ cần nhả khóa là nó nghe lại
        return
        
    # Đẻ luồng ngầm mới tinh
    uart_enable["value"] = True
    _listener_thread = threading.Thread(target=uart_state_listener, args=(ser,), daemon=True)
    _listener_thread.start()