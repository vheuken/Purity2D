#include "rendersystem.h"

#include <iostream>
#include <sstream>

#include "../framework/window/window.h"
#include "../framework/scene.h"

Purity::RenderSystem::RenderSystem(Purity::Window* window)
    : AbstractSystem(),
      mWindow(window),
      mRenderThread(&RenderSystem::run, this)
{
}

Purity::RenderSystem::~RenderSystem()
{
    mRenderThread.join();
}

void Purity::RenderSystem::update(Scene* scene)
{
    if (scene != mCurrentScene)
    {
        mCurrentSceneMutex.lock();

        mCurrentScene = scene;

        mCurrentSceneMutex.unlock();
    }
}

void Purity::RenderSystem::run()
{
    float fps, currentTime;
    sf::Clock timer;
    float lastTime = 0;

    while (mWindow->isOpen())
    {
        currentTime = timer.restart().asSeconds();

        if (mCurrentScene)
        {
            mCurrentSceneMutex.lock();

            mWindow->clear();
            mWindow->draw(*mCurrentScene);
            mWindow->display();

            mCurrentSceneMutex.unlock();
        }

        fps = 1.f / (currentTime);
        lastTime = currentTime;
        //std::cout << "FPS: " << fps << std::endl;
    }
}
