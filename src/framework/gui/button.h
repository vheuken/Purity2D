#ifndef PURITY_BUTTON_H
#define PURITY_BUTTON_H

#include <functional>
#include "../input/mouse.h"
#include "../graphics/drawable.h"
#include "../graphics/rect.h"

namespace Purity
{
    class Button : protected Drawable
    {
    public:
        Button(const Rect& rect);

        void setRect(const Rect& rect);

        template <typename Functor>
        bool isMouseOver(const Vector2i& mousePos, Functor onClick);

        virtual void draw(RenderTarget& target) const;

    private:
        Rect mRect;

        bool mMouseDown = false;
    };

    template <typename Functor>
    bool Button::isMouseOver(const Purity::Vector2i& mousePos, Functor onClick)
    {
        if (mousePos.x >= mRect.position.x &&
            mousePos.y >= mRect.position.y &&
            mousePos.x <= (mRect.position.x + mRect.width) &&
            mousePos.y <= (mRect.position.y + mRect.height))
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                mMouseDown = true;
            }
            else if (!Mouse::isButtonPressed(Mouse::Left))
            {
                if (mMouseDown == true)
                {
                    onClick();
                    mMouseDown = false;
                }
            }
            return true;
        }

        mMouseDown = false;
        return false;
    }
}



#endif // PURITY_BUTTON_H
