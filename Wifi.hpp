#ifndef _WIFI_H_
#define _WIFI_H_

#include <iwlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

class Wifi {
  int _skfd;
  iwrange _range;
  std::time_t _time;
  std::string _interface;
  wireless_scan *_result;
  wireless_scan_head _context;
  
public:
  Wifi(std::string);
  int startScan();

private:
  std::string getSSID();
  std::string getMAC();
  int hasWifiProtected();
};

#endif /* _WIFI_H_*/
