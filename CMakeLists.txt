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

cmake_minimum_required(VERSION 3.13)
project(
    relays
    VERSION 0.0.1
    LANGUAGES C CXX
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

# Set default build type to Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

enable_testing()

#
# Package information
#
set(API_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
set(PACKAGE_VERSION ${PROJECT_VERSION})

#
# Build options
#
set(BUILD_GENERIC_ARCH OFF CACHE BOOL "Enable building without architecture-specitif optimization")
set(TEST_COVERAGE OFF CACHE BOOL "Enable test coverage")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
if(COMPILER_SUPPORTS_MARCH_NATIVE AND NOT BUILD_GENERIC_ARCH)
    include(OptimizeForArchitecture)
    OptimizeForArchitecture()
endif()

if (TEST_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage")
endif()

#
# Dependencies
#
set(Python_ADDITIONAL_VERSIONS 3.7)
find_package(PythonLibs REQUIRED)

#
# Sources
#
add_subdirectory(src)
add_subdirectory(tests)

#
# WRAPPERS
#
add_subdirectory(wrappers/python)
