#ifndef MOVABLE_OBJECT_H
#define MOVABLE_OBJECT_H

#include <luabind/luabind.hpp>
#include "object.h"

namespace Purity
{
    class MovableObject : public Object
    {
    public:
        MovableObject(const Tmx::Object* object, b2World* world);

        void applyLinearImpulse(float x, float y);
        void setLinearVelocity(float x, float y);
        float getLinearVelocityX() const;
        float getLinearVelocityY() const;

        static luabind::scope luaBindings();
    };
}

#endif // MOVABLE_OBJECT_H