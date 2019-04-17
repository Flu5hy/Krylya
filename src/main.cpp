#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <cmath>

#include "DeviceI2C.h"
#include "NMEAUtil.h"

#include <sstream>
#include <vector>


struct GpsFix {
    long timestamp;
    float lon;
    float lat;
    float alt;
};

void runGps()
{
    std::fstream gpsin;
    gpsin.open("/dev/serial0", std::fstream::in);

    std::string nmeaMessage;
    while(std::getline(gpsin, nmeaMessage))
    {
        if(nmeaMessage.size() >= 5 && nmeaMessage.compare(1, 5, "GPGGA") == 0)
        {
            NMEAUtil::GPGGAWrapper gpgga(nmeaMessage);

            std::cout << nmeaMessage << std::endl;
            std::cout.flush();
            std::cout << gpgga.getTimestamp()  << " : " << gpgga.getLongitude() << ", " << gpgga.getLatitude() << ", " << gpgga.getAltitude() << std::endl;
            usleep(1000000);
        }
    }
}

int16_t convert(uint16_t value)
{
    int16_t result = 0;
    if (value >= 0x8000)
    {
        result = -((65535 - value) + 1);
    }
    else
    {
        result = value;
    }
    return result;
}

void runImu()
{
    DeviceI2C imuDevice("/dev/i2c-1", 0x68);
    while(true) {
        int16_t temperature = convert(imuDevice.read(MPU6050_REG_TEMP));
        int16_t xAcc = convert(imuDevice.read(MPU6050_REG_ACCEL_X));
        int16_t yAcc = convert(imuDevice.read(MPU6050_REG_ACCEL_Y));
        int16_t ZAcc = convert(imuDevice.read(MPU6050_REG_ACCEL_Z));

        float tempDegreeCelsius = ((float)temperature) / 340 + 36.53;
        float xAccPhys = xAcc / 16384.0;
        float yAccPhys = yAcc / 16384.0;
        float zAccPhys = ZAcc / 16384.0;

        std::cout << "IMU Temperature: " << tempDegreeCelsius << std::endl;
        std::cout << "IMU Acc-x: " << xAccPhys << std::endl;
        std::cout << "IMU Acc-y: " << yAccPhys << std::endl;
        std::cout << "IMU Acc-z: " << zAccPhys << std::endl;
        std::cout << "IMU Acc-sum: " << std::sqrt(xAccPhys*xAccPhys + yAccPhys*yAccPhys + zAccPhys*zAccPhys) << std::endl;

        usleep(1000000);
    }
}

int main()
{
    std::thread gpsThread(&runGps);
    std::thread imuThread(&runImu);

    gpsThread.join();
    imuThread.join();
}

