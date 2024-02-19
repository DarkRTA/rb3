#ifndef _MSL_MEM_FUNCS_H
#define _MSL_MEM_FUNCS_H

#include "size_def.h"

#ifdef __cplusplus
extern "C" {
#endif

void __copy_longs_aligned(void* dst, const void* src, size_t len);
void __copy_longs_rev_aligned(void* dst, const void* src, size_t len);
void __copy_longs_unaligned(void* dst, const void* src, size_t len);
void __copy_longs_rev_unaligned(void* dst, const void* src, size_t len);
void __fill_mem(void* dest, int val, size_t count);

#ifdef __cplusplus
}
#endif

#endif
