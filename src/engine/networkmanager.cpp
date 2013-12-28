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
        sendDataToClients();
    }
    else
    {
        receiveDataFromServer();
    }
}

void Purity::NetworkManager::setPort(unsigned short port)
{
    mPort = port;
    mSocket.bind(mPort);
    mListener.listen(5775);
}

void Purity::NetworkManager::sendAction(std::string recipient, std::string objectName, std::string action)
{
    sf::Packet packet;
    sf::IpAddress r = recipient;

    packet << objectName << action;

    if (mSocket.send(packet, r, mPort) != sf::Socket::Done)
    {
        std::cerr << "Error sending!" << std::endl;
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

void Purity::NetworkManager::receiveAction(std::string sender)
{
    sf::Packet packet;
    sf::IpAddress s = sender;
    std::string objectName, action;

    mSocket.receive(packet, s, mPort);

    if (packet >> objectName >> action)
    {
        std::cout << "Object " << objectName << " is performing " << action << std::endl;
    }
}

void Purity::NetworkManager::connectToServer(std::string serverAddressStr)
{
    sf::TcpSocket socket;
    sf::IpAddress serverAddress(serverAddressStr);
    this->mServerAddress = serverAddress;
    sf::Socket::Status status = socket.connect(mServerAddress, 5775);
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
    sf::Packet p;
    p << "6666666666666666666666666666666666666666666";
    for (auto it = mClientAddressList.begin(); it != mClientAddressList.end(); ++it)
    {
        if (mSocket.send(p, *it, mPort) != sf::Socket::Done)
        {
            std::cout << "ERROR\n";
        }
        
    }
}

void Purity::NetworkManager::receiveDataFromServer()
{
    sf::Packet p;
    mSocket.receive(p, mServerAddress, mPort);

    std::cout << "Received " << p.getDataSize() << " bytes from " << mServerAddress <<  std::endl;
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
