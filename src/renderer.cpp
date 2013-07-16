#include "renderer.h"

Purity::Renderer::Renderer(sf::RenderWindow* window, bool debugMode)
    : mCurrentScene(nullptr), 
      mWindow(window),
      mRenderThread(&Renderer::run, this),
      mDebugMode(debugMode)
{
    if (mDebugMode)
    {
        initializeDebugInfo();
    }
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
        mCurrentSceneMutex.lock();

        if (mCurrentScene)
        {
            mWindow->clear();
            mWindow->draw(*mCurrentScene);

            if (mDebugMode)
            {
                drawDebugInfo();
            }

            mWindow->display();
        }

        mCurrentSceneMutex.unlock();
    }
}

void Purity::Renderer::drawDebugInfo()
{
    sf::Text debugText;
    sf::Vector2f textPos;
    std::ostringstream convert;
    int textSize = 18;
    const sf::View view = mWindow->getView();

    textPos.x = view.getCenter().x - view.getSize().x/2;
    textPos.x = view.getCenter().y - view.getSize().y/2;

    debugText.setPosition(textPos);
    debugText.setFont(mDebugFont);
    debugText.setColor(sf::Color::Red);
    debugText.setCharacterSize(textSize);

    debugText.setString("Debug:");

    mWindow->draw(debugText);
    debugText.move(0, textSize);
    convert << calculateFPS();
    debugText.setString("FPS: " + convert.str());

    mWindow->draw(debugText);
}

void Purity::Renderer::initializeDebugInfo()
{
    mDebugFont.loadFromFile("orbitron.ttf");
}

int Purity::Renderer::calculateFPS()
{
    static sf::Clock frameTimer;
    static int fps = 0;
    static unsigned int frameCounter = 0;

    frameCounter++;

    if (frameTimer.getElapsedTime().asSeconds() >= 1)
    {
        frameTimer.restart();
        fps = frameCounter;
        frameCounter = 0;
    }

    return fps;
}