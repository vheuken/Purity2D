#ifndef ENTITY_STATE_H
#define ENTITY_STATE_H

#include <Box2D/Box2D.h>
#include <SFML/Network.hpp>

namespace Purity
{
    struct EntityState
    {
        EntityState();
        EntityState(const int id);
        void update(const b2Body * body);

        int entityId;
        b2Vec2 position;
        float32 angle;
    };

    sf::Packet& operator <<(sf::Packet& packet, const EntityState& action);
    sf::Packet& operator >>(sf::Packet& packet, EntityState& action);

    // b2vec2
    sf::Packet& operator <<(sf::Packet& packet, const b2Vec2& vector);
    sf::Packet& operator >>(sf::Packet& packet, b2Vec2& vector);
}

#endif // ENTITY_STATE_H
