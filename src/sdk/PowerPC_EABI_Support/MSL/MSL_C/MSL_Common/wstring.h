#ifndef _MSL_WSTRING_H
#define _MSL_WSTRING_H

#include "restrict_def.h"
#include "size_def.h"
#include "wchar_def.h"

#ifdef __cplusplus
extern "C" {
#endif

size_t wcslen(const wchar_t *str);

wchar_t *wcscpy(wchar_t *RESTRICT dest, const wchar_t *RESTRICT src);
wchar_t *wcsncpy(wchar_t *RESTRICT dest, const wchar_t *RESTRICT src, size_t count);
wchar_t *wcscat(wchar_t *RESTRICT dest, const wchar_t *RESTRICT src);
wchar_t *wcsncat(wchar_t *RESTRICT dest, const wchar_t *RESTRICT src, size_t count);
size_t wcsxfrm(wchar_t *RESTRICT dest, const wchar_t *RESTRICT src, size_t count);

int wcscmp(const wchar_t *lhs, const wchar_t *rhs);
int wcsncmp(const wchar_t *lhs, const wchar_t *rhs, size_t count);
int wcscoll(const wchar_t *lhs, const wchar_t *rhs);
wchar_t *wcschr(const wchar_t *str, wchar_t ch);
wchar_t *wcsrchr(const wchar_t *str, wchar_t ch);
size_t wcsspn(const wchar_t *dest, const wchar_t *src);
size_t wcscspn(const wchar_t *dest, const wchar_t *src);

wchar_t *wcspbrk(const wchar_t *dest, const wchar_t *str);
wchar_t *wcsstr(const wchar_t *dest, const wchar_t *src);
wchar_t *
wcstok(wchar_t *RESTRICT str, const wchar_t *RESTRICT delim, wchar_t **RESTRICT ptr);

#ifdef __cplusplus
}
#endif

#endif
