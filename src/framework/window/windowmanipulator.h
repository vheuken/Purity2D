#ifndef PURITY_WINDOW_MANIPULATOR_H
#define PURITY_WINDOW_MANIPULATOR_H

#include "../system/vector2.h"

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

        Vector2i mLastMousePosRelativeToWindow;
        Vector2i mWindowResizeOffsetRightBottom;

        bool mWindowDrag;
        bool mWindowResize;
        bool mRightBorderGrabbed;
        bool mBottomBorderGrabbed;
        bool mTopBorderGrabbed;
        bool mLeftBorderGrabbed;
    };
}

#endif // PURITY_WINDOW_MANIPULATOR_H
