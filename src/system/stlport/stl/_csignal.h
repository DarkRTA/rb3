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

#ifndef _STLP_INTERNAL_CSIGNAL
#define _STLP_INTERNAL_CSIGNAL

#include _STLP_NATIVE_CPP_C_HEADER(csignal)

namespace _STLP_STD {
using _STLP_VENDOR_STD::signal;
using _STLP_VENDOR_STD::raise;
using _STLP_VENDOR_STD::sig_atomic_t;
}

#endif /* _STLP_INTERNAL_CSIGNAL */
