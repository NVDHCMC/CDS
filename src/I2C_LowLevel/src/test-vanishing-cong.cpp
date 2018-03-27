//get image from astra and write to video file
//#include "opencv2/videoio/videoio.hpp"
#include "api_i2c_pwm.h"
#include "api_uart.h"
#include "api_lane_detection.h"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <OpenNI.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


using namespace std;
using namespace cv;
using namespace openni;
Mat element = getStructuringElement(MORPH_RECT,Size(2*7+1,2*2+1),Point(5,2));
Mat element1 = getStructuringElement(MORPH_RECT,Size(2*3+1,2*1+1),Point(3,1));
int Xmin, Xmax, Z;
Mat bgr_img;
int t =0;
int h1=0, v=0, minv=0, maxv=0;
int XOmin[200], XOmax[200], ZO[200];
int nr =0;
#define SAMPLE_READ_WAIT_TIMEOUT 2000 //2000ms
#define VIDEO_FRAME_WIDTH 640
#define VIDEO_FRAME_HEIGHT 480

VideoWriter depth_videoWriter;
VideoWriter bgr_videoWriter;
bool is_save_file = true;
//====================================================================
Mat gray(480,640,CV_8U);
//====================================================================

int cport_nr;
char buf_send[BUFF_SIZE];
char buf_send1[BUFF_SIZE];
void setThrottle(int speed) {
	if (speed>=0)
     sprintf(buf_send, "f%d\n", speed);
	else { 
		speed=-speed;
		sprintf(buf_send, "b%d\n", speed);
	}
}


