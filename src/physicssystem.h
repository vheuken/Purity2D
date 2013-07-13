#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "scene.h"

namespace Purity
{
    class PhysicsSystem
    {
    public:
        PhysicsSystem();

    private:
        void update(const Scene& scene) const;
    };
}

#endif // PHYSICS_SYSTEM_H