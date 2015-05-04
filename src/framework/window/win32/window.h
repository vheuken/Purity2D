#ifndef PURITY_WINDOWS_WINDOW_H
#define PURITY_WINDOWS_WINDOW_H

#include "../window.h"

namespace Purity
{
class Win32Window : public Window
{
public:
    Win32Window(int width,
                int height,
                const std::string& title,
                ViewportType viewportType = ViewportType::CENTER);

    void maximize();
};
}

#endif // PURITY_WINDOWS_WINDOW_H
