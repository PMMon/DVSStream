#include "dvs2udp.hpp"
#include <string>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <type_traits>


int main(int argc, char *argv[]) {
  	//pid_t pid = getpid();
  	//printf("pid: %u\n", pid);
	//sleep(10);

	const char* filename = "None"; 
	std::string command = "Nonset";
	uint32_t interval;
	uint32_t buffer_size = 512;
	const char* port = "3333";	// Port number
	const char* IPAdress = NULL;	// IP Adress - if NULL, use own IP. Hugin: 172.16.222.30; SPIF: 172.16.223.2
	const char* camera = "davis";	// Specify camera type

	int nr_packets = 0;
	uint32_t max_packets;
	int id = 1;
	int devAddress = 0;
	int exitcode, sockfd;

    if (argc < 3) {
        fprintf(stderr,"usage: ./stream2ethernet <max_packet_size> <nr_packets_2_send> (Optional: <camera type> <usb id> <device Address> <port> <IP Adress>)\n");
        exit(1);
    }
	else if (argc == 4)
	{
		camera = argv[3];
	}
	else if (argc == 5)
	{
		camera = argv[3];
		id = stoi(argv[4]);
	}
	else if (argc == 6)
	{
		camera = argv[3];
		id = stoi(argv[4]);
		devAddress = stoi(argv[5]);
	}
	else if (argc == 7)
	{
		camera = argv[3];
		id = stoi(argv[4]);
		devAddress = stoi(argv[5]);
		port = argv[6];
	}
	else if (argc == 8)
	{
		camera = argv[3];
		id = stoi(argv[4]);
		devAddress = stoi(argv[5]);
		port = argv[6];
		IPAdress = argv[7];
	}
	else if (argc == 9)
	{
		camera = argv[3];
		id = stoi(argv[4]);
		devAddress = stoi(argv[5]);
		port = argv[6];
		IPAdress = argv[7];
		filename = argv[8];
	}

	interval = strtol(argv[1], NULL, 0);
	max_packets = strtol(argv[2], NULL, 0);
	
	if (strcmp (camera, "davis") == 0){		
		DVSStream<libcaer::devices::davis> dvsstream(interval, buffer_size, port, IPAdress, NULL, filename); 

		auto davisHandler = dvsstream.connect2davis(id, devAddress);
		davisHandler = dvsstream.startdatastream(davisHandler);

		while (nr_packets < max_packets) {
			dvsstream.sendpacket(davisHandler, false);
			nr_packets += 1;
		}

		exitcode = dvsstream.stopdatastream(davisHandler);

		dvsstream.closesocket();

		printf("Total number of events sent: %ld\n", dvsstream.events_sent); 
	}
	else if (strcmp (camera, "dvx") == 0)
	{
		DVSStream<libcaer::devices::dvXplorer> dvsstream(interval, buffer_size, port, IPAdress, NULL, filename); 

		auto davisHandler = dvsstream.connect2dvx(id, devAddress);
		davisHandler = dvsstream.startdatastream(davisHandler);

		while (nr_packets < max_packets) {
			dvsstream.sendpacket(davisHandler, false);
			nr_packets += 1;
		}

		exitcode = dvsstream.stopdatastream(davisHandler);

		dvsstream.closesocket();

		printf("Total number of events sent: %ld\n", dvsstream.events_sent); 
	}
	else
	{
		throw "Invalid cameratype! Please use either 'davis' or 'dvx'";
	}

}