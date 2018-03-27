#include "OpenniWrapper.hpp"

namespace Wrapper {
	OpenniWrapper::OpenniWrapper() {
	}
	
	OpenniWrapper::~OpenniWrapper() {
	}
	
	bool OpenniWrapper::init() {
		openni::Status rv = OpenNI::initialize();
		bool ret = true;
		if (rv != STATUS_OK) {
			ret = false;
			printf("-- [ERROR]: Unable to initialize OpenNI");
		}
		
		rv = this->astra.open(ANY_DEVICE);
		if (rv != STATUS_OK) {
			printf("-- [ERROR]: Unable to open new device");
			ret = false;
		}
		return ret;
	}
	
	void OpenniWrapper::stream_color() {
	}
	
	void OpenniWrapper::stream_depth() {
	}
}
