/*
    Compile unit: C:\rockband2\system\src\utl\MemMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80611EF4 -> 0x80613FB8
*/
static int gTimeStamp; // size: 0x4, address: 0x80A55470
class FreeBlock {
    // total size: 0xC
    unsigned int mSizeWords; // offset 0x0, size 0x4
    unsigned int mTimeStamp; // offset 0x4, size 0x4
    class FreeBlock * mNextBlock; // offset 0x8, size 0x4
};
// Range: 0x80611EF4 -> 0x80611F78
unsigned char FreeBlock::AttemptMerge() {}

static class Heap gHeaps[16]; // size: 0x200, address: 0x8098A088
static int gNumHeaps; // size: 0x4, address: 0x80A55474
static int gHeapStack[16]; // size: 0x40, address: 0x8098A288
static int gHeapStackSize; // size: 0x4, address: 0x80A55478
static int gCheckConsistency; // size: 0x4, address: 0x80A5547C
static unsigned char gInsideMemFunc; // size: 0x1, address: 0x80A55480
unsigned char gStlAllocNameLookup; // size: 0x1, address: 0x80A55481
const char * gStlAllocName; // size: 0x4, address: 0x80A47B40
class CriticalSection * gMemLock; // size: 0x4, address: 0x80A55484
// Range: 0x80611F78 -> 0x80611FEC
int GetCurrentHeapNum() {
    // Local variables
    class CritSecTracker __cst; // r1+0x8

    // References
    // -> static int gHeapStack[16];
    // -> static int gHeapStackSize;
    // -> class CriticalSection * gMemLock;
}

