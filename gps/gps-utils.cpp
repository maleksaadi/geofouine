#include <time.h>
#include <string>

#include <stddef.h>
#include <utils/utils>
#include <iostream>

namespace gps {

 struct timeval gps_time( const std::string & date, const std::string & time_of_day )
  {
   timeval tv;
   struct tm tm;

   std::string t=date+time_of_day;
   for (int i=1;i<=5;i++) t.insert(3*i-1,":");
   
   strptime(t.c_str(),"%d:%m:%y:%H:%M:%S",&tm);

   tv.tv_sec=mktime(&tm);
   size_t i=time_of_day.find('.');
   if (i!=std::string::npos)
    tv.tv_usec=std::stof(time_of_day.substr(i))*1000000;
   else
    tv.tv_usec=0;

   return tv;
  }

 std::string gps_utc_date_s(const struct timeval & tv)
  {
   const size_t buffer_size=50;
   char buffer[buffer_size];

   strftime (buffer,
             buffer_size,
             "%d%m%Y", 
             gmtime(&tv.tv_sec)
             );

   return std::string(buffer);
  }
 

} // namespace gps
