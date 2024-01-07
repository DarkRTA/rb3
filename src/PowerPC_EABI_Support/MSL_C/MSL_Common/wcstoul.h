#ifndef MSL_WCSTOUL_H
#define MSL_WCSTOUL_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

unsigned long
__wcstoul(int, int, wint_t (*wReadProc)(void *, wint_t, int), void *, int *, int *, int *);
//__wcstoull

long wcstol(const wchar_t *restrict str, wchar_t **restrict str_end, int base);
long long wcstoll(const wchar_t *restrict str, wchar_t **restrict str_end, int base);
unsigned long wcstoul(const wchar_t *restrict str, wchar_t **restrict str_end, int base);
unsigned long long
wcstoull(const wchar_t *restrict str, wchar_t **restrict str_end, int base);

float wcstof(const wchar_t *restrict str, wchar_t **restrict str_end);
double wcstod(const wchar_t *restrict str, wchar_t **restrict str_end);
long double wcstold(const wchar_t *restrict str, wchar_t **restrict str_end);

#ifdef __cplusplus
}
#endif

#endif
