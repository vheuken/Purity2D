#ifndef NETWORK_ACTION_H
#define NETWORK_ACTION_H

#include <string>
#include <SFML/Network.hpp>
#include <enet/enet.h>

namespace Purity
{
    const int NETWORK_ACTION_MAX_STRING_LENGTH = 50;

    struct NetworkAction
    {
        char objectName[NETWORK_ACTION_MAX_STRING_LENGTH + 1];
        char actionName[NETWORK_ACTION_MAX_STRING_LENGTH + 1];
    };

    //sf::Packet& operator <<(sf::Packet& packet, const NetworkAction& action);
    //sf::Packet& operator >>(sf::Packet& packet, NetworkAction& action);
}

#endif // NETWORK_ACTION_H