#include <iostream>

#include "./relay.h"
#include "./connection.h"
#include "./circuit.h"
#include "./traverser.h"

int main(int /*argc*/, char** /*argv*/)
{
    std::cout << "Hello, socially distanced world!\n";

    Relays::Circuit OR_circuit;

    OR_circuit._relays.resize(3);



//    Relays::Traverser traverser;

    return 0;
}
