add_library(prod_pure_lib STATIC src/prod_pure.c)

target_include_directories(prod_pure_lib PUBLIC src)
target_link_libraries(prod_pure_lib pdgl_defs)

add_lizard_target(prod_pure_lib_lizard ALL ARGUMENTS --warnings_only)

set_target_properties(prod_pure_lib PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES
                                               "C")
