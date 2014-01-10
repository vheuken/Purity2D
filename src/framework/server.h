#ifndef SERVER_H
#define SERVER_H

#include <string>
#include "host.h"

namespace Purity
{
    class Server : public Host
    {
    public:
        Server(unsigned short port);
    };
}

#endif // SERVER_H
