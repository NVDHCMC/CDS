//#include "main.hpp"
#include "HardwareController.hpp"

boost::shared_ptr<Hardware::Controller> pController;

int main(int argc, char ** argv) {
	ros::init(argc, argv, "HW_Controler");
	std::string command_topic("hardware_command");
	std::string data_topic("data_topic");
	pController.reset(new Hardware::Controller(data_topic, command_topic));
	pController->fetch_command();
	
	return 0;
}
