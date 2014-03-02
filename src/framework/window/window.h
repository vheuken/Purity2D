#ifndef PURITY_WINDOW_H
#define PURITY_WINDOW_H

#include <string>
#include <SFML/Graphics.hpp>

#include "windowmanipulator.h"

namespace Purity
{
    const unsigned int STRETCHABLE_BORDER_PIXELS = 50;

    class Window
    {
    public:
        Window(int width, int height, std::string title);

        void clear();
        void draw(const sf::Drawable& drawable);
        void display();

        void setView(const sf::View& view);
        const sf::View& getView() const;

        void setSize(const sf::Vector2u& size);
        sf::Vector2u getSize() const;

        void setPosition(const sf::Vector2i& position);
        sf::Vector2i getPosition() const;

        bool pollEvent(sf::Event& event);

        void setActive(bool active);
        bool isOpen() const;

        void close();

        void manipulateWindow();

        const sf::Window& getInternalWindow() const;

    private:
        sf::RenderWindow mInternalWindow;

        WindowManipulator mWindowManipulator;
    };
}

#endif // PURITY_WINDOW_H
