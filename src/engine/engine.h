#ifndef ENGINE_H
#define ENGINE_H

#include <queue>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "scenemanager.h"
#include "renderer.h"
#include "physicssystem.h"
#include "inputmanager.h"
#include "networksystem.h"
#include "commandlinearguments.h"

namespace luabind
{
    struct scope;
}

namespace Purity
{
    class Engine
    {
    public:
        void initialize(CommandLineArguments commandLineArguments);
        void run();
        void cleanup();

        sf::View getView();
        void setView(const sf::View & view);

        static luabind::scope luaBindings();

    private:
        std::unique_ptr<sf::RenderWindow> mWindow;
        std::unique_ptr<Renderer> mRenderer;
        std::unique_ptr<SceneManager> mSceneManager;
        std::unique_ptr<PhysicsSystem> mPhysicsSystem;
        std::unique_ptr<InputManager> mInputManager;
        std::unique_ptr<NetworkSystem> mNetworkSystem;

	    std::unique_ptr<std::queue<sf::Event> > mInputQueue;
        std::unique_ptr<std::queue<NetworkAction> > mServerActionQueue;
        
        CommandLineArguments mProgramOptions;

        void initializeWindow();
        void initializeRenderer();
        void initializeSceneManager();
        void initializePhysicsSystem();
        void initializeInputManager();
        void initializeNetworkSystem();
    };

}

#endif // ENGINE_H
