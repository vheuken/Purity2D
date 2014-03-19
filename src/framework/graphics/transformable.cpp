#include "transformable.h"

void Purity::Transformable::setPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}


void Purity::Transformable::setPosition(const Vector2i& position)
{
    mPosition = position;
}

Purity::Vector2i Purity::Transformable::getPosition() const
{
    return mPosition;
}
