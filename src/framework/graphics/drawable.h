// this was ganked from SFML, I just changed the namespace

#ifndef PURITY_DRAWABLE_H
#define PURITY_DRAWABLE_H

class SDL_Renderer;

namespace Purity
{

    class Drawable
    {
    protected:
        friend class RenderTarget;

        virtual void draw(SDL_Renderer* target) const = 0;
    };
}

#endif // PURITY_DRAWABLE_H
