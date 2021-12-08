#include <assert.h>
#include <cstring>
#include <chrono>
#include <thread>
#include "CLI11.hpp"
#include "client.hpp"


int main(int argc, char *argv[]) {
    CLI::App app{"Listen to DVS data from UDP socket"};
    
    /*
     *  Variables
     */

    // network parameters
    std::string port_cli; 
    int sockfd;
    struct sockaddr_storage their_addr;
    socklen_t addr_len;
    int numbytes;
    int max_events_per_packet = 600;

    // script behavior
    std::string filename;
    std::fstream fileOutput;
    int x_max, y_max; 
    uint64_t events_received = 0, t_max = 0, events_received_timeframe = 0, print_time;

    // event parameters
    bool timestamp_flag, polarity; 
    uint16_t x_coord, y_coord;
    uint64_t timestamp; 

    /*
     *  CLI Input
     */

    // port number
    auto app_port = app.add_subcommand("port", "Port")->required();
    app_port->add_option("port_number", port_cli, "Port number")->required();

    // max events per packet
    auto app_max_events = app.add_subcommand("max_events", "Maximum events per packet");
    app_max_events->add_option("max_events", max_events_per_packet, "Number of maximum events per packet")->required();

    // output filename
    auto app_file = app.add_subcommand("file", "Output file");
    app_file->add_option("filename", filename, "Filename of output")->required();

    // decoding
    auto app_decoding = app.add_subcommand("decoding", "Decode packets");
    app_decoding->add_option("xmax", x_max, "Maximum x-coordinate")->required();
    app_decoding->add_option("ymax", y_max, "Maximum y-coordinate")->required();

    // time of script
    auto app_time = app.add_subcommand("time", "Time frame of script");
    app_time->add_option("t_max", t_max, "Maximum time of script")->required();

    // time of script
    auto app_print_time = app.add_subcommand("print_time", "Time for printing number of events");
    app_print_time->add_option("print_t", print_time, "Time interval for printing")->required();

    CLI11_PARSE(app, argc, argv);

    const char* port = port_cli.c_str(); 
    u_int16_t int_buf[max_events_per_packet];

    if (app_file->parsed()) {
	    fileOutput.open(filename, std::fstream::app);
	}

    /* 
     *  Connect as client
    */
    sockfd = establish_connection(port);
    std::cout << ("listener: waiting to recvfrom...") << std::endl; 

    // start receiving events 
    addr_len = sizeof their_addr;

    auto start = std::chrono::steady_clock::now();
    auto start_print = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start);
    auto duration_print = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start);

    while (true) {

        if (app_print_time->parsed()) {
            duration_print = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_print);

            if (duration_print.count() > print_time){
                std::cout << "Events received: " << events_received_timeframe << std::endl;
                start_print = std::chrono::steady_clock::now();
                events_received_timeframe = 0; 
            }
        }

        if ((numbytes = recvfrom(sockfd, int_buf, sizeof(int_buf) , 0, (struct sockaddr *)&their_addr, &addr_len)) == -1) {
            perror("recvfrom");
            exit(1);
        }

        if (events_received == 0){
            start = std::chrono::steady_clock::now();
        }

        if (app_time->parsed()) {
            duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start);

            if (duration.count() > t_max){
                break; 
            }
        }

        events_received += numbytes/4; // 4 bytes (32 bits) per event for no time stamp data
        events_received_timeframe += numbytes/4;

        if (app_decoding->parsed()) {
            // Decoding last event according to protocol
            for(int i = 0; i<numbytes/2; i++){

                // decode byte 2 and 3 -> polarity bit
                if (i % 2 == 0){
                    if(int_buf[i] & 0x8000){
                        polarity = 1;
                    } else {
                        polarity = 0;
                }
                    // decode byte 2 and 3 -> 15 bit event address Y
                    y_coord = int_buf[i] & 0x7FFF;
                    assert(y_coord < y_max); 
                }
                
                // decode byte 0 and byte 1 -> no-timestamp bit
                else if (i % 2 != 0){
                    if(int_buf[i] & 0x8000){
                        timestamp_flag = 1;
                    } else {
                        timestamp_flag = 0;
                    }

                    // decode byte 1 -> 15 bit event address X
                    x_coord = int_buf[i] & 0x7FFF;
                    assert(x_coord < x_max);

                    // print
                    std::cout << "timestamp bit: " << timestamp_flag << std::endl; 
                    std::cout << "x: " << x_coord << std::endl; 
                    std::cout << "y: " << y_coord << std::endl; 
                    std::cout << "polarity: " << polarity << std::endl; 
                }
            }
        }

        if (app_file->parsed()) {
            fileOutput << "DVS " << " " << x_coord << " " << y_coord << " " << polarity << std::endl;
        }
    } 

    close(sockfd);

    std::cout << "Events received: " << events_received << std::endl;

    return 0;
}
