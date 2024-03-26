#ifndef _COMPLEX_H
#define _COMPLEX_H

#if __STDC_VERSION__ >= 199901L

#ifdef __cplusplus
extern "C" {
#endif

#define imaginary _Imaginary
#define complex _Complex

/* TODO
#define _Imaginary_I
#define _Complex_I
#define I
*/

#define _COMPLEX_FN(name)                                                            \
    double complex name(double complex z);                                           \
    float complex name##f(float complex z);                                          \
    long double complex name##l(long double complex z)

#define _COMPLEX_FN_RS(name)                                                         \
    double name(double complex z);                                                   \
    float name##f(float complex z);                                                  \
    long double name##l(long double complex z)

#define _COMPLEX_FN_2P(name)                                                         \
    double name(double complex x, double complex y);                                 \
    float name##f(float complex x, float complex y);                                 \
    long double name##l(long double complex x, long double complex y)

_COMPLEX_FN(cabs);
_COMPLEX_FN(carg);
_COMPLEX_FN(creal);
_COMPLEX_FN(cimag);

_COMPLEX_FN_2P(cpow);

_COMPLEX_FN_RS(cacos);
_COMPLEX_FN_RS(cacosh);
_COMPLEX_FN_RS(casin);
_COMPLEX_FN_RS(casinh);
_COMPLEX_FN_RS(catan);
_COMPLEX_FN_RS(catanh);
_COMPLEX_FN_RS(ccos);
_COMPLEX_FN_RS(ccosh);
_COMPLEX_FN_RS(cexp);
_COMPLEX_FN_RS(clog);
_COMPLEX_FN_RS(clog10);
_COMPLEX_FN_RS(conj);
_COMPLEX_FN_RS(cproj);
_COMPLEX_FN_RS(csin);
_COMPLEX_FN_RS(csinh);
_COMPLEX_FN_RS(csqrt);
_COMPLEX_FN_RS(ctan);
_COMPLEX_FN_RS(ctanh);

#undef _COMPLEX_FN
#undef _COMPLEX_FN_RS
#undef _COMPLEX_FN_2P

#ifdef __cplusplus
}
#endif

#endif

#endif
