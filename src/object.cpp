#include "object.h"

void Purity::Object::createBody(b2World* world)
{
    hitboxBody = world->CreateBody(&hitboxBodyDef);
}

void Purity::Object::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(visibleHitbox);
}