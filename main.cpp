//============================================================================
// Name        : main.cpp
// Author      : UQAR, Thierry Giroux Veilleux
// Version     :
// Copyright   :
// Description : Read GPS and Wireless information from drivers write it on a file.
//============================================================================

#include <iostream>
#include <libgpsmm.h>
#include <sys/socket.h>
#include <iwlib.h>

using namespace std;

int main() {

	gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);

	if (gps_rec.stream(WATCH_ENABLE | WATCH_JSON) == NULL) {
		cerr << "Démarrez GPSD!!!\n";
		return 1;
	}

	wireless_scan_head context;

	for (;;) {

		//1 - obtenons la donnée gps.

		struct gps_data_t* newdata;

		if (!gps_rec.waiting(50000000))
			continue;

		if ((newdata = gps_rec.read()) == NULL) {
			cerr << "Erreur de lecture.\n";
			return 1;
		} else {
			cout << newdata->fix.time << " :";
			cout << newdata->fix.latitude << ", ";
			cout << newdata->fix.longitude << ", ";
			cout << newdata->fix.altitude << "M. " << endl;
		}

		//2 - scannons les données wifi.
		int skfd;
		skfd = iw_sockets_open();

		char* interface = "eth1";
		int ret = iw_scan(skfd, interface, WIRELESS_EXT, &context);

		cout << ret;
		if (ret >= 0) {
			while (context.result) {
				if (context.result->b.has_essid && context.result->b.essid_on)
					cout << "ESSID : " << context.result->b.essid << endl;
				cout << "Entryption : "
						<< (context.result->b.has_key ? "on" : "off") << endl;

				context.result = context.result->next;
			}

		}
		iw_sockets_close(skfd);
		sleep(1);

	}

	return 0;
}
