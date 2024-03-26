#ifndef _MSL_IMAXDIV_DEF_H
#define _MSL_IMAXDIV_DEF_H

#include "MSL_Common/restrict_def.h"
#include "MSL_Common/intmax_def.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    intmax_t quot;
    intmax_t rem;
} imaxdiv_t;

intmax_t imaxabs(intmax_t n);
imaxdiv_t imaxdiv(intmax_t x, intmax_t y);

intmax_t strtoimax(const char *RESTRICT nptr, char **RESTRICT endptr, int base);
uintmax_t strtoumax(const char *RESTRICT nptr, char **RESTRICT endptr, int base);

intmax_t wcstoimax(const wchar_t *RESTRICT nptr, wchar_t **RESTRICT endptr, int base);
uintmax_t wcstoumax(const wchar_t *RESTRICT nptr, wchar_t **RESTRICT endptr, int base);

#ifdef __cplusplus
}
#endif

#endif
