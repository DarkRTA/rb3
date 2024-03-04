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
#ifndef _STLP_TIME_FACETS_C
#define _STLP_TIME_FACETS_C

#ifndef _STLP_INTERNAL_TIME_FACETS_H
#  include <stl/_time_facets.h>
#endif

#ifndef _STLP_INTERNAL_NUM_PUT_H
#  include <stl/_num_put.h>
#endif

#ifndef _STLP_INTERNAL_NUM_GET_H
#  include <stl/_num_get.h>
#endif

namespace _STLP_STD {

//----------------------------------------------------------------------
// Declarations of static template members.
template <class _CharT, class _InputIterator>
locale::id time_get<_CharT, _InputIterator>::id;

template <class _CharT, class _OutputIterator>
locale::id time_put<_CharT, _OutputIterator>::id;

}

namespace _STLP_PRIV {

template <class _InIt, class _CharT>
const string*
__match(_InIt& __first, _InIt& __last, const string *__name, const string *__name_end,
        const ctype<_CharT>& __ct) {
  typedef ptrdiff_t difference_type;
  difference_type __n = __name_end - __name;
  difference_type __i;
  size_t __pos = 0;
  difference_type __check_count = __n;
  bool __do_check[_MAXNAMES];
  const string* __matching_name[_MAX_NAME_LENGTH];

  for (__i = 0; __i < _MAXNAMES; ++__i)
    __do_check[__i] = true;

  for (__i = 0; __i < _MAX_NAME_LENGTH; ++__i)
    __matching_name[__i] = __name_end;

  while (__first != __last) {
    for (__i = 0; __i < __n; ++__i) {
      if (__do_check[__i]) {
        if (*__first == __ct.widen(__name[__i][__pos])) {
          if (__pos == (__name[__i].size() - 1)) {
            __do_check[__i] = 0;
            __matching_name[__pos + 1] = __name + __i;
            --__check_count;
            if (__check_count == 0) {
              ++__first;
              return __name + __i;
            }
          }
        }
        else {
          __do_check[__i] = 0;
          --__check_count;
          if (__check_count == 0)
            return __matching_name[__pos];
        }
      }
    }

    ++__first; ++__pos;
  }

  return __matching_name[__pos];
}

// __get_formatted_time reads input that is assumed to be formatted
// according to the rules for the C strftime function (C standard,
// 7.12.3.5).  This function is used to implement the do_get_time
// and do_get_date virtual functions, which depend on the locale
// specifications for the time and day formats respectively.
// Note the catchall default case, intended mainly for the '%Z'
// format designator, which does not make sense here since the
// representation of timezones is not part of the locale.
//
// The case branches are implemented either by doing a match using
// the appopriate name table or by doing a __get_integer_nogroup.
//
// 'y' format is assumed to mean that the input represents years
// since 1900.  That is, 2002 should be represented as 102.  There
// is no century-guessing.
//
// The match is successful if and only if the second component of the
// return value is format_end.

// Note that the antepenultimate parameter is being used only to determine
// the correct overloading for the calls to __get_integer_nogroup.
template <class _InIt1, class _Ch>
string::const_iterator
__get_formatted_time (_InIt1 __first,  _InIt1 __last,
                                 string::const_iterator __format, string::const_iterator __format_end,
                                 _Ch*, const _Time_Info& __table,
                                 const ios_base& __s, ios_base::iostate& __err, tm* __t) {
  const ctype<_Ch>& __ct = *static_cast<const ctype<_Ch>*>(__s._M_ctype_facet());
  while (__first != __last && __format != __format_end) {
    if (*__format == '%') {
      ++__format;
      char __c = *__format;
      if (__c == '#') { //MS extension
        ++__format;
        __c = *__format;
      }

      switch (__c) {
        case 'a': {
          const string* __pr = __match(__first, __last,
                                       __table._M_dayname + 0, __table._M_dayname + 7,
                                       __ct);
          if (__pr == __table._M_dayname + 7)
            return __format;
          __t->tm_wday = static_cast<int>(__pr - __table._M_dayname);
          break;
        }

        case 'A': {
          const string* __pr = __match(__first, __last,
                                       __table._M_dayname + 7, __table._M_dayname + 14,
                                       __ct);
          if (__pr == __table._M_dayname + 14)
            return __format;
          __t->tm_wday = static_cast<int>(__pr - __table._M_dayname - 7);
          break;
        }

        case 'b': {
          const string* __pr = __match(__first, __last,
                                       __table._M_monthname + 0, __table._M_monthname + 12,
                                       __ct);
          if (__pr == __table._M_monthname + 12)
            return __format;
          __t->tm_mon = static_cast<int>(__pr - __table._M_monthname);
          break;
        }

        case 'B': {
          const string* __pr = __match(__first, __last,
                                       __table._M_monthname + 12, __table._M_monthname + 24,
                                       __ct);
          if (__pr == __table._M_monthname + 24)
            return __format;
          __t->tm_mon = static_cast<int>(__pr - __table._M_monthname - 12);
          break;
        }

        case 'd': {
          bool __pr = __get_decimal_integer(__first, __last, __t->tm_mday, static_cast<_Ch*>(0));
          if (!__pr || __t->tm_mday < 1 || __t->tm_mday > 31) {
            __err |= ios_base::failbit;
            return __format;
          }
          break;
        }

        case 'H': case 'I': {
          bool __pr = __get_decimal_integer(__first, __last, __t->tm_hour, static_cast<_Ch*>(0));
          if (!__pr)
            return __format;
          break;
        }

        case 'j': {
          bool __pr = __get_decimal_integer(__first, __last, __t->tm_yday, static_cast<_Ch*>(0));
          if (!__pr)
            return __format;
          break;
        }

        case 'm': {
          bool __pr = __get_decimal_integer(__first, __last, __t->tm_mon, static_cast<_Ch*>(0));
          --__t->tm_mon;
          if (!__pr || __t->tm_mon < 0 || __t->tm_mon > 11) {
            __err |= ios_base::failbit;
            return __format;
          }
          break;
        }

        case 'M': {
          bool __pr = __get_decimal_integer(__first, __last, __t->tm_min, static_cast<_Ch*>(0));
          if (!__pr)
            return __format;
          break;
        }

        case 'p': {
          const string* __pr = __match(__first, __last,
                                       __table._M_am_pm + 0, __table._M_am_pm + 2, __ct);
          if (__pr == __table._M_am_pm + 2)
            return __format;
          // 12:00 PM <=> 12:00, 12:00 AM <=> 00:00
          if (__pr == __table._M_am_pm + 1 && __t->tm_hour != 12 )
            __t->tm_hour += 12;
          if (__pr == __table._M_am_pm && __t->tm_hour == 12 )
            __t->tm_hour = 0;
          break;
        }

        case 'S': {
          bool __pr = __get_decimal_integer(__first, __last, __t->tm_sec, static_cast<_Ch*>(0));
          if (!__pr)
            return __format;
          break;
        }

        case 'y': {
          bool __pr = __get_decimal_integer(__first, __last, __t->tm_year, static_cast<_Ch*>(0));
          if (!__pr)
            return __format;
          break;
        }

        case 'Y': {
          bool __pr = __get_decimal_integer(__first, __last, __t->tm_year, static_cast<_Ch*>(0));
          __t->tm_year -= 1900;
          if (!__pr)
            return __format;
          break;
        }

        default:
          break;
      }
    }
    else {
      if (*__first++ != __ct.widen(*__format)) break;
    }

    ++__format;
  }

  return __format;
}

template <class _InIt, class _CharT>
bool
__get_short_or_long_dayname(_InIt& __first, _InIt& __last, const ctype<_CharT>& __ct,
                            const _Time_Info& __table, tm* __t) {
  const string* __pr =
    __match(__first, __last, __table._M_dayname + 0, __table._M_dayname + 14, __ct);
  __t->tm_wday = static_cast<int>((__pr - __table._M_dayname) % 7);
  return __pr != __table._M_dayname + 14;
}

template <class _InIt, class _CharT>
bool
__get_short_or_long_monthname(_InIt& __first, _InIt& __last, const ctype<_CharT>& __ct,
                              const _Time_Info& __table, tm* __t) {
  const string* __pr =
    __match(__first, __last, __table._M_monthname + 0, __table._M_monthname + 24, __ct);
  __t->tm_mon = static_cast<int>((__pr - __table._M_monthname) % 12);
  return __pr != __table._M_monthname + 24;
}

template <class _OuIt>
_OuIt
__put_time(char * __first, char * __last, _OuIt __out_ite,
           const ios_base& __s, wchar_t) {
    const ctype<wchar_t>& __ct = *static_cast<const ctype<wchar_t>*>(__s._M_ctype_facet());
    wchar_t __wbuf[64];
    __ct.widen(__first, __last, __wbuf);
    ptrdiff_t __len = __last - __first;
    wchar_t * __eend = __wbuf + __len;
    return copy((wchar_t*)__wbuf, __eend, __out_ite);
}

}

