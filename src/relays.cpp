#include <iostream>

#include "./circuit.h"
#include "./connection.h"
#include "./relay.h"
#include "./traverser.h"

int main(int /*argc*/, char** /*argv*/)
{
    std::cout << "Hello, socially distanced world!\n";

    Relays::Circuit flip_flop;
    flip_flop.ordered = true;

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

    traverser.transfer(flip_flop);

    for (int i = 0; i < 10; i++)
    {
        traverser.traverse(flip_flop);
        std::cout << r1 << " --- " << r2 << std::endl;
    }

    return 0;
}
