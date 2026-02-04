/*!
 *  @file toml_parser.c
 *
 *  @brief  Parses a toml string into a production store and frees a store created with the module.
 *
 *
 *  @author    Joe Starr
 *
 */

#include "toml_parser.h"
#include "stdio.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <pdgl_defs.h>
#include <prod_pure.h>
#include <prod_range.h>
#include <prod_janet.h>
#include <production_store.h>
#include <tomlc17.h>

/*************************************************************************************************/
/************************** Defines **************************************************************/
/*************************************************************************************************/

/*************************************************************************************************/
/************************** Private Function Declarations ****************************************/
/*************************************************************************************************/
STATIC_INLINE prodstr_obj_t * tomlprsr_prod_pure_builder(toml_datum_t tbl);
STATIC_INLINE prodstr_obj_t * tomlprsr_prod_range_builder(toml_datum_t tbl);
STATIC_INLINE prodstr_obj_t * tomlprsr_prod_janet_builder(toml_datum_t tbl);
STATIC_INLINE char ** tomlprsr_prod_pure_builder_list(toml_datum_t ary);
STATIC_INLINE void tomlprsr_prod_range_free(prodstr_obj_t *prd);
STATIC_INLINE void tomlprsr_prod_janet_free(prodstr_obj_t *prd);
STATIC_INLINE void tomlprsr_prod_pure_free(prodstr_obj_t *prd);


/*************************************************************************************************/
/************************** Local Variables ******************************************************/
/*************************************************************************************************/

typedef prodstr_obj_t * (*prod_builder_funptr_t)(toml_datum_t tbl);


static const size_t          num_of_prod_builders     = 3;
static prod_builder_funptr_t registed_prod_builders[] = { &tomlprsr_prod_pure_builder,
                                                          &tomlprsr_prod_janet_builder,
                                                          &tomlprsr_prod_range_builder };



/*************************************************************************************************/
/************************** Public Function Definitions ******************************************/
/*************************************************************************************************/
prodstr_store_t *const tomlprsr_parse(const char *toml_data)
{
    prodstr_store_t *store = NULL;

    if (NULL != toml_data)
    {
        toml_result_t tbl = toml_parse(toml_data, strlen(toml_data));

        if (true == tbl.ok)
        {
            toml_datum_t         arr;
            size_t               i        = 0;
            const prodstr_obj_t *entry    = NULL;
            prodstr_obj_t **     prd_buff = NULL;
            store = (prodstr_store_t *)malloc((sizeof(prodstr_store_t)));

            if (NULL == store)
            {
                toml_free(tbl);
                return NULL;
            }
            store->production_count = 0;
            for (i = 0; i < PRODSTR_TABLE_SIZE; i++)
            {
                store->table[i] = NULL;
            }

            arr = toml_seek(tbl.toptab, "production");
            if (TOML_ARRAY != arr.type)
            {
                toml_free(tbl);
                free(store);
                return NULL;
            }

            prd_buff = calloc(arr.u.arr.size, sizeof(prodstr_obj_t *));

            if (NULL == prd_buff)
            {
                toml_free(tbl);
                free(store);
                return NULL;
            }

            for (i = 0; i < arr.u.arr.size; i++)
            {
                toml_datum_t prod  = arr.u.arr.elem[i];
                size_t       j     = 0;
                bool         added = false;
                prd_buff[i] = NULL;
                for (j = 0; j < num_of_prod_builders; j++)
                {
                    prd_buff[i] = registed_prod_builders[j](prod);
                    if (NULL != prd_buff[i])
                    {
                        added = prodstr_add(store, prd_buff[i]);
                        break;
                    }
                }
                if (false == added)
                {
                    size_t k;
                    for (k = 0; k < arr.u.arr.size; k++)
                    {
                        free(prd_buff[k]);
                    }
                    free(prd_buff);
                    free(store);
                    return NULL;
                }
            }

            free(prd_buff);
            toml_free(tbl);

            entry = prodstr_find(store, DEFS_PDGL_ENTRY_SYMBOL);
            if (NULL == entry)
            {
                tomlprsr_free(store);
                return NULL;
            }
        }
    }
    return store;
}

