#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <queue>

#include "../framework/system/event.h"
#include "../framework/system/actionmanager.h"

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
        ActionManager mActionManager;
    };
}

#endif // INPUT_MANAGER_H
