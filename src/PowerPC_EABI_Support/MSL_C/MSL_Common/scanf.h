#ifndef MSL_SCANF_H
#define MSL_SCANF_H

#include <stdarg.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

int scanf(const char *restrict format, ...);
int fscanf(FILE *restrict stream, const char *restrict format, ...);
int sscanf(const char *restrict buffer, const char *restrict format, ...);

int vscanf(const char *restrict format, va_list vlist);
int vfscanf(FILE *restrict stream, const char *restrict format, va_list vlist);
int vsscanf(const char *restrict buffer, const char *restrict format, va_list vlist);

#ifdef __cplusplus
}
#endif

#endif
