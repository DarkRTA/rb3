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

#ifndef _STLP_INTERNAL_CWCTYPE
#define _STLP_INTERNAL_CWCTYPE

#  if defined (_STLP_USE_NEW_C_HEADERS)
#    include _STLP_NATIVE_CPP_C_HEADER(cwctype)
#  else
#    include _STLP_NATIVE_C_HEADER(wctype.h)
#  endif

#  if defined (_STLP_IMPORT_VENDOR_CSTD)

_STLP_BEGIN_NAMESPACE
using _STLP_VENDOR_CSTD::wctype_t;
using _STLP_VENDOR_CSTD::wint_t;

#    if !defined (_STLP_NO_CSTD_FUNCTION_IMPORTS)
using _STLP_VENDOR_CSTD::wctrans_t;
using _STLP_VENDOR_CSTD::towctrans;
using _STLP_VENDOR_CSTD::wctrans;
using _STLP_VENDOR_CSTD::wctype;
using _STLP_VENDOR_CSTD::iswctype;

using _STLP_VENDOR_CSTD::iswalnum;
using _STLP_VENDOR_CSTD::iswalpha;
using _STLP_VENDOR_CSTD::iswcntrl;

using _STLP_VENDOR_CSTD::iswdigit;
using _STLP_VENDOR_CSTD::iswgraph;
using _STLP_VENDOR_CSTD::iswlower;
using _STLP_VENDOR_CSTD::iswprint;
using _STLP_VENDOR_CSTD::iswpunct;
using _STLP_VENDOR_CSTD::iswspace;
using _STLP_VENDOR_CSTD::iswupper;
using _STLP_VENDOR_CSTD::iswxdigit;

using _STLP_VENDOR_CSTD::towlower;
using _STLP_VENDOR_CSTD::towupper;
#    endif /* _STLP_NO_CSTD_FUNCTION_IMPORTS */
_STLP_END_NAMESPACE
#  endif /* _STLP_IMPORT_VENDOR_CSTD */


#endif /* _STLP_INTERNAL_CWCTYPE */
