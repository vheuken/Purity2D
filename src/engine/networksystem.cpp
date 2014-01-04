#include "networksystem.h"
#include "luamanager.h"
#include <iostream>

Purity::NetworkSystem::NetworkSystem(std::queue<NetworkAction> * serverActionQueue) 
: mServer(false), mServerActionQueue(serverActionQueue), AbstractSystem()
{
    mSocket.setBlocking(false);
    mListener.setBlocking(false);
    luabind::globals(LuaManager::getManager()->getState())["GPurityNetwork"] = this;
}

void Purity::NetworkSystem::update(Scene* scene)
{
    if (mCurrentScene != scene)
    {
        mCurrentScene = scene;
    }

    if (isServer())
    {
        listenForNewConnections();
        sendDataToClients();
        receiveActionsFromClients();
    }
    else
    {
        sendActionsToServer();
        receiveDataFromServer();
    }
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
    this->mServer = isServer;
}

bool Purity::NetworkSystem::isServer() const
{
    return mServer;
}

void Purity::NetworkSystem::receiveAction(sf::IpAddress& client)
{
    sf::Packet packet;
    NetworkAction action;

    sf::IpAddress backup = client;

    if (mSocket.receive(packet, client, mPort) != sf::Socket::Done)
    {
        client = backup;
    }
    
    if (packet >> action)
    {
        mServerActionQueue->push(action);
        std::cout << "Object " << action.objectName << " is performing " << action.actionName << std::endl;
    }
}

void Purity::NetworkSystem::connectToServer(std::string serverAddressStr)
{
    sf::TcpSocket socket;
    sf::IpAddress serverAddress(serverAddressStr);
    this->mServerAddress = serverAddress;
    sf::Socket::Status status = socket.connect(mServerAddress, mPort);
    if (status != sf::Socket::Done)
    {
    }
    else if (status == sf::Socket::Done)
    {
        std::cout << "Connected to " << mServerAddress << std::endl;
    }
    
    socket.disconnect();

    sf::Packet emptyPacket;
    mSocket.send(emptyPacket, mServerAddress, mPort);
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
    std::vector<EntityState> listOfStates = mCurrentScene->getEntityStates();

    sf::Packet packet;

    for (auto client = mClientAddressList.begin(); client != mClientAddressList.end(); ++client)
    {
        for (auto state = listOfStates.begin(); state != listOfStates.end(); ++state)
        {
            packet << *state;

            mSocket.send(packet, *client, mPort);
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
        std::cout << "Received state of size: " << sizeof(state) << std::endl;
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
        ;
}
