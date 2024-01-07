#ifndef MSL_SCANF_H
#define MSL_SCANF_H

#include "types.h"
#include <stdarg.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

int scanf(const char *RESTRICT format, ...);
int fscanf(FILE *RESTRICT stream, const char *RESTRICT format, ...);
int sscanf(const char *RESTRICT buffer, const char *RESTRICT format, ...);

int vscanf(const char *RESTRICT format, va_list vlist);
int vfscanf(FILE *RESTRICT stream, const char *RESTRICT format, va_list vlist);
int vsscanf(const char *RESTRICT buffer, const char *RESTRICT format, va_list vlist);

#ifdef __cplusplus
}
#endif

#endif
