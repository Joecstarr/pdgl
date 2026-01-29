#include "negative.h"
#include <prod_range.h>
#include "unity.h"
#include "../../utils/test_utils_prod_range.h"
#include "unity_internals.h"
#include <pdgl_defs.h>

static void test_prod_range_resolve_negative_null(void);
static void test_prod_range_resolve_negative_bad_bound(void);
static void test_prod_range_resolve_negative_bad_string(void);

void test_prod_range_resolve_negative(void)
{
    RUN_TEST(test_prod_range_resolve_negative_null);
    RUN_TEST(test_prod_range_resolve_negative_bad_bound);
    RUN_TEST(test_prod_range_resolve_negative_bad_string);
}

static void test_prod_range_resolve_negative_null(void)
{
    const char *out = prod_range_resolve(NULL);

    TEST_ASSERT_NULL(out);
}

static void test_prod_range_resolve_negative_bad_bound(void)
{
    char str[DEFS_PDGL_MAX_STRING_SIZE] = { '\0' };
    prod_range_config_t cfg             = { 10, -10, str };
    const char *        out             = prod_range_resolve(&cfg);

    TEST_ASSERT_NULL(out);
}

static void test_prod_range_resolve_negative_bad_string(void)
{
    prod_range_config_t cfg = { 10, 10, NULL };
    const char *        out = prod_range_resolve(&cfg);

    TEST_ASSERT_NULL(out);
}
