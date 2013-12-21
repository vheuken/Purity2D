#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <SFML/Network.hpp>
#include <luabind/luabind.hpp>
#include <string>

namespace Purity
{
    class NetworkManager
    {
    public:
        NetworkManager();

        std::string getLocalAddress();
        std::string getPublicAddress();

        void update();

        void send(std::string recipient);
        void receive(std::string sender);

        static luabind::scope luaBindings();

    private:
        sf::UdpSocket socket;
        unsigned short port;
    };
}

#endif // NETWORK_MANAGER_H