/**
 *  \file prod_pure.h
 *
 *  \brief Defines the functionality of a pure production.
 *
 *
 *  \author Joe Starr
 *
 */

#ifndef PROD_PURE_H
#define PROD_PURE_H

/*************************************************************************************************/
/*************************** Includes ************************************************************/
/*************************************************************************************************/

#include <stddef.h>

/*************************************************************************************************/
/*************************** Defines *************************************************************/
/*************************************************************************************************/

/**
 * \brief The type identifier for the `pure` production type.
 */
#define PROD_PURE_NAME    ("pure")

/*************************************************************************************************/
/*************************** Typedefs ************************************************************/
/*************************************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \struct prod_pure_config_t
 * \brief Configuration type for a pure production.
 *
 */
typedef struct {
    char **repl_list; /**< List of strings serving as possible replacements in the production.*/
    size_t repl_len;  /**< The number of replacement strings in the list.*/
    char **term_list; /**< List of strings serving as possible terminals in the production.*/
    size_t term_len;  /**< The number of terminal strings in the list.*/
} prod_pure_config_t;


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
 * \brief The resolve function for the pure production type.
 *
 * Resolve at random a replacement string.
 *
 * \param config A configuration of a production.
 * \return A pointer to the output of the resolution.
 */
const char * prod_pure_resolve(const void *config);

/**
 * \brief The resolve function for the pure production type.
 *
 * Terminate at random with a terminal string.
 *
 * \param config A configuration of a production.
 * \return A pointer to the output of the resolution.
 */
const char * prod_pure_terminate(const void *config);

#ifdef __cplusplus
}
#endif


#endif /* end PROD_PURE_H*/
