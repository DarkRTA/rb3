/*
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */


#ifndef _STLP_C_LOCALE_H
#define _STLP_C_LOCALE_H

/*
 * Implementation dependent definitions.
 * Beware: This header is not a purely internal header, it is also included
 * from the outside world when building the STLport library. So this header
 * should not reference internal headers (stlport/stl/_*.h) directly.
 */
#  include <stddef.h>
#  include <wchar.h>
#  include <ctype.h>

/*
 * GENERAL FRAMEWORK
 */

/*
 * Opaque types, implementation (if there is one) depends
 * on platform locale API.
 */
struct _Locale_ctype;
struct _Locale_numeric;
struct _Locale_time;
struct _Locale_collate;
struct _Locale_monetary;
struct _Locale_messages;
struct _Locale_name_hint;

/*
 * Bitmask macros.
 * For narrow characters, we expose the lookup table interface.
 */

/* Internal bitmask macros, os-specific. */

#if defined (__MWERKS__)
#  define _Locale_CNTRL  __control_char
#  define _Locale_UPPER  __upper_case
#  define _Locale_LOWER  __lower_case
#  define _Locale_DIGIT  __digit
#  define _Locale_XDIGIT __hex_digit
#  define _Locale_PUNCT  __punctuation
#  define _Locale_SPACE  __space_char
#  define _Locale_PRINT  __printable
#  define _Locale_ALPHA  __alphanumeric
#endif

/* We arbitrarily consider _Locale_CNTRL macro to check locale facet numeric
 * identifier has been defined for the platform/compiler:
 */
#if !defined (_Locale_CNTRL)
#  error Unable to find your platform locale facets definitions, please grant them.
#endif

#endif /* _STLP_C_LOCALE_H */
