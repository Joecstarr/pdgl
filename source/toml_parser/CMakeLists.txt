add_library(toml_parser_lib STATIC src/toml_parser.c)

target_include_directories(toml_parser_lib PUBLIC src)
target_link_libraries(
  toml_parser_lib
  tomlc_lib
  production_store_lib
  pdgl_defs
  prod_pure_lib
  prod_range_lib
  prod_janet_lib)

add_lizard_target(toml_parser_lib_lizard ALL ARGUMENTS --warnings_only)

set_target_properties(toml_parser_lib
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)
