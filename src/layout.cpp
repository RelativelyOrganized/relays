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

#include "./layout.h"

#include <algorithm>

namespace Relays
{

uint64_t Layout::push_layout(const Layout& layout)
{
    if (layout._relays.empty())
    {
        // TODO: error management
        return 0;
    }

    // This contains the id of the first relay that shall be imported from layout
    uint64_t relay_start = _relays.size();
    uint64_t clock_start = _clocks.size();

    // Copy the relays
    _relays.reserve(_relays.size() + layout._relays.size());
    std::copy(layout._relays.begin(), layout._relays.end(), std::back_inserter(_relays));

    // Copy the clocks
    _clocks.reserve(_clocks.size() + layout._clocks.size());
    std::copy(layout._clocks.begin(), layout._clocks.end(), std::back_inserter(_clocks));

    // Copy the connections. We need to offset the ids.
    _connections.reserve(_connections.size() + layout._connections.size());
    std::transform(layout._connections.begin(),
        layout._connections.end(),
        _connections.begin(),
        [this, relay_start, clock_start](const Relays::Connection& input) {
            Connection output;
            if (input.source == Source::Relay)
                output.from = input.from + relay_start;
            else // input.source == Source::Clock
                output.from = input.from + clock_start;
            output.to = input.to + relay_start;
            output.slot = input.slot;
            output.invert = input.invert;
            return output;
        });

    // Done
    return relay_start;
}

} // namespace Relays
