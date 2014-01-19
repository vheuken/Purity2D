#include "server.h"
#include <iostream>

Purity::Server::Server(const unsigned short port, std::queue<NetworkAction>* actionQueue)
{
    mAddress.host = ENET_HOST_ANY;

    mAddress.port = port;

    mHost = enet_host_create(&mAddress, 32, 2, 0, 0);
    
    if (mHost == NULL)
    {
        std::cerr << "Error occured while trying to create an ENet server host\n";
    }

    mReceivedActionQueue = actionQueue;
}

void Purity::Server::handleEvents()
{
    ENetEvent event;
    NetworkAction action;

    while (enet_host_service(mHost, &event, 0) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            std::cout << "New peer!" << std::endl;
            break;
        
        case ENET_EVENT_TYPE_DISCONNECT:
            std::cout << "Peer disconnected!" << std::endl;
            break;
        case ENET_EVENT_TYPE_RECEIVE:
            memcpy(&action, event.packet->data, event.packet->dataLength);

            std::cout << action.objectName << " is performing " << action.actionName << std::endl;

            mReceivedActionQueue->push(action);

            enet_packet_destroy(event.packet);

            break;

        default:
            std::cout << "Default!\n";
        }
    }
}

void Purity::Server::sendDataToClients(const std::vector<EntityState>& entityStates)
{
    static sf::Clock timer;

    if (timer.getElapsedTime().asMilliseconds() >= 20)
    {
        std::cout << "Sending packets to clients!!" << std::endl;
        for (auto stateIter = entityStates.begin(); stateIter != entityStates.end(); ++stateIter)
        {
            EntityState state = *stateIter;

            ENetPacket* packet = enet_packet_create(&state, sizeof(state), ENET_PACKET_FLAG_SENT);

            enet_host_broadcast(mHost, 0, packet);
        }
        timer.restart();
    }
}