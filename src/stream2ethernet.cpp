#include "dvs2udp.hpp"
#include <string>
#include <iostream>


int main(int argc, char *argv[]) {
	const char* filename = "None"; 
	std::string command = "Nonset";
	uint32_t interval;
	uint32_t buffer_size = 512;
	const char* port = "3333";	// Port number
	const char* IPAdress = NULL;	// IP Adress - if NULL, use own IP.

	int nr_packets = 0;
	uint32_t max_packets;
	int id = 1;
	int exitcode, sockfd;

    if (argc < 3) {
        fprintf(stderr,"usage: ./stream2ethernet <max_packet_size> <nr_packets_2_send> (Optional: <usb id> <port> <IP Adress>)\n");
        exit(1);
    }
	else if (argc == 4)
	{
		id = stoi(argv[3]);
	}
	else if (argc == 5)
	{
		id = stoi(argv[3]);
		port = argv[4];
	}
	else if (argc == 6)
	{
		id = stoi(argv[3]);
		port = argv[4];
		IPAdress = argv[5];
	}
	else if (argc == 7){
		id = stoi(argv[3]);
		port = argv[4];
		IPAdress = argv[5];
		filename = argv[6];
	}

	interval = strtol(argv[1], NULL, 0);
	max_packets = strtol(argv[2], NULL, 0);

	DVSStream dvsstream(interval, buffer_size, port, IPAdress, NULL, filename); 

	auto davisHandler = dvsstream.connect2camera(id);
	davisHandler = dvsstream.startdatastream(davisHandler);

	while (nr_packets < max_packets) {
		dvsstream.sendpacket(davisHandler, false);
		nr_packets += 1;
	}

	exitcode = dvsstream.stopdatastream(davisHandler);

	dvsstream.closesocket();

	printf("Total number of events sent: %ld\n", dvsstream.events_sent);

}