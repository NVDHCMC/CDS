#include "Processing.hpp"
#define UPPER_Y 		100
#define LOWER_Y 		80
#define SUM_REQUIRED 	20
#define ROI_WIDTH 		20

namespace CDIO4_0 {
	__inline__ void Processing::preprocess() {
		cv::copyMakeBorder(this->gray, this->frame, 0, 0, 200, 200, cv::BORDER_CONSTANT, border_value);
		cv::warpPerspective(this->frame, this->warped_frame, warp_matrix, cv::Size(1040, 480), cv::INTER_LINEAR);
		cv::resize(this->warped_frame(roi), this->resized_warped, cv::Size(128, 128), cv::INTER_LINEAR);
		cv::threshold(this->resized_warped, this->thresholded, 220, 0xff, cv::THRESH_BINARY);
		//cv::erode(this->thresholded, this->thresholded, this->kernel);
		cv::morphologyEx(this->thresholded, this->thresholded, 0, this->kernel);

		this->img_roi = this->thresholded(roi2);
		this->img_roi_list.at(0) = this->thresholded(this->roi_list.at(0));
		this->img_roi_list.at(1) = this->thresholded(this->roi_list.at(1));
		
		// Compute hog descriptor vector
		cv::Rect asd(0, 0, 128, 96);
		this->hog.compute(this->resized_warped(asd), this->hog_descriptor);
	}

	__inline__ uint8_t Processing::calculate_hist() {
		uint8_t pc = 0; // Point count
		uint8_t p1 = 0;
		uint8_t sum = 0; // Hist sum


		for (int ite = 0; ite < 2; ite++) {
			// Fill all vector with 0
			std::fill(this->histogram_list.at(ite).begin(), this->histogram_list.at(ite).end(), 0);


			// Calculate histogram vectors
			for (int i = 0; i < 128; i++) {
				for (int j = 0; j < 20; j++) {
					if (this->img_roi_list.at(ite).at<uchar>(j, i, 0) != 0) {
						this->histogram_list.at(ite).at(i) += 1;
					}
				}
			}

			// Calculate hot spots
			for (int i = 0; i < 128; i++) {
				if (this->histogram_list.at(ite).at(i) != 0) {
					// Reset sum
					sum = 0;
					p1 = i;

					// Continue to sum until it hits zero
					while ((i < 128) && (this->histogram_list.at(ite).at(i) != 0)) {
						sum += histogram_list.at(ite).at(i);
						i++;
					}
					
					// Filtering
					if (sum > SUM_REQUIRED) {
						this->hot_spot_list.at(pc).x = (p1 + i - 1)/2;
						this->hot_spot_list.at(pc).y = (this->roi_list.at(ite).y + 10);
						pc++;
					}
				}
			}

			// Finish calculating hot spots
		}
		// Done

		return pc;
		
	}

	__inline__ void Processing::find_nearest_hotspot(int pc) {
		cv::Point temp;
		int distance;
		this->current_side.at(1) = 0;
		this->current_side.at(0) = 0;
		for(int i = 0; i < pc; i++) {
			temp = this->hot_spot_list.at(i) - this->last_known_point.at(0);
			distance = temp.x*temp.x + temp.y*temp.y;
			if (distance < 400) {
				cv::circle(this->resized_warped, this->hot_spot_list.at(i), 5, cv::Scalar(0, 0, 0), -1);
				this->last_known_point.at(0) = this->hot_spot_list.at(i);
				this->current_side.at(0) = 1;
			}

			//printf("%d %d %d\n", this->hot_spot_list.at(i).x, this->hot_spot_list.at(i).y, i);
			temp = this->hot_spot_list.at(i) - this->last_known_point.at(1);
			distance = temp.x*temp.x + temp.y*temp.y;
			if (distance < 400) {
				cv::circle(this->resized_warped, this->hot_spot_list.at(i), 5, cv::Scalar::all(255), -1);
				this->last_known_point.at(1) = this->hot_spot_list.at(i);
				this->current_side.at(1) = 1;
			}
		}
	}

	__inline__ void Processing::get_center_pixel(int pc) {
		this->center_x_old = this->center_x;


		if ( (this->current_side.at(0) == 0) && (this->current_side.at(1) == 0) )
		{
			this->center_x = this->center_x_old;
		}
		else if ( (this->current_side.at(0) == 1) && (this->current_side.at(1) == 1) ) 
		{
			this->center_x = (this->last_known_point.at(0).x + this->last_known_point.at(1).x)/2;
		}
		else if ( (this->current_side.at(0) == 0) && (this->current_side.at(1) == 1) ) 
		{
			
		}
		else if( (this->current_side.at(0) == 1) && (this->current_side.at(1) == 0) )
		{
			
		}
	}


	__inline__ void Processing::find_center() {
		// Caculate hist
		int pc = 0;
		pc = this->calculate_hist();
		this->find_nearest_hotspot(pc);

		// Get the histogram
		this->get_center_pixel(pc);
	}
}