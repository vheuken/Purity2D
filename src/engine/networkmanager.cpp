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

void Purity::NetworkManager::send(std::string recipient)
{
    char data[100] = "5555555555555555555555";
    sf::IpAddress r = recipient;
    if (mSocket.send(data, 100, recipient, mPort) != sf::Socket::Done)
    {
        std::cerr << "Error sending!" << std::endl;
    }
}

void Purity::NetworkManager::receive(std::string sender)
{
    char data[100];
    std::size_t r;
    sf::IpAddress s = sender;
    mSocket.receive(data, 100, r, s, mPort);

    std::cout << "Received " << r << " bytes from " << sender << std::endl;
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
        .def("send", &NetworkManager::send)
        .def("receive", &NetworkManager::receive)
        ;
}