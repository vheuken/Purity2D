#include "renderer.h"

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "../framework/scene.h"

Purity::Renderer::Renderer(sf::RenderWindow* window)
    : mCurrentScene(nullptr), 
      mWindow(window),
      mRenderThread(&Renderer::run, this)
{
}

Purity::Renderer::~Renderer()
{
    mRenderThread.join();
}

void Purity::Renderer::update(Scene* scene)
{
    if (scene != mCurrentScene)
    {
        mCurrentSceneMutex.lock();

        mCurrentScene = scene;

        mCurrentSceneMutex.unlock();
    }
}

void Purity::Renderer::run()
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
        std::cout << "FPS: " << fps << std::endl;
    }
}