#ifndef _WCHAR_TIME_H
#define _WCHAR_TIME_H

#include <time.h>
#include "MSL_C/MSL_Common/wchar_def.h"

#ifdef __cplusplus
extern "C" {
#endif

size_t wcsftime(wchar_t *str, size_t count, const wchar_t *format, struct tm *time);

#ifdef __cplusplus
}
#endif

#endif
