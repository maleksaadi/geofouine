//============================================================================
// Name        : main.cpp
// Author      : UQAR, Thierry Giroux Veilleux,saadi Abdelmalek
// Version     :
// Copyright   :
// Description : Read GPS and Wireless information from drivers write it on a file.
// Depends on  : libiw-dev, libgps-dev
//============================================================================

#include <iostream>
#include <libgpsmm.h>

#include <sys/socket.h>
#include <iwlib.h>
#include <pthread.h>
#include <fstream>
#include <limits>
#include <sstream>

#include "csv-ostream.h"

using namespace std;

typedef std::numeric_limits< double > dbl;
#define wi_result context.result
#define wi_config  context.result->b
#define wi_stats context.result->stats
#define csv_na  csv << "\"" << "N/A" << "\", "
//#define csv_add(x) csv << "\"" << x << "\", "
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
     csv::csv_ostream GPSdataStream(csv);
    GPSdataStream <<
    "time"<<"time_incert"<<"latitude"<<"lat_uncert"<<"longitude"<<"long_uncert"
    <<"altitude"<<"alt_uncert"<<"course"<<"course_uncert"<<"ground_speed"<<"ground_speed_uncert"
    <<"climb_speed"<<"climb_speed_incert"<<endl;
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

               csv.open ("GPSdata.csv",std::ofstream::app);
                csv.precision(dbl::digits10);
                //Time TimeIncert	Latitude LatUncert	Longitude LongUncert	Altitude AltUncert	Course CourseUncert GroundSpeed GroundSpeedUncert	ClimbSpeed	ClimbSpeedIncert

                GPSdataStream<<(newdata->fix.time )<< endl;			/* Time */
                GPSdataStream<<(newdata->fix.ept )<< endl;		/* Expected time uncertainty */
                GPSdataStream<<(newdata->fix.latitude )<< endl;	/* Latitude in degrees (valid if mode >= 2) */
                GPSdataStream<<(newdata->fix.epy )<< endl;  	/* Latitude position uncertainty, meters */
                GPSdataStream<<(newdata->fix.longitude )<< endl;	/* Longitude in degrees (valid if mode >= 2) */
                GPSdataStream<<(newdata->fix.epx )<< endl;  	/* Longitude position uncertainty, meters */
                GPSdataStream<<(newdata->fix.altitude )<< endl;	/* Altitude in meters (valid if mode == 3) */
                GPSdataStream<<(newdata->fix.epv )<< endl;  	/* Vertical position uncertainty, meters */
                GPSdataStream<<(newdata->fix.track )<< endl;	/* Course made good (relative to true north) */
                GPSdataStream<<(newdata->fix.epd )<< endl;		/* Track uncertainty, degrees */
                GPSdataStream<<(newdata->fix.speed )<< endl;	/* Speed over ground, meters/sec */
                GPSdataStream<<(newdata->fix.eps )<< endl;		/* Speed uncertainty, meters/sec */
                GPSdataStream<<(newdata->fix.climb )<< endl;       /* Vertical speed, meters/sec */
                GPSdataStream<<(newdata->fix.epc ) << endl;		/* Vertical speed uncertainty */
                cout << newdata->fix.latitude<<", "<< newdata->fix.longitude<<endl;


                csv.close();


                csv.close();
            }
        }


    }


    pthread_exit(NULL);
}




