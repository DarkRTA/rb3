#ifndef _STDINT_H
#define _STDINT_H

#include <limits.h>
#include "MSL_Common/intmax_def.h"

#ifdef __cplusplus
extern "C" {
#endif

/* clang-format off */

typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;

typedef signed char        int_least8_t;
typedef short              int_least16_t;
typedef int                int_least32_t;
typedef long long          int_least64_t;

typedef signed char        int_fast8_t;
typedef int                int_fast16_t;
typedef int                int_fast32_t;
typedef long long          int_fast64_t;

typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

typedef unsigned char      uint_least8_t;
typedef unsigned short     uint_least16_t;
typedef unsigned int       uint_least32_t;
typedef unsigned long long uint_least64_t;

typedef unsigned char      uint_fast8_t;
typedef unsigned int       uint_fast16_t;
typedef unsigned int       uint_fast32_t;
typedef unsigned long long uint_fast64_t;

#define INT8_MIN           CHAR_MIN
#define INT16_MIN          SHRT_MIN
#define INT32_MIN          INT_MIN
#define INT64_MIN          LLONG_MIN

#define INT8_MAX           CHAR_MAX
#define INT16_MAX          SHRT_MAX
#define INT32_MAX          INT_MAX
#define INT64_MAX          LLONG_MAX

#define INT_LEAST8_MIN     INT8_MIN
#define INT_LEAST16_MIN    INT16_MIN
#define INT_LEAST32_MIN    INT32_MIN
#define INT_LEAST64_MIN    INT64_MIN

#define INT_LEAST8_MAX     INT8_MAX
#define INT_LEAST16_MAX    INT16_MAX
#define INT_LEAST32_MAX    INT32_MAX
#define INT_LEAST64_MAX    INT64_MAX

#define INT_FAST8_MIN      INT8_MIN
#define INT_FAST16_MIN     INT32_MIN
#define INT_FAST32_MIN     INT32_MIN
#define INT_FAST64_MIN     INT64_MIN

#define INT_FAST8_MAX      INT8_MAX
#define INT_FAST16_MAX     INT32_MAX
#define INT_FAST32_MAX     INT32_MAX
#define INT_FAST64_MAX     INT64_MAX

#define UINT8_MAX          UCHAR_MAX
#define UINT16_MAX         USHRT_MAX
#define UINT32_MAX         UINT_MAX
#define UINT64_MAX         ULLONG_MAX

#define UINT_LEAST8_MAX    UINT8_MAX
#define UINT_LEAST16_MAX   UINT16_MAX
#define UINT_LEAST32_MAX   UINT32_MAX
#define UINT_LEAST64_MAX   UINT64_MAX

#define UINT_FAST8_MAX     UINT8_MAX
#define UINT_FAST16_MAX    UINT32_MAX
#define UINT_FAST32_MAX    UINT32_MAX
#define UINT_FAST64_MAX    UINT64_MAX

#define INTPTR_MIN         LONG_MIN
#define INTPTR_MAX         LONG_MAX
#define UINTPTR_MAX        ULONG_MAX

#define INTMAX_MIN         INT64_MIN
#define INTMAX_MAX         INT64_MAX
#define UINTMAX_MAX        UINT64_MAX

#define PTRDIFF_MIN        INTPTR_MIN
#define PTRDIFF_MAX        INTPTR_MAX

#define SIZE_MAX           ULONG_MAX

#define SIG_ATOMIC_MIN     INT32_MIN
#define SIG_ATOMIC_MAX     INT32_MAX

#ifndef WCHAR_MIN
#define WCHAR_MIN          0x0000
#endif

#ifndef WCHAR_MAX
#define WCHAR_MAX          0xffff
#endif

#ifndef WINT_MIN
#define WINT_MIN           WCHAR_MIN
#endif

#ifndef WINT_MAX
#define WINT_MAX           WCHAR_MAX
#endif

#define INT8_C(x)          (x)
#define INT16_C(x)         (x)
#define INT32_C(x)         (x)
#define INT64_C(x)         (x ## LL)

#define UINT8_C(x)         (x)
#define UINT16_C(x)        (x)
#define UINT32_C(x)        (x ## U)
#define UINT64_C(x)        (x ## ULL)

#define INTMAX_C(x)        INT64_C(x)
#define UINTMAX_C(x)       UINT64_C(x)

/* clang-format on */

#ifdef __cplusplus
}
#endif

#endif
