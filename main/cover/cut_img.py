import cv2
import os
import time

# Thư mục để lưu , tạo nếu k có
if not os.path.exists('data_train'):
    os.makedirs('data_train')

video_path = r'video_20260303_111850.avi'


cap = cv2.VideoCapture(video_path)

if not cap.isOpened():
    exit()

frame_rate = cap.get(cv2.CAP_PROP_FPS) 
interval = int(frame_rate) 

count = 0  
start_time = time.time()  

while True:
    ret, frame = cap.read()
    if not ret:
        break  

    elapsed_time = time.time() - start_time  

    if elapsed_time >= 0.08: 
         
    # Thư mục sẽ lưu
        file_name = f"data_train/x4{count}.jpg"
        
        cv2.imwrite(file_name, frame)
        print(f"Đã lưu {file_name}")
        
        count += 1 
        start_time = time.time()  

    cv2.imshow('Video', frame)
    

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()