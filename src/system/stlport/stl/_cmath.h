/*
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

#ifndef _STLP_INTERNAL_CMATH
#define _STLP_INTERNAL_CMATH

#if defined (_STLP_USE_NEW_C_HEADERS)
#  if defined (_STLP_HAS_NO_NAMESPACES) && !defined (exception)
#    define exception __math_exception
#  endif
#  include _STLP_NATIVE_CPP_C_HEADER(cmath)
#  if defined (_STLP_HAS_NO_NAMESPACES)
#    undef exception
#  endif
#else
#  include <math.h>
#endif

#define _STLP_CMATH_FUNC_NAMESPACE

#define _STLP_MATH_INLINE(float_type, func, cfunc) \
     inline float_type func (float_type x) { return _STLP_CMATH_FUNC_NAMESPACE::cfunc(x); }
#define _STLP_MATH_INLINE2(float_type, type, func, cfunc) \
     inline float_type func (float_type x, type y) { return _STLP_CMATH_FUNC_NAMESPACE::cfunc(x, y); }
#define _STLP_MATH_INLINE_D(float_type, func, cfunc)
#define _STLP_MATH_INLINE2_D(float_type, type, func, cfunc)

/** macros to define math functions
These macros (having an X somewhere in the name) forward to the C library's
double functions but cast the arguments and return values to the given type. */

#define _STLP_MATH_INLINEX(__type,func,cfunc) \
  inline __type func (__type x) \
  { return __STATIC_CAST(__type, _STLP_CMATH_FUNC_NAMESPACE::cfunc((double)x)); }
#define _STLP_MATH_INLINE2X(__type1,__type2,func,cfunc) \
  inline __type1 func (__type1 x, __type2 y) \
  { return __STATIC_CAST(__type1, _STLP_CMATH_FUNC_NAMESPACE::cfunc((double)x, y)); }
#define _STLP_MATH_INLINE2PX(__type,func,cfunc) \
  inline __type func (__type x, __type *y) { \
    double tmp1, tmp2; \
    tmp1 = _STLP_CMATH_FUNC_NAMESPACE::cfunc(__STATIC_CAST(double, x), &tmp2); \
    *y = __STATIC_CAST(__type, tmp2); \
    return __STATIC_CAST(__type, tmp1); \
  }
#define _STLP_MATH_INLINE2XX(__type,func,cfunc) \
  inline __type func (__type x, __type y) \
  { return __STATIC_CAST(__type, _STLP_CMATH_FUNC_NAMESPACE::cfunc((double)x, (double)y)); }


/** rough characterization of compiler and native C library
For the compiler, it can either support long double or not. If it doesn't, the
macro _STLP_NO_LONG_DOUBLE is not defined and we don't define any long double
overloads.
For the native C library the question is whether it has variants with an 'f'
suffix (for float as opposed to double) or an 'l' suffix (for long double). If
the float variants are missing, _STLP_NO_VENDOR_MATH_F is defined, when the
long double variants are missing, _STLP_NO_VENDOR_MATH_L is defined. Of course
the latter doesn't make sense anyway when the compiler already has no long
double support.

Those two traits determine a) which overloads get defined and b) how they are
defined.

Meaning of suffixes:
""   : function returning and taking a float_type
"2"  : function returning a float_type and taking to float_types
"2P" : function returning a float_type and taking a float_type and a float_type*
"2PI": function returning a float_type and taking a float_type and an int*
"2I" : function returning a float_type and taking a float_Type and an int
*/

#if !defined (_STLP_NO_LONG_DOUBLE) && !defined (_STLP_NO_VENDOR_MATH_L) && !defined (_STLP_NO_VENDOR_MATH_F)
   // long double support and both e.g. sinl(long double) and sinf(float)
   // This is the default for a correct and complete native library.
