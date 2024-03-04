#ifndef _MSL_MBCONVERT_H
#define _MSL_MBCONVERT_H

#include "restrict_def.h"
#include "size_def.h"
#include "wchar_def.h"
#include "wint_def.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mbstate_t {}; /* TODO */

wint_t btowc(int c);
int wctob(wint_t c);

/* clang-format off */
size_t mbrlen(const char *RESTRICT s, size_t n, struct mbstate_t *RESTRICT ps);
size_t mbrtowc(wchar_t *RESTRICT pwc, const char *RESTRICT s, size_t n, struct mbstate_t *RESTRICT ps);
int mbsinit(const struct mbstate_t *ps);
size_t mbsrtowcs(wchar_t *RESTRICT dst, const char **RESTRICT src, size_t len, struct mbstate_t *RESTRICT ps);
size_t wcrtomb(char *RESTRICT s, wchar_t wc, struct mbstate_t *RESTRICT ps);
size_t wcsrtombs(char *RESTRICT dst, const wchar_t **RESTRICT src, size_t len, struct mbstate_t *RESTRICT ps);
/* clang-format on */

#ifdef __cplusplus
}
#endif

#endif
