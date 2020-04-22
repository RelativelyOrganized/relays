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

#include "./circuit.h"
#include <algorithm>

namespace Relays
{

uint64_t Circuit::push_circuit( const Circuit& circuit )
{
    if (circuit._relays.empty())
    {
        // TODO: error management
        return 0;
    }

    // This contains the id of the first relay that shall be imported from circuit
    uint64_t circuit_start = _relays.size();

    // Lets copy the relays
    _relays.reserve(_relays.size() + circuit._relays.size());
    std::copy(circuit._relays.begin(), circuit._relays.end(), std::back_inserter(_relays));

    // Lets copy the connections. We need to offset the ids.
    _connections.reserve(_connections.size() + circuit._connections.size());
    std::transform(circuit._connections.begin(), circuit._connections.end(), _connections.begin(), [ this, offset = circuit_start ]( const Relays::Connection& input )
    {
        Connection output;
        output.from = input.from + offset;
        output.to = input.to + offset;
        output.invert = input.invert;
        return output;
    });

    // Done
    return circuit_start;
}

}
