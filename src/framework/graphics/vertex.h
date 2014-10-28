#ifndef PURITY_VERTEX_H
#define PURITY_VERTEX_H

#include "../system/vector2.h"

namespace Purity
{
class Vertex
{
public:
    Vertex() = default;
    Vertex(const Vector2i& pos);

    Vector2i position;
    Vector2i texCoords;
};
}

#endif // PURITY_VERTEX_H
