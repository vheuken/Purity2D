#ifndef PURITY_RENDER_TARGET_H
#define PURITY_RENDER_TARGET_H

struct SDL_Renderer;

namespace Purity
{
    class Drawable;

    class RenderTarget
    {
    public:
        RenderTarget();

        void clear();
        void draw(const Drawable& drawable);
        void display();

    protected:
        SDL_Renderer* mRenderer;
    };
}

#endif // PURITY_RENDER_TARGET_H
