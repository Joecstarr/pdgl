# =================================================================================================
# toml-c library
# =================================================================================================
block(SCOPE_FOR VARIABLES)
unset(CMAKE_CXX_CPPCHECK)
unset(CMAKE_C_CPPCHECK)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_library(tomlc_lib STATIC ./tomlc17/src/tomlc17.c)
target_include_directories(tomlc_lib PUBLIC ./tomlc17/src/)

endblock()

# =================================================================================================
# argparse library
# =================================================================================================
block(SCOPE_FOR VARIABLES)
unset(CMAKE_CXX_CPPCHECK)
unset(CMAKE_C_CPPCHECK)

add_library(argparse_lib STATIC ./argparse/argparse.c)

target_include_directories(argparse_lib INTERFACE ./argparse/)

endblock()

# =================================================================================================
# fmem library
# =================================================================================================
block(SCOPE_FOR VARIABLES)
unset(CMAKE_CXX_CPPCHECK)
unset(CMAKE_C_CPPCHECK)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
add_subdirectory(fmem)

endblock()

# =================================================================================================
# janet library
# =================================================================================================
block(SCOPE_FOR VARIABLES)
unset(CMAKE_CXX_CPPCHECK)
unset(CMAKE_C_CPPCHECK)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_library(janet_lib STATIC ./janet/janet.c)
target_include_directories(janet_lib PUBLIC janet)
target_link_libraries(janet_lib m)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_link_libraries(janet_lib ws2_32 kernel32 psapi wsock32)
endif(CMAKE_SYSTEM_NAME STREQUAL "Windows")

endblock()

# =================================================================================================
# cmock library
# =================================================================================================
block(SCOPE_FOR VARIABLES)
unset(CMAKE_CXX_CPPCHECK)
unset(CMAKE_C_CPPCHECK)

add_library(unity_lib STATIC ./unity/src/unity.c)
target_include_directories(unity_lib PUBLIC unity/src)

add_library(cmock_lib STATIC ./cmock/src/cmock.c)
target_include_directories(cmock_lib PUBLIC cmock/src)
target_link_libraries(cmock_lib unity_lib)

endblock()

# =================================================================================================
# Add lizard when not building for WASM
# =================================================================================================
if(NOT CMAKE_BUILD_TYPE STREQUAL "Emscripten")
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
  include(FindLizard.cmake)
  find_package(Lizard)
endif()
