#ifndef _EXTRAS_H
#define _EXTRAS_H

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
