/*
 *
 * Copyright (c) 1996,1997
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

#ifndef _STLP_TYPE_TRAITS_H
#define _STLP_TYPE_TRAITS_H

/*
This header file provides a framework for allowing compile time dispatch
based on type attributes. This is useful when writing template code.
For example, when making a copy of an array of an unknown type, it helps
to know if the type has a trivial copy constructor or not, to help decide
if a memcpy can be used.

The class template __type_traits provides a series of typedefs each of
which is either __true_type or __false_type. The argument to
__type_traits can be any type. The typedefs within this template will
attain their correct values by one of these means:
    1. The general instantiation contain conservative values which work
       for all types.
    2. Specializations may be declared to make distinctions between types.
    3. Some compilers (such as the Silicon Graphics N32 and N64 compilers)
       will automatically provide the appropriate specializations for all
       types.

EXAMPLE:

//Copy an array of elements which have non-trivial copy constructors
template <class T> void copy(T* source, T* destination, int n, __false_type);
//Copy an array of elements which have trivial copy constructors. Use memcpy.
template <class T> void copy(T* source, T* destination, int n, __true_type);

//Copy an array of any type by using the most efficient copy mechanism
template <class T> inline void copy(T* source,T* destination,int n) {
   copy(source, destination, n,
        typename __type_traits<T>::has_trivial_copy_constructor());
}
*/

#ifndef _STLP_TYPE_MANIPS_H
#  include <stl/type_manips.h>
#endif

#ifdef _STLP_USE_BOOST_SUPPORT
#  include <stl/boost_type_traits.h>
#  include <boost/type_traits/add_reference.hpp>
#  include <boost/type_traits/add_const.hpp>
#endif /* _STLP_USE_BOOST_SUPPORT */

namespace _STLP_STD {

#if !defined (_STLP_USE_BOOST_SUPPORT)

// The following could be written in terms of numeric_limits.
// We're doing it separately to reduce the number of dependencies.

template <class _Tp> struct _IsIntegral
{ typedef __false_type _Ret; };

template<> struct _IsIntegral<bool>
{ typedef __true_type _Ret; };

template<> struct _IsIntegral<char>
{ typedef __true_type _Ret; };

template<> struct _IsIntegral<signed char>
{ typedef __true_type _Ret; };

template<> struct _IsIntegral<unsigned char>
{ typedef __true_type _Ret; };

template<> struct _IsIntegral<wchar_t>
{ typedef __true_type _Ret; };

template<> struct _IsIntegral<short>
{ typedef __true_type _Ret; };

template<> struct _IsIntegral<unsigned short>
{ typedef __true_type _Ret; };

template<> struct _IsIntegral<int>
{ typedef __true_type _Ret; };

template<> struct _IsIntegral<unsigned int>
{ typedef __true_type _Ret; };

template<> struct _IsIntegral<long>
{ typedef __true_type _Ret; };

template<> struct _IsIntegral<unsigned long>
{ typedef __true_type _Ret; };

template<> struct _IsIntegral<long long>
{ typedef __true_type _Ret; };

template<> struct _IsIntegral<unsigned long long>
{ typedef __true_type _Ret; };

template <class _Tp> struct _IsRational
{ typedef __false_type _Ret; };

template<> struct _IsRational<float>
{ typedef __true_type _Ret; };

template<> struct _IsRational<double>
{ typedef __true_type _Ret; };

template<> struct _IsRational<long double>
{ typedef __true_type _Ret; };

// Forward declarations.
template <class _Tp> struct __type_traits;
template <class _IsPOD> struct __type_traits_aux {
   typedef __false_type    has_trivial_default_constructor;
   typedef __false_type    has_trivial_copy_constructor;
   typedef __false_type    has_trivial_assignment_operator;
   typedef __false_type    has_trivial_destructor;
   typedef __false_type    is_POD_type;
};

template<>
struct __type_traits_aux<__false_type> {
   typedef __false_type    has_trivial_default_constructor;
   typedef __false_type    has_trivial_copy_constructor;
   typedef __false_type    has_trivial_assignment_operator;
   typedef __false_type    has_trivial_destructor;
   typedef __false_type    is_POD_type;
};

template<>
struct __type_traits_aux<__true_type> {
  typedef __true_type    has_trivial_default_constructor;
  typedef __true_type    has_trivial_copy_constructor;
  typedef __true_type    has_trivial_assignment_operator;
  typedef __true_type    has_trivial_destructor;
  typedef __true_type    is_POD_type;
};

template <class _Tp>
struct _IsRef {
  typedef __false_type _Ret;
};

template <class _Tp>  struct _IsPtr {
  typedef __false_type _Ret;
};

template <class _Tp>
struct __type_traits {
   typedef __true_type     this_dummy_member_must_be_first;
                   /* Do not remove this member. It informs a compiler which
                      automatically specializes __type_traits that this
                      __type_traits template is special. It just makes sure that
                      things work if an implementation is using a template
                      called __type_traits for something unrelated. */

