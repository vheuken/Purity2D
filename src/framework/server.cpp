#include "server.h"
#include <iostream>

Purity::Server::Server(const unsigned short port)
{
    mAddress.host = ENET_HOST_ANY;

    mAddress.port = port;

    mHost = enet_host_create(&mAddress, 32, 2, 0, 0);
    
    if (mHost == NULL)
    {
        std::cerr << "Error occured while trying to create an ENet server host\n";
    }
}

void Purity::Server::handleEvents()
{
    ENetEvent event;

    while (enet_host_service(mHost, &event, 0) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            std::cout << "New peer!\n";
            break;
        
        case ENET_EVENT_TYPE_DISCONNECT:
            std::cout << "Peer disconnected!\n";
            break;
        case ENET_EVENT_TYPE_RECEIVE:
            std::cout << "Packet received!" << std::endl;
            break;

        default:
            std::cout << "Default!\n";
        }
    }
}
