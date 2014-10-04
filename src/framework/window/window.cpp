#include "window.h"
#include <iostream>
#include <functional>
#include <bitset>
#include <SDL.h>

#include "../system/configuration.h"
#include "../input/mouse.h"

#if defined(__ANDROID__) ||  defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
const bool CONTENT_MODE_DEFAULT = true;
#else
const bool CONTENT_MODE_DEFAULT = false;
#endif

Purity::Window::Window(int width, int height, std::string title, ViewportType viewportType)
: mWindowManipulator(this),
  mViewportType(viewportType),
  mBorderless(Configuration::getInstance()->getBool("window", "borderless", false)),
  mCursorLock(Configuration::getInstance()->getBool("window", "cursor_lock", true)),
  mContentMode(CONTENT_MODE_DEFAULT),
  minimumSize(Configuration::getInstance()->getInteger("window", "minimum_size_x", 160),
              Configuration::getInstance()->getInteger("window", "minimum_size_y", 144)),
  mCloseButton(Rect(Vector2i(width-30, 5), 25, 25)),
  mMaximizeButton(Rect(Vector2i(width-60, 5), 25, 25)),
  mMinimizeButton(Rect(Vector2i(width-90, 5), 25, 25))
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
    }

    int flags = 0;

    if (isBorderless())
    {
#ifdef _WIN32
        flags = SDL_WINDOW_BORDERLESS;
#else
        flags = SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE;
#endif
    }
    else
    {
        flags = SDL_WINDOW_RESIZABLE;
    }

#if defined(__ANDROID__) ||  defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
    SDL_DisplayMode mode;

    if (SDL_GetDesktopDisplayMode(0, &mode) != 0)
    {
        std::cerr << "SDL_GetDesktopDisplayMode failed: " << SDL_GetError() << std::endl;
    }

    mInternalWindow = SDL_CreateWindow(title.c_str(),
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       mode.w,
                                       mode.h,
                                       flags);
#else
    mInternalWindow = SDL_CreateWindow(title.c_str(),
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       width,
                                       height,
                                       flags);
#endif
    SDL_SetWindowMinimumSize(mInternalWindow, minimumSize.x, minimumSize.y);

    if (mInternalWindow == nullptr)
    {
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
    }

    mRenderer = SDL_CreateRenderer(mInternalWindow, -1, SDL_RENDERER_ACCELERATED);

    if (mRenderer == nullptr)
    {
        std::cerr << "Could not create renderer: " << SDL_GetError() << std::endl;
    }

    Vector2i viewSize(Configuration::getInstance()->getInteger("window", "view_size_x", 800),
                      Configuration::getInstance()->getInteger("window", "view_size_y", 400));

    mView.setSize(static_cast<Vector2f>(viewSize));

    auto viewportTypeStr = Configuration::getInstance()->getString("window", "viewport_type", "letterbox");


    if (viewportTypeStr == "stretch")
    {
        mViewportType = ViewportType::STRETCH;
    }
    else if (viewportTypeStr == "center")
    {
        mViewportType = ViewportType::CENTER;
    }
    else // default to "letterbox"
    {
        mViewportType = ViewportType::LETTERBOX;
    }

    setWindowMode();
}

Purity::Window::~Window()
{
    SDL_Quit();
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
        setWindowMode();
    }
    else
    {
        setContentMode();
    }
}

void Purity::Window::setWindowMode()
{
    mContentMode = false;

    if (mCursorLock)
    {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
}

void Purity::Window::setContentMode()
{
    mContentMode = true;

    if (mCursorLock)
    {
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }
}

void Purity::Window::maximize()
{
    if (!isMaximized())
    {
        SDL_MaximizeWindow(mInternalWindow);
    }
    else
    {
        SDL_RestoreWindow(mInternalWindow);
    }
}

void Purity::Window::minimize()
{
    SDL_MinimizeWindow(mInternalWindow);
}

bool Purity::Window::isBorderless() const
{
    return mBorderless;
}

bool Purity::Window::isMaximized() const
{
    return (SDL_WINDOW_MAXIMIZED & SDL_GetWindowFlags(mInternalWindow));
}

void Purity::Window::close()
{
    SDL_DestroyWindow(mInternalWindow);
    mInternalWindow = nullptr;
}

void Purity::Window::manipulateWindow()
{
    if (!isContentMode())
    {
        if (isBorderless())
        {
            handleUIButtons();
        }

        if (!isMaximized() && !mMouseOnButtons)
        {
            mWindowManipulator.manipulateWindow();
        }
    }
}

void Purity::Window::handleUIButtons()
{
    std::bitset<3> mask;

    // handle clicks
    mask[0] = mCloseButton.isMouseOver(Mouse::getPosition(*this), std::bind(&Window::close, this));
    mask[1] = mMaximizeButton.isMouseOver(Mouse::getPosition(*this), std::bind(&Window::maximize, this));
    mask[2] = mMinimizeButton.isMouseOver(Mouse::getPosition(*this), std::bind(&Window::minimize, this));

    if (mask.any())
    {
        mMouseOnButtons = true;
    }
    else
    {
        if (!Mouse::isButtonPressed(Mouse::Left))
        {
            mMouseOnButtons = false;
        }
    }

    // window resizes
    auto size = getSize();
    mCloseButton.setRect(Rect(Vector2i(size.x-30, 5), 25, 25));
    mMaximizeButton.setRect(Rect(Vector2i(size.x-60, 5), 25, 25));
    mMinimizeButton.setRect(Rect(Vector2i(size.x-90, 5), 25, 25));
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
    if (mContentMode == false)
    {
        SDL_Rect rect;
        Vector2i size;

        if (mViewportType == ViewportType::LETTERBOX)
        {
            size = static_cast<Vector2i>(getSize());
            SDL_RenderSetLogicalSize(mRenderer, getSize().x, getSize().y);
        }
        else
        {
            size = static_cast<Vector2i>(mView.getSize());
        }

        rect.w = size.x;
        rect.h = size.y;
        rect.x = 0;
        rect.y = 0;


        SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(mRenderer, 128, 128, 128, 200);
        SDL_RenderFillRect(mRenderer, &rect);

        if (isBorderless())
        {
            mCloseButton.draw(*this);
            mMaximizeButton.draw(*this);
            mMinimizeButton.draw(*this);
        }
    }

    setResizeHandling();

    SDL_RenderPresent(mRenderer);
}

void Purity::Window::setResizeHandling()
{
    if (mViewportType == ViewportType::STRETCH)
    {
        setRenderScale();
    }
    else if (mViewportType == ViewportType::LETTERBOX)
    {
        setRenderMaintainAspectRatio();
    }

    // TODO: implement center
}

void Purity::Window::setRenderScale()
{
    auto windowSize = static_cast<Vector2f>(getSize());
    auto viewSize = mView.getSize();

    Vector2f scale;
    scale.x = windowSize.x / viewSize.x;
    scale.y = windowSize.y / viewSize.y;

    SDL_RenderSetScale(mRenderer, scale.x, scale.y);
}

void Purity::Window::setRenderMaintainAspectRatio()
{
    SDL_RenderSetLogicalSize(mRenderer, mView.getSize().x, mView.getSize().y);
}
