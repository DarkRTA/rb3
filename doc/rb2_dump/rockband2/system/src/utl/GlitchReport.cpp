/*
    Compile unit: C:\rockband2\system\src\utl\GlitchReport.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80609454 -> 0x8060A408
*/
class DataArray * types; // size: 0x4, address: 0x80A55420
// Range: 0x80609454 -> 0x806094D0
void * GlitchReport::GlitchReport(class GlitchReport * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__12GlitchReport;
}

// Range: 0x806094D0 -> 0x806096B0
void * GlitchReport::~GlitchReport(class GlitchReport * const this /* r30 */) {}

// Range: 0x806096B0 -> 0x80609804
void GlitchReport::AddGlitch(class GlitchReport * const this /* r31 */) {
    // Local variables
    float glitchMs; // f2
    const class SongPos & p; // r0
    int i; // r6
    struct Glitch * g; // r30
    int j; // r7

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x80609804 -> 0x806099C4
unsigned char GlitchReport::Poll(class GlitchReport * const this /* r31 */) {
    // Local variables
    float frameMs; // f0

    // References
    // -> class Rnd & TheRnd;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

// Range: 0x806099C4 -> 0x80609B9C
void GlitchReport::AddGlitchEvent(class GlitchReport * const this /* r28 */, const class String & s /* r29 */) {
    // Local variables
    int i; // r30
    struct GlitchEvent ge; // r1+0x10
    int count; // r31
    int i; // r30
    struct Glitch * g; // r27
    int j; // r26
}

// Range: 0x80609B9C -> 0x80609D58
void GlitchReport::ProcessGlitch(struct Glitch * g /* r28 */) {
    // Local variables
    int i; // r31
    class String & s; // r30
    int j; // r29
    char buffer[256]; // r1+0x18
    char * dest; // r4
    char last; // r5
    const char * c; // r6
    char cur; // r3
}

// Range: 0x80609D58 -> 0x80609F0C
void GlitchReport::ProcessReport(class GlitchReport * const this /* r30 */) {
    // Local variables
    int i; // r28
    struct Glitch * g; // r4
    int i; // r31
    struct Glitch * g; // r28
    int j; // r29
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct binary_function {
    // total size: 0x1
};
struct __stlport_class {
    // total size: 0x1
};
struct less : public binary_function, public __stlport_class {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x80609F0C -> 0x80609F1C
void GlitchReport::StopReport() {}

static class Symbol _s; // size: 0x4, address: 0x80A55428
static class Symbol _s; // size: 0x4, address: 0x80A55430
// Range: 0x80609F1C -> 0x8060A408
class DataNode GlitchReport::Handle(class GlitchReport * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x50
    class String s; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x54
} __vt__12GlitchReport; // size: 0x54, address: 0x8092C280
struct {
    // total size: 0x8
} __RTTI__PQ212GlitchReport11GlitchEvent; // size: 0x8, address: 0x8092C350
struct {
    // total size: 0x8
} __RTTI__PPQ212GlitchReport6Glitch; // size: 0x8, address: 0x8092C388
struct _OKToMemCpy {
    // total size: 0x1
};

