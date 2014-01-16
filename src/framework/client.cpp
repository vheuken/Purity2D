#include "client.h"
#include <iostream>

Purity::Client::Client() 
: mServerPeer(nullptr)
{
    mHost = enet_host_create(NULL, 1, 2, 0, 0);
    
    if (mHost == NULL)
    {
        std::cerr << "Error occured while trying to create an ENet client host\n";
    }
}

void Purity::Client::handleEvents()
{
    ENetEvent event;

    while (enet_host_service(mHost, &event, 0) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            std::cout << "Packet received!\n";
        }
    }
}

void Purity::Client::sendAction(NetworkAction action)
{
    ENetPacket * enetPacket;

    enetPacket = enet_packet_create(&action, sizeof(NetworkAction), ENET_PACKET_FLAG_RELIABLE);

    enet_peer_send(mServerPeer, 0, enetPacket);
}

void Purity::Client::connectToServer(std::string serverAddressStr, unsigned short port)
{
    ENetAddress address;
    ENetEvent event;
    ENetPeer *peer;

    enet_address_set_host(&address, serverAddressStr.c_str());
    address.port = port;

    peer = enet_host_connect(mHost, &address, 2, 0);

    if (peer == NULL)
    {
        std::cerr << "No available peers for initiating connection\n";
    }

    if (enet_host_service(mHost, &event, 5000) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT)
    {
        std::cout << "Connected to " << serverAddressStr << std::endl;
        mServerPeer = peer;
    }
    else
    {
        enet_peer_reset(peer);
        std::cout << "Connection to " << serverAddressStr << " failed" << std::endl;
    }
}
