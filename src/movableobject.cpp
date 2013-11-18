#include "movableobject.h"

#include <luabind/luabind.hpp>

Purity::MovableEntity::MovableEntity(const Tmx::Object* object, b2World* world)
    : Entity(object, world)
{
    mHitboxBody->SetType(b2_dynamicBody);
}


void Purity::MovableEntity::applyLinearImpulse(float x, float y)
{
    b2Vec2 force;
    force.Set(x, y);
    mHitboxBody->ApplyLinearImpulse(force, b2Vec2(0,0), false); 
}

void Purity::MovableEntity::setLinearVelocity(float x, float y)
{
    b2Vec2 force;
    force.Set(x,y);
    mHitboxBody->SetLinearVelocity(force);
}

float Purity::MovableEntity::getLinearVelocityY() const
{
    return mHitboxBody->GetLinearVelocity().y;
}


float Purity::MovableEntity::getLinearVelocityX() const
{
    return mHitboxBody->GetLinearVelocity().x;
}

luabind::scope Purity::MovableEntity::luaBindings()
{
    return luabind::class_<MovableEntity, Entity>("MovableObject")
        .def("applyLinearImpulse", &MovableEntity::applyLinearImpulse)
        .def("setLinearVelocity",  &MovableEntity::setLinearVelocity)
        .def("getLinearVelocityX", &MovableEntity::getLinearVelocityX)
        .def("getLinearVelocityY", &MovableEntity::getLinearVelocityY)
        .def("getX", &Entity::getX)
        .def("getY", &Entity::getY)
    ;
}