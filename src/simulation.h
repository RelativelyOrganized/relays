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

#include "./circuit.h"
#include "./traverser.h"

namespace Relays
{

class Simulation
{
  public:
    /**
     * Runs the simulation (in a separate thread)
     * \return Return false if the simulation is already running, true otherwise
     */
    bool run();

    /**
     * Stop the simulation
     * \return Return true if the simulation was successfully stopped
     */
    bool stop();

    /**
     * Set the circuit to work on
     * \param circuit Circuit to work on
     */
    void setCircuit(const Circuit& circuit) { _circuit = circuit; }

    /**
     * Set the step period, in ns
     * \param period Period in ns
     */
    void setStepPeriod(uint32_t period) { _step_period = period; }

  private:
    uint32_t _step_period{5}; //! Time between each simulation step, in ns
    Traverser _traverser;
    Circuit _circuit;

    bool _continue{false};
    std::thread _simulationThread{};
};

} // namespace Relays

#endif // __RELAYS_SIMULATION_H__
