#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SFML/Graphics.hpp>
#include "scene.h"

namespace Purity
{
    class InputManager
    {
    public:
        InputManager(sf::RenderWindow* window);

        void update(Scene* scene);

    private:
        sf::RenderWindow* mWindow;
    };
}

#endif // INPUT_MANAGER_H