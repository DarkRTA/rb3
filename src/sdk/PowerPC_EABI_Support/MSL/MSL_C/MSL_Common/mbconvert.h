#ifndef MSL_MBCONVERT_H
#define MSL_MBCONVERT_H

#include "macros.h"
#include "wchar_def.h"

#ifdef __cplusplus
extern "C" {
#endif

// TODO
struct mbstate_t;

wint_t btowc(int c);
int wctob(wint_t c);

// clang-format off: compactness
size_t mbrlen(const char *RESTRICT s, size_t n, struct mbstate_t *RESTRICT ps);
size_t mbrtowc(wchar_t *RESTRICT pwc, const char *RESTRICT s, size_t n, struct mbstate_t *RESTRICT ps);
int mbsinit(const struct mbstate_t *ps);
size_t mbsrtowcs(wchar_t *RESTRICT dst, const char **RESTRICT src, size_t len, struct mbstate_t *RESTRICT ps);
size_t wcrtomb(char *RESTRICT s, wchar_t wc, struct mbstate_t *RESTRICT ps);
size_t wcsrtombs(char *RESTRICT dst, const wchar_t **RESTRICT src, size_t len, struct mbstate_t *RESTRICT ps);
// clang-format on

#ifdef __cplusplus
}
#endif

#endif
