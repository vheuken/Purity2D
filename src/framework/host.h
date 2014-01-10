#ifndef HOST_H
#define HOST_H

#include <enet/enet.h>

namespace Purity
{
    class Host
    {
    public:
        ~Host();

    private:
        ENetHost* host;
        ENetAddress address;
    };
}

#endif // HOST_H
