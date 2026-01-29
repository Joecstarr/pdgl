add_library(prod_range_lib STATIC src/prod_range.c)

target_include_directories(prod_range_lib PUBLIC src)
target_link_libraries(prod_range_lib pdgl_defs)

add_lizard_target(prod_range_lib_lizard ALL ARGUMENTS --warnings_only)

set_target_properties(prod_range_lib
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")
add_subdirectory(test)
