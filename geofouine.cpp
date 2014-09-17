//============================================================================
// Name        : main.cpp
// Author      : UQAR, Thierry Giroux Veilleux,Saadi Abdelmalek
// Version     :
// Copyright   :
// Description : Read GPS and Wireless information from drivers write it on a file.
// Depends on  : libiw-dev, libgps-dev
//============================================================================
{
#include <time.h>
#include <iostream>
#include <iomanip>
#include <libgpsmm.h>
#include <sys/socket.h>
#include <iwlib.h>
#include <pthread.h>
#include <fstream>
#include <limits>
#include<sstream>
#include <list>
#include <algorithm>

#include <gps/gps-stream>
#include <gps/gps-stream-decoder>
#include <gps/gps-data>
#include <gps/gps-thread>


using namespace std;

typedef std::numeric_limits< double > dbl;
//des petits raccourcis :
#define wi_result context.result
#define wi_config  context.result->b
#define wi_stats context.result->stats
#define csv_na  csv << "\"" << "N/A" << "\", "
#define csv_add(x) csv << "\"" << x << "\", "
#define csv_add_final(x) csv << "\"" << x << "\""

template <typename T>
string convert_intarray_string ( T numbers[])
{
   int n = sizeof(numbers)/sizeof(numbers[0]);
    stringstream ss;
    for (int i = 0; i <=n; i++)
    {
        ss << (int)numbers[i];
        ss << ";";
    }
    return ss.str();
}



string convert_freqarray_string(iw_freq freq[])
{
int n = sizeof(freq)/sizeof(freq[0]);
    stringstream ss;
    for (int i = 0; i <=n; i++)
    {
        ss << (int)freq[i].m;
        ss << "e";
        ss << (int)freq[i].e;
        ss << ";";
    }
    return ss.str();

}
}
void* start_GPS_Scan(void*)
{
    gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);

    if (gps_rec.stream(WATCH_ENABLE | WATCH_JSON) == NULL)
    {
        cerr << "Démarrez GPSD!!!\n";
        pthread_exit(NULL);
    }
    //Préparons le fichier csv.
    std::ofstream csv;
    csv.open ("GPSdata.csv",std::ofstream::trunc);
    csv <<
    "\"time\",\"time_incert\",\"latitude\",\"lat_uncert\",\"longitude\",\"long_uncert\","<<
    "\"altitude\",\"alt_uncert\",\"course\",\"course_uncert\",\"ground_speed\",\"ground_speed_uncert\",\"climb_speed\",\"climb_speed_incert\""<<endl;
    csv.close();
    for (;;)
    {
        //1 - obtenons la donnée gps.

        struct gps_data_t* newdata;

        if (!gps_rec.waiting(50000000))
            continue;

        if ((newdata = gps_rec.read()) == NULL)
        {
            cerr << "Erreur de lecture.\n";
            pthread_exit(NULL);
        }
        else
        {

            if(newdata->fix.mode>=2)
            {
                csv.open ("GPSdata.csv",std::ofstream::app);
                csv.precision(dbl::digits10);
                //Time TimeIncert	Latitude LatUncert	Longitude LongUncert	Altitude AltUncert	Course CourseUncert GroundSpeed GroundSpeedUncert	ClimbSpeed	ClimbSpeedIncert

                csv_add(newdata->fix.time );			/* Time */
                csv_add(newdata->fix.ept );		/* Expected time uncertainty */
                csv_add(newdata->fix.latitude );	/* Latitude in degrees (valid if mode >= 2) */
                csv_add(newdata->fix.epy );     /* Latitude position uncertainty, meters */
                csv_add(newdata->fix.longitude );	/* Longitude in degrees (valid if mode >= 2) */
                csv_add(newdata->fix.epx );     /* Longitude position uncertainty, meters */
                csv_add(newdata->fix.altitude );	/* Altitude in meters (valid if mode == 3) */
                csv_add(newdata->fix.epv );     /* Vertical position uncertainty, meters */
                csv_add(newdata->fix.track );	/* Course made good (relative to true north) */
                csv_add(newdata->fix.epd );		/* Track uncertainty, degrees */
                csv_add(newdata->fix.speed );	/* Speed over ground, meters/sec */
                csv_add(newdata->fix.eps );		/* Speed uncertainty, meters/sec */
                csv_add(newdata->fix.climb );       /* Vertical speed, meters/sec */
                csv_add_final(newdata->fix.epc ) << endl;		/* Vertical speed uncertainty */
                cout << newdata->fix.latitude<<", "<< newdata->fix.longitude<<endl;


                csv.close();
            }
        }


    }


    pthread_exit(NULL);
}








            public class Wifi
{
    void Wifi 
	{
	    wireless_scan_head context;
    iw_range range;

    //Préparons le fichier csv.
    std::ofstream csv;
    csv.open ("WiFiData.csv",std::ofstream::trunc);
    csv <<
    "\"time\",\"time_incert\", \"protocol_name\", \"network_id\", \"freq\", \"freq_flags\", \"Encoding_key\", \"key_size\", \"key_flags\", \"essid_on\", \"essid_name\", \"essid_len\", \"oper_mode\","<<
    " \"device_dependant_status\", \"link_quality_qual\", \"link_quality_level\", \"link_quality_noise\", \"link_quality_updated\", \"packet_discard_counts_nwid\", \"packet_discard_counts_code\", \"packet_discard_counts_fragment\", \"packet_discard_counts_retries\", \"packet_discard_counts_misc\", \"packet_missed_counts_beacon\""<<endl;
    //csv.close();


    csv.open ("WiFiRange.csv",std::ofstream::trunc);
    csv <<  "\"time\",\"time_incert\",\"range_throughput\", \"range_min_nwid\", \"range_max_nwid\", \"range_old_num_channels\", \"range_old_num_frequency\", \"range_sensitivity\", "
 << "\"range_avg_quality_qual\", \"range_avg_quality_level\", \"range_avg_quality_noise\", \"range_avg_quality_updated\", "
 << "\"range_max_quality_qual\", \"range_max_quality_level\", \"range_max_quality_noise\", \"range_max_quality_updated\", "
 << "\"range_num_bitrates\", \"range_list_bitrates\", \"range_min_rts\", \"range_max_rts\", \"range_min_frag\", \"range_max_frag\", "
 << "\"range_min_pm_period\", \"range_max_pm_period\", \"range_min_pm_timeout\", \"range_max_pm_timeout\", \"range_pm_period_flags\",\"range_pt_flags\", \"range_pm_capa\", "
 << "\"range_encoding_size_ls\", renge_num_encoding_size\", \"range_max_encoding_tokens\", \"range_encoding_login_index\", "
 << "\"range_transmit_power_capa\", \"range_num_transmit_power\", \"range_transmit_power_ls_bps\", "
 << "\"range_retry_limit_capa\", \"range_retry_limit_flags\", \"range_min_retry\", \"range_max_retry\", \"range_min_retry_lifetime\", \"range_max_retry_lifetime\", "
 << "\"range_num_channels\", \"range_num_frequency\", \"range_freq_list\", "
 << "\"range_enc_capa\", \"range_min_pm_saving\", \"range_max_pm_saving\", \"range_pm_saving_flags\", \"range_modul_capa\", "
 << "\"range_bitrate_capa\"";


    csv <<endl;
   // csv.close();

           //2 - scannons les données wifi.
      public int skfd;
        skfd = iw_sockets_open();

        char* interface = new char[5];
        strcpy( interface, "wlan0" );
        time_t timestamp;
        time(&timestamp);
        int now = (int)timestamp;
        int retScan = iw_scan(skfd, interface, WIRELESS_EXT, &context);
        int retRange = iw_get_range_info(skfd, interface, &range);
		//time, time_incert, protocol_name, network_id, freq, freq_flags, Encoding_key, key_size, key_flags, essid_on, essid_name, essid_len, oper_mode,
//device_dependant_status, link_quality_qual, link_quality_level, link_quality_noise, link_quality_updated, packet_discard_counts_nwid, packet_discard_counts_code, packet_discard_counts_fragment, packet_discard_counts_retries, packet_discard_counts_misc, packet_missed_counts_beacon,



                csv.open ("WiFiData.csv",std::ofstream::app);
                csv.precision(dbl::digits10);

                csv_add(now   );  //time
                csv_add(""  );  //time_incert
                csv_add(wi_config.name   );  //protocol_name
				 iw_sockets_close(skfd);
	
	}
}


  public  class wi_config.has_nwid : wifi
   {  
      void Wi_config.has_nwid 
	  {  
	       csv_add((int)wi_config.nwid.value );  //network_id

                    cout << "network id : " << (int)wi_config.nwid.value << endl;
					 csv<<endl;
                csv.close();
                context.result = context.result->next;
	  }
   }
  
   public class wi_config.has_freq : wifi 
	{
	   void Vi_config.has_freq
	    {  
		   
                    csv_add(wi_config.freq   );  //freq
                    csv_add(wi_config.freq_flags   );  //freq_flags
					 csv<<endl;
                csv.close();
                context.result = context.result->next;
		}
	}
	
	public class wi_config.has_key : wifi 
	{
	    void Wi_config.has_key 
		{
		    csv_add(wi_config.key   );  //Encoding_key
                    csv_add(wi_config.key_size   );  //key_size
                    csv_add(wi_config.key_flags   );  //key_flags
					 csv<<endl;
                csv.close();
                context.result = context.result->next;
		}
	}
  
         public  class wi_config.has_essid : wifi
		  {
		         void Wi_config.has_essid 
				 {
				       csv_add((wi_config.essid_on?"ON":"OFF")  );  //essid_on
					    csv<<endl;
                csv.close();
                context.result = context.result->next;
				 }
		  }
		  
		 public class wi_config.has_essid && wi_config.essid_on: wifi 
                {
                          void Wi_config.has_essid && wi_config.essid_on 
						  {
                    csv_add(wi_config.essid   );  //essid_name
                    csv_add(wi_config.essid_len   );  //essid_len

                    cout << "essid : " << wi_config.essid << endl;
					 csv<<endl;
                csv.close();
                context.result = context.result->next;
					       }
                }
				
				
				public class  wi_config.has_mode : wifi 
				{
                             void Wi_config.has_mode
                {
                    csv_add(wi_config.mode   );  //oper_mode,{
                
				csv_add(wi_config.mode   );  //oper_mode,
				 csv<<endl;
                csv.close();
                context.result = context.result->next;
				}
				}
    
	
	     public class (context.result->has_stats) : wifi {
                
				void Context.result->has_stats
				{

                    csv_add( (int)wi_stats.status  );  //device_dependant_status
                    csv_add( (int)wi_stats.qual.qual  );  //link_quality_qual
                    csv_add( (int)wi_stats.qual.level  );  //link_quality_level
                    csv_add( (int)wi_stats.qual.noise  );  //link_quality_noise
                    csv_add( (int)wi_stats.qual.updated  );  //link_quality_updated
                    csv_add( (int)wi_stats.discard.nwid  );  //packet_discard_counts_nwid
                    csv_add( (int)wi_stats.discard.code  );  //packet_discard_counts_code
                    csv_add( (int)wi_stats.discard.fragment  );  //packet_discard_counts_fragment
                    csv_add( (int)wi_stats.discard.retries  );  //packet_discard_counts_retries
                    csv_add( (int)wi_stats.discard.misc  );  //packet_discard_counts_misc
                    csv_add_final( (int)wi_stats.miss.beacon  );  //packet_missed_counts_beacon


                         }}
	
	  public  class retRange : wifi
        {
		
		    void RetRange {

            csv.open ("WiFiRange.csv",std::ofstream::app);

            csv_add(now   );  //time
            csv_add(""  );  //time_incert

            csv_add((int)range.throughput  );//range_throughput
            csv_add((int)range.min_nwid  );//range_min_nwid
            csv_add((int)range.max_nwid  );//range_max_nwid
            csv_add((int)range.old_num_channels  );//range_old_num_channels
            csv_add((int)range.old_num_frequency  );//range_old_num_frequency
            csv_add((int)range.sensitivity  );//range_sensitivity,
            csv_add((int)range.avg_qual.qual  );//range_avg_quality_qual
            csv_add((int)range.avg_qual.level  );//range_avg_quality_level
            csv_add((int)range.avg_qual.noise  );//range_avg_quality_noise
            csv_add((int)range.avg_qual.updated  );//range_avg_quality_updated,
            csv_add((int)range.max_qual.qual  );//range_max_quality_qual
            csv_add((int)range.max_qual.level  );//range_max_quality_level
            csv_add((int)range.max_qual.noise  );//range_max_quality_noise
            csv_add((int)range.max_qual.updated  );//range_max_quality_updated,
            csv_add((int)range.num_bitrates  );//range_num_bitrates
            csv_add(convert_intarray_string(range.bitrate ) );//range_list_bitrates
            csv_add((int)range.min_rts  );//range_min_rts
            csv_add((int)range.max_rts  );//range_max_rts
            csv_add((int)range.min_frag  );//range_min_frag,
            csv_add((int)range.max_frag  );//range_min_frag,
            csv_add((int)range.min_pmp  );//range_min_pm_period
            csv_add((int)range.max_pmp  );//range_max_pm_period
            csv_add((int)range.min_pmt  );//range_min_pm_timeout
            csv_add((int)range.max_pmt  );//range_max_pm_timeout
            csv_add((int)range.pmp_flags  );//range_pm_period_flags
            csv_add((int)range.pmt_flags  );//range_pm_timeout_flags
            csv_add((int)range.pm_capa  );//range_pm_capa
            csv_add(convert_intarray_string(range.encoding_size)  );//range_encoding_size_ls
            csv_add((int)range.num_encoding_sizes  );//renge_num_encoding_size
            csv_add((int)range.max_encoding_tokens  );//range_max_encoding_tokens
            csv_add((int)range.encoding_login_index  );//range_encoding_login_index,
            csv_add((int)range.txpower_capa  );//range_transmit_power_capa
            csv_add((int)range.num_txpower  );//range_num_transmit_power
            csv_add(convert_intarray_string(range.txpower)  );//range_transmit_power_ls_bps,
            csv_add((int)range.retry_capa  );//range_retry_limit_capa
            csv_add((int)range.retry_flags  );//range_retry_limit_flags
            csv_add((int)range.min_retry  );//range_min_retry
            csv_add((int)range.max_retry  );//range_max_retry
            csv_add((int)range.min_r_time  );//range_min_retry_lifetime
            csv_add((int)range.max_r_time  ); //range_max_retry_lifetime
            csv_add((int)range.num_channels  );//range_num_channels
            csv_add((int)range.num_frequency  );//range_num_frequency
            csv_add(convert_freqarray_string(range.freq)  );//range_freq_list
            csv_add((int)range.enc_capa  );//range_enc_capa
            csv_add((int)range.min_pms  );//range_min_pm_saving
            csv_add((int)range.max_pms  );//range_max_pm_saving
            csv_add((int)range.pms_flags  );//range_pm_saving_flags
            csv_add((int)range.modul_capa  );//range_modul_capa
            csv_add_final((int)range.bitrate_capa  ) << endl;//range_bitrate_capa
            csv.close();
        }
		}
	
}}



