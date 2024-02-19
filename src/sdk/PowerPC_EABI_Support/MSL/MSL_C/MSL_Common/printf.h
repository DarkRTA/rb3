#ifndef _MSL_PRINTF_H
#define _MSL_PRINTF_H

#include "file_def.h"
#include "restrict_def.h"
#include "va_list_def.h"

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char *RESTRICT format, ...);
int fprintf(FILE *RESTRICT stream, const char *RESTRICT format, ...);
int sprintf(char *RESTRICT buffer, const char *RESTRICT format, ...);
int snprintf(char *RESTRICT buffer, size_t bufsz, const char *RESTRICT format, ...);

int vprintf(const char *RESTRICT format, va_list vlist);
int vfprintf(FILE *RESTRICT stream, const char *RESTRICT format, va_list vlist);
int vsprintf(char *RESTRICT buffer, const char *RESTRICT format, va_list vlist);
int vsnprintf(char *RESTRICT buffer, size_t bufsz, const char *RESTRICT format, va_list vlist);

#ifdef __cplusplus
}
#endif

#endif
