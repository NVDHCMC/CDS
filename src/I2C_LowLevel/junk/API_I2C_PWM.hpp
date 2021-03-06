#ifndef __API_I2C_PWM_HPP
#define __API_I2C_PWM_HPP

#include <string.h>
#include <termios.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#include "JHPWMPCA9685.h"

// At 61 hz a frame is 16.39 milliseconds
// The PCA9685 PWM Driver is 12 bits
// Full Reverse signal to the ESC is 1 ms
// Neutral signal to the ESC is 1.5 ms
// Full Throttle signal to the ESC is 2 ms

#define PWM_FREQ 60
//dieu khien dong co
#define THROTTLE_MAX_REVERSE    245 // 153 // 1.0 ms/16.39ms * 4096
#define THROTTLE_NEUTRAL        368 // 363 // 1.5 ms/16.39ms * 4096
#define THROTTLE_MAX_FORWARD    491 // 573 // 2.0 ms/16.39ms * 4096
//dieu khien servo
#define STEERING_MAX_RIGHT1      200 // 153
#define STEERING_MAX_LEFT1       530 // 573
#define STEERING_MAX_RIGHT2      200 // 153
#define STEERING_MAX_LEFT2       530 // 573

// The THROTTLE is plugged into the following PWM channel
#define THROTTLE_CHANNEL  0
// The Steering Servo is plugged into the follow PWM channel
#define STEERING_CHANNEL1 1
#define STEERING_CHANNEL2 2


#define DIR_REVERSE     1
#define DIR_BRAKE       0
#define DIR_FORWARD     2

#define SET_CTRL 1
#define GET_CTRL 2

#define MIN_ANGLE -90 // 10 * maxLeft angle(20 degree) = -200, mul 10 to smooth control
#define MAX_ANGLE 90  // 10 * maxRight angle

namespace Hardware {
	class API_I2C {
	public:
		API_I2C();
		~API_I2C();
		int getkey();
		int map (double x, int in_min, int in_max, int out_min, int out_max);
		void api_pwm_pca9685_init();
		void api_pwm_pca9685_release();
		int api_set_STEERING_control(double &theta);
		int api_set_FORWARD_control(int &throttle_val);
		int api_set_REVERSE_control(int &throttle_val);
	private:
		PCA9685 pca9685;
	};
}

#endif
