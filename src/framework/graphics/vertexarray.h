#ifndef PURITY_VERTEX_ARRAY_H
#define PURITY_VERTEX_ARRAY_H

#include <vector>
#include "vertex.h"

namespace Purity
{
    class VertexArray
    {
    public:
        VertexArray();

        unsigned int getVertexCount() const;

        Vertex& operator[](unsigned int index);
        const Vertex& operator[](unsigned int index) const;

        void append(const Vertex& vertex);

    private:
        std::vector<Vertex> mVertexList;
    };
}

#endif // PURITY_VERTEX_ARRAY_H
