/**
 *  \file resolution_machine.c
 *
 *  \brief Handle the production of a word in a language configured into a production store.
 *
 *
 *  \author Joe Starr
 *
 */

#include "resolution_machine.h"
#include "production_store.h"
#include <stdio.h>
#include <string.h>
#include <pdgl_defs.h>

/*************************************************************************************************/
/************************** Defines **************************************************************/
/*************************************************************************************************/

/*************************************************************************************************/
/************************** Private Function Declarations ****************************************/
/*************************************************************************************************/
STATIC_INLINE const prodstr_obj_t * get_next_production(resmach_partial_t *partial,
                                                        const prodstr_store_t *store,
                                                        FILE *stream);

/*************************************************************************************************/
/************************** Local Variables ******************************************************/
/*************************************************************************************************/

/*************************************************************************************************/
/************************** Public Function Definitions ******************************************/
/*************************************************************************************************/

/* Docstring in header */
uint8_t resmach_execute(const prodstr_store_t *store,
                        resmach_stack_t *stack,
                        FILE *stream)
{
    uint8_t retval = RESMACH_EXECUTE_FAIL;

    if (NULL == store)
    {
        retval |= RESMACH_EXECUTE_NULL_STORE;
    }
    else if (NULL == stack)
    {
        retval |= RESMACH_EXECUTE_NULL_STACK;
    }
    else if (NULL == stream)
    {
        retval |= RESMACH_EXECUTE_NULL_STREAM;
    }
    else
    {
        size_t             stack_count = 1;
        resmach_partial_t *stack_ptr   = &stack->partials[stack_count - 1];
        /* Find entry production*/
        const prodstr_obj_t *prd = prodstr_find(store, DEFS_PDGL_ENTRY_SYMBOL);
        if (NULL == prd)
        {
            retval |= RESMACH_EXECUTE_NO_ENTRY;
        }
        else
        {
            retval = RESMACH_EXECUTE_SUCCESS;
            /* Execute the entry production*/
            stack_ptr->partial_ptr = (char *)stack_ptr->buff;
            strcpy(stack_ptr->partial_ptr, prd->res(prd->config));
            /* While the stack is not empty.*/
            while (0 < stack_count)
            {
                stack_ptr = &stack->partials[stack_count - 1];
                prd       = get_next_production(stack_ptr, store, stream);
                if (NULL != prd)
                {
                    /* The stack has room for a new production*/
                    if (stack_count < stack->stack_len)
                    {
                        stack_count++;
                        stack_ptr = &stack->partials[stack_count - 1];
                        stack_ptr->partial_ptr = (char *)stack_ptr->buff;
                        strcpy(stack_ptr->partial_ptr, prd->res(prd->config));
                    }
                    else/* The stack has no room for a new production*/
                    {
                        fprintf(stream, "%s", prd->term(prd->config));
                    }
                }
                else
                {
                    /* Partial is exhausted*/
                    stack_count--;
                }
            }
        }
    }
    return retval;
}

/*************************************************************************************************/
/************************** Private Function Definitions *****************************************/
/*************************************************************************************************/

/**
 * \brief Identify the next production in the current partial.
 *
 * Parse the partial string from the current location printing as the partial is consumed. When a
 *production is found report that production to the calling function. If none is found report NULL.
 *
 * \param partial The partial to consume.
 * \param store The store to search for productions in.
 * \param stream The stream to print to.
 * \return A pointer to the next production or NULL if partial is complete.
 */
STATIC_INLINE const prodstr_obj_t * get_next_production(resmach_partial_t *partial,
                                                        const prodstr_store_t *store,
                                                        FILE *stream)
{
    const char *buff_end = partial->buff + strlen(partial->buff);

    /* While partial_ptr is not at the end of the partial string.*/
    while (partial->partial_ptr < buff_end)
    {
        /* If the partial_ptr is at a '%{' substring */
        if (('%' == *partial->partial_ptr) && ('{' == *(partial->partial_ptr + 1)))
        {
            /* Ensure the '%' is not delimited*/
            if (((partial->buff < partial->partial_ptr) &&
                 ('\\' != *(partial->partial_ptr - 1))) ||
                (partial->partial_ptr == partial->buff))
            {
                char * search_ptr = partial->partial_ptr + 2;
                char   name[DEFS_PDGL_MAX_NAME_SIZE] = { '\0' };
                size_t i = 0;
                /* Find the symbol for the potential production*/
                do {
                    name[i] = *search_ptr;
                    i++;
                    search_ptr++;
                }while ((i < DEFS_PDGL_MAX_NAME_SIZE) && ('}' != *search_ptr));

                search_ptr++;
                /* Ensure the name is a valid size*/
                if (i < DEFS_PDGL_MAX_NAME_SIZE)
                {
                    /* Try to find production from store*/
                    const prodstr_obj_t *prod;
                    prod = prodstr_find(store, name);
                    if (NULL != prod)
                    {
                        /* Found production. Move partial pointer after symbol and return
                         * production.*/
                        partial->partial_ptr = search_ptr;
                        return prod;
                    }
                }
            }
        }
        fprintf(stream, "%c", *partial->partial_ptr);
        partial->partial_ptr++;
    }
    return NULL;
}
