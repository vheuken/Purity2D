#ifndef PURITY_BUTTON_H
#define PURITY_BUTTON_H

#include <functional>
#include "../graphics/drawable.h"
#include "../graphics/rect.h"

namespace Purity
{
    class Button : protected Drawable
    {
    public:
        Button(const Rect& rect);

        template <typename Functor>
        bool isMouseOver(const Vector2i& mousePos, Functor onClick);

        virtual void draw(RenderTarget& target) const;

    private:
        Rect mRect;
    };

    template <typename Functor>
    bool Button::isMouseOver(const Purity::Vector2i& mousePos, Functor onClick)
    {
        if (mousePos.x >= mRect.position.x &&
            mousePos.y >= mRect.position.y &&
            mousePos.x <= (mRect.position.x + mRect.width) &&
            mousePos.y <= (mRect.position.y + mRect.height))
        {
            onClick();
            return true;
        }
        return false;
    }
}



#endif // PURITY_BUTTON_H
