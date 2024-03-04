/*
 *
 * Copyright (c) 2003
 * Fran�ois Dumont
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


#ifndef _STLP_TYPE_MANIPS_H
#define _STLP_TYPE_MANIPS_H

namespace _STLP_STD {

struct __true_type {};
struct __false_type {};

}

namespace _STLP_PRIV {
using _STLP_STD::__true_type;
using _STLP_STD::__false_type;
}

namespace _STLP_STD {

//bool to type
template <int _Is>
struct __bool2type
{ typedef __true_type _Ret; };

template<>
struct __bool2type<1> { typedef __true_type _Ret; };

template<>
struct __bool2type<0> { typedef __false_type _Ret; };

//type to bool
template <class __bool_type>
struct __type2bool { enum {_Ret = 1}; };

template<>
struct __type2bool<__true_type> { enum {_Ret = 1}; };

template<>
struct __type2bool<__false_type> { enum {_Ret = 0}; };

//Negation
template <class _BoolType>
struct _Not { typedef __false_type _Ret; };

template<>
struct _Not<__false_type> { typedef __true_type _Ret; };

// logical and of 2 predicated
template <class _P1, class _P2>
struct _Land2 { typedef __false_type _Ret; };

template<>
struct _Land2<__true_type, __true_type> { typedef __true_type _Ret; };

// logical and of 3 predicated
template <class _P1, class _P2, class _P3>
struct _Land3 { typedef __false_type _Ret; };

template<>
struct _Land3<__true_type, __true_type, __true_type> { typedef __true_type _Ret; };

//logical or of 2 predicated
template <class _P1, class _P2>
struct _Lor2 { typedef __true_type _Ret; };

template<>
struct _Lor2<__false_type, __false_type> { typedef __false_type _Ret; };

// logical or of 3 predicated
template <class _P1, class _P2, class _P3>
struct _Lor3 { typedef __true_type _Ret; };

template<>
struct _Lor3<__false_type, __false_type, __false_type> { typedef __false_type _Ret; };

////////////////////////////////////////////////////////////////////////////////
// class template __select
// Selects one of two types based upon a boolean constant
// Invocation: __select<_Cond, T, U>::Result
// where:
// flag is a compile-time boolean constant
// T and U are types
// Result evaluates to T if flag is true, and to U otherwise.
////////////////////////////////////////////////////////////////////////////////
// BEWARE: If the compiler do not support partial template specialization or nested template
//classes the default behavior of the __select is to consider the condition as false and so return
//the second template type!!

template <bool _Cond, class _Tp1, class _Tp2>
struct __select { typedef _Tp1 _Ret; };

template <class _Tp1, class _Tp2>
struct __select<false, _Tp1, _Tp2> { typedef _Tp2 _Ret; };

template <class _Tp1, class _Tp2>
struct _IsSameAux {
  typedef __false_type _RetT;
  enum { _Ret = 0 };
};

template <class _Tp>
struct _UnConstType { typedef _Tp _Type; };

template <class _Tp>
struct _UnVolatileType { typedef _Tp _Type; };

template <class _Tp>
struct _UnCVType {
  typedef typename _UnVolatileType<_Tp>::_Type _UnVType;
  typedef typename _UnConstType<_UnVType>::_Type _Type;
};

template <class _Tp>
struct _IsSameAux<_Tp, _Tp> {
  typedef __true_type _RetT;
  enum { _Ret = 1 };
};

template <class _Tp>
struct _UnConstType<const _Tp> { typedef _Tp _Type; };

template <class _Tp>
struct _UnVolatileType<volatile _Tp> { typedef _Tp _Type; };

template <class _Tp1, class _Tp2>
struct _IsSame {
  typedef typename _UnCVType<_Tp1>::_Type _Type1;
  typedef typename _UnCVType<_Tp2>::_Type _Type2;

  typedef _IsSameAux<_Type1, _Type2> _Aux;
  enum { _Ret = _Aux::_Ret };
  typedef typename _Aux::_RetT _RetT;
};

/*
 * The following struct will tell you if 2 types are the same, the limitations are:
 *  - it compares the types without the const or volatile qualifiers, int and const int
 *    will be considered as same for instance.
 *  - the previous remarks do not apply to pointer types, int* and int const* won't be
 *    considered as comparable. (int * and int *const are).
 */
template <class _Tp1, class _Tp2>
struct _AreSameUnCVTypes {
  enum { _Same = _IsSame<_Tp1, _Tp2>::_Ret };
  typedef typename _IsSame<_Tp1, _Tp2>::_RetT _Ret;
};

template <class _Src, class _Dst>
struct _ConversionHelper {
  static char _Test(bool, _Dst);
  static char* _Test(bool, ...);
  static _Src _MakeSource();
};

template <class _Src, class _Dst>
struct _IsConvertible {
  typedef _ConversionHelper<_Src*, const volatile _Dst*> _H;
  enum { value = (sizeof(char) == sizeof(_H::_Test(false, _H::_MakeSource()))) };
  typedef typename __bool2type<value>::_Ret _Ret;
};

/* This struct is intended to say if a pointer can be convertible to an other
 * taking into account cv qualifications. It shouldn't be instanciated with
 * something else than pointer type as it uses pass by value parameter that
 * results in compilation error when parameter type has a special memory
 * alignment
 */
template <class _Src, class _Dst>
struct _IsCVConvertible {
  typedef _ConversionHelper<_Src, _Dst> _H;
  enum { value = (sizeof(char) == sizeof(_H::_Test(false, _H::_MakeSource()))) };
  typedef typename __bool2type<value>::_Ret _Ret;
};

template <class _Tp>
struct _IsConst { typedef __false_type _Ret; };

template <class _Tp>
struct _IsConst <const _Tp> { typedef __true_type _Ret; };

}

#endif /* _STLP_TYPE_MANIPS_H */
