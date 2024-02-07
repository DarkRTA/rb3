/*
    Compile unit: C:\rockband2\system\src\rndobj\Console.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804786A0 -> 0x804799B4
*/
static class RndConsole * gConsole; // size: 0x4, address: 0x80A52A68
// Range: 0x804786A0 -> 0x804786DC
static class DataNode DataContinue() {
    // References
    // -> static class RndConsole * gConsole;
}

// Range: 0x804786DC -> 0x80478718
static class DataNode DataBreak() {
    // References
    // -> static class RndConsole * gConsole;
}

// Range: 0x80478718 -> 0x80478758
static class DataNode DataStep() {
    // References
    // -> static class RndConsole * gConsole;
}

// Range: 0x80478758 -> 0x80478798
static class DataNode DataNext() {
    // References
    // -> static class RndConsole * gConsole;
}

// Range: 0x80478798 -> 0x804787D8
static class DataNode DataFinish() {
    // References
    // -> static class RndConsole * gConsole;
}

// Range: 0x804787D8 -> 0x80478814
static class DataNode DataList() {
    // References
    // -> static class RndConsole * gConsole;
}

// Range: 0x80478814 -> 0x80478850
static class DataNode DataWhere() {
    // References
    // -> static class RndConsole * gConsole;
}

// Range: 0x80478850 -> 0x8047888C
static class DataNode DataSetBreak() {
    // References
    // -> static class RndConsole * gConsole;
}

// Range: 0x8047888C -> 0x804788C8
static class DataNode DataBreakpoints() {
    // References
    // -> static class RndConsole * gConsole;
}

// Range: 0x804788C8 -> 0x804789B8
static class DataNode DataClear(class DataArray * a /* r31 */) {
    // Local variables
    int n; // r4

    // References
    // -> static class RndConsole * gConsole;
    // -> const char * gNullStr;
}

// Range: 0x804789B8 -> 0x804789C8
static class DataNode DataNop() {}

// Range: 0x804789C8 -> 0x80478A08
static class DataNode DataUp() {
    // References
    // -> static class RndConsole * gConsole;
}

// Range: 0x80478A08 -> 0x80478A48
static class DataNode DataDown() {
    // References
    // -> static class RndConsole * gConsole;
}

// Range: 0x80478A48 -> 0x80478ADC
static class DataNode DataHelp(class DataArray * a /* r31 */) {
    // References
    // -> static class RndConsole * gConsole;
}

struct Breakpoint {
    // total size: 0x8
    class DataArray * parent; // offset 0x0, size 0x4
    int index; // offset 0x4, size 0x4
};
// Range: 0x80478ADC -> 0x80478BA8
void * Breakpoint::~Breakpoint(struct Breakpoint * const this /* r29 */) {}

class RndConsole : public Object {
    // total size: 0x64
    unsigned char mShowing; // offset 0x28, size 0x1
    class RndOverlay * mOutput; // offset 0x2C, size 0x4
    class RndOverlay * mInput; // offset 0x30, size 0x4
    class list mBuffer; // offset 0x34, size 0x8
    struct _List_iterator mBufPtr; // offset 0x3C, size 0x4
    int mMaxBuffer; // offset 0x40, size 0x4
    int mTabLen; // offset 0x44, size 0x4
    int mCursor; // offset 0x48, size 0x4
    class Object * mKeyboardOverride; // offset 0x4C, size 0x4
    unsigned char mPumpMsgs; // offset 0x50, size 0x1
    class DataArray * mDebugging; // offset 0x54, size 0x4
    int mLevel; // offset 0x58, size 0x4
    class list mBreakpoints; // offset 0x5C, size 0x8
};
// Range: 0x80478BA8 -> 0x80478C60
void RndConsole::MoveLevel() {
    // References
    // -> class Debug TheDebug;
    // -> class DataArray * gCallStack[100];
    // -> class DataArray * * gCallStackPtr;
}

// Range: 0x80478C60 -> 0x80478E5C
void RndConsole::InsertBreak(class RndConsole * const this /* r28 */, class DataArray * a /* r29 */, int i /* r30 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std38_List_node<Q210RndConsole10Breakpoint>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std38_List_node<Q210RndConsole10Breakpoint>; // size: 0x8, address: 0x808F2C90
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class _List_node : public _List_node_base {
    // total size: 0x10
public:
    struct Breakpoint _M_data; // offset 0x8, size 0x8
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
class list : public _List_base {
    // total size: 0x8
};
// Range: 0x80478E5C -> 0x80478EF8
void * RndConsole::~RndConsole(class RndConsole * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__10RndConsole;
}

// Range: 0x80478EF8 -> 0x80478FA8
void RndConsole::SetShowing(class RndConsole * const this /* r30 */, unsigned char s /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80478FA8 -> 0x80479608
unsigned char RndConsole::OnMsg(class RndConsole * const this /* r30 */, const class KeyboardKeyMsg & msg /* r31 */) {
    // Local variables
    struct _List_iterator end; // r1+0x68
    class String & s; // r3
    class String & s; // r29
    const char * _err; // r29
    char buffer[2]; // r1+0x8

    // References
    // -> long TheDebugJump[100];
    // -> class Debug TheDebug;
}

// Range: 0x80479608 -> 0x804799B4
void RndConsole::ExecuteLine(class RndConsole * const this /* r30 */) {
    // Local variables
    class String & s; // r31
    class DataNode cmd; // r1+0x50
    class DataNode ret; // r1+0x48

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6String>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
}

struct {
    // total size: 0xC
} __vt__14KeyboardKeyMsg; // size: 0xC, address: 0x808F32E0
struct {
    // total size: 0x8
} __RTTI__14KeyboardKeyMsg; // size: 0x8, address: 0x808F3308
struct {
    // total size: 0x54
} __vt__10RndConsole; // size: 0x54, address: 0x808F3330
struct {
    // total size: 0x8
} __RTTI__10RndConsole; // size: 0x8, address: 0x808F33A8

