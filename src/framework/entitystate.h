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
}

#endif // ENTITY_STATE_H
