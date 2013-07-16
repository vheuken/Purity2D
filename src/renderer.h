#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "scene.h"

namespace Purity
{
    class Renderer
    {
    public:
        Renderer(sf::RenderWindow* window);

        void update(Scene* scene);

    private:
        sf::RenderWindow* mWindow;
        Scene* mCurrentScene;
        std::mutex mCurrentSceneMutex;
        std::thread mRenderThread;

        void run();
    };
}

#endif // RENDERER_H