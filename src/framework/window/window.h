#ifndef PURITY_WINDOW_H
#define PURITY_WINDOW_H

#include <string>

#include "windowmanipulator.h"
#include "../system/vector2.h"
#include "../graphics/rendertarget.h"
#include "../graphics/view.h"
#include "../system/event.h"
#include "../gui/button.h"

struct SDL_Window;
struct SDL_Renderer;
union  SDL_Event;

namespace Purity
{
    enum class ViewportType 
    {
        LETTERBOX,
        CENTER,
        STRETCH
    };

    class Window : public RenderTarget
    {
    public:
        Window(int width, int height, std::string title, ViewportType viewportType = ViewportType::CENTER);
        ~Window();

        void setSize(const Vector2u& size);
        Vector2u getSize() const;

        void setPosition(const Vector2i& position);
        Vector2i getPosition() const;

        bool pollEvent(Event& event);

        bool isOpen() const;

        bool isContentMode() const;

        void toggleMode();
        void setWindowMode();
        void setContentMode();

        void maximize();
        void minimize();

        bool isBorderless() const;

        bool isMaximized() const;

        void close();

        void manipulateWindow();

        void handleUIButtons();

        void gainFocus();

        void loseFocus();

        void display();

    private:
        SDL_Window* mInternalWindow;

        WindowManipulator mWindowManipulator;

        ViewportType mViewportType;

        bool mBorderless;

        bool mIsInputFocused;

        bool mCursorLock;

        bool mContentMode;

        Vector2i minimumSize;

        Button mCloseButton;

        void setResizeHandling();
        void setRenderScale();
        void setRenderMaintainAspectRatio();
    };
}

#endif // PURITY_WINDOW_H
