import time
import matplotlib
matplotlib.use("Agg")
import cv2
from ultralytics import YOLO

model = YOLO("./weights/yolov8n-pose.pt")
print(model.names)
video_path = "demo.mp4"
output_path = "output_demo.mp4"

cap = cv2.VideoCapture(video_path)

# 获取视频的宽度、高度和帧率
width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
fps = cap.get(cv2.CAP_PROP_FPS)

# 创建VideoWriter对象
fourcc = cv2.VideoWriter_fourcc(*'mp4v')
out = cv2.VideoWriter(output_path, fourcc, fps, (width, height))

while cap.isOpened():
    ret, frame = cap.read()
    if ret:
        t1 = time.perf_counter()
        results = model.predict(frame, imgsz=640, stream=False, vid_stride=True)  # stream=True
        result = results[0].plot(conf=True, labels=True, boxes=True, masks=True)
        t2 = time.perf_counter()
        fps = 1 / (t2 - t1)
        cv2.putText(result, f"{fps:.3f} FPS", (15, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
        cv2.imshow("result", result)

        # 将处理后的帧写入视频文件
        out.write(result)

        if cv2.waitKey(1) & 0xFF == ord("q"):
            break
    else:
        break

cap.release()
out.release()  # 释放VideoWriter对象
cv2.destroyAllWindows()
