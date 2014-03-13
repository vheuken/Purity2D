#include "rendersystem.h"

#include <iostream>
#include <sstream>

#include "../framework/window/window.h"
#include "../framework/scene.h"

Purity::RenderSystem::RenderSystem(Purity::Window* window)
    : AbstractSystem(),
      mWindow(window)
{
}

void Purity::RenderSystem::update(Scene* scene)
{
    if (scene != mCurrentScene)
    {
        mCurrentScene = scene;
    }

    run();
}

void Purity::RenderSystem::run()
{
    float fps, currentTime;
    sf::Clock timer;
    float lastTime = 0;

    currentTime = timer.restart().asSeconds();

    if (mCurrentScene)
    {
        mWindow->clear();
        //mWindow->draw(*mCurrentScene);
        mWindow->display();
    }

    fps = 1.f / (currentTime);
    lastTime = currentTime;
    //std::cout << "FPS: " << fps << std::endl;
}
