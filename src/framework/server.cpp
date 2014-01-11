#include "server.h"
#include <iostream>

Purity::Server::Server(const unsigned short port)
{
    address.host = ENET_HOST_ANY;

    address.port = port;

    host = enet_host_create(&address, 32, 2, 0, 0);
    
    if (host == NULL)
    {
        std::cerr << "Error occured while trying to create an ENet server host\n";
    }
}
