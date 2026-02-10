/**
 *  \file prod_pure.c
 *
 *  \brief Defines the functionality of a pure production.
 *
 *
 *  \author Joe Starr
 *
 */

#include "prod_pure.h"
#include <stddef.h>
#include <stdlib.h>
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

/* Docstring in header */
const char * prod_pure_resolve(const void *config)
{
    const char *retval = NULL;

    if (NULL != config)
    {
        const prod_pure_config_t *typed_cfg = (const prod_pure_config_t *)config;

        if ((0 < typed_cfg->trans_len) && (NULL != typed_cfg->trans_list))
        {
            size_t idx = rand() % typed_cfg->trans_len;

            retval = typed_cfg->trans_list[idx];
        }
    }
    return retval;
}

/* Docstring in header */
const char * prod_pure_terminate(const void *config)
{
    const char *retval = NULL;

    if (NULL != config)
    {
        const prod_pure_config_t *typed_cfg = (const prod_pure_config_t *)config;

        if ((0 < typed_cfg->term_len) && (NULL != typed_cfg->term_list))
        {
            size_t idx = rand() % typed_cfg->term_len;

            retval = typed_cfg->term_list[idx];
        }
    }
    return retval;
}

/*************************************************************************************************/
/************************** Private Function Definitions *****************************************/
/*************************************************************************************************/
