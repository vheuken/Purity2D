#include <SDL.h>

#include "rect.h"

namespace Purity
{
	class View
	{
	public:
		View() = default;
		View(const Rect& viewportRect);

		void setCenter(const Vector2i& center);
		void setSize(const Vector2i& size);
		
		void setViewport(const Rect& viewportRect);
		Rect getViewport() const;

	private:
		Rect mViewport;		
    };
}
