#ifndef HOST_H
#define HOST_H

#include <enet/enet.h>

namespace Purity
{
    class Host
    {
    public:
        virtual ~Host();

    private:
        ENetHost* host;
    };
}

#endif // HOST_H
