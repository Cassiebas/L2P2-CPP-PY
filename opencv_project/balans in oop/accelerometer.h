#include "mpu6050.h"

#define RAD_T_DEG 57.29577951308 //rad to degrees 180/pi

#ifndef ACCELERO__H
#define ACCELERO__H
class accelerometer: public mpu6050 {
	public :
		accelerometer();
		void measure();
		void checktresholds();
	
	private :
		int16_t two_complement_to_int( uint16_t word);
		void getfirst();
		void bringtodeg();
		
		int16_t AX;
		int16_t AY;
		int16_t AZ;
		int16_t signed_int; //for complementary
		
		float _accel_angle[2];
		
		int firstmeasurex;
		int firstmeasurey;
		int firstmeasurez;
		int flag;
};
#endif
