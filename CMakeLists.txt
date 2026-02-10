# CMakeList.txt : CMake project for tanglenomicon, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.12)

project(
  tanglenomicon
  LANGUAGES C CXX
  VERSION 0.0.1)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_C_STANDARD 90)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(TEST_RESULTS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/tests/results/)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Emscripten")
  set(Python_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.venv/bin)
  set(Python3_EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR}/.venv/bin/python)
  set(Python3_FIND_VIRTUALENV "ONLY")
  set(ENV{VIRTUAL_ENV} "${CMAKE_CURRENT_SOURCE_DIR}/.venv")
  find_package(Python REQUIRED)
  find_program(CYTHON "cython")
endif(NOT CMAKE_BUILD_TYPE STREQUAL "Emscripten")

# ##############################################################################
# Start Compiler Defines
# ##############################################################################

set(CMAKE_CXX_FLAGS_RELEASE
    "-O2 -Wall"
    CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELEASE
    "-O2 -Wall"
    CACHE STRING "" FORCE)
mark_as_advanced(CMAKE_CXX_FLAGS_RELEASE CMAKE_C_FLAGS_RELEASE)
# Update the documentation string of CMAKE_BUILD_TYPE for GUIs

set(CMAKE_CXX_FLAGS_DEBUG
    "-O1 -g -Wall"
    CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_DEBUG
    "-O1 -g -Wall"
    CACHE STRING "" FORCE)
mark_as_advanced(CMAKE_CXX_FLAGS_DEBUG CMAKE_C_FLAGS_DEBUG)

set(CMAKE_CXX_FLAGS_EMSCRIPTEN
    "-O3 -fPIC -Wall"
    CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_EMSCRIPTEN
    "-O3 -fPIC -Wall"
    CACHE STRING "" FORCE)
mark_as_advanced(CMAKE_CXX_FLAGS_EMSCRIPTEN CMAKE_C_FLAGS_EMSCRIPTEN)
# Update the documentation string of CMAKE_BUILD_TYPE for GUIs

if(CMAKE_BUILD_TYPE STREQUAL "Emscripten")
  set(CMAKE_CXX_STANDARD 17)
  add_compile_definitions(ENABLE_EMSCRIPTEN)
endif(CMAKE_BUILD_TYPE STREQUAL "Emscripten")

# ##############################################################################
# End Compiler Defines
# ##############################################################################
#
# ##############################################################################
# Start Includes
# ##############################################################################

add_subdirectory(libraries)

enable_testing()

add_subdirectory(source)
add_subdirectory(wrappers)
