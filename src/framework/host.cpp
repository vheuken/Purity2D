#include "host.h"

Purity::Host::~Host()
{
    for (size_t i = 0; i < mHost->connectedPeers; ++i)
    {
        enet_peer_disconnect(&mHost->peers[i], 0);
    }
    enet_host_destroy(mHost);
}
