#include <prod_janet.h>
#include "unity.h"
#include <pdgl_defs.h>
#include "../../utils/test_utils_prod_janet.h"

static void test_prod_janet_resolve_positive_null_param(void);

void test_prod_janet_resolve_positive(void)
{
    char script_tr[] = "(for i 0 10 (print `b` ))";
    char script_te[] = "(print `terminal` )";
    char out[DEFS_PDGL_MAX_STRING_SIZE] = { '\0' };
    prod_janet_config_t cof             = { script_tr, script_te, out, DEFS_PDGL_MAX_STRING_SIZE };
    const char *        output          = prod_janet_resolve(&cof);

    TEST_ASSERT_NOT_NULL(output);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("bbbbbbbbbb", output, "");
}
