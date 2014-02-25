#ifndef MOVABLE_ENTITY_H
#define MOVABLE_ENTITY_H

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
        MovableEntity(const Tmx::Object* object, b2World* world, const sf::Texture * texture);

        void applyLinearImpulse(float x, float y);
        void setLinearVelocity(float x, float y);
        float getLinearVelocityX() const;
        float getLinearVelocityY() const;

        static luabind::scope luaBindings();
    };
}

#endif // MOVABLE_ENTITY_H