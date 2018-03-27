
#ifndef __MAIN_HPP
#define __MAIN_HPP

#include "ros/ros.h"
#include <stdint.h>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include "I2C_LowLevel/Control_param.h"
#include "api_i2c_pwm.h"
#include "JHPWMPCA9685.h"

namespace Hardware {
	class Controller {
	public:
		Controller();
		Controller(std::string publish_tpic_name, std::string subscribe_tpic_name);
		~Controller();
		void send_data();
		void fetch_command();
		
	private:
		ros::NodeHandle control_param;
		ros::Publisher data;
		ros::Subscriber command;
		
		PCA9685 pca9685;
		
		std::string publish_topic_name;
		std::string subscribe_topic_name;
		int buffer_length;
		void api_pwm_pca9685_init();
		void command_callback(const I2C_LowLevel::Control_param::ConstPtr& ctrl_param);
	};
	
	Controller::Controller(): buffer_length{1000} {
		this->data = this->control_param.advertise<I2C_LowLevel::Control_param>("Default_topic_name", buffer_length);
		this->api_pwm_pca9685_init();
	}
	
	Controller::Controller(std::string publish_tpic_name, std::string subscribe_tpic_name): buffer_length{1000} {
		this->publish_topic_name = publish_tpic_name;
		this->subscribe_topic_name = subscribe_tpic_name;
		this->data = this->control_param.advertise<I2C_LowLevel::Control_param>(this->publish_topic_name, buffer_length);
		this->api_pwm_pca9685_init();
	}
	
	Controller::~Controller() {
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
		printf("Steering angle: %f\tThrottle %f\n, ctrl_param->steering_angle", ctrl_param->throttle);
	}
	
	void Controller::api_pwm_pca9685_init()
	{
		// Initialize the PWM board
		int err = this->pca9685.openPCA9685();
		if (err < 0)
		{
			cout<< endl<< "Error: %d"<< this->pca9685.error<< flush;
		}

		cout<< endl<< "PCA9685 Device Address: 0x"<< hex
			<< this->pca9685.kI2CAddress<< dec<< endl;

		this->pca9685.setAllPWM(0,0) ;
		this->pca9685.reset() ;
		this->pca9685.setPWMFrequency( PWM_FREQ ) ;
		// Set the PWM to "neutral" (1.5ms)
		sleep(1) ;
		int pwm2 = map( 0, MIN_ANGLE, MAX_ANGLE, STEERING_MAX_RIGHT2, STEERING_MAX_LEFT2 );
		this->pca9685.setPWM(STEERING_CHANNEL2, 0, pwm2);
		this->pca9685.setPWM(STEERING_CHANNEL1, 0, pwm2);
		this->pca9685.setPWM(THROTTLE_CHANNEL,0,THROTTLE_NEUTRAL);
		sleep(1) ;
	}

}

#endif
