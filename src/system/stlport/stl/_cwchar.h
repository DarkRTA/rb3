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

#ifndef _STLP_INTERNAL_CWCHAR
#define _STLP_INTERNAL_CWCHAR

#  if !defined (_STLP_NO_CWCHAR) && defined (_STLP_USE_NEW_C_HEADERS)
#    include _STLP_NATIVE_CPP_C_HEADER(cwchar)
#  elif defined (_STLP_NO_WCHAR_T)
#    include _STLP_NATIVE_C_HEADER(stddef.h)
#  else
#    include _STLP_NATIVE_C_HEADER(wchar.h)
#  endif

#  ifndef _STLP_INTERNAL_MBSTATE_T
#    include <stl/_mbstate_t.h>
#  endif

#  if !defined (_STLP_NO_WCHAR_T)
#    ifndef WCHAR_MIN
#      define WCHAR_MIN 0
#      define WCHAR_MAX ((wchar_t)~0)
#    endif
#  endif

#  if defined (_STLP_IMPORT_VENDOR_CSTD)

_STLP_BEGIN_NAMESPACE
#    if defined (_STLP_NO_WCHAR_T)
typedef int wint_t;
#    else
using _STLP_VENDOR_CSTD::wint_t;
#    endif

using _STLP_VENDOR_CSTD::size_t;

#    if !defined (_STLP_NO_NATIVE_MBSTATE_T) && !defined (_STLP_USE_OWN_MBSTATE_T)
using _STLP_VENDOR_MB_NAMESPACE::mbstate_t;

#      if !defined (_STLP_NO_CSTD_FUNCTION_IMPORTS)
using _STLP_VENDOR_MB_NAMESPACE::btowc;
using _STLP_VENDOR_MB_NAMESPACE::mbsinit;
using _STLP_VENDOR_MB_NAMESPACE::mbrlen;
using _STLP_VENDOR_MB_NAMESPACE::mbrtowc;
using _STLP_VENDOR_MB_NAMESPACE::mbsrtowcs;
using _STLP_VENDOR_MB_NAMESPACE::wcrtomb;
using _STLP_VENDOR_MB_NAMESPACE::wcsrtombs;
#      endif

#    endif /* _STLP_NO_NATIVE_MBSTATE_T */

#    if !defined (_STLP_NO_NATIVE_WIDE_FUNCTIONS) && ! defined (_STLP_NO_CSTD_FUNCTION_IMPORTS)

using _STLP_VENDOR_CSTD::fgetwc;
using _STLP_VENDOR_CSTD::fgetws;
using _STLP_VENDOR_CSTD::fputwc;
using _STLP_VENDOR_CSTD::fputws;

using _STLP_VENDOR_CSTD::fwide;
using _STLP_VENDOR_CSTD::fwprintf;
using _STLP_VENDOR_CSTD::fwscanf;
using _STLP_VENDOR_CSTD::getwchar;

using _STLP_VENDOR_CSTD::getwc;
using _STLP_VENDOR_CSTD::ungetwc;
using _STLP_VENDOR_CSTD::putwc;
using _STLP_VENDOR_CSTD::putwchar;

using _STLP_VENDOR_CSTD::swprintf;
using _STLP_VENDOR_CSTD::vswprintf;
using _STLP_VENDOR_CSTD::swscanf;
using _STLP_VENDOR_CSTD::vfwprintf;
using _STLP_VENDOR_CSTD::vwprintf;

using _STLP_VENDOR_CSTD::wcsftime;
using _STLP_VENDOR_CSTD::wcstok;

using _STLP_VENDOR_CSTD::wcscoll;
using _STLP_VENDOR_CSTD::wcsxfrm;
using _STLP_VENDOR_CSTD::wcscat;
using _STLP_VENDOR_CSTD::wcsrchr;
using _STLP_VENDOR_CSTD::wcscmp;

using _STLP_VENDOR_CSTD::wcscpy;
using _STLP_VENDOR_CSTD::wcscspn;

using _STLP_VENDOR_CSTD::wcslen;
using _STLP_VENDOR_CSTD::wcsncat;
using _STLP_VENDOR_CSTD::wcsncmp;
using _STLP_VENDOR_CSTD::wcsncpy;
using _STLP_VENDOR_CSTD::wcspbrk;
using _STLP_VENDOR_CSTD::wcschr;

using _STLP_VENDOR_CSTD::wcsspn;

using _STLP_VENDOR_CSTD::wcstod;
using _STLP_VENDOR_CSTD::wcstol;

using _STLP_VENDOR_CSTD::wcsstr;
using _STLP_VENDOR_CSTD::wmemchr;

using _STLP_VENDOR_CSTD::wctob;
using _STLP_VENDOR_CSTD::wmemcmp;
using _STLP_VENDOR_CSTD::wmemmove;
using _STLP_VENDOR_CSTD::wprintf;
using _STLP_VENDOR_CSTD::wscanf;

using _STLP_VENDOR_CSTD::wmemcpy;
using _STLP_VENDOR_CSTD::wmemset;

using _STLP_VENDOR_CSTD::wcslen;
using _STLP_VENDOR_CSTD::wcscmp;
using _STLP_VENDOR_CSTD::wcscpy;
using _STLP_VENDOR_CSTD::wcsstr;
using _STLP_VENDOR_CSTD::wcschr;
using _STLP_VENDOR_CSTD::wcsrchr;
using _STLP_VENDOR_CSTD::wcspbrk;
#    endif /* _STLP_NO_NATIVE_WIDE_FUNCTIONS */
_STLP_END_NAMESPACE

#  endif /* _STLP_IMPORT_VENDOR_CSTD */

#endif /* _STLP_INTERNAL_CWCHAR */
