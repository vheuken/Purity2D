#include "host.h"

Purity::Host::~Host()
{
    enet_host_destroy(mHost);
}
