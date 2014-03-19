#ifndef PURITY_TIMER_H
#define PURITY_TIMER_H

namespace Purity
{
    class Timer
    {
    public:
        Timer();

        unsigned int getElapsedTime() const;

        void restart();

    private:
        unsigned int mStartingTick;
    };
}

#endif // PURITY_TIMER_H
