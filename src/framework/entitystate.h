#ifndef ENTITY_STATE_H
#define ENTITY_STATE_H

#include <Box2D/Box2D.h>

namespace Purity
{
    struct EntityState
    {
        void update(const b2Body * body);

        b2Vec2 position;
        float32 angle;
    };
}

#endif // ENTITY_STATE_H
