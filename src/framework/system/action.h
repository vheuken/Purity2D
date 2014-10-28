#ifndef PURITY_ACTION_H
#define PURITY_ACTION_H

#include "event.h"

namespace Purity
{
struct Action
{
    bool state = false;
    Event activateEvent;
    Event deactivateEvent;
};
}

#endif // PURITY_ACTION_H
