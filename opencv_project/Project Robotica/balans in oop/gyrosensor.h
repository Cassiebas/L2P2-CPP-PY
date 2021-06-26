#include "mpu6050.h"
//    Gyroscope
//#define G_OFF_X -733
//#define G_OFF_Y 433
//#define G_OFF_Z -75
//Select the appropriate settings

#define GYRO_RANGE 3

#if GYRO_RANGE == 1 
	#define GYRO_SENS 65.5
	#define GYRO_CONFIG 0b00001000
#elif GYRO_RANGE == 2
	#define GYRO_SENS 32.8
	#define GYRO_CONFIG 0b00010000
#elif GYRO_RANGE == 0
  #define GYRO_SENS 1
#elif GYRO_RANGE == 3
	#define GYRO_SENS 16.4
	#define GYRO_CONFIG 0b00011000
#else //Otherwise, default to 0
	#define GYRO_SENS 131.0
	#define GYRO_CONFIG 0b00000000
#endif
#undef GYRO_RANGE


#ifndef GYRO_H
#define GYRO_H

class gyrosensor: public mpu6050 {
	private:
		float gyro_off[3]; //Temporary storage
		float gx_off = 0;
		float gy_off = 0;
		float gz_off = 0;
		
		int16_t X;
		int16_t Y;
		int16_t Z;
		
		void getOffsets();
};
#endif
