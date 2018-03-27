#ifndef __PROCESSING_HPP
#define __PROCESSING_HPP
#include "openni2.h"
#include "ros/ros.h"
#include "I2C_LowLevel/Control_param.h"

namespace CDIO4_0 {
	typedef enum Direction {
		left,
		right,
		undefined
	} direction;
	
	typedef enum Inter_type {
		Straight,
		T_type,
		cross
	} intersection_type;
	
	class Processing {
	private:
		// Control params
		float kp;
		int throttle;
		float steering_angle;
		
		// Mics
		std::vector<int> histogram;
		std::vector<float> point1;
		std::vector<float> point2;
		std::vector<float> sum_f;
		std::vector<float> hog_descriptor;
		std::vector< std::vector<cv::Point> > sign_contours;
		std::vector<cv::Vec4i> sign_hierarchy;
		
		// SVM models
		cv::Ptr<cv::ml::SVM> svm_model;
		cv::Ptr<cv::ml::SVM> sign_model;
		cv::Scalar border_value;
		
		// Warp matrices
		cv::Point2f warp_src[4];
		cv::Point2f warp_dst[4];
		cv::Mat warp_matrix;
		cv::Rect roi;
		cv::Rect roi2;
		cv::Mat kernel;
		uint32_t straight_count;
		cv::HOGDescriptor hog;
		cv::HOGDescriptor hog2;
		
		// Debug
		cv::Mat test_image;
		char filename[100];
		
		// ROS components
		ros::NodeHandle control_param;
		ros::Publisher data;
		ros::Rate loop_rate;
		I2C_LowLevel::Control_param ctrl_param;
		int count;
		
		// Functions
		__inline__ void preprocess();
		__inline__ void find_center();
		__inline__ intersection_type is_intersection();
		__inline__ bool looking_for_sign();
		__inline__ direction which_way_to_turn();

		// New solution
		std::vector<cv::Rect> roi_list;
		std::vector< std::vector<int> > histogram_list;
		std::vector<cv::Mat> img_roi_list;
		std::vector<cv::Point> hot_spot_list;

	public:
		Processing(const char * SVM_model_path = "");
		~Processing();
		bool trainSVM();
		bool deploySVM();
		int doLoop();
		
		// Sources
		cv::Mat disparity;
		cv::Mat bgr_img;
		cv::Mat bgr_img_flipped;
		cv::Mat hsv_img;
		cv::Mat hsv_img_depth_thresholded;
		cv::Mat hsv_img_thresholded;
		cv::Mat depth_img;
		cv::Mat depth_mask;
		cv::Mat valid_depth;
		cv::Mat gray;
		cv::Mat gray_flipped;
		cv::Mat ir_img;
		
		// Processed
		cv::Mat frame;
		cv::Mat warped_frame;
		cv::Mat resized_warped;
		cv::Mat thresholded;
		cv::Mat img_roi;
		
		//
		float center_x;
		float center_x_old;
		intersection_type i_type;
		direction richtung;
		
	};
}
		
#endif