// Range: 0x80611FEC -> 0x806120B0
void MemFreeBlockStats(int heapNum /* r28 */, int & num /* r29 */, int & bytes /* r30 */, int & largest /* r31 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x8

    // References
    // -> static class Heap gHeaps[16];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class CriticalSection * gMemLock;
}

class AllocBlock {
    // total size: 0x4
    unsigned int mSizeWords : 24; // offset 0x0, size 0x4
    unsigned int mPadWords : 4; // offset 0x0, size 0x4
    unsigned int mMagicNibble : 4; // offset 0x0, size 0x4
};
class Heap {
    // total size: 0x20
    class FreeBlock * mFreeBlockChain; // offset 0x0, size 0x4
    int * mStart; // offset 0x4, size 0x4
    const char * mName; // offset 0x8, size 0x4
    int mSizeWords; // offset 0xC, size 0x4
    int mNum; // offset 0x10, size 0x4
    unsigned char mIsHandleHeap; // offset 0x14, size 0x1
    int mDebugLevel; // offset 0x18, size 0x4
    enum Strategy mStrategy; // offset 0x1C, size 0x4
};
// Range: 0x806120B0 -> 0x80612160
void Heap::InsertFreeBlock(class Heap * const this /* r26 */, class FreeBlock * iBlock /* r27 */, int iSizeWords /* r28 */, class FreeBlock * iPrevBlock /* r29 */, class FreeBlock * iNextBlock /* r30 */, int iTimeStamp /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80612160 -> 0x806121B8
void Heap::FreeBlockStats() {
    // Local variables
    class FreeBlock * freeBlock; // r7
    int sizeBytes; // r3
}

enum Strategy {
    kFirstFit = 0,
    kBestFit = 1,
    kLRUFit = 2,
    kLastFit = 3,
};
// Range: 0x806121B8 -> 0x806122CC
void Heap::Init(class Heap * const this /* r24 */, const char * name /* r25 */, int num /* r26 */, int * mem /* r27 */, int sizeWords /* r28 */, unsigned char isHandle /* r29 */, enum Strategy strategy /* r30 */, int debug_level /* r31 */) {
    // References
    // -> static int gTimeStamp;
    // -> class Debug TheDebug;
}

// Range: 0x806122CC -> 0x80612334
void Heap::FirstFit() {
    // Local variables
    class FreeBlock * freeBlock; // r9
    class FreeBlock * lastBlock; // r10
}

// Range: 0x80612334 -> 0x806123A4
void Heap::BestFit() {
    // Local variables
    class FreeBlock * freeBlock; // r9
    class FreeBlock * lastBlock; // r10
}

// Range: 0x806123A4 -> 0x80612420
void Heap::LRUFit() {
    // Local variables
    class FreeBlock * freeBlock; // r9
    class FreeBlock * lastBlock; // r10
    int best_time; // r11
    int timestamp; // r7
}

// Range: 0x80612420 -> 0x80612484
void Heap::LastFit() {
    // Local variables
    class FreeBlock * freeBlock; // r9
    class FreeBlock * lastBlock; // r10
}

struct FreeBlockInfo {
    // total size: 0x10
    class FreeBlock * mBlock; // offset 0x0, size 0x4
    class FreeBlock * mPrevBlock; // offset 0x4, size 0x4
    int mSizeWords; // offset 0x8, size 0x4
    int mPadWords; // offset 0xC, size 0x4
};
// Range: 0x80612484 -> 0x80612744
int * Heap::Alloc(class Heap * const this /* r29 */, int iSizeWords /* r30 */, int & oActSize /* r31 */) {
    // Local variables
    struct FreeBlockInfo info; // r1+0x18
    int num_free; // r1+0x10
    int bytes_free; // r1+0xC
    int largest_block; // r1+0x8
    int allocWords; // r27
    int leftoverWords; // r5
    class AllocBlock * allocBlock; // r6

    // References
    // -> class CriticalSection * gMemLock;
    // -> static unsigned char gInsideMemFunc;
    // -> struct OSThread * gMainThreadID;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80612744 -> 0x80612884
int * Heap::Truncate(class Heap * const this /* r29 */, int * iMem /* r30 */, int iSizeWords /* r26 */, int & oActSize /* r31 */) {
    // Local variables
    class AllocBlock * allocBlock; // r28
    int truncWords; // r27
    class FreeBlock * prevFree; // r1+0xC
    class FreeBlock * nextFree; // r1+0x8
    class FreeBlock * freeBlock; // r26

    // References
    // -> static int gTimeStamp;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80612884 -> 0x806128C8
int Heap::AllocSize() {
    // Local variables
    class AllocBlock * allocBlock; // r0
}

// Range: 0x806128C8 -> 0x806128F8
void Heap::FindFreeNeighbors() {
    // Local variables
    class FreeBlock * freeBlock; // r3
    class FreeBlock * lastBlock; // r0
}

// Range: 0x806128F8 -> 0x80612A0C
unsigned char Heap::Free(class Heap * const this /* r31 */) {
    // Local variables
    class AllocBlock * allocBlock; // r30
    class FreeBlock * prevFree; // r1+0xC
    class FreeBlock * nextFree; // r1+0x8
    class FreeBlock * freeBlock; // r30

    // References
    // -> static int gTimeStamp;
}

// Range: 0x80612A0C -> 0x80612ACC
static void PrintAlloc(class TextStream & iStream /* r29 */, const class AllocInfo * info /* r30 */) {}

// Range: 0x80612ACC -> 0x80612D18
void Heap::Print(class Heap * const this /* r29 */, class TextStream & iStream /* r30 */, unsigned char iFreeOnly /* r31 */) {
    // Local variables
    class FreeBlock * freeBlock; // r26
    int * addr; // r25
    int * heapEnd; // r24
    int * equalAllocStart; // r23
    int equalAllocSize; // r22
    int numEqualAllocs; // r21
    const class AllocInfo * equalInfo; // r20
    int sizeWords; // r19
    int bytes; // r5
    int * pad; // r3
    class AllocBlock * allocBlock; // r0
    const class AllocInfo * info; // r18
    int bytes; // r17
    int num_free; // r1+0x10
    int bytes_free; // r1+0xC
    int largest_block; // r1+0x8
}

// Range: 0x80612D18 -> 0x80612DBC
void MemPushHeap(int iHeap /* r31 */) {
    // References
    // -> static int gHeapStack[16];
    // -> static int gHeapStackSize;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static int gNumHeaps;
    // -> class CriticalSection * gMemLock;
}

// Range: 0x80612DBC -> 0x80612E2C
void MemPopHeap() {
    // References
    // -> class CriticalSection * gMemLock;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static int gHeapStackSize;
}

// Range: 0x80612E2C -> 0x80612EC0
void * MemDoTempAllocations::MemDoTempAllocations(class MemDoTempAllocations * const this /* r31 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x8

    // References
    // -> static class Heap gHeaps[16];
    // -> class CriticalSection * gMemLock;
}

// Range: 0x80612EC0 -> 0x80612FA4
void * MemDoTempAllocations::~MemDoTempAllocations(class MemDoTempAllocations * const this /* r29 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Heap gHeaps[16];
    // -> class CriticalSection * gMemLock;
}

// Range: 0x80612FA4 -> 0x806132BC
void MemInit() {
    // Local variables
    class CritSecTracker __cst; // r1+0x4C
    unsigned char disable; // r1+0xA
    unsigned char tracking; // r1+0x9
    class DataArray * config; // r27
    void * tmp; // r26
    class DataArray * heaps; // r25
    int i; // r24
    int bytes; // r1+0x48
    unsigned char handle; // r1+0x8
    int region; // r1+0x44
    int debug; // r1+0x40
    enum Strategy strategy; // r1+0x3C

    // References
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static int gNumHeaps;
    // -> static int gCheckConsistency;
    // -> class CriticalSection * gMemLock;
}

// Range: 0x806132BC -> 0x80613414
static void AddHeap(const char * name /* r24 */, int heap /* r25 */, int bytes /* r1+0x8 */, unsigned char handle /* r26 */, enum Strategy strategy /* r27 */, int debug_level /* r28 */) {
    // Local variables
    int reqBytes; // r30
    char * raw_mem; // r29
    int leftover_bytes; // r30

    // References
    // -> static int gNumHeaps;
    // -> static class Heap gHeaps[16];
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x80613414 -> 0x80613494
static int GetFreeSystemMemory() {
    // Local variables
    int left; // r31
    int right; // r30
    int middle; // r29
    void * tmp; // r0
}

// Range: 0x80613494 -> 0x80613498
void MemTerminate() {}

// Range: 0x80613498 -> 0x80613624
void * MemAlloc(int iSizeBytes /* r30 */, const char * type /* r31 */, int iAlign /* r28 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x10
    void * allocated_mem; // r29
    int sizeWords; // r4
    int wordAlign; // r5
    int act_size; // r1+0xC
    void * allocated_mem; // r28

    // References
    // -> class MemTracker * gMemTracker;
    // -> static class Heap gHeaps[16];
    // -> class CriticalSection * gMemLock;
}

// Range: 0x80613624 -> 0x806136F0
void * MemAllocTemp(int size /* r29 */, const char * type /* r30 */, int align /* r31 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0xC
    class MemDoTempAllocations tmp; // r1+0x8

    // References
    // -> static int gHeapStackSize;
    // -> class CriticalSection * gMemLock;
}

// Range: 0x806136F0 -> 0x806137B4
void MemFree(void * iMem /* r30 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x8
    int i; // r31

    // References
    // -> static int gNumHeaps;
    // -> static class Heap gHeaps[16];
    // -> class CriticalSection * gMemLock;
}

// Range: 0x806137B4 -> 0x806138E0
void * MemTruncate(void * iMem /* r27 */, int iSizeBytes /* r28 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0xC
    int sizeWords; // r31
    int actSize; // r1+0x8
    int * ret; // r30
    int i; // r29

    // References
    // -> static int gNumHeaps;
    // -> static class Heap gHeaps[16];
    // -> class CriticalSection * gMemLock;
}

// Range: 0x806138E0 -> 0x806139DC
int MemAllocSize(void * iMem /* r29 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x8
    int i; // r31
    int size; // r30

    // References
    // -> class Debug TheDebug;
    // -> static int gNumHeaps;
    // -> static class Heap gHeaps[16];
    // -> class CriticalSection * gMemLock;
}

// Range: 0x806139DC -> 0x80613AE0
void * MemRealloc(void * mem /* r29 */, int newSize /* r1+0x8 */, const char * type /* r30 */, int align /* r31 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x10
    int oldSize; // r1+0xC
    void * ret; // r31
    void * ret; // r31

    // References
    // -> static int gNumHeaps;
    // -> class CriticalSection * gMemLock;
}

// Range: 0x80613AE0 -> 0x80613AE8
int MemNumHeaps() {
    // References
    // -> static int gNumHeaps;
}

// Range: 0x80613AE8 -> 0x80613B88
int MemFindHeap(const char * iName /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> static int gNumHeaps;
    // -> static class Heap gHeaps[16];
}

// Range: 0x80613B88 -> 0x80613BA0
char * MemHeapName() {
    // References
    // -> static class Heap gHeaps[16];
}

// Range: 0x80613BA0 -> 0x80613BBC
int MemHeapSize() {
    // References
    // -> static class Heap gHeaps[16];
}

// Range: 0x80613BBC -> 0x80613C3C
void MemPrint(int heap /* r29 */, class TextStream & s /* r30 */, unsigned char freeOnly /* r31 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x8

    // References
    // -> static class Heap gHeaps[16];
    // -> class CriticalSection * gMemLock;
}

class HandleInfo {
    // total size: 0x10
public:
    class MemHandle * mPtr; // offset 0x0, size 0x4
    int mLockCnt; // offset 0x4, size 0x4
    int mPad[2]; // offset 0x8, size 0x8
};
// Range: 0x80613C3C -> 0x80613C54
void * MemHandle::MemHandle() {}

// Range: 0x80613C54 -> 0x80613C70
void * MemHandle::Lock() {}

// Range: 0x80613C70 -> 0x80613D20
void MemHandle::Unlock(class MemHandle * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80613D20 -> 0x80613E64
class MemHandle * MemAllocH(int sizeBytes /* r28 */, const char * type /* r29 */) {
    // Local variables
    void * raw_mem; // r30

    // References
    // -> static class Heap gHeaps[16];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct OSThread * gMainThreadID;
}

// Range: 0x80613E64 -> 0x80613F44
void MemFreeH(class MemHandle * h /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct OSThread * gMainThreadID;
}

// Range: 0x80613F44 -> 0x80613F50
void * __nw() {}

// Range: 0x80613F50 -> 0x80613F54
void __dl() {}

// Range: 0x80613F54 -> 0x80613F64
void * __nwa() {}

// Range: 0x80613F64 -> 0x80613F68
void __dla() {}

// Range: 0x80613F68 -> 0x80613F98
void * MemOrPoolAlloc() {}

// Range: 0x80613F98 -> 0x80613FB8
void MemOrPoolFree() {}


