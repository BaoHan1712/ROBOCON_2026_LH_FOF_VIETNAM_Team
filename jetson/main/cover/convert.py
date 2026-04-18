from ultralytics import YOLO

# Load a model
model = YOLO(r"cover/models/nhathop.pt")  # load an official model
# # Export the model
model.export(format="onnx", half = True)
# results = model.predict(r"cover\do3.mp4",  show=True, conf=0.4, imgsz= 640)  