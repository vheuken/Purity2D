#ifndef PURITY_VERTEX_ARRAY_H
#define PURITY_VERTEX_ARRAY_H

#include <vector>
#include "vertex.h"
#include "rect.h"

namespace Purity
{
    class VertexArray
    {
    public:
        unsigned int getVertexCount() const;

        Vertex& operator[](unsigned int index);
        const Vertex& operator[](unsigned int index) const;

        void append(const Vertex& vertex);

        Rect getBounds() const;

    private:
        std::vector<Vertex> mVertexList;

        bool xCompare(const Vertex& a, const Vertex& b) const;
        bool yCompare(const Vertex& a, const Vertex& b) const;
    };
}

#endif // PURITY_VERTEX_ARRAY_H
