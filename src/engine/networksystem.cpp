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

    if (isServer())
    {
    }
    else
    {
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
    mSocket.bind(mPort);
    mListener.listen(mPort);
}

void Purity::NetworkSystem::sendAction(std::string objectName, std::string actionName)
{
    NetworkAction action;
    action.objectName = objectName;
    action.actionName = actionName;

    mClientActionQueue.push(action);
}

void Purity::NetworkSystem::sendActionsToServer()
{
    while (mClientActionQueue.empty() == false)
    {
        sf::Packet packet;

        packet << mClientActionQueue.front();

        mClientActionQueue.pop();

        mSocket.send(packet, mServerAddress, mPort);
    }
}

void Purity::NetworkSystem::setServer(bool isServer)
{
    this->mIsServer = isServer;
}

bool Purity::NetworkSystem::isServer() const
{
    return mIsServer;
}

void Purity::NetworkSystem::receiveAction(sf::IpAddress& client)
{
    sf::Packet packet;
    NetworkAction action;

    sf::IpAddress c = client;

    if (mSocket.receive(packet, c, mPort) != sf::Socket::Done)
    {
        //std::cout << "Error receiving actions";
    }

    if (packet >> action)
    {
        std::cout << "Object " << action.objectName << " is performing " << action.actionName << std::endl;
        mServerActionQueue->push(action);
    }
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

void Purity::NetworkSystem::listenForNewConnections()
{
    sf::TcpSocket client;

    if (mListener.accept(client) == sf::Socket::Done)
    {
        std::cout << "New connection received from: " << client.getRemoteAddress() << std::endl;
        addClient(client.getRemoteAddress());
    }
    client.disconnect(); 
    sf::Packet emptyPacket;
    mSocket.send(emptyPacket, client.getRemoteAddress(), mPort);
}

void Purity::NetworkSystem::addClient(const sf::IpAddress& clientAddress)
{
    mClientAddressList.push_back(clientAddress);
}

void Purity::NetworkSystem::sendDataToClients()
{
    if (mCurrentScene)
    {
        std::vector<EntityState> listOfStates = mCurrentScene->getEntityStates();

        sf::Packet packet;

        for (auto client = mClientAddressList.begin(); client != mClientAddressList.end(); ++client)
        {
            for (auto state = listOfStates.begin(); state != listOfStates.end(); ++state)
            {
                packet << *state;

                mSocket.send(packet, *client, mPort);

                packet.clear();
            }
        }
    }
}

void Purity::NetworkSystem::receiveDataFromServer()
{
    sf::Packet packet;
    EntityState state;
    sf::IpAddress s = mServerAddress;

    mSocket.receive(packet, s, mPort);

    if (packet >> state)
    {
        std::cout << sizeof(state) << std::endl;
        //mStateQueue.push(state);
    }
}

void Purity::NetworkSystem::receiveActionsFromClients()
{
    for (auto it = mClientAddressList.begin(); it != mClientAddressList.end(); ++it)
    {
        receiveAction(*it);
    }
}

luabind::scope Purity::NetworkSystem::luaBindings()
{
    return luabind::class_<NetworkSystem>("NetworkSystem")
        .def("getLocalAddress", &NetworkSystem::getLocalAddress)
        .def("getPublicAddress", &NetworkSystem::getPublicAddress)
        .def("setPort", &NetworkSystem::setPort)
        .def("sendAction", &NetworkSystem::sendAction)
        .def("receiveAction", &NetworkSystem::receiveAction)
        .def("connectToServer", &NetworkSystem::connectToServer)
        .def("setServer", &NetworkSystem::setServer)
        .def("initializeServer", &NetworkSystem::initializeServer)
        .def("initializeClient", &NetworkSystem::initializeClient)
        ;
}
