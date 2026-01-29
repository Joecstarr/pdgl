/*!
 *  @file prod_range.c
 *
 *  @brief Defines the functionality of a range production, yielding an integer in a given range.
 *
 *
 *  @author    Joe Starr
 *
 */

#include "prod_range.h"
#include <stdio.h>
#include <string.h>
#include <pdgl_defs.h>

/*************************************************************************************************/
/************************** Defines **************************************************************/
/*************************************************************************************************/

/*************************************************************************************************/
/************************** Private Function Declarations ****************************************/
/*************************************************************************************************/

/*************************************************************************************************/
/************************** Local Variables ******************************************************/
/*************************************************************************************************/

/*************************************************************************************************/
/************************** Public Function Definitions ******************************************/
/*************************************************************************************************/
/* cppcheck-suppress staticFunction */
const char * prod_range_resolve(const void *config)
{
    if (NULL != config)
    {
        const prod_range_config_t *typed_cfg = (const prod_range_config_t *)config;
        if (typed_cfg->lower_bound <= typed_cfg->upper_bound)
        {
            int value = rand() % ((typed_cfg->upper_bound) - (typed_cfg->lower_bound) + 1) +
                        typed_cfg->lower_bound;
            if (NULL != typed_cfg->out_str)
            {
                sprintf(typed_cfg->out_str, "%d", value);
                return typed_cfg->out_str;
            }
        }
    }
    return NULL;
}

const char * prod_range_terminate(const void *config)
{
    return prod_range_resolve(config);
}

/*************************************************************************************************/
/************************** Private Function Definitions *****************************************/
/*************************************************************************************************/
