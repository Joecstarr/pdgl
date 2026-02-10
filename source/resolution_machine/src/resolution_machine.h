/**
 *  \file resolution_machine.h
 *
 *  \brief Handle the production of a word in a language configured into a production store.
 *
 *
 *  \author Joe Starr
 *
 */

#ifndef RESOLUTION_MACHINE_H
#define RESOLUTION_MACHINE_H

/*************************************************************************************************/
/*************************** Includes ************************************************************/
/*************************************************************************************************/
#include <production_store.h>
#include <pdgl_defs.h>
#include <stdio.h>

/*************************************************************************************************/
/*************************** Defines *************************************************************/
/*************************************************************************************************/

/*************************** Execute Flags *******************************************************/

/**
 * \brief The execution was successful.
 */
#define RESMACH_EXECUTE_SUCCESS        (0x0u)

/**
 * \brief The execution was unsuccessful.
 *
 * | Flag \ bit                 | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
 * | -------------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
 * | Fail                       | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 1   |
 * | No Entry Symbol            | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |
 * | NULL store                 | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   |
 * | NULL stack                 | 0   | 0   | 0   | 0   | 1   | 0   | 0   | 0   |
 * | NULL stream                | 0   | 0   | 0   | 1   | 0   | 0   | 0   | 0   |
 */
#define RESMACH_EXECUTE_FAIL           (0x1u)

/**
 * \brief The execution was unsuccessful with a TOML error for missing entry symbol.
 */
#define RESMACH_EXECUTE_NO_ENTRY       (0x1u << 0x1u)

/**
 * \brief The execution was unsuccessful with a NULL pointer to the production store.
 */
#define RESMACH_EXECUTE_NULL_STORE     (0x1u << 0x2u)

/**
 * \brief The execution was unsuccessful with a NULL pointer to the stack.
 */
#define RESMACH_EXECUTE_NULL_STACK     (0x1u << 0x3u)

/**
 * \brief The execution was unsuccessful with a NULL pointer to an output stream.
 */
#define RESMACH_EXECUTE_NULL_STREAM    (0x1u << 0x4u)

/*************************************************************************************************/
/*************************** Typedefs ************************************************************/
/*************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \struct resmach_partial_t
 * \brief The type of a partial resolution placeholder.
 *
 */
typedef struct {
    char *      partial_ptr; /**< A pointer to the next index in the partial buffer to proccess.*/
    const char *buff;        /**< A pointer to a const char buffer to use for storing the string
                              * being resolved.*/
} resmach_partial_t;

/**
 * \struct resmach_stack_t
 * \brief A stack of resolution partials being resolved.
 *
 */
typedef struct {
    resmach_partial_t *partials;  /**< A pointer to a list of partials to use as the stack.*/
    size_t             stack_len; /**< The number of partials on the stack.*/
} resmach_stack_t;


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
 * \brief Execute the production of a word in the language found in the production store.
 *
 * Utilizing the given stack execute the production of a word in the language configured in the
 *production store. Output the results of the execution to the configured stream.
 *
 *
 * \param store A production store containing a DGL
 * \param stack A stack of partial resolutions.
 * \param stream An output stream.
 * \return A status flag indicating success.
 */
uint8_t resmach_execute(const prodstr_store_t *store,
                        resmach_stack_t *stack,
                        FILE *stream);


#ifdef __cplusplus
}
#endif

#endif /* end RESOLUTION_MACHINE_H*/
