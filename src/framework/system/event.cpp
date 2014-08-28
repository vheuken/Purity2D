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
