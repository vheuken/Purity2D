#ifndef HOST_H
#define HOST_H

#include <enet/enet.h>

namespace Purity
{
class Host
{
public:
    ~Host();

    virtual void handleEvents() = 0;

protected:
    ENetHost* mHost;
    ENetAddress mAddress;
};
}

#endif // HOST_H
