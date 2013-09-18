#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include <string>
#include <queue>
#include <memory>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>
#include <luabind/luabind.hpp>
#include "scene.h"
#include "luamanager.h"

namespace Purity
{
    const float32 TIME_STEP = 1.0f / 120.0f;
    const int32 VELOCITY_ITERATIONS = 6;
    const int32 POSITION_ITERATIONS = 2;

    const b2Vec2 GRAVITY(0.0, 15);

    class PhysicsSystem
    {
    public:
        PhysicsSystem(std::queue<sf::Event>* inputQueue);

        void update(Scene* scene);

    private:
        sf::Clock mFrameTimer;
        unsigned int mLastTime;
        unsigned int mFrameTimeMilleseconds;
        std::unique_ptr<b2World> mWorld;
        Scene* mCurrentScene;
	    std::queue<sf::Event>* mInputQueue;

	    void step();
	    void handleInput();
		void runUpdateScripts();
    };
}

#endif // PHYSICS_SYSTEM_H
