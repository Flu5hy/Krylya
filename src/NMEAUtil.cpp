
#include "NMEAUtil.h"

#include <sstream>


static std::vector<std::string> split(const std::string &s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> elems;
  while (std::getline(ss, item, delim)) {
    elems.push_back(std::move(item));
  }
  return elems;
}


namespace NMEAUtil {
   
   
#define GPGGA_TOKEN_TIMESTAMP                   1
#define GPGGA_TOKEN_LONGITUDE                   2
#define GPGGA_TOKEN_LONGITUDE_ALIGNMENT         3
#define GPGGA_TOKEN_LATITUDE                    4
#define GPGGA_TOKEN_LATITUDE_ALIGNMENT          5
#define GPGGA_TOKEN_GPS_QUALITY                 6
#define GPGGA_TOKEN_SATELLITE_COUNT             7
#define GPGGA_TOKEN_HORIZONTAL_DOP              8
#define GPGGA_TOKEN_ANTENNA_HEIGHT_MSL          9
#define GPGGA_TOKEN_ANTENNA_HEIGHT_UNIT        10
#define GPGGA_TOKEN_DGPS_AGE                   11
#define GPGGA_TOKEN_DGPS_REFERENCE_STATION     12
#define GPGGA_TOKEN_CHECKSUM                   13

GPGGAWrapper::GPGGAWrapper(std::string& gpggaMessage)
{
   m_tokens = split(gpggaMessage, ',');
}

double GPGGAWrapper::getLongitude() const
{
   const auto& token = m_tokens[GPGGA_TOKEN_LONGITUDE];
         
   if(token.size() < 2) {
      return 0.0;
   }
   
   return stod(token.substr(0,2)) + stod(token.substr(2,token.size()-2)) / 60;
}

double GPGGAWrapper::getLatitude() const
{
   const auto& token = m_tokens[GPGGA_TOKEN_LATITUDE];
   
   if(token.size() < 3) {
      return 0.0;
   }
      
   auto days = token.substr(0,3);
   auto minutes = token.substr(3,token.size()-3);
   
   return stod(days) + stod(minutes) / 60;
}

double GPGGAWrapper::getAltitude() const
{
   const auto& token = m_tokens[GPGGA_TOKEN_ANTENNA_HEIGHT_MSL];
      
   if(token.size() < 1) {
      return 0.0;
   }
   
   return stod(token);
}

long GPGGAWrapper::getTimestamp() const
{
   const auto& token = m_tokens[GPGGA_TOKEN_TIMESTAMP];
   
   if(token.size() < 6) {
      return 0;
   }
   
   return stoi(token.substr(0,2)) * 60 * 24 + stoi(token.substr(2,2)) * 60 + stoi(token.substr(4,2));
}
   
   
}
