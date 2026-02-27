#ifndef _STRING_H
#define _STRING_H

#include "MSL_Common/restrict_def.h"

#include "PowerPC_EABI_Support/Runtime/__mem.h" /* IWYU pragma: export */
#include "MSL_Common/string_api.h" /* IWYU pragma: export */
#include "MSL_Common/extras.h" /* IWYU pragma: export */

#ifdef __cplusplus
extern "C" {
#endif

char *strcpy(char *RESTRICT dest, const char *RESTRICT src);
char *strncpy(char *RESTRICT dest, const char *RESTRICT src, size_t count);
char *strcat(char *RESTRICT dest, const char *RESTRICT src);
char *strncat(char *RESTRICT dest, const char *RESTRICT src, size_t count);
char *strdup(const char *src);
char *strndup(const char *src, size_t size);

size_t strxfrm(char *RESTRICT dest, const char *RESTRICT src, size_t count);

size_t strlen(const char *str);



int strcmp(const char *lhs, const char *rhs);
int strncmp(const char *lhs, const char *rhs, size_t count);
char *strchr(const char *str, int ch);
char *strrchr(const char *str, int ch);
int strcoll(const char *lhs, const char *rhs);

size_t strspn(const char *dest, const char *src);
size_t strcspn(const char *dest, const char *src);

char *strpbrk(const char *dest, const char *breakset);
char *strstr(const char *str, const char *substr);
char *strtok(char *RESTRICT str, const char *RESTRICT delim);

char *strerror(int errnum);

void *memchr(const void *ptr, int ch, size_t count);
int memcmp(const void *lhs, const void *rhs, size_t count);
void *memmove(void *dest, const void *src, size_t count);

#ifdef __cplusplus
}
#endif

#endif
