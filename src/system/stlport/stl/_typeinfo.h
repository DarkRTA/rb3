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

#ifndef _STLP_INTERNAL_TYPEINFO
#define _STLP_INTERNAL_TYPEINFO

#include _STLP_NATIVE_CPP_RUNTIME_HEADER(typeinfo)

#if defined(_STLP_USE_OWN_NAMESPACE)

_STLP_BEGIN_NAMESPACE

using _STLP_VENDOR_EXCEPT_STD::type_info;
using _STLP_VENDOR_EXCEPT_STD::bad_typeid;
using _STLP_VENDOR_EXCEPT_STD::bad_cast;

_STLP_END_NAMESPACE

#endif

#endif
