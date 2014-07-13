#include "networksystem.h"
#include "luamanager.h"
#include <iostream>
#include <LuaBridge.h>

Purity::NetworkSystem::NetworkSystem(std::queue<NetworkAction> * serverActionQueue)
: AbstractSystem(),
  mIsServer(false),
  mServerActionQueue(serverActionQueue)
{
    if (enet_initialize() != 0)
    {
        std::cerr << "Error initializing enet!" << std::endl;
    }

    mClientReceievdStates = std::unique_ptr<std::map<unsigned int, EntityState> >(new std::map<unsigned int, EntityState>);

    //luabind::globals(LuaManager::getManager()->getState())["GPurityNetwork"] = this;
    luabridge::setGlobal(LuaManager::getManager()->getState(), this, "GPurityNetwork");
}

Purity::NetworkSystem::~NetworkSystem()
{
    enet_deinitialize();
}

void Purity::NetworkSystem::update(Scene* scene)
{
    if (mCurrentScene != scene)
    {
        mCurrentScene = scene;
    }

    if (mServer && isServer())
    {
        mServer->handleEvents();
        mServer->sendDataToClients(mCurrentScene->getEntityStates());
    }
    else if (mClient)
    {
        mClient->handleEvents();

        while (mClientActionQueue.empty() == false)
        {
            mClient->sendAction(mClientActionQueue.front());

            mClientActionQueue.pop();
        }

        for (auto it = mClientReceievdStates->begin(); it != mClientReceievdStates->end(); ++it)
        {
            mCurrentScene->setEntityState(it->second);
        }
    }
}

void Purity::NetworkSystem::initializeServer(unsigned short port)
{
    mServer = std::unique_ptr<Server>(new Server(port, mServerActionQueue));
    mPort = port;
    mIsServer = true;
}

void Purity::NetworkSystem::initializeClient()
{
    mClient = std::unique_ptr<Client>(new Client(mClientReceievdStates.get()));
}

void Purity::NetworkSystem::setPort(unsigned short port)
{
    mPort = port;
}

void Purity::NetworkSystem::sendAction(std::string objectName, std::string actionName)
{
    NetworkAction action;

    std::copy(objectName.begin(), objectName.end(), action.objectName);
    std::copy(actionName.begin(), actionName.end(), action.actionName);

    action.objectName[objectName.size()] = '\0';
    action.actionName[actionName.size()] = '\0';

    mClientActionQueue.push(action);
}

void Purity::NetworkSystem::setServer(bool isServer)
{
    this->mIsServer = isServer;
}

bool Purity::NetworkSystem::isServer() const
{
    return mIsServer;
}

void Purity::NetworkSystem::connectToServer(std::string serverAddressStr)
{
    mClient->connectToServer(serverAddressStr, mPort);
}

std::string Purity::NetworkSystem::getLocalAddress()
{
    return "";
    //return sf::IpAddress::getLocalAddress().toString();
}

std::string Purity::NetworkSystem::getPublicAddress()
{
    return "";
    //return sf::IpAddress::getPublicAddress().toString();
}

void Purity::NetworkSystem::luaBindings(lua_State* state)
{
    luabridge::getGlobalNamespace(state)
            .beginNamespace("Purity")
                .beginClass<NetworkSystem> ("NetworkSystem")
                    .addFunction("getLocalAddress", &NetworkSystem::getLocalAddress)
                    .addFunction("getPublicAddress", &NetworkSystem::getPublicAddress)
                    .addFunction("setPort", &NetworkSystem::setPort)
                    .addFunction("connectToServer", &NetworkSystem::connectToServer)
                    .addFunction("setServer", &NetworkSystem::setServer)
                    .addFunction("initializeServer", &NetworkSystem::initializeServer)
                    .addFunction("initializeClient", &NetworkSystem::initializeClient)
                .endClass()
            .endNamespace();
}