   /* The following restrictions should be observed for the sake of
      compilers which automatically produce type specific specializations
      of this class:
          - You may reorder the members below if you wish
          - You may remove any of the members below if you wish
          - You must not rename members without making the corresponding
            name change in the compiler
          - Members you add will be treated like regular members unless

            you add the appropriate support in the compiler. */

   typedef __false_type    has_trivial_default_constructor;
   typedef __false_type    has_trivial_copy_constructor;
   typedef __false_type    has_trivial_assignment_operator;
   typedef __false_type    has_trivial_destructor;
   typedef __false_type    is_POD_type;
};

template <class _Tp> struct _IsPtr<_Tp*>
{ typedef __true_type _Ret; };
template <class _Tp> struct _IsRef<_Tp&>
{ typedef __true_type _Ret; };

template <class _Tp> struct __type_traits<_Tp*> : __type_traits_aux<__true_type>
{};

// Provide some specializations.  This is harmless for compilers that
//  have built-in __types_traits support, and essential for compilers
//  that don't.
#  define _STLP_DEFINE_TYPE_TRAITS_FOR(Type) \
template<> struct __type_traits< Type > : __type_traits_aux<__true_type> {}; \
template<> struct __type_traits< const Type > : __type_traits_aux<__true_type> {}; \
template<> struct __type_traits< volatile Type > : __type_traits_aux<__true_type> {}; \
template<> struct __type_traits< const volatile Type > : __type_traits_aux<__true_type> {}

_STLP_DEFINE_TYPE_TRAITS_FOR(bool);
_STLP_DEFINE_TYPE_TRAITS_FOR(char);
_STLP_DEFINE_TYPE_TRAITS_FOR(signed char);
_STLP_DEFINE_TYPE_TRAITS_FOR(unsigned char);
_STLP_DEFINE_TYPE_TRAITS_FOR(wchar_t);

_STLP_DEFINE_TYPE_TRAITS_FOR(short);
_STLP_DEFINE_TYPE_TRAITS_FOR(unsigned short);
_STLP_DEFINE_TYPE_TRAITS_FOR(int);
_STLP_DEFINE_TYPE_TRAITS_FOR(unsigned int);
_STLP_DEFINE_TYPE_TRAITS_FOR(long);
_STLP_DEFINE_TYPE_TRAITS_FOR(unsigned long);
_STLP_DEFINE_TYPE_TRAITS_FOR(long long);
_STLP_DEFINE_TYPE_TRAITS_FOR(unsigned long long);

_STLP_DEFINE_TYPE_TRAITS_FOR(float);
_STLP_DEFINE_TYPE_TRAITS_FOR(double);
_STLP_DEFINE_TYPE_TRAITS_FOR(long double);

template <class _ArePtrs, class _Src, class _Dst>
struct _IsCVConvertibleIf
{ typedef typename _IsCVConvertible<_Src, _Dst>::_Ret _Ret; };

template <class _Src, class _Dst>
struct _IsCVConvertibleIf<__false_type, _Src, _Dst>
{ typedef __false_type _Ret; };

template <class _Src, class _Dst>
struct _TrivialNativeTypeCopy {
  typedef typename _IsPtr<_Src>::_Ret _Ptr1;
  typedef typename _IsPtr<_Dst>::_Ret _Ptr2;
  typedef typename _Land2<_Ptr1, _Ptr2>::_Ret _BothPtrs;
  typedef typename _IsCVConvertibleIf<_BothPtrs, _Src, _Dst>::_Ret _Convertible;
  typedef typename _Land2<_BothPtrs, _Convertible>::_Ret _Trivial1;

