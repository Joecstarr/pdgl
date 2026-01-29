add_executable(
  test_resolution_machine_app
  test_resolution_machine.c ./tests/execute/negative.c
  ./tests/execute/positive.c ./utils/test_utils_resolution_machine.c)

target_link_libraries(test_resolution_machine_app unity_lib cmock_lib
                      resolution_machine_lib fmem)

add_test(NAME test_resolution_machine COMMAND test_resolution_machine_app)
