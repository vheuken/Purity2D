#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "host.h"

namespace Purity
{
    class Client : public Host
    {
    public:
        Client();

        void handleEvents();

        void connectToServer(std::string serverAddressStr, unsigned short port);
    };
}

#endif // CLIENT_H
