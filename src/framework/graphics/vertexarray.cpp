#include "vertexarray.h"

unsigned int Purity::VertexArray::getVertexCount() const
{
    return mVertexList.size();
}

Purity::Vertex& Purity::VertexArray::operator[](unsigned int index)
{
    return mVertexList.at(index);
}

const Purity::Vertex& Purity::VertexArray::operator[](unsigned int index) const
{
    return mVertexList.at(index);
}

void Purity::VertexArray::append(const Purity::Vertex& vertex)
{
    mVertexList.push_back(vertex);
}
