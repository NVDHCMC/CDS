#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <boost/scoped_ptr.hpp>
#include "Processing.hpp"
//#define THINH_SOLUTION

using namespace cv;
using namespace std;

int main(int argc, char ** argv) {
#ifndef THINH_SOLUTION
	ros::init(argc, argv, "Commander");
	boost::scoped_ptr<CDIO4_0::Processing> cdio_solution(new CDIO4_0::Processing());
	
	cdio_solution->doLoop();
#else
	
	// Thinh solution
	std::string filename = "/home/ubuntu/jupyter/output2.avi";
	cv::VideoCapture capture(filename);
	cv::Mat frame;
	
	if(!capture.isOpened())
		throw "sadfsdfa";

	cv::namedWindow("w",1);
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(10, 10), cv::Point(7, 7));
	
	double x,y,w,h;
	int size; 
	for( ; ; )
	{
		capture >> frame;
		if(frame.empty())
			break;
		cv::Mat thr;
		cv::Mat thr2;
		cv::Mat test;
		
		cv::cvtColor(frame, thr, CV_BGR2GRAY);
		cv::cvtColor(frame, thr2, CV_BGR2GRAY);
		cv::threshold(thr,thr,30,255,0);
		cv::morphologyEx(thr, thr, 0, kernel);
		
		int largest_area; 
		largest_area = 0;
		int largest_contour_index; 
		largest_contour_index = 0;
		cv::Rect bounding_rect;
		std::vector< std::vector<cv::Point> > contours;
		std::vector<cv::Vec4i> hierarchy;
		//cv::Mat dst(frame);
		
		cv::findContours(thr,contours, hierarchy, CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE);
		for(int i = 0; i < contours.size();i ++)
		{
			double a = cv::contourArea(contours[i], false);
			if(a > largest_area)
			{
				largest_area = a;
				largest_contour_index = i;
				bounding_rect = cv::boundingRect(contours[i]);
			}
		}
		x = bounding_rect.x;
		y = bounding_rect.y;
		w = bounding_rect.width+20;
		h = bounding_rect.height;
	    
	    printf(" %d %d %d %d\n", bounding_rect.x, bounding_rect.y, bounding_rect.height, bounding_rect.width);
		
		if (largest_area > 5000)
		{
		for(int i = x+w/2-50;i<x+w/2+50;i++)
		{
			for (int j=0;j<thr.rows;j++)
			thr.at<uchar>(j,i) = 255;
		}
	    }
		//x,y,w,h = cv::boundingRect(contours[i]);
		/*
		if (largest_area > 500)
		{
			x++;
		}
		*/
		
		cv::rectangle(frame,bounding_rect, cv::Scalar(0,255,0), 1,8,0);
		//Scalar color(255,255,255);
		/*for (int i = 0; i < 480; i++) {
			for (int j = 0; j < 640; j++) {
				if (abs(0.00550200057941*j + -0.226713896529*i - ((float) thr2.at<uchar>(i, j)) + 99.212752098) < 5) {
					thr.at<uchar>(i, j) = 0;
				}
			}
		}*/
		
		
		
		//cv::imshow("w2", frame);
		cv::imshow("w", thr);
		cv::waitKey(20);
	}
	cv::waitKey(0);
	
#endif
	return 0;
}
