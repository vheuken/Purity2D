#include "renderer.h"

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
    mCurrentSceneMutex.lock();

    if (scene != mCurrentScene)
    {
        mCurrentScene = scene;
    }

    mCurrentSceneMutex.unlock();
}

void Purity::Renderer::run()
{
    while (mWindow->isOpen())
    {
        sf::sleep(sf::seconds(1));
        mCurrentSceneMutex.lock();

        if (mCurrentScene)
        {
            mWindow->clear();
            mWindow->draw(*mCurrentScene);
            mWindow->display();
        }

        mCurrentSceneMutex.unlock();
    }
}