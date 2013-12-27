#include "networkmanager.h"
#include "luamanager.h"
#include <iostream>

Purity::NetworkManager::NetworkManager()
{
    mSocket.setBlocking(false);
    luabind::globals(LuaManager::getManager()->getState())["GPurityNetwork"] = this;
}

void Purity::NetworkManager::update()
{

}

void Purity::NetworkManager::setPort(unsigned short port)
{
    mPort = port;
    mSocket.bind(mPort);
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

    packet >> objectName >> action;

    std::cout << "Object " << objectName << " is performing " << action << std::endl;
}

std::string Purity::NetworkManager::getLocalAddress()
{
    return sf::IpAddress::getLocalAddress().toString();
}

std::string Purity::NetworkManager::getPublicAddress()
{
    return sf::IpAddress::getPublicAddress().toString();
}

luabind::scope Purity::NetworkManager::luaBindings()
{
    return luabind::class_<NetworkManager>("NetworkManager")
        .def("getLocalAddress", &NetworkManager::getLocalAddress)
        .def("getPublicAddress", &NetworkManager::getPublicAddress)
        .def("setPort", &NetworkManager::setPort)
        .def("sendAction", &NetworkManager::sendAction)
        .def("receiveAction", &NetworkManager::receiveAction)
        ;
}