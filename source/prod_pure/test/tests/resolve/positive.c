#include <prod_pure.h>
#include "positive.h"
#include "unity.h"
#include "../../utils/test_utils_prod_pure.h"
#include <string.h>

static void test_prod_pure_resolve_positive_single(void);
static void test_prod_pure_resolve_positive_multi(void);

void test_prod_pure_resolve_positive(void)
{
    RUN_TEST(test_prod_pure_resolve_positive_single);
    RUN_TEST(test_prod_pure_resolve_positive_multi);
}

void test_prod_pure_resolve_positive_single(void)
{
    char  term1[]          = "term";
    char *terms[]          = { term1 };
    char  trans1[]         = "trans";
    char *trans[]          = { trans1 };
    prod_pure_config_t cfg = { trans, 1, terms, 1 };
    const char *       out = prod_pure_resolve(&cfg);

    TEST_ASSERT_NOT_NULL(out);

    TEST_ASSERT_EQUAL_STRING_MESSAGE(trans1, out, "");
}

void test_prod_pure_resolve_positive_multi(void)
{
    char  term1[]          = "term1";
    char  term2[]          = "term2";
    char *terms[]          = { term1, term2 };
    char  trans1[]         = "trans1";
    char  trans2[]         = "trans2";
    char *trans[]          = { trans1, trans2 };
    prod_pure_config_t cfg = { trans, 2, terms, 2 };
    const char *       out = prod_pure_resolve(&cfg);

    TEST_ASSERT_NOT_NULL(out);

    if ((0 != strcmp(trans1, out)) && (0 != strcmp(trans2, out)))
    {
        TEST_FAIL();
    }
}
