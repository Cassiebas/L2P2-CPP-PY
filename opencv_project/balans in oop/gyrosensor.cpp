#include "gyrosensor.h"

gyrosensor::gyrosensor()
{
	
}
;

void gyrosensor::getOffsets() {
	gx_off = 0, gy_off = 0, gz_off = 0; //Initialize the offsets to zero
	
	printf("Calculating offsets!\n");
	for (int i = 0; i < 1000; i++) {
		gyro_off[0] = i2c_read(0x43) << 8 | i2c_read(0x44); //read X registers
		gyro_off[1] = i2c_read(0x45) << 8 | i2c_read(0x46); //read Y registers
		gyro_off[2] = i2c_read(0x47) << 8 | i2c_read(0x48); //read Z registers
		gx_off = gx_off + gyro_off[0]; //add x
		gy_off = gy_off + gyro_off[1]; //add z
		gz_off = gy_off + gyro_off[2]; //add y
	}

	gx_off = gx_off / 1000, gy_off = gy_off / 1000, gz_off = gz_off / 1000; //divide by number of loops (to average)
	printf("Offsets obtained!\n");
}

void gyrosensor::measure()
{
	X = i2c_read(0x43) << 8 | i2c_read(0x44); //Read X registers (gyro)
	Y = i2c_read(0x45) << 8 | i2c_read(0x46); //Read Y registers
	Z = i2c_read(0x47) << 8 | i2c_read(0x48); //Read Z registers      		
	
	
	X = (round(X - gx_off) * 1000.0 / GYRO_SENS ) / 1000.0;
	Y = (round(Y - gy_off) * 1000.0 / GYRO_SENS ) / 1000.0;
	Z = (round(Z - gz_off) * 1000.0 / GYRO_SENS ) / 1000.0;
}
