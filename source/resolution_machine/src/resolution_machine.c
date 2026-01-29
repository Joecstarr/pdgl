/*!
 *  @file resolution_machine.c
 *
 *  @brief  Handles the production of a word in a language configured into a production store.
 *
 *
 *  @author    Joe Starr
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
        size_t               stack_count = 1;
        resmach_partial_t *  stack_ptr   = &stack->partials[stack_count - 1];
        const prodstr_obj_t *prd         = prodstr_find(store, DEFS_PDGL_ENTRY_SYMBOL);
        if (NULL == prd)
        {
            retval |= RESMACH_EXECUTE_NO_ENTRY;
        }
        else
        {
            retval = RESMACH_EXECUTE_SUCCESS;
            stack_ptr->partial_ptr = (char *)stack_ptr->buff;
            strcpy(stack_ptr->partial_ptr, prd->res(prd->config));
            while (0 < stack_count)
            {
                stack_ptr = &stack->partials[stack_count - 1];
                prd       = get_next_production(stack_ptr, store, stream);
                if (NULL != prd)
                {
                    if (stack_count < stack->stack_len)
                    {
                        stack_count++;
                        stack_ptr = &stack->partials[stack_count - 1];
                        stack_ptr->partial_ptr = (char *)stack_ptr->buff;
                        strcpy(stack_ptr->partial_ptr, prd->res(prd->config));
                    }
                    else
                    {
                        fprintf(stream, "%s", prd->term(prd->config));
                    }
                }
                else
                {
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

STATIC_INLINE const prodstr_obj_t * get_next_production(resmach_partial_t *partial,
                                                        const prodstr_store_t *store,
                                                        FILE *stream)
{
    const char *buff_end = partial->buff + strlen(partial->buff);

    for (; partial->partial_ptr < buff_end; partial->partial_ptr++)
    {
        if (('%' == *partial->partial_ptr) && ('{' == *(partial->partial_ptr + 1)))
        {
            if (((partial->buff < partial->partial_ptr) &&
                 ('\\' != *(partial->partial_ptr - 1))) ||
                (partial->partial_ptr == partial->buff))
            {
                char * search_ptr = partial->partial_ptr + 2;
                char   name[DEFS_PDGL_MAX_NAME_SIZE] = { '\0' };
                size_t i = 0;

                do {
                    name[i] = *search_ptr;
                    i++;
                    search_ptr++;
                }while ((i < DEFS_PDGL_MAX_NAME_SIZE) && ('}' != *search_ptr));

                search_ptr++;

                if (i < DEFS_PDGL_MAX_NAME_SIZE)
                {
                    const prodstr_obj_t *prod;
                    prod = prodstr_find(store, name);
                    if (NULL != prod)
                    {
                        partial->partial_ptr = search_ptr;
                        return prod;
                    }
                }
            }
        }
        fprintf(stream, "%c", *partial->partial_ptr);
    }
    return NULL;
}
