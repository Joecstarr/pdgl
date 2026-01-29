add_executable(
  test_prod_janet_app
  test_prod_janet.c utils/test_utils_prod_janet.c ./tests/terminal/negative.c
  ./tests/terminal/positive.c ./tests/resolve/negative.c
  ./tests/resolve/positive.c)

target_link_libraries(test_prod_janet_app prod_janet_lib unity_lib cmock_lib)

add_test(NAME test_prod_janet COMMAND test_prod_janet_app)
