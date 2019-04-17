
#include <string>
#include <vector>

namespace NMEAUtil {

class GPGGAWrapper
{
public:
   GPGGAWrapper(std::string& gpggaMessage);
   
   double getLongitude() const;
   double getLatitude() const;
   double getAltitude() const;
   long getTimestamp() const;
   
private:
   std::vector<std::string> m_tokens;
};


}
