#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include "entitystate.h"
#include "host.h"

namespace Purity
{
    class Server : public Host
    {
    public:
        Server(const unsigned short port);

        void handleEvents();

        void sendDataToClients(const std::vector<EntityState>& entityStates);
    };
}

#endif // SERVER_H
