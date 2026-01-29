add_executable(
  test_toml_parser_app test_toml_parser.c utils/test_utils_toml_parser.c
                       ./tests/parsing/positive.c ./tests/parsing/negative.c)

target_link_libraries(
  test_toml_parser_app
  unity_lib
  cmock_lib
  toml_parser_lib
  prod_pure_lib
  prod_range_lib
  prod_janet_lib)

add_custom_command(
  TARGET test_toml_parser_app
  POST_BUILD
  COMMAND
    mkdir -p ${CMAKE_BINARY_DIR}/toml_parser_test_data/ && cp
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/data/*
    ${CMAKE_BINARY_DIR}/toml_parser_test_data/)

add_test(
  NAME test_toml_parser
  COMMAND test_toml_parser_app
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
