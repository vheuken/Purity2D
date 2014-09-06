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

        void update(Scene* scene);

    private:
        Window* mWindow;

        void run();
    };
}

#endif // RENDER_SYSTEM_H
