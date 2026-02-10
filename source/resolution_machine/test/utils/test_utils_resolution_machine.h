/**
 *  \file test_utils_resolution_machine.h
 *
 *  \brief
 *
 *
 *  \author    Joe Starr
 *
 */

#ifndef TEST_UTIL_RESOLUTION_MACHINE_H
#define TEST_UTIL_RESOLUTION_MACHINE_H

/******************************************************************************/
/*************************** Includes *****************************************/
/******************************************************************************/

/******************************************************************************/
/*************************** Defines ******************************************/
/******************************************************************************/

/**
 * \brief
 *
 */
typedef struct {
    char *trans_str;
    char *term_str;
} test_resmach_prod_config_t;
/******************************************************************************/
/*************************** Public Function Declarations *********************/
/******************************************************************************/
const char * test_resmach_prod_resolve(const void *config);
const char * test_resmach_prod_terminate(const void *config);

#endif /* end TEST_UTIL_RESOLUTION_MACHINE_H*/
