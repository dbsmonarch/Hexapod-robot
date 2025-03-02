import time
import matplotlib
matplotlib.use("Agg")
import cv2
from ultralytics import YOLO
from jetcam.csi_camera import CSICamera  # pip3 install traitlets==4.3.3
model = YOLO("./weights/yolov8n-pose.pt")
print(model.names)
video_path = 0

# CSI-0
cap = CSICamera(capture_device=0, width=640, height=480)
out = cv2.VideoWriter('out.mp4', cv2.VideoWriter_fourcc('D', 'I', 'V', 'X'), 25, (640, 480))
while True:
    frame = cap.read()

    t1 = time.perf_counter()
    results = model.predict(frame, imgsz=640, stream=False, vid_stride=True)  # stream=True
    result = results[0].plot(conf=True, labels=True, boxes=True, masks=True)
    t2 = time.perf_counter()
    fps = 1 / (t2 - t1)
    cv2.putText(result, f"{fps:.3f} FPS", (15, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
    cv2.imshow("result", result)
    out.write(result)

    if cv2.waitKey(1) & 0xFF == ord("q"):
        break
out.release()
cv2.destroyAllWindows()
