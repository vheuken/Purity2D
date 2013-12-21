#include "networkmanager.h"
#include "luamanager.h"
#include <iostream>

Purity::NetworkManager::NetworkManager() : port(54000)
{
    luabind::globals(LuaManager::getManager()->getState())["GPurityNetwork"] = this;
}

void Purity::NetworkManager::update()
{

}

void Purity::NetworkManager::send(std::string recipient)
{
    char data[100] = "5555555555555555555555";
    sf::IpAddress r = recipient;
    socket.send(data, 100, recipient, port);
}

void Purity::NetworkManager::receive(std::string sender)
{
    char data[100];
    std::size_t r;
    sf::IpAddress s = sender;
    socket.receive(data, 100, r, s, port);

    std::cout << "Received " << r << " bytes: ";
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
        .def("send", &NetworkManager::send)
        .def("receive", &NetworkManager::receive)
        ;
}