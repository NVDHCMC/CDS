
#ifndef __HARDWARE_CONTROLLER_HPP
#define __HARDWARE_CONTROLLER_HPP

#include "ros/ros.h"
#include <stdint.h>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include "I2C_LowLevel/Control_param.h"
#include "API_I2C_PWM.hpp"
#include "JHPWMPCA9685.h"
#include "GPIOHal.hpp"

namespace Hardware {
	class Controller {
	public:
		Controller();
		Controller(std::string publish_tpic_name, std::string subscribe_tpic_name);
		~Controller();
		
		GPIO hal_gpio;
		
		void send_data();
		void fetch_command();
		bool init();
		
	private:
		ros::NodeHandle control_param;
		ros::Publisher data;
		ros::Subscriber command;
		
		API_I2C api_i2c;
		
		std::string publish_topic_name;
		std::string subscribe_topic_name;
		int buffer_length;
		void command_callback(const I2C_LowLevel::Control_param::ConstPtr& ctrl_param);
	};
}

#endif
