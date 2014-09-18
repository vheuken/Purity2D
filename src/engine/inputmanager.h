#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <queue>
#include "../framework/system/vector2.h"
#include "../framework/system/event.h"

namespace Purity
{
    class Window;

    class InputManager
    {
    public:
        InputManager(Window* window, std::queue<Event>* inputQueue);

        void update();

    private:
        Window* mWindow;
        std::queue<Event>* mInputQueue;

        bool mModeLock;

        Vector2i mWindowPos;
        Vector2u mWindowSize;
        bool mMustHandleWindowResize;
        void handleWindowResize();
    };
}

#endif // INPUT_MANAGER_H
