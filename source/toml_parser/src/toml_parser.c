/**
 *  \file toml_parser.c
 *
 *  \brief Parses a TOML string into a production store and frees a store created with the module.
 *
 *
 *  \author Joe Starr
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
#include <prod_weighted.h>
#include <production_store.h>
#include <tomlc17.h>

/*************************************************************************************************/
/************************** Defines **************************************************************/
/*************************************************************************************************/

/*************************************************************************************************/
/************************** Private Function Declarations ****************************************/
/*************************************************************************************************/
STATIC_INLINE prodstr_obj_t * tomlprsr_prod_pure_builder(toml_datum_t tbl);
STATIC_INLINE void tomlprsr_prod_pure_free(prodstr_obj_t *prd);
STATIC_INLINE char ** tomlprsr_prod_pure_builder_list(toml_datum_t ary);
STATIC_INLINE void tomlprsr_prod_range_free(prodstr_obj_t *prd);
STATIC_INLINE prodstr_obj_t * tomlprsr_prod_range_builder(toml_datum_t tbl);
STATIC_INLINE void tomlprsr_prod_janet_free(prodstr_obj_t *prd);
STATIC_INLINE prodstr_obj_t * tomlprsr_prod_janet_builder(toml_datum_t tbl);
STATIC_INLINE void tomlprsr_prod_weighted_free(prodstr_obj_t *prd);
STATIC_INLINE prodstr_obj_t * tomlprsr_prod_weighted_builder(toml_datum_t tbl);
STATIC_INLINE prod_weighted_pair_t * tomlprsr_prod_weighted_builder_list(toml_datum_t ary);


/*************************************************************************************************/
/************************** Local Variables ******************************************************/
/*************************************************************************************************/

/**
 *\typedef prod_builder_funptr_t
 *
 * \brief Function pointer for production builder functions.
 */
typedef prodstr_obj_t * (*prod_builder_funptr_t)(toml_datum_t tbl);

/**
 *\typedef prod_free_funptr_t
 *
 * \brief Function pointer for production free functions.
 */
typedef void (*prod_free_funptr_t)(prodstr_obj_t *prd);

/**
 * \class prodstr_builder_set_t
 * \brief Structure for a production object type specific data.
 *
 * The data needed to abstract the building of a production object away from its specific type.
 */
typedef struct {
    char *                type;  /**< A pointer to the string representing the type of object.*/
    prod_builder_funptr_t build; /**< A function pointer to the build function for the object.*/
    prod_free_funptr_t    free;  /**< A function pointer to the free function for the object.*/
}prodstr_builder_set_t;


/**
 * \brief List of productions configured for building a production store.
 */
static prodstr_builder_set_t registed_prod_builders[] = {
    { PROD_PURE_NAME,     &tomlprsr_prod_pure_builder,     &tomlprsr_prod_pure_free     },
    { PROD_JANET_NAME,    &tomlprsr_prod_janet_builder,    &tomlprsr_prod_janet_free    },
    { PROD_RANGE_NAME,    &tomlprsr_prod_range_builder,    &tomlprsr_prod_range_free    },
    { PROD_WEIGHTED_NAME, &tomlprsr_prod_weighted_builder, &tomlprsr_prod_weighted_free },
    { NULL,               NULL,                            NULL                         }
    /* This list must be null terminated*/
};



