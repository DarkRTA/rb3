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

#include _STLP_NATIVE_CPP_C_HEADER(cwctype)

namespace _STLP_STD {
using _STLP_VENDOR_STD::wctype_t;
using _STLP_VENDOR_STD::wint_t;

using _STLP_VENDOR_STD::wctrans_t;
using _STLP_VENDOR_STD::towctrans;
using _STLP_VENDOR_STD::wctrans;
using _STLP_VENDOR_STD::wctype;
using _STLP_VENDOR_STD::iswctype;

using _STLP_VENDOR_STD::iswalnum;
using _STLP_VENDOR_STD::iswalpha;
using _STLP_VENDOR_STD::iswcntrl;

using _STLP_VENDOR_STD::iswdigit;
using _STLP_VENDOR_STD::iswgraph;
using _STLP_VENDOR_STD::iswlower;
using _STLP_VENDOR_STD::iswprint;
using _STLP_VENDOR_STD::iswpunct;
using _STLP_VENDOR_STD::iswspace;
using _STLP_VENDOR_STD::iswupper;
using _STLP_VENDOR_STD::iswxdigit;

using _STLP_VENDOR_STD::towlower;
using _STLP_VENDOR_STD::towupper;
}


#endif /* _STLP_INTERNAL_CWCTYPE */
