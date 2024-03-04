/*
 * Copyright (c) 1999
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
// WARNING: This is an internal header file, included by other C++
// standard library headers.  You should not attempt to use this header
// file directly.


#ifndef _STLP_INTERNAL_NUM_PUT_H
#define _STLP_INTERNAL_NUM_PUT_H

#ifndef _STLP_INTERNAL_NUMPUNCT_H
# include <stl/_numpunct.h>
#endif

#ifndef _STLP_INTERNAL_CTYPE_H
# include <stl/_ctype.h>
#endif

#ifndef _STLP_INTERNAL_OSTREAMBUF_ITERATOR_H
# include <stl/_ostreambuf_iterator.h>
#endif

#ifndef _STLP_INTERNAL_IOSTREAM_STRING_H
# include <stl/_iostream_string.h>
#endif

namespace _STLP_STD {

// num_put facet
template <class _CharT, class _OutputIter = ostreambuf_iterator<_CharT, char_traits<_CharT> > >
class num_put: public locale::facet {
  friend class _Locale_impl;
public:
  typedef _CharT      char_type;
  typedef _OutputIter iter_type;

  explicit num_put(size_t __refs = 0) : locale::facet(__refs) {}

  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                bool __val) const {
    return do_put(__s, __f, __fill, __val);
  }

  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
               long __val) const {
    return do_put(__s, __f, __fill, __val);
  }

  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                unsigned long __val) const {
    return do_put(__s, __f, __fill, __val);
  }

  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                long long __val) const {
    return do_put(__s, __f, __fill, __val);
  }

  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                unsigned long long __val) const {
    return do_put(__s, __f, __fill, __val);
  }

  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                double __val) const {
    return do_put(__s, __f, __fill, (double)__val);
  }

  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                long double __val) const {
    return do_put(__s, __f, __fill, __val);
  }

  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                const void * __val) const {
    return do_put(__s, __f, __fill, __val);
  }

  static locale::id id;

protected:
  ~num_put() {}

  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, bool __val) const;
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, long __val) const;
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, unsigned long __val) const;
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, double __val) const;
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, long double __val) const;

  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, long long __val) const;
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, unsigned long long __val) const;
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, const void* __val) const;
};

}

#if defined (_STLP_EXPOSE_STREAM_IMPLEMENTATION)

namespace _STLP_PRIV {

template <class _Integer>
char*
__write_integer_backward(char* __buf, ios_base::fmtflags __flags, _Integer __x);

/*
 * Returns the position on the right of the digits that has to be considered
 * for the application of the grouping policy.
 */
extern size_t __write_float(__iostring&, ios_base::fmtflags, int, double);
extern size_t __write_float(__iostring&, ios_base::fmtflags, int, long double);

/*
 * Gets the digits of the integer part.
 */
void __get_floor_digits(__iostring&, long double);

template <class _CharT>
void __get_money_digits(_STLP_BASIC_IOSTRING(_CharT)&, ios_base&, long double);

extern void __convert_float_buffer(__iostring const&, __iowstring&, const ctype<wchar_t>&, wchar_t, bool = true);
extern void __adjust_float_buffer(__iostring&, char);

extern char*
__write_integer(char* buf, ios_base::fmtflags flags, long x);

extern ptrdiff_t __insert_grouping(char* first, char* last, const string&, char, char, char, int);
extern void __insert_grouping(__iostring&, size_t, const string&, char, char, char, int);
extern ptrdiff_t __insert_grouping(wchar_t*, wchar_t*, const string&, wchar_t, wchar_t, wchar_t, int);
extern void __insert_grouping(__iowstring&, size_t, const string&, wchar_t, wchar_t, wchar_t, int);

}

#endif /* _STLP_EXPOSE_STREAM_IMPLEMENTATION */

#if defined (_STLP_EXPOSE_STREAM_IMPLEMENTATION) && !defined (_STLP_LINK_TIME_INSTANTIATION)
#  include <stl/_num_put.c>
#endif

#endif /* _STLP_INTERNAL_NUMERIC_FACETS_H */

// Local Variables:
// mode:C++
// End:
