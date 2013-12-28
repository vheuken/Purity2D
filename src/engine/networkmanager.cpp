#include "networkmanager.h"
#include "luamanager.h"
#include <iostream>

Purity::NetworkManager::NetworkManager()
{
    mSocket.setBlocking(false);
    mListener.setBlocking(false);
    luabind::globals(LuaManager::getManager()->getState())["GPurityNetwork"] = this;
}

void Purity::NetworkManager::update()
{
    listenForConnections();
}

void Purity::NetworkManager::setPort(unsigned short port)
{
    mPort = port;
    mSocket.bind(mPort);
    mListener.listen(mPort);
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

void Purity::NetworkManager::connectToServer(std::string serverAddress)
{
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect(serverAddress, mPort);

    if (status != sf::Socket::Done)
    {
        std::cerr << "Connection to " << serverAddress << " failed!" << std::endl;
    }
    else if (status == sf::Socket::Done)
    {
        std::cout << "Connected to " << serverAddress << std::endl;
    }
}


std::string Purity::NetworkManager::getLocalAddress()
{
    return sf::IpAddress::getLocalAddress().toString();
}

std::string Purity::NetworkManager::getPublicAddress()
{
    return sf::IpAddress::getPublicAddress().toString();
}

void Purity::NetworkManager::listenForConnections()
{
    sf::TcpSocket client;

    if (mListener.accept(client) == sf::Socket::Done)
    {
        std::cout << "New connection received from: " << client.getRemoteAddress() << std::endl;
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
        ;
}