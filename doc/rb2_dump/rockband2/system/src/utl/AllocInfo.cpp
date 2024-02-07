/*
    Compile unit: C:\rockband2\system\src\utl\AllocInfo.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805FF634 -> 0x805FF984
*/
static char gDefaultMem[4]; // size: 0x4, address: 0x80A55390
class Pool {
    // total size: 0x4
    char * mFree; // offset 0x0, size 0x4
};
static class Pool sPool; // size: 0x4, address: 0x80A55398
// Range: 0x805FF634 -> 0x805FF67C
static class Pool & GetPool() {
    // References
    // -> static char gDefaultMem[4];
    // -> static class Pool sPool;
}

class AllocInfo {
    // total size: 0x18
public:
    int mReqSize; // offset 0x0, size 0x4
    int mActSize; // offset 0x4, size 0x4
    const char * mType; // offset 0x8, size 0x4
    void * mMem; // offset 0xC, size 0x4
    signed char mHeap; // offset 0x10, size 0x1
    unsigned char mPooled; // offset 0x11, size 0x1
    signed short mTimeSlice; // offset 0x12, size 0x2
    unsigned char mStrat; // offset 0x14, size 0x1
};
// Range: 0x805FF67C -> 0x805FF6B8
void AllocInfo::SetPoolMemory() {}

// Range: 0x805FF6B8 -> 0x805FF750
void * AllocInfo::__nw() {
    // Local variables
    void * mem; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805FF750 -> 0x805FF784
void AllocInfo::__dl(void * mem /* r31 */) {}

// Range: 0x805FF784 -> 0x805FF7DC
void * AllocInfo::AllocInfo(class AllocInfo * const this /* r31 */) {
    // References
    // -> class MemTracker * gMemTracker;
}

// Range: 0x805FF7DC -> 0x805FF80C
int AllocInfo::StackCompare() {
    // Local variables
    int cmp; // r0
}

// Range: 0x805FF80C -> 0x805FF884
int AllocInfo::Compare(const class AllocInfo * const this /* r30 */, const class AllocInfo & rhs /* r31 */) {
    // Local variables
    int cmp; // r0
}

// Range: 0x805FF884 -> 0x805FF8D8
void AllocInfo::Validate() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805FF8D8 -> 0x805FF948
void AllocInfo::Print(const class AllocInfo * const this /* r30 */, class TextStream & s /* r31 */) {}

// Range: 0x805FF948 -> 0x805FF94C
void AllocInfo::FillStackTrace() {}

// Range: 0x805FF94C -> 0x805FF984
class TextStream & __ls(class TextStream & s /* r31 */) {}

class HeapStats {
    // total size: 0x14
public:
    int mTotalNumAllocs; // offset 0x0, size 0x4
    int mTotalActSize; // offset 0x4, size 0x4
    int mTotalReqSize; // offset 0x8, size 0x4
    int mMaxNumAllocs; // offset 0xC, size 0x4
    int mMaxActSize; // offset 0x10, size 0x4
};
class BlockStat {
    // total size: 0x18
public:
    const char * mName; // offset 0x0, size 0x4
    int mSizeReq; // offset 0x4, size 0x4
    int mSizeAct; // offset 0x8, size 0x4
    int mMaxSize; // offset 0xC, size 0x4
    int mNumAllocs; // offset 0x10, size 0x4
    unsigned char mHeap; // offset 0x14, size 0x1
};
class BlockStatTable {
    // total size: 0x600C
    class BlockStat mStats[1024]; // offset 0x0, size 0x6000
    int mMaxStats; // offset 0x6000, size 0x4
    int mNumStats; // offset 0x6004, size 0x4
    unsigned char mSizeMatters; // offset 0x6008, size 0x1
};
class AllocInfoVec {
    // total size: 0xC
    class AllocInfo * * mStart; // offset 0x0, size 0x4
    class AllocInfo * * mEnd; // offset 0x4, size 0x4
    class AllocInfo * * mEndOfStorage; // offset 0x8, size 0x4
};
class MemTracker {
    // total size: 0x18190
    class AllocInfo * * mHashMem; // offset 0x0, size 0x4
    class KeylessHash * mHash; // offset 0x4, size 0x4
    signed short mTimeSlice; // offset 0x8, size 0x2
    class HeapStats mHeapStats[16]; // offset 0xC, size 0x140
    class BlockStatTable mHeapTypeStats[2]; // offset 0x14C, size 0xC018
    class BlockStatTable mPoolTypeStats[2]; // offset 0xC164, size 0xC018
    int mCurStatTable; // offset 0x1817C, size 0x4
    class AllocInfoVec mFreedInfos; // offset 0x18180, size 0xC
    class TextStream * mLog; // offset 0x1818C, size 0x4
};

