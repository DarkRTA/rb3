/*
    Compile unit: C:\rockband2\system\src\utl\MakeString.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x806105A0 -> 0x80611750
*/
static class CriticalSection * gLock; // size: 0x4, address: 0x80A55458
static char * * * gBuf; // size: 0x4, address: 0x80A5545C
static int gNum[1]; // size: 0x4, address: 0x80A55460
static struct OSThread * gThreadIds[1]; // size: 0x4, address: 0x80A55464
static int gCurThread; // size: 0x4, address: 0x80A55468
static int gNumThreads; // size: 0x4, address: 0x80A5546C
// Range: 0x806105A0 -> 0x806107C8
static char * NextBuf() {
    // Local variables
    class CritSecTracker __cst; // r1+0x8
    int i; // r29
    int j; // r28
    int cur; // r28
    char * buf; // r28

    // References
    // -> static int gNum[1];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static int gCurThread;
    // -> static struct OSThread * gThreadIds[1];
    // -> static int gNumThreads;
    // -> static char * * * gBuf;
    // -> static class CriticalSection * gLock;
}

// Range: 0x806107C8 -> 0x8061084C
void TerminateMakeString() {
    // Local variables
    int i; // r31
    int j; // r30

    // References
    // -> static char * * * gBuf;
}

// Range: 0x8061084C -> 0x8061091C
void * FormatString::FormatString(class FormatString * const this /* r30 */, const char * fmt /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

enum /* @enum$6182MakeString_cpp */ {
    kInit = 0,
    kUnknown = 1,
    kKnown = 2,
};
// Range: 0x8061091C -> 0x80610A48
void FormatString::UpdateType(class FormatString * const this /* r29 */) {
    // Local variables
    enum /* @enum$6182MakeString_cpp */ {
        kInit = 0,
        kUnknown = 1,
        kKnown = 2,
    } state; // r31
    char * i; // r30

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80610A48 -> 0x80610B3C
class FormatString & FormatString::__ls(class FormatString * const this /* r28 */, void * i /* r31 */) {
    // Local variables
    char c; // r29
    int n; // r0

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x80610B3C -> 0x80610C30
class FormatString & FormatString::__ls(class FormatString * const this /* r28 */, unsigned int i /* r31 */) {
    // Local variables
    char c; // r29
    int n; // r0

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x80610C30 -> 0x80610D24
class FormatString & FormatString::__ls(class FormatString * const this /* r28 */, unsigned long i /* r31 */) {
    // Local variables
    char c; // r29
    int n; // r0

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x80610D24 -> 0x80610E18
class FormatString & FormatString::__ls(class FormatString * const this /* r28 */, long i /* r31 */) {
    // Local variables
    char c; // r29
    int n; // r0

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x80610E18 -> 0x80610F04
class FormatString & FormatString::__ls(class FormatString * const this /* r27 */, unsigned long long i /* r31 */) {
    // Local variables
    char c; // r29
    int n; // r0

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x80610F04 -> 0x80610FF0
class FormatString & FormatString::__ls(class FormatString * const this /* r27 */, long long i /* r31 */) {
    // Local variables
    char c; // r29
    int n; // r0

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x80610FF0 -> 0x806110E4
class FormatString & FormatString::__ls(class FormatString * const this /* r28 */, int i /* r31 */) {
    // Local variables
    char c; // r29
    int n; // r0

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x806110E4 -> 0x80611268
class FormatString & FormatString::__ls(class FormatString * const this /* r31 */) {
    // Local variables
    char c; // r28
    int n; // r29

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x80611268 -> 0x806113A8
class FormatString & FormatString::__ls(class FormatString * const this /* r28 */, const char * i /* r31 */) {
    // Local variables
    char c; // r29
    int n; // r0

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x806113A8 -> 0x806114A4
class FormatString & FormatString::__ls(class FormatString * const this /* r28 */, float i /* f31 */) {
    // Local variables
    char c; // r29
    int n; // r0

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x806114A4 -> 0x80611598
class FormatString & FormatString::__ls(class FormatString * const this /* r28 */, const class String & i /* r31 */) {
    // Local variables
    char c; // r29
    int n; // r0

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x80611598 -> 0x8061168C
class FormatString & FormatString::__ls(class FormatString * const this /* r28 */, class Symbol & i /* r31 */) {
    // Local variables
    char c; // r29
    int n; // r0

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x8061168C -> 0x80611750
char * FormatString::Str(class FormatString * const this /* r30 */) {
    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}


