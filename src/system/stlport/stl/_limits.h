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

/* NOTE: This may be not portable code. Parts of numeric_limits<> are
 * inherently machine-dependent.  At present this file is suitable
 * for the MIPS, SPARC, Alpha and ia32 architectures.
 */

#ifndef _STLP_INTERNAL_LIMITS
#define _STLP_INTERNAL_LIMITS

#ifndef _STLP_CLIMITS
#  include <climits>
#endif

#ifndef _STLP_CFLOAT
#  include <cfloat>
#endif

#if !defined (_STLP_INTERNAL_CWCHAR)
#  include <stl/_cwchar.h>
#endif

namespace _STLP_STD {

enum float_round_style {
  round_indeterminate       = -1,
  round_toward_zero         =  0,
  round_to_nearest          =  1,
  round_toward_infinity     =  2,
  round_toward_neg_infinity =  3
};

enum float_denorm_style {
  denorm_indeterminate = -1,
  denorm_absent        =  0,
  denorm_present       =  1
};

}

namespace _STLP_PRIV {

// Base class for all specializations of numeric_limits.
template <class __number>
class _Numeric_limits_base {
public:

  static __number (min)() _STLP_NOTHROW { return __number(); }
  static __number (max)() _STLP_NOTHROW { return __number(); }

  static const int
  digits = 0,
  digits10 = 0,
  radix = 0,
  min_exponent = 0,
  min_exponent10 = 0,
  max_exponent = 0,
  max_exponent10 = 0;

  static const float_denorm_style has_denorm =  denorm_absent;
  static const float_round_style round_style = round_toward_zero;

  static const bool
    is_specialized = false,
    is_signed  = false,
    is_integer = false,
    is_exact = false,
    has_infinity = false,
    has_quiet_NaN = false,
    has_signaling_NaN = false,
    has_denorm_loss = false,
    is_iec559 = false,
    is_bounded = false,
    is_modulo = false,
    traps = false,
    tinyness_before = false;

  static __number epsilon() _STLP_NOTHROW     { return __number(); }
  static __number round_error() _STLP_NOTHROW { return __number(); }

  static __number infinity() _STLP_NOTHROW      { return __number(); }
  static __number quiet_NaN() _STLP_NOTHROW     { return __number(); }
  static __number signaling_NaN() _STLP_NOTHROW { return __number(); }
  static __number denorm_min() _STLP_NOTHROW    { return __number(); }
};

// Base class for integers.

template <class _Int, _Int __imin, _Int __imax, int __idigits, bool __ismod>
class _Integer_limits : public _Numeric_limits_base<_Int> {
public:

  static _Int (min) () _STLP_NOTHROW { return (_Int)__imin; }
  static _Int (max) () _STLP_NOTHROW { return (_Int)__imax; }

  static const int
  digits = (__idigits < 0) ?
  ((int)((sizeof(_Int) * (CHAR_BIT))) - ((__imin == 0) ? 0 : 1))
  : (__idigits),
  digits10 = (digits * 301UL) / 1000,
  radix = 2;

  static const bool
  is_specialized = true,
  is_signed = (__imin != 0),
  is_integer = true,
  is_exact = true,
  is_bounded = true,
  is_modulo = __ismod;
};

// Base class for floating-point numbers.
template <class __number,
         int __Digits, int __Digits10,
         int __MinExp, int __MaxExp,
         int __MinExp10, int __MaxExp10,
         bool __IsIEC559,
         float_round_style __RoundStyle>
class _Floating_limits : public _Numeric_limits_base<__number> {
public:

  static const int
  digits = __Digits,
  digits10 = __Digits10,

  radix = (  FLT_RADIX /* 2 */ ),
  min_exponent = __MinExp,
  max_exponent = __MaxExp,
  min_exponent10 = __MinExp10,
  max_exponent10 = __MaxExp10;

  static const float_denorm_style has_denorm = denorm_indeterminate;
  static const float_round_style round_style = __RoundStyle;

