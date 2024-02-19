#ifndef _MSL_TIME_DEF_H
#define _MSL_TIME_DEF_H

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

#endif
