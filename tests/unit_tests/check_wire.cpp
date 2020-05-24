#undef NDEBUG // get assert in release mode

#include <cassert>

#include "./wire.h"

using namespace Relays;

int main()
{
    Output output{Output::False};
    Input input{Input::True};

    Wire wire;
    wire.from = &output;
    wire.to = &input;

    wire.step(0, 0);
    assert(input == Input::False);

    wire.invert = true;
    wire.step(0, 0);
    assert(input == Input::True);

    output = Output::True;
    wire.step(0, 0);
    assert(input == Input::False);

    return 0;
}
