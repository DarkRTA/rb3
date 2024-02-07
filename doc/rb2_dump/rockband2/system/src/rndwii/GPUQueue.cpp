/*
    Compile unit: C:\rockband2\system\src\rndwii\GPUQueue.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8054D9EC -> 0x8054DCCC
*/
class GPUQueue {
    // total size: 0x18
    int mSize; // offset 0x0, size 0x4
    char * mBuffer; // offset 0x4, size 0x4
    char * mNextBlock; // offset 0x8, size 0x4
    int mNumReqs; // offset 0xC, size 0x4
    int mCurBytes; // offset 0x10, size 0x4
    int mMaxBytes; // offset 0x14, size 0x4
};
class GPUQueue gGPUMem; // size: 0x18, address: 0x80982230
class GPUQueue & GPUMem; // size: 0x4, address: 0x80A53E48
// Range: 0x8054D9EC -> 0x8054DA0C
void * GPUQueue::GPUQueue() {}

// Range: 0x8054DA0C -> 0x8054DA74
void * GPUQueue::~GPUQueue(class GPUQueue * const this /* r30 */) {}

static int _x; // size: 0x4, address: 0x80A53E4C
// Range: 0x8054DA74 -> 0x8054DB20
void GPUQueue::Init(class GPUQueue * const this /* r30 */) {
    // Local variables
    class DataArray * config; // r31

    // References
    // -> static int _x;
}

static class RndOverlay * stats; // size: 0x4, address: 0x80A53E54
// Range: 0x8054DB20 -> 0x8054DBBC
void GPUQueue::Begin(class GPUQueue * const this /* r31 */) {
    // References
    // -> static class RndOverlay * stats;
}

// Range: 0x8054DBBC -> 0x8054DBD4
void GPUQueue::End() {}

// Range: 0x8054DBD4 -> 0x8054DC7C
void * GPUQueue::Acquire(class GPUQueue * const this /* r29 */, int numBytes /* r30 */) {
    // Local variables
    char * p; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8054DC7C -> 0x8054DCCC
static void __sinit_\GPUQueue_cpp() {
    // References
    // -> class GPUQueue & GPUMem;
    // -> class GPUQueue gGPUMem;
}


