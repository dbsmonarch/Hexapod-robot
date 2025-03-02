import sensor, image, time, lcd
from maix import KPU
import gc
from fpioa_manager import fm
from machine import UART
import time
lcd.init()
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 1000)
clock = time.clock()
anchor = (0.1075, 0.126875, 0.126875, 0.175, 0.1465625, 0.2246875, 0.1953125, 0.25375, 0.2440625, 0.351875, 0.341875, 0.4721875, 0.5078125, 0.6696875, 0.8984375, 1.099687, 2.129062, 2.425937)
kpu = KPU()
kpu.load_kmodel("/sd/KPU/yolo_face_detect/face_detect_320x240.kmodel")
kpu.init_yolo2(anchor, anchor_num=9, img_w=320, img_h=240, net_w=320 , net_h=240 ,layer_w=10 ,layer_h=8, threshold=0.5, nms_value=0.2, classes=1)
fm.register(6, fm.fpioa.UART2_RX)
fm.register(8, fm.fpioa.UART2_TX)
yb_uart = UART(UART.UART2, 9600, 8, 0, 0, timeout=1000, read_buf_len=4096)
while True:
	clock.tick()
	img = sensor.snapshot()
	kpu.run_with_output(img)
	dect = kpu.regionlayer_yolo2()
	fps = clock.fps()
	if len(dect) > 0:
		print("dect:",dect)
		for l in dect :
			a = img.draw_rectangle(l[0],l[1],l[2],l[3], color=(0, 255, 0))
			if(l[0] <= 120):
				yb_uart.write('a')
			if(l[0] >= 160):
				yb_uart.write('b')
			if(l[1] <= 60):
				yb_uart.write('c')
			if(l[1] >= 100):
				yb_uart.write('d')
	a = img.draw_string(0, 0, "%2.1ffps" %(fps), color=(0, 60, 128), scale=2.0)
	lcd.display(img)
	gc.collect()
kpu.deinit()