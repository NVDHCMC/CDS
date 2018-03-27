#!/usr/bin/env python

import numpy as np
import cv2
from primesense import openni2
from primesense import _openni2 as c_api

import rospy
from I2C_LowLevel.msg import Control_param
from std_msgs.msg import Float32

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
    center_x = 64
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
        center_x=(point_1[0]+point_1[1]+point_2[0]+point_2[1])/4
        # straight
        if abs(point_1[0]-point_2[0]) < 15 and abs(point_1[1]-point_2[1]) < 15 and junction_flag == 0:
            straight_count+=1
        if straight_count>50:
            straight_flag = 1
            
    elif len(point_1) == 0:
        center_x=center_x_old
        
    if straight_flag == 1:
        # junction?
        img_roi = img_eroded[24:44,center_x_old-15:center_x_old+15]
        
        if np.sum(np.apply_along_axis(np.count_nonzero, 0, img_roi)) > 15 and junction_flag == 0:
            junction_flag = 1
            print "Nga ba"
            junction_frame = count
            straight_flag = 0
            straight_count = 0
            
    if (junction_flag==1 and len(point_1)==1) == False:      
        if center_x_old!=0 and abs(center_x-center_x_old)>tolerance:
            center_x=center_x_old 
    
    if count > junction_frame + 100:
        junction_flag = 0
            
    center_x_old = center_x
    return center_x_old, straight_count, straight_flag, junction_flag, junction_frame

def callback(data):
    file_object.write("%d %f\n" % (frame_count, data.data))


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
IMAGE_H = 450
IMAGE_W = 640
src = np.float32([[362, 180], [0, 480], [678, 180], [1040, 480]])
dst = np.float32([[200, 0], [200, IMAGE_H+30], [840, 0], [840, IMAGE_H+30]])
cap = cv2.VideoCapture('/media/ubuntu/Backup_data/data13/output13.avi')

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
kp = 3

pub = rospy.Publisher('vehicle_command', Control_param)
rospy.init_node('custom_talker', anonymous=True)
r = rospy.Rate(50) #10hz
msg = Control_param()
dev = init()
color_stream = start_color(dev)

msg.throttle = 0


while not rospy.is_shutdown():
    ## Code
    depth_stream = dev.create_depth_stream()
    depth_stream.start()
    depth_stream.set_video_mode(c_api.OniVideoMode(pixelFormat = c_api.OniPixelFormat.ONI_PIXEL_FORMAT_DEPTH_100_UM, resolutionX=640, resolutionY=480, fps=30))
    color_stream = dev.create_color_stream()
    color_stream.set_video_mode(c_api.OniVideoMode(pixelFormat = c_api.OniPixelFormat.ONI_PIXEL_FORMAT_RGB888, resolutionX=640, resolutionY=480, fps=30))
    color_stream.start()
    frame = depth_stream.read_frame()
    kernel = np.ones((7,7),np.uint8)
    Max = 0
    frame_data = frame.get_buffer_as_uint16()
    img = np.frombuffer(frame_data, dtype=np.uint16)
    img.shape = (480, 640)
    img = cv2.flip(img,1)
    img8 = (img/256).astype('uint8')
    #depth_ROI = img[360:480,:]
    #img8 = cv2.flip(img8,1)

    (_,img8) = cv2.threshold(img8,30,255,cv2.THRESH_BINARY)

    img8_copy = img8.copy()
    img8_copy = cv2.bitwise_not(img8_copy)
    Left_ROI = img8_copy[240:479,0:319]

    Right_ROI = img8_copy[240:479,320:640]
    Right_ROI = cv2.morphologyEx(Right_ROI,cv2.MORPH_OPEN, kernel)
    #contours,hierarchy = cv2.findContours(Right_ROI, cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)
    #for cnt in contours:
        #AreaR = cv2.contourArea(cnt)
        #if AreaR > Max:
            #Max_Right = AreaR
    #print(Max_Right)
    #if Max_Right > 50000:
        #angle = 30
    #if Max_Right < 50000:
	#	angle = 0
    #print(angle)
    #contoursL,hierarchy = cv2.findContours(Left_ROI, cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)
    #for cnt in contoursL:
        #AreaL = cv2.contourArea(cnt)
        #if AreaL > Max:
            #Max_Left = AreaL
    #print(Max_Left)
    #if Max_Left > 60000:
        #angle = -30
    #else:
		#angle = 0
    #print(angle)
    
    ## Message
    msg.steering_angle = 0
    cv2.imshow("sdf", img8)
    cv2.waitKey(1)
    pub.publish(msg)
    r.sleep()
        
cap.release()
 
# Closes all the frames
cv2.destroyAllWindows() 
    
