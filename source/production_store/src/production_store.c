/**
 *  \file production_store.c
 *
 *  \brief Describes the storage used for productions of a language.
 *
 *
 *  \author Joe Starr
 *
 */

#include "production_store.h"
#include <string.h>
#include <pdgl_defs.h>
#include <stddef.h>
#include <string.h>

/*************************************************************************************************/
/************************** Defines **************************************************************/
/*************************************************************************************************/

/*************************************************************************************************/
/************************** Private Function Declarations ****************************************/
/*************************************************************************************************/
STATIC_INLINE size_t prodstr_hash(const void *buf, size_t buflength);

/*************************************************************************************************/
/************************** Local Variables ******************************************************/
/*************************************************************************************************/

/*************************************************************************************************/
/************************** Public Function Definitions ******************************************/
/*************************************************************************************************/

/* Docstring in header*/
bool prodstr_add(prodstr_store_t *store, prodstr_obj_t *prd)
{
    if (NULL == store)
    {
        return false;
    }
    else if (NULL == prd)
    {
        return false;
    }
    else if (NULL == prd->name)
    {
        return false;
    }
    else if (NULL == prd->type)
    {
        return false;
    }
    else if (NULL == prd->config)
    {
        return false;
    }
    else
    {
        /* Hash the name*/
        size_t hash = prodstr_hash(prd->name, strlen(prd->name));
        /* If the bucket for hash is full add to the linked list*/
        if (NULL != store->table[hash])
        {
            /* Make sure nothing in the list shares the name*/
            prodstr_obj_t *tblprd = store->table[hash];
            do{
                if (0 == strcmp(tblprd->name, prd->name))
                {
                    return false;
                }
                tblprd = tblprd->next;
            }while (NULL != tblprd);

            /* Set current head to next of new production*/
            prodstr_obj_t *old_obj = store->table[hash];
            prd->next = old_obj;
        }
        /* Add production to table at hash*/
        store->table[hash] = prd;
        store->count++;
        return true;
    }
}

/* Docstring in header*/
const prodstr_obj_t * prodstr_find(const prodstr_store_t *store,
                                   const char *name)
{
    if (NULL == store)
    {
        return NULL;
    }
    else if (NULL == name)
    {
        return NULL;
    }
    else
    {
        size_t         hash   = prodstr_hash(name, strlen(name));
        prodstr_obj_t *curobj = store->table[hash];
        while (NULL != curobj)
        {
            if (DEFS_PDGL_STRING_MATCH == strcmp(name, curobj->name))
            {
                return curobj;
            }
            curobj = curobj->next;
        }
        return NULL;
    }
}

/*************************************************************************************************/
/************************** Private Function Definitions *****************************************/
/*************************************************************************************************/

/**
 * \brief Hash an input buffer into an unsigned int.
 *
 * Hash with the input buffer with [Adler-32](https://en.wikipedia.org/wiki/Adler-32).
 *
 * \param buf The buffer to hash.
 * \param buflength The number of bytes to include in the hash.
 * \return An unsigned int in the range of $0<h<$PRODSTR_TABLE_SIZE.
 */
size_t prodstr_hash(const void *buf, size_t buflength)
{
    size_t         i;
    const uint8_t *buffer = (const uint8_t *)buf;
    uint32_t       s1     = 1;
    uint32_t       s2     = 0;

    for (i = 0; i < buflength; i++)
    {
        s1 = (s1 + buffer[i]) % 65521;
        s2 = (s2 + s1) % 65521;
    }
    return ((s2 << 16) | s1) % PRODSTR_TABLE_SIZE;
}
