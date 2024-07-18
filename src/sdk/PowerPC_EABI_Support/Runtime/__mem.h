#ifndef RUNTIME_MEM_H
#define RUNTIME_MEM_H

#include "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/size_def.h"
#include "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/restrict_def.h"

#ifdef __cplusplus
extern "C" {
#endif

__declspec(section ".init") void* memcpy(void *RESTRICT dest, const void *RESTRICT src, size_t count);
__declspec(section ".init") void __fill_mem(void* dest, int val, size_t count);
__declspec(section ".init") void* memset(void *dest, int ch, size_t count);

#ifdef __cplusplus
}
#endif

#endif
