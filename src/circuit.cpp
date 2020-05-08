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

bool Circuit::setFromLayout(const Layout& layout)
{
    auto flatLayout = layout.flatten();
    // Convert all Relays to Transistors
    _transistors.resize(flatLayout._relays.size());
    for (size_t i = 0; i < flatLayout._relays.size(); ++i)
        _transistors[i].switchDuration = flatLayout._relays[i].switchDuration;

    // Convert all Clocks to Quartz
    _quartz.reserve(flatLayout._clocks.size());
    for (const auto& clock : flatLayout._clocks)
        _quartz.emplace_back(clock);

    // Convert all Connections to Wires
    _wires.resize(flatLayout._connections.size());
    for (size_t i = 0; i < flatLayout._connections.size(); ++i)
    {
        auto& connection = flatLayout._connections[i];
        auto& wire = _wires[i];

        if (connection.source == Source::Relay)
        {
            wire.from = &_transistors[connection.from].output;
        }
        else if (connection.source == Source::Clock)
        {
            wire.from = &_quartz[connection.from].output;
        }
        else
        {
            // connection.source == Source::Layout should not happen
            // the Layout should have been flattened before conversion to Circuit
            return false;
        }

        if (connection.slot == Slot::Input)
            wire.to = &_transistors[connection.to].input;
        else
            wire.to = &_transistors[connection.to].command;

        wire.invert = connection.invert;
    }

    // Convert all Interfaces to pointers to Inputs and Outputs
    _pinsIn.resize(flatLayout._interfaceIn.size());
    for (size_t i = 0; i < flatLayout._interfaceIn.size(); ++i)
    {
        auto& interface = flatLayout._interfaceIn[i];
        auto& pin = _pinsIn[i];

        if (interface.slot == Slot::Input)
            pin = &_transistors[interface.index].input;
        else
            pin = &_transistors[interface.index].command;
    }

    _pinsOut.resize(flatLayout._interfaceOut.size());
    for (size_t i = 0; i < flatLayout._interfaceOut.size(); ++i)
    {
        auto& interface = flatLayout._interfaceOut[i];
        auto& pin = _pinsOut[i];

        pin = &_transistors[interface.index].output;
    }

    return true;
}

} // namespace Relays
