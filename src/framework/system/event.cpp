#include "event.h"

Purity::Event& Purity::Event::operator=(const SDL_Event& sdlEvent)
{
    switch(sdlEvent.type)
    {
    case SDL_KEYDOWN:
        convertKeyPressedEvent(*this, sdlEvent);
        break;

    case SDL_KEYUP:
        convertKeyReleasedEvent(*this, sdlEvent);
        break;

    case SDL_WINDOWEVENT:
        if (sdlEvent.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            this->type = Event::Closed;
        }
        switch (sdlEvent.window.event)
        {
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            this->type = Event::FocusGained;
            break;

        case SDL_WINDOWEVENT_FOCUS_LOST:
            this->type = Event::FocusLost;
            break;

        case SDL_WINDOWEVENT_RESIZED:
            this->type = Event::Resized;
            break;
        }
        break;

    case SDL_FINGERDOWN:
        this->type = Event::TouchBegan;
        convertTouchEvent(*this, sdlEvent);
        break;

    case SDL_FINGERMOTION:
        this->type = Event::TouchMoved;
        convertTouchEvent(*this, sdlEvent);
        break;

    case SDL_FINGERUP:
        this->type = Event::TouchEnded;
        convertTouchEvent(*this, sdlEvent);
        break;
    }

    return *this;
}

void Purity::convertKeyPressedEvent(Purity::Event& event, const SDL_Event& sdlEvent)
{
    event.type = Event::KeyPressed;
    event.keyEvent.code = sdlEvent.key.keysym.sym;
}

void Purity::convertKeyReleasedEvent(Purity::Event& event, const SDL_Event& sdlEvent)
{
    event.type = Event::KeyReleased;
    event.keyEvent.code = sdlEvent.key.keysym.sym;
}

void Purity::convertTouchEvent(Purity::Event& event, const SDL_Event& sdlEvent)
{
    event.touchEvent.x = sdlEvent.tfinger.x;
    event.touchEvent.y = sdlEvent.tfinger.y;
    event.touchEvent.dx = sdlEvent.tfinger.dx;
    event.touchEvent.dy = sdlEvent.tfinger.dy;
    event.touchEvent.pressure = sdlEvent.tfinger.pressure;
}

