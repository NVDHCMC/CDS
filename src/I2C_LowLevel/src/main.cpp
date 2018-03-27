#include "HardwareController.hpp"

// Define GPIO pins and Sensor input
#define BUTTON_1 		160
#define BUTTON_2		161
#define BUTTON_3		163
#define BUTTON_4 		164
#define SENSOR 			165
#define LED				166

boost::shared_ptr<Hardware::Controller> pController;

bool init_gpio() {
	int ret = 0;
	bool rv = true;
	ret += pController->hal_gpio.gpioUnexport(BUTTON_1);
	ret += pController->hal_gpio.gpioExport(BUTTON_1);
	std::cout << "1\n";
	ret += pController->hal_gpio.gpioUnexport(BUTTON_2);
	ret += pController->hal_gpio.gpioExport(BUTTON_2);
	std::cout << "2\n";
	ret += pController->hal_gpio.gpioUnexport(BUTTON_3);
	ret += pController->hal_gpio.gpioExport(BUTTON_3);
	std::cout << "3\n";
	ret += pController->hal_gpio.gpioUnexport(BUTTON_4);
	ret += pController->hal_gpio.gpioExport(BUTTON_4);
	std::cout << "4\n";
	ret += pController->hal_gpio.gpioUnexport(SENSOR);
	ret += pController->hal_gpio.gpioExport(SENSOR);
	std::cout << "5\n";
	ret += pController->hal_gpio.gpioUnexport(LED);
	ret += pController->hal_gpio.gpioExport(LED);
	std::cout << "6\n";
	ret += pController->hal_gpio.gpioSetDirection(BUTTON_1, INPUT);
	ret += pController->hal_gpio.gpioSetDirection(BUTTON_2, INPUT);
	ret += pController->hal_gpio.gpioSetDirection(BUTTON_3, INPUT);
	ret += pController->hal_gpio.gpioSetDirection(BUTTON_4, INPUT);
	ret += pController->hal_gpio.gpioSetDirection(SENSOR, INPUT);
	ret += pController->hal_gpio.gpioSetDirection(LED, OUTPUT);
	
	if (ret != 0) {
		rv = false;
	}
	
	return rv;
}

int main(int argc, char ** argv) {
	ros::init(argc, argv, "HW_Controler");
	std::string command_topic("vehicle_command");
	std::string data_topic("data_topic");
	pController.reset(new Hardware::Controller(data_topic, command_topic));
	
	if (!(pController->init()))
	{
		std::cout << "-- [ERROR]: Error in PCA9685 initialization.\n";
		return -1;
	}
	
	if (!(init_gpio())) {
		std::cout << "-- [ERROR]: Error in GPIO initialization.\n";
		return -1;
	}	
	
	/*ros::Rate loop_rate(10);
	unsigned int bt_status = 0;
	unsigned int sensor_status = 0;
	while (ros::ok()) {
		pController->hal_gpio.gpioGetValue(BUTTON_4, &bt_status);
		pController->hal_gpio.gpioGetValue(SENSOR, &sensor_status);
		printf("Button 4: %d\n", bt_status);
		printf("Sensor  : %d\n", sensor_status);
		loop_rate.sleep();
		ros::spinOnce();
	}*/
	pController->fetch_command();
	
	return 0;
}