int main()
{
 //gps_worker * this_worker = new gps_worker(std::cout);

 //this_worker->run();
  gps::gps_stream * this_gps_stream = new gps::gps_stream("/dev/ttyACM0");

  this_gps_stream->set_update_rate(gps::gps_stream::update_250ms);
  while (true)
   {
    string t= this_gps_stream->read();
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
       << " speed=" << t->speed
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
       << " satellites= [";
       for (int s : t->satellites)
        std::cout << " " << s;
       std::cout << " ]" << std::endl;
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
       << "\t [";
      for(auto x : t->satellites)
       std::cout 
        << " [" << x.prn 
        << "," << x.elevation 
        << "," << x.azimuth 
        << "," << x.snr 
        << "]";
      std::cout << " ]" << std::endl;
      
     }

    delete data;
   }

  delete this_gps_stream;

  return 0;
  
  
  for (;;)
    {





       

        if (retScan >= 0)
        {
            while (context.result)
            {




                if(wi_config.has_nwid)
                {
                     Wi_config.has_nwid ();
					 
                }
                else csv_na;

                if(wi_config.has_freq)
                {
                    Wi_config.has_freq ();
                }
                else
                {
                    csv_na;
                    csv_na;
                }
                if(wi_config.has_key)
                {
                    Wi_config.has_key();
                }
                else
                {
                    csv_na;
                    csv_na;
                    csv_na;
                }
                if(wi_config.has_essid)
                {
                   Wi_config.has_essid ();
                }
                else
                    csv_na;

                if(wi_config.has_essid && wi_config.essid_on)
                {

                   Wi_config.has_essid && wi_config.essid_on ();
                }
                else
                {
                    csv_na;
                    csv_na;
                }

                if(wi_config.has_mode)
                {
                  
                       Wi_config.has_mode
                }
                else
                {
                    csv_na;
                }


                if(context.result->has_stats)
                {

                    Context.result->has_stats ();

                         }
                         else
                {
                    csv  << "\"\" , \"\" , \"\" , \"\" , \"\" , \"\" , \"\" , \"\" , \"\" , \"\" , \"\"";  //link_quality_qual

                }
               
            }


        }


        if (retRange >= 0)
        {

          RetRange();
        }



      

    }
    pthread_exit(NULL);
  
  
  
  
  
  
  
  
 /*
    pthread_t thread_GPS;
    pthread_t thread_WiFi;
    pthread_attr_t attribut;
    void *etat;
    pthread_attr_init(&attribut);
    pthread_attr_setdetachstate(&attribut, PTHREAD_CREATE_JOINABLE);


    pthread_create(&thread_GPS, NULL, start_GPS_Scan, NULL);
    pthread_create(&thread_WiFi, NULL, start_WiFi_Scan, NULL);

    pthread_attr_destroy(&attribut);

    pthread_join(thread_GPS, &etat);
    pthread_join(thread_WiFi, &etat);

    pthread_exit(NULL);
*/
}
