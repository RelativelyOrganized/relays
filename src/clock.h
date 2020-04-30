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

#ifndef __RELAYS_CLOCK_H__
#define __RELAYS_CLOCK_H__

#include <cassert>
#include <cstdint>

#include "./slot_types.h"

namespace Relays
{

class Clock
{
  public:
    /**
     * Constructor
     */
    Clock() { period = 1.0 / frequency; }

    /**
     * Set the clock frequency
     * \param freq Frequency
     */
    inline void setFrequency(double freq)
    {
        assert(freq != 0.0);
        frequency = freq;
        period = 1.0 / freq;
    }

    /**
     * Set the clock period
     * \param period Period
     */
    inline void setPeriod(double period)
    {
        assert(period != 0.0);
        period = period;
        frequency = 1.0 / period;
    }

  public:
    double frequency{100.0};
    double period;
};

} // namespace Relays

#endif // __RELAYS_CLOCK_H__
