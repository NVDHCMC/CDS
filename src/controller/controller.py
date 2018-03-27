#!/usr/bin/env python

import numpy as np
import cv2
from primesense import openni2
from primesense import _openni2 as c_api

import rospy
from I2C_LowLevel.msg import Control_param
from std_msgs.msg import Float32

# Global params
count = 0
low_threshold = 150
high_threshold = 255
polygon = np.array([ [0,479], [740,479], [740,200] , [0,200] ], np.int32)
polygon2 = np.array([[362, 180], [0, 480], [1040, 480], [678, 180]], np.int32)
polygon2 = polygon2.reshape((-1,1,2))
polygon3 = np.array([[130, 270], [130, 480], [800, 480], [800, 270]])
polygon3 = polygon3.reshape((-1,1,2))
element = cv2.getStructuringElement(cv2.MORPH_RECT,(2*7+1,2*2+1))
element1 = cv2.getStructuringElement(cv2.MORPH_RECT,(2*3+1,2*1+1))
kernel = np.ones((2, 2), np.uint8)

# Global variables
center_x_old= 0
junction_flag = 0 
junction_frame = 0
# variable for lane_detection
direction = "right"
tolerance = 30
min_y=80
max_y=100
sum_required = 20
straight_count = 0
straight_flag = 0
#variable for thresholding
thresh = 220
maxValue = 255

def talker(dev, color_stream):
    pub = rospy.Publisher('vehicle_command', Control_param)
    rospy.init_node('custom_talker', anonymous=True)
    r = rospy.Rate(50) #10hz
    msg = Control_param()
    
    while not rospy.is_shutdown():
		msg.throttle, msg.steering_angle = processing_image(dev, color_stream)
		pub.publish(msg)
		r.sleep()
    
def init():
	openni2.initialize("/home/ubuntu/Downloads/2-Linux/OpenNI-Linux-Arm-2.3/Redist/")
	dev = openni2.Device.open_any()
	return dev

def start_color(dev):
	# Start color stream
	color_stream = dev.create_color_stream()
	color_stream.set_video_mode(c_api.OniVideoMode(pixelFormat = c_api.OniPixelFormat.ONI_PIXEL_FORMAT_RGB888, resolutionX=640, resolutionY=480, fps=30))
	color_stream.start()
	return color_stream

def transformImage(image, src, dst):
    M = cv2.getPerspectiveTransform(src, dst)
    warped = cv2.warpPerspective(image, M, (image.shape[1], image.shape[0]), flags=cv2.INTER_LINEAR)
    return warped

def center_path(img, img_eroded, min_y, max_y, direction, center_x_old, tolerance, sum_required, straight_count, straight_flag, count, junction_flag, junction_frame):
    global center_x
    center_x = 320
    ### detect center of lanes
    histogram = []
    point = []
    point_1=[]
    point_2=[]
    sum_f = []
    width=128
    text_scale=0.3
    color = (255,255,255)
    thickness = 1
    
    histogram = np.zeros((width,), dtype=int)
