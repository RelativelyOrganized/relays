/*
 * This file is part of Relays.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Relays is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Relays.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __RELAYS_SIMULATION_H__
#define __RELAYS_SIMULATION_H__

#include <thread>

#include "./layout.h"
#include "./traverser.h"

namespace Relays
{

class Simulation
{
  public:
    /**
     * Get whether the simulation is running
     * \return Return true if the simulation is running
     */
    bool isRunning() const { return _continue; }

    /**
     * Runs the simulation (in a separate thread)
     * \return Return false if the simulation is already running, true otherwise
     */
    bool run();

    /**
     * Runs a fixed amount of simulated time
     * \param timeLimit Time limit after which to stop the simulation, in ns
     * \return Return false if the simulation is already running, true otherwise
     */
    bool run(uint64_t timeLimit);

    /**
     * Stop the simulation
     * \return Return true if the simulation was successfully stopped
     */
    bool stop();

    /**
     * Set the layout to work on
     * \param layout Layout to work on
     */
    void setLayout(const Layout& layout) { _layout = layout; }

    /**
     * Set the step period, in ns
     * \param period Period in ns
     */
    void setStepPeriod(uint32_t period) { _step_period = period; }

  private:
    uint32_t _step_period{5}; //! Time between each simulation step, in ns
    Traverser _traverser;
    Layout _layout;

    bool _continue{false};
    std::thread _simulationThread{};
};

} // namespace Relays

#endif // __RELAYS_SIMULATION_H__
