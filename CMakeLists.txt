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

set(Python_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.venv/bin)
set(Python3_EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR}/.venv/bin/python)
set(Python3_FIND_VIRTUALENV "ONLY")
set(ENV{VIRTUAL_ENV} "${CMAKE_CURRENT_SOURCE_DIR}/.venv")

find_package(
  Python
  COMPONENTS Interpreter Development.Module
  REQUIRED)
find_program(CYTHON "cython")

add_compile_options($<$<CONFIG:Debug>:-Og>)
add_compile_options($<$<CONFIG:Release>:-O2>)

add_subdirectory(libraries)

# ##############################################################################
# Start Compiler Defines
# ##############################################################################

# ##############################################################################
# Start Includes
# ##############################################################################

enable_testing()

add_subdirectory(source)

# ##############################################################################
# End Compiler Defines
# ##############################################################################

# ##############################################################################
# Start Extra Build Defines
# ##############################################################################

# ##############################################################################
# Start Extra Build Defines
# ##############################################################################
