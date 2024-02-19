#ifndef _MSL_MATH_API_H
#define _MSL_MATH_API_H


#ifdef __cplusplus
extern "C" {
#endif

#if defined(i386) || defined(i486) || defined(intel) || defined(x86) || defined(i86pc)   \
    || defined(__alpha) || defined(__osf__)
#define __LITTLE_ENDIAN
#endif

#ifdef __LITTLE_ENDIAN
#define __HI(x) *(1 + (int *)&x)
#define __LO(x) *(int *)&x
#define __HIp(x) *(1 + (int *)x)
#define __LOp(x) *(int *)x
#else
#define __HI(x) *(int *)&x
#define __LO(x) *(1 + (int *)&x)
#define __HIp(x) *(int *)x
#define __LOp(x) *(1 + (int *)x)
#endif

typedef float float_t;
typedef double double_t;

#ifdef __cplusplus
}
#endif

#endif