#    img_roi = img_eroded[min_y:max_y, :, 1] #if 3 channels
    img_roi = img_eroded[min_y:max_y, :]
    histogram = np.apply_along_axis(np.count_nonzero, 0, img_roi)
    
    for w in range(0, len(histogram)-1):
        if (histogram[w]!=0 and histogram[w-1]==0) or (histogram[w]!=0 and histogram[w+1]==0):
            point.append(w)
            
    for no in range(0,len(point)-1):
        if np.sum(histogram[point[no]:point[no+1]]) > sum_required :
            point_1.append(point[no])
            point_2.append(point[no+1])
    #print histogram        
    ### detect center of path
    if len(point_1) == 1:
        cv2.putText(img,'1 lane detected',(0,120),cv2.FONT_HERSHEY_SIMPLEX, text_scale,color,thickness,cv2.LINE_AA)
        center_lanes = (point_1[0]+point_2[0])/2
        if junction_flag == 1:
            if direction == "left":
                if center_lanes<43:
                    center_x = (center_lanes+128)/2
                else:
                    center_x = center_lanes/2
            elif direction == "right":
                if center_lanes>86:
                    center_x = center_lanes/2
                else:
                    center_x = (center_lanes+128)/2
        else:
            if center_lanes>center_x_old:
                center_x = center_lanes/2
            elif center_lanes<center_x_old:
                center_x = (center_lanes+128)/2
            
    elif len(point_1) == 2:
        cv2.putText(img,'2 lanes detected',(0,120),cv2.FONT_HERSHEY_SIMPLEX, text_scale,color,thickness,cv2.LINE_AA)
        center_x=(point_1[0]+point_1[1]+point_2[0]+point_2[1])/4
        # straight
        if abs(point_1[0]-point_2[0]) < 15 and abs(point_1[1]-point_2[1]) < 15 and junction_flag == 0:
            straight_count+=1
        if straight_count>100:
            straight_flag = 1
            
    elif len(point_1) == 0:
        cv2.putText(img,'nothing is detected',(5,120),cv2.FONT_HERSHEY_SIMPLEX, text_scale,color,thickness,cv2.LINE_AA)
        center_x=center_x_old
        
    if straight_flag == 1:
        cv2.putText(img,'straight',(5,30),cv2.FONT_HERSHEY_SIMPLEX, text_scale,color,thickness,cv2.LINE_AA)
        cv2.rectangle(img, (center_x_old-15,34), (center_x_old+15,54), color, thickness)

        # junction?
        img_roi = img_eroded[44:64,center_x_old-15:center_x_old+15]
        if np.sum(np.apply_along_axis(np.count_nonzero, 0, img_roi)) > 15 and junction_flag == 0:
            cv2.putText(img,'junction',(5,50),cv2.FONT_HERSHEY_SIMPLEX, text_scale,color,thickness,cv2.LINE_AA)

            junction_flag = 1
            junction_frame = count
            straight_flag = 0
            straight_count = 0
            
    if (junction_flag==1 and len(point_1)==1) == False:      
        if center_x_old!=0 and abs(center_x-center_x_old)>tolerance:
            center_x=center_x_old 
    
    if count > junction_frame + 100:
        junction_flag = 0
    
    if junction_flag == 1:
        cv2.putText(img,'junc_flag',(5,70),cv2.FONT_HERSHEY_SIMPLEX, text_scale,color,thickness,cv2.LINE_AA)
        
        if direction == "left":
            cv2.putText(img,'turn left',(60,10),cv2.FONT_HERSHEY_SIMPLEX, text_scale,color,thickness,cv2.LINE_AA)
        if direction == "right":
            cv2.putText(img,'turn right',(60,10),cv2.FONT_HERSHEY_SIMPLEX, text_scale,color,thickness,cv2.LINE_AA)
            
    center_x_old = center_x
    
    cv2.circle( img, (center_x, (min_y+max_y)/2), 4, color, -1, 8 )
    cv2.putText(img,'center',(center_x, (min_y+max_y)/2),cv2.FONT_HERSHEY_SIMPLEX, text_scale,color,thickness,cv2.LINE_AA)
    
    cv2.line(img, (0, min_y), (129, min_y), color, thickness)
    cv2.line(img, (0, max_y), (129, max_y), color, thickness)
    
    return center_x_old, straight_count, straight_flag, junction_flag, junction_frame

def processing_image(dev, color_stream):
	throttle = 0
	steering_angle = 0.0
	frame_color = color_stream.read_frame()
	frame_color_data = frame_color.get_buffer_as_uint8()
	frame = np.frombuffer(frame_color_data, dtype=np.uint8)
	frame.shape = (480, 640, 3)
	frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR);
	frame = cv2.flip(frame,1)
	img_gray=cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

	# Set threshold and maxValue
	thresh = 220
	maxValue = 255

	# Basic threshold example
	th, img_thres = cv2.threshold(img_gray, thresh, maxValue, cv2.THRESH_BINARY);

	ignore_mask_color = (255,) * frame.shape[2]
	mask = np.zeros_like(img_thres) 
	cv2.fillPoly(mask, [ polygon ], ignore_mask_color)

	masked_image = cv2.bitwise_and(img_thres, mask)

	img_eroded = cv2.erode(masked_image, kernel, iterations=1)
	
	center_x_old, straight_count, straight_flag, junction_flag, junction_frame =center_path(gray, img_eroded,min_y,max_y, direction, center_x_old, tolerance, sum_required, straight_count, straight_flag, count, junction_flag, junction_frame)
	
	#Calculate steering angle
	kp = 0.8
	steering_angle = kp*(320-center_x_old)
	#cv2.imshow("Live feed", frame)
	
	return throttle, steering_angle
	
frame_count = 0;
file_object  = open("/home/ubuntu/data.txt", 'w')

def callback(data):
    file_object.write("%d %f\n" % (frame_count, data.data))
    
if __name__ == '__main__':
	key = 0;
	dev = init()
	color_stream = start_color(dev)
	# Controlling
	#try:
	#	talker(dev, color_stream)
	#except rospy.ROSInterruptException:
	#	pass
	
	# NN data
	
	sub = rospy.Subscriber('chatter', Float32, callback)
	rospy.init_node('custom_talker', anonymous=True)
	while (key != 27):
		frame_count += 1;
		frame_color = color_stream.read_frame()
		frame_color_data = frame_color.get_buffer_as_uint8()
		img = np.frombuffer(frame_color_data, dtype=np.uint8)
		img.shape = (480, 640, 3)
		img = cv2.cvtColor(img, cv2.COLOR_RGB2BGR);
		key = cv2.waitKey(1) & 0xff
		if key == 27:
			break
		cv2.imshow("Live feed", img);
		out.write(img)
	out.release()
	cv2.destroyAllWindows()
	#try:
	#	talker(dev, color_stream)
	#except rospy.ROSInterruptException: pass
