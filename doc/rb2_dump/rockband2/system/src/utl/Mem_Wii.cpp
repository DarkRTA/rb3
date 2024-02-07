/*
    Compile unit: C:\rockband2\system\src\utl\Mem_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80614210 -> 0x8061460C
*/
static unsigned char gHeapInitialized; // size: 0x1, address: 0x80A55488
struct MEMLink {
    // total size: 0x8
    void * prevObject; // offset 0x0, size 0x4
    void * nextObject; // offset 0x4, size 0x4
};
struct MEMList {
    // total size: 0xC
    void * headObject; // offset 0x0, size 0x4
    void * tailObject; // offset 0x4, size 0x4
    unsigned short numObjects; // offset 0x8, size 0x2
    unsigned short offset; // offset 0xA, size 0x2
};
struct /* @class$6086Mem_Wii_cpp */ {
    // total size: 0x4
    unsigned long _reserved : 24; // offset 0x0, size 0x4
    unsigned long optFlag : 8; // offset 0x0, size 0x4
};
union /* @class$6085Mem_Wii_cpp */ {
    unsigned long val; // offset 0x0, size 0x4
    struct /* @class$6086Mem_Wii_cpp */ {
        // total size: 0x4
        unsigned long _reserved : 24; // offset 0x0, size 0x4
        unsigned long optFlag : 8; // offset 0x0, size 0x4
    } fields; // offset 0x0, size 0x4
};
struct MEMiHeapHead {
    // total size: 0x3C
    unsigned long signature; // offset 0x0, size 0x4
    struct MEMLink link; // offset 0x4, size 0x8
    struct MEMList childList; // offset 0xC, size 0xC
    void * heapStart; // offset 0x18, size 0x4
    void * heapEnd; // offset 0x1C, size 0x4
    struct OSMutex mutex; // offset 0x20, size 0x18
    union /* @class$6085Mem_Wii_cpp */ {
        unsigned long val; // offset 0x0, size 0x4
        struct /* @class$6086Mem_Wii_cpp */ {
            // total size: 0x4
            unsigned long _reserved : 24; // offset 0x0, size 0x4
            unsigned long optFlag : 8; // offset 0x0, size 0x4
        } fields; // offset 0x0, size 0x4
    } attribute; // offset 0x38, size 0x4
};
static struct MEMiHeapHead * gMEM1Heap; // size: 0x4, address: 0x80A5548C
static struct MEMiHeapHead * gMEM2Heap; // size: 0x4, address: 0x80A55490
// Range: 0x80614210 -> 0x806142E4
static void InitDefaultHeap() {
    // Local variables
    void * arena1Lo; // r31
    void * arena1Hi; // r30
    void * arena2Lo; // r29
    void * arena2Hi; // r28

    // References
    // -> static struct MEMiHeapHead * gMEM2Heap;
    // -> static struct MEMiHeapHead * gMEM1Heap;
    // -> static unsigned char gHeapInitialized;
}

// Range: 0x806142E4 -> 0x806142F4
void * __sys_alloc() {}

// Range: 0x806142F4 -> 0x806142F8
void __sys_free() {}

// Range: 0x806142F8 -> 0x80614404
void * WiiAllocHeap(int * size /* r29 */, int membank /* r30 */) {
    // References
    // -> static struct MEMiHeapHead * gMEM2Heap;
    // -> static struct MEMiHeapHead * gMEM1Heap;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static unsigned char gHeapInitialized;
}

// Range: 0x80614404 -> 0x8061451C
void * WiiAllocHeapAlign(int * size /* r28 */, int membank /* r30 */, int align /* r29 */) {
    // References
    // -> static struct MEMiHeapHead * gMEM2Heap;
    // -> static struct MEMiHeapHead * gMEM1Heap;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static unsigned char gHeapInitialized;
}

// Range: 0x8061451C -> 0x80614564
void * WiiMalloc(unsigned long size /* r31 */) {
    // References
    // -> static struct MEMiHeapHead * gMEM1Heap;
    // -> static unsigned char gHeapInitialized;
}

// Range: 0x80614564 -> 0x80614570
void WiiFree() {
    // References
    // -> static struct MEMiHeapHead * gMEM1Heap;
}

// Range: 0x80614570 -> 0x8061460C
void WiiFreeHeap(void * ptr /* r30 */, int membank /* r31 */) {
    // References
    // -> static struct MEMiHeapHead * gMEM2Heap;
    // -> static struct MEMiHeapHead * gMEM1Heap;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}


