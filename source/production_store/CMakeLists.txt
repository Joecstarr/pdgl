add_library(production_store_lib STATIC src/production_store.c)

target_include_directories(production_store_lib PUBLIC src)
target_link_libraries(production_store_lib pdgl_defs)

set_target_properties(production_store_lib
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")

if(NOT CMAKE_BUILD_TYPE STREQUAL "Emscripten")
  add_subdirectory(test)
  add_lizard_target(production_store_lib_lizard ALL ARGUMENTS --warnings_only)
endif(NOT CMAKE_BUILD_TYPE STREQUAL "Emscripten")
