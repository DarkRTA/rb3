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

#ifndef _STLP_CHAR_TRAITS_H
#define _STLP_CHAR_TRAITS_H

// Define char_traits

#ifndef _STLP_INTERNAL_CSTDDEF
#  include <stl/_cstddef.h>
#endif

#ifndef _STLP_INTERNAL_CSTRING
#  include <stl/_cstring.h>
#endif

#ifndef _STLP_INTERNAL_CONSTRUCT_H
#  include <stl/_construct.h>
#endif

#ifndef _STLP_INTERNAL_CWCHAR
#  include <stl/_cwchar.h>
#endif

namespace _STLP_STD {

template <class _Tp> class allocator;

#define _STLP_NULL_CHAR_INIT(_ChT) _ChT()

typedef long streamoff;
typedef ptrdiff_t streamsize;

// Class fpos, which represents a position within a file.  (The C++
// standard calls for it to be defined in <ios>.  This implementation
// moves it to <iosfwd>, which is included by <ios>.)
template <class _StateT> class fpos {
public:                         // From table 88 of the C++ standard.
  fpos(streamoff __pos) : _M_pos(__pos), _M_st(_STLP_NULL_CHAR_INIT(_StateT)) {}
  fpos() : _M_pos(0), _M_st(_STLP_NULL_CHAR_INIT(_StateT)) {}

  operator streamoff() const { return _M_pos; }

  bool operator==(const fpos& __y) const
  { return _M_pos == __y._M_pos; }
  bool operator!=(const fpos& __y) const
  { return _M_pos != __y._M_pos; }

  fpos& operator+=(streamoff __off) {
    _M_pos += __off;
    return *this;
  }
  fpos& operator-=(streamoff __off) {
    _M_pos -= __off;
    return *this;
  }

  fpos operator+(streamoff __off) {
    fpos __tmp(*this);
    __tmp += __off;
    return __tmp;
  }
  fpos operator-(streamoff __off) {
    fpos __tmp(*this);
    __tmp -= __off;
    return __tmp;
  }

public:                         // Manipulation of the state member.
  _StateT state() const { return _M_st; }
  void state(_StateT __st) { _M_st = __st; }
private:
  streamoff _M_pos;
  _StateT _M_st;
};

typedef fpos<mbstate_t> streampos;
typedef fpos<mbstate_t> wstreampos;

// Class __char_traits_base.
template <class _CharT, class _IntT>
class __char_traits_base {
public:
  typedef _CharT char_type;
  typedef _IntT int_type;
  typedef streamoff off_type;
  typedef streampos pos_type;
  typedef mbstate_t state_type;

  static void assign(char_type& __c1, const char_type& __c2) { __c1 = __c2; }
  static bool eq(const char_type& __c1, const char_type& __c2)
  { return __c1 == __c2; }
  static bool lt(const char_type& __c1, const char_type& __c2)
  { return __c1 < __c2; }

  static int compare(const char_type* __s1, const char_type* __s2, size_t __n) {
    for (size_t __i = 0; __i < __n; ++__i)
      if (!eq(__s1[__i], __s2[__i]))
        return __s1[__i] < __s2[__i] ? -1 : 1;
    return 0;
  }

  static size_t length(const char_type* __s) {
    const char_type _NullChar = char_type();
    size_t __i(0);
    for (; !eq(__s[__i], _NullChar); ++__i) {}
    return __i;
  }

  static const char_type* find(const char_type* __s, size_t __n, const char_type& __c) {
    for ( ; __n > 0 ; ++__s, --__n)
      if (eq(*__s, __c))
        return __s;
    return 0;
  }

  static char_type* move(char_type* __s1, const char_type* __s2, size_t _Sz)
  { return (_Sz == 0 ? __s1 : (char_type*)memmove(__s1, __s2, _Sz * sizeof(char_type))); }

  static char_type* copy(char_type* __s1, const char_type* __s2, size_t __n) {
    return (__n == 0 ? __s1 :
      (char_type*)memcpy(__s1, __s2, __n * sizeof(char_type)));
  }

  static char_type* assign(char_type* __s, size_t __n, char_type __c) {
    for (size_t __i = 0; __i < __n; ++__i)
      __s[__i] = __c;
    return __s;
  }

  static int_type not_eof(const int_type& __c)
  { return !eq_int_type(__c, eof()) ? __c : static_cast<int_type>(0); }

  static char_type to_char_type(const int_type& __c)
  { return (char_type)__c; }

  static int_type to_int_type(const char_type& __c)
  { return (int_type)__c; }

  static bool eq_int_type(const int_type& __c1, const int_type& __c2)
  { return __c1 == __c2; }

  static int_type eof()
  { return (int_type)-1; }
};

// Generic char_traits class.  Note that this class is provided only
//  as a base for explicit specialization; it is unlikely to be useful
//  as is for any particular user-defined type.  In particular, it
//  *will not work* for a non-POD type.

template <class _CharT>
class char_traits
  : public __char_traits_base<_CharT, _CharT> {};

// Specialization for char.

template<>
class char_traits<char>
  : public __char_traits_base<char, int> {
public:
  typedef char char_type;
  typedef int int_type;
  typedef streamoff off_type;
  typedef streampos pos_type;
  typedef mbstate_t state_type;

  static char to_char_type(const int& __c)
  { return (char)(unsigned char)__c; }

  static int to_int_type(const char& __c)
  { return (unsigned char)__c; }

  static int compare(const char* __s1, const char* __s2, size_t __n)
  { return memcmp(__s1, __s2, __n); }

  static size_t length(const char* __s)
  { return strlen(__s); }

  static void assign(char& __c1, const char& __c2)
  { __c1 = __c2; }

  static char* assign(char* __s, size_t __n, char __c) {
    memset(__s, __c, __n);
    return __s;
  }
};

// Specialization for wchar_t.
template<>
class char_traits<wchar_t>
  : public __char_traits_base<wchar_t, wint_t> {
public:
  static wchar_t* move(wchar_t* __dest, const wchar_t* __src, size_t __n)
  { return wmemmove(__dest, __src, __n); }

  static wchar_t* copy(wchar_t* __dest, const wchar_t* __src, size_t __n)
  { return wmemcpy(__dest, __src, __n); }

  static int compare(const wchar_t* __s1, const wchar_t* __s2, size_t __n)
  { return wmemcmp(__s1, __s2, __n); }

  static wchar_t* assign(wchar_t* __s, size_t __n, wchar_t __c)
  { return wmemset(__s, __c, __n); }

  static size_t length(const wchar_t* __s)
  { return wcslen(__s); }

  static void assign(wchar_t& __c1, const wchar_t& __c2)
  { __c1 = __c2; }
};

}

#endif /* _STLP_CHAR_TRAITS_H */

// Local Variables:
// mode:C++
// End:
