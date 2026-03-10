#include "test_utils_toml_parser.h"
#include "production_store.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unity.h>

static char *buffer;

#define TOML_PARSER_TEST_UTILS_DATA_DIR    ("./toml_parser_test_data")

static void test_toml_parser_release_prd_ll(prodstr_obj_t *prd)
{
    if (NULL != prd->next)
    {
        test_toml_parser_release_prd_ll(prd->next);
    }
    free(prd);
}

void test_toml_parser_release_store(prodstr_store_t *store)
{
    size_t i;

    for (i = 0; i < PRODSTR_TABLE_SIZE; i++)
    {
        if (NULL != store->table[i])
        {
            test_toml_parser_release_prd_ll(store->table[i]);
        }
    }
    free(store);
}

/* cppcheck-suppress-begin nullPointerOutOfResources*/
char * test_toml_parser_read_test_file(const char *file)
{
    /*
     * https://www.fundza.com/c4serious/fileIO_reading_all/4_IO_readall.c
     * */

    /* declare a file pointer */
    FILE *infile;
    long  numbytes;

    TEST_ASSERT_NULL_MESSAGE(buffer, "file buffer is not null");

    char path[4096] = { '\0' };

    sprintf(path, "%s/%s", TOML_PARSER_TEST_UTILS_DATA_DIR, file);

    /* open an existing file for reading */
    infile = fopen(path, "r");

    /* quit if the file does not exist */

    TEST_ASSERT_NOT_NULL_MESSAGE(infile, "The file does not exist.");

    /* Get the number of bytes */

    fseek(infile, 0L, SEEK_END);

    numbytes = ftell(infile);

    /* reset the file position indicator to the beginning of the file */
    fseek(infile, 0L, SEEK_SET);

    /* grab sufficient memory for the buffer to hold the text */
    buffer = (char *)calloc(numbytes + 1, sizeof(char));

    TEST_ASSERT_NOT_NULL_MESSAGE(buffer, "buffer is still null when it shouldn't be.");

    size_t i;
    for (i = 0; i < numbytes + 1; i++)
    {
        buffer[i] = '\0';
    }

    /* copy all the text into the buffer */
    size_t out = fread(buffer, sizeof(char), numbytes, infile);

    TEST_ASSERT_EQUAL_UINT16_MESSAGE(out, out, "");
    fclose(infile);

    return buffer;
}

void test_toml_parser_free_file()
{
/* free the memory we used for the buffer */
    if (NULL != buffer)
    {
        free(buffer);
        buffer = NULL;
    }
}

/* cppcheck-suppress-end nullPointerOutOfResources*/
