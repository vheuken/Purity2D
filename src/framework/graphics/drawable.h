// this was ganked from SFML, I just changed the namespace

#ifndef PURITY_DRAWABLE_H
#define PURITY_DRAWABLE_H

#include "rendertarget.h"

namespace Purity
{
    //class RenderTarget;

    class Drawable
    {
    protected:
        friend class RenderTarget;
        virtual void draw(RenderTarget& target) const = 0;
    };
}

#endif // PURITY_DRAWABLE_H