#  define _STLP_DEF_MATH_INLINE(func,cf) \
  _STLP_MATH_INLINE(float,func,cf##f) \
  _STLP_MATH_INLINE_D(double,func,cf) \
  _STLP_MATH_INLINE(long double,func,cf##l)
#  define _STLP_DEF_MATH_INLINE2(func,cf) \
  _STLP_MATH_INLINE2(float,float,func,cf##f) \
  _STLP_MATH_INLINE2_D(double,double,func,cf) \
  _STLP_MATH_INLINE2(long double,long double,func,cf##l)
#  define _STLP_DEF_MATH_INLINE2P(func,cf) \
  _STLP_MATH_INLINE2(float,float *,func,cf##f) \
  _STLP_MATH_INLINE2_D(double,double *,func,cf) \
  _STLP_MATH_INLINE2(long double,long double *,func,cf##l)
#  define _STLP_DEF_MATH_INLINE2PI(func,cf) \
  _STLP_MATH_INLINE2(float,int *,func,cf##f) \
  _STLP_MATH_INLINE2_D(double,int *,func,cf) \
  _STLP_MATH_INLINE2(long double,int *,func,cf##l)
#  define _STLP_DEF_MATH_INLINE2I(func,cf) \
  _STLP_MATH_INLINE2(float,int,func,cf##f) \
  _STLP_MATH_INLINE2_D(double,int,func,cf) \
  _STLP_MATH_INLINE2(long double,int,func,cf##l)
#else
#  if !defined (_STLP_NO_LONG_DOUBLE)
#    if !defined (_STLP_NO_VENDOR_MATH_F)
       // long double support and e.g. sinf(float) but not e.g. sinl(long double)
#      define _STLP_DEF_MATH_INLINE(func,cf) \
      _STLP_MATH_INLINE(float,func,cf##f) \
      _STLP_MATH_INLINEX(long double,func,cf)
#      define _STLP_DEF_MATH_INLINE2(func,cf) \
      _STLP_MATH_INLINE2(float,float,func,cf##f) \
      _STLP_MATH_INLINE2XX(long double,func,cf)
#      define _STLP_DEF_MATH_INLINE2P(func,cf) \
      _STLP_MATH_INLINE2(float,float *,func,cf##f) \
      _STLP_MATH_INLINE2PX(long double,func,cf)
#      define _STLP_DEF_MATH_INLINE2PI(func,cf) \
      _STLP_MATH_INLINE2(float,int *,func,cf##f) \
      _STLP_MATH_INLINE2X(long double,int *,func,cf)
#      define _STLP_DEF_MATH_INLINE2I(func,cf) \
      _STLP_MATH_INLINE2(float,int,func,cf##f) \
      _STLP_MATH_INLINE2X(long double,int,func,cf)
#    elif !defined (_STLP_NO_VENDOR_MATH_L)
       // long double support and e.g. sinl(long double) but not e.g. sinf(float)
#      define _STLP_DEF_MATH_INLINE(func,cf) \
      _STLP_MATH_INLINEX(float,func,cf) \
      _STLP_MATH_INLINE(long double,func,cf##l)
#      define _STLP_DEF_MATH_INLINE2(func,cf) \
      _STLP_MATH_INLINE2XX(float,func,cf) \
      _STLP_MATH_INLINE2(long double,long double,func,cf##l)
#      define _STLP_DEF_MATH_INLINE2P(func,cf) \
      _STLP_MATH_INLINE2PX(float,func,cf) \
      _STLP_MATH_INLINE2(long double,long double *,func,cf##l)
#      define _STLP_DEF_MATH_INLINE2PI(func,cf) \
      _STLP_MATH_INLINE2X(float,int *,func,cf) \
      _STLP_MATH_INLINE2(long double,int *,func,cf##l)
#      define _STLP_DEF_MATH_INLINE2I(func,cf) \
      _STLP_MATH_INLINE2X(float,int,func,cf) \
      _STLP_MATH_INLINE2(long double,int,func,cf##l)
#    else
#      define _STLP_DEF_MATH_INLINE(func,cf) \
      _STLP_MATH_INLINEX(float,func,cf) \
      _STLP_MATH_INLINEX(long double,func,cf)
#      define _STLP_DEF_MATH_INLINE2(func,cf) \
      _STLP_MATH_INLINE2XX(float,func,cf) \
      _STLP_MATH_INLINE2XX(long double,func,cf)
#      define _STLP_DEF_MATH_INLINE2P(func,cf) \
      _STLP_MATH_INLINE2PX(float,func,cf) \
      _STLP_MATH_INLINE2PX(long double,func,cf)
#      define _STLP_DEF_MATH_INLINE2PI(func,cf) \
      _STLP_MATH_INLINE2X(float,int *,func,cf) \
      _STLP_MATH_INLINE2X(long double,int *,func,cf)
#      define _STLP_DEF_MATH_INLINE2I(func,cf) \
      _STLP_MATH_INLINE2X(float,int,func,cf) \
      _STLP_MATH_INLINE2X(long double,int,func,cf)
#    endif
#  else
#    if !defined (_STLP_NO_VENDOR_MATH_F)
#      define _STLP_DEF_MATH_INLINE(func,cf) \
      _STLP_MATH_INLINE(float,func,cf##f)
#      define _STLP_DEF_MATH_INLINE2(func,cf) \
      _STLP_MATH_INLINE2(float,float,func,cf##f)
#      define _STLP_DEF_MATH_INLINE2P(func,cf) \
      _STLP_MATH_INLINE2(float,float *,func,cf##f)
#      define _STLP_DEF_MATH_INLINE2PI(func,cf) \
      _STLP_MATH_INLINE2(float,int *,func,cf##f)
#      define _STLP_DEF_MATH_INLINE2I(func,cf) \
      _STLP_MATH_INLINE2(float,int,func,cf##f)
#    else // _STLP_NO_VENDOR_MATH_F
       // neither long double support nor e.g. sinf(float) functions
#      define _STLP_DEF_MATH_INLINE(func,cf) \
      _STLP_MATH_INLINEX(float,func,cf)
#      define _STLP_DEF_MATH_INLINE2(func,cf) \
      _STLP_MATH_INLINE2XX(float,func,cf)
#      define _STLP_DEF_MATH_INLINE2P(func,cf) \
      _STLP_MATH_INLINE2PX(float,func,cf)
#      define _STLP_DEF_MATH_INLINE2PI(func,cf) \
      _STLP_MATH_INLINE2X(float,int *,func,cf)
#      define _STLP_DEF_MATH_INLINE2I(func,cf) \
      _STLP_MATH_INLINE2X(float,int,func,cf)
#    endif // _STLP_NO_VENDOR_MATH_F
#  endif
#endif

inline double abs(double __x) { return ::fabs(__x); }

_STLP_DEF_MATH_INLINE(abs, fabs)
_STLP_DEF_MATH_INLINE(acos, acos)
_STLP_DEF_MATH_INLINE(asin, asin)
_STLP_DEF_MATH_INLINE(atan, atan)
_STLP_DEF_MATH_INLINE2(atan2, atan2)
_STLP_DEF_MATH_INLINE(ceil, ceil)
_STLP_DEF_MATH_INLINE(cos, cos)
_STLP_DEF_MATH_INLINE(cosh, cosh)
_STLP_DEF_MATH_INLINE(exp, exp)
_STLP_DEF_MATH_INLINE(fabs, fabs)
_STLP_DEF_MATH_INLINE(floor, floor)
_STLP_DEF_MATH_INLINE2(fmod, fmod)
_STLP_DEF_MATH_INLINE2PI(frexp, frexp)
_STLP_DEF_MATH_INLINE2I(ldexp, ldexp)
_STLP_DEF_MATH_INLINE(log, log)
_STLP_DEF_MATH_INLINE(log10, log10)
_STLP_DEF_MATH_INLINE2P(modf, modf)
_STLP_DEF_MATH_INLINE(sin, sin)
_STLP_DEF_MATH_INLINE(sinh, sinh)
_STLP_DEF_MATH_INLINE(sqrt, sqrt)
_STLP_DEF_MATH_INLINE(tan, tan)
_STLP_DEF_MATH_INLINE(tanh, tanh)
_STLP_DEF_MATH_INLINE2(pow, pow)

#    ifndef _STLP_NO_VENDOR_MATH_F
inline float pow(float __x, int __y) { return _STLP_CMATH_FUNC_NAMESPACE::powf(__x, __STATIC_CAST(float,__y)); }
#    else
inline float pow(float __x, int __y) { return __STATIC_CAST(float, _STLP_CMATH_FUNC_NAMESPACE::pow(__x, __STATIC_CAST(float,__y))); }
#    endif
inline double pow(double __x, int __y) { return _STLP_CMATH_FUNC_NAMESPACE::pow(__x, __STATIC_CAST(double,__y)); }
#    if !defined (_STLP_NO_LONG_DOUBLE)
#      if !defined(_STLP_NO_VENDOR_MATH_L)
inline long double pow(long double __x, int __y) { return _STLP_CMATH_FUNC_NAMESPACE::powl(__x, __STATIC_CAST(long double,__y)); }
#      else
inline long double pow(long double __x, int __y) { return __STATIC_CAST(long double, _STLP_CMATH_FUNC_NAMESPACE::pow(__x, __STATIC_CAST(long double,__y))); }
#      endif
#    endif
#endif

#if defined (_STLP_RESTORE_FUNCTION_INTRINSIC)
//restoration of the default intrinsic status of those functions:
#  pragma intrinsic (abs, acos, asin, atan, atan2, cos, cosh, exp, fabs, fmod, log, log10, sin, sinh, sqrt, tan, tanh)
#  pragma warning(pop)
#  undef _STLP_RESTORE_FUNCTION_INTRINSIC
#endif

/* C++ Standard is unclear about several call to 'using ::func' if new overloads
 * of ::func appears between 2 successive 'using' calls. To avoid this potential
 * problem we provide all abs overload before the 'using' call.
 * Beware: This header inclusion has to be after all abs overload of this file.
 *         The first 'using ::abs' call is going to be in the other header.
 */
#ifndef _STLP_INTERNAL_CSTDLIB
#  include <stl/_cstdlib.h>
#endif

#if defined (_STLP_IMPORT_VENDOR_CSTD) && !defined (_STLP_NO_CSTD_FUNCTION_IMPORTS)
_STLP_BEGIN_NAMESPACE
using ::abs;
using ::acos;
using ::asin;
using ::atan;
using ::atan2;
using ::ceil;
using ::cos;
using ::cosh;
using ::exp;
using ::fabs;
using ::floor;
using ::fmod;
using ::frexp;
using ::hypot;
using ::ldexp;
using ::log;
using ::log10;
using ::modf;
using ::pow;
using ::sin;
using ::sinh;
using ::sqrt;
using ::tan;
using ::tanh;
_STLP_END_NAMESPACE

#endif /* _STLP_INTERNAL_CMATH */

// Local Variables:
// mode:C++
// End:
