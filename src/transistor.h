/*
 * This file is part of Transistors.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Transistors is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Transistors.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __TRANSISTORS_TRANSISTOR_H__
#define __TRANSISTORS_TRANSISTOR_H__

#include <ostream>

#include "./slot_types.h"

namespace Relays
{

class Transistor
{
  public:
    /**
     * Evaluate relay's output given its input and command
     * \param now Time since epoch
     * \param dt Time step since previous update, in ns
     */
    void step(uint64_t /*now*/, uint32_t /*dt*/)
    {
        output = static_cast<Output>((static_cast<bool>(input) && static_cast<bool>(command)));
    }

  public:
    Input input{Input::False};
    Input command{Input::False};
    Output output{Output::False};

    friend std::ostream& operator<<(std::ostream& stream, Transistor& relay);
};

} // namespace Relays

#endif // __TRANSISTORS_TRANSISTOR_H__
