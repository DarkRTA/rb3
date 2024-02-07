/*
    Compile unit: C:\rockband2\system\src\utl\MemTrack.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8061460C -> 0x80614CEC
*/
static void * gAllocInfoHeap; // size: 0x4, address: 0x80A55498
class MemTracker * gMemTracker; // size: 0x4, address: 0x80A5549C
static int gFirstFileNum; // size: 0x4, address: 0x80A554A0
// Range: 0x8061460C -> 0x8061472C
static void StartLog(const char * base /* r28 */) {
    // Local variables
    char name[64]; // r1+0x8
    int i; // r30
    class File * f; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static int gFirstFileNum;
}

// Range: 0x8061472C -> 0x80614738
static void StopLog() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80614738 -> 0x80614868
void MemTrackInit() {
    // Local variables
    class CritSecTracker __cst; // r1+0x14

    // References
    // -> static void * gAllocInfoHeap;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class MemTracker * gMemTracker;
    // -> class CriticalSection * gMemLock;
}

// Range: 0x80614868 -> 0x80614908
void MemTrackAlloc(int reqSize /* r26 */, int actSize /* r27 */, const char * type /* r28 */, void * mem /* r29 */, unsigned char pooled /* r30 */, unsigned char strat /* r31 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x8
    int heap; // r0

    // References
    // -> class CriticalSection * gMemLock;
    // -> class MemTracker * gMemTracker;
}

// Range: 0x80614908 -> 0x8061496C
void MemTrackFree(void * mem /* r31 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x8

    // References
    // -> class CriticalSection * gMemLock;
    // -> class MemTracker * gMemTracker;
}

// Range: 0x8061496C -> 0x80614A00
void MemTrackRealloc(void * oldMem /* r28 */, int reqSize /* r29 */, int actSize /* r30 */, void * newMem /* r31 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x8

    // References
    // -> class CriticalSection * gMemLock;
    // -> class MemTracker * gMemTracker;
}

// Range: 0x80614A00 -> 0x80614A74
class AllocInfo * MemTrackGetInfo(void * mem /* r31 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x8

    // References
    // -> class CriticalSection * gMemLock;
    // -> class MemTracker * gMemTracker;
}

// Range: 0x80614A74 -> 0x80614B14
void MemTrackReport(int minSize /* r31 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> class CriticalSection * gMemLock;
    // -> class MemTracker * gMemTracker;
}

// Range: 0x80614B14 -> 0x80614BA4
void MemTrackHeapDump(unsigned char freeOnly /* r30 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x8
    int heap; // r31

    // References
    // -> class Debug TheDebug;
    // -> class CriticalSection * gMemLock;
}

// Range: 0x80614BA4 -> 0x80614BDC
void MemTrackStartLog() {
    // References
    // -> class Debug TheDebug;
    // -> class MemTracker * gMemTracker;
}

// Range: 0x80614BDC -> 0x80614C04
void MemTrackStopLog() {
    // References
    // -> class MemTracker * gMemTracker;
}

// Range: 0x80614C04 -> 0x80614C40
static class DataNode MemTrackReportDF() {}

// Range: 0x80614C40 -> 0x80614C7C
static class DataNode MemTrackHeapDumpDF() {}

// Range: 0x80614C7C -> 0x80614CE4
static class DataNode MemTrackLogDF(class DataArray * array /* r31 */) {}

// Range: 0x80614CE4 -> 0x80614CE8
void * DebugHeapAlloc() {}

// Range: 0x80614CE8 -> 0x80614CEC
void DebugHeapFree() {}


