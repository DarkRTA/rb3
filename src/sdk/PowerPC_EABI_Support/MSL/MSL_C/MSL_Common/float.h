#ifndef MSL_COMMON_FLOAT_H
#define MSL_COMMON_FLOAT_H

#include "compiler_macros.h"

#ifdef __cplusplus
extern "C" {
#endif

DECL_SECTION(".data") extern int __float_nan;
DECL_SECTION(".data") extern float __float_huge;
DECL_SECTION(".data") extern double __double_huge;

#define INFINITY (__float_huge)
#define NAN (*(float *)&__float_nan)
#define HUGE_VAL (__double_huge)

#ifdef __cplusplus
}
#endif

#endif
