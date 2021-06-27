#include "accelerometer.h"
#include "gyrosensor.h"
#include "mpu6050.h"


int main(int argc, char *argv[]) {
	printf("balans\n");
	
	//char accel_x_h,accel_x_l,accel_y_h,accel_y_l,accel_z_h,accel_z_l;
	//uint16_t fifo_len = 0;
	
	mpu6050 mpu1;
	mpu1.MPUinit();
	
	accelerometer accel;
	
	while(1)
	{
		accel.measure();
		accel.checktresholds();
	}
	
 	//printf("Entering getoffsets()\n");
  	//gyro.getOffsets();
  

	/*while(fifo_len != 1024) { //fifo keeps overflowing for no reason?
		accel_x_h = i2c_read(REG_FIFO_COUNT_L);
		accel_x_l = i2c_read(REG_FIFO_COUNT_H);
		fifo_len = merge_bytes(accel_x_h,accel_x_l);
		if(fifo_len == 1024) {
			printf("fifo overflow !\n");
			i2c_write(REG_USER_CTRL, 0x44);
			continue;
		
      		accel_x_h = i2c_read(REG_FIFO);
		accel_x_l = i2c_read(REG_FIFO);
		accel_y_h = i2c_read(REG_FIFO);
		accel_y_l = i2c_read(REG_FIFO);
		accel_z_h = i2c_read(REG_FIFO);
		accel_z_l = i2c_read(REG_FIFO);
		}
      */
	

return 0;
}
