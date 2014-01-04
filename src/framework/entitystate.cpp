#include "entitystate.h"

Purity::EntityState::EntityState()
{
}

Purity::EntityState::EntityState(int id)
    : entityId(id)
{
}

void Purity::EntityState::update(const b2Body *body)
{
    position = body->GetPosition();
    angle = body->GetAngle();
}

sf::Packet& Purity::operator <<(sf::Packet& packet, const Purity::EntityState& state)
{
    packet << state.entityId << state.position << state.angle;
}

sf::Packet& Purity::operator >>(sf::Packet& packet, Purity::EntityState& state)
{
    packet << state.entityId << state.position << state.angle;
}

sf::Packet& Purity::operator <<(sf::Packet& packet, const b2Vec2& vector)
{
    packet << vector.x << vector.y;
}

sf::Packet& Purity::operator >>(sf::Packet& packet, b2Vec2& vector)
{
    packet >> vector.x >> vector.y;
}
