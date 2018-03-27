#include "Processing.hpp"

//#define CONFIG_WITHDEPTH

namespace CDIO4_0 {
	
	__inline__ direction Processing::which_way_to_turn() {
		direction d;
		d = undefined;
		
		// Extract candidate
		cv::cvtColor(this->bgr_img, this->hsv_img, cv::COLOR_BGR2HSV);
		cv::inRange(this->hsv_img, cv::Scalar(75, 80, 130), cv::Scalar(150, 255, 255), this->hsv_img_thresholded);
		
#ifdef CONFIG_WITHDEPTH
		// With depth
		this->hsv_img_depth_thresholded = cv::Scalar(0);
		this->hsv_img_thresholded.copyTo(this->hsv_img_depth_thresholded, this->depth_mask);
		cv::findContours(this->hsv_img_depth_thresholded, this->sign_contours, this->sign_hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
#else
		// /wo depth
		cv::findContours(this->hsv_img_thresholded, this->sign_contours, this->sign_hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
#endif	

		float a;
		cv::Rect bounding_rect;
		
		// Thresholding contour areas
		int cc = 0;
		cv::Mat roi;
		std::vector<float> hog_descriptor2;
		float prediction;
		
		for (int i = 0; i < this->sign_contours.size(); i++) {
			a = cv::contourArea(this->sign_contours[i], false);
			if (a > 300) {
				bounding_rect = cv::boundingRect(sign_contours[i]);
				roi = this->gray(bounding_rect);
				cv::resize(roi, roi, cv::Size(32, 32), cv::INTER_LINEAR);
				this->hog2.compute(roi, hog_descriptor2);
				prediction = this->sign_model->predict(hog_descriptor2);
				if (prediction == 1) {
					d = left;
				}
				else if (prediction == 2) {
					d = right;
				}
			}
		}

		return d;
	}
	
	__inline__ intersection_type Processing::is_intersection() {
		intersection_type t;
		t = Straight;
		
		if (this->svm_model->predict(this->hog_descriptor)) {
			t = T_type;
		}
		
		return t;
	}
	
	__inline__ bool Processing::looking_for_sign() {
		bool rv = false;
		return rv;
	}
}