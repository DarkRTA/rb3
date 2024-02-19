#ifndef MSL_WSCANF_H
#define MSL_WSCANF_H

#include <stdarg.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

int wscanf(const wchar_t *RESTRICT format, ...);
int fwscanf(FILE *RESTRICT stream, const wchar_t *RESTRICT format, ...);
int swscanf(const wchar_t *RESTRICT buffer, const wchar_t *RESTRICT format, ...);

int vwscanf(const wchar_t *RESTRICT format, va_list vlist);
int vfwscanf(FILE *RESTRICT stream, const wchar_t *RESTRICT format, va_list vlist);
int vswscanf(
    const wchar_t *RESTRICT buffer, const wchar_t *RESTRICT format, va_list vlist
);

#ifdef __cplusplus
}
#endif

#endif