void analyzeFrame(const VideoFrameRef& frame)
{
    DepthPixel* depth_img_data;
    RGB888Pixel* color_img_data;
    int w = frame.getWidth();
    int h = frame.getHeight();
    Mat depth_img(h, w, CV_16U);
    Mat depth_ROI;
    Mat depth_img_8u;
    Mat color_img(h, w, CV_8UC3);
    Mat dis, U_dis;
Mat mn;
    vector<Vec2f> lines;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    switch (frame.getVideoMode().getPixelFormat())
    {
    case PIXEL_FORMAT_DEPTH_1_MM:
    case PIXEL_FORMAT_DEPTH_100_UM:
	//cout<<"aaasdfjmbkfhdlfl"<<endl;
        depth_img_data = (DepthPixel*)frame.getData();
        memcpy(depth_img.data, depth_img_data, h*w*sizeof(DepthPixel));
	depth_ROI = depth_img(Range(360,479),Range::all());
	depth_img_8u = Mat::zeros(120,639,CV_8U);
	convertScaleAbs(depth_ROI, depth_img_8u,0.014,0);//0.014
        depth_img_8u.convertTo(depth_img_8u, CV_8U);
	flip(depth_img_8u,depth_img_8u,1);
	
	//==================================================
	//==================================================
	dis = Mat::zeros(256,640,CV_8U);
	for(int i=0;i<depth_img_8u.cols;i++){
	   for(int j=0;j<depth_img_8u.rows;j++){
		unsigned char d = depth_img_8u.at<uchar>(j,i);
		if(d!=0)
		dis.at<uchar>(d,i) += 1; 
	   }	
	}
	threshold(dis,U_dis,30,255,0);
	//dilate(U_dis,U_dis,element1);
	//=====================================================
	findContours(U_dis,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
	t = hierarchy.size();
	for(int i =0;i<hierarchy.size();i++){
	vector<Point> z = contours[i];
        Point pt1,pt2;
	minv = z[0].x;
	maxv = z[0].x;
	int ymin = z[0].y;
	h1 = dis.at<uchar>(ymin,maxv);
	for(int j =1;j<z.size();j++){
	pt1 = z[j-1];
	pt2 = z[j];
	if(maxv<pt2.x) maxv = pt2.x;
	if(minv>pt2.x) minv = pt2.x;
	if(ymin>pt2.y) ymin = pt2.y;
	if(h1<dis.at<uchar>(pt2.y,pt2.x)) h1 = dis.at<uchar>(pt2.y,pt2.x);
	}
	//v = cvRound(0.00913*ymin*ymin-3.735*ymin+409.4);
	v = cvRound(0.00913*ymin*ymin-3.95*ymin+409.4);
	int Z = 270*600/(v+360-240); //264
	//int Z = 270*600/(v+240-240);
	int Xmin = Z*(minv-320)/580-20;  //312
	int Xmax = Z*(maxv-320)/580-20;
	XOmin[i] = Xmin;
	XOmax[i] = Xmax;
	ZO[i] = Z;
	minv = (510*Xmin+91+316*Z)/Z;
	maxv = (510*Xmax+91+316*Z)/Z;
	v = (137470+239*Z)/Z;//+15;
	Z=270*509/(v-239);
	if(minv<0) minv =1;
	if(maxv>=640) maxv = 639;
	if(v>=480){ v = 479; h1 = h1-(v-479);}
	//line(bgr_img,Point(minv,v),Point(maxv,v),Scalar(0,0,255),1,CV_AA);
	//line(bgr_img,Point(minv,v-h1),Point(maxv,v-h1),Scalar(0,0,255),1,CV_AA);
	//line(bgr_img,Point(minv,v),Point(minv,v-h1),Scalar(0,0,255),1,CV_AA);
	//line(bgr_img,Point(maxv,v-h1),Point(maxv,v),Scalar(0,0,255),1,CV_AA);
	//bgr_img(Range(v-h1,v),Range(minv,maxv)) = Mat::zeros(h1,maxv-minv,CV_8UC3);
	gray(Range(v-h1,v),Range(minv,maxv)) = Mat::zeros(h1,maxv-minv,CV_8U);
	}
	//imshow("gray1",bgr_img);
	//imshow("gray",gray(Range(360,480),Range::all()));
        //imshow("depth", depth_img_8u);
	//bgr_videoWriter.write(bgr_img);
	//cvtColor(depth_img_8u, mn, CV_GRAY2BGR);
	//depth_videoWriter.write(mn);
        break;

    case PIXEL_FORMAT_RGB888:
//cout<<"cong"<<endl;
        color_img_data = (RGB888Pixel*)frame.getData();

        memcpy(color_img.data, color_img_data, h*w*sizeof(RGB888Pixel));

        cvtColor(color_img, color_img, COLOR_RGB2BGR);

	flip(color_img,color_img,1);
	cvtColor(color_img,gray,CV_BGR2GRAY);
	//color_img.copyTo(bgr_img);
	//GaussianBlur(gray, gray, Size(5, 5), 0, 0);
	adaptiveThreshold(gray,gray,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,155,-40);
	erode(gray,gray,element);
	dilate(gray,gray,element);
	Canny(gray, gray, 60, 70, 3);
	cvtColor(gray,color_img,CV_GRAY2BGR);
	//if ((is_save_file)&&(!color_img.empty()))
			//bgr_videoWriter.write(color_img);
        break;
    default:
        printf("Unknown format\n");
    }
}

int
map1 (double x, int in_min, int in_max, int out_min, int out_max)
{
    double toReturn =  1.0 * (x - in_min) * (out_max - out_min) /
            (in_max - in_min) + out_min ;
    return (int)(round(toReturn));
}

int main(int argc, char **argv)
{
    //=======================================
	Mat moi, left, right;
	int height = 480;
	int xc=0, yc=0;
	float e2 = 0,e3 = 0,pe2=0, PID, conge2 = 0;
	float A = 0,B = 0, X=0, X1=0, X2 =0,r1,r2;
	double theta = 0.0, mintheta =0.0, maxtheta = 0.0, ctheta =0.0;;
	//float kp = 0.6,kd =0.6,ki = 0.00;
	float kp = 0.8,kd =1.2,ki = 0.00;
	int dir = 0, throttle_val = 0, set_throttle_val = 10, current_state = 0;
	unsigned int ll=0;
    //================================================================

    PCA9685 *pca9685 = new PCA9685() ;
    api_pwm_pca9685_init( pca9685 );
    if (argc > 1) sscanf(argv[1], "%d", &set_throttle_val);
    throttle_val = set_throttle_val;
    fprintf(stderr, "Initial speed: %d\n", set_throttle_val);
    dir = DIR_REVERSE;
    if (pca9685->error >= 0)
    api_pwm_set_control( pca9685, dir, throttle_val, theta, current_state );
    //cport_nr = api_uart_open();
    //=====================================================================
    Status rc = OpenNI::initialize();
    if (rc != STATUS_OK)
    {
        printf("Initialize failed\n%s\n", OpenNI::getExtendedError());
        return 1;
    }
    //================================================================
    Device device; 
    rc = device.open(ANY_DEVICE);
    if (rc != STATUS_OK)
    {
        printf("Couldn't open device\n%s\n", OpenNI::getExtendedError());
        return 2;
    }

    VideoStream depth, color;  

    if (device.getSensorInfo(SENSOR_DEPTH) != NULL)
    {
        rc = depth.create(device, SENSOR_DEPTH);  
        if (rc == STATUS_OK)
        {
            VideoMode depth_mode = depth.getVideoMode();
            depth_mode.setFps(30);
            depth_mode.setResolution(640, 480);
            depth_mode.setPixelFormat(PIXEL_FORMAT_DEPTH_100_UM);
            depth.setVideoMode(depth_mode);

            rc = depth.start();
            if (rc != STATUS_OK)
            {
                printf("Couldn't start the color stream\n%s\n", OpenNI::getExtendedError());
            }
        }
        else
        {
            printf("Couldn't create depth stream\n%s\n", OpenNI::getExtendedError());
        }
    }

    if (device.getSensorInfo(SENSOR_COLOR) != NULL) //anh mau
    {
        rc = color.create(device, SENSOR_COLOR);
        if (rc == STATUS_OK)
        {
            VideoMode color_mode = color.getVideoMode();
            color_mode.setFps(30);
            color_mode.setResolution(640, 480);
            color_mode.setPixelFormat(PIXEL_FORMAT_RGB888);
            color.setVideoMode(color_mode);

            rc = color.start();
            if (rc != STATUS_OK)
            {
                printf("Couldn't start the color stream\n%s\n", OpenNI::getExtendedError());
            }
        }
        else
        {
            printf("Couldn't create color stream\n%s\n", OpenNI::getExtendedError());
        }
    }

    VideoFrameRef colorframe;
    VideoFrameRef depthframe;
    VideoStream* streams[] = {&depth, &color};

	int codec = CV_FOURCC('D','I','V', 'X');
    Size output_size(VIDEO_FRAME_WIDTH, VIDEO_FRAME_HEIGHT);
    Size output_size1(VIDEO_FRAME_WIDTH, VIDEO_FRAME_HEIGHT/4);

    string depth_filename = "depth.avi";
	string bgr_filename = "bgr.avi";
    
    Mat depthMap;
	Mat bgrImage;

    Mat crop_depthMap;
    Mat crop_grayImage;

    char key = 0;

    bool start = false;
    bool stop = false;
    bool stop1= false;
    bool pstop = false;

    if(is_save_file)
    {
        depth_videoWriter.open(depth_filename, codec, 12, output_size1, true);
		bgr_videoWriter.open(bgr_filename, codec, 12, output_size, true);
    }

	cout<< " Press s to start and f to stop"<< endl<< flush;
		throttle_val = 50;
		setThrottle(throttle_val);
	char k = 1;
sprintf(buf_send, "x");
sprintf(buf_send1, "c");
int Xmin1=0,Xmax1 =0;
int dis = 280,goc = 500, tr = 0;
float mtheta, ztheta, ptheta;
int lk=0, sv =4;
float rmin[200], rmax[200], r1min[200], r1max[200], bkmin,r0,pptheta =0.0;
float r0min,r0max;
    while (true)
    {

		key = getkey();
         if( key == 's'){
            start = true;
	    //api_uart_write(cport_nr, buf_send);		
	cport_nr = api_uart_open();
		api_uart_write(cport_nr, buf_send1);
		RS232_CloseComport(cport_nr);
	api_pwm_set_control( pca9685, dir, throttle_val, theta, current_state );	
	}	
        if( key == 'f')
            stop = true;
        if( stop ){
	    fprintf(stderr, "End process.\n");
            theta = 0;
            throttle_val = 0;
            setThrottle(throttle_val);
            //api_uart_write(cport_nr, buf_send);
	    int pwm2 = map1( 0, MIN_ANGLE, MAX_ANGLE, STEERING_MAX_RIGHT, STEERING_MAX_LEFT );
		pca9685->setPWM(STEERING_CHANNEL2,0, pwm2);
cport_nr = api_uart_open();
	//api_uart_write(cport_nr, buf_send);
	RS232_CloseComport(cport_nr);
	    break;
	}

        if( start )
        {     
/*if(lk>=sv) {
	if(ll>5) {
theta = 250;
api_pwm_set_control( pca9685, dir, throttle_val, theta, current_state );
waitKey(800);
stop =true;
}
}*/
		/*if(stop1 == true){
		cport_nr = api_uart_open();
		api_uart_write(cport_nr, buf_send);
		RS232_CloseComport(cport_nr);
		pstop = true;
		} 
		if((pstop == true)&&(stop1 == false)){
		cport_nr = api_uart_open();
		api_uart_write(cport_nr, buf_send1);
		RS232_CloseComport(cport_nr);
		pstop = false;
		}*/
		
		int readyStream = -1;
		    rc = OpenNI::waitForAnyStream(streams,2, &readyStream, SAMPLE_READ_WAIT_TIMEOUT);
		    if (rc != STATUS_OK)
		    {
		        printf("Wait failed! (timeout is %d ms)\n%s\n", SAMPLE_READ_WAIT_TIMEOUT, OpenNI::getExtendedError());
		        break;
		    }

		    //switch (k)
		    //{
		    //case 0:
		        // Depth
		        //depth.readFrame(&frame);
			
			//k = 1;
		        //break;
		    //case 1:
		        // Color
		        //color.readFrame(&frame);
			//k--;
		        //break;
		   // default:
		        //printf("Unxpected stream\n");
			color.readFrame(&colorframe);
			//waitKey(2);
			//readyStream = 1;
			//rc = OpenNI::waitForAnyStream(streams,2, &readyStream, SAMPLE_READ_WAIT_TIMEOUT);
			depth.readFrame(&depthframe);
			//k--;
		    //}
	analyzeFrame(colorframe);
	analyzeFrame(depthframe);
//=====================================================================================
	ztheta = 0;
	if(nr>0){
	nr--;dis = 150;}
	else dis = 280;
//=======================================================================================
	gray.copyTo(moi);
	left = moi(Range(3*height/4,479), Range(0,319));
	 right = moi(Range(3*height/4,479), Range(320,639));
	//===========================================================================
	vector<Vec2f> lineleft, lineright;
	HoughLines(left, lineleft, 1, CV_PI / 180, 60, 0, 0);
	HoughLines(right, lineright, 1, CV_PI / 180,60, 0, 0);
	vector<Vec2f> lineleftsc = lineleft;
	vector<Vec2f> linerightsc = lineright;
	int wright = lineright.size();
	int wleft = lineleft.size();
	//===========================================================================
	int a=0, b=0, c=0, d=0;
	if((wleft>0) && (wright>0)){
	//=========================================================
	int n = 0;
	for(int i=0;i<wleft;i++){

	   //==================================================================
	   float rho = lineleftsc[i][0], phi = lineleftsc[i][1];
	   for(int j=0;j<wright;j++){
		//====================================================================================
		if(abs(linerightsc[j][1]-lineleftsc[i][1])<0.2){//goc bang nhau
		    float y1 = (lineleftsc[i][0]-320*cos(lineleftsc[i][1]))/sin(lineleftsc[i][1]);
		    float y2 = (linerightsc[j][0])/sin(linerightsc[j][1]);
		  if(abs(y1-y2)<60){ // cung toa do y
		    float rho1 = linerightsc[j][0],phi1 = linerightsc[j][1];
		    rho1 = rho1+320*cos(phi1)+360*sin(phi1);
		//(510.151*cos(phi)+509.15*sin(phi))*X+(316.4116*cos(phi)+238.76*sin(phi)-rho)*Z+0.3372*Y*cos(phi) =0;
		    float co = 510.151*cos(phi1);
		    float si = 316.4116*cos(phi1)+238.76*sin(phi1)-rho1;
		    mtheta = -(atan(si/co))*1800/3.14;
		    if(abs(mtheta-ptheta)<goc) {
			ptheta = theta = mtheta;
		    //cout<<"1line2 "<<theta<<endl;
		    //tr=3;
		    goto cong;
		}
		//=======================================================================================
		    if(abs(mtheta-ptheta)>800){
			int yp = 0;
dilate(gray,gray,element1);
			for(int p = 0;p<640;p++){
			  int us = (rho1-p*cos(phi1))/sin(phi1);
			  if(gray.at<uchar>(us,p)!=0) yp++;
			}
			if(yp>300&&ll>90){
theta = 0;
api_pwm_set_control( pca9685, dir, throttle_val, theta, current_state );
waitKey(1500);
theta = 150;
api_pwm_set_control( pca9685, dir, throttle_val, theta, current_state );
waitKey(500);
theta = 0;
api_pwm_set_control( pca9685, dir, throttle_val, theta, current_state );
waitKey(1000);
			 lk++;
			 ll = 0;
			}
			
		    }
		  }
		}
	   }
	   //===================================================================

		
	   //(510.151*cos(phi))*X+(316.4116*cos(phi)+238.76*sin(phi)-rho)*Z+(509.15*sin(phi)+0.3372cos(phi))*Y =0;	
	   //if(abs(cos(phi))>0.03){
	     rho = rho + 360*sin(phi);
	     float co = 510.151*cos(phi);
	     float si = 316.4116*cos(phi)+238.76*sin(phi)-rho;
	     float r = (509.15*sin(phi)+0.3372*cos(phi))*270;
			   //Z = 758.5;
	     mtheta = -(atan(si/co))*1800/3.14;
	     if(abs(mtheta-ptheta)<goc){
	     ztheta += mtheta;
	     a += (-r-758.5*si)/co;
	     n++;}
            }
	//}
	if(n!=0){
	  a = a/n;
	}
	else goto duy;
	//===========================================================================
	int n1 = 0;
	for(int i=0;i<wright;i++){
	   float rho = linerightsc[i][0], phi = linerightsc[i][1];
	   //if(abs(cos(phi))>0.05){
	     rho = rho + 360*sin(phi)+320*cos(phi);
	     float co = 510.151*cos(phi);
	     float si = 316.4116*cos(phi)+238.76*sin(phi)-rho;
	     float r = (509.15*sin(phi)+0.3372*cos(phi))*270;
			   //Z = 758.5;
	     mtheta = -(atan(si/co))*1800/3.14;
	     if(abs(mtheta-ptheta)<goc){
	     ztheta += mtheta;
	     c += (-r-758.5*si)/co;
	     n1++;}
	   //}
	}
	if(n1!=0){
	  c = c/n1;
	  //ptheta = ztheta/1n;
	}
	else goto vo;
	if(n1+n>0) ptheta = ztheta/(n+n1);
	tr = 0;
	//==================================================================	
	X = (c+a)/2;
//==========================================================================================================
	if(t!=0){
	Xmin1 = c; Xmax1 = a;
	//cout<<"co vat can"<<endl;
	nr = 1;
//dis = 100;
	for(int i=0;i<t;i++){
	if(XOmin[i]>a&&XOmax[i]<c){//nam giua duong
	  if(XOmin[i]-a>350) {//lech phai
	    if(Xmin1>XOmin[i]) Xmin1 = XOmin[i];
	  }
	  else if(c-XOmax[i]>350) {//lech trai
	    if(Xmax1<XOmax[i]) Xmax1 = XOmax[i];
	  }
	  else{
	     //stop = true;
	     //goto cong;
	  } 
	}
	else if((XOmax[i]>a)&&(XOmax[i]<c)){//chan duong ben trai
	  if(c-XOmax[i]>350) {
	    if(Xmax1<XOmax[i]) Xmax1 = XOmax[i];
	  }
	  else {//stop = true; goto cong;
	  }
	}
	else if((XOmin[i]<c)&&(XOmin[i]>a)){//chan duong ben phai
	  if(XOmin[i]-a>350) {
	    if(Xmin1>XOmin[i]) Xmin1 = XOmin[i];
	  }
	  else{ //stop = true; goto cong;
	  }
	}
	else if((XOmin[i]<a)&&(XOmax[i]>c)) {//stop = true; goto cong;
         } //chan nguyen duong
else;
	}
//if(abs(Xmin1 - Xmax1)<300) stop = true;
X = (Xmin1 + Xmax1)/2;
	}
	else {
	  if(nr>0) {
	    if(Xmin1>c) Xmin1 = c;
	    if(Xmax1<a) Xmax1 = a;
	    X = (Xmin1 + Xmax1)/2;
	  }
	}
//===============================================================================================

	pe2 = e2;
	e2 = X-17;
	if(pe2!=0)
	   conge2 = e2-pe2;
	PID = kp*e2+ kd*conge2;
	theta = PID;
//cout<<"2 line"<<endl;
	//cout<<"TH 1"<<endl;
	//cout<<"a"<<a<<endl;
	//cout<<"c"<<c<<endl;
	//cout<<"X"<<X<<endl;
	//cout<<"theta"<<theta<<endl;
//cout<<"aas"<<endl

	}

//===========================================================================

	else if(wleft>0){
vo:
//cout<<"line trai"<<endl;
a=0;b=0;c=0;d=0;
	   int n = 0;
	   for(int i=0;i<wleft;i++){
		//(510.151*cos(phi))*X+(316.4116*cos(phi)+238.76*sin(phi)-rho)*Z+(509.15*sin(phi)+0.3372cos(phi))*Y =0;	
	      float rho = lineleftsc[i][0], phi = lineleftsc[i][1];
	      //if(abs(cos(phi))>0.05){
	        rho = rho + 360*sin(phi);
	        float co = 510.151*cos(phi);
	        float si = 316.4116*cos(phi)+238.76*sin(phi)-rho;
	        float r = (509.15*sin(phi)+0.3372*cos(phi))*270;
	        if(r>0){
		   r1 = r - (dis)*sqrt(si*si+co*co);
		   r2 = r - 2*dis*sqrt(si*si+co*co);
		}
	        else{    
		   r1 = r + (dis)*sqrt(si*si+co*co);
		   r2 = r + 2*dis*sqrt(si*si+co*co);
		}
		//Z = 758.5;
		mtheta = -(atan(si/co))*1800/3.14;
	        if(abs(mtheta-ptheta)<goc||tr!=1){
		ztheta += mtheta;
		a += (-r1-758.5*si)/co;
		b += (-r-758.5*si)/co;
		c += (-r2-758.5*si)/co;
	        n++;}
		if(abs(mtheta-ptheta)>800&&tr==1){
		  int yp = 0;
dilate(gray,gray,element1);
		  for(int p = 0;p<320;p++){
		     int us = (rho-p*cos(phi))/sin(phi);
		     if(gray.at<uchar>(us,p)!=0) yp++;
		  }
		  if(yp>200&&ll>90){
		     lk++;
		     ll = 0;
		  }
		  
		}
	      }
	   //}
	   tr = 1;
	   if(n>0){
	     X = a/n;
	     X1 = b/n;
	     X2 = c/n;
	     ptheta = ztheta/n;
	   } 
        bkmin = r0 = (X*X+758.5*758.5)/2/X;
//===============================================================================
        if(t!=0){
	//cout<<"line trai"<<endl;
	//cout<<"bk cong"<<bkmin<<endl;
	r0max = (X1*X1+758.5*758.5)/2/X1;
	r0min = (X2*X2+758.5*758.5)/2/X2;
if(1/r0min>1/r0max) {
	r0min = (X1*X1+758.5*758.5)/2/X1;
	r0max = (X2*X2+758.5*758.5)/2/X2;
}
//cout<<"r0min"<<r0min<<endl;
//cout<<"r0max"<<r0max<<endl;
        k=0;n=0;
	for(int i=0;i<t;i++){
	   if(XOmin[i]==150) XOmin[i] = 155;
	   if(XOmax[i]==-150) XOmax[i] = -155; 
	   rmin[i] = ((XOmin[i]-150)*(XOmin[i]-150)+ZO[i]*ZO[i])/2/(XOmin[i]-150);
	   rmax[i] = ((XOmax[i]+150)*(XOmax[i]+150)+ZO[i]*ZO[i])/2/(XOmax[i]+150);
	}
	for(int i=0;i<t;i++){
	   for(int j=i+1;j<t;j++){
	      if((1/rmin[i])>(1/rmin[j])){
		float temp = rmin[i];
		rmin[i] = rmin[j];
		rmin[j] = temp;
		temp = rmax[i];
		rmax[i] = rmax[j];
		rmax[j] = temp;
	      }
	   }
	}
	for(int i=0;i<t-1;i++){
	  if((1/rmin[i+1])<(1/rmax[i])){
	    if((1/rmax[i+1])<(1/rmax[i])){rmin[i+1]=rmin[i];rmax[i+1]=rmax[i];}
	    else{rmin[i+1]=rmin[i];}
	    r1min[n] = rmin[i+1]; r1max[n] = rmax[i+1];
	  }
	  else{r1min[n] = rmin[i]; r1max[n] = rmax[i];r1min[n+1] = rmin[i+1]; r1max[n+1] = rmax[i+1];n=n+1;}
	}
	for(int i=0;i<n+1;i++){
	  //cout<<"bk min"<<r1min[i]<<endl;
	  //cout<<"bk max"<<r1max[i]<<endl;
	  if((1/r1min[i]<1/r0)&&(1/r1max[i]>1/r0)){/*
	  if(1/r1min[i]>1/r0min){if(1/r1min[i]<1/bkmin) bkmin = r1min[i];nr=5;}
	  if(1/r1max[i]<1/r0max){if(1/r1max[i]>1/bkmin) bkmin = r1max[i];nr=5;}*/
	  /*if(1/r1min[i]<1/r0){bkmin = r1max[i]; nr=-5;}
	  if(1/r1max[i]>1/r0){bkmin = r1min[i]; nr=5;}*/
	  if(abs(r1min[i]-r0)>abs(r1max[i]-r0)){bkmin = r1max[i];}
	  else{bkmin = r1min[i]; nr=0;}
/*if(r0>0){
	    if(r1max[i]<bkmin) bkmin = r1max[i];}
else{if(r1min[i]>bkmin) bkmin = r1min[i];}*/
	  }
	}
//cout<<"bk vatcan"<<bkmin<<endl;
        }
//================================================================================
	     /*pe2 = e2;
	     e2 = X-17;
	     if(pe2!=0)
	       conge2 = e2-pe2;
	     PID = kp*e2+ kd*conge2;
	     theta = PID;*/
	theta = atan(300/bkmin);
	theta= theta*1800/3.14;
	theta = 1.5*theta+0.3*(theta-pptheta);
//cout<<"theta"<<theta<<endl;
/*
	     if(t!=0){
	       ctheta = kp*X1;
	      for(int i=0;i<t;i++){
	       mintheta = atan((XOmin[i]-250)/ZO[i])*1800/3.14;
	       maxtheta = atan((XOmax[i]+250)/ZO[i])*1800/3.14;
	       if(mintheta>ctheta&&mintheta<theta) {theta = mintheta;dis =100;nr=3;}
		if(maxtheta>theta&&maxtheta<250) {theta = maxtheta; dis = 400;nr=3;}
		if(mintheta<ctheta&&maxtheta>250) {stop1= true; goto cong;}
		}
	     }*/
	}
//============================================================================

	else if(wright>0){
duy:
//cout<<"line phai"<<endl;
	   int n = 0;
a=0;b=0;c=0;d=0;
	   for(int i=0;i<wright;i++){
	      float rho = linerightsc[i][0], phi = linerightsc[i][1];
	     // if(abs(cos(phi))>0.05){
	        rho = rho + 360*sin(phi)+320*cos(phi);
	        float co = 510.151*cos(phi);
	        float si = 316.4116*cos(phi)+238.76*sin(phi)-rho;
	        float r = (509.15*sin(phi)+0.3372*cos(phi))*270;
	        if(r>0){
		   r1 = r - (dis)*sqrt(si*si+co*co);
		   r2 = r - 2*(dis)*sqrt(si*si+co*co);
		}
		else{    
		   r1 = r + (dis)*sqrt(si*si+co*co);
		   r2 = r + 2*(dis)*sqrt(si*si+co*co);
		}
	        //Z = 758.5;
		mtheta = -(atan(si/co))*1800/3.14;
	        if(abs(mtheta-ptheta)<goc||tr!=2){
		ztheta += mtheta;
	        c += (-r1-758.5*si)/co;
		d += (-r-758.5*si)/co;
		a += (-r2-758.5*si)/co;
	        n++;}
		if(abs(mtheta-ptheta)>800&&tr==2){
		  int yp = 0;
dilate(gray,gray,element1);
		  for(int p = 320;p<640;p++){
		     int us = (rho-p*cos(phi))/sin(phi);
		     if(gray.at<uchar>(us,p)!=0) yp++;
		  }
		  if(yp>200&&ll>120){
		     lk++;
		     ll = 0;
		  }
		  
		}
	      }
		tr = 2;
	  // }
	   if(n>0){
	      X = c/n;
	      X1 = d/n;
	      X2 = a/n;
	      ptheta = ztheta/n;
	   }
	   bkmin = r0 = (X*X+758.5*758.5)/2/X;
//===================================================================
        if(t!=0){
//cout<<"line phai"<<endl;
//cout<<"bk cong"<<bkmin<<endl;
	r0max = (X1*X1+758.5*758.5)/2/X1;
	r0min = (X2*X2+758.5*758.5)/2/X2;
if(1/r0min>1/r0max) {
	r0min = (X1*X1+758.5*758.5)/2/X1;
	r0max = (X2*X2+758.5*758.5)/2/X2;
}
//cout<<"r0min"<<r0min<<endl;
//cout<<"r0max"<<r0max<<endl;
       k=0;n=0;
	for(int i=0;i<t;i++){
	   if(XOmin[i]==150) XOmin[i] = 155;
	   if(XOmax[i]==-150) XOmax[i] = -155; 
	   rmin[i] = ((XOmin[i]-150)*(XOmin[i]-150)+ZO[i]*ZO[i])/2/(XOmin[i]-150);
	   rmax[i] = ((XOmax[i]+150)*(XOmax[i]+150)+ZO[i]*ZO[i])/2/(XOmax[i]+150);
	}
	for(int i=0;i<t;i++){
	   for(int j=i+1;j<t;j++){
	      if((1/rmin[i])>(1/rmin[j])){
		float temp = rmin[i];
		rmin[i] = rmin[j];
		rmin[j] = temp;
		temp = rmax[i];
		rmax[i] = rmax[j];
		rmax[j] = temp;
	      }
	   }
	}
	for(int i=0;i<t-1;i++){
	  if((1/rmin[i+1])<(1/rmax[i])){
	    if((1/rmax[i+1])<(1/rmax[i])){rmin[i+1]=rmin[i];rmax[i+1]=rmax[i];}
	    else{rmin[i+1]=rmin[i];}
	    r1min[n] = rmin[i+1]; r1max[n] = rmax[i+1];
	  }
	  else{r1min[n] = rmin[i]; r1max[n] = rmax[i];r1min[n+1] = rmin[i+1]; r1max[n+1] = rmax[i+1];n=n+1;}
	}
	for(int i=0;i<n+1;i++){
	  //cout<<"bk min"<<r1min[i]<<endl;
	  //cout<<"bk max"<<r1max[i]<<endl;
	  if((1/r1min[i]<1/r0)&&(1/r1max[i]>1/r0)){
	  /*if(1/r1min[i]>1/r0min){if(1/r1min[i]<1/bkmin) bkmin = r1min[i];nr=5;}
	  if(1/r1max[i]<1/r0max){if(1/r1max[i]>1/bkmin) bkmin = r1max[i];nr=5;}*/
	  /*if(1/r1min[i]<1/r0){bkmin = r1max[i]; nr = 5;}
	  if(1/r1max[i]>1/r0){bkmin = r1min[i]; nr = -5;}*/
	  if(abs(r1min[i]-r0)>abs(r1max[i]-r0)){bkmin = r1max[i]; nr=0;}
	  else{bkmin = r1min[i];}
	    /*if(r0>0){
	    if(r1max[i]<bkmin) bkmin = r1max[i];}
	    else{if(r1min[i]>bkmin) bkmin = r1min[i];}*/
	  }
	}
//cout<<"bk vatcan"<<bkmin<<endl;
        }
//===================================================================
	theta = atan(300/bkmin);
	theta= theta*1800/3.14;
	theta = 1.5*theta+0.3*(theta-pptheta);
//cout<<"theta"<<theta<<endl;
	    /*pe2 = e2;
	    e2 = X-17;
	    if(pe2!=0)
		conge2 = e2-pe2;
            PID = kp*e2+ kd*conge2;
	    theta = PID;*/
	    //cout<<"TH 3"<<endl;

	   
	}
else{
if(t>0){
nr = 0;k=0;
int n=0;
for(int i=0;i<t;i++){
   if(XOmin[i]==150) XOmin[i] = 155;
   if(XOmax[i]==-150) XOmax[i] = -155; 
   rmin[i] = ((XOmin[i]-150)*(XOmin[i]-150)+ZO[i]*ZO[i])/2/(XOmin[i]-150);
   rmax[i] = ((XOmax[i]+150)*(XOmax[i]+150)+ZO[i]*ZO[i])/2/(XOmax[i]+150);
}
for(int i=0;i<t;i++){
   for(int j=i+1;j<t;j++){
      if((1/rmin[i])>(1/rmin[j])){
	float temp = rmin[i];
	rmin[i] = rmin[j];
	rmin[j] = temp;
	temp = rmax[i];
	rmax[i] = rmax[j];
	rmax[j] = temp;
      }
   }
}
for(int i=0;i<t-1;i++){
  if((1/rmin[i+1])<(1/rmax[i])){
    if((1/rmax[i+1])<(1/rmax[i])){rmin[i+1]=rmin[i];rmax[i+1]=rmax[i];}
    else{rmin[i+1]=rmin[i];}
    r1min[n] = rmin[i+1]; r1max[n] = rmax[i+1];
  }
  else{r1min[n] = rmin[i]; r1max[n] = rmax[i];r1min[n+1] = rmin[i+1]; r1max[n+1] = rmax[i+1];n=n+1;}
}
k=0;
bkmin = r1min[0];
for(int i=0;i<n+1;i++){
	  //cout<<"bk min"<<r1min[i]<<endl;
	  //cout<<"bk max"<<r1max[i]<<endl;
  if(r1min[i]<0&&r1max[i]>0){
    if(theta>0){
    if(abs(r1max[i])>abs(bkmin)){ bkmin = r1max[i];k++;}}
    else{if(abs(r1min[i])>abs(bkmin)){ bkmin = r1min[i];k++;}}
  }
}
  if(k>0){
  theta = atan(300/bkmin);
  theta= theta*1800/3.14;
  theta = 1.5*theta+0.3*(theta-pptheta);
  pptheta = theta;
//cout<<"bk vatcan"<<bkmin<<endl;
//cout<<"theta"<<theta<<endl;
  }
}
else{
   if(nr>0) nr--;
   else theta = 0;
}
}
	cong:
//cout<<"theta"<<theta<<endl;
pptheta = theta;
api_pwm_set_control( pca9685, dir, throttle_val, theta, current_state );
ll++;
//cout<<ll<<endl;
//cout<<"theta"<<ptheta<<endl;
		    char key = waitKey(1);

		    if( key == 27 ) break;
	}

    }
	if(is_save_file )
    {
        depth_videoWriter.release();
		bgr_videoWriter.release();
    }
    depth.stop();
    color.stop();
    depth.destroy();
    color.destroy();
    device.close();
    OpenNI::shutdown();

    return 0;
}







