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

include_directories(../src/)

add_executable(check_example check_example.cpp)
add_test(check_example check_example)

add_executable(check_flip_flop check_flip_flop.cpp)
target_link_libraries(check_flip_flop relays-${API_VERSION})
add_test(check_flip_flop check_flip_flop)

#
# Code coverage
#
if (TEST_COVERAGE)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_custom_command(OUTPUT test_coverage
            COMMAND mkdir -p ${CMAKE_BINARY_DIR}/coverage
            COMMAND lcov --no-external --capture --initial
                --directory ${CMAKE_SOURCE_DIR}
                --output-file coverage/relays_base.info
            COMMAND make test
            COMMAND lcov --no-external --capture
                --directory ${CMAKE_SOURCE_DIR}
                --output-file coverage/relays.info
            COMMAND lcov --add-tracefile ${CMAKE_BINARY_DIR}/coverage/relays_base.info
                --add-tracefile ${CMAKE_BINARY_DIR}/coverage/relays.info
                --output-file ${CMAKE_BINARY_DIR}/coverage/relays_total.info
            COMMAND genhtml --output-directory ${CMAKE_BINARY_DIR}/coverage ${CMAKE_BINARY_DIR}/coverage/relays_total.info
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            )

        add_custom_target(check_coverage DEPENDS test_coverage)
    endif()
endif()
