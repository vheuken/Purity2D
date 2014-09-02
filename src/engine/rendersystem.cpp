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
        mCurrentScene = scene;
    }
}

void Purity::RenderSystem::run()
{
    mWindow->setActive(true);

    while (mWindow->isOpen())
    {
        std::cout << "window is open!" << std::endl;
        if (mCurrentScene)
        {
            std::cout << "Scene exists!" << std::endl;
            mWindow->clear();
            mWindow->draw(*mCurrentScene);
            mWindow->display();
        }
    }
}
