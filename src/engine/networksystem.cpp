#include "networksystem.h"
#include "luamanager.h"
#include <iostream>

Purity::NetworkSystem::NetworkSystem(std::queue<NetworkAction> * serverActionQueue) 
: mIsServer(false), mServerActionQueue(serverActionQueue), AbstractSystem()
{
    if (enet_initialize() != 0)
    {
        std::cerr << "Error initializing enet!" << std::endl;
    }

    mSocket.setBlocking(false);
    mListener.setBlocking(false);
    luabind::globals(LuaManager::getManager()->getState())["GPurityNetwork"] = this;
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
    }
    else if (mClient)
    {
        mClient->handleEvents();

        while (mClientActionQueue.empty() == false)
        {
            sf::Packet packet;

            packet << mClientActionQueue.front();

            mClientActionQueue.pop();

            mClient->sendPacket(packet);
        }
    }
}

void Purity::NetworkSystem::initializeServer(unsigned short port)
{
    mServer = std::unique_ptr<Server>(new Server(port));
    mPort = port;
    mIsServer = true;
}

void Purity::NetworkSystem::initializeClient()
{
    mClient = std::unique_ptr<Client>(new Client());
}

void Purity::NetworkSystem::setPort(unsigned short port)
{
    mPort = port;
}

void Purity::NetworkSystem::sendAction(std::string objectName, std::string actionName)
{
    NetworkAction action;
    action.objectName = objectName;
    action.actionName = actionName;

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
    return sf::IpAddress::getLocalAddress().toString();
}

std::string Purity::NetworkSystem::getPublicAddress()
{
    return sf::IpAddress::getPublicAddress().toString();
}

luabind::scope Purity::NetworkSystem::luaBindings()
{
    return luabind::class_<NetworkSystem>("NetworkSystem")
        .def("getLocalAddress", &NetworkSystem::getLocalAddress)
        .def("getPublicAddress", &NetworkSystem::getPublicAddress)
        .def("setPort", &NetworkSystem::setPort)
        .def("sendAction", &NetworkSystem::sendAction)
        .def("connectToServer", &NetworkSystem::connectToServer)
        .def("setServer", &NetworkSystem::setServer)
        .def("initializeServer", &NetworkSystem::initializeServer)
        .def("initializeClient", &NetworkSystem::initializeClient)
        ;
}
