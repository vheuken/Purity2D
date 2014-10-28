#ifndef NETWORK_SYSTEM_H
#define NETWORK_SYSTEM_H

#include <string>
#include <map>
#include <queue>
#include <memory>
#include <enet/enet.h>

#include "subsystemable.h"
#include "../framework/network/networkaction.h"
#include "../framework/scene.h"
#include "../framework/network/server.h"
#include "../framework/network/client.h"

struct lua_State;

namespace Purity
{
class NetworkSystem : public SubSystemable
{
public:
    NetworkSystem(std::queue<NetworkAction>* serverActionQueue);

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

    void static luaBindings(lua_State* state);

private:
    unsigned short mPort;
    bool mIsServer;

    std::queue<NetworkAction>* mServerActionQueue;
    std::queue<NetworkAction> mClientActionQueue;
    std::unique_ptr<Client> mClient;
    std::unique_ptr<Server> mServer;
    std::unique_ptr<std::map<unsigned int, EntityState>> mClientReceievdStates;
};
}

#endif // NETWORK_SYSTEM_H
