#ifndef NETWORK_SYSTEM_H
#define NETWORK_SYSTEM_H

#include <SFML/Network.hpp>
#include <luabind/luabind.hpp>
#include <string>
#include <vector>
#include <queue>
#include <enet/enet.h>

#include "abstractsystem.h"
#include "networkaction.h"
#include "../framework/scene.h"

namespace Purity
{
    class NetworkSystem : public AbstractSystem
    {
    public:
        NetworkSystem(std::queue<NetworkAction> * serverActionQueue);
        ~NetworkSystem();

        std::string getLocalAddress();
        std::string getPublicAddress();

        void update(Scene* scene);

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
        std::queue<EntityState> mStateQueue;

        void listenForNewConnections();
        void addClient(const sf::IpAddress& clientAddress);
        void sendDataToClients();
        void receiveDataFromServer();
        void sendActionsToServer();
        void receiveActionsFromClients();
    };
}

#endif // NETWORK_SYSTEM_H