void* start_WiFi_Scan(void*)
{

    wireless_scan_head context;
    iw_range range;

    //Préparons le fichier csv.
    std::ofstream csv;
    csv.open ("WiFiData.csv",std::ofstream::trunc);

    csv::csv_ostream WifiDataStream(csv);
    WifiDataStream <<
    "time"<<"time_incert"<< "protocol_name"<< "network_id"<<"freq"<< "freq_flags"<<"Encoding_key"<<"key_size"<<"key_flags"<<" essid_on"<< "essid_name"<< "essid_len"<<
    "device_dependant_status"<<"link_quality_qual"<< "link_quality_level"<<"link_quality_noise"<<"link_quality_updated"<<"packet_discard_counts_nwid"<<"packet_discard_counts_code"<<"packet_discard_counts_fragment"<< "packet_discard_counts_retries"<<" packet_discard_counts_misc"<< "packet_missed_counts_beacon"<<endl;
    csv.close();


    csv.open ("WiFiRange.csv",std::ofstream::trunc);
     csv::csv_ostream WifiRangeStream(csv);

    WifiRangeStream <<  "time"<<"time_incert"<<"range_throughput"<< "range_min_nwid"<< "range_max_nwid"<< "range_old_num_channels"<< "range_old_num_frequency"<< "range_sensitivity"
 << "range_avg_quality_qual"<<"range_avg_quality_level"<<"range_avg_quality_noise"<< "range_avg_quality_updated"
 << "range_max_quality_qual"<< "range_max_quality_level"<< "range_max_quality_noise"<< "range_max_quality_updated"
 << "range_num_bitrates"<<"range_list_bitrates"<<"range_min_rts"<<"range_max_rts"<< "range_min_frag"<< "range_max_frag"
 << "range_min_pm_period"<< "range_max_pm_period"<< "range_min_pm_timeout"<< "range_max_pm_timeout"<< "range_pm_period_flags"<<"range_pt_flags"<< "range_pm_capa"
 << "range_encoding_size_ls"<< "renge_num_encoding_size" <<"range_max_encoding_tokens"<< "range_encoding_login_index"
 << "range_transmit_power_capa"<<"range_num_transmit_power"<< "range_transmit_power_ls_bps"
 << "range_retry_limit_cap"<< "range_retry_limit_flags"<< "range_min_retry"<< "range_max_retry" << "range_min_retry_lifetime"<<"range_max_retry_lifetime"
 << "range_num_channels"<< "range_num_frequency"<<"range_freq_list"
 << "range_enc_capa"<<"range_min_pm_saving"<< "range_max_pm_saving"<< "range_pm_saving_flags"<<"range_modul_capa"
 << "range_bitrate_capa";


    csv <<endl;
    csv.close();


    for (;;)
    {




        //2 - scannons les données wifi.
        int skfd;
        skfd = iw_sockets_open();

        char* interface = new char[5];
        strcpy( interface, "wlan0" );
        time_t timestamp;
        time(&timestamp);
        int now = (int)timestamp;
        int retScan = iw_scan(skfd, interface, WIRELESS_EXT, &context);
        int retRange = iw_get_range_info(skfd, interface, &range);
        iw_sockets_close(skfd);

        if (retScan >= 0)
        {
            while (context.result)
            {



                csv.open ("WiFiData.csv",std::ofstream::app);

                csv.precision(dbl::digits10);

                WifiDataStream <<(now   )<< endl;  //time
                WifiDataStream <<(""  )<< endl;  //time_incert
                WifiDataStream <<(wi_config.name   )<< endl;  //protocol_name
                if(wi_config.has_nwid)
                {
                    WifiDataStream <<((int)wi_config.nwid.value )<< endl;  //network_id

                    cout << "network id : " << (int)wi_config.nwid.value << endl;
                }
                else csv_na;

                if(wi_config.has_freq)
                {
                    WifiDataStream <<(wi_config.freq   )<< endl;  //freq
                    WifiDataStream <<(wi_config.freq_flags   )<< endl;  //freq_flags
                }
                else
                {
                    csv_na;
                    csv_na;
                }
                if(wi_config.has_key)
                {
                    WifiDataStream <<(wi_config.key   )<< endl;  //Encoding_key
                    WifiDataStream <<(wi_config.key_size   )<< endl;  //key_size
                    WifiDataStream <<(wi_config.key_flags   )<< endl;  //key_flags
                }
                else
                {
                    csv_na;
                    csv_na;
                    csv_na;
                }
                if(wi_config.has_essid)
                {
                    WifiDataStream <<((wi_config.essid_on?"ON":"OFF")  )<< endl;  //essid_on
                }
                else
                    csv_na;

                if(wi_config.has_essid && wi_config.essid_on)
                {

                    WifiDataStream <<(wi_config.essid   )<< endl;  //essid_name
                    WifiDataStream <<(wi_config.essid_len   )<< endl;  //essid_len

                    cout << "essid : " << wi_config.essid << endl;
                }
                else
                {
                    csv_na;
                    csv_na;
                }

                if(wi_config.has_mode)
                {
                    WifiDataStream <<(wi_config.mode   )<< endl;  //oper_mode,

                }
                else
                {
                    csv_na;
                }


                if(context.result->has_stats)
                {

                    WifiDataStream <<( (int)wi_stats.status  )<< endl;  //device_dependant_status
                    WifiDataStream <<( (int)wi_stats.qual.qual  )<< endl;  //link_quality_qual
                    WifiDataStream <<( (int)wi_stats.qual.level  )<< endl;  //link_quality_level
                    WifiDataStream <<( (int)wi_stats.qual.noise  )<< endl;  //link_quality_noise
                    WifiDataStream <<( (int)wi_stats.qual.updated  )<< endl;  //link_quality_updated
                    WifiDataStream <<( (int)wi_stats.discard.nwid  )<< endl;  //packet_discard_counts_nwid
                    WifiDataStream <<( (int)wi_stats.discard.code  )<< endl;  //packet_discard_counts_code
                    WifiDataStream <<( (int)wi_stats.discard.fragment  )<< endl;  //packet_discard_counts_fragment
                    WifiDataStream <<( (int)wi_stats.discard.retries  )<< endl;  //packet_discard_counts_retries
                    WifiDataStream <<( (int)wi_stats.discard.misc  )<< endl;  //packet_discard_counts_misc
                    csv_add_final( (int)wi_stats.miss.beacon  )<< endl;  //packet_missed_counts_beacon


                         }
                         else
                {
                    csv  << "\"\" , \"\" , \"\" , \"\" , \"\" , \"\" , \"\" , \"\" , \"\" , \"\" , \"\"";  //link_quality_qual

                }
                csv<<endl;
                csv.close();
                context.result = context.result->next;
            }


        }


        if (retRange >= 0)
        {

            csv.open ("WiFiRange.csv",std::ofstream::app);

            WifiRangeStream <<(now   );  //time
            WifiRangeStream  <<(""  );  //time_incert

            WifiRangeStream  <<((int)range.throughput  )<< endl;//range_throughput
            WifiRangeStream  <<((int)range.min_nwid  )<< endl;//range_min_nwid
            WifiRangeStream  <<((int)range.max_nwid  )<< endl;//range_max_nwid
           WifiRangeStream  <<((int)range.old_num_channels  )<< endl;//range_old_num_channels
           WifiRangeStream  <<((int)range.old_num_frequency  )<< endl;//range_old_num_frequency
            WifiRangeStream  <<((int)range.sensitivity  )<< endl;//range_sensitivity,
            WifiRangeStream  <<((int)range.avg_qual.qual  )<< endl;//range_avg_quality_qual
            WifiRangeStream  <<((int)range.avg_qual.level  )<< endl;//range_avg_quality_level
            WifiRangeStream  <<((int)range.avg_qual.noise  )<< endl;//range_avg_quality_noise
            WifiRangeStream  <<((int)range.avg_qual.updated  )<< endl;//range_avg_quality_updated,
            WifiRangeStream  <<((int)range.max_qual.qual  )<< endl;//range_max_quality_qual
            WifiRangeStream  <<((int)range.max_qual.level  )<< endl;//range_max_quality_level
            WifiRangeStream <<((int)range.max_qual.noise  )<< endl;//range_max_quality_noise
            WifiRangeStream  <<((int)range.max_qual.updated  )<< endl;//range_max_quality_updated,
            WifiRangeStream  <<((int)range.num_bitrates  )<< endl;//range_num_bitrates
            WifiRangeStream  <<(convert_intarray_string(range.bitrate ) )<< endl;//range_list_bitrates
            WifiRangeStream  <<((int)range.min_rts  )<< endl;//range_min_rts
            WifiRangeStream <<((int)range.max_rts  )<< endl;//range_max_rts
            WifiRangeStream  <<((int)range.min_frag  )<< endl;//range_min_frag,
            WifiRangeStream  <<((int)range.max_frag  )<< endl;//range_min_frag,
            WifiRangeStream <<((int)range.min_pmp  )<< endl;//range_min_pm_period
            WifiRangeStream  <<((int)range.max_pmp  )<< endl;//range_max_pm_period
            WifiRangeStream  <<((int)range.min_pmt  )<< endl;//range_min_pm_timeout
            WifiRangeStream <<((int)range.max_pmt  )<< endl;//range_max_pm_timeout
            WifiRangeStream  <<((int)range.pmp_flags  )<< endl;//range_pm_period_flags
            WifiRangeStream <<((int)range.pmt_flags  )<< endl;//range_pm_timeout_flags
            WifiRangeStream  <<((int)range.pm_capa  )<< endl;//range_pm_capa
            WifiRangeStream  <<(convert_intarray_string(range.encoding_size)  );//range_encoding_size_ls
            WifiRangeStream  <<((int)range.num_encoding_sizes  )<< endl;//renge_num_encoding_size
            WifiRangeStream  <<((int)range.max_encoding_tokens  )<< endl;//range_max_encoding_tokens
            WifiRangeStream  <<((int)range.encoding_login_index  )<< endl;//range_encoding_login_index,
            WifiRangeStream  <<((int)range.txpower_capa  )<< endl;//range_transmit_power_capa
            WifiRangeStream  <<((int)range.num_txpower  )<< endl;//range_num_transmit_power
           WifiRangeStream  <<(convert_intarray_string(range.txpower)  )<< endl;//range_transmit_power_ls_bps,
            WifiRangeStream  <<((int)range.retry_capa  )<< endl;//range_retry_limit_capa
            WifiRangeStream  <<((int)range.retry_flags  )<< endl;//range_retry_limit_flags
            WifiRangeStream  <<((int)range.min_retry  )<< endl;//range_min_retry
            WifiRangeStream <<((int)range.max_retry  )<< endl;//range_max_retry
            WifiRangeStream  <<((int)range.min_r_time  )<< endl;//range_min_retry_lifetime
            WifiRangeStream  <<((int)range.max_r_time  )<< endl; //range_max_retry_lifetime
            WifiRangeStream  <<((int)range.num_channels  )<< endl;//range_num_channels
            WifiRangeStream  <<((int)range.num_frequency  )<< endl;//range_num_frequency
            WifiRangeStream  <<(convert_freqarray_string(range.freq)  )<< endl;//range_freq_list
            WifiRangeStream <<((int)range.enc_capa  )<< endl;//range_enc_capa
            WifiRangeStream  <<((int)range.min_pms  )<< endl;//range_min_pm_saving
           WifiRangeStream  <<((int)range.max_pms  )<< endl;//range_max_pm_saving
            WifiRangeStream  <<((int)range.pms_flags  )<< endl;//range_pm_saving_flags
            WifiRangeStream  <<((int)range.modul_capa  )<< endl;//range_modul_capa
            WifiRangeStream <<((int)range.bitrate_capa  ) << endl;//range_bitrate_capa
            csv.close();

        }



        //sleep(1);

    }
    pthread_exit(NULL);
}



int main()
{

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
}
