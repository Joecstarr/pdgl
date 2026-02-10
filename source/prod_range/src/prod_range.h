/**
 *  \file prod_range.h
 *
 *  \brief Defines the functionality of a range production, yielding an integer in a given range.
 *
 *
 *  \author Joe Starr
 *
 */

#ifndef PROD_RANGE_H
#define PROD_RANGE_H

/*************************************************************************************************/
/*************************** Includes ************************************************************/
/*************************************************************************************************/

#include <stddef.h>

/*************************************************************************************************/
/*************************** Defines *************************************************************/
/*************************************************************************************************/

/**
 * \brief The type identifier for the `range` production type.
 */
#define PROD_RANGE_NAME    ("range")

/*************************************************************************************************/
/*************************** Typedefs ************************************************************/
/*************************************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \struct prod_range_config_t
 * \brief Configuration type for a Janet production.
 *
 */
typedef struct {
    int    lower_bound; /**< Lower bound for random number generation. Inclusive.*/
    int    upper_bound; /**< Upper bound for random number generation. Inclusive.*/
    char * out_str;     /**< A pointer to an output string buffer.*/
    size_t out_str_len; /**< The length of the output buffer.*/
} prod_range_config_t;


#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
/*************************** Public Function Declarations ****************************************/
/*************************************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif


/**
 * \brief The resolve function for the range production type.
 *
 * Randomly select an integer between a lower and upper bound. Convert to a string stored in an
 *output buffer for the configured production.
 *
 * \param config A configuration of a production.
 * \return A pointer to the output of the resolution.
 */
const char * prod_range_resolve(const void *config);

/**
 * \brief The resolve function for the range production type.
 *
 * Calls the resolve function.
 *
 * \param config A configuration of a production.
 * \return A pointer to the output of the resolution.
 */
const char * prod_range_terminate(const void *config);

#ifdef __cplusplus
}
#endif


#endif /* end PROD_RANGE_H */