namespace _STLP_STD {

template <class _Ch, class _InIt>
_InIt
time_get<_Ch, _InIt>::do_get_date(_InIt __s, _InIt  __end,
                                  ios_base& __str, ios_base::iostate&  __err,
                                  tm* __t) const {
  typedef string::const_iterator string_iterator;

  string_iterator __format = _M_timeinfo._M_date_format.begin();
  string_iterator __format_end = _M_timeinfo._M_date_format.end();

  string_iterator __result
    = _STLP_PRIV::__get_formatted_time(__s, __end, __format, __format_end,
                                      static_cast<_Ch*>(0), _M_timeinfo,
                                      __str, __err, __t);
  if (__result == __format_end)
    __err = ios_base::goodbit;
  else {
    __err = ios_base::failbit;
    if (__s == __end)
      __err |= ios_base::eofbit;
  }
  return __s;
}

template <class _Ch, class _InIt>
_InIt
time_get<_Ch, _InIt>::do_get_time(_InIt __s, _InIt  __end,
                                  ios_base& __str, ios_base::iostate&  __err,
                                  tm* __t) const {
  typedef string::const_iterator string_iterator;
  string_iterator __format = _M_timeinfo._M_time_format.begin();
  string_iterator __format_end = _M_timeinfo._M_time_format.end();

  string_iterator __result
    = _STLP_PRIV::__get_formatted_time(__s, __end, __format, __format_end,
                                      static_cast<_Ch*>(0), _M_timeinfo,
                                      __str, __err, __t);
  __err = __result == __format_end ? ios_base::goodbit
                                   : ios_base::failbit;
  if (__s == __end)
    __err |= ios_base::eofbit;
  return __s;
}

template <class _Ch, class _InIt>
_InIt
time_get<_Ch, _InIt>::do_get_year(_InIt __s, _InIt  __end,
                                  ios_base&, ios_base::iostate&  __err,
                                  tm* __t) const {
  if (__s == __end) {
    __err = ios_base::failbit | ios_base::eofbit;
    return __s;
  }

  bool __pr =  _STLP_PRIV::__get_decimal_integer(__s, __end, __t->tm_year, static_cast<_Ch*>(0));
  __t->tm_year -= 1900;
  __err = __pr ? ios_base::goodbit : ios_base::failbit;
  if (__s == __end)
    __err |= ios_base::eofbit;

  return __s;
}

template <class _Ch, class _InIt>
_InIt
time_get<_Ch, _InIt>::do_get_weekday(_InIt __s, _InIt  __end,
                                     ios_base &__str, ios_base::iostate &__err,
                                     tm *__t) const {
  const ctype<_Ch>& __ct = *static_cast<const ctype<_Ch>*>(__str._M_ctype_facet());
  bool __result =
    _STLP_PRIV::__get_short_or_long_dayname(__s, __end, __ct, _M_timeinfo, __t);
  if (__result)
    __err = ios_base::goodbit;
  else {
    __err = ios_base::failbit;
    if (__s == __end)
      __err |= ios_base::eofbit;
  }
  return __s;
}

template <class _Ch, class _InIt>
_InIt
time_get<_Ch, _InIt>::do_get_monthname(_InIt __s, _InIt  __end,
                                       ios_base &__str, ios_base::iostate &__err,
                                       tm *__t) const {
  const ctype<_Ch>& __ct = *static_cast<const ctype<_Ch>*>(__str._M_ctype_facet());
  bool __result =
    _STLP_PRIV::__get_short_or_long_monthname(__s, __end, __ct, _M_timeinfo, __t);
  if (__result)
    __err = ios_base::goodbit;
  else {
    __err = ios_base::failbit;
    if (__s == __end)
      __err |= ios_base::eofbit;
  }
  return __s;
}

template<class _Ch, class _OutputIter>
_OutputIter
time_put<_Ch,_OutputIter>::put(_OutputIter __s, ios_base& __f, _Ch __fill,
                               const tm* __tmb, const _Ch* __pat,
                               const _Ch* __pat_end) const {
  //  locale __loc = __f.getloc();
  //  const ctype<_Ch>& _Ct = use_facet<ctype<_Ch> >(__loc);
  const ctype<_Ch>& _Ct = *static_cast<const ctype<_Ch>*>(__f._M_ctype_facet());
  while (__pat != __pat_end) {
    char __c = _Ct.narrow(*__pat, 0);
    if (__c == '%') {
      char __mod = 0;
      ++__pat;
      __c = _Ct.narrow(*__pat++, 0);
      if (__c == '#') { // MS extension
        __mod = __c;
        __c = _Ct.narrow(*__pat++, 0);
      }
      __s = do_put(__s, __f, __fill, __tmb, __c, __mod);
    }
    else
      *__s++ = *__pat++;
  }
  return __s;
}

template<class _Ch, class _OutputIter>
_OutputIter
time_put<_Ch,_OutputIter>::do_put(_OutputIter __s, ios_base& __f, _Ch /* __fill */,
                                  const tm* __tmb, char __format,
                                  char __modifier ) const {
  char __buf[64];
  char * __iend = _STLP_PRIV::__write_formatted_time(_STLP_ARRAY_AND_SIZE(__buf),
                                                    __format, __modifier, _M_timeinfo, __tmb);
  //  locale __loc = __f.getloc();
  return _STLP_PRIV::__put_time(__buf, __iend, __s, __f, _Ch());
}

}

#endif /* _STLP_TIME_FACETS_C */

// Local Variables:
// mode:C++
// End:
