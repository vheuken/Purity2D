#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "scenemanager.h"
#include "renderer.h"

namespace Purity
{

    class Engine
    {
    public:
        void initialize();
        void run();
        void cleanup();

    private:
        std::unique_ptr<sf::RenderWindow> mWindow;
        std::unique_ptr<Renderer> mRenderer;
        std::unique_ptr<SceneManager> mSceneManager;

        void initializeWindow();
        void initializeRenderer();
        void initializeSceneManager();
    };

}

#endif // ENGINE_H