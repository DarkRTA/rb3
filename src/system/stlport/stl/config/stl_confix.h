/*
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

/*
 * STLport configuration file
 * It is internal STLport header - DO NOT include it directly
 * Purpose of this file : to define STLport settings that depend on
 * compiler flags or can be otherwise missed
 *
 */

#ifndef _STLP_CONFIX_H
# define _STLP_CONFIX_H

/* If, by any chance, C compiler gets there, try to help it to pass smoothly */
# if ! defined (__cplusplus) && ! defined (_STLP_HAS_NO_NAMESPACES)
#  define _STLP_HAS_NO_NAMESPACES
# endif

#endif
