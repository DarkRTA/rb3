#ifndef UTL_POOLALLOC_H
#define UTL_POOLALLOC_H

// forward declaration
class FixedSizeAlloc;

class ChunkAllocator {
public:
    FixedSizeAlloc *mAllocs[32];

    ChunkAllocator(int, int, int);
    void *Alloc(int);
    void Free(void *, int);
    void UploadDebugStats();

    // *might* be wrong
    operator bool() { return mAllocs != 0; }
};

class FixedSizeAlloc {
public:
    FixedSizeAlloc(int, ChunkAllocator *, int);
    virtual ~FixedSizeAlloc();
    virtual void *RawAlloc(int);

    int mAllocSizeWords;
    int mNumAllocs;
    int mMaxAllocs;
    int mNumChunks;
    int *mFreeList;
    int mNodesPerChunk;
    ChunkAllocator *mAlloc;

    void *Alloc();
    void Free(void *);
    void Refill();
};

enum PoolType {
    MainPool,
    FastPool
};

bool AddrIsInPool(void *, PoolType);
void *_PoolAlloc(int, int, PoolType);
void _PoolFree(int, PoolType, void *);

#define NEW_POOL_OVERLOAD(obj)                                                           \
    void *operator new(size_t s) { return _PoolAlloc(s, sizeof(obj), FastPool); }        \
    void *operator new(size_t, void *place) { return place; }

#define DELETE_POOL_OVERLOAD(obj)                                                        \
    void operator delete(void *v) { _PoolFree(sizeof(obj), FastPool, v); }

#endif
