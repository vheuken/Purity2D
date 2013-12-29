#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <SFML/Network.hpp>
#include <luabind/luabind.hpp>
#include <string>
#include <vector>
#include <queue>

#include "networkaction.h"

namespace Purity
{
    class NetworkManager
    {
    public:
        NetworkManager(std::queue<NetworkAction> * serverActionQueue);

        std::string getLocalAddress();
        std::string getPublicAddress();

        void update();

        void setPort(unsigned short port);

        void sendAction(std::string objectName, std::string actionName);
        void receiveAction(sf::IpAddress& client);

        void connectToServer(std::string serverAddress);

        void setServer(bool isServer);
        bool isServer() const;

        static luabind::scope luaBindings();

    private:
        sf::UdpSocket mSocket;
        sf::TcpListener mListener;
        sf::IpAddress mServerAddress;
        std::vector<sf::IpAddress> mClientAddressList;

        unsigned short mPort;
        bool mServer;

        std::queue<NetworkAction>* mServerActionQueue;
        std::queue<NetworkAction>  mClientActionQueue;

        void listenForNewConnections();
        void addClient(const sf::IpAddress& clientAddress);
        void sendDataToClients();
        void receiveDataFromServer();
        void sendActionsToServer();
        void receiveActionsFromClients();
    };
}

#endif // NETWORK_MANAGER_H
