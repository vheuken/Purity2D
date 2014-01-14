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

void Purity::Server::sendDataToClients(const std::vector<EntityState>& entityStates)
{
    for (auto state = entityStates.begin(); state != entityStates.end(); ++state)
    {
        ENetPacket* packet = enet_packet_create(&state, sizeof(state), ENET_PACKET_FLAG_RELIABLE);

        for (size_t i = 0; i < mHost->connectedPeers; ++i)
        {
            enet_peer_send(&mHost->peers[i], 0, packet);
        }
    }
}