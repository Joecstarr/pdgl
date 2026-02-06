if(NOT CMAKE_BUILD_TYPE STREQUAL "Emscripten")
  add_executable(pdgl_cli src/main.cpp)

  target_link_libraries(pdgl_cli toml_parser_lib production_store_lib
                        resolution_machine_lib pdgl_defs cxxopts_lib)

  target_include_directories(pdgl_cli PUBLIC src)
endif(NOT CMAKE_BUILD_TYPE STREQUAL "Emscripten")
