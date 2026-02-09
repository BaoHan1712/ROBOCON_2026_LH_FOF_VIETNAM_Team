import cv2
import numpy as np

# ================== CONFIG ==================
ROWS = 3
COLS = 3
OUT_SIZE = 640   # resize về 640x640

dragging_point = -1
points = []

# ================== MOUSE CALLBACK ==================
def mouse_callback(event, x, y, flags, param):
    global dragging_point, points

    if event == cv2.EVENT_LBUTTONDOWN:
        for i, p in enumerate(points):
            if abs(x - p[0]) < 10 and abs(y - p[1]) < 10:
                dragging_point = i
                break

    elif event == cv2.EVENT_MOUSEMOVE:
        if dragging_point != -1:
            points[dragging_point] = [x, y]

    elif event == cv2.EVENT_LBUTTONUP:
        dragging_point = -1


# ================== MAIN ==================
def process_grid(image_path):
    global points

    img = cv2.imread(image_path)
    img = cv2.resize(img, (640, 640))
    if img is None:
        print("Không tìm thấy ảnh!")
        return

    h, w = img.shape[:2]

    # ---- KHỞI TẠO 4 GÓC BAN ĐẦU (bạn kéo lại sau) ----
    points = [
        [int(w * 0.3), int(h * 0.3)],  # TL
        [int(w * 0.7), int(h * 0.3)],  # TR
        [int(w * 0.7), int(h * 0.7)],  # BR
        [int(w * 0.3), int(h * 0.7)]   # BL
    ]

    cv2.namedWindow("Adjust Corners")
    cv2.setMouseCallback("Adjust Corners", mouse_callback)

    while True:
        display = img.copy()

        # vẽ polygon
        for i in range(4):
            cv2.circle(display, tuple(points[i]), 6, (0, 0, 255), -1)
            cv2.line(display, tuple(points[i]), tuple(points[(i+1)%4]), (0,255,0), 2)

        cv2.putText(display, "Keo 4 diem do, nhan SPACE de warp",
                    (20, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (255,255,0), 2)

        cv2.imshow("Adjust Corners", display)
        key = cv2.waitKey(1)

        if key == 32:  # SPACE
            print("\n===== TOA DO 4 DIEM DA CHON (theo thu tu TL, TR, BR, BL) =====")
            for i, p in enumerate(points):
                print(f"Point {i}: x={p[0]}, y={p[1]}")
            # format sẵn cho copy dán vào code
            print("\nDang numpy array:")
            print("src_points = np.float32([")
            for p in points:
                print(f" [{p[0]}, {p[1]}],")
                print("])\n")
            break
        elif key == 27:  # ESC
            cv2.destroyAllWindows()
            return

    cv2.destroyWindow("Adjust Corners")

    # ================== PERSPECTIVE WARP ==================
    src = np.float32(points)
    dst = np.float32([
        [0, 0],
        [OUT_SIZE, 0],
        [OUT_SIZE, OUT_SIZE],
        [0, OUT_SIZE]
    ])

    matrix = cv2.getPerspectiveTransform(src, dst)
    warped = cv2.warpPerspective(img, matrix, (OUT_SIZE, OUT_SIZE))

    # ================== GRID 3x3 ==================
    cell_h = OUT_SIZE // ROWS
    cell_w = OUT_SIZE // COLS

    for r in range(ROWS):
        for c in range(COLS):
            x1 = c * cell_w
            y1 = r * cell_h
            x2 = x1 + cell_w
            y2 = y1 + cell_h

            cv2.rectangle(warped, (x1, y1), (x2, y2), (0,255,0), 2)
            cv2.putText(warped, f"{r},{c}", (x1+10, y1+30),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0,0,255), 2)
            print("Cell:", r, c, "Coords:", x1, y1, x2, y2)

    cv2.imshow("Warped + Grid 3x3 (640x640)", warped)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


# ================== RUN ==================
if __name__ == "__main__":
    process_grid(r"matrix\real.jpg")