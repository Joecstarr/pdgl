add_executable(
  test_prod_range_app test_prod_range.c utils/test_utils_prod_range.c
                      ./tests/resolve/negative.c ./tests/resolve/positive.c)

target_link_libraries(test_prod_range_app prod_range_lib unity_lib cmock_lib)

add_test(NAME test_prod_range COMMAND test_prod_range_app)
