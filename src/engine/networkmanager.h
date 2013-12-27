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

        void setPort(unsigned short port);

        void sendAction(std::string recipient, std::string objectName, std::string action);
        void receiveAction(std::string sender);

        static luabind::scope luaBindings();

    private:
        sf::UdpSocket mSocket;
        unsigned short mPort;
    };
}

#endif // NETWORK_MANAGER_H