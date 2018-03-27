#include "HardwareController.hpp"


namespace Hardware {
	Controller::Controller(): buffer_length{1000} {
		this->data = this->control_param.advertise<I2C_LowLevel::Control_param>("Default_topic_name", buffer_length);
	}
	
	Controller::Controller(std::string publish_tpic_name, std::string subscribe_tpic_name): buffer_length{1000} {
		this->publish_topic_name = publish_tpic_name;
		this->subscribe_topic_name = subscribe_tpic_name;
		this->data = this->control_param.advertise<I2C_LowLevel::Control_param>(this->publish_topic_name, buffer_length);
	}
	
	Controller::~Controller() {
		this->api_i2c.api_pwm_pca9685_release();
	}
	
	void Controller::send_data() {
		
	}
	
	void Controller::fetch_command() {
		// Start fetching command from publisher
		this->command = this->control_param.subscribe<I2C_LowLevel::Control_param>(this->subscribe_topic_name, buffer_length, &Controller::command_callback, this);
		
		// Let ROS handle receive callback
		ros::spin();
	}
	
	void Controller::command_callback(const I2C_LowLevel::Control_param::ConstPtr& ctrl_param) {
		// Put your control code here;
		printf("Steering angle: %f\tThrottle %d\n", ctrl_param->steering_angle, ctrl_param->throttle);
		int throttle_val = ctrl_param->throttle;
		double steering_angle = ctrl_param->steering_angle;
		this->api_i2c.api_set_STEERING_control(steering_angle);
		this->api_i2c.api_set_FORWARD_control(throttle_val);
	}
	
	bool Controller::init() {
		bool rv = true;
		this->api_i2c.api_pwm_pca9685_init();
		if (this->api_i2c.pca9685.error >= 0) {
			rv = true;
		}
		else {
			rv = false;
		}
		return rv;
	}
}