  typedef typename __bool2type<(sizeof(_Src) == sizeof(_Dst))>::_Ret _SameSize;

  typedef typename _IsIntegral<_Src>::_Ret _Int1;
  typedef typename _IsIntegral<_Dst>::_Ret _Int2;
  typedef typename _Land2<_Int1, _Int2>::_Ret _BothInts;

  typedef typename _IsRational<_Src>::_Ret _Rat1;
  typedef typename _IsRational<_Dst>::_Ret _Rat2;
  typedef typename _Land2<_Rat1, _Rat2>::_Ret _BothRats;

  typedef typename _Lor2<_BothInts, _BothRats>::_Ret _BothNatives;
  typedef typename _Land2<_BothNatives, _SameSize>::_Ret _Trivial2;

  typedef typename _Lor2<_Trivial1, _Trivial2>::_Ret _Ret;
};

template <class _Src, class _Dst>
struct _TrivialCopy {
  typedef typename _TrivialNativeTypeCopy<_Src, _Dst>::_Ret _NativeRet;

  typedef typename __type_traits<_Src>::has_trivial_assignment_operator _Tr1;
  typedef typename _AreSameUnCVTypes<_Src, _Dst>::_Ret _Tr2;
  typedef typename _Land2<_Tr1, _Tr2>::_Ret _UserRet;

  typedef typename _Lor2<_NativeRet, _UserRet>::_Ret _Ret;
  static _Ret _Answer() { return _Ret(); }
};

template <class _Src, class _Dst>
struct _TrivialUCopy {
  typedef typename _TrivialNativeTypeCopy<_Src, _Dst>::_Ret _NativeRet;

  typedef typename __type_traits<_Src>::has_trivial_copy_constructor _Tr1;
  typedef typename _AreSameUnCVTypes<_Src, _Dst>::_Ret _Tr2;
  typedef typename _Land2<_Tr1, _Tr2>::_Ret _UserRet;

  typedef typename _Lor2<_NativeRet, _UserRet>::_Ret _Ret;
  static _Ret _Answer() { return _Ret(); }
};

template <class _Tp>
struct _DefaultZeroValue {
  typedef typename _IsIntegral<_Tp>::_Ret _Tr1;
  typedef typename _IsRational<_Tp>::_Ret _Tr2;
  typedef typename _IsPtr<_Tp>::_Ret _Tr3;
  typedef typename _Lor3<_Tr1, _Tr2, _Tr3>::_Ret _Ret;
};

template <class _Tp>
struct _TrivialInit {
  typedef typename __type_traits<_Tp>::has_trivial_default_constructor _Tr1;
  typedef typename _DefaultZeroValue<_Tp>::_Ret _Tr2;
  typedef typename _Not<_Tr2>::_Ret _Tr3;
  typedef typename _Land2<_Tr1, _Tr3>::_Ret _Ret;
  static _Ret _Answer() { return _Ret(); }
};

#endif /* !_STLP_USE_BOOST_SUPPORT */

template <class _Tp>
struct _IsPtrType {
  typedef typename _IsPtr<_Tp>::_Ret _Type;
  static _Type _Ret() { return _Type(); }
};

template <class _Tp>
struct _IsRefType {
  typedef typename _IsRef<_Tp>::_Ret _Type;
  static _Type _Ret() { return _Type();}
};

template <class _Tp>
struct __call_traits {
#if defined (_STLP_USE_BOOST_SUPPORT) && !defined (_STLP_NO_EXTENSIONS)
  typedef typename __select< ::boost::is_reference<_Tp>::value,
                             _Tp, typename ::boost::add_reference< typename ::boost::add_const<_Tp>::type >::type>::_Ret param_type;
#else
  typedef const _Tp& param_type;
#endif /* _STLP_USE_BOOST_SUPPORT */
};

#if !defined (_STLP_USE_BOOST_SUPPORT) && !defined (_STLP_NO_EXTENSIONS)
template <class _Tp>
struct __call_traits<_Tp&>
{ typedef _Tp& param_type; };
#endif

template <class _Tp1, class _Tp2>
struct _BothPtrType {
  typedef typename _IsPtr<_Tp1>::_Ret _IsPtr1;
  typedef typename _IsPtr<_Tp2>::_Ret _IsPtr2;

