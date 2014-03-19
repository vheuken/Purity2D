#ifndef PURITY_TRANSFORMABLE_H
#define PURITY_TRANSFORMABLE_H

#include "../system/vector2.h"

namespace Purity
{
    class Transformable
    {
    public:
        void setPosition(int x, int y);
        void setPosition(const Vector2i& position);

        Vector2i getPosition() const;

    private:
        Vector2i mPosition;
    };
}

#endif // PURITY_TRANSFORMABLE_H
