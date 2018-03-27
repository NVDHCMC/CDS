
#ifndef _OPENNI_WRAPPER
#define _OPENNI_WRAPPER

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <OpenNI.h>

namespace Wrapper {
	class OpenniWrapper {
	public:
		OpenniWrapper();
		~OpenniWrapper();
		
		bool init();
		void stream_depth();
		void stream_color();
		
		openni::Device astra;
	private:
		
	};
}

#endif
