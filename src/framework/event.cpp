#include "event.h"

Purity::EventType Purity::Event::getType() const
{
    return static_cast<EventType>(mEvent.type);
}
