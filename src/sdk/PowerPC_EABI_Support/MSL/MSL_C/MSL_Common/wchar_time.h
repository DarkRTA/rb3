#ifndef _MSL_WCHAR_TIME_H
#define _MSL_WCHAR_TIME_H

#include "size_def.h"
#include "time_def.h"
#include "wchar_def.h"

#ifdef __cplusplus
extern "C" {
#endif

size_t wcsftime(wchar_t *str, size_t count, const wchar_t *format, struct tm *time);

#ifdef __cplusplus
}
#endif

#endif
