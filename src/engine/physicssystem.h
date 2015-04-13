#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include <queue>
#include <memory>
#include <Box2D/Box2D.h>

#include "subsystemable.h"
#include "../framework/network/networkaction.h"
#include "../framework/system/timer.h"
#include "../framework/system/event.h"

namespace Purity
{
const float32 TIME_STEP = 1.0f / 120.0f;
const int32 VELOCITY_ITERATIONS = 6;
const int32 POSITION_ITERATIONS = 2;

const b2Vec2 GRAVITY(0.0, 15);

class PhysicsSystem : public SubSystemable
{
public:
    PhysicsSystem(std::queue<Event>* inputQueue, std::queue<NetworkAction>* serverActionQueue);

    void update(Scene* scene);

    b2World* getWorld() const;

private:
    Timer mFrameTimer;
    unsigned int mLastTime;
    unsigned int mFrameTimeMilleseconds;
    std::unique_ptr<b2World> mWorld;

    std::queue<Event>* mInputQueue;
    std::queue<NetworkAction>* mServerActionQueue;

    void step();
    void handleInput();
    void handleServerActions();
    void runUpdateScripts();
};
}

#endif // PHYSICS_SYSTEM_H
