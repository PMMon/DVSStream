#pragma once

#define LIBCAER_FRAMECPP_OPENCV_INSTALLED 0

#include <libcaercpp/devices/davis.hpp>
#include "DVSEvents.hpp"
#include <torch/script.h>
#include <atomic>
#include <csignal>

#ifndef DVSSTREAM_H
#define DVSSTREAM_H

using namespace std;


class DVSStream{
    public:
        // Parameters
        uint32_t container_interval;
        uint32_t buffer_size;
        int sockfd = -1;
        const char* serverport;
        const char* IPAdress;
        struct addrinfo *p;
        const char* filename;
        std::fstream fileOutput;

        static const uint16_t UDP_max_bytesize = 512;
        uint32_t message[UDP_max_bytesize/4];
        uint64_t events_sent = 0;

        DVSStream(uint32_t interval, uint32_t bfsize, const char* port, const char* IP, struct addrinfo *point, const char* file);

        static void globalShutdownSignalHandler(int signal);
        static void usbShutdownHandler(void *ptr); 
        libcaer::devices::davis connect2camera(int ID);
        libcaer::devices::davis startdatastream(libcaer::devices::davis davisHandle);
        void sendpacket(libcaer::devices::davis davisHandle, bool include_timestamp);
        int stopdatastream(libcaer::devices::davis davisHandle);
        void closesocket(); 
};

#endif