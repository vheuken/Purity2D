#ifndef SERVER_H
#define SERVER_H

#include "host.h"

namespace Purity
{
    class Server : public Host
    {
    public:
        Server(const unsigned short port);

        void handleEvents();
    };
}

#endif // SERVER_H
