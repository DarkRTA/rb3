#ifndef MSL_WPRINTF_H
#define MSL_WPRINTF_H

#include "types.h"
#include <stdarg.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

int wprintf(const wchar_t *restrict format, ...);
int fwprintf(FILE *restrict stream, const wchar_t *restrict format, ...);
int swprintf(wchar_t *restrict buffer, size_t bufsz, const wchar_t *restrict format, ...);

int vwprintf(const wchar_t *restrict format, va_list vlist);
int vfwprintf(FILE *restrict stream, const wchar_t *restrict format, va_list vlist);
int vswprintf(
    wchar_t *restrict buffer, size_t bufsz, const wchar_t *restrict format, va_list vlist
);

#ifdef __cplusplus
}
#endif

#endif
