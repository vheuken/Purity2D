#ifndef NETWORK_SYSTEM_H
#define NETWORK_SYSTEM_H

#include <SFML/Network.hpp>
#include <luabind/luabind.hpp>
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include <enet/enet.h>

#include "abstractsystem.h"
#include "../framework/networkaction.h"
#include "../framework/scene.h"
#include "../framework/server.h"
#include "../framework/client.h"

namespace Purity
{
    class NetworkSystem : public AbstractSystem
    {
    public:
        NetworkSystem(std::queue<NetworkAction> * serverActionQueue,
                      std::map<unsigned int, EntityState> * receivedStates);

        ~NetworkSystem();

        std::string getLocalAddress();
        std::string getPublicAddress();

        void update(Scene* scene);

        void setPort(unsigned short port);

        void sendAction(std::string objectName, std::string actionName);

        void connectToServer(std::string serverAddress);
        
        void initializeServer(unsigned short port);
        void initializeClient();

        void setServer(bool isServer);
        bool isServer() const;

        static luabind::scope luaBindings();

    private:
        unsigned short mPort;
        bool mIsServer;
        
        std::unique_ptr<Client> mClient;
        std::unique_ptr<Server> mServer;
        std::queue<NetworkAction>* mServerActionQueue;
        std::queue<NetworkAction>  mClientActionQueue;
        std::map<unsigned int, EntityState>* mClientReceievdStates;
    };
}

#endif // NETWORK_SYSTEM_H
