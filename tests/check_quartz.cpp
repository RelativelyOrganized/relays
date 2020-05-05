#undef NDEBUG // get assert in release mode

#include <cassert>

#include "./clock.h"
#include "./quartz.h"

using namespace Relays;

int main()
{
    Clock clock;
    clock.setFrequency(1000.0);

    Quartz quartz(clock);
    assert(quartz.period == clock.period);

    quartz.step(5e5, 5e5);
    assert(quartz.output == Output::False);

    quartz.step(1e6, 5e5);
    assert(quartz.output == Output::True);

    quartz.step(2e6, 1e6);
    assert(quartz.output == Output::False);

    return 0;
}
