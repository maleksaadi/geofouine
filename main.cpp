//============================================================================
// Name        : main.cpp
// Author      : UQAR, Thierry Giroux Veilleux
// Version     :
// Copyright   :
// Description : Read GPS and Wireless information from drivers write it on a file.
// Depends on  : libiw-dev, libgps-dev
//============================================================================

#include <Wifi.hpp>

int main(void) {
  Wifi Wifi("wlan0");
  
  while (42)
    Wifi.startScan();
  return 0;
}
