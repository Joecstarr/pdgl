add_executable(
  test_production_store_app
  test_production_store.c ./tests/add/negative.c ./tests/add/positive.c
  ./tests/find/negative.c ./tests/find/positive.c
  utils/test_utils_production_store.c)

target_link_libraries(test_production_store_app unity_lib cmock_lib
                      production_store_lib)

add_test(NAME test_production_store COMMAND test_production_store_app)
