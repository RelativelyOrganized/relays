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

    quartz.step(5e8, 5e8);
    assert(quartz.output == Output::False);

    quartz.step(1e9, 5e8);
    assert(quartz.output == Output::True);

    return 0;
}
