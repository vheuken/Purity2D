#ifndef PURITY_RENDER_TARGET_H
#define PURITY_RENDER_TARGET_H

#include "vertexarray.h"
#include "view.h"
#include "../spritesheet.h"

struct SDL_Renderer;

namespace Purity
{
    class Drawable;

    class RenderTarget
    {
    public:
        void setView(const View& view);
        const View& getView() const;

        void clear();
        void display();

        void draw(const Drawable& drawable);
        void draw(const Purity::Rect& rectToDraw);
        void draw(const SpriteSheet* spriteSheet, unsigned short animationFrame, const Purity::Vector2f& position);

    protected:
        SDL_Renderer* mRenderer;

    private:
        View mView;
    };
}

#endif // PURITY_RENDER_TARGET_H
