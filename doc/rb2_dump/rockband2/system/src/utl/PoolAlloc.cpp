/*
    Compile unit: C:\rockband2\system\src\utl\PoolAlloc.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x806204E0 -> 0x80620E24
*/
// Range: 0x806204E0 -> 0x806204EC
static int SizeToIndex() {}

// Range: 0x806204EC -> 0x806204F8
static int IndexToPoolSize() {}

static int gHunkSize; // size: 0x4, address: 0x80A47BA0
static int gSmallHunkSize; // size: 0x4, address: 0x80A47BA4
static int gTotalChunksSize; // size: 0x4, address: 0x80A55508
static unsigned char gInited; // size: 0x1, address: 0x80A5550C
// Range: 0x806204F8 -> 0x8062054C
void PoolAllocInit(class DataArray * data /* r31 */) {
    // References
    // -> static unsigned char gInited;
    // -> static int gHunkSize;
}

static int * gPoolEnd; // size: 0x4, address: 0x80A55510
static int * gPoolStart; // size: 0x4, address: 0x80A55514
// Range: 0x8062054C -> 0x80620620
static int * RawPoolAlloc() {
    // Local variables
    int sizeWords; // r0
    int * mem; // r0

    // References
    // -> static int gSmallHunkSize;
    // -> static int gHunkSize;
    // -> static int * gPoolEnd;
    // -> static int * gPoolStart;
    // -> static int gTotalChunksSize;
}

class ChunkAllocator * gChunkAlloc; // size: 0x4, address: 0x80A55518
class FixedSizeAlloc {
    // total size: 0x1C
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    int mAllocSizeWords; // offset 0x4, size 0x4
    int mNumAllocs; // offset 0x8, size 0x4
    int mMaxAllocs; // offset 0xC, size 0x4
    int mNumChunks; // offset 0x10, size 0x4
    int * mFreeList; // offset 0x14, size 0x4
    int mNodesPerChunk; // offset 0x18, size 0x4
};
// Range: 0x80620620 -> 0x806206A8
void * FixedSizeAlloc::FixedSizeAlloc(class FixedSizeAlloc * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__14FixedSizeAlloc;
}

// Range: 0x806206A8 -> 0x80620708
void * FixedSizeAlloc::Alloc(class FixedSizeAlloc * const this /* r31 */) {
    // Local variables
    int * mem; // r3
}

// Range: 0x80620708 -> 0x80620780
void FixedSizeAlloc::Free(class FixedSizeAlloc * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80620780 -> 0x80620854
void FixedSizeAlloc::Refill(class FixedSizeAlloc * const this /* r30 */) {
    // Local variables
    int chunk_size; // r31
    int * chunk; // r3
    int * ptr; // r3
    int * end; // r4
    int * next; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80620854 -> 0x8062085C
int * FixedSizeAlloc::RawAlloc() {}

// Range: 0x8062085C -> 0x806208A4
void FixedSizeAlloc::GetStats() {}

class ChunkAllocator {
    // total size: 0x80
    class FixedSizeAlloc * mAllocs[32]; // offset 0x0, size 0x80
};
// Range: 0x806208A4 -> 0x80620938
void * ChunkAllocator::ChunkAllocator(class ChunkAllocator * const this /* r29 */) {
    // Local variables
    int i; // r30
}

// Range: 0x80620938 -> 0x806209B4
void * ChunkAllocator::Alloc(class ChunkAllocator * const this /* r30 */) {
    // Local variables
    int fixedSizeIndex; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x806209B4 -> 0x80620A78
void ChunkAllocator::Free(class ChunkAllocator * const this /* r28 */, void * mem /* r29 */) {
    // Local variables
    int fixedSizeIndex; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80620A78 -> 0x80620B74
void ChunkAllocator::Print(class ChunkAllocator * const this /* r27 */, class TextStream & stream /* r28 */) {
    // Local variables
    int size; // r1+0x18
    int allocs; // r1+0x14
    int maxallocs; // r1+0x10
    int cap; // r1+0xC
    int waste; // r1+0x8
    int total_waste; // r30
    int i; // r29

    // References
    // -> static int gTotalChunksSize;
}

// Range: 0x80620B74 -> 0x80620C60
void * PoolAlloc(int classSize /* r29 */, int reqSize /* r31 */, const char * type /* r30 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x8
    void * mem; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ChunkAllocator * gChunkAlloc;
    // -> class CriticalSection * gMemLock;
}

// Range: 0x80620C60 -> 0x80620D08
void PoolFree(int classSize /* r30 */, void * mem /* r31 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ChunkAllocator * gChunkAlloc;
    // -> class CriticalSection * gMemLock;
}

// Range: 0x80620D08 -> 0x80620D98
void PoolReport(class TextStream & stream /* r31 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ChunkAllocator * gChunkAlloc;
    // -> class CriticalSection * gMemLock;
}

class ReclaimableAlloc : public FixedSizeAlloc {
    // total size: 0x2C
    const char * mType; // offset 0x1C, size 0x4
    class vector mRawMems; // offset 0x20, size 0xC
};
// Range: 0x80620D98 -> 0x80620E24
int * ReclaimableAlloc::RawAlloc(class ReclaimableAlloc * const this /* r31 */) {
    // Local variables
    void * mem; // r1+0xC
}

struct {
    // total size: 0x10
} __vt__16ReclaimableAlloc; // size: 0x10, address: 0x8092F060
struct {
    // total size: 0x8
} __RTTI__16ReclaimableAlloc; // size: 0x8, address: 0x8092F090
struct {
    // total size: 0x10
} __vt__14FixedSizeAlloc; // size: 0x10, address: 0x8092F098
struct {
    // total size: 0x8
} __RTTI__14FixedSizeAlloc; // size: 0x8, address: 0x8092F0B8

