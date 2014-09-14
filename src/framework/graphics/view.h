#ifndef PURITY_VIEW_H
#define PURITY_VIEW_H

#include <SDL.h>

#include "rect.h"

namespace Purity
{
	class View
	{
	public:
		View() = default;
		View(const Vector2f& center, const Vector2f& size);

		void setCenter(const Vector2f& center);
		void setSize(const Vector2f& size);
		
		void setViewport(const Rect& viewportRect);
		Rect getViewport() const;

	private:
		Rect mViewport;

        Vector2f mCenter;
        Vector2f mSize;
    };
}

#endif // PURITY_VIEW_H
