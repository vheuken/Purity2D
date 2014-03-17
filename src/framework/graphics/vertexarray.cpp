#include "vertexarray.h"

#include <algorithm>
#include <functional>

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

Purity::Rect Purity::VertexArray::getBounds() const
{
    Rect bounds;

    auto vertexList = mVertexList;

    std::sort(vertexList.begin(), vertexList.end(),
              [](const Vertex& a, const Vertex& b) -> bool
              {
                  return a.position.x < b.position.x;
              });

    std::sort(vertexList.begin(), vertexList.end(),
              [](const Vertex& a, const Vertex& b) -> bool
              {
                  return a.position.y < b.position.y;
              });

    bounds.width = mVertexList[1].position.x - mVertexList[0].position.x;
    bounds.height = mVertexList[2].position.y - mVertexList[0].position.y;

    return std::move(bounds);
}

bool Purity::VertexArray::xCompare(const Purity::Vertex& a, const Purity::Vertex& b) const
{
    return a.position.x < b.position.x;
}

bool Purity::VertexArray::yCompare(const Purity::Vertex& a, const Purity::Vertex& b) const
{
    return a.position.y < b.position.y;
}
