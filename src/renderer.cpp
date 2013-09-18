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
    if (scene != mCurrentScene)
    {
        mCurrentSceneMutex.lock();

        mCurrentScene = scene;

        mCurrentSceneMutex.unlock();
    }
}

void Purity::Renderer::run()
{
    while (mWindow->isOpen())
    {
        if (mCurrentScene)
        {
            mCurrentSceneMutex.lock();

            mWindow->clear();
            mWindow->draw(*mCurrentScene);
            mWindow->display();

            mCurrentSceneMutex.unlock();
        }
    }
}