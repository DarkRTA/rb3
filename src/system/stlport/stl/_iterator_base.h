/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996-1998
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
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

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef _STLP_INTERNAL_ITERATOR_BASE_H
#define _STLP_INTERNAL_ITERATOR_BASE_H

#ifndef _STLP_INTERNAL_CSTDDEF
#  include <stl/_cstddef.h>
#endif

namespace _STLP_STD {

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};


template <class _Category, class _Tp, class _Distance = ptrdiff_t,
          class _Pointer = _Tp*, class _Reference = _Tp& >
struct iterator {
  typedef _Category  iterator_category;
  typedef _Tp        value_type;
  typedef _Distance  difference_type;
  typedef _Pointer   pointer;
  typedef _Reference reference;
};
template<>
struct iterator<output_iterator_tag, void, void, void, void> {
  typedef output_iterator_tag  iterator_category;
  typedef void                value_type;
  typedef void                difference_type;
  typedef void                pointer;
  typedef void                reference;
};

#define _STLP_VALUE_TYPE(_It, _Tp)        (typename iterator_traits< _Tp >::value_type*)0
#define _STLP_DISTANCE_TYPE(_It, _Tp)     (typename iterator_traits< _Tp >::difference_type*)0
#define _STLP_ITERATOR_CATEGORY(_It, _Tp) typename iterator_traits< _Tp >::iterator_category()
#define _STLP_IS_REF_TYPE_REAL_REF(_It, _Tp) _IsRefType< typename iterator_traits< _Tp >::reference >::_Ret()

template <class _Iterator>
struct iterator_traits {
  typedef typename _Iterator::iterator_category iterator_category;
  typedef typename _Iterator::value_type        value_type;
  typedef typename _Iterator::difference_type   difference_type;
  typedef typename _Iterator::pointer           pointer;
  typedef typename _Iterator::reference         reference;
};

// fbp : this order keeps gcc happy
template <class _Tp>
struct iterator_traits<const _Tp*> {
  typedef random_access_iterator_tag  iterator_category;
  typedef _Tp                         value_type;
  typedef ptrdiff_t                   difference_type;
  typedef const _Tp*                  pointer;
  typedef const _Tp&                  reference;
};

template <class _Tp>
struct iterator_traits<_Tp*> {
  typedef random_access_iterator_tag  iterator_category;
  typedef _Tp                         value_type;
  typedef ptrdiff_t                   difference_type;
  typedef _Tp*                        pointer;
  typedef _Tp&                        reference;
};

# if ! defined (_STLP_NO_ANACHRONISMS)
// The base classes input_iterator, output_iterator, forward_iterator,
// bidirectional_iterator, and random_access_iterator are not part of
// the C++ standard.  (They have been replaced by struct iterator.)
// They are included for backward compatibility with the HP STL.
template <class _Tp, class _Distance> struct input_iterator :
  public iterator <input_iterator_tag, _Tp, _Distance, _Tp*, _Tp&> {};
struct output_iterator : public iterator <output_iterator_tag, void, void, void, void> {};
template <class _Tp, class _Distance> struct forward_iterator :
  public iterator<forward_iterator_tag, _Tp, _Distance, _Tp*, _Tp&> {};
template <class _Tp, class _Distance> struct bidirectional_iterator :
  public iterator<bidirectional_iterator_tag, _Tp, _Distance, _Tp*, _Tp&> {};
template <class _Tp, class _Distance> struct random_access_iterator :
  public iterator<random_access_iterator_tag, _Tp, _Distance, _Tp*, _Tp&> {};

#endif /* _STLP_NO_ANACHRONISMS */

template <class _InputIterator, class _Distance>
inline void __distance(const _InputIterator& __first, const _InputIterator& __last,
                                  _Distance& __n, const input_iterator_tag &) {
  _InputIterator __it(__first);
  while (__it != __last) { ++__it; ++__n; }
}

template <class _RandomAccessIterator, class _Distance>
inline void __distance(const _RandomAccessIterator& __first,
                                  const _RandomAccessIterator& __last,
                                  _Distance& __n, const random_access_iterator_tag &) {
  __n += __last - __first;
}

#ifndef _STLP_NO_ANACHRONISMS
template <class _InputIterator, class _Distance>
inline void distance(const _InputIterator& __first,
        const _InputIterator& __last, _Distance& __n) {
  __distance(__first, __last, __n, _STLP_ITERATOR_CATEGORY(__first, _InputIterator));
}
#endif

template <class _InputIterator>
inline typename iterator_traits<_InputIterator>::difference_type
__distance(const _InputIterator& __first, const _InputIterator& __last, const input_iterator_tag &) {
  typename iterator_traits<_InputIterator>::difference_type __n = 0;
  _InputIterator __it(__first);
  while (__it != __last) {
    ++__it; ++__n;
  }
  return __n;
}

template <class _RandomAccessIterator>
inline typename iterator_traits<_RandomAccessIterator>::difference_type
__distance(const _RandomAccessIterator& __first, const _RandomAccessIterator& __last,
           const random_access_iterator_tag &) {
  return __last - __first;
}

