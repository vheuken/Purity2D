#include "window.h"
#include <iostream>

#include <SDL.h>

#include "../system/configuration.h"

Purity::Window::Window(int width, int height, std::string title, ViewportType viewportType)
: mWindowManipulator(this),
  mViewportType(viewportType),
  mIsBorderless(Configuration::getInstance()->getBool("window", "borderless", false)),
  mCursorLock(Configuration::getInstance()->getBool("window", "cursor_lock", true)),
  mContentMode(true)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
    }

    int flags = 0;

    if (mIsBorderless)
    {
        flags = SDL_WINDOW_BORDERLESS;
    }
    else
    {
        flags = SDL_WINDOW_RESIZABLE;
    }

    mInternalWindow = SDL_CreateWindow(title.c_str(),
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       width,
                                       height,
                                       flags);

    if (mInternalWindow == nullptr)
    {
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
    }

    mRenderer = SDL_CreateRenderer(mInternalWindow, -1, SDL_RENDERER_ACCELERATED);

    if (mRenderer == nullptr)
    {
        std::cerr << "Could not create renderer: " << SDL_GetError() << std::endl;
    }

    if (mCursorLock)
    {
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }
}

Purity::Window::~Window()
{
    SDL_Quit();
}


void Purity::Window::setView(const Purity::View& view)
{
    mView = view;
}


const Purity::View& Purity::Window::getView() const
{
    return mView;
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

bool Purity::Window::pollEvent(Purity::Event& event)
{
    SDL_Event sdlEvent;
    bool ret = SDL_PollEvent(&sdlEvent);

    event = sdlEvent;

    return ret;
}

bool Purity::Window::isOpen() const
{
    return mInternalWindow;
}

bool Purity::Window::isContentMode() const
{
    return mContentMode;
}

void Purity::Window::toggleMode()
{
    if (isContentMode())
    {
        mContentMode = false;

        if (mCursorLock)
        {
            SDL_SetRelativeMouseMode(SDL_FALSE);
        }
    }
    else
    {
        mContentMode = true;

        if (mCursorLock)
        {
            SDL_SetRelativeMouseMode(SDL_TRUE);
        }
    }
}

void Purity::Window::close()
{
    SDL_DestroyWindow(mInternalWindow);
    mInternalWindow = nullptr;
}

void Purity::Window::manipulateWindow()
{
    if (mIsBorderless && !isContentMode())
    {
        mWindowManipulator.manipulateWindow();
    }
}

void Purity::Window::gainFocus()
{
    mIsInputFocused = true;
}

void Purity::Window::loseFocus()
{
    mIsInputFocused = false;
}

void Purity::Window::display()
{
    if (mIsInputFocused == false)
    {
        SDL_Rect rect;

        rect.w = getSize().x;
        rect.h = getSize().y;
        rect.x = 0;
        rect.y = 0;

        SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(mRenderer, 128, 128, 128, 200);
        SDL_RenderFillRect(mRenderer, &rect);
    }

    SDL_RenderPresent(mRenderer);
}
