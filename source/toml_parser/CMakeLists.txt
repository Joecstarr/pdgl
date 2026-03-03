add_library(toml_parser_lib STATIC src/toml_parser.c)

target_include_directories(toml_parser_lib PUBLIC src)
target_link_libraries(
  toml_parser_lib
  tomlc_lib
  production_store_lib
  pdgl_defs
  prod_pure_lib
  prod_weighted_lib
  prod_range_lib
  prod_janet_lib)

set_target_properties(toml_parser_lib
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")

if(NOT CMAKE_BUILD_TYPE STREQUAL "Emscripten")
  add_subdirectory(test)
  add_lizard_target(toml_parser_lib_lizard ALL ARGUMENTS --warnings_only)
endif(NOT CMAKE_BUILD_TYPE STREQUAL "Emscripten")
