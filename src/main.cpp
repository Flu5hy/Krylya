#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::fstream gpsin;
    gpsin.open("/dev/serial0", std::fstream::in);

    std::string nmeaMessage;
    while(std::getline(gpsin, nmeaMessage))
    {
        std::cout << nmeaMessage << std::endl;
    }
}
