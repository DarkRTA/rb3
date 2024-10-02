#pragma once
#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef void *(*malloc_func)(u32 size);
typedef void (*free_func)(void* mem);

void RADSetMemory(malloc_func malloc, free_func free);
void *radmalloc(u32 size);
void radfree(void* mem);

#ifdef __cplusplus
}
#endif
