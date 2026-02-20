#include <prod_janet.h>
#include "pdgl_defs.h"
#include "unity.h"
#include "../../utils/test_utils_prod_janet.h"
#include "unity_internals.h"

static void test_prod_janet_resolve_negative_null_config(void);
static void test_prod_janet_resolve_negative_null_trans(void);
static void test_prod_janet_resolve_negative_zero_len_out(void);
static void test_prod_janet_resolve_negative_null_out(void);

void test_prod_janet_resolve_negative(void)
{
    RUN_TEST(test_prod_janet_resolve_negative_null_config);
    RUN_TEST(test_prod_janet_resolve_negative_null_trans);
    RUN_TEST(test_prod_janet_resolve_negative_zero_len_out);
    RUN_TEST(test_prod_janet_resolve_negative_null_out);
}

STATIC_INLINE void test_prod_janet_resolve_negative_zero_len_out(void)
{
    char script_tr[] = "(print `replacement` )";
    char script_te[] = "(print `terminal` )";
    char out[DEFS_PDGL_MAX_STRING_SIZE] = { '\0' };
    prod_janet_config_t cof             = { script_tr, script_te, out, 0 };
    const char *        output          = prod_janet_resolve(&cof);

    TEST_ASSERT_NULL(output);
}

STATIC_INLINE void test_prod_janet_resolve_negative_null_out(void)
{
    char script_tr[]           = "(print `replacement` )";
    char script_te[]           = "(print `terminal` )";
    prod_janet_config_t cof    = { script_tr, script_te, NULL, DEFS_PDGL_MAX_STRING_SIZE };
    const char *        output = prod_janet_resolve(&cof);

    TEST_ASSERT_NULL(output);
}

static void test_prod_janet_resolve_negative_null_config(void)
{
    const char *output = prod_janet_resolve(NULL);

    TEST_ASSERT_NULL(output);
}

static void test_prod_janet_resolve_negative_null_trans(void)
{
    char script_te[] = "(print `terminal` )";
    char out[DEFS_PDGL_MAX_STRING_SIZE] = { '\0' };
    prod_janet_config_t cof             = { NULL, script_te, out, 0 };
    const char *        output          = prod_janet_resolve(&cof);

    TEST_ASSERT_NULL(output);
}
