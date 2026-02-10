/**
 *  \file pdgl_defs.h
 *
 *  \brief Common definitions for the PDGL.
 *
 *
 *  \author Joe Starr
 *
 */

#ifndef UTIL_PDGL_DEFS_H
#define UTIL_PDGL_DEFS_H

#include <stdint.h>

/******************************************************************************/
/****************************** Pre processor Switches ************************/
/******************************************************************************/


#ifndef STATIC_INLINE
#if defined(__GNUC__) || defined(__cplusplus) || \
    (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L))

/**
 * \brief standard static inline macro
 */
#define STATIC_INLINE    static inline
#else

/**
 * \brief standard static inline macro
 */
#define STATIC_INLINE    static
#endif
#endif /* STATIC_INLINE */


/**
 * \brief Static inline macro for a uint8_t function
 */
#define STATIC_INLINE_UINT8    STATIC_INLINE uint8_t
/******************************************************************************/
/****************************** Includes **************************************/
/******************************************************************************/

/******************************************************************************/
/****************************** Typedefs **************************************/
/******************************************************************************/

/******************************************************************************/
/****************************** Defines **************************************/
/******************************************************************************/

/**
 * \brief Define the maximum size of a string in the PDGL
 */
#define DEFS_PDGL_MAX_STRING_SIZE    (3000)

/**
 * \brief Define the maximum size of a production name in the PDGL
 */
#define DEFS_PDGL_MAX_NAME_SIZE      (200)

/**
 * \brief Define the name of the required entry symbol in the PDGL
 */
#define DEFS_PDGL_ENTRY_SYMBOL       ("entry")

/**
 * \brief Define a macro for match result from the strcmp function
 */
#define DEFS_PDGL_STRING_MATCH       (0x0u)
#endif /* end UTIL_PDGL_DEFS_H */
