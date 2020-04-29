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

#ifndef __RELAYS_TRAVERSER_H__
#define __RELAYS_TRAVERSER_H__

#include "./circuit.h"

namespace Relays
{

class Traverser
{
  public:
    /**
     * Traverses a circuit, and updates its state along the way
     * \param circuit Circuit to traverse
     * \param now Time since epoch
     * \param dt Time step since previous update, in ns
     * \return Return false if the circuit was not organized
     */
    bool step(Circuit& circuit, uint64_t now, uint32_t dt);

    /**
     * Updates the current face of the circuit.
     * \param circuit Circuit to work on
     * \param now Time since epoch
     * \param dt Time step since previous update, in ns
     */
    void update(Circuit& circuit, uint64_t now, uint32_t dt);

    /**
     * Transferts the outputs of the relays to the connected inputs (input or command).
     * \param circuit Circuit to work on
     * \param now Time since epoch
     * \param dt Time step since previous update, in ns
     */
    void transfer(Circuit& circuit, uint64_t now, uint32_t dt);
};

} // namespace Relays

#endif //__RELAYS_TRAVERSER_H__
