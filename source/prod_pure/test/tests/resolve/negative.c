#include <prod_pure.h>
#include "negative.h"
#include "unity.h"
#include "../../utils/test_utils_prod_pure.h"

static void test_prod_pure_resolve_negative_null_config(void);
static void test_prod_pure_resolve_negative_null_trans(void);
static void test_prod_pure_resolve_negative_zero_trans(void);

void test_prod_pure_resolve_negative(void)
{
    RUN_TEST(test_prod_pure_resolve_negative_null_config);
    RUN_TEST(test_prod_pure_resolve_negative_null_trans);
    RUN_TEST(test_prod_pure_resolve_negative_zero_trans);
}

static void test_prod_pure_resolve_negative_null_config(void)
{
    const char *out = prod_pure_resolve(NULL);

    TEST_ASSERT_NULL(out);
}

static void test_prod_pure_resolve_negative_zero_trans(void)
{
    char  term1[]          = "term";
    char *terms[]          = { term1 };
    char  trans1[]         = "trans";
    char *trans[]          = { trans1 };
    prod_pure_config_t cfg = { trans, 0, terms, 1 };
    const char *       out = prod_pure_resolve(&cfg);

    TEST_ASSERT_NULL(out);
}

static void test_prod_pure_resolve_negative_null_trans(void)
{
    char  term1[]          = "term";
    char *terms[]          = { term1 };
    prod_pure_config_t cfg = { NULL, 1, terms, 1 };
    const char *       out = prod_pure_resolve(&cfg);

    TEST_ASSERT_NULL(out);
}
