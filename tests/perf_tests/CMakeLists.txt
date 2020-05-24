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

add_custom_command(OUTPUT measure_perf
    COMMAND bash -c "PYTHONPATH=${CMAKE_BINARY_DIR}/wrappers/python python3 ${CMAKE_CURRENT_SOURCE_DIR}/check_perf.py"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(check_perf DEPENDS pyrelays measure_perf)
