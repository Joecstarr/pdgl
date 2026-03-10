add_executable(
  test_prod_weighted_app
  test_prod_weighted.c utils/test_utils_prod_weighted.c
  ./tests/terminal/negative.c ./tests/terminal/positive.c
  ./tests/resolve/negative.c ./tests/resolve/positive.c)

target_link_libraries(test_prod_weighted_app prod_weighted_lib unity_lib
                      cmock_lib)

add_test(NAME test_prod_weighted COMMAND test_prod_weighted_app)
