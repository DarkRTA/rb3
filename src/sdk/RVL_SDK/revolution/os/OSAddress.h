#ifndef RVL_SDK_OS_ADDRESS_H
#define RVL_SDK_OS_ADDRESS_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(NDEBUG)
# define OSPhysicalToCached(addr)	(void *)((u32)(addr) + 0x80000000)
# define OSPhysicalToUncached(addr)	(void *)((u32)(addr) + 0xC0000000)
# define OSCachedToPhysical(addr)	(void *)((u32)(addr) - 0x80000000)
# define OSUncachedToPhysical(addr)	(void *)((u32)(addr) - 0xC0000000)
#else
void *(OSPhysicalToCached)(void *addr);
void *(OSPhysicalToUncached)(void *addr);
void *(OSCachedToPhysical)(void *addr);
void *(OSUncachedToPhysical)(void *addr);
#endif

#ifdef __cplusplus
}
#endif

#endif
