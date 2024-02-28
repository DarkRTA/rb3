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

#ifndef _STLP_INTERNAL_CSTDLIB
#define _STLP_INTERNAL_CSTDLIB

#if defined (_STLP_USE_NEW_C_HEADERS)
#  include _STLP_NATIVE_CPP_C_HEADER(cstdlib)
#else
#  include <stdlib.h>
#endif

#ifdef _STLP_IMPORT_VENDOR_CSTD
_STLP_BEGIN_NAMESPACE
using _STLP_VENDOR_CSTD::div_t;
using _STLP_VENDOR_CSTD::ldiv_t;
using _STLP_VENDOR_CSTD::size_t;

#  ifndef _STLP_NO_CSTD_FUNCTION_IMPORTS
using _STLP_VENDOR_CSTD::abort;
using _STLP_VENDOR_CSTD::getenv;

using _STLP_VENDOR_CSTD::mblen;
using _STLP_VENDOR_CSTD::mbtowc;

using _STLP_VENDOR_CSTD::system;
using _STLP_VENDOR_CSTD::bsearch;

using _STLP_VENDOR_CSTD::atexit;
using _STLP_VENDOR_CSTD::exit;
using _STLP_VENDOR_CSTD::calloc;
using _STLP_VENDOR_CSTD::free;
using _STLP_VENDOR_CSTD::malloc;
using _STLP_VENDOR_CSTD::realloc;
using _STLP_VENDOR_CSTD::atof;
using _STLP_VENDOR_CSTD::atoi;
using _STLP_VENDOR_CSTD::atol;

using _STLP_VENDOR_CSTD::mbstowcs;

using _STLP_VENDOR_CSTD::strtod;
using _STLP_VENDOR_CSTD::strtol;
using _STLP_VENDOR_CSTD::strtoul;

#    if !(defined (_STLP_NO_NATIVE_WIDE_STREAMS) || defined (_STLP_NO_MBSTATE_T))
using _STLP_VENDOR_CSTD::wcstombs;
using _STLP_VENDOR_CSTD::wctomb;
#    endif
using _STLP_VENDOR_CSTD::qsort;
using _STLP_VENDOR_CSTD::labs;
using _STLP_VENDOR_CSTD::ldiv;
#    if defined (_STLP_LONG_LONG) && !defined (_STLP_NO_VENDOR_STDLIB_L)
using _STLP_VENDOR_CSTD::llabs;
using _STLP_VENDOR_CSTD::lldiv_t;
using _STLP_VENDOR_CSTD::lldiv;
#    endif
using _STLP_VENDOR_CSTD::rand;
using _STLP_VENDOR_CSTD::srand;
#  endif /* _STLP_NO_CSTD_FUNCTION_IMPORTS */
_STLP_END_NAMESPACE
#endif /* _STLP_IMPORT_VENDOR_CSTD */

inline long abs(long __x) { return _STLP_VENDOR_CSTD::labs(__x); }
inline _STLP_VENDOR_CSTD::ldiv_t div(long __x, long __y) { return _STLP_VENDOR_CSTD::ldiv(__x, __y); }

#if defined (_STLP_RESTORE_FUNCTION_INTRINSIC)
#  pragma intrinsic (abs)
#  pragma warning (pop)
#  undef _STLP_RESTORE_FUNCTION_INTRINSIC
#endif

#if defined (_STLP_LONG_LONG)
#  if !defined (_STLP_NO_VENDOR_STDLIB_L)
inline _STLP_LONG_LONG  abs(_STLP_LONG_LONG __x) { return _STLP_VENDOR_CSTD::llabs(__x); }
inline lldiv_t div(_STLP_LONG_LONG __x, _STLP_LONG_LONG __y) { return _STLP_VENDOR_CSTD::lldiv(__x, __y); }
#  else
inline _STLP_LONG_LONG  abs(_STLP_LONG_LONG __x) { return __x < 0 ? -__x : __x; }
#  endif
#endif

/* C++ Standard is unclear about several call to 'using ::func' if new overloads
 * of ::func appears between 2 successive 'using' calls. To avoid this potential
 * problem we provide all abs overload before the 'using' call.
 * Beware: This header inclusion has to be after all abs overload of this file.
 *         The first 'using ::abs' call is going to be in the other header.
 */
#ifndef _STLP_INTERNAL_CMATH
#  include <stl/_cmath.h>
#endif

#if defined (_STLP_IMPORT_VENDOR_CSTD) && !defined (_STLP_NO_CSTD_FUNCTION_IMPORTS)
// ad hoc, don't replace with _STLP_VENDOR_CSTD::abs here! - ptr 2005-03-05
_STLP_BEGIN_NAMESPACE
using ::abs;
using ::div;
_STLP_END_NAMESPACE
#endif

#endif /* _STLP_INTERNAL_CSTDLIB */
