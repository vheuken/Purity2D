#include "client.h"
#include <iostream>

Purity::Client::Client()
{
    host = enet_host_create(NULL, 1, 2, 0, 0);
    
    if (host == NULL)
    {
        std::cerr << "Error occured while trying to create an ENet client host\n";
    }
}

void Purity::Client::connectToServer(std::string serverAddressStr, unsigned short port)
{
    ENetAddress address;
    ENetEvent event;
    ENetPeer *peer;

    enet_address_set_host(&address, serverAddressStr.c_str());
    address.port = port;

    peer = enet_host_connect(host, &address, 2, 0);

    if (peer == NULL)
    {
        std::cerr << "No available peers for initiating connection\n";
    }

    if (enet_host_service(host, &event, 5000) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT)
    {
        std::cout << "Connected to " << serverAddressStr << std::endl;
    }
    else
    {
        enet_peer_reset(peer);
        std::cout << "Connection to " << serverAddressStr << " failed" << std::endl;
    }
}
