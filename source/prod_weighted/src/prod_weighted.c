/**
 *  \file prod_weighted.c
 *
 *  \brief Defines the functionality of a weighted production.
 *
 *
 *  \author Joe Starr
 *
 */

#include "prod_weighted.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <pdgl_defs.h>

/*************************************************************************************************/
/************************** Defines **************************************************************/
/*************************************************************************************************/

/**
 * \brief Posted by chux, modified by community. See post 'Timeline' for change history Retrieved
 *2026-03-11, License - CC BY-SA 4.0
 */
#define IMAX_BITS(m)    ((m) / ((m) % 255 + 1) / 255 % 255 * 8 + 7 - 86 / ((m) % 255 + 12))

/**
 * \brief Posted by chux, modified by community. See post 'Timeline' for change history Retrieved
 *2026-03-11, License - CC BY-SA 4.0
 */
#define RAND_MAX_WIDTH    IMAX_BITS(RAND_MAX)

/*************************************************************************************************/
/************************** Private Function Declarations ****************************************/
/*************************************************************************************************/

STATIC_INLINE uint64_t  prod_weighted_sum(prod_weighted_pair_t *pairs, size_t pairs_len);
STATIC_INLINE const char *prod_weighted_select(prod_weighted_pair_t *pairs, size_t pairs_len);
STATIC_INLINE uint64_t rand_uint64(void);

/*************************************************************************************************/
/************************** Local Variables ******************************************************/
/*************************************************************************************************/

/*************************************************************************************************/
/************************** Public Function Definitions ******************************************/
/*************************************************************************************************/

/* Docstring in header */
const char * prod_weighted_resolve(const void *config)
{
    const char *retval = NULL;

    if (NULL != config)
    {
        const prod_weighted_config_t *typed_cfg = (const prod_weighted_config_t *)config;

        if ((0 < typed_cfg->repl_len) && (NULL != typed_cfg->repl_list))
        {
            retval = prod_weighted_select(typed_cfg->repl_list, typed_cfg->repl_len);
        }
    }
    return retval;
}

/* Docstring in header */
const char * prod_weighted_terminate(const void *config)
{
    const char *retval = NULL;

    if (NULL != config)
    {
        const prod_weighted_config_t *typed_cfg = (const prod_weighted_config_t *)config;

        if ((0 < typed_cfg->term_len) && (NULL != typed_cfg->term_list))
        {
            retval = prod_weighted_select(typed_cfg->term_list, typed_cfg->repl_len);
        }
    }
    return retval;
}

/*************************************************************************************************/
/************************** Private Function Definitions *****************************************/
/*************************************************************************************************/

/**
 * \brief Compute the sum of the weights for an input list of string/weight pairs.
 *
 * \param pairs A list of string/weight pairs.
 * \param pairs_len The length of the input list.
 * \return The sum of the weights from the list.
 */
STATIC_INLINE uint64_t prod_weighted_sum(prod_weighted_pair_t *pairs, size_t pairs_len)
{
    size_t   i;
    uint64_t retval = 0u;

    for (i = 0u; i < pairs_len; i++)
    {
        if (retval < (UINT64_MAX - pairs[i].weight))
        {
            retval += pairs[i].weight;
        }
        else
        {
            return 0u;
        }
    }
    return retval;
}

/**
 * \brief Select by weighted random selection a string from a list of string/weight pairs.
 *
 * Compute the sum of the selection weights. Then compute a random integer $r$ between 0 and the
 *sum. Determine which partial sum holds $r$ and report that string.
 *
 * \param pairs A list of string/weight pairs.
 * \param pairs_len The length of the input list.
 * \return The selected string or NULL on an error.
 */
STATIC_INLINE const char *prod_weighted_select(prod_weighted_pair_t *pairs, size_t pairs_len)
{
    const char *retval = NULL;

    uint64_t sum = prod_weighted_sum(pairs, pairs_len);

    if (sum != 0)
    {
        size_t   i;
        uint64_t idx = rand_uint64();
        idx %= sum;

        uint64_t part_sum = 0;
        for (i = 0; i < pairs_len; i++)
        {
            part_sum += pairs[i].weight;
            if (idx < part_sum)
            {
                retval = pairs[i].string;
                break;
            }
        }
    }
    return retval;
}

/**
 * \brief Select by weighted random selection a string from a list of string/weight pairs.
 *
 * Posted by chux, modified by community. See post
 *'Timeline' for change history Retrieved 2026-03-11, License - CC BY-SA 4.0
 *
 * \return A random uint64
 */
STATIC_INLINE uint64_t rand_uint64(void)
{
    uint64_t retval = 0;
    size_t   i;

    for (i = 0; i < 64; i += RAND_MAX_WIDTH)
    {
        retval <<= RAND_MAX_WIDTH;
        retval  ^= (unsigned)rand();
    }
    return retval;
}
