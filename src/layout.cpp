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
#include <map>

namespace Relays
{

/*
 * This methode flattens a layout by merging all its children layouts
 * into it. The inner connections between layouts are converted to connections
 * to relays and clocks.
 *
 * For example it converts the following layout:
 *
 * +----------------------------------------------------------------------------------+
 * |               +--------------------------------------+                           |
 * |0   +-----+    |0  +-----+                  +-----+  0|                +-----+   0|
 * >~~~~|Relay|====>~~~|Relay|----------------->|Relay|~~~>===============>|Relay|~~~~>
 * >~~~~|0    |    >~~~|0    |     +-----+  +-->|1    |   |             +->|1    |    |
 * |1   +-----+    |1  +-----+     |Clock|--+   +-----+   |    +-----+  |  +-----+    |
 * |               |               |0    |                |    |Clock|--+             |
 * |               |Child layout   +-----+                |    |0    |                |
 * |Main layout    +--------------------------------------+    +-----+                |
 * +----------------------------------------------------------------------------------+
 *
 * into this:
 *
 * +-------------------------------------------------------------------------+
 * |0  +-----+    +-----+                  +-----+                +-----+   0|
 * >~~~|Relay|--->|Relay|----------------->|Relay|--------------->|Relay|~~~~>
 * >~~~|0    |    |2    |     +-----+  +-->|3    |             +->|1    |    |
 * |1  +-----+    +-----+     |Clock|--+   +-----+    +-----+  |  +-----+    |
 * |                          |1    |                 |Clock|--+             |
 * |                          +-----+                 |0    |                |
 * |Main layout                                       +-----+                |
 * +-------------------------------------------------------------------------+
 *
 * legend:
 * ~~~ interface
 * --- connection between Relay/Relay or Clock/Relay
 * === connection between Relay/Layout or Layout/Relay
 *
 */
Layout Layout::flatten() const
{
    Layout flatLayout;

    // Copy the existing relays, clocks and interfaces
    flatLayout._relays = _relays;
    flatLayout._clocks = _clocks;
    flatLayout._interfaceIn = _interfaceIn;
    flatLayout._interfaceOut = _interfaceOut;

    // Go through connexions
    // We only add a child layout if it it has at least one output
    // connected to the current layout, so we have to list them first
    std::map<uint64_t, const Layout*> outLayouts;
    for (const auto& connection : _connections)
    {
        if (connection.source != Source::Layout && connection.sink != Sink::Layout)
            flatLayout._connections.push_back(connection);
        else if (connection.sink == Sink::Layout)
            outLayouts[connection.layoutOut] = &_childrenLayouts[connection.layoutOut];
    }

    std::map<uint64_t, Layout> selectedLayouts;
    for (const auto& connection : _connections)
    {
        if (connection.source != Source::Layout && connection.sink != Sink::Layout)
            continue;

        auto outLayoutIt = outLayouts.find(connection.layoutIn);
        if (outLayoutIt == outLayouts.end())
            continue;

        // The layout has inputs and outputs connected, we keep it
        // as a new copy because we have work to do on it
        selectedLayouts[connection.layoutIn] = *outLayoutIt->second;

        // Copy the connection to the flat layout
        flatLayout._connections.push_back(connection);
    }

    // All selected layouts have to be flattened too
    for (auto& [id, layout] : selectedLayouts)
        layout = layout.flatten();

    // Now we incorporate it inside the flat layout
    size_t relayShift = _relays.size();
    size_t clockShift = _clocks.size();

    std::map<uint64_t, size_t> layoutRelaysShift;
    std::map<uint64_t, size_t> layoutClocksShift;

    // Copy the relays and clock to the flat layout
    for (const auto& [id, layout] : selectedLayouts)
    {
        for (const auto& connection : layout._connections)
        {
            auto flatConnection = connection;
            if (flatConnection.source == Source::Relay)
                flatConnection.from += relayShift;
            else if (flatConnection.source == Source::Clock)
                flatConnection.from += clockShift;

            flatConnection.to += relayShift;
            flatLayout._connections.push_back(flatConnection);
        }

        layoutRelaysShift[id] = relayShift;
        relayShift += layout._relays.size();
        std::copy(layout._relays.begin(), layout._relays.end(), std::back_inserter(flatLayout._relays));

        layoutClocksShift[id] = clockShift;
        clockShift += layout._clocks.size();
        std::copy(layout._clocks.begin(), layout._clocks.end(), std::back_inserter(flatLayout._clocks));
    }

    // Update connections related to this layout
    for (auto& connection : flatLayout._connections)
    {
        if (connection.source == Source::Layout)
        {
            auto& input = selectedLayouts[connection.layoutIn]._interfaceOut[connection.from];
            if (input.source == Source::Relay)
            {
                connection.from = input.index + layoutRelaysShift[connection.layoutIn];
                connection.layoutIn = 0;
                connection.source = Source::Relay;
            }
            else if (input.source == Source::Clock)
            {
                connection.from = input.index + layoutClocksShift[connection.layoutIn];
                connection.layoutIn = 0;
                connection.source = Source::Clock;
            }
            else
            {
                assert(false);
            }
        }

        if (connection.sink == Sink::Layout)
        {
            auto& output = selectedLayouts[connection.layoutOut]._interfaceIn[connection.to];
            connection.to = output.index + layoutRelaysShift[connection.layoutOut];
            connection.layoutOut = 0;
            connection.sink = Sink::Relay;
            connection.slot = output.slot;
        }
    }

    return flatLayout;
}

bool Layout::addLayout(const Layout& layout, const std::vector<Connection>& in, const std::vector<Connection>& out)
{
    _childrenLayouts.push_back(layout);

    for (const auto& connection : in)
    {
        if (connection.sink != Sink::Layout)
            return false;

        auto newConnection = connection;
        newConnection.layoutOut = _childrenLayouts.size() - 1;
        _connections.push_back(newConnection);
    }

    for (const auto& connection : out)
    {
        if (connection.source != Source::Layout)
            return false;

        auto newConnection = connection;
        newConnection.layoutIn = _childrenLayouts.size() - 1;
        _connections.push_back(newConnection);
    }

    return true;
}

} // namespace Relays
