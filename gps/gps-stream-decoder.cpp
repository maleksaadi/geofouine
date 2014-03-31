#include <string>
#include <gps/gps-data>
#include <gps/gps-stream-decoder>

namespace gps {

gps::gps_data * gps_stream_decoder::decode(const std::string & gps_sentence)
{
  std::string type=gps_sentence.substr(1,5);

  try
   {
    if (type=="GPRMC")
     return new gps::gps_data_position(gps_sentence);
    else
     if (type=="GPGGA")
      return new gps::gps_data_fix(gps_sentence);
     else
      if (type=="GPGSA")
       return new gps::gps_data_overall_satellite_info(gps_sentence);
      else
       if (type=="GPGSV")
        return new gps::gps_data_satellites(gps_sentence);
       else
        return new gps::gps_data_unsupported(gps_sentence);
   }
  catch (...) { return new gps::gps_data_error(gps_sentence); }
  return 0;
}

} // namespace gps
