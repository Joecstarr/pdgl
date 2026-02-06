add_executable(pdgl_wasm src/main.cpp)

target_link_libraries(pdgl_wasm toml_parser_lib production_store_lib
                      resolution_machine_lib fmem pdgl_defs)

target_include_directories(pdgl_wasm PUBLIC src)

if(CMAKE_BUILD_TYPE STREQUAL "Emscripten")
  set_target_properties(
    pdgl_wasm
    PROPERTIES
      LINK_FLAGS
      "-O3 -sALLOW_MEMORY_GROWTH  -s ENVIRONMENT=web --closure 1  -s SINGLE_FILE=1 -s EXPORTED_RUNTIME_METHODS=['FS'] -s EXPORT_ES6 --bind -s 'EXPORT_NAME=pdgl_wasm'"
  )
  add_custom_command(
    TARGET pdgl_wasm
    POST_BUILD
    COMMAND touch ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

  add_custom_command(
    TARGET pdgl_wasm
    POST_BUILD
    COMMAND
      mkdir -p ${CMAKE_BINARY_DIR}/pdgl_wasm_test_data/ && cp
      ${CMAKE_BINARY_DIR}/pdgl_wasm.js
      ${CMAKE_BINARY_DIR}/pdgl_wasm_test_data/pdgl_wasm.js)

  add_custom_command(
    TARGET pdgl_wasm
    POST_BUILD
    COMMAND
      mkdir -p ${CMAKE_BINARY_DIR}/pdgl_wasm_test_data/ && cp
      ${CMAKE_CURRENT_SOURCE_DIR}/test/*
      ${CMAKE_BINARY_DIR}/pdgl_wasm_test_data/)

endif(CMAKE_BUILD_TYPE STREQUAL "Emscripten")
