/*!
 *  @file resolution_machine.h
 *
 *  @brief  Handles the production of a word in a language configured into a production store.
 *
 *
 *  @author    Joe Starr
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

/*
 *
 | Flag\bit                   | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
 | -------------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
 | Success                    | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   |
 | Fail                       | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 1   |
 | No Entry Symbol            | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |
 | NULL store                 | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   |
 | NULL stack                 | 0   | 0   | 0   | 0   | 1   | 0   | 0   | 0   |
 | NULL stream                | 0   | 0   | 0   | 1   | 0   | 0   | 0   | 0   |
 | `
 |
 */

/*!
 * @brief
 *
 */
#define RESMACH_EXECUTE_SUCCESS        (0x0u)

/*!
 * @brief
 *
 */
#define RESMACH_EXECUTE_FAIL           (0x1u)

/*!
 * @brief
 *
 */
#define RESMACH_EXECUTE_NO_ENTRY       (0x1u << 0x1u)

/*!
 * @brief
 *
 */
#define RESMACH_EXECUTE_NULL_STORE     (0x1u << 0x2u)

/*!
 * @brief
 *
 */
#define RESMACH_EXECUTE_NULL_STACK     (0x1u << 0x3u)

/*!
 * @brief
 *
 */
#define RESMACH_EXECUTE_NULL_STREAM    (0x1u << 0x4u)

/*************************************************************************************************/
/*************************** Typedefs ************************************************************/
/*************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief
 *
 */
typedef struct {
    char *      partial_ptr;
    const char *buff;
} resmach_partial_t;

/*!
 * @brief
 *
 */
typedef struct {
    resmach_partial_t * const partials;
    size_t                    stack_len;
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

uint8_t resmach_execute(const prodstr_store_t *store,
                        resmach_stack_t *stack,
                        FILE *stream);


#ifdef __cplusplus
}
#endif

#endif /* end RESOLUTION_MACHINE_H*/
