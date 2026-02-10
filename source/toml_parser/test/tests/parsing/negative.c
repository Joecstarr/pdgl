#include <stdlib.h>
#include <toml_parser.h>
#include "production_store.h"
#include "unity.h"
#include "../../utils/test_utils_toml_parser.h"
#include <prod_pure.h>
/* cppcheck-suppress-begin constVariablePointer */
static void test_parsing_negative_null(void);
static void test_parsing_negative_malformed_toml(void);
static void test_parsing_negative_range_name(void);
static void test_parsing_negative_range_lower(void);
static void test_parsing_negative_range_upper(void);
static void test_parsing_negative_pure_name(void);
static void test_parsing_negative_pure_terminal(void);
static void test_parsing_negative_pure_transition(void);
static void test_parsing_negative_janet_name(void);
static void test_parsing_negative_janet_terminal(void);
static void test_parsing_negative_janet_transition(void);
static void test_parsing_negative_extra_values(void);
static void test_parsing_negative_range_name_type(void);
static void test_parsing_negative_range_lower_type(void);
static void test_parsing_negative_range_upper_type(void);
static void test_parsing_negative_pure_name_type(void);
static void test_parsing_negative_pure_terminal_type(void);
static void test_parsing_negative_pure_transition_type(void);
static void test_parsing_negative_janet_name_type(void);
static void test_parsing_negative_janet_terminal_type(void);
static void test_parsing_negative_janet_transition_type(void);
static void test_parsing_negative_no_entry(void);

void test_parsing_negative(void)
{
    RUN_TEST(test_parsing_negative_null);
    RUN_TEST(test_parsing_negative_malformed_toml);
    RUN_TEST(test_parsing_negative_range_name);
    RUN_TEST(test_parsing_negative_range_lower);
    RUN_TEST(test_parsing_negative_range_upper);
    RUN_TEST(test_parsing_negative_pure_name);
    RUN_TEST(test_parsing_negative_pure_terminal);
    RUN_TEST(test_parsing_negative_pure_transition);
    RUN_TEST(test_parsing_negative_janet_name);
    RUN_TEST(test_parsing_negative_janet_terminal);
    RUN_TEST(test_parsing_negative_janet_transition);
    RUN_TEST(test_parsing_negative_extra_values);
    RUN_TEST(test_parsing_negative_range_name_type);
    RUN_TEST(test_parsing_negative_range_lower_type);
    RUN_TEST(test_parsing_negative_range_upper_type);
    RUN_TEST(test_parsing_negative_pure_name_type);
    RUN_TEST(test_parsing_negative_pure_terminal_type);
    RUN_TEST(test_parsing_negative_pure_transition_type);
    RUN_TEST(test_parsing_negative_janet_name_type);
    RUN_TEST(test_parsing_negative_janet_terminal_type);
    RUN_TEST(test_parsing_negative_janet_transition_type);
    RUN_TEST(test_parsing_negative_no_entry);
}

static void test_parsing_negative_extra_values(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_pure_extra.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NOT_NULL(store);

    const prodstr_obj_t *pure = prodstr_find(store, "entry");
    TEST_ASSERT_NOT_NULL(pure);
    prod_pure_config_t *pure_cfg = (prod_pure_config_t *)pure->config;
    TEST_ASSERT_EQUAL_STRING(pure_cfg->term_list[0], "terminal");
    TEST_ASSERT_EQUAL_STRING(pure_cfg->trans_list[0], "transition");

    test_toml_parser_release_store(store);
}

static void test_parsing_negative_no_entry(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_no_entry.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_range_name(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_range_name.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_range_lower(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_range_lower.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_range_upper(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_range_upper.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_pure_name(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_pure_name.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_pure_terminal(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_pure_terminal.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_pure_transition(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_pure_transition.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_janet_name(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_janet_name.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_janet_terminal(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_janet_terminal.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_janet_transition(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_janet_transition.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_null(void)
{
    prodstr_store_t *const store = tomlprsr_parse(NULL);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_malformed_toml(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_malformed.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_range_name_type(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_range_name_type.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_range_lower_type(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_range_lower_type.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_range_upper_type(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_range_upper_type.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_pure_name_type(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_pure_name_type.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_pure_terminal_type(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_pure_terminal_type.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_pure_transition_type(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_pure_transition_type.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_janet_name_type(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_janet_name_type.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_janet_terminal_type(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_janet_terminal_type.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_janet_transition_type(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_janet_transition_type.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

/* cppcheck-suppress-end constVariablePointer */
