#include <prod_weighted.h>
#include "negative.h"
#include "unity.h"
#include "../../utils/test_utils_prod_weighted.h"

static void test_prod_weighted_terminal_negative_null_config(void);
static void test_prod_weighted_terminal_negative_null_term(void);
static void test_prod_weighted_terminal_negative_zero_term(void);
static void test_prod_weighted_terminal_negative_overflow_trans(void);

void test_prod_weighted_terminal_negative(void)
{
    RUN_TEST(test_prod_weighted_terminal_negative_null_config);
    RUN_TEST(test_prod_weighted_terminal_negative_null_term);
    RUN_TEST(test_prod_weighted_terminal_negative_zero_term);
    RUN_TEST(test_prod_weighted_terminal_negative_overflow_trans);
}

static void test_prod_weighted_terminal_negative_null_config(void)
{
    const char *out = prod_weighted_terminate(NULL);

    TEST_ASSERT_NULL(out);
}

static void test_prod_weighted_terminal_negative_zero_term(void)

{
    prod_weighted_pair_t   terms[] = {  };
    prod_weighted_pair_t   trans[] = { { "trans", 1 }, { "trans2", 1 } };
    prod_weighted_config_t cfg     = { trans, 2, terms, 0 };
    const char *           out     = prod_weighted_terminate(&cfg);

    TEST_ASSERT_NULL(out);
}

static void test_prod_weighted_terminal_negative_null_term(void)
{
    prod_weighted_pair_t   trans[] = { { "trans", 1 }, { "trans2", 1 } };
    prod_weighted_config_t cfg     = { trans, 2, NULL, 2 };
    const char *           out     = prod_weighted_terminate(&cfg);

    TEST_ASSERT_NULL(out);
}

static void test_prod_weighted_terminal_negative_overflow_trans(void)
{
    prod_weighted_pair_t   terms[] = { { "term", 1 }, { "term2", UINT64_MAX } };
    prod_weighted_pair_t   trans[] = { { "trans", 1 }, { "trans2", UINT64_MAX } };
    prod_weighted_config_t cfg     = { trans, 2, terms, 2 };
    const char *           out     = prod_weighted_terminate(&cfg);

    TEST_ASSERT_NULL(out);
}
