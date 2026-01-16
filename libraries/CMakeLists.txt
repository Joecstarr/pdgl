block(SCOPE_FOR VARIABLES)
unset(CMAKE_CXX_CPPCHECK)
unset(CMAKE_C_CPPCHECK)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_library(tomlc_lib STATIC ./tomlc17/src/tomlc17.c)
target_include_directories(tomlc_lib PUBLIC ./tomlc17/src/)
endblock()

block(SCOPE_FOR VARIABLES)
unset(CMAKE_CXX_CPPCHECK)
unset(CMAKE_C_CPPCHECK)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(fmem)

endblock()

block(SCOPE_FOR VARIABLES)
unset(CMAKE_CXX_CPPCHECK)
unset(CMAKE_C_CPPCHECK)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_library(janet_lib STATIC ./janet/janet.c ./janet/shell.c)
target_include_directories(janet_lib PUBLIC janet)
target_link_libraries(janet_lib m)
endblock()

block(SCOPE_FOR VARIABLES)
unset(CMAKE_CXX_CPPCHECK)
unset(CMAKE_C_CPPCHECK)

add_library(unity_lib STATIC ./unity/src/unity.c)
target_include_directories(unity_lib PUBLIC unity/src)

add_library(cmock_lib STATIC ./cmock/src/cmock.c)
target_include_directories(cmock_lib PUBLIC cmock/src)
target_link_libraries(cmock_lib unity_lib)

endblock()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
include(FindLizard.cmake)
find_package(Lizard)
