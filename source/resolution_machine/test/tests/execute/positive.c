#include <resolution_machine.h>
#include "unity.h"
#include "../../utils/test_utils_resolution_machine.h"
#include "unity_internals.h"
#include <stdio.h>
#include <fmem.h>

static void test_execute_positive_valid_inputs(void);
static void test_execute_positive_terminal(void);



void test_execute_positive(void)
{
    RUN_TEST(test_execute_positive_valid_inputs);
    RUN_TEST(test_execute_positive_terminal);
}

static void test_execute_positive_valid_inputs(void)
{
    test_resmach_prod_config_t entry_cfg = { "Trans", "Term" };
    char              entry_name[]       = "entry";
    char              entry_type[]       = "pure";
    prodstr_obj_t     entry_prod         = { NULL,
                                             entry_name,
                                             entry_type,
                                             &entry_cfg,
                                             &test_resmach_prod_resolve,
                                             &test_resmach_prod_terminate };
    prodstr_store_t   production_store = { { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
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
                                             NULL, NULL, &entry_prod, NULL, NULL, NULL, NULL, NULL,
                                             NULL,
                                             NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                             NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                             NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                             NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                             NULL, NULL, NULL },
                                           1 };
    char              part_buff[DEFS_PDGL_MAX_STRING_SIZE] = { '\0' };
    resmach_partial_t partial     = { part_buff, part_buff };
    resmach_partial_t partials[1] = { partial };
    resmach_stack_t   stack       = { partials, 1 };
    char *            buffer      = NULL;
    size_t            bufferSize  = 0;
    fmem              fm;

    fmem_init(&fm);

    FILE *  stream = fmem_open(&fm, "w+");
    uint8_t retval = resmach_execute(&production_store, &stack, stream);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(RESMACH_EXECUTE_SUCCESS, retval, "");

    fflush(stream);
    fmem_mem(&fm, (void *)&buffer, &bufferSize);

    TEST_ASSERT_EQUAL_STRING_MESSAGE(entry_cfg.trans_str, buffer, "");
    fmem_term(&fm);
}

static void test_execute_positive_terminal(void)
{
    test_resmach_prod_config_t entry_cfg = { "entry(%{terminal})", "Term" };
    char          entry_name[]           = "entry";
    char          entry_type[]           = "pure";
    prodstr_obj_t entry_prd = { NULL,
                                entry_name,
                                entry_type,
                                &entry_cfg,
                                &test_resmach_prod_resolve,
                                &test_resmach_prod_terminate };
    test_resmach_prod_config_t terminal_cfg = { "term_trans", "term_term" };
    char              terminal_name[]       = "terminal";
    char              terminal_type[]       = "pure";
    prodstr_obj_t     terminal_prd          = { NULL,
                                                terminal_name,
                                                terminal_type,
                                                &terminal_cfg,
                                                &test_resmach_prod_resolve,
                                                &test_resmach_prod_terminate };
    prodstr_store_t   production_store = { { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
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
                                             NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                             &terminal_prd,
                                             NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                             NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                             NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                             NULL, NULL, &entry_prd, NULL, NULL, NULL, NULL, NULL,
                                             NULL,
                                             NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                             NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                             NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                             NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                             NULL, NULL, NULL },
                                           1 };
    char              part_buff[DEFS_PDGL_MAX_STRING_SIZE] = { '\0' };
    resmach_partial_t partial     = { part_buff, part_buff };
    resmach_partial_t partials[1] = { partial };
    resmach_stack_t   stack       = { partials, 1 };
    char *            buffer      = NULL;
    size_t            bufferSize  = 0;
    fmem              fm;

    fmem_init(&fm);

    FILE *  stream = fmem_open(&fm, "w+");
    uint8_t retval = resmach_execute(&production_store, &stack, stream);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(RESMACH_EXECUTE_SUCCESS, retval, "");

    fflush(stream);
    fmem_mem(&fm, (void *)&buffer, &bufferSize);

    TEST_ASSERT_EQUAL_STRING_MESSAGE("entry(term_term)", buffer, "");

    fmem_term(&fm);
}
