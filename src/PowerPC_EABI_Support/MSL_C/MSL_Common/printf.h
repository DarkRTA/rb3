#ifndef MSL_PRINTF_H
#define MSL_PRINTF_H

#include <stdarg.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char *restrict format, ...);
int fprintf(FILE *restrict stream, const char *restrict format, ...);
int sprintf(char *restrict buffer, const char *restrict format, ...);
int snprintf(char *restrict buffer, size_t bufsz, const char *restrict format, ...);

int vprintf(const char *restrict format, va_list vlist);
int vfprintf(FILE *restrict stream, const char *restrict format, va_list vlist);
int vsprintf(char *restrict buffer, const char *restrict format, va_list vlist);
int vsnprintf(char *restrict buffer, size_t bufsz, const char *restrict format, va_list vlist);

#ifdef __cplusplus
}
#endif

#endif
