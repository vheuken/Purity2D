#ifndef NETWORK_ACTION_H
#define NETWORK_ACTION_H

#include <string>
#include <SFML/Network.hpp>
#include <enet/enet.h>

namespace Purity
{
    struct NetworkAction
    {
        enet_uint8* objectName;
        enet_uint8* actionName;
    };

    //sf::Packet& operator <<(sf::Packet& packet, const NetworkAction& action);
    //sf::Packet& operator >>(sf::Packet& packet, NetworkAction& action);
}

#endif // NETWORK_ACTION_H