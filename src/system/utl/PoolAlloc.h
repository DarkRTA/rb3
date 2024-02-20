#ifndef UTL_POOLALLOC_H
#define UTL_POOLALLOC_H

// enum PoolType {
//     MainPool,
//     FastPool
// };

void* _PoolAlloc(int, int, PoolType);
void _PoolFree(int, PoolType, void*);

#endif
