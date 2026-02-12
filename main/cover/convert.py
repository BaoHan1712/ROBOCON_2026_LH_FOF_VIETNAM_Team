from ultralytics import YOLO

# Load a model
model = YOLO(r"cover\models\kfs.onnx")  # load an official model
# # Export the model
# model.export(format="onnx", simplify = True, half = True, opset=21)
results = model.predict(r"cover\x4.mp4",  show=True, conf=0.75, imgsz= 640, save= True)  