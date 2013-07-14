#ifndef MOVABLE_OBJECT_H
#define MOBABLE_OBJECT_H

#include "object.h"

namespace Purity
{
    class MovableObject : public Object
    {
    public:
        MovableObject(float x, float y, b2World* world);

        void applyLinearImpulse(float x, float y);
        void setLinearVelocity(float x, float y);
        float getLinearVelocityX() const;
        float getLinearVelocityY() const;
    };
}

#endif // MOVABLE_OBJECT_H