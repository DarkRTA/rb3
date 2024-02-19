#ifndef _MSL_MBSTRING_H
#define _MSL_MBSTRING_H

#include "restrict_def.h"
#include "size_def.h"
#include "wchar_def.h"

#ifdef __cplusplus
extern "C" {
#endif

int __mbtowc_noconv(wchar_t *, const char *, size_t);
int __wctomb_noconv(char *, wchar_t);

int mblen(const char *s, size_t n);
int mbtowc(wchar_t *RESTRICT pwc, const char *RESTRICT s, size_t n);
size_t mbstowcs(wchar_t *RESTRICT dst, const char *RESTRICT src, size_t len);
int wctomb(char *s, wchar_t wc);
size_t wcstombs(char *RESTRICT dst, const wchar_t *RESTRICT src, size_t len);

#ifdef __cplusplus
}
#endif

#endif
