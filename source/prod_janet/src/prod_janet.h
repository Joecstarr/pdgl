/**
 *  \file prod_janet.h
 *
 *  \brief Defines the functionality of a Janet production, allowing for injection of arbitrary
 *Janet code.
 *
 *
 *  \author Joe Starr
 *
 */

#ifndef PROD_JANET_H
#define PROD_JANET_H

/*************************************************************************************************/
/*************************** Includes ************************************************************/
/*************************************************************************************************/
#include <stddef.h>

/*************************************************************************************************/
/*************************** Defines *************************************************************/
/*************************************************************************************************/

/**
 * \brief The type identifier for the `janet` production type.
 */
#define PROD_JANET_NAME    ("janet")

/*************************************************************************************************/
/*************************** Typedefs ************************************************************/
/*************************************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \struct prod_janet_config_t
 *
 * \brief Configuration type for a Janet production.
 */
typedef struct {
    char * trans_str;   /**< A pointer to the transition script as a string.*/
    char * term_str;    /**< A pointer to the termination script as a string.*/
    char * out_str;     /**< A pointer to an output string buffer.*/
    size_t out_str_len; /**< The length of the output buffer.*/
} prod_janet_config_t;


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
 * \brief The resolve function for the Janet production type.
 *
 * Starts a Janet VM and executes the configured resolution script.
 *
 * \param config A configuration of a production.
 * \return A pointer to the output of the resolution.
 */
const char * prod_janet_resolve(const void *config);

/**
 * \brief The resolve function for the Janet production type.
 *
 * Starts a Janet VM and executes the configured terminal script.
 *
 * \param config A configuration of a production.
 * \return A pointer to the output of the resolution.
 */
const char * prod_janet_terminate(const void *config);

#ifdef __cplusplus
}
#endif


#endif /* end PROD_JANET_H*/