void tomlprsr_free(prodstr_store_t *store)
{
    size_t i;

    for (i = 0; i < PRODSTR_TABLE_SIZE; i++)
    {
        prodstr_obj_t *obj = store->table[i];
        while (NULL != obj)
        {
            prodstr_obj_t *nextobj = obj->next;
            if (DEFS_PDGL_STRING_MATCH == strcmp(obj->type, PROD_PURE_NAME))
            {
                tomlprsr_prod_pure_free(obj);
            }
            else if (DEFS_PDGL_STRING_MATCH == strcmp(obj->type, PROD_JANET_NAME))
            {
                tomlprsr_prod_janet_free(obj);
            }
            else if (DEFS_PDGL_STRING_MATCH == strcmp(obj->type, PROD_RANGE_NAME))
            {
                tomlprsr_prod_range_free(obj);
            }
            obj = nextobj;
        }
        store->table[i] = NULL;
    }
    free(store);
}

/*************************************************************************************************/
/************************** Private Function Definitions *****************************************/
/*************************************************************************************************/

STATIC_INLINE void tomlprsr_prod_range_free(prodstr_obj_t *prd)
{
    if (NULL != prd)
    {
        prod_range_config_t *config = (prod_range_config_t *)prd->config;
        free(config->out_str);
        free(prd->name);
        free(prd->type);
    }
    free(prd);
}

STATIC_INLINE void tomlprsr_prod_janet_free(prodstr_obj_t *prd)
{
    if (NULL != prd)
    {
        prod_janet_config_t *config = (prod_janet_config_t *)prd->config;
        free(config->out_str);
        free(config->term_str);
        free(config->transition_str);
        free(prd->name);
        free(prd->type);
    }
    free(prd);
}

STATIC_INLINE void tomlprsr_prod_pure_free(prodstr_obj_t *prd)
{
    if (NULL != prd)
    {
        size_t i;
        prod_pure_config_t *config = (prod_pure_config_t *)prd->config;
        for (i = 0; i < config->term_len; i++)
        {
            free(config->term_list[i]);
        }
        for (i = 0; i < config->transition_len; i++)
        {
            free(config->transition_list[i]);
        }

        free(config->transition_list);
        free(config->term_list);
        free(config);
        free(prd->name);
        free(prd->type);
    }
    free(prd);
}

STATIC_INLINE char ** tomlprsr_prod_pure_builder_list(toml_datum_t ary)
{
    size_t i = 0;

    char **buff = calloc(ary.u.arr.size, sizeof(char *));

    if (NULL == buff)
    {
        return NULL;
    }

    for (i = 0; i < ary.u.arr.size; i++)
    {
        toml_datum_t value = ary.u.arr.elem[i];
        buff[i] = NULL;
        if (TOML_STRING == value.type)
        {
            size_t str_len = strlen(value.u.s) + 1;
            if (str_len < DEFS_PDGL_MAX_STRING_SIZE)
            {
                char *str_config = (char *)calloc(str_len, sizeof(char));
                if (NULL != str_config)
                {
                    strcpy(str_config, value.u.s);
                    buff[i] = str_config;
                }
                else
                {
                    size_t j;
                    for (j = 0; j <= i; j++)
                    {
                        free(buff[i]);
                    }
                    free(buff);
                    return NULL;
                }
            }
            else
            {
                size_t j;
                for (j = 0; j <= i; j++)
                {
                    free(buff[i]);
                }
                free(buff);
                return NULL;
            }
        }
        else
        {
            size_t j;
            for (j = 0; j <= i; j++)
            {
                free(buff[i]);
            }
            free(buff);
            return NULL;
        }
    }
    return buff;
}

