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

class Layout
{
  public:
    /**
     * Pushes a copy of the layout and returns the id of its first relay
     * \param layout Layout to add to this one
     * \return Return the id of the first relay added
     */
    uint64_t push_layout(const Layout& layout);

  public:
    std::vector<Relay> _relays;
    std::vector<Connection> _connections;
    std::vector<Clock> _clocks;
};

} // namespace Relays

#endif // __RELAYS_LAYOUT_H__
