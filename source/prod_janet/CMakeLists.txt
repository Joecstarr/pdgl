add_library(prod_janet_lib STATIC src/prod_janet.c
                                  ${CMAKE_CURRENT_BINARY_DIR}/init_script.c)

target_include_directories(prod_janet_lib PUBLIC src)
target_link_libraries(prod_janet_lib pdgl_defs janet_lib fmem)

set_target_properties(prod_janet_lib
                      PROPERTIES IMPORTED_LINK_INTERFACE_LANGUAGES "C")

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/init_script.c
  COMMAND xxd -i init_script.janet > ${CMAKE_CURRENT_BINARY_DIR}/init_script.c
  DEPENDS ${SOURCE_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/src/init_script.janet
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Emscripten")
  add_lizard_target(prod_janet_lib_lizard ALL ARGUMENTS --warnings_only)
  add_subdirectory(test)
endif(NOT CMAKE_BUILD_TYPE STREQUAL "Emscripten")
