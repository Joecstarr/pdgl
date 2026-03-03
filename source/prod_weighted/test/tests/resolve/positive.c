#include <prod_weighted.h>
#include "positive.h"
#include "unity.h"
#include "../../utils/test_utils_prod_weighted.h"
#include <string.h>

static void test_prod_weighted_resolve_positive_single(void);
static void test_prod_weighted_resolve_positive_multi(void);

void test_prod_weighted_resolve_positive(void)
{
    RUN_TEST(test_prod_weighted_resolve_positive_single);
    RUN_TEST(test_prod_weighted_resolve_positive_multi);
}

void test_prod_weighted_resolve_positive_single(void)
{
    prod_weighted_pair_t   terms[] = { { "term", 1 } };
    prod_weighted_pair_t   trans[] = { { "trans", 1 } };
    prod_weighted_config_t cfg     = { trans, 1, terms, 1 };
    const char *           out     = prod_weighted_resolve(&cfg);

    TEST_ASSERT_NOT_NULL(out);

    TEST_ASSERT_EQUAL_STRING_MESSAGE(trans[0].string, out, "");
}

void test_prod_weighted_resolve_positive_multi(void)
{
    prod_weighted_pair_t   terms[] = { { "term", 1 }, { "term2", 2 } };
    prod_weighted_pair_t   trans[] = { { "trans", 1 }, { "trans2", 2 } };
    prod_weighted_config_t cfg     = { trans, 2, terms, 2 };

    int    count1 = 0;
    int    count2 = 0;
    size_t i;

    for (i = 0; i < 3000; i++)
    {
        const char *out = prod_weighted_resolve(&cfg);
        TEST_ASSERT_NOT_NULL(out);
        if (0 == strcmp(trans[0].string, out))
        {
            count1++;
        }
        else if (0 == strcmp(trans[1].string, out))
        {
            count2++;
        }
        else
        {
            TEST_FAIL();
        }
    }

    double X2 = ((count2 - 2000.0) * (count2 - 2000.0)) / 2000.0;
    X2 += ((count1 - 1000.0) * (count1 - 1000.0)) / 1000.0;
    /*https://www.itl.nist.gov/div898/handbook/eda/section3/eda3674.htm*/
    TEST_ASSERT_LESS_THAN_FLOAT_MESSAGE(10.828, X2, "Sample rate bad");
}
