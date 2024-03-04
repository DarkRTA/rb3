/*
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
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
 */

// The header <exception> contains low-level functions that interact
// with a compiler's exception-handling mechanism.  It is assumed to
// be supplied with the compiler, rather than with the library, because
// it is inherently tied very closely to the compiler itself.

// On platforms where <exception> does not exist, this header defines
// an exception base class.  This is *not* a substitute for everything
// in <exception>, but it suffices to support a bare minimum of STL
// functionality.

#ifndef _STLP_INTERNAL_EXCEPTION
#define _STLP_INTERNAL_EXCEPTION

#include _STLP_NATIVE_CPP_RUNTIME_HEADER(exception)

#if defined (_STLP_USE_OWN_NAMESPACE)

_STLP_BEGIN_NAMESPACE

using _STLP_VENDOR_EXCEPT_STD::exception;
using _STLP_VENDOR_EXCEPT_STD::bad_exception;

using _STLP_VENDOR_EXCEPT_STD::unexpected;
using _STLP_VENDOR_EXCEPT_STD::unexpected_handler;
using _STLP_VENDOR_EXCEPT_STD::set_unexpected;

using _STLP_VENDOR_EXCEPT_STD::terminate;
using _STLP_VENDOR_EXCEPT_STD::terminate_handler;
using _STLP_VENDOR_EXCEPT_STD::set_terminate;

using _STLP_VENDOR_EXCEPT_STD::uncaught_exception;

_STLP_END_NAMESPACE

#endif /* _STLP_OWN_NAMESPACE */

#endif /* _STLP_INTERNAL_EXCEPTION */
