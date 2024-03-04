/*
 * Copyright (c) 1997
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

#ifndef _STLP_STRING_FWD_H
#define _STLP_STRING_FWD_H

#ifndef _STLP_IOSFWD
#  include <iosfwd>
#endif

namespace _STLP_STD {

template <class _CharT,
          class _Traits = char_traits<_CharT>,
          class _Alloc = allocator<_CharT> >
class basic_string;

typedef basic_string<char, char_traits<char>, allocator<char> > string;
typedef basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > wstring;

}

namespace _STLP_PRIV {

//This function limits header dependency between exception and string
//implementation. It is implemented in _string.h
const char* __get_c_string(const string& __str);

}

#endif /* _STLP_STRING_FWD_H */

// Local Variables:
// mode:C++
// End:
