#ifndef _MSL_WSCANF_H
#define _MSL_WSCANF_H

#include "file_def.h"
#include "restrict_def.h"
#include "size_def.h"
#include "wchar_def.h"
#include "va_list_def.h"

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
