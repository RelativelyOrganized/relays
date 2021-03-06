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

include_directories(${CMAKE_SOURCE_DIR}/src/)

add_executable(check_flip_flop check_flip_flop.cpp)
target_link_libraries(check_flip_flop relays-${API_VERSION})
add_test(check_flip_flop check_flip_flop)

add_executable(check_circuit check_circuit.cpp)
target_link_libraries(check_circuit relays-${API_VERSION})
add_test(check_circuit check_circuit)

add_executable(check_quartz check_quartz.cpp)
target_link_libraries(check_quartz relays-${API_VERSION})
add_test(check_quartz check_quartz)

add_executable(check_transistor check_transistor.cpp)
target_link_libraries(check_transistor relays-${API_VERSION})
add_test(check_transistor check_transistor)

add_executable(check_wire check_wire.cpp)
target_link_libraries(check_wire relays-${API_VERSION})
add_test(check_wire check_wire)

add_executable(check_expected check_expected.cpp)
target_link_libraries(check_expected relays-${API_VERSION})
add_test(check_expected check_expected)

add_executable(check_layout check_layout.cpp)
target_link_libraries(check_layout relays-${API_VERSION})
add_test(check_layout check_layout)

add_test(NAME check_pyrelays COMMAND bash -c "PYTHONPATH=${CMAKE_BINARY_DIR}/wrappers/python python3 ${CMAKE_CURRENT_SOURCE_DIR}/check_pyrelays.py")

#
# Code coverage
#
if (TEST_COVERAGE)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_custom_command(OUTPUT test_coverage
            COMMAND mkdir -p ${CMAKE_BINARY_DIR}/coverage
            COMMAND lcov --no-external --capture --initial
                --directory ${CMAKE_SOURCE_DIR}
                --exclude '${CMAKE_SOURCE_DIR}/tests/*'
                --output-file coverage/relays_base.info
            COMMAND make test
            COMMAND lcov --no-external --capture
                --directory ${CMAKE_SOURCE_DIR}
                --exclude '${CMAKE_SOURCE_DIR}/tests/*'
                --output-file coverage/relays.info
            COMMAND lcov --add-tracefile ${CMAKE_BINARY_DIR}/coverage/relays_base.info
                --add-tracefile ${CMAKE_BINARY_DIR}/coverage/relays.info
                --exclude '${CMAKE_SOURCE_DIR}/tests/*'
                --output-file ${CMAKE_BINARY_DIR}/coverage/relays_total.info
            COMMAND genhtml --output-directory ${CMAKE_BINARY_DIR}/coverage ${CMAKE_BINARY_DIR}/coverage/relays_total.info
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            )

        add_custom_target(check_coverage DEPENDS test_coverage)
    endif()
endif()
