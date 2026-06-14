import numpy as np
import matplotlib.pyplot as plt

# --- HÀM 1: Mô phỏng chính xác theo logic Code C của bạn (Min bị chặn ở 80) ---
def tinh_toc_do_goc(current_error, hs_tracking=20, max_toc=250, k=1.0):
    if current_error <= hs_tracking:
        return 80
    
    error = current_error - hs_tracking
    if error > 100: 
        error = 100

    # Phương trình phi tuyến bậc 2
    speed_out = 20 + int(k * ((max_toc - 20) * error * error) / 10000)

    # Bộ kẹp giới hạn (Saturate)
    if speed_out > max_toc: speed_out = max_toc
    if speed_out < 80:     speed_out = 80
    return speed_out

# --- HÀM 2: Đề xuất hiệu chỉnh tối ưu (Đạt Min 70 và mượt mà không có vùng chết) ---
def tinh_toc_do_toi_uu(current_error, hs_tracking=20, max_toc=250, min_toc=70, k=1.0):
    if current_error <= hs_tracking:
        return min_toc
    
    error = current_error - hs_tracking
    if error > 100: 
        error = 100

    # Sử dụng min_toc làm điểm khởi đầu (Offset) thay vì cố định số 20
    speed_out = min_toc + int(k * ((max_toc - min_toc) * error * error) / 10000)

    if speed_out > max_toc: speed_out = max_toc
    if speed_out < min_toc: speed_out = min_toc
    return speed_out

# Vector hóa hàm để áp dụng mượt mà trên mảng dữ liệu Numpy
tinh_toc_do_goc_vec = np.vectorize(tinh_toc_do_goc)
tinh_toc_do_toi_uu_vec = np.vectorize(tinh_toc_do_toi_uu)

# Giả lập dải giá trị của Biến trở (current_error) từ 0 đến 150
# (Đủ để đi qua vùng hs_tracking, vùng tăng trưởng phi tuyến và vùng bão hòa)
gia_tri_bien_tro = np.linspace(0, 150, 1000)

# Cấu hình tham số mô phỏng
HS_TRACKING = 20
MAX_TOC = 250

# Tính toán các đáp ứng đầu ra
y_goc = tinh_toc_do_goc_vec(gia_tri_bien_tro, hs_tracking=HS_TRACKING, max_toc=MAX_TOC, k=1.0)
y_toi_uu = tinh_toc_do_toi_uu_vec(gia_tri_bien_tro, hs_tracking=HS_TRACKING, max_toc=MAX_TOC, min_toc=70, k=1.0)
y_goc_k07 = tinh_toc_do_goc_vec(gia_tri_bien_tro, hs_tracking=HS_TRACKING, max_toc=MAX_TOC, k=0.7)

# --- Khởi tạo đồ thị ---
fig, ax = plt.subplots(figsize=(10, 6))

# Vẽ các đường đặc tuyến
ax.plot(gia_tri_bien_tro, y_goc, label='Code C hien tai (k=1.0, Min vinh cuu o 80)', color='crimson', linewidth=2.5)
ax.plot(gia_tri_bien_tro, y_goc_k07, label='Code C hien tai (k=0.7, Do nhay thap)', color='orange', linestyle='-.', linewidth=2)
ax.plot(gia_tri_bien_tro, y_toi_uu, label='De xuat toi uu (Min=70, Dap ung muot)', color='dodgerblue', linewidth=2.5, linestyle='--')

# Đánh dấu các mốc giới hạn vật lý bằng đường dotted
ax.axhline(MAX_TOC, color='red', linestyle=':', alpha=0.7, label=f'Max Speed ({MAX_TOC})')
ax.axhline(80, color='purple', linestyle=':', alpha=0.5, label='Min trong code gốc (80)')
ax.axhline(70, color='darkgreen', linestyle=':', alpha=0.5, label='Min mong muon (70)')
ax.axvline(HS_TRACKING, color='gray', linestyle=':', alpha=0.7)

# Thêm chú thích văn bản trực quan trên đồ thị
ax.text(HS_TRACKING + 2, 100, f'hs_tracking = {HS_TRACKING}', rotation=90, color='gray', fontsize=10)
ax.text(HS_TRACKING + 102, 100, 'Bao hoa Error = 100', rotation=90, color='gray', fontsize=10)

# Minh họa Vùng Chết (Dead-zone) của code cũ bằng mũi tên trỏ vào đồ thị
ax.annotate('Vung chet vo y\n(Gia tri tinh < 80 nen bi san phang)', 
            xy=(45, 80), xytext=(35, 130),
            arrowprops=dict(facecolor='black', shrink=0.08, width=1, headwidth=6))

# Định dạng đồ thị tổng thể
ax.set_title('Mo phong Dac tuyen Dieu khien Toc do Dong co theo Biem tro', fontsize=14, fontweight='bold')
ax.set_xlabel('Gia tri Biem tro (current_error)', fontsize=12)
ax.set_ylabel('Toc do Dong co (speed_out)', fontsize=12)
ax.grid(True, linestyle='--', alpha=0.5)
ax.legend(loc='upper left', fontsize=10)

# Hiển thị đồ thị
plt.tight_layout()
plt.show()