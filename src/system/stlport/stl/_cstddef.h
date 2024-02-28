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

#ifndef _STLP_INTERNAL_CSTDDEF
#define _STLP_INTERNAL_CSTDDEF

#  if defined (_STLP_USE_NEW_C_HEADERS)
#    include _STLP_NATIVE_CPP_C_HEADER(cstddef)
#  else
#    include <stddef.h>
#  endif

#  ifdef _STLP_IMPORT_VENDOR_CSTD
_STLP_BEGIN_NAMESPACE
using _STLP_VENDOR_CSTD::ptrdiff_t;
using _STLP_VENDOR_CSTD::size_t;
_STLP_END_NAMESPACE
#  endif /* _STLP_IMPORT_VENDOR_CSTD */

#endif /* _STLP_INTERNAL_CSTDDEF */
