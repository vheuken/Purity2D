#ifndef PURITY_WINDOW_MANIPULATOR_H
#define PURITY_WINDOW_MANIPULATOR_H

#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>

namespace Purity
{
    class Window;

    class WindowManipulator
    {
    public:
        WindowManipulator(Window* window);

        void manipulateWindow();

    private:
        Window* mWindow;

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

#endif // PURITY_WINDOW_MANIPULATOR_H
