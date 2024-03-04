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
#ifndef _STLP_INTERNAL_COMPLEX
#define _STLP_INTERNAL_COMPLEX

// This header declares the template class complex, as described in
// in the draft C++ standard.  Single-precision complex numbers
// are complex<float>, double-precision are complex<double>, and
// quad precision are complex<long double>.

// Note that the template class complex is declared within namespace
// std, as called for by the draft C++ standard.

#ifndef _STLP_INTERNAL_CMATH
#  include <stl/_cmath.h>
#endif

namespace _STLP_STD {

template <class _Tp> struct complex;

template<> struct complex<float>;
template<> struct complex<double>;
template<> struct complex<long double>;

template <class _Tp>
struct complex {
  typedef _Tp value_type;
  typedef complex<_Tp> _Self;

  // Constructors, destructor, assignment operator.
  complex() : _M_re(0), _M_im(0) {}
  complex(const value_type& __x)
    : _M_re(__x), _M_im(0) {}
  complex(const value_type& __x, const value_type& __y)
    : _M_re(__x), _M_im(__y) {}
  complex(const _Self& __z)
    : _M_re(__z._M_re), _M_im(__z._M_im) {}

  _Self& operator=(const _Self& __z) {
    _M_re = __z._M_re;
    _M_im = __z._M_im;
    return *this;
  }

  template <class _Tp2>
  explicit complex(const complex<_Tp2>& __z)
    : _M_re(__z._M_re), _M_im(__z._M_im) {}

  template <class _Tp2>
  _Self& operator=(const complex<_Tp2>& __z) {
    _M_re = __z._M_re;
    _M_im = __z._M_im;
    return *this;
  }

  // Element access.
  value_type real() const { return _M_re; }
  value_type imag() const { return _M_im; }

  // Arithmetic op= operations involving one real argument.

  _Self& operator= (const value_type& __x) {
    _M_re = __x;
    _M_im = 0;
    return *this;
  }
  _Self& operator+= (const value_type& __x) {
    _M_re += __x;
    return *this;
  }
  _Self& operator-= (const value_type& __x) {
    _M_re -= __x;
    return *this;
  }
  _Self& operator*= (const value_type& __x) {
    _M_re *= __x;
    _M_im *= __x;
    return *this;
  }
  _Self& operator/= (const value_type& __x) {
    _M_re /= __x;
    _M_im /= __x;
    return *this;
  }

  // Arithmetic op= operations involving two complex arguments.

  static void  _div(const value_type& __z1_r, const value_type& __z1_i,
                               const value_type& __z2_r, const value_type& __z2_i,
                               value_type& __res_r, value_type& __res_i);

  static void _div(const value_type& __z1_r,
                              const value_type& __z2_r, const value_type& __z2_i,
                              value_type& __res_r, value_type& __res_i);

  template <class _Tp2> _Self& operator+= (const complex<_Tp2>& __z) {
    _M_re += __z._M_re;
    _M_im += __z._M_im;
    return *this;
  }

  template <class _Tp2> _Self& operator-= (const complex<_Tp2>& __z) {
    _M_re -= __z._M_re;
    _M_im -= __z._M_im;
    return *this;
  }

