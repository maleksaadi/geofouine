#include <sys/time.h>
#include <stdint.h>
#include <string>

#include <utils/utils>

namespace utils {
  namespace ts {

    // in UTC
    struct timeval now() {
      struct timeval tv;
      
      gettimeofday(&tv,0);
      return tv;
    }
    
  } // namespace ts
  
  namespace time {
    std::string time_s(const struct timeval & tv) {
      const size_t buffer_size = 50;
      char buffer[buffer_size];
      
      strftime (buffer,
		buffer_size,
		"%Y/%m/%d %H:%M:%S", 
		localtime(&tv.tv_sec));

      // danger! works accidentally
      // because the first part of
      // the string remains the same!
      sprintf (buffer,"%s.%06ld", buffer, tv.tv_usec);
      return std::string(buffer);
    }

    std::string utc_time_s(const struct timeval & tv) {
      const size_t buffer_size = 50;
      char buffer[buffer_size];
      
      strftime (buffer,
		buffer_size,
		"%Y/%m/%d %H:%M:%S", 
		gmtime(&tv.tv_sec));
      
      // danger! works accidentally
      // because the first part of
      // the string remains the same!
      sprintf (buffer,"%s.%06ld", buffer, tv.tv_usec);
      return std::string(buffer);
    }
    
    std::string utc_date_s(const struct timeval & tv) {
      return utc_time_s(tv).substr(0,8);
    }
  } // namespace time
  
} // namespace utils
