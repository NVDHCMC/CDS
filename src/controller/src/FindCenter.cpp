#include "Processing.hpp"
#define UPPER_Y 		100
#define LOWER_Y 		80
#define SUM_REQUIRED 	20

namespace CDIO4_0 {
	
	__inline void Processing::duong_solution() {
	}
	
	
	
	
	__inline void Processing::minh_solution() {
	}
	
	__inline void Processing::calc_hist() {
	}
	
	__inline__ void Processing::find_center() {
		for (int i = 0; i < 128; i++) {
			for (int j = 0; j < (UPPER_Y - LOWER_Y); j++) {
				this->histogram.at(i) = 0;
			}
		}
		for (int i = 0; i < 128; i++) {
			for (int j = 0; j < (UPPER_Y - LOWER_Y); j++) {
				if (this->img_roi.at<uchar>(j, i, 0) != 0) {
					this->histogram.at(i) += 1;
				}
			}
		}
		// Get the histogram
		uint8_t pc = 0;
		uint8_t p1 = 0;
		uint8_t sum = 0;
		this->center_x_old = this->center_x;
		unsigned int i = 0;
		for ( i = 0; i < 128; i++) {
			if (this->histogram.at(i) != 0) {
				sum = 0;
				p1 = i;
				while ((i < 128) && (this->histogram.at(i) != 0)) {
					sum += histogram.at(i);
					i++;
				}
				
				if (sum > SUM_REQUIRED) {
					this->point1.at(pc) = p1;
					if (i > 0)
						this->point2.at(pc) = i - 1;
					else 
						this->point2.at(pc) = 0;
					pc++;
				}
			}
		}
		float center_lanes = 0.0;
		//printf("1\n");
		if ((pc == 0)){
			this->center_x = this->center_x_old;
		}
#ifdef DUONG
		//else if (this->i_type != Straight) {
			//printf("Junction\n");
		else if (this->richtung == left) {
			printf("Left\n");
			if (pc == 1) {
				center_lanes = ((float) (this->point1.at(0)+this->point2.at(0)))/2.0;
				if (center_lanes > 60.0) {
					this->center_x = (center_lanes + 45.0)/2.0;
				}
				else {
					this->center_x = (center_lanes + 60.0)/2.0;
				}
			}
			else if (pc == 2) {
				this->center_x = (this->point1.at(0) + this->point1.at(1) + this->point2.at(0) + this->point2.at(1))/4.0;
				this->center_x = ((this->center_x  + 60.0)/2);
			}
		}
		else if (this->richtung == right) {
			printf("Right\n");
			if (pc == 1) {
				center_lanes = ((float) (this->point1.at(0)+this->point2.at(0)))/2.0;
				printf("%f\n", center_lanes);
				if (center_lanes < 68.0) {
					this->center_x = (center_lanes + 70.0)/2.0;
				}
				else {
					this->center_x = (center_lanes + 64.0)/2.0;
				}
			}
			else if (pc == 2) {
				this->center_x = (this->point1.at(0) + this->point1.at(1) + this->point2.at(0) + this->point2.at(1))/4.0;
				this->center_x = ((this->center_x  + 64.0)/2);
			}
		}
		else {
			if (pc == 1) {
				center_lanes = ((float) (this->point1.at(0)+this->point2.at(0)))/2.0;
				if (center_lanes > this->center_x_old) {
					this->center_x = (center_lanes)/2.0;
				}
				else if (center_lanes <= this->center_x_old) {
					this->center_x = (center_lanes + 128.0)/2.0;
				}
			}
			if (pc == 2) {
				this->center_x = (this->point1.at(0) + this->point1.at(1) + this->point2.at(0) + this->point2.at(1))/4.0;
			}
		}
#endif


/* ------------------------ MINH ------------------------------------*/
#ifdef OLD
		else if (pc == 1) {
			center_lanes = ((float) (this->point1.at(0)+this->point2.at(0)))/2.0;
			cv::circle(this->thresholded, cv::Point(center_lanes, 90), 4, cv::Scalar(0, 0, 0), -1);
			
			cv::circle(this->thresholded, cv::Point(10,10), 4, cv::Scalar(255, 255, 255), -1);
			//if (this->i_type != Straight) {
			if ((center_lanes >= 44)&&(center_lanes <= 84)){
				if (this->richtung == right) {
					this->center_x = (center_lanes + 128.0)/2.0;
				}
				else if (this->richtung == left) {
					this->center_x = center_lanes/2.0;
				}
				else{
					if ((center_x_old!=0 && (abs(center_x-center_x_old)>20){
						center_x=center_x_old;
					}
				}
			}
			//else if (this->i_type == Straight) {
			else {
				if (center_lanes > this->center_x_old) {
					this->center_x = center_lanes/2.0;
				}
				else if (center_lanes < this->center_x_old) {
					this->center_x = (center_lanes+128.0)/2.0;
				}
			}
			char vitri[30];
			sprintf(vitri, "%f", this->center_x);
			cv::putText(this->thresholded,vitri,(5,20),cv::FONT_HERSHEY_SIMPLEX, 0.3,cv::Scalar(255, 255, 255),1);

		}
		else if (pc == 2) {
			this->center_x = (this->point1.at(0) + this->point1.at(1) + this->point2.at(0) + this->point2.at(1))/4.0;
		}
		/*
		if ((center_x_old!=0 && (abs(center_x-center_x_old)>20){
			center_x=center_x_old;
		}
		*/
            
#endif



	}
}