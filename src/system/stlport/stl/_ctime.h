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

#ifndef _STLP_INTERNAL_CTIME
#define _STLP_INTERNAL_CTIME

#include _STLP_NATIVE_CPP_C_HEADER(ctime)

_STLP_BEGIN_NAMESPACE
using _STLP_VENDOR_CSTD::size_t;
using _STLP_VENDOR_CSTD::clock_t;
using _STLP_VENDOR_CSTD::time_t;
using _STLP_VENDOR_CSTD::tm;
using _STLP_VENDOR_CSTD::clock;
using _STLP_VENDOR_CSTD::asctime;
using _STLP_VENDOR_CSTD::ctime;
using _STLP_VENDOR_CSTD::gmtime;

using _STLP_VENDOR_CSTD::difftime;
using _STLP_VENDOR_CSTD::mktime;
using _STLP_VENDOR_CSTD::localtime;
using _STLP_VENDOR_CSTD::strftime;
using _STLP_VENDOR_CSTD::time;
_STLP_END_NAMESPACE

#endif /* _STLP_INTERNAL_CTIME */
