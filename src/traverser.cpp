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

void Traverser::update(Circuit& circuit, uint64_t now, uint32_t dt)
{
    if (unlikely(circuit._transistors.empty()))
        return;

    // Transistors outputs update step
    for (auto& transistor : circuit._transistors)
        transistor.step(now, dt);

    // Quartz update step
    for (auto& quartz : circuit._quartz)
        quartz.step(now, dt);
}

void Traverser::transfer(Circuit& circuit, uint64_t now, uint32_t dt)
{
    // Outputs to inputs transmission step
    if (unlikely(circuit._wires.empty()))
        return;

    for (const auto& wire : circuit._wires)
        wire.step(now, dt);
}

} // namespace Relays
