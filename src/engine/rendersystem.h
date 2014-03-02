#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <thread>
#include <mutex>

#include "abstractsystem.h"

namespace Purity
{
    class Window;

    class RenderSystem : public AbstractSystem
    {
    public:
        RenderSystem(Window* window);
        ~RenderSystem();

        void update(Scene* scene);

    private:
        Window* mWindow;

        std::mutex mCurrentSceneMutex;
        std::thread mRenderThread;

        void run();
    };
}

#endif // RENDER_SYSTEM_H
