#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <queue>
#include <SFML/Window.hpp>

namespace sf
{
    class RenderWindow;
}

namespace Purity
{
    class Scene;

    class InputManager
    {
    public:
        InputManager(sf::RenderWindow* window, std::queue<sf::Event>* inputQueue);

        void update(Scene* scene);

    private:
        sf::RenderWindow* mWindow;
	    Scene* mCurrentScene;
	    std::queue<sf::Event>* mInputQueue;	
    };
}

#endif // INPUT_MANAGER_H
