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

#ifndef __RELAYS_LAYOUT_H__
#define __RELAYS_LAYOUT_H__

#include <vector>

#include "./clock.h"
#include "./connection.h"
#include "./relay.h"

namespace Relays
{

struct Interface
{
    enum class Slot : uint8_t
    {
        Input = 0,
        Command = 1
    };

    enum class Source : uint8_t
    {
        Relay = 0,
        Clock = 1,
        Layout = 2
    };

    uint64_t index{0};
    Slot slot{Slot::Input};
    Source source{Source::Relay};
};

class Layout
{
  public:
    /**
     * Flatten the Layout to a new one with no child.
     * \return Return a new, flattened Layout
     */
    Layout flatten() const;

    /**
     * Add a child layout, and connect it to the current one.
     * The connections are not used as-is and are updated to match the
     * current state of the current layout. In any case the correct relays,
     * clocks or layout IDs must be specified for the connection to be set
     * \param layout Layout to add as a child
     * \param in Input connections to the newly added layout
     * \param out Output connections to the newly added layout
     * \return bool Return true if the layout was successfully added
     */
    bool addLayout(const Layout& layout, const std::vector<Connection>& in, const std::vector<Connection>& out);

  public:
    std::vector<Layout> _childrenLayouts;
    std::vector<Relay> _relays;
    std::vector<Clock> _clocks;
    std::vector<Connection> _connections;
    std::vector<Interface> _interfaceIn;
    std::vector<Interface> _interfaceOut;
};

} // namespace Relays

#endif // __RELAYS_LAYOUT_H__
