#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "scenemanager.h"
#include "renderer.h"
#include "physicssystem.h"

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
        std::unique_ptr<PhysicsSystem> mPhysicsSystem;

        void initializeWindow();
        void initializeRenderer();
        void initializeSceneManager();
        void initializePhysicsSystem();
    };

}

#endif // ENGINE_H