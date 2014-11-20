//============================================================================
// Name        : main.cpp
// Author      : UQAR, Thierry Giroux Veilleux
// Version     :
// Copyright   :
// Description : Read GPS and Wireless information from drivers write it on a file.
// Depends on  : libiw-dev, libgps-dev
//============================================================================

#include <Wifi.hpp>

void gpsScan(); // temporaire

int main(void) {
  gpsScan();
  /*
  Wifi Wifi("wlan0");
  
  while (42)
    Wifi.startScan();
  */
  return 0;
}
