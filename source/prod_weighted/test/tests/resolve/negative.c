#include <prod_weighted.h>
#include "negative.h"
#include "unity.h"
#include "../../utils/test_utils_prod_weighted.h"
#include "unity_internals.h"

static void test_prod_weighted_resolve_negative_null_config(void);
static void test_prod_weighted_resolve_negative_null_trans(void);
static void test_prod_weighted_resolve_negative_zero_trans(void);
static void test_prod_weighted_resolve_negative_overflow_trans(void);

void test_prod_weighted_resolve_negative(void)
{
    RUN_TEST(test_prod_weighted_resolve_negative_null_config);
    RUN_TEST(test_prod_weighted_resolve_negative_null_trans);
    RUN_TEST(test_prod_weighted_resolve_negative_zero_trans);
    RUN_TEST(test_prod_weighted_resolve_negative_overflow_trans);
}

static void test_prod_weighted_resolve_negative_null_config(void)
{
    const char *out = prod_weighted_resolve(NULL);

    TEST_ASSERT_NULL(out);
}

static void test_prod_weighted_resolve_negative_zero_trans(void)
{
    prod_weighted_pair_t   terms[] = { { "term", 1 } };
    prod_weighted_pair_t   trans[] = { { "trans", 1 } };
    prod_weighted_config_t cfg     = { trans, 0, terms, 1 };
    const char *           out     = prod_weighted_resolve(&cfg);

    TEST_ASSERT_NULL(out);
}

static void test_prod_weighted_resolve_negative_null_trans(void)
{
    prod_weighted_pair_t   terms[] = { { "term", 1 } };
    prod_weighted_config_t cfg     = { NULL, 1, terms, 1 };
    const char *           out     = prod_weighted_resolve(&cfg);

    TEST_ASSERT_NULL(out);
}

static void test_prod_weighted_resolve_negative_overflow_trans(void)
{
    prod_weighted_pair_t   terms[] = { { "term", 1 }, { "term2", UINT64_MAX } };
    prod_weighted_pair_t   trans[] = { { "trans", 1 }, { "trans2", UINT64_MAX } };
    prod_weighted_config_t cfg     = { trans, 2, terms, 2 };
    const char *           out     = prod_weighted_resolve(&cfg);

    TEST_ASSERT_NULL(out);
}
