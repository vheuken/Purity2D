#ifndef PURITY_EVENT_H
#define PURITY_EVENT_H

#include <SDL.h>

namespace Purity
{
    class Event
    {
    public:
        unsigned int getType() const;
    private:
        SDL_Event mEvent;
    };
}

#endif // PURITY_EVENT_H
