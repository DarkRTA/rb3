#ifndef _MSL_BUFFER_IO_H
#define _MSL_BUFFER_IO_H

#include "file_def.h"

#ifdef __cplusplus
extern "C" {
#endif

int __flush_buffer(FILE* file, size_t* length);
void __prep_buffer(FILE* file);

#ifdef __cplusplus
}
#endif

#endif
