#include "object.h"

Purity::Object::Object(float x, float y)
{
    setX(x);
    setY(y);
}

void Purity::Object::setX(float x)
{
    this->mPositionX = x;
    b2Vec2 pos;
    pos.Set(x, getY());

    mHitboxBody->SetTransform(pos, mHitboxBody->GetAngle());
}

void Purity::Object::setY(float y)
{
    this->mPositionY = y;
    b2Vec2 pos;
    pos.Set(getX(), y);

    mHitboxBody->SetTransform(pos, mHitboxBody->GetAngle());
}

float Purity::Object::getX() const
{
    return mPositionX;
}

float Purity::Object::getY() const
{
    return mPositionY;
}

void Purity::Object::createBody(b2World* world)
{
    mHitboxBody = world->CreateBody(&mHitboxBodyDef);
}

void Purity::Object::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mHitboxShape);
}