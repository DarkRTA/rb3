#ifndef MSL_WPRINTF_H
#define MSL_WPRINTF_H

#include <stdarg.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

int wprintf(const wchar_t *RESTRICT format, ...);
int fwprintf(FILE *RESTRICT stream, const wchar_t *RESTRICT format, ...);
int swprintf(wchar_t *RESTRICT buffer, size_t bufsz, const wchar_t *RESTRICT format, ...);

int vwprintf(const wchar_t *RESTRICT format, va_list vlist);
int vfwprintf(FILE *RESTRICT stream, const wchar_t *RESTRICT format, va_list vlist);
int vswprintf(
    wchar_t *RESTRICT buffer, size_t bufsz, const wchar_t *RESTRICT format, va_list vlist
);

#ifdef __cplusplus
}
#endif

#endif
