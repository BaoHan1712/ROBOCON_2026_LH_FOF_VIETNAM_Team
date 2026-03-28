from ultralytics import YOLO

# Load a pretrained YOLO11n model
model = YOLO(r"cover\models\kfs_2.pt")

print(model.names) 