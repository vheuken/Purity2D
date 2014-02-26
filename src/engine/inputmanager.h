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
    const unsigned int STRETCHABLE_BORDER_PIXELS = 50;

    class InputManager
    {
    public:
        InputManager(sf::RenderWindow* window, std::queue<sf::Event>* inputQueue);

        void update();

    private:
        sf::RenderWindow* mWindow;
        std::queue<sf::Event>* mInputQueue;

        bool isWindowManipulationEvent(const sf::Event& event) const;
        void manipulateWindow(const sf::Event& event);
        void setWindowFlags(const sf::Event& event);
        bool isMouseOnBorder() const;

        void dragWindow();
        void resizeWindow();

        sf::Vector2i mLastMousePosRelativeToWindow;

        bool mWindowDrag;
        bool mWindowResize;
    };
}

#endif // INPUT_MANAGER_H
