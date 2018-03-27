#include "Processing.hpp"

#define WIDTH 			128
#define TEXT_SCALE 		0.3f
#define COLOR 
#define THICKNESS 		1
#define CONSTANT 		64
//#define DEBUG
//#define DUONG
#define OLD
//#define CONFIG_NOSPEED

namespace CDIO4_0 {
	Processing::Processing(const char * SVM_model_path): 
		histogram(128, 0), border_value(0, 0, 0), roi(200, 0, 640, 480), 
		point1(100, 0), point2(100, 0), roi2(0, LOWER_Y, 128, (UPPER_Y - LOWER_Y)),
		loop_rate(30) {
			
#ifdef DUONG
		printf("Now running DUONG's solution\n");
#endif

#ifdef CONFIG_NOSPEED
		printf("Now running at PWM level 0\n");
#endif
		framework::OpenNI2::Instance()->init();
		
		this->warp_src[0] = cv::Point2f(362, 180);
		this->warp_src[1] = cv::Point2f(0, 480);
		this->warp_src[2] = cv::Point2f(678, 180);
		this->warp_src[3] = cv::Point2f(1040, 480);
		this->warp_dst[0] = cv::Point2f(200, 0);
		this->warp_dst[1] = cv::Point2f(200, 480);
		this->warp_dst[2] = cv::Point2f(840, 0);
		this->warp_dst[3] = cv::Point2f(840, 480);
		this->warp_matrix = cv::getPerspectiveTransform(this->warp_src, this->warp_dst);
		this->kernel 	  = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(3, 3), cv::Point(1, 1));
		
		this->hog 		  = {
			cv::Size(128, 96),
			cv::Size(16, 16),
			cv::Size(8, 8),
			cv::Size(8, 8), 
			20,
			1,
			-1,
			0,
			0.2,
			1,
			64,
			1
		};
		
		this->hog2 		  = {
			cv::Size(32, 32),
			cv::Size(16, 16),
			cv::Size(8, 8),
			cv::Size(8, 8), 
			18,
			1,
			-1,
			0,
			0.2,
			1,
			64,
			1
		};
		
		this->kp = 3.0;
		this->throttle = 40;
		this->steering_angle = 0.0;
		this->center_x = 64.0;
		this->count = 0;
		this->data = this->control_param.advertise<I2C_LowLevel::Control_param>("vehicle_command", 1000);
#ifdef DEBUG
		this->test_image = cv::imread("/home/ubuntu/jupyter/fr_g91.jpg", 0);
#endif
		
		this->svm_model = cv::Algorithm::load<cv::ml::SVM>("/home/ubuntu/jupyter/1st_model.xml");
		this->sign_model = cv::Algorithm::load<cv::ml::SVM>("/home/ubuntu/jupyter/bienbao6.xml");
	}
	
	Processing::~Processing() {
	}
	
	int Processing::doLoop() {
		uint8_t key = 0;
		uint8_t rv = 1;
		while ((key != 27) && (ros::ok())) {
			if (framework::OpenNI2::Instance()->getData(this->bgr_img, this->depth_img, this->gray, this->disparity))//framework::OpenNI2::Instance()->getGrayImage(this->gray))
			{
#ifndef DEBUG
				//printf("Still looping\n");
				this->preprocess();
				//this->i_type = this->is_intersection();
				this->i_type = Straight;
				if (i_type == T_type)
					printf("Nga 3\n");
				else 
					printf("Di thang\n");
					
				this->throttle = 40;
				this->richtung = this->which_way_to_turn();
				
				if (this->richtung == left)
					printf("left\n");
				else if(this->richtung == right)
					printf("right\n");
				else
					printf("undefined\n");
					
				
				this->find_center();
				
				printf("%f\n", center_x);
				cv::circle(this->thresholded, cv::Point(center_x, 90), 3, cv::Scalar(255, 255, 255), -1);
				cv::rectangle(this->thresholded, roi2, cv::Scalar(255, 255, 255), 2);
				sprintf(filename, "/home/ubuntu/jupyter/debug/frame%d.jpg", this->count);
				cv::imwrite(filename, this->thresholded);
				this->count++;
				this->steering_angle = (CONSTANT - center_x )*this->kp;
				//if (this->steering_angle >= 45.0) this->steering_angle = 45.0;
				//if (this->steering_angle <= -45.0) this->steering_angle	= -45.0;
				cv::imshow("Debug", this->bgr_img);
				cv::imshow("Debug2", this->thresholded);
				//printf("%f\n", center_x);
				key = cv::waitKey(1) & 0xff;
#endif
				
#ifdef DEBUG
				this->preprocess();
				this->richtung = this->which_way_to_turn();
				if (this->richtung == left)
					printf("left\n");
				else if(this->richtung == right)
					printf("right\n");
				else
					printf("undefined\n");
				//printf("%f", this->steering_angle);
				cv::imshow("Debug", this->resized_warped);
				cv::imshow("Debug2", this->thresholded);
				key = cv::waitKey(1) & 0xff;
#endif
			}
			else 
			{
				rv = 0;
				break;
			}
			
#ifndef NOT_PUBLISHING
#ifdef CONFIG_NOSPEED
			this->throttle = 0;
#endif
			ctrl_param.throttle = this->throttle;
			ctrl_param.steering_angle = this->steering_angle;
			data.publish(ctrl_param);
#endif
			ros::spinOnce();
			loop_rate.sleep();
		}
		
		ctrl_param.throttle = 0;
		ctrl_param.steering_angle = 0;
		data.publish(ctrl_param);
		return rv;
	}
	



	__inline__ void Processing::preprocess() {
		//cv::flip(this->gray, this->gray_flipped, 1);
		cv::copyMakeBorder(this->gray, this->frame, 0, 0, 200, 200, cv::BORDER_CONSTANT, border_value);
		cv::warpPerspective(this->frame, this->warped_frame, warp_matrix, cv::Size(1040, 480), cv::INTER_LINEAR);
		cv::resize(this->warped_frame(roi), this->resized_warped, cv::Size(128, 128), cv::INTER_LINEAR);
		cv::threshold(this->resized_warped, this->thresholded, 220, 0xff, cv::THRESH_BINARY);
		cv::erode(this->thresholded, this->thresholded, this->kernel);
		//cv::inRange(this->disparity, cv::Scalar(40, 40, 40), cv::Scalar(255, 255, 255), this->depth_mask);
		
		this->img_roi = this->thresholded(roi2);
		
		
		// Compute hog descriptor vector
#ifdef DEBUG
		//this->hog.compute(this->test_image, this->hog_descriptor);
#else
		cv::Rect asd(0, 0, 128, 96);
		this->hog.compute(this->resized_warped(asd), this->hog_descriptor);
#endif
	}
}
