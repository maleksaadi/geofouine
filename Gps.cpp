#include <gps/gps-stream>
#include <gps/gps-stream-decoder>
#include <gps/gps-data>
#include <gps/gps-thread>

void gpsScan() {
  gps_worker * this_worker = new gps_worker(std::cout);
  
  this_worker->run();
  
  gps::gps_stream * this_gps_stream = new gps::gps_stream("/dev/ttyUSB0");

  this_gps_stream->set_update_rate(gps::gps_stream::update_250ms);

  while (true) {
    std::string t= this_gps_stream->read();
    std::cout
    << utils::time::time_s(utils::ts::now())
    << "\t"
    << utils::time::utc_time_s(utils::ts::now())
    << "\t"
    << t
    << std::endl;

    gps::gps_data * data = gps::gps_stream_decoder::decode(t);

    std::cout << typeid(*data).name() << std::endl;

    if (typeid(*data)==typeid(gps::gps_data_position))
     {
      gps::gps_data_position * t=(gps::gps_data_position*)data;
      std::cout
      << "{" << utils::time::time_s(t->when) << "} "
      << "RMC "
      << t->latitude.first << ' '
      << t->latitude.second
      << ","
      << t->longitude.first << ' '
      << t->longitude.second
      << std::endl;
     }
    if (typeid(*data)==typeid(gps::gps_data_overall_satellite_info))
     {
      gps::gps_data_overall_satellite_info * t
       = (gps::gps_data_overall_satellite_info*)data;


      std::cout
      << "{" << utils::time::time_s(t->when) << "} "
      << "GSA "
      << (t->automatic_selection ? "A":"M")
      << "dop=" << t->dilution_of_precision
      << " hdop=" << t->horizontal_dilution_of_precision
      << " vdop=" << t->vertical_dilution_of_precision
      << " satellites=";
       for (int s : t->satellites)
       std::cout << " " << s;
       std::cout << std::endl;
     }

    if (typeid(*data)==typeid(gps::gps_data_fix))
     {
      gps::gps_data_fix * t= (gps::gps_data_fix*)data;
      std::cout
      << "{ " << utils::time::time_s(t->when) << "} "
      << "GGA "
      << t->latitude.first << ' '
      << t->latitude.second
      << ","
      << t->longitude.first << ' '
      << t->longitude.second
      << " fix Q=" << t->fix_quality
      << " nb sat=" << t->nb_satellites_tracked
      << " hdop=" << t->horizontal_dilution_of_precision
      << " alt=" << t->altitude
      << " geo=" << t->geoid_altitude
      << std::endl;
     }

    if (typeid(*data)==typeid(gps::gps_data_satellites))
     {
      gps::gps_data_satellites *t=(gps::gps_data_satellites*)data;
      std::cout
      << "{ " << utils::time::time_s(t->when) << "} "
      << "GSV "
      << t->part_nb << "/" << t->nb_parts
      << " nb=" << t->nb_satellites
      << "\t";
      for(auto x : t->satellites)
       std::cout
       << " [" << x.prn
       << "," << x.elevation
       << "," << x.azimuth
       << "," << x.snr
       << "]";
       std::cout << std::endl;

     }

    delete data;
   }

  delete this_gps_stream;
}
