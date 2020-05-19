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

#ifndef __RELAYS_CONNECTION_H__
#define __RELAYS_CONNECTION_H__

#include <cstdint>

namespace Relays
{

class Connection
{
  public:
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

    enum class Sink : uint8_t
    {
        Relay = 0,
        Layout = 1
    };

  public:
    uint64_t from{0};
    uint64_t to{0};
    uint64_t layoutIn{0};
    uint64_t layoutOut{0};
    Source source{Source::Relay};
    Sink sink{Sink::Relay};
    Slot slot{Slot::Input};
    bool invert{false};
};

} // namespace Relays

#endif //__RELAYS_CONNECTION_H__
