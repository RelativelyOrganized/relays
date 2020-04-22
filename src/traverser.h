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
     * \return Return false if the circuit was not organized
     */
    bool traverse( Circuit& circuit );
};

}

#endif //__RELAYS_TRAVERSER_H__
