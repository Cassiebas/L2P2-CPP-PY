#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>

#define MPU6050_I2C_ADDR 0x68
#define REG_ACCEL_ZOUT_H 0x3F
#define REG_ACCEL_ZOUT_L 0x40
#define REG_PWR_MGMT_1 0x6B
#define REG_ACCEL_CONFIG 0x1C
#define REG_SMPRT_DIV 0x19
#define REG_CONFIGS 0x1A
#define REG_GYRO_CONFIG 0x1B
#define REG_FIFO_EN 0x23
#define REG_USER_CTRL 0x6A
#define REG_FIFO_COUNT_L 0x72
#define REG_FIFO_COUNT_H 0x73
#define REG_FIFO 0x74
#define REG_WHO_AM_I 0x75


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

#define RAD_T_DEG 57.29577951308 //rad to degrees 180/pi

class Balans {
	public :
	void i2c_write(__u8 reg_address, __u8 val);
	char i2c_read(uint8_t reg_address);
	
