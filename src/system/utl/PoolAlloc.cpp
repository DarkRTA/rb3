#include "utl/PoolAlloc.h"
#include "os/Debug.h"
#include "os/CritSec.h"

extern CriticalSection* gMemLock;
extern ChunkAllocator* gChunkAlloc;

FixedSizeAlloc::FixedSizeAlloc(int mAllocSizeWords, ChunkAllocator* alloc, int j) : 
    mAllocSizeWords(mAllocSizeWords), mNumAllocs(0), mMaxAllocs(0), 
    mNumChunks(0), mFreeList(0), mNodesPerChunk(j), mAlloc(alloc) {
    MILO_ASSERT(mAllocSizeWords != 0, 0xDD);
}

void* FixedSizeAlloc::Alloc(){
    if(!mFreeList) Refill();
    int oldNumAllocs = mNumAllocs++;
    if(mMaxAllocs < oldNumAllocs){
        mMaxAllocs = oldNumAllocs;
    }
}

void FixedSizeAlloc::Free(void* v){
    v = mFreeList;
    mFreeList = (int*)v;
    MILO_ASSERT(mNumAllocs > 0, 0x102);
    mNumAllocs--;
}

#define MAX_FIXED_ALLOCS 0x40

void* ChunkAllocator::Alloc(int i){
    
}

void ChunkAllocator::Free(void* v, int fixedSizeIndex){
    MILO_ASSERT(fixedSizeIndex < MAX_FIXED_ALLOCS, 0x16D);
    MILO_ASSERT(mAllocs[fixedSizeIndex], 0x16E);
    mAllocs[fixedSizeIndex]->Free(v);
}

void _PoolFree(int size, PoolType pool, void* addr){
    if(!AddrIsInPool(addr, pool)){
        _MemFree(addr);
    }
    else if(addr){
        CritSecTracker cst(gMemLock);
        MILO_ASSERT(gChunkAlloc[pool], 0x22F);
        gChunkAlloc[pool].Free(addr, size);
    }
}
