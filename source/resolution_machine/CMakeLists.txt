add_library(resolution_machine_lib STATIC src/resolution_machine.c)

target_include_directories(resolution_machine_lib PUBLIC src)
target_link_libraries(resolution_machine_lib production_store_lib pdgl_defs)

set_target_properties(resolution_machine_lib
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")

if(NOT CMAKE_BUILD_TYPE STREQUAL "Emscripten")
  add_subdirectory(test)
  add_lizard_target(resolution_machine_lib_lizard ALL ARGUMENTS --warnings_only)
endif(NOT CMAKE_BUILD_TYPE STREQUAL "Emscripten")
