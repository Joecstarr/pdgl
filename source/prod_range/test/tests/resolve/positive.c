#include "positive.h"
#include <prod_range.h>
#include "stdlib.h"
#include "unity.h"
#include "../../utils/test_utils_prod_range.h"
#include "unity_internals.h"
#include <pdgl_defs.h>

static void test_prod_range_resolve_positive_on_the_nose(void);
static void test_prod_range_resolve_positive_range(void);

void test_prod_range_resolve_positive(void)
{
    RUN_TEST(test_prod_range_resolve_positive_on_the_nose);
    RUN_TEST(test_prod_range_resolve_positive_range);
}

void test_prod_range_resolve_positive_on_the_nose(void)
{
    char str[DEFS_PDGL_MAX_STRING_SIZE] = { '\0' };
    prod_range_config_t cfg             = { 10, 10, str };
    const char *        out             = prod_range_resolve(&cfg);

    TEST_ASSERT_NOT_NULL(out);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("10", out, "");
}

void test_prod_range_resolve_positive_range(void)
{
    char str[DEFS_PDGL_MAX_STRING_SIZE] = { '\0' };
    prod_range_config_t cfg             = { -10, 10, str };
    const char *        out             = prod_range_resolve(&cfg);

    TEST_ASSERT_NOT_NULL(out);
    TEST_ASSERT_INT_WITHIN(10, 0, atoi(out));
}
