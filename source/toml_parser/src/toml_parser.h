/**
 *  \file toml_parser.h
 *
 *  \brief Parses a TOML string into a production store and frees a store created with the module.
 *
 *
 *  \author Joe Starr
 *
 */

#ifndef TOML_PARSER_H
#define TOML_PARSER_H

/*************************************************************************************************/
/*************************** Includes ************************************************************/
/*************************************************************************************************/
#include <stdint.h>
#include <production_store.h>

/*************************************************************************************************/
/*************************** Defines *************************************************************/
/*************************************************************************************************/

/*************************************************************************************************/
/*************************** Public Function Declarations ****************************************/
/*************************************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif


/**
 * \brief Parse a language spec TOML string into a production store.
 *
 * Read the TOML into an object. From the object parse into a production store. Ensure the existence
 *of an entry symbol production.
 *
 * \param toml_data String TOML data to parse.
 * \return A pointer to a production store on success. A NULL pointer on failure.
 */
prodstr_store_t *const tomlprsr_parse(const char *toml_data);

/**
 * \brief Free a store created by the TOML parsing Function.
 *
 * Free each pointer allocated by the parsing function.
 *
 * \param store The store to free.
 */
void tomlprsr_free(prodstr_store_t *store);

#ifdef __cplusplus
}
#endif


#endif /* end TOML_PARSER_H*/
