/*
    Compile unit: C:\rockband2\system\src\os\Debug.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805AE980 -> 0x805AF400
*/
const char * kAssertStr; // size: 0x4, address: 0x80A477D8
class Debug TheDebug; // size: 0xFC, address: 0x809847B4
class DebugNotifier TheDebugNotifier; // size: 0x1, address: 0x80A549B0
class DebugFailer TheDebugFailer; // size: 0x1, address: 0x80A549B4
long TheDebugJump[100]; // size: 0x190, address: 0x809848B0
// Range: 0x805AE980 -> 0x805AE9A4
void (* Debug::SetModalCallback(class Debug * const this /* r5 */))(unsigned char &, char *, unsigned char) {
    // Local variables
    void (* old)(unsigned char &, char *, unsigned char); // r0
}

// Range: 0x805AE9A4 -> 0x805AEA54
void Debug::Init(class Debug * const this /* r31 */) {
    // Local variables
    const char * log; // r4
    const char * log; // r4
}

// Range: 0x805AEA54 -> 0x805AEAF0
void Debug::Poll(class Debug * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct OSThread * gMainThreadID;
}

// Range: 0x805AEAF0 -> 0x805AEB90
static void DebugModal(unsigned char & fail /* r29 */, char * msg /* r30 */, unsigned char wait /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805AEB90 -> 0x805AEBC4
void Debug::SetTry() {}

// Range: 0x805AEBC4 -> 0x805AEC70
void Debug::Notify(class Debug * const this /* r29 */, const char * msg /* r30 */) {
    // Local variables
    unsigned char fail; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct OSThread * gMainThreadID;
}

// Range: 0x805AEC70 -> 0x805AED9C
void Debug::Fail(class Debug * const this /* r29 */, const char * msg /* r30 */) {
    // Local variables
    struct _List_iterator i; // r1+0x18
    unsigned char fail; // r1+0x8

    // References
    // -> struct OSThread * gMainThreadID;
    // -> long TheDebugJump[100];
}

// Range: 0x805AED9C -> 0x805AEF10
void Debug::Modal(class Debug * const this /* r29 */, unsigned char & fail /* r30 */, const char * msg /* r31 */) {
    // Local variables
    char buf[4096]; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> class AppChild * TheAppChild;
}

// Range: 0x805AEF10 -> 0x805AEFEC
void Debug::Exit(class Debug * const this /* r31 */, int err /* r29 */, unsigned char call_exit /* r30 */) {
    // Local variables
    struct _List_iterator i; // r1+0x14

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805AEFEC -> 0x805AF08C
void Debug::RemoveExitCallback(void (* f)() /* r31 */) {}

// Range: 0x805AF08C -> 0x805AF148
void Debug::Print(class Debug * const this /* r30 */, const char * msg /* r31 */) {}

// Range: 0x805AF148 -> 0x805AF23C
void Debug::StartLog(class Debug * const this /* r29 */, const char * file /* r30 */, unsigned char always_flush /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805AF23C -> 0x805AF290
void Debug::StopLog(class Debug * const this /* r31 */) {}

// Range: 0x805AF290 -> 0x805AF338
void * Debug::Debug(class Debug * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__5Debug;
}

// Range: 0x805AF338 -> 0x805AF3B8
void * Debug::~Debug(class Debug * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__5Debug;
}

struct {
    // total size: 0x10
} __vt__5Debug; // size: 0x10, address: 0x80923340
struct {
    // total size: 0x8
} __RTTI__5Debug; // size: 0x8, address: 0x80923368
// Range: 0x805AF3B8 -> 0x805AF400
static void __sinit_\Debug_cpp() {
    // References
    // -> class Debug TheDebug;
}

class AppChild {
    // total size: 0xC
    unsigned char mEnabled; // offset 0x0, size 0x1
    class BinStream * mStream; // offset 0x4, size 0x4
    unsigned char mSync; // offset 0x8, size 0x1
};

