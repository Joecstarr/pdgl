/**
 *  \file production_store.h
 *
 *  \brief Describes the storage used for productions of a language.
 *
 *
 *  \author Joe Starr
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

/**
 * \brief The size of the production store hash table.
 */
#define PRODSTR_TABLE_SIZE    (200u)

/*************************************************************************************************/
/*************************** Typedefs ************************************************************/
/*************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \typedef resolve_funptr_t
 * \brief Function pointer type for a resolution function.
 */
typedef const char * (*resolve_funptr_t)(const void *config);

/**
 * \typedef terminate_funptr_t
 * \brief Function pointer type for a termination function.
 */
typedef const char * (*terminate_funptr_t)(const void *config);

/**
 * \struct prodstr_obj_s
 * \brief A production object to be placed in the production store.
 *
 */
struct prodstr_obj_s {
    struct prodstr_obj_s *next;   /**< A pointer to a production_object in a linked list of objects
                                   * with the same hash.*/
    char *                name;   /**< The name of the production object.*/
    char *                type;   /**< The ID for the type of production.*/
    void *                config; /**< The type specific configuration for the object. The void
                                   * pointer must be cast to a production specific version when
                                   * consumed.*/
    resolve_funptr_t      res;    /**< A resolution function pointer for the configured production
                                   * type.*/
    terminate_funptr_t    term;   /**< A termination function pointer for the configured production
                                   * type.*/
};

/**
 * \typedef prodstr_obj_t
 * \brief A production object to be placed in the production store.
 *
 * Separated to make Doxygen happy.
 *
 */
typedef struct prodstr_obj_s prodstr_obj_t;



/**
 * \struct prodstr_store_t
 * \brief Storage type for a production store.
 *
 */
typedef struct {
    prodstr_obj_t *table[PRODSTR_TABLE_SIZE]; /**< A hash table of production objects.*/
    size_t         count;                     /**< A count of objects in the store.*/
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

/**
 * \brief Add a production to the given store.
 *
 * Add the given production to the given store. Indicate success with true and failure with false.
 *
 * \param store The store to add to.
 * \param prd The production to add.
 * \return The success or failure of the addition.
 */
bool prodstr_add(prodstr_store_t *store, prodstr_obj_t *prd);

/**
 * \brief Find a production with the given name in the given store.
 *
 * Search the store for a production with the given name. Indicate success with a pointer to a
 *production. Indicate failure with a NULL pointer.
 *
 * \param store The store to search.
 * \param name The name to find.
 * \return A pointer to a production on success. A NULL pointer on failure.
 */
const prodstr_obj_t *prodstr_find(const prodstr_store_t *store,
                                  const char *name);

#ifdef __cplusplus
}
#endif

#endif /* end PRODUCTION_STORE_H*/
