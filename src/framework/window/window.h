#ifndef PURITY_WINDOW_H
#define PURITY_WINDOW_H

#include <string>
#include <SFML/Graphics.hpp>

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

        void setView(const sf::View &view);
        const sf::View& getView() const;

        bool pollEvent(sf::Event& event);

        void setActive(bool active);
        bool isOpen() const;

        void close();

        void manipulateWindow();

    private:
        sf::RenderWindow mInternalWindow;

        void setWindowFlags();
        bool isMouseOnBorder() const;

        void dragWindow();
        void resizeWindow();
        void setBorderGrabbedFlags();
        sf::Vector2i mLastMousePosRelativeToWindow;

        bool mWindowDrag;
        bool mWindowResize;
        bool mRightBorderGrabbed;
        bool mBottomBorderGrabbed;
        bool mTopBorderGrabbed;
        bool mLeftBorderGrabbed;
    };
}

#endif // PURITY_WINDOW_H
