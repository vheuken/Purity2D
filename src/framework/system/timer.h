#ifndef PURITY_TIMER_H
#define PURITY_TIMER_H

struct lua_State;

namespace Purity
{
class Timer
{
public:
    Timer();

    unsigned int getElapsedTime() const;

    void restart();

    static void luaBindings(lua_State* state);

private:
    unsigned int mStartingTick;
};
}

#endif // PURITY_TIMER_H
