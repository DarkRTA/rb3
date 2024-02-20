#ifndef UTL_POOLALLOC_H
#define UTL_POOLALLOC_H
#include <new>

void* _PoolAlloc(int, int, PoolType);
void _PoolFree(int, PoolType, void*);

#endif
