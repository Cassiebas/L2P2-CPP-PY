#include "mpu6050.h"

mpu6050::mpu6050()
{
	file = -1
}

void mpu6050::MPUinit()
{
  	i2c_write(REG_PWR_MGMT_1, 0x01);  //confiugrated for gyro use (X)
	i2c_write(REG_ACCEL_CONFIG, 0x00);  //leave at 2g full scale range
	i2c_write(REG_SMPRT_DIV, 0x01);   //sample rate divider = gyro output rate / (1 + smplrt_div) 
	i2c_write(REG_CONFIGS, 0x00);      //usage of fsync, frame synchronization 
  	i2c_write(REG_GYRO_CONFIG, 0b00011000);
	i2c_write(REG_FIFO_EN, 0x00);     //was 88 temp and accel, try 70 for gyro xyz, 8 for accel. keeps on overflowing.
	i2c_write(REG_USER_CTRL, 0x44);   //driven by i2c master, reset fifo
	
	snprintf(bus_filename, 250, "/dev/i2c-1"); 	//put text into a buffer
	file = open(bus_filename, O_RDWR);		//O_RDWR read write
	
	if (file < 0) {
		/* error */
		exit(1);
	}

	if (ioctl(file, I2C_SLAVE, MPU6050_I2C_ADDR) < 0) { //ioctl(filedescriptor, request, argument) performs controlfunctions on streamdevices
		/* error */
		exit(1);
	}
}

void mpu6050::i2c_write(__u8 reg_address, __u8 val) {
	char buf[2];
	if(file < 0) {
		printf("Error, i2c bus is not available\n");
		exit(1);
	}

	buf[0] = reg_address;
	buf[1] = val;

	if (write(file, buf, 2) != 2) {
		printf("Error, unable to write to i2c device\n");
		exit(1);
	}

}

char mpu6050::i2c_read(uint8_t reg_address) {
	char buf[1];
	if(file < 0) {
		printf("Error, i2c bus is not available\n");
		exit(1);
	}

	buf[0] = reg_address;

	if (write(file, buf, 1) != 1) {
		printf("Error, unable to write to i2c device\n");
		exit(1);
	}


	if (read(file, buf, 1) != 1) {
		printf("Error, unable to read from i2c device\n");
		exit(1);
	}

	return buf[0];
}
