#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <queue>

union SDL_Event;

namespace Purity
{
    class Window;

    class InputManager
    {
    public:
        InputManager(Window* window, std::queue<SDL_Event*>* inputQueue);

        void update();

    private:
        Window* mWindow;
        std::queue<SDL_Event*>* mInputQueue;
    };
}

#endif // INPUT_MANAGER_H