  template <class _Tp2> _Self& operator*= (const complex<_Tp2>& __z) {
    value_type __r = _M_re * __z._M_re - _M_im * __z._M_im;
    value_type __i = _M_re * __z._M_im + _M_im * __z._M_re;
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  template <class _Tp2> _Self& operator/= (const complex<_Tp2>& __z) {
    value_type __r;
    value_type __i;
    _div(_M_re, _M_im, __z._M_re, __z._M_im, __r, __i);
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  _Self& operator+= (const _Self& __z) {
    _M_re += __z._M_re;
    _M_im += __z._M_im;
    return *this;
  }

  _Self& operator-= (const _Self& __z) {
    _M_re -= __z._M_re;
    _M_im -= __z._M_im;
    return *this;
  }

  _Self& operator*= (const _Self& __z) {
    value_type __r = _M_re * __z._M_re - _M_im * __z._M_im;
    value_type __i = _M_re * __z._M_im + _M_im * __z._M_re;
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  _Self& operator/= (const _Self& __z) {
    value_type __r;
    value_type __i;
    _div(_M_re, _M_im, __z._M_re, __z._M_im, __r, __i);
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  // Data members.
  value_type _M_re;
  value_type _M_im;
};

// Explicit specializations for float, double, long double.  The only
// reason for these specializations is to enable automatic conversions
// from complex<float> to complex<double>, and complex<double> to
// complex<long double>.

template<>
struct complex<float> {
  typedef float value_type;
  typedef complex<float> _Self;
  // Constructors, destructor, assignment operator.

  complex(value_type __x = 0.0f, value_type __y = 0.0f)
    : _M_re(__x), _M_im(__y) {}

  complex(const complex<float>& __z)    : _M_re(__z._M_re), _M_im(__z._M_im) {}

  inline explicit complex(const complex<double>& __z);
  inline explicit complex(const complex<long double>& __z);

  // Element access.
  value_type real() const { return _M_re; }
  value_type imag() const { return _M_im; }

  // Arithmetic op= operations involving one real argument.

  _Self& operator= (value_type __x) {
    _M_re = __x;
    _M_im = 0.0f;
    return *this;
  }
  _Self& operator+= (value_type __x) {
    _M_re += __x;
    return *this;
  }
  _Self& operator-= (value_type __x) {
    _M_re -= __x;
    return *this;
  }
  _Self& operator*= (value_type __x) {
    _M_re *= __x;
    _M_im *= __x;
    return *this;
  }
  _Self& operator/= (value_type __x) {
    _M_re /= __x;
    _M_im /= __x;
    return *this;
  }

  // Arithmetic op= operations involving two complex arguments.

  static void _div(const float& __z1_r, const float& __z1_i,
                              const float& __z2_r, const float& __z2_i,
                              float& __res_r, float& __res_i);

  static void _div(const float& __z1_r,
                              const float& __z2_r, const float& __z2_i,
                              float& __res_r, float& __res_i);

  template <class _Tp2>
  complex<float>& operator=(const complex<_Tp2>& __z) {
    _M_re = __z._M_re;
    _M_im = __z._M_im;
    return *this;
  }

  template <class _Tp2>
  complex<float>& operator+= (const complex<_Tp2>& __z) {
    _M_re += __z._M_re;
    _M_im += __z._M_im;
    return *this;
  }

  template <class _Tp2>
  complex<float>& operator-= (const complex<_Tp2>& __z) {
    _M_re -= __z._M_re;
    _M_im -= __z._M_im;
    return *this;
  }

  template <class _Tp2>
  complex<float>& operator*= (const complex<_Tp2>& __z) {
    float __r = _M_re * __z._M_re - _M_im * __z._M_im;
    float __i = _M_re * __z._M_im + _M_im * __z._M_re;
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  template <class _Tp2>
  complex<float>& operator/= (const complex<_Tp2>& __z) {
    float __r;
    float __i;
    _div(_M_re, _M_im, __z._M_re, __z._M_im, __r, __i);
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  _Self& operator=(const _Self& __z) {
    _M_re = __z._M_re;
    _M_im = __z._M_im;
    return *this;
  }

  _Self& operator+= (const _Self& __z) {
    _M_re += __z._M_re;
    _M_im += __z._M_im;
    return *this;
  }

  _Self& operator-= (const _Self& __z) {
    _M_re -= __z._M_re;
    _M_im -= __z._M_im;
    return *this;
  }

  _Self& operator*= (const _Self& __z) {
    value_type __r = _M_re * __z._M_re - _M_im * __z._M_im;
    value_type __i = _M_re * __z._M_im + _M_im * __z._M_re;
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  _Self& operator/= (const _Self& __z) {
    value_type __r;
    value_type __i;
    _div(_M_re, _M_im, __z._M_re, __z._M_im, __r, __i);
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  // Data members.
  value_type _M_re;
  value_type _M_im;
};

template<>
struct complex<double> {
  typedef double value_type;
  typedef complex<double> _Self;

  // Constructors, destructor, assignment operator.

  complex(value_type __x = 0.0, value_type __y = 0.0)
    : _M_re(__x), _M_im(__y) {}

  complex(const complex<double>& __z)
    : _M_re(__z._M_re), _M_im(__z._M_im) {}
  inline complex(const complex<float>& __z);
  explicit inline complex(const complex<long double>& __z);

  // Element access.
  value_type real() const { return _M_re; }
  value_type imag() const { return _M_im; }

  // Arithmetic op= operations involving one real argument.

  _Self& operator= (value_type __x) {
    _M_re = __x;
    _M_im = 0.0;
    return *this;
  }
  _Self& operator+= (value_type __x) {
    _M_re += __x;
    return *this;
  }
  _Self& operator-= (value_type __x) {
    _M_re -= __x;
    return *this;
  }
  _Self& operator*= (value_type __x) {
    _M_re *= __x;
    _M_im *= __x;
    return *this;
  }
  _Self& operator/= (value_type __x) {
    _M_re /= __x;
    _M_im /= __x;
    return *this;
  }

  // Arithmetic op= operations involving two complex arguments.

  static void _div(const double& __z1_r, const double& __z1_i,
                              const double& __z2_r, const double& __z2_i,
                              double& __res_r, double& __res_i);
  static void _div(const double& __z1_r,
                              const double& __z2_r, const double& __z2_i,
                              double& __res_r, double& __res_i);

  template <class _Tp2>
  complex<double>& operator=(const complex<_Tp2>& __z) {
    _M_re = __z._M_re;
    _M_im = __z._M_im;
    return *this;
  }

  template <class _Tp2>
  complex<double>& operator+= (const complex<_Tp2>& __z) {
    _M_re += __z._M_re;
    _M_im += __z._M_im;
    return *this;
  }

  template <class _Tp2>
  complex<double>& operator-= (const complex<_Tp2>& __z) {
    _M_re -= __z._M_re;
    _M_im -= __z._M_im;
    return *this;
  }

  template <class _Tp2>
  complex<double>& operator*= (const complex<_Tp2>& __z) {
    double __r = _M_re * __z._M_re - _M_im * __z._M_im;
    double __i = _M_re * __z._M_im + _M_im * __z._M_re;
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  template <class _Tp2>
  complex<double>& operator/= (const complex<_Tp2>& __z) {
    double __r;
    double __i;
    _div(_M_re, _M_im, __z._M_re, __z._M_im, __r, __i);
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  _Self& operator=(const _Self& __z) {
    _M_re = __z._M_re;
    _M_im = __z._M_im;
    return *this;
  }

  _Self& operator+= (const _Self& __z) {
    _M_re += __z._M_re;
    _M_im += __z._M_im;
    return *this;
  }

  _Self& operator-= (const _Self& __z) {
    _M_re -= __z._M_re;
    _M_im -= __z._M_im;
    return *this;
  }

  _Self& operator*= (const _Self& __z) {
    value_type __r = _M_re * __z._M_re - _M_im * __z._M_im;
    value_type __i = _M_re * __z._M_im + _M_im * __z._M_re;
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  _Self& operator/= (const _Self& __z) {
    value_type __r;
    value_type __i;
    _div(_M_re, _M_im, __z._M_re, __z._M_im, __r, __i);
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  // Data members.
  value_type _M_re;
  value_type _M_im;
};

template<>
struct complex<long double> {
  typedef long double value_type;
  typedef complex<long double> _Self;

  // Constructors, destructor, assignment operator.
  complex(value_type __x = 0.0l, value_type __y = 0.0l)
    : _M_re(__x), _M_im(__y) {}

  complex(const complex<long double>& __z)
    : _M_re(__z._M_re), _M_im(__z._M_im) {}
  inline complex(const complex<float>& __z);
  inline complex(const complex<double>& __z);

  // Element access.
  value_type real() const { return _M_re; }
  value_type imag() const { return _M_im; }

  // Arithmetic op= operations involving one real argument.

  _Self& operator= (value_type __x) {
    _M_re = __x;
    _M_im = 0.0l;
    return *this;
  }
  _Self& operator+= (value_type __x) {
    _M_re += __x;
    return *this;
  }
  _Self& operator-= (value_type __x) {
    _M_re -= __x;
    return *this;
  }
  _Self& operator*= (value_type __x) {
    _M_re *= __x;
    _M_im *= __x;
    return *this;
  }
  _Self& operator/= (value_type __x) {
    _M_re /= __x;
    _M_im /= __x;
    return *this;
  }

  // Arithmetic op= operations involving two complex arguments.

  static void _div(const long double& __z1_r, const long double& __z1_i,
                              const long double& __z2_r, const long double& __z2_i,
                              long double& __res_r, long double& __res_i);

  static void _div(const long double& __z1_r,
                              const long double& __z2_r, const long double& __z2_i,
                              long double& __res_r, long double& __res_i);

  template <class _Tp2>
  complex<long double>& operator=(const complex<_Tp2>& __z) {
    _M_re = __z._M_re;
    _M_im = __z._M_im;
    return *this;
  }

  template <class _Tp2>
  complex<long double>& operator+= (const complex<_Tp2>& __z) {
    _M_re += __z._M_re;
    _M_im += __z._M_im;
    return *this;
  }

  template <class _Tp2>
  complex<long double>& operator-= (const complex<_Tp2>& __z) {
    _M_re -= __z._M_re;
    _M_im -= __z._M_im;
    return *this;
  }

  template <class _Tp2>
  complex<long double>& operator*= (const complex<_Tp2>& __z) {
    long double __r = _M_re * __z._M_re - _M_im * __z._M_im;
    long double __i = _M_re * __z._M_im + _M_im * __z._M_re;
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  template <class _Tp2>
  complex<long double>& operator/= (const complex<_Tp2>& __z) {
    long double __r;
    long double __i;
    _div(_M_re, _M_im, __z._M_re, __z._M_im, __r, __i);
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  _Self& operator=(const _Self& __z) {
    _M_re = __z._M_re;
    _M_im = __z._M_im;
    return *this;
  }

  _Self& operator+= (const _Self& __z) {
    _M_re += __z._M_re;
    _M_im += __z._M_im;
    return *this;
  }

  _Self& operator-= (const _Self& __z) {
    _M_re -= __z._M_re;
    _M_im -= __z._M_im;
    return *this;
  }

  _Self& operator*= (const _Self& __z) {
    value_type __r = _M_re * __z._M_re - _M_im * __z._M_im;
    value_type __i = _M_re * __z._M_im + _M_im * __z._M_re;
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  _Self& operator/= (const _Self& __z) {
    value_type __r;
    value_type __i;
    _div(_M_re, _M_im, __z._M_re, __z._M_im, __r, __i);
    _M_re = __r;
    _M_im = __i;
    return *this;
  }

  // Data members.
  value_type _M_re;
  value_type _M_im;
};

// Converting constructors from one of these three specialized types
// to another.

inline complex<float>::complex(const complex<double>& __z)
  : _M_re((float)__z._M_re), _M_im((float)__z._M_im) {}
inline complex<double>::complex(const complex<float>& __z)
  : _M_re(__z._M_re), _M_im(__z._M_im) {}
inline complex<float>::complex(const complex<long double>& __z)
  : _M_re((float)__z._M_re), _M_im((float)__z._M_im) {}
inline complex<double>::complex(const complex<long double>& __z)
  : _M_re((double)__z._M_re), _M_im((double)__z._M_im) {}
inline complex<long double>::complex(const complex<float>& __z)
  : _M_re(__z._M_re), _M_im(__z._M_im) {}
inline complex<long double>::complex(const complex<double>& __z)
  : _M_re(__z._M_re), _M_im(__z._M_im) {}

// Unary non-member arithmetic operators.

template <class _Tp>
inline complex<_Tp> operator+(const complex<_Tp>& __z)
{ return __z; }

template <class _Tp>
inline complex<_Tp>  operator-(const complex<_Tp>& __z)
{ return complex<_Tp>(-__z._M_re, -__z._M_im); }

// Non-member arithmetic operations involving one real argument.

template <class _Tp>
inline complex<_Tp> operator+(const _Tp& __x, const complex<_Tp>& __z)
{ return complex<_Tp>(__x + __z._M_re, __z._M_im); }

template <class _Tp>
inline complex<_Tp> operator+(const complex<_Tp>& __z, const _Tp& __x)
{ return complex<_Tp>(__z._M_re + __x, __z._M_im); }

template <class _Tp>
inline complex<_Tp> operator-(const _Tp& __x, const complex<_Tp>& __z)
{ return complex<_Tp>(__x - __z._M_re, -__z._M_im); }

template <class _Tp>
inline complex<_Tp> operator-(const complex<_Tp>& __z, const _Tp& __x)
{ return complex<_Tp>(__z._M_re - __x, __z._M_im); }

template <class _Tp>
inline complex<_Tp> operator*(const _Tp& __x, const complex<_Tp>& __z)
{ return complex<_Tp>(__x * __z._M_re, __x * __z._M_im); }

template <class _Tp>
inline complex<_Tp> operator*(const complex<_Tp>& __z, const _Tp& __x)
{ return complex<_Tp>(__z._M_re * __x, __z._M_im * __x); }

template <class _Tp>
inline complex<_Tp> operator/(const _Tp& __x, const complex<_Tp>& __z) {
  complex<_Tp> __result;
  complex<_Tp>::_div(__x,
                     __z._M_re, __z._M_im,
                     __result._M_re, __result._M_im);
  return __result;
}

template <class _Tp>
inline complex<_Tp> operator/(const complex<_Tp>& __z, const _Tp& __x)
{ return complex<_Tp>(__z._M_re / __x, __z._M_im / __x); }

// Non-member arithmetic operations involving two complex arguments

template <class _Tp>
inline complex<_Tp>
operator+(const complex<_Tp>& __z1, const complex<_Tp>& __z2)
{ return complex<_Tp>(__z1._M_re + __z2._M_re, __z1._M_im + __z2._M_im); }

template <class _Tp>
inline complex<_Tp>
operator-(const complex<_Tp>& __z1, const complex<_Tp>& __z2)
{ return complex<_Tp>(__z1._M_re - __z2._M_re, __z1._M_im - __z2._M_im); }

template <class _Tp>
inline complex<_Tp>
operator*(const complex<_Tp>& __z1, const complex<_Tp>& __z2) {
  return complex<_Tp>(__z1._M_re * __z2._M_re - __z1._M_im * __z2._M_im,
                      __z1._M_re * __z2._M_im + __z1._M_im * __z2._M_re);
}

template <class _Tp>
inline complex<_Tp>
operator/(const complex<_Tp>& __z1, const complex<_Tp>& __z2) {
  complex<_Tp> __result;
  complex<_Tp>::_div(__z1._M_re, __z1._M_im,
                     __z2._M_re, __z2._M_im,
                     __result._M_re, __result._M_im);
  return __result;
}

// Comparison operators.

template <class _Tp>
inline bool operator==(const complex<_Tp>& __z1, const complex<_Tp>& __z2)
{ return __z1._M_re == __z2._M_re && __z1._M_im == __z2._M_im; }

template <class _Tp>
inline bool operator==(const complex<_Tp>& __z, const _Tp& __x)
{ return __z._M_re == __x && __z._M_im == 0; }

template <class _Tp>
inline bool operator==(const _Tp& __x, const complex<_Tp>& __z)
{ return __x == __z._M_re && 0 == __z._M_im; }

template <class _Tp>
inline bool operator!=(const complex<_Tp>& __z1, const complex<_Tp>& __z2)
{ return __z1._M_re != __z2._M_re || __z1._M_im != __z2._M_im; }

template <class _Tp>
inline bool operator!=(const complex<_Tp>& __z, const _Tp& __x)
{ return __z._M_re != __x || __z._M_im != 0; }

template <class _Tp>
inline bool operator!=(const _Tp& __x, const complex<_Tp>& __z)
{ return __x != __z._M_re || 0 != __z._M_im; }

// Other basic arithmetic operations
template <class _Tp>
inline _Tp real(const complex<_Tp>& __z)
{ return __z._M_re; }

template <class _Tp>
inline _Tp imag(const complex<_Tp>& __z)
{ return __z._M_im; }

template <class _Tp>
_Tp abs(const complex<_Tp>& __z);

template <class _Tp>
_Tp arg(const complex<_Tp>& __z);

template <class _Tp>
inline _Tp norm(const complex<_Tp>& __z)
{ return __z._M_re * __z._M_re + __z._M_im * __z._M_im; }

template <class _Tp>
inline complex<_Tp> conj(const complex<_Tp>& __z)
{ return complex<_Tp>(__z._M_re, -__z._M_im); }

template <class _Tp>
complex<_Tp> polar(const _Tp& __rho)
{ return complex<_Tp>(__rho, 0); }

template <class _Tp>
complex<_Tp> polar(const _Tp& __rho, const _Tp& __phi);

template<>
float abs(const complex<float>&);
template<>
double abs(const complex<double>&);
template<>
float arg(const complex<float>&);
template<>
double arg(const complex<double>&);
template<>
complex<float> polar(const float& __rho, const float& __phi);
template<>
complex<double> polar(const double& __rho, const double& __phi);

template <class _Tp>
_Tp abs(const complex<_Tp>& __z)
{ return _Tp(abs(complex<double>(double(__z.real()), double(__z.imag())))); }

template <class _Tp>
_Tp arg(const complex<_Tp>& __z)
{ return _Tp(arg(complex<double>(double(__z.real()), double(__z.imag())))); }

template <class _Tp>
complex<_Tp> polar(const _Tp& __rho, const _Tp& __phi) {
  complex<double> __tmp = polar(double(__rho), double(__phi));
  return complex<_Tp>(_Tp(__tmp.real()), _Tp(__tmp.imag()));
}

template<>
long double arg(const complex<long double>&);
template<>
long double abs(const complex<long double>&);
template<>
complex<long double> polar(const long double&, const long double&);

#if !defined (_STLP_USE_NO_IOSTREAMS)

}

#  include <iosfwd>

namespace _STLP_STD {

// Complex output, in the form (re,im).  We use a two-step process
// involving stringstream so that we get the padding right.
template <class _Tp, class _CharT, class _Traits>
basic_ostream<_CharT, _Traits>& 
operator<<(basic_ostream<_CharT, _Traits>& __os, const complex<_Tp>& __z);

template <class _Tp, class _CharT, class _Traits>
basic_istream<_CharT, _Traits>&
operator>>(basic_istream<_CharT, _Traits>& __is, complex<_Tp>& __z);

// Specializations for narrow characters; lets us avoid widen.

basic_istream<char, char_traits<char> >&
operator>>(basic_istream<char, char_traits<char> >& __is, complex<float>& __z);

basic_istream<char, char_traits<char> >&
operator>>(basic_istream<char, char_traits<char> >& __is, complex<double>& __z);

basic_ostream<char, char_traits<char> >&
operator<<(basic_ostream<char, char_traits<char> >& __is, const complex<float>& __z);

basic_ostream<char, char_traits<char> >&
operator<<(basic_ostream<char, char_traits<char> >& __is, const complex<double>& __z);

basic_istream<char, char_traits<char> >&
operator>>(basic_istream<char, char_traits<char> >& __is, complex<long double>& __z);

basic_ostream<char, char_traits<char> >&
operator<<(basic_ostream<char, char_traits<char> >& __is, const complex<long double>& __z);

#endif


// Transcendental functions.  These are defined only for float,
//  double, and long double.  (Sqrt isn't transcendental, of course,
//  but it's included in this section anyway.)

complex<float> sqrt(const complex<float>&);

complex<float> exp(const complex<float>&);
complex<float>  log(const complex<float>&);
complex<float> log10(const complex<float>&);

complex<float> pow(const complex<float>&, int);
complex<float> pow(const complex<float>&, const float&);
complex<float> pow(const float&, const complex<float>&);
complex<float> pow(const complex<float>&, const complex<float>&);

complex<float> sin(const complex<float>&);
complex<float> cos(const complex<float>&);
complex<float> tan(const complex<float>&);

complex<float> sinh(const complex<float>&);
complex<float> cosh(const complex<float>&);
complex<float> tanh(const complex<float>&);

complex<double> sqrt(const complex<double>&);

complex<double> exp(const complex<double>&);
complex<double> log(const complex<double>&);
complex<double> log10(const complex<double>&);

complex<double> pow(const complex<double>&, int);
complex<double> pow(const complex<double>&, const double&);
complex<double> pow(const double&, const complex<double>&);
complex<double> pow(const complex<double>&, const complex<double>&);

complex<double> sin(const complex<double>&);
complex<double> cos(const complex<double>&);
complex<double> tan(const complex<double>&);

complex<double> sinh(const complex<double>&);
complex<double> cosh(const complex<double>&);
complex<double> tanh(const complex<double>&);

complex<long double> sqrt(const complex<long double>&);
complex<long double> exp(const complex<long double>&);
complex<long double> log(const complex<long double>&);
complex<long double> log10(const complex<long double>&);

complex<long double> pow(const complex<long double>&, int);
complex<long double> pow(const complex<long double>&, const long double&);
complex<long double> pow(const long double&, const complex<long double>&);
complex<long double> pow(const complex<long double>&,
                                                   const complex<long double>&);

complex<long double> sin(const complex<long double>&);
complex<long double> cos(const complex<long double>&);
complex<long double> tan(const complex<long double>&);

complex<long double> sinh(const complex<long double>&);
complex<long double> cosh(const complex<long double>&);
complex<long double> tanh(const complex<long double>&);

}

#ifndef _STLP_LINK_TIME_INSTANTIATION
#  include <stl/_complex.c>
#endif

#endif

// Local Variables:
// mode:C++
// End:
