#!/usr/bin/python
import smbus
import math
 
# Register
power_mgmt_1 = 0x6b
power_mgmt_2 = 0x6c
 
def read_byte(reg):
    return bus.read_byte_data(address, reg)
 
def read_word(reg):
    h = bus.read_byte_data(address, reg)
    l = bus.read_byte_data(address, reg+1)
    value = (h << 8) + l
    return value
 
def read_word_2c(reg):
    val = read_word(reg)
    if (val >= 0x8000):
        return -((65535 - val) + 1)
    else:
        return val
 
def dist(a,b):
    return math.sqrt((a*a)+(b*b))
 
def get_y_rotation(x,y,z):
    radians = math.atan2(x, dist(y,z))
    return -math.degrees(radians)
 
def get_x_rotation(x,y,z):
    radians = math.atan2(y, dist(x,z))
    return math.degrees(radians)
 
bus = smbus.SMBus(1) # bus = smbus.SMBus(0) fuer Revision 1
address = 0x68       # via i2cdetect
 
# Aktivieren, um das Modul ansprechen zu koennen
bus.write_byte_data(address, power_mgmt_1, 0)
 
print ("Gyro")
print ("--------")
 
gyroskop_xout = read_word_2c(0x43)
gyroskop_yout = read_word_2c(0x45)
gyroskop_zout = read_word_2c(0x47)
 
print ("gyro_xout: ", ("%5d" % gyroskop_xout), " accelerates: ", (gyroskop_xout / 131))
print ("gyro_yout: ", ("%5d" % gyroskop_yout), " accelerates: ", (gyroskop_yout / 131))
print ("gyro_zout: ", ("%5d" % gyroskop_zout), " accelerates: ", (gyroskop_zout / 131))
 
print
print ("Speedsensor")
print ("---------------------")
 
accel_xout = read_word_2c(0x3b)
accel_yout = read_word_2c(0x3d)
accel_zout = read_word_2c(0x3f)
 
accel_xout_speed = accel_xout / 16384.0
accel_yout_speed = accel_yout / 16384.0
accel_zout_speed = accel_zout / 16384.0
 
print ("speed_xout: ", ("%6d" % accel_xout), " accelerates: ", accel_xout_speed)
print ("speed_yout: ", ("%6d" % accel_yout), " accelerates: ", accel_yout_speed)
print ("speed_zout: ", ("%6d" % accel_zout), " accelerates: ", accel_zout_speed)
 
print ("X Rotation: " , get_x_rotation(accel_xout_speed, accel_yout_speed, accel_zout_speed))
print ("Y Rotation: " , get_y_rotation(accel_xout_speed, accel_yout_speed, accel_zout_speed))