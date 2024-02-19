#ifndef _MSL_EXTRAS_H
#define _MSL_EXTRAS_H

#include "size_def.h"

#ifdef __cplusplus
extern "C" {
#endif

int stricmp(const char*, const char*);
int strnicmp(const char*, const char*, size_t);

size_t strnlen(const char *str, size_t maxlen);

int strcasecmp(const char *lhs, const char *rhs);

#ifdef __cplusplus
}
#endif

#endif
