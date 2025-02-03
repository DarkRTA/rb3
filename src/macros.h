#ifndef MACROS_H
#define MACROS_H

#include "compiler_macros.h"

// Useful macros

#define STR_(x) #x
#define STR(x) STR_(x)

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MINEQ(x, y) ((x) <= (y) ? (x) : (y))

#define ABS(x) ((x) > 0 ? (x) : -(x))

#define CLAMP(low, high, x) ((x) > (high) ? (high) : ((x) < (low) ? (low) : (x)))

#define ROUND_UP(x, align) (((x) + (align) - 1) & (-(align)))
#define ROUND_UP_PTR(x, align) ((void *)((((u32)(x)) + (align) - 1) & (~((align) - 1))))

#define ROUND_DOWN(x, align) ((x) & (-(align)))
#define ROUND_DOWN_PTR(x, align) ((void *)(((u32)(x)) & (~((align) - 1))))

#define ROTATE_LEFT(x, i) (((x) << (i)) | ((x) >> ((sizeof((x)) * 8) - (i))))
#define ROTATE_RIGHT(x, i) (((x) >> (i)) | ((x) << ((sizeof((x)) * 8) - (i))))

#define VARSIZE_ARRAY 1
#define ARRAY_LENGTH(x) (sizeof((x)) / sizeof((x)[0]))

#define null 0

#define RELEASE(x) (delete x, x = null)
#define RELEASEARRAY(x) (delete[] (ubyte *)x, x = null)

#endif
