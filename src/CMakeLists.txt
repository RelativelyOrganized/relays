#
# This file is part of Relays.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Relays is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Relays.  If not, see <http://www.gnu.org/licenses/>.
#

#
# Enable all warnings as errors
#
add_definitions(-Wall -Wextra -Werror)

#
# Includes
#
include_directories(./)

#
# Relays library
#
add_library(relays-${API_VERSION} STATIC)

target_sources(relays-${API_VERSION} PRIVATE
    relay.cpp
    circuit.cpp
    layout.cpp
    simulation.cpp
    traverser.cpp
)

target_link_libraries(relays-${API_VERSION} pthread)

#
# Relays binary
#
add_executable(relays relays.cpp)
target_link_libraries(relays relays-${API_VERSION})

install(TARGETS relays DESTINATION "bin/")
