#ifndef ENGINE_H
#define ENGINE_H

#include <queue>
#include <memory>

#include "../framework/window/window.h"

#include "scenemanager.h"
#include "rendersystem.h"
#include "physicssystem.h"
#include "inputmanager.h"
#include "networksystem.h"
#include "commandlinearguments.h"

#include <SDL_events.h>

namespace luabind
{
    struct scope;
}

namespace Purity
{
    class Engine
    {
    public:
        Engine(const CommandLineArguments& commandLineArguments);

        void initialize();
        void run();
        void cleanup();

    private:
        std::unique_ptr<Window> mWindow;
        std::unique_ptr<RenderSystem> mRenderSystem;
        std::unique_ptr<SceneManager> mSceneManager;
        std::unique_ptr<PhysicsSystem> mPhysicsSystem;
        std::unique_ptr<InputManager> mInputManager;
        std::unique_ptr<NetworkSystem> mNetworkSystem;

	    std::unique_ptr<std::queue<SDL_Event> > mInputQueue;
        std::unique_ptr<std::queue<NetworkAction> > mServerActionQueue;

        const CommandLineArguments mProgramOptions;

        void initializeWindow();
        void initializeRenderSystem();
        void initializeSceneManager();
        void initializePhysicsSystem();
        void initializeInputManager();
        void initializeNetworkSystem();
    };

}

#endif // ENGINE_H
