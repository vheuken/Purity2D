#ifndef PURITY_RENDERER_H
#define PURITY_RENDERER_H

struct SDL_Renderer;

namespace Purity
{
    class Renderer
    {
    protected:
        static SDL_Renderer* sRenderer;
    };
}

#endif // PURITY_RENDERER_H