  typedef typename _Land2<_IsPtr1, _IsPtr2>::_Ret _Ret;
  static _Ret _Answer() { return _Ret(); }
};

template <class _Tp1, class _Tp2, class _IsRef1, class _IsRef2>
struct _OKToSwap {
  typedef typename _AreSameUnCVTypes<_Tp1, _Tp2>::_Ret _Same;
  typedef typename _Land3<_Same, _IsRef1, _IsRef2>::_Ret _Type;
  static _Type _Answer() { return _Type(); }
};

template <class _Tp1, class _Tp2, class _IsRef1, class _IsRef2>
inline _OKToSwap<_Tp1, _Tp2, _IsRef1, _IsRef2>
_IsOKToSwap(_Tp1*, _Tp2*, const _IsRef1&, const _IsRef2&)
{ return _OKToSwap<_Tp1, _Tp2, _IsRef1, _IsRef2>(); }

template <class _Src, class _Dst>
inline _TrivialCopy<_Src, _Dst> _UseTrivialCopy(_Src*, _Dst*)
{ return _TrivialCopy<_Src, _Dst>(); }

template <class _Src, class _Dst>
inline _TrivialUCopy<_Src, _Dst> _UseTrivialUCopy(_Src*, _Dst*)
{ return _TrivialUCopy<_Src, _Dst>(); }

template <class _Tp>
inline _TrivialInit<_Tp> _UseTrivialInit(_Tp*)
{ return _TrivialInit<_Tp>(); }

template <class _Tp>
struct _IsPOD {
  typedef typename __type_traits<_Tp>::is_POD_type _Type;
  static _Type _Answer() { return _Type(); }
};

template <class _Tp>
inline _IsPOD<_Tp> _Is_POD(_Tp*)
{ return _IsPOD<_Tp>(); }

template <class _Tp>
struct _DefaultZeroValueQuestion {
  typedef typename _DefaultZeroValue<_Tp>::_Ret _Ret;
  static _Ret _Answer() { return _Ret(); }
};

template <class _Tp>
inline _DefaultZeroValueQuestion<_Tp> _HasDefaultZeroValue(_Tp*)
{ return _DefaultZeroValueQuestion<_Tp>(); }

/*
 * Base class used:
 * - to simulate partial template specialization
 * - to simulate partial function ordering
 * - to recognize STLport class from user specialized one
 */
template <class _Tp>
struct __stlport_class
{ typedef _Tp _Type; };

template <class _Tp>
struct _IsSTLportClass {
  typedef typename _IsConvertible<_Tp, __stlport_class<_Tp> >::_Ret _Ret;
};

template <class _Tp>
class _TpWithState : private _Tp {
  _TpWithState();
  int _state;
};

/* This is an internal helper struct used to guess if we are working
 * on a stateless class. It can only be instanciated with a class type. */
template <class _Tp>
struct _IsStateless {
  enum { _Is = sizeof(_TpWithState<_Tp>) == sizeof(int) };
  typedef typename __bool2type<_Is>::_Ret _Ret;
};

}

#define _STLP_IS_POD_ITER(_It, _Tp) typename __type_traits< typename iterator_traits< _Tp >::value_type >::is_POD_type()

#endif /* _STLP_TYPE_TRAITS_H */

// Local Variables:
// mode:C++
// End:
