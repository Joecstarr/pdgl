/**
 *  \file prod_weighted.h
 *
 *  \brief Defines the functionality of a weighted production.
 *
 *
 *  \author Joe Starr
 *
 */

#ifndef PROD_WEIGHTED_H
#define PROD_WEIGHTED_H

/*************************************************************************************************/
/*************************** Includes ************************************************************/
/*************************************************************************************************/

#include <stddef.h>
#include <stdint.h>

/*************************************************************************************************/
/*************************** Defines *************************************************************/
/*************************************************************************************************/

/**
 * \brief The type identifier for the `weighted` production type.
 */
#define PROD_WEIGHTED_NAME    ("weighted")

/*************************************************************************************************/
/*************************** Typedefs ************************************************************/
/*************************************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \struct prod_weighted_pair_t
 * \brief Configuration type for a weighted production.
 *
 */
typedef struct {
    char *   string; /**< List of strings serving as possible replacements in the production.*/
    uint64_t weight; /**< The number of terminal strings in the list.*/
} prod_weighted_pair_t;

/**
 * \struct prod_weighted_config_t
 * \brief Configuration type for a weighted production.
 *
 */
typedef struct {
    prod_weighted_pair_t *repl_list; /**< List of strings serving as possible replacements in the
                                      * production.*/
    size_t                repl_len;  /**< The number of replacement strings in the list.*/
    prod_weighted_pair_t *term_list; /**< List of strings serving as possible terminals in the
                                      * production.*/
    size_t                term_len;  /**< The number of terminal strings in the list.*/
} prod_weighted_config_t;


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
 * \brief The resolve function for the weighted production type.
 *
 * Resolve at random a replacement string.
 *
 * \param config A configuration of a production.
 * \return A pointer to the output of the resolution.
 */
const char * prod_weighted_resolve(const void *config);

/**
 * \brief The resolve function for the weighted production type.
 *
 * Terminate at random with a terminal string.
 *
 * \param config A configuration of a production.
 * \return A pointer to the output of the resolution.
 */
const char * prod_weighted_terminate(const void *config);

#ifdef __cplusplus
}
#endif


#endif /* end PROD_WEIGHTED_H*/
