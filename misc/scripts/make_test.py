from pathlib import Path

docs = Path("../../source/")

for name in docs.glob("**/src/*.c"):
    module = name.parent.parent
    nn = name.stem
    module_test_dir = module / "test"
    module_tests_dir = module_test_dir / "tests"
    module_misc_dir = module_test_dir / "utils"

    module_misc_dir.mkdir(exist_ok=True, parents=True)
    module_test_dir.mkdir(exist_ok=True, parents=True)
    module_tests_dir.mkdir(exist_ok=True, parents=True)

    with open(module_misc_dir / f"test_utils_{nn}.c", "w") as file:
        content = f'#include "test_utils_{nn}.h"'
        file.write(content)

    with open(module_misc_dir / f"test_utils_{nn}.h", "w") as file:
        content = f"""/*!
 *  @file test_utils_{nn}.h
 *
 *  @brief  
 *
 *
 *  @author    Joe Starr
 *
 */

#ifndef {nn.replace(".", "_").upper()} 
#define {nn.replace(".", "_").upper()}

/******************************************************************************/
/*************************** Includes *****************************************/
/******************************************************************************/

/******************************************************************************/
/*************************** Defines ******************************************/
/******************************************************************************/

/******************************************************************************/
/*************************** Public Function Declarations *********************/
/******************************************************************************/

#endif /* end {nn.replace(".", "_").upper()}*/

"""
        file.write(content)

    with open(module_test_dir / f"test_{nn}.c", "w") as file:
        content = """#include "unity.h"

/******************************************************************************/
/*******************************Untested Frameworks****************************/
/******************************************************************************/

/******************************************************************************/
/******************************* Stubs ****************************************/
/******************************************************************************/

/******************************************************************************/
/*******************************Test Data**************************************/
/******************************************************************************/

/* clang-format off */

/* clang-format on */

/******************************************************************************/
/*******************************Test prep**************************************/
/******************************************************************************/

void setUp(void)
{
}

void tearDown(void)
{
}

/******************************************************************************/
/*******************************Test main**************************************/
/******************************************************************************/
int main(void)
{
    UNITY_BEGIN();
    return UNITY_END();
}
"""
        file.write(content)
        ...
    ...

    with open(module_test_dir / "CMakeLists.txt", "w") as file:
        content = f"""add_executable(test_{nn}_app
  test_{nn}.c
  utils/test_utils_{nn}.c)

target_link_libraries(test_{nn}_app
  unity_lib
  cmock_lib)

add_test(NAME test_{nn} COMMAND test_{nn}_app)
        """
        file.write(content)
        ...
    ...

    with open(module_tests_dir / ".gitkeep", "w") as file:
        content = ""
        file.write(content)
