add_executable(
  test_prod_pure_app
  test_prod_pure.c utils/test_utils_prod_pure.c ./tests/terminal/negative.c
  ./tests/terminal/positive.c ./tests/resolve/negative.c
  ./tests/resolve/positive.c)

target_link_libraries(test_prod_pure_app prod_pure_lib unity_lib cmock_lib)

add_test(NAME test_prod_pure COMMAND test_prod_pure_app)
