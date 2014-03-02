#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <queue>
#include <SFML/Window/Event.hpp>

namespace Purity
{
    class Window;

    class InputManager
    {
    public:
        InputManager(Window* window, std::queue<sf::Event>* inputQueue);

        void update();

    private:
        Window* mWindow;
        std::queue<sf::Event>* mInputQueue;
    };
}

#endif // INPUT_MANAGER_H
