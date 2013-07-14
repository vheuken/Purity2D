#include "movableobject.h"

Purity::MovableObject::MovableObject(float x, float y, b2World* world)
    : Object(x, y, world)
{

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

