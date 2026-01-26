/*!
 *  @file pdgl_defs.h
 *
 *  @brief  Common definitions for the PDGL.
 *
 *
 *  @author    Joe Starr
 *
 */

#ifndef UTIL_PDGL_DEFS_H
#define UTIL_PDGL_DEFS_H

#include <stdint.h>

/******************************************************************************/
/****************************** Pre processor Switches ************************/
/******************************************************************************/
#ifndef __PYX_EXTERN_C
#ifdef _WIN32
#ifndef _CRT_SECURE_NO_WARNINGS

/*! For portability we're using the old style "unsafe" string interfaces. We can suppress warning on
 * windows. */
#define _CRT_SECURE_NO_WARNINGS    (1u)
#else
#if (_CRT_SECURE_NO_WARNINGS != 1u)
#error \
    "Something has gone wrong. We want this define to be 1 and it's already not"
#else
#endif
#endif
#ifndef _CRT_DEPRECATE_TEXT

/*! For portability we're using the old style "unsafe" string interfaces. We can suppress warning on
 * windows. */
#define _CRT_DEPRECATE_TEXT    (1u)
#else
#if (_CRT_DEPRECATE_TEXT != 1u)
#error \
    "Something has gone wrong. We want this define to be 1 and it's already not"
#else
#endif
#endif
#endif
#endif

#ifndef STATIC_INLINE
#if defined(__GNUC__) || defined(__cplusplus) || \
    (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L))
#define STATIC_INLINE    static inline
#else
#define STATIC_INLINE    static
#endif
#endif /* STATIC_INLINE */

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

#define DEFS_PDGL_MAX_STRING_SIZE    (3000)
#define DEFS_PDGL_MAX_NAME_SIZE      (200)
#define DEFS_PDGL_ENTRY_SYMBOL       ("entry")
#define DEFS_PDGL_STRING_MATCH       (0x0u)
#endif /* end UTIL_PDGL_DEFS_H */