/*************************************************************************************************/
/************************** Public Function Definitions ******************************************/
/*************************************************************************************************/
/* Docstring in header*/
prodstr_store_t *const tomlprsr_parse(const char *toml_data)
{
    prodstr_store_t *store = NULL;

    if (NULL != toml_data)
    {
        /* try to parse the input TOML*/
        toml_result_t tbl = toml_parse(toml_data, strlen(toml_data));

        if (true == tbl.ok)
        {
            toml_datum_t         arr;
            size_t               i        = 0;
            const prodstr_obj_t *entry    = NULL;
            prodstr_obj_t **     prd_buff = NULL;
            /* Allocate a new production store*/
            store = (prodstr_store_t *)malloc((sizeof(prodstr_store_t)));

            if (NULL == store)
            {
                toml_free(tbl);
                return NULL;
            }
            /* Initialize the store table*/
            store->count = 0;
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

            /* Get a buffer of pointers to production object to make freeing easier if we find a
             * failure*/
            prd_buff = calloc(arr.u.arr.size, sizeof(prodstr_obj_t *));

            if (NULL == prd_buff)
            {
                toml_free(tbl);
                free(store);
                return NULL;
            }

            /* For each item in the TOML array */
            for (i = 0; i < arr.u.arr.size; i++)
            {
                toml_datum_t           prod    = arr.u.arr.elem[i];
                prodstr_builder_set_t *builder = registed_prod_builders;
                bool added = false;
                prd_buff[i] = NULL;
                /* For each configured production type*/
                while (NULL != builder->type)
                {
                    toml_datum_t type = toml_seek(prod, "type");
                    if (DEFS_PDGL_STRING_MATCH == strcmp(type.u.s, builder->type))
                    {
                        /* Try to parse the production as the jth type*/
                        prd_buff[i] = builder->build(prod);
                        if (NULL != prd_buff[i])
                        {
                            /* Parsed successfully add to store.*/
                            added = prodstr_add(store, prd_buff[i]);
                            break;
                        }
                    }
                    builder++;
                }
                /* If we failed to add a production on the last attempt */
                if (false == added)
                {
                    /* Free everything and report an error state */
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

            /* Free the production temp buffer, and free the TOML table. */
            free(prd_buff);
            toml_free(tbl);

            /* We have exhausted all the productions in the array. Now ensure that there is a
             * production with the entry symbol.*/
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

/* Docstring in header*/
void tomlprsr_free(prodstr_store_t *store)
{
    size_t i;

    /* For each table */
    for (i = 0; i < PRODSTR_TABLE_SIZE; i++)
    {
        prodstr_obj_t *obj = store->table[i];
        while (NULL != obj)
        {
            prodstr_builder_set_t *builder = registed_prod_builders;
            prodstr_obj_t *        nextobj = obj->next;

            /* For each configured production type*/
            while (NULL != builder->type)
            {
                if (DEFS_PDGL_STRING_MATCH == strcmp(obj->type, builder->type))
                {
                    builder->free(obj);
                    break;
                }
                builder++;
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

/*************************************************************************************************/
/**************************   Pure Production Functions   *****************************************/
/*************************************************************************************************/

/**
 * \brief Builder function for a pure production
 *
 * Parses a pure production from TOML to a prodstr_obj_t configured as a pure production.
 *
 * \param tbl TOML production data to parse
 * \return A pointer to a prodstr_obj_t when successful and a NULL pointer when unsuccessful.
 */
STATIC_INLINE prodstr_obj_t * tomlprsr_prod_pure_builder(toml_datum_t tbl)
{
    toml_datum_t type         = toml_seek(tbl, "type");
    toml_datum_t name         = toml_seek(tbl, "name");
    toml_datum_t replacements = toml_seek(tbl, "replacements");
    toml_datum_t terminals    = toml_seek(tbl, "terminals");

    if ((TOML_STRING == name.type) &&
        (TOML_ARRAY == replacements.type) &&
        (TOML_ARRAY == terminals.type))
    {
        size_t cur_str_len         = 0;
        prod_pure_config_t *config = NULL;
        prodstr_obj_t *     prd    = NULL;
        char **repl_buff           = NULL;
        char **term_buff           = NULL;

        char *cur_str = NULL;


        config = (prod_pure_config_t *)malloc(sizeof(prod_pure_config_t));
        if (NULL == config)
        {
            return NULL;
        }

        config->repl_len  = replacements.u.arr.size;
        config->term_len  = terminals.u.arr.size;
        config->term_list = NULL;
        config->repl_list = NULL;


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


        repl_buff = tomlprsr_prod_pure_builder_list(replacements);
        if (NULL == repl_buff)
        {
            free(prd->name);
            free(prd->type);
            free(config);
            free(prd);
            return NULL;
        }
        config->repl_list = repl_buff;

        term_buff = tomlprsr_prod_pure_builder_list(terminals);
        if (NULL == term_buff)
        {
            size_t i;
            for (i = 0; i < config->repl_len; i++)
            {
                free(config->repl_list[i]);
            }
            free(config->repl_list);
            free(prd->name);
            free(prd->type);
            free(config);
            free(prd);
            return NULL;
        }
        config->term_list = term_buff;

        return prd;
    }

    return NULL;
}

/**
 * \brief Free an allocated pure production.
 *
 * \param prd The production object to free.
 */
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
        for (i = 0; i < config->repl_len; i++)
        {
            free(config->repl_list[i]);
        }

        free(config->repl_list);
        free(config->term_list);
        free(config);
        free(prd->name);
        free(prd->type);
        free(prd);
    }
}

/**
 * \brief Parse TOML array into a list of strings for a pure production.
 *
 * Parse the given TOML array of strings into an array of c strings for a pure production.
 *
 * \param ary A TOML array of strings.
 * \return A list of strings when successful and a NULL pointer when unsuccessful.
 */
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

/*************************************************************************************************/
/**************************   Range Production Functions   ***************************************/
/*************************************************************************************************/


/**
 * \brief Builder function for a range production
 *
 * Parses a pure production from TOML to a prodstr_obj_t configured as a range production.
 *
 * \param tbl TOML production data to parse
 * \return A pointer to a prodstr_obj_t when successful and a NULL pointer when unsuccessful.
 */
STATIC_INLINE prodstr_obj_t * tomlprsr_prod_range_builder(toml_datum_t tbl)
{
    toml_datum_t type       = toml_seek(tbl, "type");
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

    return NULL;
}

/**
 * \brief Free an allocated range production.
 *
 * \param prd The production object to free.
 */
STATIC_INLINE void tomlprsr_prod_range_free(prodstr_obj_t *prd)
{
    if (NULL != prd)
    {
        prod_range_config_t *config = (prod_range_config_t *)prd->config;
        free(config->out_str);
        free(config);
        free(prd->name);
        free(prd->type);
    }
    free(prd);
}

/*************************************************************************************************/
/**************************   Janet Production Functions   ***************************************/
/*************************************************************************************************/

/**
 * \brief Builder function for a Janet production
 *
 * Parses a pure production from TOML to a prodstr_obj_t configured as a Janet production.
 *
 * \param tbl TOML production data to parse
 * \return A pointer to a prodstr_obj_t when successful and a NULL pointer when unsuccessful.
 */
STATIC_INLINE prodstr_obj_t * tomlprsr_prod_janet_builder(toml_datum_t tbl)
{
    /* #lizard forgives(cyclomatic_complexity) */
    toml_datum_t type        = toml_seek(tbl, "type");
    toml_datum_t name        = toml_seek(tbl, "name");
    toml_datum_t replacement = toml_seek(tbl, "replacement");
    toml_datum_t terminal    = toml_seek(tbl, "terminal");

    if ((TOML_STRING == name.type) &&
        (TOML_STRING == replacement.type) &&
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
        config->out_str     = NULL;
        config->out_str_len = DEFS_PDGL_MAX_STRING_SIZE;
        config->term_str    = NULL;
        config->repl_str    = NULL;


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

        cur_str_len = strlen(replacement.u.s) + 1;
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
        strcpy(cur_str, replacement.u.s);
        config->repl_str = cur_str;
        cur_str          = NULL;

        cur_str_len = strlen(terminal.u.s) + 1;
        cur_str     = (char *)calloc(cur_str_len, sizeof(char));

        if ((NULL == cur_str) || (cur_str_len > DEFS_PDGL_MAX_STRING_SIZE))
        {
            free(prd->name);
            free(prd->type);
            free(config->out_str);
            free(config->repl_str);
            free(config);
            free(prd);
            return NULL;
        }
        strcpy(cur_str, terminal.u.s);
        config->term_str = cur_str;
        cur_str          = NULL;

        return prd;
    }
    return NULL;
}

/**
 * \brief Free an allocated Janet production.
 *
 * \param prd The production object to free.
 */
STATIC_INLINE void tomlprsr_prod_janet_free(prodstr_obj_t *prd)
{
    if (NULL != prd)
    {
        prod_janet_config_t *config = (prod_janet_config_t *)prd->config;
        free(config->out_str);
        free(config->term_str);
        free(config->repl_str);
        free(config);
        free(prd->name);
        free(prd->type);
        free(prd);
    }
}

/*************************************************************************************************/
/**************************   Weighted Production Functions   ************************************/
/*************************************************************************************************/

/**
 * \brief Builder function for a weighted production
 *
 * Parses a pure production from TOML to a prodstr_obj_t configured as a weighted production.
 *
 * \param tbl TOML production data to parse
 * \return A pointer to a prodstr_obj_t when successful and a NULL pointer when unsuccessful.
 */
STATIC_INLINE prodstr_obj_t * tomlprsr_prod_weighted_builder(toml_datum_t tbl)
{
    /* #lizard forgives(cyclomatic_complexity) */
    toml_datum_t type         = toml_seek(tbl, "type");
    toml_datum_t name         = toml_seek(tbl, "name");
    toml_datum_t replacements = toml_seek(tbl, "replacements");
    toml_datum_t terminals    = toml_seek(tbl, "terminals");

    if ((TOML_STRING == name.type) &&
        (TOML_ARRAY == replacements.type) &&
        (TOML_ARRAY == terminals.type))
    {
        size_t cur_str_len             = 0;
        prod_weighted_config_t *config = NULL;
        prodstr_obj_t *         prd    = NULL;
        char *cur_str = NULL;
        prod_weighted_pair_t *repl_buff = NULL;
        prod_weighted_pair_t *term_buff = NULL;


        config = (prod_weighted_config_t *)malloc(sizeof(prod_weighted_config_t));
        if (NULL == config)
        {
            return NULL;
        }

        config->repl_list = NULL;
        config->repl_len  = replacements.u.arr.size;
        config->term_list = NULL;
        config->term_len  = terminals.u.arr.size;


        prd = (prodstr_obj_t *)malloc(sizeof(prodstr_obj_t));
        if (NULL == prd)
        {
            free(config);
            return NULL;
        }

        prd->name   = NULL;
        prd->config = (void *)config;
        prd->next   = NULL;
        prd->res    = &prod_weighted_resolve;
        prd->term   = &prod_weighted_terminate;


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

        repl_buff = tomlprsr_prod_weighted_builder_list(replacements);
        if (NULL == repl_buff)
        {
            free(prd->name);
            free(prd->type);
            free(config);
            free(prd);
            return NULL;
        }
        config->repl_list = repl_buff;

        term_buff = tomlprsr_prod_weighted_builder_list(terminals);
        if (NULL == term_buff)
        {
            volatile size_t i;
            for (i = 0; i < config->repl_len; i++)
            {
                free(config->repl_list[i].string);
            }
            free(config->repl_list);
            free(prd->name);
            free(prd->type);
            free(config);
            free(prd);
            return NULL;
        }
        config->term_list = term_buff;



        return prd;
    }
    return NULL;
}

/**
 * \brief Free an allocated weighted production.
 *
 * \param prd The production object to free.
 */
STATIC_INLINE void tomlprsr_prod_weighted_free(prodstr_obj_t *prd)
{
    if (NULL != prd)
    {
        size_t i;
        prod_weighted_config_t *config = (prod_weighted_config_t *)prd->config;
        for (i = 0; i < config->repl_len; i++)
        {
            free(config->repl_list[i].string);
        }
        for (i = 0; i < config->term_len; i++)
        {
            free(config->term_list[i].string);
        }

        free(config->repl_list);
        free(config->term_list);
        free(config);

        free(prd->name);
        free(prd->type);
        free(prd);
    }
}

/**
 * \brief Parse TOML array into a list of strings for a pure production.
 *
 * Parse the given TOML array of strings into an array of c strings for a pure production.
 *
 * \param ary A TOML array of strings.
 * \return A list of strings when successful and a NULL pointer when unsuccessful.
 */
STATIC_INLINE prod_weighted_pair_t * tomlprsr_prod_weighted_builder_list(toml_datum_t ary)
{
    size_t i;

    prod_weighted_pair_t *buff = calloc(ary.u.arr.size, sizeof(prod_weighted_pair_t));

    if (NULL == buff)
    {
        return NULL;
    }

    for (i = 0; i < ary.u.arr.size; i++)
    {
        toml_datum_t value  = ary.u.arr.elem[i];
        toml_datum_t string = toml_seek(value, "string");
        toml_datum_t weight = toml_seek(value, "weight");

        if ((TOML_STRING == string.type) && (TOML_INT64 == weight.type))
        {
            buff[i].string = NULL;
            buff[i].weight = 0;
            size_t str_len = strlen(string.u.s) + 1;
            if (str_len < DEFS_PDGL_MAX_STRING_SIZE)
            {
                char *str_config = (char *)calloc(str_len, sizeof(char));

                if (NULL != str_config)
                {
                    strcpy(str_config, string.u.s);
                    buff[i].string = str_config;
                    buff[i].weight = weight.u.int64;
                }
                else
                {
                    size_t j;
                    for (j = 0; j <= i; j++)
                    {
                        free(buff[i].string);
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
                    free(buff[i].string);
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
                free(buff[i].string);
            }
            free(buff);
            return NULL;
        }
    }
    return buff;
}
