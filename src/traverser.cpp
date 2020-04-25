#include "./traverser.h"

#define likely(x) __builtin_expect((x), 1)
#define unlikely(x) __builtin_expect((x), 0)

namespace Relays
{

bool Traverser::traverse(Circuit& circuit)
{
    if (!circuit.ordered)
        return false;

    update(circuit);
    transfer(circuit);

    return true;
}

void Traverser::update(Circuit& circuit)
{
    if (unlikely(circuit._relays.empty()))
        return;

    // Relays outputs update step
    Relay* relay = &circuit._relays.at(0);
    const std::size_t relays_count = circuit._relays.size();
    for (std::size_t i = 0; i < relays_count; i++)
    {
        relay->output = (relay->input && relay->command);
        relay++;
    }
}

void Traverser::transfer(Circuit& circuit)
{
    // Outputs to inputs transmission step
    if (unlikely(circuit._connections.empty()))
        return;

    Connection* connection = &circuit._connections.at(0);
    const std::size_t connections_count = circuit._connections.size();
    for (std::size_t i = 0; i < connections_count; i++)
    {
        Relay* from = &circuit._relays.at(connection->from);
        Relay* to = &circuit._relays.at(connection->to);
        bool* to_field = (&to->input + static_cast<int>(connection->slot));
        *to_field = from->output != connection->invert;
        connection++;
    }
}

} // namespace Relays