STATIC_INLINE prodstr_obj_t * tomlprsr_prod_pure_builder(toml_datum_t tbl)
{
    toml_datum_t type = toml_seek(tbl, "type");


    if (DEFS_PDGL_STRING_MATCH == strcmp(type.u.s, PROD_PURE_NAME))
    {
        toml_datum_t name        = toml_seek(tbl, "name");
        toml_datum_t transitions = toml_seek(tbl, "transitions");
        toml_datum_t terminals   = toml_seek(tbl, "terminals");
        if (
            (TOML_STRING == name.type) &&
            (TOML_ARRAY == transitions.type) &&
            (TOML_ARRAY == terminals.type))
        {
            size_t cur_str_len         = 0;
            prod_pure_config_t *config = NULL;
            prodstr_obj_t *     prd    = NULL;
            char **trans_buff          = NULL;
            char **term_buff           = NULL;

            char *cur_str = NULL;


            config = (prod_pure_config_t *)malloc(sizeof(prod_pure_config_t));
            if (NULL == config)
            {
                return NULL;
            }

            config->transition_len  = transitions.u.arr.size;
            config->term_len        = terminals.u.arr.size;
            config->term_list       = NULL;
            config->transition_list = NULL;


            prd = (prodstr_obj_t *)malloc(sizeof(prodstr_obj_t));
            if (NULL == prd)
            {
                free(config);
                return NULL;
            }

            prd->name   = NULL;
            prd->config = (void *)config;
            prd->next   = NULL;
            prd->res    = &prod_pure_resolve;
            prd->term   = &prod_pure_terminate;

            cur_str_len = strlen(name.u.s) + 1;
            cur_str     = (char *)calloc(cur_str_len, sizeof(char));
            if ((NULL == cur_str) || (cur_str_len > DEFS_PDGL_MAX_NAME_SIZE))
            {
                free(config);
                free(prd);
                return NULL;
            }

            strcpy(cur_str, name.u.s);
            prd->name = cur_str;
            cur_str   = NULL;

            cur_str_len = strlen(type.u.s) + 1;
            cur_str     = (char *)calloc(cur_str_len, sizeof(char));

            if ((NULL == cur_str) || (cur_str_len > DEFS_PDGL_MAX_NAME_SIZE))
            {
                free(prd->name);
                free(config);
                free(prd);
                return NULL;
            }
            strcpy(cur_str, type.u.s);
            prd->type = cur_str;
            cur_str   = NULL;


            trans_buff = tomlprsr_prod_pure_builder_list(transitions);
            if (NULL == trans_buff)
            {
                free(prd->name);
                free(prd->type);
                free(config);
                free(prd);
                return NULL;
            }
            config->transition_list = trans_buff;

            term_buff = tomlprsr_prod_pure_builder_list(terminals);
            if (NULL == term_buff)
            {
                size_t i;
                for (i = 0; i < config->transition_len; i++)
                {
                    free(config->transition_list[i]);
                }
                free(config->transition_list);
                free(prd->name);
                free(prd->type);
                free(config);
                free(prd);
                return NULL;
            }
            config->term_list = term_buff;

            return prd;
        }
    }
    return NULL;
}

STATIC_INLINE prodstr_obj_t * tomlprsr_prod_range_builder(toml_datum_t tbl)
{
    toml_datum_t type = toml_seek(tbl, "type");

    if (DEFS_PDGL_STRING_MATCH == strcmp(type.u.s, PROD_RANGE_NAME))
    {
        toml_datum_t name       = toml_seek(tbl, "name");
        toml_datum_t lowerbound = toml_seek(tbl, "lower_bound");
        toml_datum_t upperbound = toml_seek(tbl, "upper_bound");
        if (
            (TOML_STRING == name.type) &&
            (TOML_INT64 == lowerbound.type) &&
            (TOML_INT64 == upperbound.type))
        {
            size_t cur_str_len          = 0;
            prod_range_config_t *config = NULL;
            prodstr_obj_t *      prd    = NULL;
            char *cur_str = NULL;

            config = (prod_range_config_t *)malloc(sizeof(prod_range_config_t));

            if (NULL == config)
            {
                return NULL;
            }

            config->lower_bound = lowerbound.u.int64;
            config->upper_bound = upperbound.u.int64;
            config->out_str     = NULL;
            config->out_str_len = DEFS_PDGL_MAX_STRING_SIZE;


            prd = (prodstr_obj_t *)malloc(sizeof(prodstr_obj_t));
            if (NULL == prd)
            {
                free(config);
                return NULL;
            }

            prd->name   = NULL;
            prd->config = (void *)config;
            prd->next   = NULL;
            prd->res    = &prod_range_resolve;
            prd->term   = &prod_range_terminate;

            cur_str_len = strlen(name.u.s) + 1;
            cur_str     = (char *)calloc(cur_str_len, sizeof(char));
            if ((NULL == cur_str) || (cur_str_len > DEFS_PDGL_MAX_NAME_SIZE))
            {
                free(config);
                free(prd);
                return NULL;
            }

            strcpy(cur_str, name.u.s);
            prd->name = cur_str;
            cur_str   = NULL;

            cur_str_len = strlen(type.u.s) + 1;
            cur_str     = (char *)calloc(cur_str_len, sizeof(char));

            if ((NULL == cur_str) || (cur_str_len > DEFS_PDGL_MAX_NAME_SIZE))
            {
                free(prd->name);
                free(config);
                free(prd);
                return NULL;
            }
            strcpy(cur_str, type.u.s);
            prd->type = cur_str;
            cur_str   = NULL;

            config->out_str = (char *)calloc(DEFS_PDGL_MAX_STRING_SIZE, sizeof(char));
            if (NULL == config->out_str)
            {
                free(prd->name);
                free(prd->type);
                free(config);
                free(prd);
                return NULL;
            }

            return prd;
        }
    }

    return NULL;
}

