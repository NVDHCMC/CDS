#include "ros/ros.h"
#include "I2C_LowLevel/Control_param.h"
#include <iostream>

int main(int argc, char ** argv) {
	ros::init(argc, argv, "Commander");
	
	ros::NodeHandle node;
	
	ros::Publisher pub1 = node.advertise<I2C_LowLevel::Control_param>("vehicle_command", 1000);
	
	ros::Rate loop_rate(50);

	I2C_LowLevel::Control_param ctrl_param;
	
	int  time = 1;
	
	if(argc == 2 ) {
		ctrl_param.throttle = atoi(argv[1]);
	}
	
	if(argc == 3 ) {
		ctrl_param.throttle = atoi(argv[1]);
		time = atoi(argv[2]);
	}
	
	ctrl_param.steering_angle = 0;
	bool forward = true;
	uint32_t count = 0;
	while (ros::ok()) {
		count++;
		
		if (count >= 50*time) {
			ctrl_param.throttle = 0;
		}
		/*if (ctrl_param.steering_angle > 20) {
			forward = false;
		}
		else if (ctrl_param.steering_angle < -20) {
			forward = true;
		}
		
		if (!forward) {
			ctrl_param.steering_angle -=2;
		}
		else { 
			ctrl_param.steering_angle += 2;
		}*/
		pub1.publish(ctrl_param);
		
		ros::spinOnce();
		
		loop_rate.sleep();
		
	}
	
	return 0;	
}
