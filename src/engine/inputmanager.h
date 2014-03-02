#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <queue>
#include <SFML/Window/Event.hpp>

namespace sf
{
    class RenderWindow;
}

namespace Purity
{
    class InputManager
    {
    public:
        InputManager(sf::RenderWindow* window, std::queue<sf::Event>* inputQueue);

        void update();

    private:
        sf::RenderWindow* mWindow;
        std::queue<sf::Event>* mInputQueue;
    };
}

#endif // INPUT_MANAGER_H
