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


#ifndef _STLP_INTERNAL_LOCALE_H
#define _STLP_INTERNAL_LOCALE_H

#ifndef _STLP_INTERNAL_CSTDLIB
#  include <stl/_cstdlib.h>
#endif

#ifndef _STLP_INTERNAL_CWCHAR
#  include <stl/_cwchar.h>
#endif

#ifndef _STLP_INTERNAL_THREADS_H
#  include <stl/_threads.h>
#endif

#ifndef _STLP_STRING_FWD_H
#  include <stl/_string_fwd.h>
#endif

namespace _STLP_STD {

class _Locale_impl;        // Forward declaration of opaque type.
class ios_base;
class locale;

template <class _CharT, class _Traits, class _Alloc>
bool __locale_do_operator_call (const locale& __loc,
                                const basic_string<_CharT, _Traits, _Alloc>& __x,
                                const basic_string<_CharT, _Traits, _Alloc>& __y);

_Locale_impl * _get_Locale_impl( _Locale_impl *locimpl );
_Locale_impl * _copy_Nameless_Locale_impl( _Locale_impl *locimpl );

template <class _Facet>
bool _HasFacet(const locale& __loc, const _Facet* __facet) _STLP_NOTHROW;

template <class _Facet>
_Facet* _UseFacet(const locale& __loc, const _Facet* __facet);

class locale {
public:
  // types:
  class facet : protected _Refcount_Base {
  protected:
    /* Here we filter __init_count user value to 0 or 1 because __init_count is a
     * size_t instance and _Refcount_Base use __stl_atomic_t instances that might
     * have lower sizeof and generate roll issues. 1 is enough to keep the facet
     * alive when required.
     */
    explicit facet(size_t __init_count = 0) : _Refcount_Base( __init_count == 0 ? 0 : 1 ) {}
    virtual ~facet();
    friend class locale;
    friend class _Locale_impl;
    friend facet * _get_facet( facet * );
    friend void _release_facet( facet *& );

  private:                        // Invalidate assignment and copying.
    facet(const facet& ) /* : _Refcount_Base(1) {} */;
    void operator=(const facet&);
  };

  class id {
    friend class locale;
    friend class _Locale_impl;
  public:
    size_t _M_index;
    static size_t _S_max;
  };

  typedef int category;
  static const category
    none      = 0x000,
    collate   = 0x010,
    ctype     = 0x020,
    monetary  = 0x040,
    numeric   = 0x100,
    time      = 0x200,
    messages  = 0x400,
    all       = collate | ctype | monetary | numeric | time | messages;

  // construct/copy/destroy:
  locale() _STLP_NOTHROW;
  locale(const locale&) _STLP_NOTHROW;
  explicit locale(const char *);
  locale(const locale&, const char*, category);

  template <class _Facet>
  locale(const locale& __loc, _Facet* __f) {
    if ( __f != 0 ) {
      this->_M_impl = _get_Locale_impl( _copy_Nameless_Locale_impl( __loc._M_impl ) );
      this->_M_insert(__f, _Facet::id);
    } else {
      this->_M_impl = _get_Locale_impl( __loc._M_impl );
    }
  }

protected:
  // those are for internal use
  locale(_Locale_impl*);

public:

  locale(const locale&, const locale&, category);
  const locale& operator=(const locale&) _STLP_NOTHROW;

  ~locale() _STLP_NOTHROW;

  template <class _Facet>
  locale combine(const locale& __loc) const {
    _Facet *__facet = 0;
    if (!_HasFacet(__loc, __facet))
      _M_throw_runtime_error();

    return locale(*this, _UseFacet(__loc, __facet));
  }

  // locale operations:
  string name() const;

  bool operator==(const locale&) const;
  bool operator!=(const locale&) const;

  template <class _CharT, class _Traits, class _Alloc>
  bool operator()(const basic_string<_CharT, _Traits, _Alloc>& __x,
                  const basic_string<_CharT, _Traits, _Alloc>& __y) const
  { return __locale_do_operator_call(*this, __x, __y); }

  // global locale objects:
  static locale global(const locale&);
  static const locale& classic();

//protected:                         // Helper functions for locale globals.
  facet* _M_get_facet(const id&) const;
  // same, but throws
  facet* _M_use_facet(const id&) const;
  static void _STLP_FUNCTION_THROWS _M_throw_runtime_error(const char* = 0);

protected:                        // More helper functions.
  void _M_insert(facet* __f, id& __id);

  // friends:
  friend class _Locale_impl;
  friend class ios_base;

protected:                        // Data members
  _Locale_impl* _M_impl;
  _Locale_impl* _M_get_impl() const { return _M_impl; }
};

//----------------------------------------------------------------------
// locale globals

template <class _Facet> inline const _Facet& use_facet(const locale& __loc) {
  _Facet *__facet = 0;
  return *_UseFacet(__loc, __facet);
}

template <class _Facet> inline bool has_facet(const locale& __loc) _STLP_NOTHROW {
  _Facet *__facet = 0;
  return _HasFacet(__loc, __facet);
}

template <class _Facet>
bool _HasFacet(const locale& __loc, const _Facet* __facet) _STLP_NOTHROW
{ return (__loc._M_get_facet(_Facet::id) != 0); }

template <class _Facet>
_Facet* _UseFacet(const locale& __loc, const _Facet* __facet)
{ return static_cast<_Facet*>(__loc._M_use_facet(_Facet::id)); }

}

#endif /* _STLP_INTERNAL_LOCALE_H */

// Local Variables:
// mode:C++
// End:
