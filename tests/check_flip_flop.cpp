#include <cassert>

#include "./circuit.h"
#include "./connection.h"
#include "./relay.h"
#include "./traverser.h"

int main()
{
    Relays::Circuit flip_flop;

    flip_flop._relays.resize(2);
    Relays::Relay& r1 = flip_flop._relays.at(0);
    Relays::Relay& r2 = flip_flop._relays.at(1);

    flip_flop._connections.resize(2);
    Relays::Connection& conn_r1_r2_cmd_inv = flip_flop._connections.at(0);
    Relays::Connection& conn_r2_r1_cmd = flip_flop._connections.at(1);

    conn_r1_r2_cmd_inv.from = &r1.output;
    conn_r1_r2_cmd_inv.to = &r2.command;
    conn_r1_r2_cmd_inv.invert = true;

    conn_r2_r1_cmd.from = &r2.output;
    conn_r2_r1_cmd.to = &r1.command;
    conn_r2_r1_cmd.invert = true;

    Relays::Traverser traverser;

    r1.input = Relays::Input::True;
    r2.input = Relays::Input::True;

    bool desired_state = true;
    const uint32_t timePerStep = 5;
    uint64_t timeSinceEpoch = 0;

    for (int i = 0; i < 100; ++i)
    {
        assert(static_cast<bool>(r1.output) == desired_state);
        assert(static_cast<bool>(r2.output) == desired_state);
        desired_state = !desired_state;
        traverser.step(flip_flop, timeSinceEpoch, timePerStep);
        timeSinceEpoch += timePerStep;
    }

    return 0;
}
