#ifndef _MSL_WCSTOUL_H
#define _MSL_WCSTOUL_H

#include "restrict_def.h"
#include "wchar_def.h"
#include "wint_def.h"

#ifdef __cplusplus
extern "C" {
#endif

unsigned long
__wcstoul(int, int, wint_t (*wReadProc)(void *, wint_t, int), void *, int *, int *, int *);
/* __wcstoull */

long wcstol(const wchar_t *RESTRICT str, wchar_t **RESTRICT str_end, int base);
long long wcstoll(const wchar_t *RESTRICT str, wchar_t **RESTRICT str_end, int base);
unsigned long wcstoul(const wchar_t *RESTRICT str, wchar_t **RESTRICT str_end, int base);
unsigned long long
wcstoull(const wchar_t *RESTRICT str, wchar_t **RESTRICT str_end, int base);

float wcstof(const wchar_t *RESTRICT str, wchar_t **RESTRICT str_end);
double wcstod(const wchar_t *RESTRICT str, wchar_t **RESTRICT str_end);
long double wcstold(const wchar_t *RESTRICT str, wchar_t **RESTRICT str_end);

#ifdef __cplusplus
}
#endif

#endif
