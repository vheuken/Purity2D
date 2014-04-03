#include "view.h"

Purity::View::View(const Vector2f& center, const Vector2f& size)
: mCenter(center),
  mSize(size)
{
}

void Purity::View::setCenter(const Vector2f& center)
{
    mCenter = center;
}

void Purity::View::setSize(const Vector2f& size)
{
    mSize = size;
}

void Purity::View::setViewport(const Purity::Rect& viewportRect)
{
	mViewport = viewportRect;
}

Purity::Rect Purity::View::getViewport() const
{
	return mViewport;
}
