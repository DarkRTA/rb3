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
 *
 */

#ifndef _STLP_INTERNAL_STDEXCEPT_BASE
#define _STLP_INTERNAL_STDEXCEPT_BASE

#  ifndef _STLP_INTERNAL_EXCEPTION
#    include <stl/_exception.h>
#  endif

#  if defined(_STLP_USE_EXCEPTIONS)

#    ifndef _STLP_INTERNAL_CSTRING
#      include <stl/_cstring.h>
#    endif

#    ifndef _STLP_STRING_FWD_H
#      include <stl/_string_fwd.h>
#    endif

#    ifndef _STLP_USE_NO_IOSTREAMS
#      define _STLP_OWN_STDEXCEPT 1
#    endif

namespace _STLP_STD {

using _STLP_VENDOR_STD::exception;

class __Named_exception : public exception {
public:
  __Named_exception(const string& __str)
#    ifndef _STLP_USE_NO_IOSTREAMS
    ;
  const char* what() const _STLP_NOTHROW_INHERENTLY;
  ~__Named_exception() _STLP_NOTHROW_INHERENTLY;
#    else
  {
#      if !defined (_STLP_USE_SAFE_STRING_FUNCTIONS)
    strncpy(_M_name, _STLP_PRIV::__get_c_string(__str), _S_bufsize);
    _M_name[_S_bufsize - 1] = '\0';
#      else
    strncpy_s(_STLP_ARRAY_AND_SIZE(_M_name), _STLP_PRIV::__get_c_string(__str), _TRUNCATE);
#      endif
  }
  const char* what() const _STLP_NOTHROW_INHERENTLY { return _M_name; }
#    endif

private:
  enum { _S_bufsize = 256 };
  char _M_name[_S_bufsize];
};

#    if defined (_STLP_DO_WARNING_POP)
#      pragma warning (pop)
#      undef _STLP_DO_WARNING_POP
#    endif

}

#  endif /*No exceptions */

#endif /* _STLP_INTERNAL_STDEXCEPT_BASE */