  static const bool
  is_specialized = true,
  is_signed = true,

  //IEC 559 specify the floating point representation of
  //infinity, quiet and signaling Not a Number. Not supporting
  //it is consider as not being able to grant those values.
  has_infinity      = __IsIEC559,
  has_quiet_NaN     = __IsIEC559,
  has_signaling_NaN = __IsIEC559,

  has_denorm_loss   =  false,
  is_iec559         =  __IsIEC559,
  is_bounded        =  true,
  traps             =  true,
  tinyness_before   =  false;
};

}

namespace _STLP_STD {

// Class numeric_limits

// The unspecialized class.

template<class _Tp>
class numeric_limits : public _STLP_PRIV::_Numeric_limits_base<_Tp> {};

// Specializations for all built-in integral types.

template<>
class numeric_limits<bool>
  : public _STLP_PRIV::_Integer_limits<bool, false, true, 1, false>
{};

template<>
class numeric_limits<char>
  : public _STLP_PRIV::_Integer_limits<char, CHAR_MIN, CHAR_MAX, -1, true>
{};

template<>
class numeric_limits<signed char>
  : public _STLP_PRIV::_Integer_limits<signed char, SCHAR_MIN, SCHAR_MAX, -1, true>
{};

template<>
class numeric_limits<unsigned char>
  : public _STLP_PRIV::_Integer_limits<unsigned char, 0, UCHAR_MAX, -1, true>
{};

template<>
class numeric_limits<wchar_t>
  : public _STLP_PRIV::_Integer_limits<wchar_t, WCHAR_MIN, WCHAR_MAX, -1, true>
{};

template<>
class numeric_limits<short>
  : public _STLP_PRIV::_Integer_limits<short, SHRT_MIN, SHRT_MAX, -1, true>
{};

template<>
class numeric_limits<unsigned short>
  : public _STLP_PRIV::_Integer_limits<unsigned short, 0, USHRT_MAX, -1, true>
{};

template<>
class numeric_limits<int>
  : public _STLP_PRIV::_Integer_limits<int, INT_MIN, INT_MAX, -1, true>
{};

template<>
class numeric_limits<unsigned int>
  : public _STLP_PRIV::_Integer_limits<unsigned int, 0, UINT_MAX, -1, true>
{};

template<>
class numeric_limits<long>
  : public _STLP_PRIV::_Integer_limits<long, LONG_MIN, LONG_MAX, -1, true>
{};

template<>
class numeric_limits<unsigned long>
  : public _STLP_PRIV::_Integer_limits<unsigned long, 0, ULONG_MAX, -1, true>
{};

template<>
class numeric_limits<long long>
  : public _STLP_PRIV::_Integer_limits<long long, LLONG_MIN, LLONG_MAX, -1, true>
{};

template<>
class numeric_limits<unsigned long long>
  : public _STLP_PRIV::_Integer_limits<unsigned long long, 0, ULLONG_MAX, -1, true>
{};

}

namespace _STLP_PRIV {

// Specializations for all built-in floating-point types.
template <class __dummy>
class _LimG {
public:
  static float get_F_inf();
  static float get_F_qNaN();
  static float get_F_sNaN();
  static double get_D_inf();
  static double get_D_qNaN();
  static double get_D_sNaN();
  static long double get_LD_inf();
  static long double get_LD_qNaN();
  static long double get_LD_sNaN();
};

}

namespace _STLP_STD {

template<>
class numeric_limits<float>
  : public _STLP_PRIV::_Floating_limits<float,
                                        FLT_MANT_DIG,   // Binary digits of precision
                                        FLT_DIG,        // Decimal digits of precision
                                        FLT_MIN_EXP,    // Minimum exponent
                                        FLT_MAX_EXP,    // Maximum exponent
                                        FLT_MIN_10_EXP, // Minimum base 10 exponent
                                        FLT_MAX_10_EXP, // Maximum base 10 exponent
                                        true,           // conforms to iec559
                                        round_to_nearest> {
public:
  static float (min) () _STLP_NOTHROW { return FLT_MIN; }
  static float denorm_min() _STLP_NOTHROW { return FLT_MIN; }
  static float (max) () _STLP_NOTHROW { return FLT_MAX; }
  static float epsilon() _STLP_NOTHROW { return FLT_EPSILON; }
  static float round_error() _STLP_NOTHROW { return 0.5f; } // Units: ulps.
  static  float infinity() _STLP_NOTHROW { return _STLP_PRIV::_LimG<bool>::get_F_inf(); }
  static  float quiet_NaN() _STLP_NOTHROW { return _STLP_PRIV::_LimG<bool>::get_F_qNaN(); }
  static  float signaling_NaN() _STLP_NOTHROW { return _STLP_PRIV::_LimG<bool>::get_F_sNaN(); }
};

template<>
class numeric_limits<double>
  : public _STLP_PRIV::_Floating_limits<double,
                                        DBL_MANT_DIG,   // Binary digits of precision
                                        DBL_DIG,        // Decimal digits of precision
                                        DBL_MIN_EXP,    // Minimum exponent
                                        DBL_MAX_EXP,    // Maximum exponent
                                        DBL_MIN_10_EXP, // Minimum base 10 exponent
                                        DBL_MAX_10_EXP, // Maximum base 10 exponent
                                        true,           // conforms to iec559
                                        round_to_nearest> {
public:
  static double (min)() _STLP_NOTHROW { return DBL_MIN; }
  static double denorm_min() _STLP_NOTHROW { return DBL_MIN; }
  static double (max)() _STLP_NOTHROW { return DBL_MAX; }
  static double epsilon() _STLP_NOTHROW { return DBL_EPSILON; }
  static double round_error() _STLP_NOTHROW { return 0.5; } // Units: ulps.
  static  double infinity() _STLP_NOTHROW { return _STLP_PRIV::_LimG<bool>::get_D_inf(); }
  static  double quiet_NaN() _STLP_NOTHROW { return _STLP_PRIV::_LimG<bool>::get_D_qNaN(); }
  static  double signaling_NaN() _STLP_NOTHROW { return _STLP_PRIV::_LimG<bool>::get_D_sNaN(); }
};

template<>
class numeric_limits<long double>
  : public _STLP_PRIV::_Floating_limits<long double,
                                        LDBL_MANT_DIG,  // Binary digits of precision
                                        LDBL_DIG,       // Decimal digits of precision
                                        LDBL_MIN_EXP,   // Minimum exponent
                                        LDBL_MAX_EXP,   // Maximum exponent
                                        LDBL_MIN_10_EXP,// Minimum base 10 exponent
                                        LDBL_MAX_10_EXP,// Maximum base 10 exponent
                                        false,          // do not conform to iec559
                                        round_to_nearest> {
public:
  static long double (min) () _STLP_NOTHROW { return LDBL_MIN; }
  static long double denorm_min() _STLP_NOTHROW { return LDBL_MIN; }
  static long double (max) () _STLP_NOTHROW { return LDBL_MAX; }
  static long double epsilon() _STLP_NOTHROW { return LDBL_EPSILON; }
  static long double round_error() _STLP_NOTHROW { return 4; } // Units: ulps.
  static long double infinity() _STLP_NOTHROW { return _STLP_PRIV::_LimG<bool>::get_LD_inf(); }
  static long double quiet_NaN() _STLP_NOTHROW { return _STLP_PRIV::_LimG<bool>::get_LD_qNaN(); }
  static long double signaling_NaN() _STLP_NOTHROW { return _STLP_PRIV::_LimG<bool>::get_LD_sNaN(); }
};

// We write special values (Inf and NaN) as bit patterns and
// cast the the appropriate floating-point types.
}

#if !defined (_STLP_LINK_TIME_INSTANTIATION)
#  include <stl/_limits.c>
#endif

#endif

// Local Variables:
// mode:C++
// End:
