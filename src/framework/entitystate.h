#ifndef ENTITY_STATE_H
#define ENTITY_STATE_H

#include <Box2D/Box2D.h>
#include <SFML/Network.hpp>

namespace Purity
{
    struct EntityState
    {
        sf::Int32 entityId;
        b2Vec2 position;
        float32 angle;
    };
}

#endif // ENTITY_STATE_H
