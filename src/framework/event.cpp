#include "event.h"

unsigned int Purity::Event::getType() const
{
    return static_cast<unsigned int>(mEvent.type);
}
