#include "object.h"

Purity::Object::Object(float x, float y)
{
    setX(x);
    setY(y);
}

void Purity::Object::setX(float x)
{
    this->mPositionX = x;
}

void Purity::Object::setY(float y)
{
    this->mPositionY = y;
}


void Purity::Object::createBody(b2World* world)
{
    mHitboxBody = world->CreateBody(&mHitboxBodyDef);
}

void Purity::Object::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mHitboxShape);
}