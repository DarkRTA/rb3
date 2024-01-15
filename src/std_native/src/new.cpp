#include <new>

#pragma force_active on
// fn_80354830
void *operator new(std::size_t size) {
    return _MemAlloc(size, 0);
}

// fn_80354838
void operator delete(void *ptr) throw() {
    MemFree(ptr);
}

// fn_8035483c
void *operator new[](std::size_t size) {
    return _MemAlloc(size, 0);
}

// fn_80354844
void operator delete[](void *ptr) throw() {
    MemFree(ptr);
}
#pragma force_active off

#define POOL_MAX 0x80
#define POOL_MAX_STL 0x100

// fn_80354848
void *MemOrPoolAlloc(int size, PoolType pool) {
    if (size == 0)
        return nullptr;

    if (size > POOL_MAX)
        return _MemAlloc(size, 0);
    else
        return _PoolAlloc(size, size, pool);
}

// fn_80354878
void MemOrPoolFree(int size, PoolType pool, void *ptr) {
    if (ptr == nullptr)
        return;

    if (size > POOL_MAX)
        MemFree(ptr);
    else
        _PoolFree(size, pool, ptr);
}

// fn_80354898
void *_MemOrPoolAllocSTL(int size, PoolType pool) {
    if (size == 0)
        return nullptr;

    if (size > POOL_MAX_STL)
        return _MemAlloc(size, 0);
    else
        return _PoolAlloc(size, size, pool);
}

// fn_803548c8
void _MemOrPoolFreeSTL(int size, PoolType pool, void *ptr) {
    if (ptr == 0)
        return;

    if (size > POOL_MAX_STL)
        MemFree(ptr);
    else
        _PoolFree(size, pool, ptr);
}
