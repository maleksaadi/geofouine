#include <Wifi.hpp>

Wifi::Wifi(std::string interface) : _interface(interface) {
}

int Wifi::startScan() {
  char *interface = new char[20];

  strcpy(interface, _interface.c_str());
  if ((_skfd = iw_sockets_open()) < 0) {
    std::cout << "iw_socket_open FAILED" << std::endl;
    exit(2);
  }
  if (iw_get_range_info(_skfd, interface, &_range) < 0) {
    std::cout << "iw_get_range_info FAILED" << std::endl;
    exit(2);
  }
  if (iw_scan(_skfd, interface, _range.we_version_compiled, &_context) < 0) {
    std::cout << "iw_scan FAILED" << std::endl;
    exit(2);
  }
  _result = _context.result;
  _time = std::time(nullptr);
  std::localtime(&_time);
  while (_result != NULL) {
    std::cout << "SSID      : " << getSSID() << std::endl
	      << "MAC       : " << getMAC() << std::endl
	      << "QUALITE   : " << static_cast<int>(_result->stats.qual.qual) << std::endl
	      << "LEVEL     : " << static_cast<int>(_result->stats.qual.level) << std::endl
	      << "FREQUENCE : " << _result->b.freq << std::endl
	      << "CHANNEL   : " << iw_freq_to_channel(_result->b.freq, &_range) << std::endl
	      << "BIT RATE  : " << _result->maxbitrate.value << std::endl
	      << "Protected : " << hasWifiProtected() << std::endl
	      << "Time      : " << _time << std::endl
	      << std::endl;
    _result = _result->next;
  }
  iw_sockets_close(_skfd);
  return (0);
}

std::string Wifi::getSSID() {
  if (_result->b.essid_on)
    return (_result->b.essid);
  else
    return ("off/any/hidden");
}

std::string Wifi::getMAC() {
  std::string mac;
  std::stringstream tmp;
  char *buffer = new char[20];

  sprintf(buffer, "%02X:%02X:%02X:%02X:%02X:%02X",
	  _result->ap_addr.sa_data[0], _result->ap_addr.sa_data[1],
	  _result->ap_addr.sa_data[2], _result->ap_addr.sa_data[3],
	  _result->ap_addr.sa_data[4], _result->ap_addr.sa_data[5]);
  tmp << buffer;
  tmp >> mac;
  return (mac);
}

int Wifi::hasWifiProtected() {
  if(_result->maxbitrate.flags & IW_ENCODE_DISABLED)
    return (0);
  else
    return (1);
}
