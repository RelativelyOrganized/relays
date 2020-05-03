#undef NDEBUG // get assert in release mode

#include <cassert>

#include "./transistor.h"

using namespace Relays;

int main()
{
    Transistor transistor;

    transistor.input = Input::True;
    transistor.command = Input::True;
    transistor.step(0, 0);
    assert(transistor.output == Output::True);

    transistor.input = Input::True;
    transistor.command = Input::False;
    transistor.step(0, 0);
    assert(transistor.output == Output::False);

    transistor.input = Input::False;
    transistor.command = Input::True;
    transistor.step(0, 0);
    assert(transistor.output == Output::False);

    transistor.input = Input::False;
    transistor.command = Input::False;
    transistor.step(0, 0);
    assert(transistor.output == Output::False);

    return 0;
}
