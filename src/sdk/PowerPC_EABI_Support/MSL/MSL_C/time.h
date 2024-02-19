#ifndef _TIME_H
#define _TIME_H


#ifdef __cplusplus
extern "C" {
#endif

// #define CLOCKS_PER_SEC

typedef long time_t;
typedef long clock_t;

/** Structure holding a calendar date and time broken down into its components. */
struct tm {
    /** seconds after the minute - [0, 60] including leap second */
    int tm_sec;

    /** minutes after the hour - [0, 59] */
    int tm_min;

    /** hours since midnight - [0, 23] */
    int tm_hour;

    /** day of the month - [1, 31] */
    int tm_mday;

    /** months since January - [0, 11] */
    int tm_mon;

    /** years since 1900 */
    int tm_year;

    /** days since Sunday - [0, 6] */
    int tm_wday;

    /** days since January 1 - [0, 365] */
    int tm_yday;

    /** daylight savings time flag */
    int tm_isdst;
};

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
