/*
    Compile unit: C:\rockband2\system\src\os\ThreadCall_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805CA290 -> 0x805CA394
*/
struct OSThread * gMainThreadID; // size: 0x4, address: 0x80A54D88
struct ThreadCallData {
    // total size: 0x14
    enum ThreadCallDataType mType; // offset 0x0, size 0x4
    int (* mFunc)(); // offset 0x4, size 0x4
    void (* mCallback)(int); // offset 0x8, size 0x4
    class ThreadCallback * mClass; // offset 0xC, size 0x4
    int mArg; // offset 0x10, size 0x4
};
static struct ThreadCallData gData; // size: 0x14, address: 0x80988BA8
// Range: 0x805CA290 -> 0x805CA2B4
void ThreadCallInit() {
    // References
    // -> static struct ThreadCallData gData;
}

// Range: 0x805CA2B4 -> 0x805CA2B8
void ThreadCallTerminate() {}

enum ThreadCallDataType {
    kTCDT_None = 0,
    kTCDT_Func = 1,
    kTCDT_Class = 2,
};
// Range: 0x805CA2B8 -> 0x805CA394
void ThreadCallPoll() {
    // Local variables
    enum ThreadCallDataType cdt; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static struct ThreadCallData gData;
}


