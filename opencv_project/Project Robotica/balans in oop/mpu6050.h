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

#ifndef MPU6050_H
#define MPU6050_H

class mpu6050 {
	public :
	void i2c_write(__u8 reg_address, __u8 val);
	char i2c_read(uint8_t reg_address);
	char bus_filename[250];
	int file;
	
	private :
	void MPUinit();
};

#endif
