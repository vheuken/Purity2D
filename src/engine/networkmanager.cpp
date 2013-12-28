#include "networkmanager.h"
#include "luamanager.h"
#include <iostream>

Purity::NetworkManager::NetworkManager() : server(false)
{
    mSocket.setBlocking(false);
    mListener.setBlocking(false);
    luabind::globals(LuaManager::getManager()->getState())["GPurityNetwork"] = this;
}

void Purity::NetworkManager::update()
{
    if (isServer())
    {
        listenForNewConnections();
        receiveActionsFromClients();
        sendDataToClients();
    }
    else
    {
        sendActionsToServer();
        receiveDataFromServer();
    }
}

void Purity::NetworkManager::setPort(unsigned short port)
{
    mPort = port;
    mSocket.bind(mPort);
    mListener.listen(mPort);
}

void Purity::NetworkManager::sendAction(std::string objectName, std::string actionName)
{
    NetworkAction action;
    action.objectName = objectName;
    action.actionName = actionName;

    actionQueue.push(action);
}

void Purity::NetworkManager::sendActionsToServer()
{
    while (actionQueue.empty() == false)
    {
        sf::Packet packet;

        packet << actionQueue.front();

        actionQueue.pop();

        mSocket.send(packet, mServerAddress, mPort);
    }
}

void Purity::NetworkManager::setServer(bool isServer)
{
    this->server = isServer;
}

bool Purity::NetworkManager::isServer() const
{
    return server;
}

void Purity::NetworkManager::receiveAction(sf::IpAddress& client)
{
    sf::Packet packet;
    NetworkAction action;

    mSocket.receive(packet, client, mPort);
    
    if (packet >> action)
    {
        std::cout << "Object " << action.objectName << " is performing " << action.actionName << std::endl;
    }
}

void Purity::NetworkManager::connectToServer(std::string serverAddressStr)
{
    sf::TcpSocket socket;
    sf::IpAddress serverAddress(serverAddressStr);
    this->mServerAddress = serverAddress;
    sf::Socket::Status status = socket.connect(mServerAddress, mPort);
    if (status != sf::Socket::Done)
    {
        std::cerr << "Connection to " << mServerAddress << " failed!" << std::endl;
    }
    else if (status == sf::Socket::Done)
    {
        std::cout << "Connected to " << mServerAddress << std::endl;
    }
    socket.disconnect();
}

std::string Purity::NetworkManager::getLocalAddress()
{
    return sf::IpAddress::getLocalAddress().toString();
}

std::string Purity::NetworkManager::getPublicAddress()
{
    return sf::IpAddress::getPublicAddress().toString();
}

void Purity::NetworkManager::listenForNewConnections()
{
    sf::TcpSocket client;

    if (mListener.accept(client) == sf::Socket::Done)
    {
        std::cout << "New connection received from: " << client.getRemoteAddress() << std::endl;
        addClient(client.getRemoteAddress());
    }
}

void Purity::NetworkManager::addClient(const sf::IpAddress& clientAddress)
{
    mClientAddressList.push_back(clientAddress);
}

void Purity::NetworkManager::sendDataToClients()
{

}

void Purity::NetworkManager::receiveDataFromServer()
{
}

void Purity::NetworkManager::receiveActionsFromClients()
{
    for (auto it = mClientAddressList.begin(); it != mClientAddressList.end(); ++it)
    {
        receiveAction(*it);
    }
}

luabind::scope Purity::NetworkManager::luaBindings()
{
    return luabind::class_<NetworkManager>("NetworkManager")
        .def("getLocalAddress", &NetworkManager::getLocalAddress)
        .def("getPublicAddress", &NetworkManager::getPublicAddress)
        .def("setPort", &NetworkManager::setPort)
        .def("sendAction", &NetworkManager::sendAction)
        .def("receiveAction", &NetworkManager::receiveAction)
        .def("connectToServer", &NetworkManager::connectToServer)
        .def("setServer", &NetworkManager::setServer)
        ;
}
