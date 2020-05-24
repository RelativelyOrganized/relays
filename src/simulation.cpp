#include "./simulation.h"
#include "./circuit.h"

#include <cassert>
#include <iostream>

using namespace std::chrono;

namespace Relays
{

bool Simulation::run()
{
    return run(0UL);
}

bool Simulation::run(uint64_t timeLimit)
{
    if (_simulationThread.joinable())
    {
        assert(_continue == true);
        return false;
    }

    _continue = true;
    _simulationThread = std::thread([this, timeLimit]() -> void {
        uint64_t timeSinceEpoch = 0;
        Circuit circuit(_layout);
        while (_continue)
        {
            _traverser.step(circuit, timeSinceEpoch, _step_period);
            timeSinceEpoch += _step_period;
            if (timeLimit != 0 && timeSinceEpoch > timeLimit)
                _continue = false;
        }
    });

    return true;
}

bool Simulation::stop()
{
    if (!_simulationThread.joinable())
    {
        assert(_continue == false);
        return false;
    }

    _continue = false;
    _simulationThread.join();
    return true;
}

} // namespace Relays
