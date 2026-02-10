#include <production_store.h>
#include <stdlib.h>
#include "unity.h"
#include "positive.h"
#include "../../utils/test_utils_production_store.h"
#include "unity_internals.h"

static void test_add_empty_store(void);
static void test_add_nonempty_store_col(void);
static void test_add_nonempty_store_no_col(void);

void test_add_positive(void)
{
    RUN_TEST(test_add_empty_store);
    RUN_TEST(test_add_nonempty_store_no_col);
    RUN_TEST(test_add_nonempty_store_col);
}

static void test_add_nonempty_store_col(void)
{
    void *          config           = malloc(sizeof(void *));
    char            name[]           = "Other Name";
    char            name_type[]      = "pure";
    prodstr_obj_t   prd              = { NULL, name, name_type, config, NULL, NULL };
    char            othername[]      = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    prodstr_obj_t   otherprd         = { NULL, othername, name_type, config, NULL, NULL };
    prodstr_store_t production_store = { { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, &otherprd,
                                           NULL, NULL, NULL },
                                         1 };

    bool result = prodstr_add(&production_store, &prd);

    TEST_ASSERT_EQUAL_UINT(2, production_store.count);
    TEST_ASSERT_EQUAL_UINT(true, result);
    const prodstr_obj_t *store_prd = production_store.table[196];
    TEST_ASSERT_NOT_NULL(store_prd);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(store_prd->name, name, "");
    TEST_ASSERT_NOT_NULL(store_prd->next);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(store_prd->next->name, othername, "");
    free(config);
}

static void test_add_nonempty_store_no_col(void)
{
    void *          config           = malloc(sizeof(void *));
    char            name[]           = "Name";
    char            name_type[]      = "pure";
    prodstr_obj_t   prd              = { NULL, name, name_type, config, NULL, NULL };
    char            othername[]      = "Other Name";
    prodstr_obj_t   otherprd         = { NULL, othername, name_type, config, NULL, NULL };
    prodstr_store_t production_store = { { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, &otherprd,
                                           NULL, NULL, NULL },
                                         1 };

    bool result = prodstr_add(&production_store, &prd);

    TEST_ASSERT_EQUAL_UINT(2, production_store.count);
    TEST_ASSERT_EQUAL_UINT(true, result);
    const prodstr_obj_t *store_prd = production_store.table[122];
    TEST_ASSERT_NOT_NULL(store_prd);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(store_prd->name, name, "");
    free(config);
}

static void test_add_empty_store(void)
{
    void *          config           = malloc(sizeof(void *));
    prodstr_store_t production_store = { { NULL }, 0 };
    char            name[]           = "Name";
    char            name_type[]      = "pure";
    prodstr_obj_t   prd = { NULL, name, name_type, config, NULL, NULL };

    bool result = prodstr_add(&production_store, &prd);

    TEST_ASSERT_EQUAL_UINT(1, production_store.count);
    TEST_ASSERT_EQUAL_UINT(true, result);
    const prodstr_obj_t *store_prd = production_store.table[122];
    TEST_ASSERT_NOT_NULL(store_prd);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(store_prd->name, name, "");
    free(config);
}
