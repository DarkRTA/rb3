#ifndef MSL_STRTOLD_H
#define MSL_STRTOLD_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

long double __strtold(
    int max_width,
    int (*ReadProc)(void *, int, int),
    void *ReadProcArg,
    int *chars_scanned,
    int *overflow
);

double atof(const char *str);

float strtof(const char *RESTRICT str, char **RESTRICT str_end);
double strtod(const char *RESTRICT str, char **RESTRICT str_end);
long double strtold(const char *RESTRICT str, char **RESTRICT str_end);

#ifdef __cplusplus
}
#endif

#endif
