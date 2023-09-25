#ifndef RB3_TYPES_H
#define RB3_TYPES_H
#include "macros.h"
#include <stddef.h>

typedef char s8;
typedef short s16;
typedef int s32;
typedef long long s64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;

typedef long l32;
typedef unsigned long ul32;

typedef s32 bool32;

#ifdef NULL
#undef NULL
#endif
#define NULL 0

#ifdef TRUE
#undef TRUE
#endif
#define TRUE 1

#ifdef FALSE
#undef FALSE
#endif
#define FALSE 0

#ifndef __MWERKS__
#define __declspec(x)
#define asm
#endif

#define DECL_WEAK __declspec(weak)

#endif
