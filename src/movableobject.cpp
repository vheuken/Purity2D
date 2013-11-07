#include "movableobject.h"

#include <luabind/luabind.hpp>

Purity::MovableObject::MovableObject(const Tmx::Object* object, b2World* world)
    : Object(object, world)
{
    mHitboxBody->SetType(b2_dynamicBody);
}


void Purity::MovableObject::applyLinearImpulse(float x, float y)
{
    b2Vec2 force;
    force.Set(x, y);
    mHitboxBody->ApplyLinearImpulse(force, b2Vec2(0,0)); 
}

void Purity::MovableObject::setLinearVelocity(float x, float y)
{
    b2Vec2 force;
    force.Set(x,y);
    mHitboxBody->SetLinearVelocity(force);
}

float Purity::MovableObject::getLinearVelocityY() const
{
    return mHitboxBody->GetLinearVelocity().y;
}


float Purity::MovableObject::getLinearVelocityX() const
{
    return mHitboxBody->GetLinearVelocity().x;
}

luabind::scope Purity::MovableObject::luaBindings()
{
    return luabind::class_<MovableObject, Object>("MovableObject")
        .def("applyLinearImpulse", &MovableObject::applyLinearImpulse)
        .def("setLinearVelocity",  &MovableObject::setLinearVelocity)
        .def("getLinearVelocityX", &MovableObject::getLinearVelocityX)
        .def("getLinearVelocityY", &MovableObject::getLinearVelocityY)
        .def("getX", &Object::getX)
        .def("getY", &Object::getY)
    ;
}