#ifndef MSL_MBSTRING_H
#define MSL_MBSTRING_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

// TODO
// struct mbstate_t;

int __mbtowc_noconv(wchar_t *, const char *, size_t);
int __wctomb_noconv(char *, wchar_t);

int mblen(const char *s, size_t n);
int mbtowc(wchar_t *restrict pwc, const char *restrict s, size_t n);
size_t mbstowcs(wchar_t *restrict dst, const char *restrict src, size_t len);
int wctomb(char *s, wchar_t wc);
size_t wcstombs(char *restrict dst, const wchar_t *restrict src, size_t len);

#ifdef __cplusplus
}
#endif

#endif
