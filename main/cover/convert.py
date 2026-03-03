from ultralytics import YOLO

# Load a model
model = YOLO(r"cover\models\kfs_2.onnx")  # load an official model
# # Export the model
# model.export(format="onnx", simplify = True, half = True, opset=21)
results = model.predict(r"cover\do3.mp4",  show=True, conf=0.4, imgsz= 640)  