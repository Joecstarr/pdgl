#include <prod_janet.h>
#include "unity.h"
#include "../../utils/test_utils_prod_janet.h"
#include <pdgl_defs.h>

static void test_prod_janet_terminal_positive_null_param(void);

void test_prod_janet_terminal_positive(void)
{
    char script_tr[] = "(for i 0 10 (print `transition` ))";
    char script_te[] = "(for i 0 10 (print `a` ))";
    char out[DEFS_PDGL_MAX_STRING_SIZE] = { '\0' };
    prod_janet_config_t cof             = { script_tr, script_te, out, DEFS_PDGL_MAX_STRING_SIZE };
    const char *        output          = prod_janet_terminate(&cof);

    TEST_ASSERT_EQUAL_STRING_MESSAGE("aaaaaaaaaa", output, "");
}
