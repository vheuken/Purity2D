#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <string>
#include <queue>
#include "host.h"

#include "entitystate.h"
#include "networkaction.h"

namespace Purity
{
    class Client : public Host
    {
    public:
        Client();

        void handleEvents();

        void sendAction(NetworkAction action);

        void connectToServer(std::string serverAddressStr, unsigned short port);

    private:
        ENetPeer * mServerPeer;
        std::queue<EntityState> mReceivedStates;
    };
}

#endif // CLIENT_H
