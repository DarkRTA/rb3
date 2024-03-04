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

#include _STLP_NATIVE_CPP_C_HEADER(cwchar)

namespace _STLP_STD {
using _STLP_VENDOR_STD::wint_t;

using _STLP_VENDOR_STD::size_t;

using _STLP_VENDOR_STD::mbstate_t;

using _STLP_VENDOR_STD::btowc;
using _STLP_VENDOR_STD::mbsinit;
using _STLP_VENDOR_STD::mbrlen;
using _STLP_VENDOR_STD::mbrtowc;
using _STLP_VENDOR_STD::mbsrtowcs;
using _STLP_VENDOR_STD::wcrtomb;
using _STLP_VENDOR_STD::wcsrtombs;

using _STLP_VENDOR_STD::fgetwc;
using _STLP_VENDOR_STD::fgetws;
using _STLP_VENDOR_STD::fputwc;
using _STLP_VENDOR_STD::fputws;

using _STLP_VENDOR_STD::fwide;
using _STLP_VENDOR_STD::fwprintf;
using _STLP_VENDOR_STD::fwscanf;
using _STLP_VENDOR_STD::getwchar;

using _STLP_VENDOR_STD::getwc;
using _STLP_VENDOR_STD::ungetwc;
using _STLP_VENDOR_STD::putwc;
using _STLP_VENDOR_STD::putwchar;

using _STLP_VENDOR_STD::swprintf;
using _STLP_VENDOR_STD::vswprintf;
using _STLP_VENDOR_STD::swscanf;
using _STLP_VENDOR_STD::vfwprintf;
using _STLP_VENDOR_STD::vwprintf;

using _STLP_VENDOR_STD::wcsftime;
using _STLP_VENDOR_STD::wcstok;

using _STLP_VENDOR_STD::wcscoll;
using _STLP_VENDOR_STD::wcsxfrm;
using _STLP_VENDOR_STD::wcscat;
using _STLP_VENDOR_STD::wcsrchr;
using _STLP_VENDOR_STD::wcscmp;

using _STLP_VENDOR_STD::wcscpy;
using _STLP_VENDOR_STD::wcscspn;

using _STLP_VENDOR_STD::wcslen;
using _STLP_VENDOR_STD::wcsncat;
using _STLP_VENDOR_STD::wcsncmp;
using _STLP_VENDOR_STD::wcsncpy;
using _STLP_VENDOR_STD::wcspbrk;
using _STLP_VENDOR_STD::wcschr;

using _STLP_VENDOR_STD::wcsspn;

using _STLP_VENDOR_STD::wcstod;
using _STLP_VENDOR_STD::wcstol;

using _STLP_VENDOR_STD::wcsstr;
using _STLP_VENDOR_STD::wmemchr;

using _STLP_VENDOR_STD::wctob;
using _STLP_VENDOR_STD::wmemcmp;
using _STLP_VENDOR_STD::wmemmove;
using _STLP_VENDOR_STD::wprintf;
using _STLP_VENDOR_STD::wscanf;

using _STLP_VENDOR_STD::wmemcpy;
using _STLP_VENDOR_STD::wmemset;

using _STLP_VENDOR_STD::wcslen;
using _STLP_VENDOR_STD::wcscmp;
using _STLP_VENDOR_STD::wcscpy;
using _STLP_VENDOR_STD::wcsstr;
using _STLP_VENDOR_STD::wcschr;
using _STLP_VENDOR_STD::wcsrchr;
using _STLP_VENDOR_STD::wcspbrk;
}

#endif /* _STLP_INTERNAL_CWCHAR */
