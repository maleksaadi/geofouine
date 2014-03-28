#include <sys/time.h>
#include <stdint.h>
#include <string>
namespace utils
{
 namespace ts
 {

  uint64_t now()
  {
   struct timeval tv;
   gettimeofday(&tv,0);
   return tv.tv_sec*1000000+tv.tv_usec;
  }

  std::string now_s()
  {
   const size_t buffer_size=50;
   char buffer[buffer_size];
   struct timeval tv;
   gettimeofday (&tv, 0);

   strftime (buffer,
             buffer_size,
             "%Y/%m/%d %H:%M:%S", 
             localtime(&tv.tv_sec)
             );

   sprintf (buffer,"%s.%03ld", buffer, tv.tv_usec);
   return std::string(buffer);
  }

 } // namespace ts

} // namespace utils
