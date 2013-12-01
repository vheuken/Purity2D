#ifndef RENDERER_H
#define RENDERER_H

#include <thread>
#include <mutex>

namespace sf
{
    class RenderWindow;
}

namespace Purity
{
    class Scene;

    class Renderer
    {
    public:
        Renderer(sf::RenderWindow* window);
        ~Renderer();

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