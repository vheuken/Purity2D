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

void Purity::Server::handleEvents()
{
    ENetEvent event;

    while (enet_host_service(host, &event, 1 / 120) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            std::cout << "New peer!\n";
            break;
        
        case ENET_EVENT_TYPE_DISCONNECT:
            std::cout << "Peer disconnected!\n";
            break;
        default:
            std::cout << "Default!\n";
        }
    }
}
