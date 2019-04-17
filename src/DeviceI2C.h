#pragma once

#include <string>

#define MPU6050_REG_ACCEL_X 0x3b
#define MPU6050_REG_ACCEL_Y 0x3d
#define MPU6050_REG_ACCEL_Z 0x3f

#define MPU6050_REG_GYRO_X 	0x43
#define MPU6050_REG_GYRO_Y 	0x45
#define MPU6050_REG_GYRO_Z 	0x47

#define MPU6050_REG_TEMP 	0x41


class DeviceI2C
{
public:
	DeviceI2C(std::string file, int addr);
	virtual ~DeviceI2C();
	
	uint16_t read(uint8_t reg);

private:
	int m_handle;
};
