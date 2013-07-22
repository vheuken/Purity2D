#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <TmxParser/Tmx.h>
#include "object.h"
#include "movableobject.h"

namespace Purity
{
    class ObjectManager
    {
    public:
        ObjectManager(const Tmx::Map* tmxMap);
    };
}

#endif // OBJECT_MANAGER_H