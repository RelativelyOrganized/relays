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

#ifndef __RELAYS_RELAY_H__
#define __RELAYS_RELAY_H__

#include <ostream>

#include "./slot_types.h"

namespace Relays
{

class Relay
{
  public:
    Input input{Input::False};
    Input command{Input::False};
    Output output{Output::False};

    friend std::ostream& operator<<(std::ostream& stream, Relay& relay);
};

} // namespace Relays

#endif // __RELAYS_RELAY_H__
