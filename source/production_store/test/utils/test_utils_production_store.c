#include "test_utils_production_store.h"
#include <stdlib.h>

static void test_production_store_release_prd_ll(prodstr_obj_t *prd)
{
    if (NULL != prd->next)
    {
        test_production_store_release_prd_ll(prd->next);
    }
    free(prd);
}

void test_production_store_release_store(prodstr_store_t *store)
{
    size_t i;

    for (i = 0; i < PRODSTR_TABLE_SIZE; i++)
    {
        if (NULL != store->table[i])
        {
            test_production_store_release_prd_ll(store->table[i]);
        }
    }
    free(store);
}
