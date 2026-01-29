#include <toml_parser.h>
#include <unity.h>
#include "../../utils/test_utils_toml_parser.h"
#include "prod_range.h"
#include "prod_pure.h"
#include "prod_janet.h"
#include "production_store.h"

void test_parsing_positive(void)
{
    const char *           toml_data = test_toml_parser_read_test_file("valid_all_prod_types.toml");
    prodstr_store_t *const store     = tomlprsr_parse(toml_data);

    TEST_ASSERT_NOT_NULL(store);
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(store->production_count, 3, "");

    const prodstr_obj_t *range = prodstr_find(store, "range production");
    TEST_ASSERT_NOT_NULL(range);
    const prod_range_config_t *range_cfg = (prod_range_config_t *)range->config;
    TEST_ASSERT_EQUAL_INT32_MESSAGE(range_cfg->lower_bound, -10, "");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(range_cfg->upper_bound, 10, "");
    TEST_ASSERT_EQUAL_PTR(&prod_range_resolve, range->res);
    TEST_ASSERT_EQUAL_PTR(&prod_range_terminate, range->term);

    const prodstr_obj_t *pure = prodstr_find(store, "entry");
    TEST_ASSERT_NOT_NULL(pure);
    const prod_pure_config_t *pure_cfg = (prod_pure_config_t *)pure->config;
    TEST_ASSERT_EQUAL_STRING(pure_cfg->term_list[0], "terminal");
    TEST_ASSERT_EQUAL_STRING(pure_cfg->transition_list[0], "transition");
    TEST_ASSERT_EQUAL_STRING(pure_cfg->term_list[1], "terminal1");
    TEST_ASSERT_EQUAL_STRING(pure_cfg->transition_list[1], "transition1");
    TEST_ASSERT_EQUAL_INT(pure_cfg->term_len, 2);
    TEST_ASSERT_EQUAL_INT(pure_cfg->transition_len, 2);

    TEST_ASSERT_EQUAL_PTR(&prod_pure_resolve, pure->res);
    TEST_ASSERT_EQUAL_PTR(&prod_pure_terminate, pure->term);

    const prodstr_obj_t *janet = prodstr_find(store, "janet production");
    TEST_ASSERT_NOT_NULL(janet);
    const prod_janet_config_t *janet_cfg = (prod_janet_config_t *)janet->config;
    TEST_ASSERT_EQUAL_STRING(janet_cfg->term_str,
                             "#terminal script\n  (print \"terminal\")\n");
    TEST_ASSERT_EQUAL_STRING(janet_cfg->transition_str,
                             "#transition script\n  (print \"transition\")\n");
    TEST_ASSERT_EQUAL_PTR(&prod_janet_resolve, janet->res);
    TEST_ASSERT_EQUAL_PTR(&prod_janet_terminate, janet->term);

    test_toml_parser_release_store(store);
}
