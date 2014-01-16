#ifndef NETWORK_ACTION_H
#define NETWORK_ACTION_H

#include <string>
#include <SFML/Network.hpp>

namespace Purity
{
    struct NetworkAction
    {
        char* objectName;
        char* actionName;
    };

    //sf::Packet& operator <<(sf::Packet& packet, const NetworkAction& action);
    //sf::Packet& operator >>(sf::Packet& packet, NetworkAction& action);
}

#endif // NETWORK_ACTION_H