template <class _InputIterator>
inline typename iterator_traits<_InputIterator>::difference_type
distance(_InputIterator __first, _InputIterator __last) {
  return __distance(__first, __last, _STLP_ITERATOR_CATEGORY(__first, _InputIterator));
}

// fbp: those are being used for iterator/const_iterator definitions everywhere
template <class _Tp>
struct _Nonconst_traits;

template <class _Tp>
struct _Const_traits {
  typedef _Tp value_type;
  typedef const _Tp&  reference;
  typedef const _Tp*  pointer;
  typedef _Const_traits<_Tp> _ConstTraits;
  typedef _Nonconst_traits<_Tp> _NonConstTraits;
};

template <class _Tp>
struct _Nonconst_traits {
  typedef _Tp value_type;
  typedef _Tp& reference;
  typedef _Tp* pointer;
  typedef _Const_traits<_Tp> _ConstTraits;
  typedef _Nonconst_traits<_Tp> _NonConstTraits;
};

/*
 * dums: A special iterator/const_iterator traits for set and multiset for which even
 * the iterator is not mutable
 */
template <class _Tp>
struct _Nonconst_Const_traits;

template <class _Tp>
struct _Const_Const_traits {
  typedef _Tp value_type;
  typedef const _Tp&  reference;
  typedef const _Tp*  pointer;
  typedef _Const_Const_traits<_Tp> _ConstTraits;
  typedef _Nonconst_Const_traits<_Tp> _NonConstTraits;
};

template <class _Tp>
struct _Nonconst_Const_traits {
  typedef _Tp value_type;
  typedef const _Tp& reference;
  typedef const _Tp* pointer;
  typedef _Const_Const_traits<_Tp> _ConstTraits;
  typedef _Nonconst_Const_traits<_Tp> _NonConstTraits;
};

/*
 * A macro to generate a new iterator traits from one of the
 * previous one. Changing the iterator traits type make iterators
 * from different containers not comparable.
 */
#define _STLP_CREATE_ITERATOR_TRAITS_BASE(Motif, Traits)        \
template <class _Tp>                                            \
struct _##Motif;                                                \
template <class _Tp>                                            \
struct _Const##Motif : public _STLP_STD::_Const_##Traits<_Tp> {  \
  typedef _Const##Motif<_Tp> _ConstTraits;                      \
  typedef _##Motif<_Tp> _NonConstTraits;                        \
};                                                              \
template <class _Tp>                                            \
struct _##Motif : public _STLP_STD::_Nonconst_##Traits<_Tp> {    \
  typedef _Const##Motif<_Tp> _ConstTraits;                      \
  typedef _##Motif<_Tp> _NonConstTraits;                        \
};

#define _STLP_CREATE_ITERATOR_TRAITS(Motif, Traits)             \
} namespace _STLP_PRIV_FORCE {                                  \
_STLP_CREATE_ITERATOR_TRAITS_BASE(Motif, Traits)                \
} namespace _STLP_STD {

#define _STLP_CREATE_HASH_ITERATOR_TRAITS(Motif, Traits)        \
} namespace _STLP_PRIV_FORCE {                                  \
_STLP_CREATE_ITERATOR_TRAITS_BASE(NonLocal##Motif, Traits)      \
_STLP_CREATE_ITERATOR_TRAITS_BASE(Local##Motif, Traits)         \
template <class _Tp>                                            \
struct _##Motif {                                               \
  typedef _ConstNonLocal##Motif<_Tp> _ConstTraits;              \
  typedef _NonLocal##Motif<_Tp> _NonConstTraits;                \
  typedef _ConstLocal##Motif<_Tp> _ConstLocalTraits;            \
  typedef _Local##Motif<_Tp> _NonConstLocalTraits;              \
};                                                              \
} namespace _STLP_STD {

template <class _InputIter, class _Distance>
inline void
__advance(_InputIter& __i, _Distance __n, const input_iterator_tag &) {
  while (__n--) ++__i;
}

// fbp : added output iterator tag variant
template <class _InputIter, class _Distance>
inline void
__advance(_InputIter& __i, _Distance __n, const output_iterator_tag &) {
  while (__n--) ++__i;
}

template <class _BidirectionalIterator, class _Distance>
inline void
__advance(_BidirectionalIterator& __i, _Distance __n,
          const bidirectional_iterator_tag &) {
  if (__n > 0)
    while (__n--) ++__i;
  else
    while (__n++) --__i;
}

template <class _RandomAccessIterator, class _Distance>
inline void
__advance(_RandomAccessIterator& __i, _Distance __n,
          const random_access_iterator_tag &) {
  __i += __n;
}

template <class _InputIterator, class _Distance>
inline void advance(_InputIterator& __i, _Distance __n) {
  __advance(__i, __n, _STLP_ITERATOR_CATEGORY(__i, _InputIterator));
}

}

#if defined (_STLP_DEBUG) && !defined (_STLP_DEBUG_H)
#  include <stl/debug/_debug.h>
#endif

#endif /* _STLP_INTERNAL_ITERATOR_BASE_H */


// Local Variables:
// mode:C++
// End:
