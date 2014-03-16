#ifndef PURITY_RENDER_TARGET_H
#define PURITY_RENDER_TARGET_H

#include "vertexarray.h"
#include "renderer.h"

namespace Purity
{
    class Drawable;

    class RenderTarget : protected Renderer
    {
    public:
        void clear();
        void display();

        void draw(const Drawable& drawable);
        void draw(const VertexArray& vertexArray, const Purity::Vector2f& position);
    };
}

#endif // PURITY_RENDER_TARGET_H
