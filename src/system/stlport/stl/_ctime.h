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

namespace _STLP_STD {
using _STLP_VENDOR_STD::size_t;
using _STLP_VENDOR_STD::clock_t;
using _STLP_VENDOR_STD::time_t;
using _STLP_VENDOR_STD::tm;
using _STLP_VENDOR_STD::clock;
using _STLP_VENDOR_STD::asctime;
using _STLP_VENDOR_STD::ctime;
using _STLP_VENDOR_STD::gmtime;

using _STLP_VENDOR_STD::difftime;
using _STLP_VENDOR_STD::mktime;
using _STLP_VENDOR_STD::localtime;
using _STLP_VENDOR_STD::strftime;
using _STLP_VENDOR_STD::time;
}

#endif /* _STLP_INTERNAL_CTIME */
