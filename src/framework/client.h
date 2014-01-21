#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <string>
#include <map>
#include "host.h"

#include "entitystate.h"
#include "networkaction.h"

namespace Purity
{
    class Client : public Host
    {
    public:
        Client(std::map<unsigned int, EntityState>* receivedStates);

        void handleEvents();

        void sendAction(NetworkAction action);

        void connectToServer(std::string serverAddressStr, unsigned short port);

    private:
        ENetPeer * mServerPeer;
        std::map<unsigned int, EntityState>* mReceivedStates;
    };
}

#endif // CLIENT_H
