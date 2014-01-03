#include "entitystate.h"

void Purity::EntityState::update(const b2Body *body)
{
    position = body->GetPosition();
    angle = body->GetAngle();
}
