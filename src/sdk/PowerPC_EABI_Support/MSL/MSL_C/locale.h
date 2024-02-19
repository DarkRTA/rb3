#ifndef _LOCALE_H
#define _LOCALE_H

#include "MSL_Common/locale_def.h"

#ifdef __cplusplus
extern "C" {
#endif

char* setlocale(int category, const char *locale);
struct lconv *localeconv();

#ifdef __cplusplus
}
#endif

#endif
