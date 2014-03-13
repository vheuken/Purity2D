#include "window.h"
#include <iostream>

#include <SDL.h>

Purity::Window::Window(int width, int height, std::string title)
: mWindowManipulator(this)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
    }

    mInternalWindow = SDL_CreateWindow(title.c_str(),
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       width,
                                       height,
                                       0);

    if (mInternalWindow == nullptr)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    }

    mRenderer = SDL_CreateRenderer(mInternalWindow, -1, 0);

    if (mRenderer == nullptr)
    {
        std::cout << "Could not create renderer: " << SDL_GetError() << std::endl;
    }

    SDL_SetWindowBrightness(mInternalWindow, 1.0);
}

Purity::Window::~Window()
{
    SDL_Quit();
}

void Purity::Window::setView(const sf::View& view)
{
    //mInternalWindow.setView(view);
}

const sf::View& Purity::Window::getView() const
{
    //return mInternalWindow.getView();
}

void Purity::Window::setSize(const Vector2u& size)
{
    SDL_SetWindowSize(mInternalWindow, size.x, size.y);
}

Purity::Vector2u Purity::Window::getSize() const
{
    int w, h;

    SDL_GetWindowSize(mInternalWindow, &w, &h);

    return Vector2u(static_cast<unsigned int>(w), static_cast<unsigned int>(h));
}

void Purity::Window::setPosition(const Vector2i& position)
{
    SDL_SetWindowPosition(mInternalWindow, position.x, position.y);
}

Purity::Vector2i Purity::Window::getPosition() const
{
    int x, y;

    SDL_GetWindowPosition(mInternalWindow, &x, &y);

    return Vector2i(x, y);
}

bool Purity::Window::pollEvent(SDL_Event* event)
{
    return SDL_PollEvent(event);
}

void Purity::Window::setActive(bool active)
{
    //mInternalWindow.setActive(active);
}

bool Purity::Window::isOpen() const
{
    return mInternalWindow;
}

void Purity::Window::close()
{
    SDL_DestroyWindow(mInternalWindow);
    mInternalWindow = nullptr;
}

void Purity::Window::manipulateWindow()
{
    mWindowManipulator.manipulateWindow();
}
