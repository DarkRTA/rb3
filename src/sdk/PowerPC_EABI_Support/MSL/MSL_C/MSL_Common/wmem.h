#ifndef _MSL_WMEM_H
#define _MSL_WMEM_H

#include "restrict_def.h"
#include "size_def.h"
#include "wchar_def.h"

#ifdef __cplusplus
extern "C" {
#endif

wchar_t *wmemcpy(wchar_t *RESTRICT dest, const wchar_t *RESTRICT src, size_t count);
wchar_t *wmemmove(wchar_t *dest, const wchar_t *src, size_t count);
int wmemcmp(const wchar_t *lhs, const wchar_t *rhs, size_t count);
wchar_t *wmemchr(const wchar_t *ptr, wchar_t ch, size_t count);
wchar_t *wmemset(wchar_t *dest, wchar_t ch, size_t count);

#ifdef __cplusplus
}
#endif

#endif
