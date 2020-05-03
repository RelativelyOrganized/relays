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

#ifndef __RELAYS_QUARTZ_H__
#define __RELAYS_QUARTZ_H__

#include <cassert>
#include <cstdint>

#include "./clock.h"
#include "./slot_types.h"

namespace Relays
{

class Quartz
{
  public:
    /**
     * Constructor
     * \param clock Clock to construct the Quartz from
     */
    Quartz(const Clock& clock) { period = clock.period; }

    /**
     * Step through the quartz and update its output
     * \param now Time since epoch
     * \param dt Time since last update
     */
    void step(uint64_t epoch, uint32_t /*dt*/)
    {
        auto currentPeriod = static_cast<uint64_t>(static_cast<double>(epoch) / (period * 1e9));
        output = static_cast<Output>(currentPeriod % 2);
    }

  public:
    Output output{Output::False};
    double period;
};

} // namespace Relays

#endif // __RELAYS_QUARTZ_H__
