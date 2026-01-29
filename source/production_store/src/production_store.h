/*!
 *  @file production_store.h
 *
 *  @brief  Describes the storage used for productions of a language.
 *
 *
 *  @author    Joe Starr
 *
 */

#ifndef PRODUCTION_STORE_H
#define PRODUCTION_STORE_H

/*************************************************************************************************/
/*************************** Includes ************************************************************/
/*************************************************************************************************/
#include <stddef.h>
#include <stdbool.h>

/*************************************************************************************************/
/*************************** Defines *************************************************************/
/*************************************************************************************************/

#define PRODSTR_TABLE_SIZE    (200u)

/*************************************************************************************************/
/*************************** Typedefs ************************************************************/
/*************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

typedef const char * (*resolve_funptr_t)(const void *config);

typedef const char * (*terminate_funptr_t)(const void *config);

/*!
 * @brief
 *
 */
typedef struct prodstr_obj_t {
    struct prodstr_obj_t *next;
    char *                name;
    char *                type;
    void *                config;
    resolve_funptr_t      res;
    terminate_funptr_t    term;
} prodstr_obj_t;



/*!
 * @brief
 *
 */
typedef struct {
    prodstr_obj_t *table[PRODSTR_TABLE_SIZE];
    size_t         production_count;
} prodstr_store_t;
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

bool prodstr_add(prodstr_store_t *store, prodstr_obj_t *prd);

const prodstr_obj_t *prodstr_find(const prodstr_store_t *store,
                                  const char *name);

#ifdef __cplusplus
}
#endif

#endif /* end PRODUCTION_STORE_H*/
