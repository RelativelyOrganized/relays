#include "./simulation.h"

#include <cassert>
#include <iostream>

using namespace std::chrono;

namespace Relays
{

bool Simulation::run()
{
    if (_simulationThread.joinable())
    {
        assert(_continue == true);
        return false;
    }

    _continue = true;
    _simulationThread = std::thread([this]() -> void {
        uint64_t timeSinceEpoch = 0;
        while (_continue)
        {
            _traverser.step(_circuit, timeSinceEpoch, _step_period);
            timeSinceEpoch += _step_period;
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
