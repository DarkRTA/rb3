#ifndef _WCHAR_DEF_H
#define _WCHAR_DEF_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef wchar_t wint_t;

#ifndef WCHAR_MIN
#define WCHAR_MIN 0x0000
#endif

#ifndef WCHAR_MAX
#define WCHAR_MAX 0xffff
#endif

#ifndef WINT_MIN
#define WINT_MIN WCHAR_MIN
#endif

#ifndef WINT_MAX
#define WINT_MAX WCHAR_MAX
#endif

// #define WEOF

#ifdef __cplusplus
}
#endif

#endif
