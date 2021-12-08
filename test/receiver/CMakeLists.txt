cmake_minimum_required(VERSION 3.7)
project(Receiver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("include/")

# Connect to socket
add_library(client SHARED client.cpp)

# Receive polarity events via UDP
add_executable(listening listening.cpp)
target_link_libraries(listening PRIVATE client)