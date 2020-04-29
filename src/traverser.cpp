#include "./traverser.h"

#define likely(x) __builtin_expect((x), 1)
#define unlikely(x) __builtin_expect((x), 0)

namespace Relays
{

bool Traverser::step(Circuit& circuit, uint64_t now, uint32_t dt)
{
    update(circuit, now, dt);
    transfer(circuit, now, dt);

    return true;
}

void Traverser::update(Circuit& circuit, uint64_t /*now*/, uint32_t /*dt*/)
{
    if (unlikely(circuit._relays.empty()))
        return;

    // Relays outputs update step
    Relay* relay = &circuit._relays.at(0);
    const std::size_t relays_count = circuit._relays.size();
    for (std::size_t i = 0; i < relays_count; ++i, ++relay)
    {
        relay->output = (relay->input && relay->command);
    }
}

void Traverser::transfer(Circuit& circuit, uint64_t /*now*/, uint32_t /*dt*/)
{
    // Outputs to inputs transmission step
    if (unlikely(circuit._connections.empty()))
        return;

    Connection* connection = &circuit._connections.at(0);
    const std::size_t connections_count = circuit._connections.size();
    for (std::size_t i = 0; i < connections_count; ++i, ++connection)
    {
        Relay* from = &circuit._relays.at(connection->from);
        Relay* to = &circuit._relays.at(connection->to);
        bool* to_field = (&to->input + static_cast<int>(connection->slot));
        *to_field = from->output != connection->invert;
    }
}

} // namespace Relays
