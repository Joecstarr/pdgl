add_library(prod_range_lib STATIC src/prod_range.c)

target_include_directories(prod_range_lib PUBLIC src)
target_link_libraries(prod_range_lib pdgl_defs)

set_target_properties(prod_range_lib
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
if(NOT CMAKE_BUILD_TYPE STREQUAL "Emscripten")
  add_subdirectory(test)
  add_lizard_target(prod_range_lib_lizard ALL ARGUMENTS --warnings_only)
endif(NOT CMAKE_BUILD_TYPE STREQUAL "Emscripten")
