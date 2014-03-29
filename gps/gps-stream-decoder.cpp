#include <string>
#include <gps/gps-data>
#include <gps/gps-stream-decoder>


gps::gps_data * gps_stream_decoder::decode(const std::string & gps_sentence)
{
  std::string type=gps_sentence.substr(1,5);

  if (type=="GPRMC")
   return new gps::gps_data_position(gps_sentence);
  else
   if (type=="GPGGA")
    return new gps::gps_data_fix(gps_sentence);
   else
    if (type=="GPGSV")
     return new gps::gps_data_satellites(gps_sentence);
    else
     return new gps::gps_data_unsupported(gps_sentence);

  return 0;
}
