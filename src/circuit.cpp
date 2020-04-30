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

namespace Relays
{

void Circuit::setFromLayout(const Layout& layout)
{
    // Convert all Relays to Transistors
    _transistors.resize(layout._relays.size());
    for (size_t i = 0; i < layout._relays.size(); ++i)
        _transistors[i].switchDuration = layout._relays[i].switchDuration;

    // Convert all Clocks to Quartz
    _quartz.reserve(layout._clocks.size());
    for (const auto& clock : layout._clocks)
        _quartz.emplace_back(clock);

    // Convert all Connections to Wires
    _wires.resize(layout._connections.size());
    for (size_t i = 0; i < layout._connections.size(); ++i)
    {
        auto& connection = layout._connections[i];
        auto& wire = _wires[i];

        if (connection.source == Source::Relay)
            wire.from = &_transistors[connection.from].output;
        else // connection.source == Source.Clock
            wire.from = &_quartz[connection.from].output;

        if (connection.slot == Slot::Input)
            wire.to = &_transistors[connection.from].input;
        else
            wire.to = &_transistors[connection.from].command;

        wire.invert = connection.invert;
    }
}

} // namespace Relays
