import cv2
import numpy as np

# ================== CONFIG ==================
IMAGE_PATH = r"matrix\real.jpg"
ROWS = 3
COLS = 3
MIN_OBJECT_AREA = 1550        # dien tich toi thieu để nhận diện
SQUARE_RATIO_TOL = 0.5       # do lech ti le vuong

# Thu tu: TL, TR, BR, BL
PTS = np.float32([
    [139, 112],
    [449, 123],
    [449, 518],
    [142, 521]
])

# ================== HELPER ==================
def lerp(p1, p2, t):
    return (1 - t) * p1 + t * p2

def get_cell_polygon(TL, TR, BR, BL, r, c, rows, cols):
    t1 = r / rows
    t2 = (r + 1) / rows
    s1 = c / cols
    s2 = (c + 1) / cols

    left_top = lerp(TL, BL, t1)
    left_bottom = lerp(TL, BL, t2)
    right_top = lerp(TR, BR, t1)
    right_bottom = lerp(TR, BR, t2)

    p1 = lerp(left_top, right_top, s1)
    p2 = lerp(left_top, right_top, s2)
    p3 = lerp(left_bottom, right_bottom, s2)
    p4 = lerp(left_bottom, right_bottom, s1)

    return np.array([p1, p2, p3, p4], dtype=np.int32)

# ================== TRACKBAR ==================
def nothing(x):
    pass

def create_trackbars():
    cv2.namedWindow("Trackbars", cv2.WINDOW_NORMAL)

    # ===== BLUE =====
    cv2.createTrackbar("B_H_min", "Trackbars", 90, 180, nothing)
    cv2.createTrackbar("B_H_max", "Trackbars", 130, 180, nothing)
    cv2.createTrackbar("B_S_min", "Trackbars", 80, 255, nothing)
    cv2.createTrackbar("B_S_max", "Trackbars", 255, 255, nothing)
    cv2.createTrackbar("B_V_min", "Trackbars", 50, 255, nothing)
    cv2.createTrackbar("B_V_max", "Trackbars", 255, 255, nothing)

    # ===== RED =====
    cv2.createTrackbar("R_H_min", "Trackbars", 0, 180, nothing)
    cv2.createTrackbar("R_H_max", "Trackbars", 10, 180, nothing)
    cv2.createTrackbar("R_S_min", "Trackbars", 80, 255, nothing)
    cv2.createTrackbar("R_S_max", "Trackbars", 255, 255, nothing)
    cv2.createTrackbar("R_V_min", "Trackbars", 50, 255, nothing)
    cv2.createTrackbar("R_V_max", "Trackbars", 255, 255, nothing)

# ================== SHAPE PROCESS ==================
def denoise_mask(mask):
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))
    mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel, iterations=1)
    mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel, iterations=2)
    return mask

def is_square_contour(cnt):
    area = cv2.contourArea(cnt)
    if area < MIN_OBJECT_AREA:
        return False

    peri = cv2.arcLength(cnt, True)
    approx = cv2.approxPolyDP(cnt, 0.04 * peri, True)

    if len(approx) != 4:
        return False

    x, y, w, h = cv2.boundingRect(approx)
    ratio = w / float(h)

    return abs(ratio - 1.0) < SQUARE_RATIO_TOL

def detect_square_in_cell(hsv, cell_mask, blue_mask, red_mask, debug_img=None):
    color_mask = cv2.bitwise_or(blue_mask, red_mask)
    color_mask = cv2.bitwise_and(color_mask, color_mask, mask=cell_mask)
    color_mask = denoise_mask(color_mask)

    contours, _ = cv2.findContours(
        color_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE
    )

    cell_area = cv2.countNonZero(cell_mask)
    MIN_CELL_RATIO = 0.12   # vật phải chiếm ít nhất 12% cell

    for cnt in contours:
        area = cv2.contourArea(cnt)

        # 1. Diện tích tuyệt đối
        if area < MIN_OBJECT_AREA:
            continue

        # 2. Diện tích tương đối so với cell
        if area < cell_area * MIN_CELL_RATIO:
            continue

        peri = cv2.arcLength(cnt, True)
        approx = cv2.approxPolyDP(cnt, 0.04 * peri, True)

        if len(approx) != 4:
            continue

        x, y, w, h = cv2.boundingRect(approx)
        ratio = w / float(h)

        if abs(ratio - 1.0) > SQUARE_RATIO_TOL:
            continue

        # ===== DEBUG DRAW =====
        if debug_img is not None:
            cv2.drawContours(debug_img, [approx], -1, (255, 0, 0), 2)
            cv2.putText(
                debug_img,
                f"{int(area)}px",
                (x, y - 5),
                cv2.FONT_HERSHEY_SIMPLEX,
                0.5,
                (255, 0, 0),
                2
            )

        return True   

    return False

