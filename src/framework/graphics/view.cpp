#include "view.h"

Purity::View::View(const Purity::Rect& viewportRect)
	: mViewport(viewportRect)
{
}

void Purity::View::setCenter(const Vector2i& center)
{
}

void Purity::View::setSize(const Vector2i& size)
{
}

void Purity::View::setViewport(const Purity::Rect& viewportRect)
{
	mViewport = viewportRect;
}

Purity::Rect Purity::View::getViewport() const
{
	return mViewport;
}
