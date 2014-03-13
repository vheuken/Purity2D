#ifndef PURITY_VERTEX_H
#define PURITY_VERTEX_H

#include "../system/vector2.h"

namespace Purity
{
    class Vertex
    {
    public:
        Vertex(const Vector2f& pos);

        Vector2f position;
        Vector2f texCoords;
    };
}

#endif // PURITY_VERTEX_H
