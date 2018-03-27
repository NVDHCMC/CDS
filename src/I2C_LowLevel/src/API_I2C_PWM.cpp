
#include "API_I2C_PWM.hpp"

using namespace std;

namespace Hardware {
	API_I2C::API_I2C() {
	}
	
	API_I2C::~API_I2C() {
	}
	
	int API_I2C::getkey() {
		int character;
		struct termios orig_term_attr;
		struct termios new_term_attr;

		/* set the terminal to raw mode */
		tcgetattr(fileno(stdin), &orig_term_attr);
		memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
		new_term_attr.c_lflag &= ~(ECHO|ICANON);
		new_term_attr.c_cc[VTIME] = 0;
		new_term_attr.c_cc[VMIN] = 0;
		tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

		/* read a character from the stdin stream without blocking */
		/*   returns EOF (-1) if no character is available */
		character = fgetc(stdin);

		/* restore the original terminal attributes */
		tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

		return character;
	}


	int API_I2C::map (double x, int in_min, int in_max, int out_min, int out_max)
	{
		double toReturn =  1.0 * (x - in_min) * (out_max - out_min) /
				(in_max - in_min) + out_min ;
		return (int)(round(toReturn));
	}


	void API_I2C::api_pwm_pca9685_init()
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

	void API_I2C::api_pwm_pca9685_release()
	{

		int dir = 0, throttle_val = 0;
		double theta = 0;
		int current_state = 0;

		if (this->pca9685.error >= 0)
			this->api_set_STEERING_control(theta);

		this->pca9685.closePCA9685();
	}
	
	
	int API_I2C::api_set_FORWARD_control(int &throttle_val)
	{       
		int pwm = this->map( throttle_val, 0, 100, THROTTLE_NEUTRAL, THROTTLE_MAX_FORWARD ); 
		this->pca9685.setPWM(THROTTLE_CHANNEL,0, pwm);
	}
	
	
	int API_I2C::api_set_REVERSE_control(int &throttle_val)
	{     
		this->pca9685.setPWM(THROTTLE_CHANNEL,0, THROTTLE_MAX_REVERSE);
		usleep(100000) ;
		this->pca9685.setPWM(THROTTLE_CHANNEL,0,THROTTLE_NEUTRAL) ;
		usleep(100000) ;  
		int pwm = this->map( throttle_val, 0, 100, THROTTLE_NEUTRAL, THROTTLE_MAX_REVERSE ); 
		this->pca9685.setPWM(THROTTLE_CHANNEL,0, pwm);
	}
	
	
	int API_I2C::api_set_STEERING_control(double &theta)
	{
		if( theta < MIN_ANGLE)
			theta = MIN_ANGLE;

		if( theta > MAX_ANGLE )
			theta = MAX_ANGLE;
			
		int pwm2 = this->map( theta, MIN_ANGLE, MAX_ANGLE, STEERING_MAX_RIGHT2, STEERING_MAX_LEFT2 ); 
		this->pca9685.setPWM(STEERING_CHANNEL2,0, pwm2);
		int pwm1 = this->map( -theta, MIN_ANGLE, MAX_ANGLE, STEERING_MAX_RIGHT1, STEERING_MAX_LEFT1 ); 
		this->pca9685.setPWM(STEERING_CHANNEL1,0, pwm1);
		return pwm2;
	}
	
}
