#include "movableentity.h"
#include <LuaBridge.h>
Purity::MovableEntity::MovableEntity(const Tmx::Object* object, b2World* world, const Purity::Texture * texture)
    : Entity(object, world, texture)
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

void Purity::MovableEntity::luaBindings(lua_State* state)
{
    luabridge::getGlobalNamespace(state)
        .beginNamespace("Purity")
            .beginClass <MovableEntity> ("MovableEntity")
                .addFunction("applyLinearImpulse", &MovableEntity::applyLinearImpulse)
                .addFunction("setLinearVelocity",  &MovableEntity::setLinearVelocity)
                .addFunction("getLinearVelocityX", &MovableEntity::getLinearVelocityX)
                .addFunction("getLinearVelocityY", &MovableEntity::getLinearVelocityY)
                .addFunction("getX", &Entity::getX)
                .addFunction("getY", &Entity::getY)
            .endClass()
        .endNamespace();
}

