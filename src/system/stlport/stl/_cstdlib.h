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

#  include _STLP_NATIVE_CPP_C_HEADER(cstdlib)

namespace _STLP_STD {
using _STLP_VENDOR_STD::div_t;
using _STLP_VENDOR_STD::ldiv_t;
using _STLP_VENDOR_STD::size_t;

using _STLP_VENDOR_STD::abort;
using _STLP_VENDOR_STD::getenv;

using _STLP_VENDOR_STD::mblen;
using _STLP_VENDOR_STD::mbtowc;

using _STLP_VENDOR_STD::system;
using _STLP_VENDOR_STD::bsearch;

using _STLP_VENDOR_STD::atexit;
using _STLP_VENDOR_STD::exit;
using _STLP_VENDOR_STD::calloc;
using _STLP_VENDOR_STD::free;
using _STLP_VENDOR_STD::malloc;
using _STLP_VENDOR_STD::realloc;
using _STLP_VENDOR_STD::atof;
using _STLP_VENDOR_STD::atoi;
using _STLP_VENDOR_STD::atol;

using _STLP_VENDOR_STD::mbstowcs;

using _STLP_VENDOR_STD::strtod;
using _STLP_VENDOR_STD::strtol;
using _STLP_VENDOR_STD::strtoul;

using _STLP_VENDOR_STD::wcstombs;
using _STLP_VENDOR_STD::wctomb;

using _STLP_VENDOR_STD::qsort;
using _STLP_VENDOR_STD::labs;
using _STLP_VENDOR_STD::ldiv;

using _STLP_VENDOR_STD::llabs;
using _STLP_VENDOR_STD::lldiv_t;
using _STLP_VENDOR_STD::lldiv;

using _STLP_VENDOR_STD::rand;
using _STLP_VENDOR_STD::srand;
}

inline long abs(long __x) { return _STLP_VENDOR_STD::labs(__x); }
inline _STLP_VENDOR_STD::ldiv_t div(long __x, long __y) { return _STLP_VENDOR_STD::ldiv(__x, __y); }

#  if !defined (_STLP_NO_VENDOR_STDLIB_L)
inline long long abs(long long __x) { return _STLP_VENDOR_STD::llabs(__x); }
inline lldiv_t div(long long __x, long long __y) { return _STLP_VENDOR_STD::lldiv(__x, __y); }
#  else
inline long long abs(long long __x) { return __x < 0 ? -__x : __x; }
#  endif

/* C++ Standard is unclear about several call to 'using ::func' if new overloads
 * of ::func appears between 2 successive 'using' calls. To avoid this potential
 * problem we provide all abs overload before the 'using' call.
 * Beware: This header inclusion has to be after all abs overload of this file.
 *         The first 'using ::abs' call is going to be in the other header.
 */
#ifndef _STLP_INTERNAL_CMATH
#  include <stl/_cmath.h>
#endif

namespace _STLP_STD {
using _STLP_VENDOR_STD::abs;
using _STLP_VENDOR_STD::div;
}

#endif /* _STLP_INTERNAL_CSTDLIB */
