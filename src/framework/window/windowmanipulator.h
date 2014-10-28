#ifndef PURITY_WINDOW_MANIPULATOR_H
#define PURITY_WINDOW_MANIPULATOR_H

#include "../system/vector2.h"

namespace Purity
{
const int STRETCHABLE_BORDER_PIXELS = 30;

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
    Vector2i mWindowResizeOffsetLeftTop;

    bool mWindowDrag;
    bool mWindowResize;
    bool mRightBorderGrabbed;
    bool mLeftBorderGrabbed;
    bool mBottomBorderGrabbed;
    bool mTopBorderGrabbed;
};
}

#endif // PURITY_WINDOW_MANIPULATOR_H
