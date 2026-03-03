#include <stdlib.h>
#include <toml_parser.h>
#include "production_store.h"
#include "unity.h"
#include "../../utils/test_utils_toml_parser.h"
#include <prod_pure.h>
/* cppcheck-suppress-begin constVariablePointer */
static void test_parsing_negative_null(void);
static void test_parsing_negative_malformed_toml(void);
static void test_parsing_negative_extra_values(void);
static void test_parsing_negative_no_entry(void);

static void test_parsing_negative_weighted_name(void);
static void test_parsing_negative_weighted_name_type(void);
static void test_parsing_negative_weighted_terminal(void);
static void test_parsing_negative_weighted_replacement(void);
static void test_parsing_negative_weighted_terminal_type(void);
static void test_parsing_negative_weighted_replacement_type(void);
static void test_parsing_negative_weighted_terminal_string(void);
static void test_parsing_negative_weighted_terminal_string_type(void);
static void test_parsing_negative_weighted_replacement_string(void);
static void test_parsing_negative_weighted_replacement_string_type(void);
static void test_parsing_negative_weighted_terminal_weight(void);
static void test_parsing_negative_weighted_terminal_weight_type(void);
static void test_parsing_negative_weighted_replacement_weight(void);
static void test_parsing_negative_weighted_replacement_weight_type(void);

static void test_parsing_negative_pure_name(void);
static void test_parsing_negative_pure_terminal(void);
static void test_parsing_negative_pure_replacement(void);
static void test_parsing_negative_pure_name_type(void);
static void test_parsing_negative_pure_terminal_type(void);
static void test_parsing_negative_pure_replacement_type(void);

static void test_parsing_negative_range_name(void);
static void test_parsing_negative_range_lower(void);
static void test_parsing_negative_range_upper(void);
static void test_parsing_negative_range_name_type(void);
static void test_parsing_negative_range_lower_type(void);
static void test_parsing_negative_range_upper_type(void);

static void test_parsing_negative_janet_name_type(void);
static void test_parsing_negative_janet_name(void);
static void test_parsing_negative_janet_terminal(void);
static void test_parsing_negative_janet_replacement(void);
static void test_parsing_negative_janet_terminal_type(void);
static void test_parsing_negative_janet_replacement_type(void);

void test_parsing_negative(void)
{
    RUN_TEST(test_parsing_negative_null);
    RUN_TEST(test_parsing_negative_malformed_toml);
    RUN_TEST(test_parsing_negative_extra_values);
    RUN_TEST(test_parsing_negative_no_entry);

    RUN_TEST(test_parsing_negative_weighted_name);
    RUN_TEST(test_parsing_negative_weighted_terminal);
    RUN_TEST(test_parsing_negative_weighted_replacement);
    RUN_TEST(test_parsing_negative_weighted_name_type);
    RUN_TEST(test_parsing_negative_weighted_terminal_type);
    RUN_TEST(test_parsing_negative_weighted_replacement_type);
    RUN_TEST(test_parsing_negative_weighted_terminal_string);
    RUN_TEST(test_parsing_negative_weighted_terminal_string_type);
    RUN_TEST(test_parsing_negative_weighted_replacement_string);
    RUN_TEST(test_parsing_negative_weighted_replacement_string_type);
    RUN_TEST(test_parsing_negative_weighted_terminal_weight);
    RUN_TEST(test_parsing_negative_weighted_terminal_weight_type);
    RUN_TEST(test_parsing_negative_weighted_replacement_weight);
    RUN_TEST(test_parsing_negative_weighted_replacement_weight_type);

    RUN_TEST(test_parsing_negative_pure_name);
    RUN_TEST(test_parsing_negative_pure_terminal);
    RUN_TEST(test_parsing_negative_pure_replacement);
    RUN_TEST(test_parsing_negative_pure_name_type);
    RUN_TEST(test_parsing_negative_pure_terminal_type);
    RUN_TEST(test_parsing_negative_pure_replacement_type);

    RUN_TEST(test_parsing_negative_range_name);
    RUN_TEST(test_parsing_negative_range_lower);
    RUN_TEST(test_parsing_negative_range_upper);
    RUN_TEST(test_parsing_negative_range_name_type);
    RUN_TEST(test_parsing_negative_range_lower_type);
    RUN_TEST(test_parsing_negative_range_upper_type);

    RUN_TEST(test_parsing_negative_janet_name_type);
    RUN_TEST(test_parsing_negative_janet_name);
    RUN_TEST(test_parsing_negative_janet_terminal);
    RUN_TEST(test_parsing_negative_janet_replacement);
    RUN_TEST(test_parsing_negative_janet_terminal_type);
    RUN_TEST(test_parsing_negative_janet_replacement_type);
}

/************************************************************************************************/
/**************** General Tests  ****************************************************************/
/************************************************************************************************/
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

static void test_parsing_negative_extra_values(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_pure_extra.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NOT_NULL(store);

    const prodstr_obj_t *pure = prodstr_find(store, "entry");
    TEST_ASSERT_NOT_NULL(pure);
    prod_pure_config_t *pure_cfg = (prod_pure_config_t *)pure->config;
    TEST_ASSERT_EQUAL_STRING(pure_cfg->term_list[0], "terminal");
    TEST_ASSERT_EQUAL_STRING(pure_cfg->repl_list[0], "replacement");

    test_toml_parser_release_store(store);
}

static void test_parsing_negative_no_entry(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_no_entry.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

/************************************************************************************************/
/**************** Pure Tests     ****************************************************************/
/************************************************************************************************/
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

static void test_parsing_negative_pure_replacement_type(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_pure_replacement_type.toml");
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

static void test_parsing_negative_pure_replacement(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_pure_replacement.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

/************************************************************************************************/
/**************** Range Tests    ****************************************************************/
/************************************************************************************************/
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

/************************************************************************************************/
/**************** Janet Tests  ******************************************************************/
/************************************************************************************************/

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

static void test_parsing_negative_janet_replacement(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_janet_replacement.toml");
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

static void test_parsing_negative_janet_replacement_type(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_janet_replacement_type.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

/************************************************************************************************/
/**************** Weighted Tests ****************************************************************/
/************************************************************************************************/
static void test_parsing_negative_weighted_name_type(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_weighted_name_type.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_weighted_name(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_weighted_name.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_weighted_terminal(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_weighted_terminal.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_weighted_replacement(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_weighted_replacement.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_weighted_terminal_type(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_weighted_terminal_type.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_weighted_replacement_type(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_weighted_replacement_type.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_weighted_terminal_string(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_weighted_terminal_string.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_weighted_replacement_string(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_weighted_replacement_string.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_weighted_terminal_string_type(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_weighted_terminal_string_type.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_weighted_replacement_string_type(void)
{
    char *toml_data =
        test_toml_parser_read_test_file("invalid_weighted_replacement_string_type.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_weighted_terminal_weight(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_weighted_terminal_weight.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_weighted_replacement_weight(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_weighted_replacement_weight.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_weighted_terminal_weight_type(void)
{
    char *toml_data = test_toml_parser_read_test_file("invalid_weighted_terminal_weight_type.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

static void test_parsing_negative_weighted_replacement_weight_type(void)
{
    char *toml_data =
        test_toml_parser_read_test_file("invalid_weighted_replacement_weight_type.toml");
    prodstr_store_t *const store = tomlprsr_parse(toml_data);

    TEST_ASSERT_NULL(store);
}

/* cppcheck-suppress-end constVariablePointer */
