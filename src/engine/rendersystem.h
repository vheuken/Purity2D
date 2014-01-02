#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <thread>
#include <mutex>

#include "abstractsystem.h"

namespace sf
{
    class RenderWindow;
}

namespace Purity
{
    class RenderSystem : public AbstractSystem
    {
    public:
        RenderSystem(sf::RenderWindow* window);
        ~RenderSystem();

        void update(Scene* scene);

    private:
        sf::RenderWindow* mWindow;
        
        std::mutex mCurrentSceneMutex;
        std::thread mRenderThread;

        void run();
    };
}

#endif // RENDER_SYSTEM_H
