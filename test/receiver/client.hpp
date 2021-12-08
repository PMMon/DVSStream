# ifndef CLIENT_HPP
# define CLIENT_HPP

#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <stdexcept>

int establish_connection(const char* port);

# endif