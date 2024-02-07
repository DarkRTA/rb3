/*
    Compile unit: C:\rockband2\system\src\os\WiiNetInit.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805CC24C -> 0x805CCC64
*/
class CriticalSection gCrit; // size: 0x1C, address: 0x80988C04
unsigned char gThreadRunning; // size: 0x1, address: 0x80A54DE8
unsigned char gDisconnectionRunning; // size: 0x1, address: 0x80A54DE9
unsigned char gDNSRunning; // size: 0x1, address: 0x80A54DEA
const char * gDNSRequest; // size: 0x4, address: 0x80A54DEC
static int _x; // size: 0x4, address: 0x80A54DF0
// Range: 0x805CC24C -> 0x805CC2FC
void * NetAllocFunc(unsigned long size /* r30 */, int align /* r31 */) {
    // Local variables
    void * ptr; // r31
    class CritSecTracker __cst; // r1+0x8

    // References
    // -> static int _x;
    // -> class CriticalSection gCrit;
}

// Range: 0x805CC2FC -> 0x805CC360
void NetFreeFunc(void * ptr /* r31 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x8

    // References
    // -> class CriticalSection gCrit;
}

// Range: 0x805CC360 -> 0x805CC368
void * _NetAlloc() {}

// Range: 0x805CC368 -> 0x805CC36C
void _NetFree() {}

struct SOLibraryConfig {
    // total size: 0x8
    void * (* alloc)(unsigned long, long); // offset 0x0, size 0x4
    void (* free)(unsigned long, void *, long); // offset 0x4, size 0x4
};
// Range: 0x805CC36C -> 0x805CC4C4
void * ConnectionThread(void * param /* r30 */) {
    // Local variables
    int * result; // r0
    long rc; // r4
    struct SOLibraryConfig soLibConfig; // r1+0x8

    // References
    // -> unsigned char gThreadRunning;
}

// Range: 0x805CC4C4 -> 0x805CC594
void * DisconnectionThread() {
    // Local variables
    int ret; // r31

    // References
    // -> unsigned char gDisconnectionRunning;
}

struct SOHostEnt {
    // total size: 0x10
    char * name; // offset 0x0, size 0x4
    char * * aliases; // offset 0x4, size 0x4
    signed short addrType; // offset 0x8, size 0x2
    signed short length; // offset 0xA, size 0x2
    unsigned char * * addrList; // offset 0xC, size 0x4
};
// Range: 0x805CC594 -> 0x805CC67C
void * DNSThread() {
    // Local variables
    class String * result; // r31
    struct SOHostEnt * ret; // r0
    char ip[16]; // r1+0x8
    unsigned char * addr; // r30
    signed short length; // r29
    int i; // r28

    // References
    // -> const char * gDNSRequest;
    // -> unsigned char gDNSRunning;
}

// Range: 0x805CC67C -> 0x805CC6CC
void * WiiNetInit::WiiNetInit(class WiiNetInit * const this /* r30 */) {
    // References
    // -> unsigned char gDisconnectionRunning;
    // -> unsigned char gThreadRunning;
}

// Range: 0x805CC6CC -> 0x805CC730
void * WiiNetInit::~WiiNetInit(class WiiNetInit * const this /* r30 */) {}

// Range: 0x805CC730 -> 0x805CC7C4
unsigned char WiiNetInit::NetConnect_Start(class WiiNetInit * const this /* r31 */) {
    // References
    // -> unsigned char gDisconnectionRunning;
}

// Range: 0x805CC7C4 -> 0x805CC870
unsigned char WiiNetInit::NetConnect_IsFinished(class WiiNetInit * const this /* r31 */) {
    // References
    // -> unsigned char gDisconnectionRunning;
    // -> unsigned char gThreadRunning;
}

// Range: 0x805CC870 -> 0x805CC8E4
void WiiNetInit::NetConnect_Close(class WiiNetInit * const this /* r31 */) {
    // References
    // -> unsigned char gDisconnectionRunning;
}

// Range: 0x805CC8E4 -> 0x805CC9C0
unsigned char WiiNetInit::StartProfanity(class WiiNetInit * const this /* r30 */, const char * username /* r31 */) {
    // Local variables
    int iStringLength; // r0
    int i; // r6

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805CC9C0 -> 0x805CCAE0
unsigned char WiiNetInit::CheckProfanity(class WiiNetInit * const this /* r29 */, unsigned char & result /* r30 */, unsigned char & fail /* r31 */) {
    // Local variables
    int i; // r4

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805CCAE0 -> 0x805CCB50
unsigned char WiiNetInit::StartDNSLookup(class WiiNetInit * const this /* r31 */) {
    // References
    // -> const char * gDNSRequest;
    // -> unsigned char gDNSRunning;
}

// Range: 0x805CCB50 -> 0x805CCB94
unsigned char WiiNetInit::CheckDNSLookup(class WiiNetInit * const this /* r5 */) {
    // References
    // -> unsigned char gDNSRunning;
}

// Range: 0x805CCB94 -> 0x805CCBCC
void WiiNetInit::KillDNSLookup() {
    // References
    // -> unsigned char gDNSRunning;
}

// Range: 0x805CCBCC -> 0x805CCC1C
int WiiNetInit::GetLastDWCError() {
    // Local variables
    int error; // r1+0x8

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805CCC1C -> 0x805CCC64
static void __sinit_\WiiNetInit_cpp() {
    // References
    // -> class CriticalSection gCrit;
}


