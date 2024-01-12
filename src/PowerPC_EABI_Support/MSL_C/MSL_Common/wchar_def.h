#ifndef _WCHAR_DEF_H
#define _WCHAR_DEF_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef wchar_t wint_t;

#define WCHAR_MIN 0x0000
#define WCHAR_MAX 0xffff

// #define WEOF

#ifdef __cplusplus
}
#endif

#endif
