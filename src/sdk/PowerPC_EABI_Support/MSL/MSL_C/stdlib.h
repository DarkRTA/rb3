#ifndef _STDLIB_H
#define _STDLIB_H

#include "MSL_Common/alloc.h" /* IWYU pragma: export */
#include "MSL_Common/arith.h" /* IWYU pragma: export */
#include "MSL_Common/mbstring.h" /* IWYU pragma: export */
#include "MSL_Common/rand.h" /* IWYU pragma: export */
#include "MSL_Common/strtold.h" /* IWYU pragma: export */
#include "MSL_Common/strtoul.h" /* IWYU pragma: export */

#ifdef __cplusplus
extern "C" {
#endif

/* For functions that return 0 on a success and -1 on failure */
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1
#endif

void qsort(void *ptr, size_t count, size_t size, int (*comp)(const void *, const void *));
void *bsearch(
    const void *key,
    const void *ptr,
    size_t count,
    size_t size,
    int (*comp)(const void *, const void *)
);

long strtol(const char *str, char **_end, int base);

int system(const char *command);
char *getenv(const char *name);

int atexit(void (*func)(void));
void exit(int);
void abort(void);
void _Exit(int exit_code);

#ifdef __cplusplus
}
#endif

#endif
