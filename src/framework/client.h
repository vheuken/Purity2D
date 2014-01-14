#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <string>
#include "host.h"

#include "../engine/networkaction.h"

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
    };
}

#endif // CLIENT_H
