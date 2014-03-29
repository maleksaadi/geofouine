#include <time.h>
#include <string>

#include <stddef.h>
#include <iostream>

namespace gps {

 struct timeval gps_time( const std::string & date, const std::string & time_of_day )
  {
   timeval tv;
   struct tm tm;
   //std::cout << date+timeofday << std::endl;
   std::string t=date+time_of_day;
   for (int i=1;i<=5;i++) t.insert(3*i-1,":");
   std::cout << "t=" << t << std::endl;
   
   strptime(t.c_str(),"%d:%m:%y:%H:%M:%S",&tm);

   tv.tv_sec=mktime(&tm);
   size_t i=time_of_day.find('.');
   if (i!=std::string::npos)
    tv.tv_usec=std::stof(time_of_day.substr(i))*1000;
   else
    tv.tv_usec=0;
   return tv;
  }

} // namespace gps