# ================== MAIN ==================
def main():
    img = cv2.imread(IMAGE_PATH)
    if img is None:
        print("Khong tim thay anh")
        return

    img = cv2.resize(img, (640, 640))
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

    TL, TR, BR, BL = PTS

    create_trackbars()

    while True:
        draw = img.copy()

        # ===== GET TRACKBAR =====
        bh_min = cv2.getTrackbarPos("B_H_min", "Trackbars")
        bh_max = cv2.getTrackbarPos("B_H_max", "Trackbars")
        bs_min = cv2.getTrackbarPos("B_S_min", "Trackbars")
        bs_max = cv2.getTrackbarPos("B_S_max", "Trackbars")
        bv_min = cv2.getTrackbarPos("B_V_min", "Trackbars")
        bv_max = cv2.getTrackbarPos("B_V_max", "Trackbars")

        rh_min = cv2.getTrackbarPos("R_H_min", "Trackbars")
        rh_max = cv2.getTrackbarPos("R_H_max", "Trackbars")
        rs_min = cv2.getTrackbarPos("R_S_min", "Trackbars")
        rs_max = cv2.getTrackbarPos("R_S_max", "Trackbars")
        rv_min = cv2.getTrackbarPos("R_V_min", "Trackbars")
        rv_max = cv2.getTrackbarPos("R_V_max", "Trackbars")

        # ===== MASK COLOR =====
        blue_mask = cv2.inRange(
            hsv,
            np.array([bh_min, bs_min, bv_min]),
            np.array([bh_max, bs_max, bv_max])
        )

        red_mask1 = cv2.inRange(
            hsv,
            np.array([rh_min, rs_min, rv_min]),
            np.array([rh_max, rs_max, rv_max])
        )
        red_mask2 = cv2.inRange(
            hsv,
            np.array([170, rs_min, rv_min]),
            np.array([180, rs_max, rv_max])
        )

        red_mask = cv2.bitwise_or(red_mask1, red_mask2)

        # ===== GRID + SHAPE CHECK =====
        for r in range(ROWS):
            for c in range(COLS):
                cell_poly = get_cell_polygon(TL, TR, BR, BL, r, c, ROWS, COLS)

                cell_mask = np.zeros(img.shape[:2], dtype=np.uint8)
                cv2.fillPoly(cell_mask, [cell_poly], 255)

                has_square = detect_square_in_cell( hsv, cell_mask, blue_mask, red_mask, debug_img=draw
)

                color = (0, 0, 255) if has_square else (0, 255, 0)
                cv2.polylines(draw, [cell_poly], True, color, 2)

        # ===== SHOW =====
        cv2.imshow("Image + Grid", draw)
        cv2.imshow("Blue Mask", blue_mask)
        cv2.imshow("Red Mask", red_mask)

        key = cv2.waitKey(30)

        if key == 32:  # SPACE
            print("===== BLUE HSV =====")
            print(f"lower_blue = np.array([{bh_min}, {bs_min}, {bv_min}])")
            print(f"upper_blue = np.array([{bh_max}, {bs_max}, {bv_max}])")
            print("===== RED HSV =====")
            print(f"lower_red1 = np.array([{rh_min}, {rs_min}, {rv_min}])")
            print(f"upper_red1 = np.array([{rh_max}, {rs_max}, {rv_max}])")
            print("----------------------------------")

        if key == 27:
            break

    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()