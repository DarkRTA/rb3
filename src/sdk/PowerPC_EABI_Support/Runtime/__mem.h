#ifndef RUNTIME_MEM_H
#define RUNTIME_MEM_H

#include "MSL_C/MSL_Common/size_def.h"
#include "MSL_C/MSL_Common/restrict_def.h"

#include "compiler_macros.h"

#ifdef __cplusplus
extern "C" {
#endif

DECL_SECTION(".init") void* memcpy(void *RESTRICT dest, const void *RESTRICT src, size_t count);
DECL_SECTION(".init") void __fill_mem(void* dest, int val, size_t count);
DECL_SECTION(".init") void* memset(void *dest, int ch, size_t count);

#ifdef __cplusplus
}
#endif

#endif
