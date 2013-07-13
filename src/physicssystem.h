#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include <memory>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>
#include "scene.h"

namespace Purity
{
    const float32 TIME_STEP = 1.0f / 120.0f;
    const int32 VELOCITY_ITERATIONS = 6;
    const int32 POSITION_ITERATIONS = 2;

    const b2Vec2 GRAVITY(0.0, 15);

    class PhysicsSystem
    {
    public:
        PhysicsSystem();

        void update(const Scene* scene);

    private:
        sf::Clock mFrameTimer;
        unsigned int mLastTime;
        unsigned int mFrameTimeMilleseconds;
        std::unique_ptr<b2World> mWorld;
        const Scene* mCurrentScene;

        void step();
    };
}

#endif // PHYSICS_SYSTEM_H