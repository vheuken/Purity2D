#ifndef HOST_H
#define HOST_H

#include <enet/enet.h>

namespace Purity
{
    class Host
    {
    public:
        ~Host();

    protected:
        ENetHost* mHost;
        ENetAddress mAddress;
    };
}

#endif // HOST_H
