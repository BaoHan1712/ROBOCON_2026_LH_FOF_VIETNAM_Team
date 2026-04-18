from ultralytics import YOLO

# Load a pretrained YOLO11n model
model = YOLO(r"cover/models/gaphop.onnx")

print(model.names) 