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


#ifndef _STLP_INTERNAL_NUM_GET_H
#define _STLP_INTERNAL_NUM_GET_H

#ifndef _STLP_INTERNAL_ISTREAMBUF_ITERATOR_H
#  include <stl/_istreambuf_iterator.h>
#endif

#ifndef _STLP_C_LOCALE_H
#  include <stl/c_locale.h>
#endif

#ifndef _STLP_INTERNAL_NUMPUNCT_H
#  include <stl/_numpunct.h>
#endif

#ifndef _STLP_INTERNAL_CTYPE_H
#  include <stl/_ctype.h>
#endif

#ifndef _STLP_INTERNAL_IOSTREAM_STRING_H
#  include <stl/_iostream_string.h>
#endif

namespace _STLP_STD {

// num_get facets
template <class _CharT, class _InputIter = istreambuf_iterator<_CharT, char_traits<_CharT> > >
class num_get: public locale::facet {
  friend class _Locale_impl;
public:
  typedef _CharT     char_type;
  typedef _InputIter iter_type;

  explicit num_get(size_t __refs = 0): locale::facet(__refs) {}

  _InputIter get(_InputIter __ii, _InputIter __end, ios_base& __str,
                 ios_base::iostate& __err, bool& __val) const
  { return do_get(__ii, __end, __str, __err, __val); }

  _InputIter get(_InputIter __ii, _InputIter __end, ios_base& __str,
                 ios_base::iostate& __err, long& __val) const
  { return do_get(__ii, __end, __str, __err, __val); }

  _InputIter get(_InputIter __ii, _InputIter __end, ios_base& __str,
                 ios_base::iostate& __err, unsigned short& __val) const
  { return do_get(__ii, __end, __str, __err, __val); }

  _InputIter get(_InputIter __ii, _InputIter __end, ios_base& __str,
                 ios_base::iostate& __err, unsigned int& __val) const
  { return do_get(__ii, __end, __str, __err, __val); }

  _InputIter get(_InputIter __ii, _InputIter __end, ios_base& __str,
                 ios_base::iostate& __err, unsigned long& __val) const
  { return do_get(__ii, __end, __str, __err, __val); }

  _InputIter get(_InputIter __ii, _InputIter __end, ios_base& __str,
                 ios_base::iostate& __err, long long& __val) const
  { return do_get(__ii, __end, __str, __err, __val); }

  _InputIter get(_InputIter __ii, _InputIter __end, ios_base& __str,
                 ios_base::iostate& __err, unsigned long long& __val) const
  { return do_get(__ii, __end, __str, __err, __val); }

  _InputIter get(_InputIter __ii, _InputIter __end, ios_base& __str,
                 ios_base::iostate& __err, float& __val) const
  { return do_get(__ii, __end, __str, __err, __val); }

  _InputIter get(_InputIter __ii, _InputIter __end, ios_base& __str,
                 ios_base::iostate& __err, double& __val) const
  { return do_get(__ii, __end, __str, __err, __val); }

  _InputIter get(_InputIter __ii, _InputIter __end, ios_base& __str,
                 ios_base::iostate& __err, long double& __val) const
  { return do_get(__ii, __end, __str, __err, __val); }

  _InputIter get(_InputIter __ii, _InputIter __end, ios_base& __str,
                 ios_base::iostate& __err, void*& __val) const
  { return do_get(__ii, __end, __str, __err, __val); }

  static locale::id id;

protected:
  ~num_get() {}

  typedef string               string_type;
  typedef ctype<_CharT>        _Ctype;
  typedef numpunct<_CharT>     _Numpunct;

  virtual _InputIter do_get(_InputIter __ii, _InputIter __end, ios_base& __str,
                            ios_base::iostate& __err, bool& __val) const;
  virtual _InputIter do_get(_InputIter __ii, _InputIter __end, ios_base& __str,
                            ios_base::iostate& __err, long& __val) const;
  virtual _InputIter do_get(_InputIter __ii, _InputIter __end, ios_base& __str,
                            ios_base::iostate& __err, unsigned short& __val) const;
  virtual _InputIter do_get(_InputIter __ii, _InputIter __end, ios_base& __str,
                            ios_base::iostate& __err, unsigned int& __val) const;
  virtual _InputIter do_get(_InputIter __ii, _InputIter __end, ios_base& __str,
                            ios_base::iostate& __err, unsigned long& __val) const;

  virtual _InputIter do_get(_InputIter __ii, _InputIter __end, ios_base& __str,
                            ios_base::iostate& __err, float& __val) const;
  virtual _InputIter do_get(_InputIter __ii, _InputIter __end, ios_base& __str,
                            ios_base::iostate& __err, double& __val) const;
  virtual _InputIter do_get(_InputIter __ii, _InputIter __end, ios_base& __str,
                            ios_base::iostate& __err, long double& __val) const;

  virtual _InputIter do_get(_InputIter __ii, _InputIter __end, ios_base& __str,
                            ios_base::iostate& __err, void*& __p) const;

  virtual _InputIter do_get(_InputIter __ii, _InputIter __end, ios_base& __str,
                            ios_base::iostate& __err, long long& __val) const;
  virtual _InputIter do_get(_InputIter __ii, _InputIter __end, ios_base& __str,
                            ios_base::iostate& __err, unsigned long long& __val) const;

};

}

#if defined (_STLP_EXPOSE_STREAM_IMPLEMENTATION)

namespace _STLP_PRIV {

bool __valid_grouping(const char*, const char*, const char*, const char*);

template <class _InputIter, class _Integer, class _CharT>
bool
__get_decimal_integer(_InputIter& __first, _InputIter& __last, _Integer& __val, _CharT*);

bool __get_fdigit(wchar_t&, const wchar_t*);
bool __get_fdigit_or_sep(wchar_t&, wchar_t, const wchar_t*);

inline void
_Initialize_get_float(const ctype<char>&,
                       char& Plus, char& Minus,
                       char& pow_e, char& pow_E,
                       char*) {
  Plus = '+';
  Minus = '-';
  pow_e = 'e';
  pow_E = 'E';
}

void _Initialize_get_float(const ctype<wchar_t>&,
                                                     wchar_t&, wchar_t&, wchar_t&, wchar_t&, wchar_t*);
void __string_to_float(const __iostring&, float&);
void __string_to_float(const __iostring&, double&);
void __string_to_float(const __iostring&, long double&);

}

#endif /* _STLP_EXPOSE_STREAM_IMPLEMENTATION */

#if defined (_STLP_EXPOSE_STREAM_IMPLEMENTATION) && !defined (_STLP_LINK_TIME_INSTANTIATION)
#  include <stl/_num_get.c>
#endif

#endif /* _STLP_INTERNAL_NUM_GET_H */

// Local Variables:
// mode:C++
// End:
