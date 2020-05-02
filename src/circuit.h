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

#ifndef __RELAYS_CIRCUIT_H__
#define __RELAYS_CIRCUIT_H__

#include <vector>

#include "./transistor.h"
#include "./wire.h"

namespace Relays
{

class Circuit
{
  public:
    std::vector<Transistor> _transistors;
    std::vector<Wire> _wires;
};

} // namespace Relays

#endif // __RELAYS_CIRCUIT_H__
