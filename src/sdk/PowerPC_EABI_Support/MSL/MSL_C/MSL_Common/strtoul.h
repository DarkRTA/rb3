#ifndef _MSL_STRTOUL_H
#define _MSL_STRTOUL_H

#include "restrict_def.h"

#ifdef __cplusplus
extern "C" {
#endif

unsigned long __strtoul(
    int base,
    int max_width,
    int (*ReadProc)(void *, int, int),
    void *ReadProcArg,
    int *chars_scanned,
    int *negative,
    int *overflow
);
unsigned long long __strtoull(
    int base,
    int max_width,
    int (*ReadProc)(void *, int, int),
    void *ReadProcArg,
    int *chars_scanned,
    int *negative,
    int *overflow
);

int atoi(const char *str);
long atol(const char *str);
long long atoll(const char *str);

long strtol(const char *RESTRICT str, char **RESTRICT str_end, int base);
long long strtoll(const char *RESTRICT str, char **RESTRICT str_end, int base);
unsigned long strtoul(const char *RESTRICT str, char **RESTRICT str_end, int base);
unsigned long long strtoull(const char *RESTRICT str, char **RESTRICT str_end, int base);

#ifdef __cplusplus
}
#endif

#endif
