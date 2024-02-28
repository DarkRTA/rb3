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

#if !defined (_STLP_NO_TYPEINFO)

#  if defined (_STLP_NO_NEW_NEW_HEADER)
#    include <typeinfo.h>
#  else
#    ifdef _STLP_BROKEN_BAD_CAST_CLASS
#      define bad_cast _STLP_NULLIFIED_BROKEN_BAD_CAST_CLASS
#    endif
#    include _STLP_NATIVE_CPP_RUNTIME_HEADER(typeinfo)
#    ifdef _STLP_BROKEN_BAD_CAST_CLASS
#      undef bad_cast
#      undef _STLP_NULLIFIED_BROKEN_BAD_CAST_CLASS
#    endif
#  endif

// if <typeinfo.h> already included, do not import anything
#  if defined(_STLP_USE_NAMESPACES) && !defined(_STLP_OLDSTD_typeinfo) && \
      (defined(_STLP_VENDOR_GLOBAL_EXCEPT_STD) || \
       defined(_STLP_USE_OWN_NAMESPACE) || defined (_STLP_DEBUG))

_STLP_BEGIN_NAMESPACE

using _STLP_VENDOR_EXCEPT_STD::type_info;
using _STLP_VENDOR_EXCEPT_STD::bad_typeid;
using _STLP_VENDOR_EXCEPT_STD::bad_cast;

_STLP_END_NAMESPACE

#  endif

#else

#  ifndef _STLP_INTERNAL_EXCEPTION
#    include <stl/_exception.h>
#  endif

_STLP_BEGIN_NAMESPACE

struct bad_cast : exception {};

_STLP_END_NAMESPACE
#endif

#endif
