/*
    Compile unit: C:\rockband2\system\src\os\HolmesClient.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805CE8CC -> 0x805CF430
*/
static class CriticalSection gCrit; // size: 0x1C, address: 0x80988C74
static class BinStream * gStream; // size: 0x4, address: 0x80A54E20
static class MemStream * gStreamBuffer; // size: 0x4, address: 0x80A54E24
class list : public _List_base {
    // total size: 0x8
};
static class list gRequests; // size: 0x8, address: 0x80988CA0
// Range: 0x805CE8CC -> 0x805CE98C
static void CheckReads() {
    // Local variables
    int act; // r30

    // References
    // -> static class list gRequests;
    // -> static class BinStream * gStream;
}

// Range: 0x805CE98C -> 0x805CE9E8
static void WaitForReads() {
    // Local variables
    class CritSecTracker __cst; // r1+0x8

    // References
    // -> static class list gRequests;
    // -> static class CriticalSection gCrit;
}

// Range: 0x805CE9E8 -> 0x805CEA38
static void HolmesFlushStreamBuffer() {
    // References
    // -> static class BinStream * gStream;
    // -> static class MemStream * gStreamBuffer;
}

// Range: 0x805CEA38 -> 0x805CEBC0
void HolmesClientInit() {
    // Local variables
    unsigned char failed; // r30
    int server_ver; // r1+0x10

    // References
    // -> static class MemStream * gStreamBuffer;
    // -> static class BinStream * gStream;
    // -> unsigned char gHostLogging;
    // -> unsigned char gHostConfig;
}

// Range: 0x805CEBC0 -> 0x805CEC04
void HolmesClientPoll() {
    // Local variables
    class CritSecTracker __cst; // r1+0x8

    // References
    // -> static class CriticalSection gCrit;
}

// Range: 0x805CEC04 -> 0x805CECF4
void HolmesClientTerminate() {
    // Local variables
    class CritSecTracker __cst; // r1+0xC

    // References
    // -> static class MemStream * gStreamBuffer;
    // -> static class BinStream * gStream;
    // -> static class CriticalSection gCrit;
}

// Range: 0x805CECF4 -> 0x805CEEF4
unsigned char HolmesClientOpen(const char * filename /* r25 */, int mode /* r27 */, unsigned int & file_size /* r31 */, int & file_handle /* r26 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x10
    unsigned char read; // r0
    unsigned char creat; // r0
    unsigned char trunc; // r0
    unsigned int size; // r1+0xC

    // References
    // -> static class MemStream * gStreamBuffer;
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> unsigned char gHostConfig;
    // -> static class BinStream * gStream;
    // -> unsigned char gHostLogging;
    // -> static class CriticalSection gCrit;
}

// Range: 0x805CEEF4 -> 0x805CF074
int HolmesClientWrite(int file_handle /* r28 */, int start /* r31 */, int bytes /* r29 */, void * buf /* r30 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x1C
    int ret; // r1+0x18

    // References
    // -> static class MemStream * gStreamBuffer;
    // -> unsigned char gHostLogging;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class BinStream * gStream;
    // -> static class CriticalSection gCrit;
}

struct ReadRequest {
    // total size: 0xC
    class File * mRequestor; // offset 0x0, size 0x4
    char * mBuffer; // offset 0x4, size 0x4
    int mBytes; // offset 0x8, size 0x4
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std55_List_node<Q226@unnamed@HolmesClient_cpp@11ReadRequest>; // size: 0x8, address: 0x80926FF0
// Range: 0x805CF074 -> 0x805CF1E8
void HolmesClientRead(int file_handle /* r27 */, int start /* r31 */, int bytes /* r28 */, void * buf /* r29 */, class File * requestor /* r30 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x1C
    struct ReadRequest req; // r1+0x20

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std55_List_node<Q226@unnamed@HolmesClient_cpp@11ReadRequest>;
    // -> unsigned char gStlAllocNameLookup;
    // -> static class list gRequests;
    // -> static class MemStream * gStreamBuffer;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class BinStream * gStream;
    // -> static class CriticalSection gCrit;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x805CF1E8 -> 0x805CF29C
unsigned char HolmesClientReadDone(class File * f /* r31 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x14
    struct _List_iterator itr; // r1+0x10

    // References
    // -> static class list gRequests;
    // -> static class CriticalSection gCrit;
}

// Range: 0x805CF29C -> 0x805CF3B0
void HolmesClientClose(class File * f /* r30 */, int file_handle /* r31 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x1C
    struct _List_iterator itr; // r1+0x18

    // References
    // -> static class MemStream * gStreamBuffer;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class BinStream * gStream;
    // -> static class list gRequests;
    // -> static class CriticalSection gCrit;
}

struct {
    // total size: 0x8
} __RTTI__P11RecurseInfo; // size: 0x8, address: 0x80927008
// Range: 0x805CF3B0 -> 0x805CF430
static void __sinit_\HolmesClient_cpp() {
    // References
    // -> static class list gRequests;
    // -> static class CriticalSection gCrit;
}

class _List_node : public _List_node_base {
    // total size: 0x14
public:
    struct ReadRequest _M_data; // offset 0x8, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};

