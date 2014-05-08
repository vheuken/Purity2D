#ifndef MOVABLE_ENTITY_H
#define MOVABLE_ENTITY_H

#include <lua.hpp>

#include "entity.h"

namespace luabind
{
    struct scope;
}

namespace Purity
{
    class MovableEntity : public Entity
    {
    public:
        MovableEntity(const Tmx::Object* object, b2World* world, const Texture * texture);

        void applyLinearImpulse(float x, float y);
        void setLinearVelocity(float x, float y);
        float getLinearVelocityX() const;
        float getLinearVelocityY() const;

        static void luaBindings(lua_State* state);
    };
}

#endif // MOVABLE_ENTITY_H
