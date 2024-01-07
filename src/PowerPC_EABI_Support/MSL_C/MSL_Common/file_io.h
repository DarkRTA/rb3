#ifndef MSL_FILE_IO_H
#define MSL_FILE_IO_H

#include "types.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

FILE *fopen(const char *restrict filename, const char *restrict mode);
FILE *
freopen(const char *restrict filename, const char *restrict mode, FILE *restrict stream);
int fclose(FILE *file);

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t
fwrite(const void *restrict buffer, size_t size, size_t count, FILE *restrict stream);
int fflush(FILE *file);

#ifdef __cplusplus
}
#endif

#endif