STATIC_INLINE prodstr_obj_t * tomlprsr_prod_janet_builder(toml_datum_t tbl)
{
    /* #lizard forgives(cyclomatic_complexity) */
    toml_datum_t type = toml_seek(tbl, "type");

    if (DEFS_PDGL_STRING_MATCH == strcmp(type.u.s, PROD_JANET_NAME))
    {
        toml_datum_t name       = toml_seek(tbl, "name");
        toml_datum_t transition = toml_seek(tbl, "transition");
        toml_datum_t terminal   = toml_seek(tbl, "terminal");
        if ((TOML_STRING == name.type) &&
            (TOML_STRING == transition.type) &&
            (TOML_STRING == terminal.type))
        {
            size_t cur_str_len          = 0;
            prod_janet_config_t *config = NULL;
            prodstr_obj_t *      prd    = NULL;
            char *cur_str = NULL;


            config = (prod_janet_config_t *)malloc(sizeof(prod_janet_config_t));
            if (NULL == config)
            {
                return NULL;
            }
            config->out_str        = NULL;
            config->out_str_len    = DEFS_PDGL_MAX_STRING_SIZE;
            config->term_str       = NULL;
            config->transition_str = NULL;


            prd = (prodstr_obj_t *)malloc(sizeof(prodstr_obj_t));
            if (NULL == prd)
            {
                free(config);
                return NULL;
            }

            prd->name   = NULL;
            prd->config = (void *)config;
            prd->next   = NULL;
            prd->res    = &prod_janet_resolve;
            prd->term   = &prod_janet_terminate;


            cur_str_len = strlen(name.u.s) + 1;
            cur_str     = (char *)calloc(cur_str_len, sizeof(char));
            if ((NULL == cur_str) || (cur_str_len > DEFS_PDGL_MAX_NAME_SIZE))
            {
                free(config);
                free(prd);
                return NULL;
            }

            strcpy(cur_str, name.u.s);
            prd->name = cur_str;
            cur_str   = NULL;

            cur_str_len = strlen(type.u.s) + 1;
            cur_str     = (char *)calloc(cur_str_len, sizeof(char));

            if ((NULL == cur_str) || (cur_str_len > DEFS_PDGL_MAX_NAME_SIZE))
            {
                free(prd->name);
                free(config);
                free(prd);
                return NULL;
            }
            strcpy(cur_str, type.u.s);
            prd->type = cur_str;
            cur_str   = NULL;

            config->out_str = (char *)calloc(DEFS_PDGL_MAX_STRING_SIZE, sizeof(char));
            if (NULL == config->out_str)
            {
                free(prd->name);
                free(prd->type);
                free(config);
                free(prd);
                return NULL;
            }

            *config->out_str = '\0';

            cur_str_len = strlen(transition.u.s) + 1;
            cur_str     = (char *)calloc(cur_str_len, sizeof(char));

            if ((NULL == cur_str) || (cur_str_len > DEFS_PDGL_MAX_STRING_SIZE))
            {
                free(prd->name);
                free(prd->type);
                free(config->out_str);
                free(config);
                free(prd);
                return NULL;
            }
            strcpy(cur_str, transition.u.s);
            config->transition_str = cur_str;
            cur_str = NULL;

            cur_str_len = strlen(terminal.u.s) + 1;
            cur_str     = (char *)calloc(cur_str_len, sizeof(char));

            if ((NULL == cur_str) || (cur_str_len > DEFS_PDGL_MAX_STRING_SIZE))
            {
                free(prd->name);
                free(prd->type);
                free(config->out_str);
                free(config->transition_str);
                free(config);
                free(prd);
                return NULL;
            }
            strcpy(cur_str, terminal.u.s);
            config->term_str = cur_str;
            cur_str          = NULL;

            return prd;
        }
    }
    return NULL;
}
