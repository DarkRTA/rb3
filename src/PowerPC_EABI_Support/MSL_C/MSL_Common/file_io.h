#ifndef MSL_FILE_IO_H
#define MSL_FILE_IO_H

#include "types.h"
#include <stdio.h>

size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream);
int fclose(FILE* file);
int fflush(FILE* file);

#endif
