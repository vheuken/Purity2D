#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <queue>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "scenemanager.h"
#include "renderer.h"
#include "physicssystem.h"
#include "inputmanager.h"

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
        std::unique_ptr<InputManager> mInputManager;
	    std::unique_ptr<std::queue<sf::Event>> mInputQueue;

        void initializeWindow();
        void initializeRenderer();
        void initializeSceneManager();
        void initializePhysicsSystem();
        void initializeInputManager();
    };

}

#endif // ENGINE_H
