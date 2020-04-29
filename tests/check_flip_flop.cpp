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

    conn_r1_r2_cmd_inv.from = 0;
    conn_r1_r2_cmd_inv.to = 1;
    conn_r1_r2_cmd_inv.invert = true;
    conn_r1_r2_cmd_inv.slot = Relays::Slot::Command;

    conn_r2_r1_cmd.from = 1;
    conn_r2_r1_cmd.to = 0;
    conn_r2_r1_cmd.invert = true;
    conn_r2_r1_cmd.slot = Relays::Slot::Command;

    Relays::Traverser traverser;

    r1.input = true;
    r2.input = true;

    bool desired_state = true;
    const uint32_t timePerStep = 5;
    uint64_t timeSinceEpoch = 0;

    for (int i = 0; i < 100; ++i)
    {
        assert(r1.output == desired_state && r2.output == desired_state);
        desired_state = !desired_state;
        traverser.step(flip_flop, timeSinceEpoch, timePerStep);
        timeSinceEpoch += timePerStep;
    }

    return 0;
}
