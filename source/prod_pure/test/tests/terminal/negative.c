#include <prod_pure.h>
#include "negative.h"
#include "unity.h"
#include "../../utils/test_utils_prod_pure.h"

static void test_prod_pure_terminal_negative_null_config(void);
static void test_prod_pure_terminal_negative_null_term(void);
static void test_prod_pure_terminal_negative_zero_term(void);

void test_prod_pure_terminal_negative(void)
{
    RUN_TEST(test_prod_pure_terminal_negative_null_config);
    RUN_TEST(test_prod_pure_terminal_negative_null_term);
    RUN_TEST(test_prod_pure_terminal_negative_zero_term);
}

static void test_prod_pure_terminal_negative_null_config(void)
{
    const char *out = prod_pure_terminate(NULL);

    TEST_ASSERT_NULL(out);
}

static void test_prod_pure_terminal_negative_zero_term(void)

{
    char  term1[]          = "term";
    char *terms[]          = { term1 };
    char  trans1[]         = "trans";
    char *trans[]          = { trans1 };
    prod_pure_config_t cfg = { trans, 1, terms, 0 };
    const char *       out = prod_pure_terminate(&cfg);

    TEST_ASSERT_NULL(out);
}

static void test_prod_pure_terminal_negative_null_term(void)
{
    char  term1[]          = "term";
    char *terms[]          = { term1 };
    char  trans1[]         = "trans";
    char *trans[]          = { trans1 };
    prod_pure_config_t cfg = { trans, 1, NULL, 1 };
    const char *       out = prod_pure_terminate(&cfg);

    TEST_ASSERT_NULL(out);
}
