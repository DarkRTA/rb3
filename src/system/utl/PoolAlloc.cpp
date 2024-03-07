#include "utl/PoolAlloc.h"
#include "os/Debug.h"

FixedSizeAlloc::FixedSizeAlloc(int mAllocSizeWords, ChunkAllocator* alloc, int j) : mAllocSizeWords(mAllocSizeWords), mNumAllocs(0), mMaxAllocs(0), mNumChunks(0), mFreeList(0), mNodesPerChunk(j), mAlloc(alloc) {
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
