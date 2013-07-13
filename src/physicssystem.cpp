#include "physicssystem.h"

Purity::PhysicsSystem::PhysicsSystem()
{
    mWorld = std::unique_ptr<b2World>(new b2World(GRAVITY));

    mLastTime = 0;
    mFrameTimeMilleseconds = 0;
    mFrameTimer.restart().asMicroseconds();
}

void Purity::PhysicsSystem::update(const Purity::Scene& scene) 
{
    step();
}

void Purity::PhysicsSystem::step()
{
    static float acumulator = 0.0;

    mLastTime = mFrameTimeMilleseconds;
    mFrameTimeMilleseconds = mFrameTimer.getElapsedTime().asMilliseconds();

    acumulator += (mFrameTimeMilleseconds - mLastTime);
    
    while (acumulator >= (TIME_STEP * 1000))
    {
        mWorld->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

        acumulator -= (TIME_STEP * 1000);
    }
}