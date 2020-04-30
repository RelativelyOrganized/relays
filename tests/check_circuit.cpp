#undef NDEBUG // get assert in release mode

#include <cassert>

#include "./circuit.h"
#include "./connection.h"
#include "./layout.h"
#include "./relay.h"

int main()
{
    Relays::Layout layout;

    layout._relays.resize(2);
    layout._connections.resize(2);
    auto& conn_r1_r2_cmd_inv = layout._connections.at(0);
    auto& conn_r2_r1_cmd = layout._connections.at(1);

    conn_r1_r2_cmd_inv.from = 0;
    conn_r1_r2_cmd_inv.to = 1;
    conn_r1_r2_cmd_inv.slot = Relays::Slot::Command;
    conn_r1_r2_cmd_inv.invert = true;

    conn_r2_r1_cmd.from = 1;
    conn_r2_r1_cmd.to = 0;
    conn_r1_r2_cmd_inv.slot = Relays::Slot::Input;
    conn_r1_r2_cmd_inv.invert = true;

    Relays::Circuit circuit(layout);

    assert(circuit._wires.size() == 2);
    assert(circuit._transistors.size() == 2);
    assert(circuit._wires[0].from == &circuit._transistors[0].output);
    assert(circuit._wires[0].to == &circuit._transistors[1].command);
    assert(circuit._wires[1].from == &circuit._transistors[1].output);
    assert(circuit._wires[1].to == &circuit._transistors[0].input);

    return 0;
}
