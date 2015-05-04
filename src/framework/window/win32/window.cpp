#include "window.h"

#include <windows.h>
#include <SDL_syswm.h>

Purity::Win32Window::Win32Window(int width,
                                 int height,
                                 const std::string& title,
                                 ViewportType viewportType)
    : Window(width, height, title, viewportType)
{
}

void Purity::Win32Window::maximize()
{
    RECT workArea;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);

    SDL_SysWMinfo info;
    SDL_GetWindowWMInfo(mInternalWindow, &info);
    APPBARDATA appBarData;
    appBarData.cbSize = sizeof(APPBARDATA);
    appBarData.hWnd = info.info.win.window;
    SHAppBarMessage(ABM_GETTASKBARPOS, &appBarData);

    // bottom
    if (appBarData.rc.top > appBarData.rc.left)
    {
        setPosition(Vector2i(0, 0));
    }
    // left
    else if (appBarData.rc.top == appBarData.rc.left && appBarData.rc.bottom > appBarData.rc.right)
    {
        setPosition(Vector2i(appBarData.rc.right, 0));
    }
    // top
    else if (appBarData.rc.top == appBarData.rc.left && appBarData.rc.bottom < appBarData.rc.right)
    {
        setPosition(Vector2i(0, appBarData.rc.bottom));
    }
    // right
    else
    {
        setPosition(Vector2i(0, 0));
    }

    setSize(Vector2u(workArea.right - workArea.left, workArea.bottom - workArea.top));
}
