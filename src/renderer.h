#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "scene.h"

namespace Purity
{
    class Renderer
    {
    public:
        Renderer(sf::RenderWindow* window, bool debugMode);
        ~Renderer();

        void update(Scene* scene);

    private:
        sf::RenderWindow* mWindow;
        Scene* mCurrentScene;
        std::mutex mCurrentSceneMutex;
        std::thread mRenderThread;
        bool mDebugMode;

        void run();
        void drawDebugInfo();
        void initializeDebugInfo();
        int calculateFPS();
        sf::Font mDebugFont;
    };
}

#endif // RENDERER_H