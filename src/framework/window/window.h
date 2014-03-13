#ifndef PURITY_WINDOW_H
#define PURITY_WINDOW_H

#include <string>
#include <SFML/Graphics.hpp>

#include "windowmanipulator.h"
#include "../system/vector2.h"
#include "../graphics/rendertarget.h"


struct SDL_Window;
struct SDL_Renderer;
union  SDL_Event;

namespace Purity
{
    const unsigned int STRETCHABLE_BORDER_PIXELS = 50;

    class Window : public RenderTarget
    {
    public:
        Window(int width, int height, std::string title);
        ~Window();

        void setView(const sf::View& view);
        const sf::View& getView() const;

        void setSize(const Vector2u& size);
        Vector2u getSize() const;

        void setPosition(const Vector2i& position);
        Vector2i getPosition() const;

        bool pollEvent(SDL_Event* event);

        void setActive(bool active);
        bool isOpen() const;

        void close();

        void manipulateWindow();

    private:
        SDL_Window* mInternalWindow;

        WindowManipulator mWindowManipulator;
    };
}

#endif // PURITY_WINDOW_H
