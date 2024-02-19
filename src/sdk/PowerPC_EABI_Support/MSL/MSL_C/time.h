#ifndef _TIME_H
#define _TIME_H

#include "MSL_Common/restrict_def.h"
#include "MSL_Common/size_def.h"
#include "MSL_Common/time_def.h"

#ifdef __cplusplus
extern "C" {
#endif

/* #define CLOCKS_PER_SEC */

time_t time(time_t *arg);
double difftime(time_t time_end, time_t time_beg);
clock_t clock(void);

char *ctime(const time_t *timer);
char *asctime(const struct tm *time_ptr);
size_t strftime(
    char *RESTRICT str,
    size_t count,
    const char *RESTRICT format,
    const struct tm *RESTRICT tp
);

time_t mktime(struct tm *arg);
struct tm *gmtime(const time_t *timer);
struct tm *localtime(const time_t *timer);

#ifdef __cplusplus
}
#endif

#endif
