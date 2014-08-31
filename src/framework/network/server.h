#ifndef SERVER_H
#define SERVER_H

#include <queue>
#include <vector>
#include "../entity/entitystate.h"
#include "host.h"

#include "networkaction.h"

#include "../system/timer.h"

namespace Purity
{
    class Server : public Host
    {
    public:
        Server(const unsigned short port, std::queue<NetworkAction>* actionQueue);

        void handleEvents();

        void sendDataToClients(const std::vector<EntityState>& entityStates);

    private:
        std::queue<NetworkAction>* mReceivedActionQueue;

        Timer mSendRateTimer;

    };
}

#endif // SERVER_H
