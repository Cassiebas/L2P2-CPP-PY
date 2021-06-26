#include "accelerometer.h"

accelerometer::accelerometer()
{
	flag = 1;
}


int16_t accelerometer::two_complement_to_int( uint16_t word) {
	signed_int = 0;

	if((word & 0x8000) == 0x8000) { // negative number
		signed_int = (int16_t) -(~word);
	} else {
		signed_int = (int16_t) (word & 0x7fff);
	}

	return signed_int;
}

void accelerometer::getfirst()
{
	if(flag)
		{
			flag = 0;
			firstmeasurex = _accel_angle[0];
			firstmeasurey = _accel_angle[1];
		}
}

void accelerometer::bringtodeg()
{
		_accel_angle[0] = atan2(AZ, AY) * RAD_T_DEG - 90.0;
		_accel_angle[1] = atan2(AZ, AX) * RAD_T_DEG - 90.0;
}

void accelerometer::checktresholds()
{
	if(_accel_angle[0] > firstmeasurex + 30)
		{
		  printf("verder dan begin x\n");
		}
		if (_accel_angle[1] > firstmeasurey + 30)
		{
		  printf("verder dan begin y\n");
		}
		if (_accel_angle[1] < firstmeasurey - 30)
		{
		  printf("negatief verder dan begin y\n");
		}
		if(_accel_angle[0] < firstmeasurex - 30)
		{
		  printf("negatief ver dan begin x\n");
		}
		
		printf("\r");
	}

void accelerometer::measure()
{
      //ask for the registers over i2c instead. bitshifting high to left by 8 spots, ORing lowers
		AX = i2c_read(0x3B) << 8 | i2c_read(0x3C); //Read X registers (accelerometer)
		AY = i2c_read(0x3D) << 8 | i2c_read(0x3E); //Read Y registers
		AZ = i2c_read(0x3F) << 8 | i2c_read(0x40); //Read Z registers
      

		AX = two_complement_to_int(AX); //complement because the datasheet says so
		AY = two_complement_to_int(AY);
		AZ = two_complement_to_int(AZ);
	
		printf("curr Y = %.3f  --  ", _accel_angle[1]);
		printf("curr X = %.3f", _accel_angle[0]);
}
