#include "./organizer.h"

namespace Relays
{

Circuit Organizer::order(const Circuit& circuit)
{
    auto ordered_circuit = circuit;
    ordered_circuit.ordered = true;
    return ordered_circuit;
}

}
