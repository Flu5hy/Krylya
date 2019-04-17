#include "DeviceI2C.h"

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

static uint8_t readByte(int handle, uint8_t reg)
{
	uint8_t result = 0;

	if (::write(handle, &reg, 1) != 1)
	{
		std::cout << "Failed to write to the i2c bus." << std::endl;
	}

	if (::read(handle, &result, 1) != 1)
	{
		std::cout << "Failed to read from the i2c bus." << std::endl;
	}

	return result;
}

DeviceI2C::DeviceI2C(std::string file, int addr)
{
	if ((m_handle = open(file.c_str(), O_RDWR)) < 0)
	{
		std::cout << "Failed to open the i2c bus" << std::endl;
		return;
	}
	
	if (ioctl(m_handle, I2C_SLAVE, addr) < 0)
	{
		std::cout << "Failed to acquire bus access and/or talk to slave." << std::endl;
		return;
	}
}

DeviceI2C::~DeviceI2C()
{
	if(close(m_handle) < 0)
	{
		std::cout << "Failed to close the i2c bus" << std::endl;
	}
}

uint16_t DeviceI2C::read(uint8_t reg)
{
	uint8_t result_l, result_h;
	
	result_h = readByte(m_handle, reg);
	result_l = readByte(m_handle, reg++);
	
	return (uint16_t) result_l | (uint16_t) (result_h << 8);
}
