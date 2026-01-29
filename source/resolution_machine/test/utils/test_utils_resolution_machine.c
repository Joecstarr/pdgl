#include "test_utils_resolution_machine.h"

const char * test_resmach_prod_resolve(const void *config)
{
    const test_resmach_prod_config_t *typed_cfg = (const test_resmach_prod_config_t *)config;

    return typed_cfg->transition_str;
}

const char * test_resmach_prod_terminate(const void *config)
{
    const test_resmach_prod_config_t *typed_cfg = (const test_resmach_prod_config_t *)config;

    return typed_cfg->term_str;
}
