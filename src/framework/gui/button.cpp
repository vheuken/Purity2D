#include "button.h"

Purity::Button::Button(const Purity::Rect& rect)
    : mRect(rect)
{
}

void Purity::Button::draw(Purity::RenderTarget& target) const
{
    target.draw(mRect);
}
