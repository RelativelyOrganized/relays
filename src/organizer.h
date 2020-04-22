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

#ifndef __RELAYS_ORGANIZER_H__
#define __RELAYS_ORGANIZER_H__

#include "./circuit.h"

namespace Relays
{

class Organizer
{
  public:
    /**
     * Orders the connections of a circuit so that going through them
     * sequentially results in going from its inputs to its outputs without
     * skipping the update of a relay
     * \param circuit Circuit to reorder
     * \return Return the same circuit, reordered
     */
    Circuit order(const Circuit& circuit);
};

}

#endif // __RELAYS_ORGANIZER_H__
