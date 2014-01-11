#include "client.h"
#include <iostream>

Purity::Client::Client()
{
    host = enet_host_create(NULL, 1, 2, 0, 0);
    
    if (host == NULL)
    {
        std::cerr << "Error occured while trying to create an ENet client host\n";
    }
}
