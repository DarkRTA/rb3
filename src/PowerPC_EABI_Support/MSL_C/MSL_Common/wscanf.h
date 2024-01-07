#ifndef MSL_WSCANF_H
#define MSL_WSCANF_H

#include "types.h"
#include <stdarg.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

int wscanf(const wchar_t *restrict format, ...);
int fwscanf(FILE *restrict stream, const wchar_t *restrict format, ...);
int swscanf(const wchar_t *restrict buffer, const wchar_t *restrict format, ...);

int vwscanf(const wchar_t *restrict format, va_list vlist);
int vfwscanf(FILE *restrict stream, const wchar_t *restrict format, va_list vlist);
int vswscanf(
    const wchar_t *restrict buffer, const wchar_t *restrict format, va_list vlist
);

#ifdef __cplusplus
}
#endif

#endif
