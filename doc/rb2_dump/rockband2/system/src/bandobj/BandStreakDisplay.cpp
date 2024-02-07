/*
    Compile unit: C:\rockband2\system\src\bandobj\BandStreakDisplay.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80261304 -> 0x80264054
*/
class DataArray * types; // size: 0x4, address: 0x80A4F248
// Range: 0x80261304 -> 0x802619EC
void * BandStreakDisplay::BandStreakDisplay(class BandStreakDisplay * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__27ObjPtr<7RndText,9ObjectDir>;
    // -> struct [anonymous] __vt__34ObjPtr<13RndAnimatable,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10RndMatAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__17BandStreakDisplay;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x802619EC -> 0x80261A4C
void BandStreakDisplay::Reset(class BandStreakDisplay * const this /* r31 */) {}

static class Symbol blow_streak; // size: 0x4, address: 0x80A4F250
// Range: 0x80261A4C -> 0x80261B40
void BandStreakDisplay::Enter(class BandStreakDisplay * const this /* r30 */) {
    // Local variables
    class RndDir * dir; // r0

    // References
    // -> const char * gNullStr;
    // -> static class Symbol blow_streak;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
}

// Range: 0x80261B40 -> 0x80261BC8
void BandStreakDisplay::Exit(class BandStreakDisplay * const this /* r31 */) {
    // Local variables
    class RndDir * dir; // r0

    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
}

// Range: 0x80261BC8 -> 0x80261C64
void BandStreakDisplay::Poll(class BandStreakDisplay * const this /* r30 */) {
    // Local variables
    float time; // f0
    int i; // r31

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x80261C64 -> 0x80261CA8
void BandStreakDisplay::SetIndicator() {}

// Range: 0x80261CA8 -> 0x80261D40
class DataNode BandStreakDisplay::OnBlownStreak(class BandStreakDisplay * const this /* r30 */, class DataArray * msg /* r31 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x80261D40 -> 0x80261D88
enum StreakColor BandStreakDisplay::GetOnColor() {}

// Range: 0x80261D88 -> 0x80262140
void BandStreakDisplay::SyncState(class BandStreakDisplay * const this /* r29 */) {
    // Local variables
    unsigned char allOn; // r6
    enum StreakColor colorOn; // r0
    int i; // r30
    unsigned char on; // r4
    enum StreakColor color; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndText;
}

// Range: 0x80262140 -> 0x802624EC
void BandStreakDisplay::SetColor(class RndMat * mat /* r22 */, enum StreakColor color /* r23 */) {
    // Local variables
    class Color c; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802624EC -> 0x80262518
void BandStreakDisplay::SetInfo() {}

static class Symbol _s; // size: 0x4, address: 0x80A4F258
static class Symbol _s; // size: 0x4, address: 0x80A4F260
static class Symbol _s; // size: 0x4, address: 0x80A4F268
static class Symbol _s; // size: 0x4, address: 0x80A4F270
static class Symbol _s; // size: 0x4, address: 0x80A4F278
static class Symbol _s; // size: 0x4, address: 0x80A4F280
static class Symbol _s; // size: 0x4, address: 0x80A4F288
static class Symbol _s; // size: 0x4, address: 0x80A4F290
static class Symbol _s; // size: 0x4, address: 0x80A4F298
static class Symbol _s; // size: 0x4, address: 0x80A4F2A0
static class Symbol _s; // size: 0x4, address: 0x80A4F2A8
static class Symbol _s; // size: 0x4, address: 0x80A4F2B0
static class Symbol _s; // size: 0x4, address: 0x80A4F2B8
static class Symbol _s; // size: 0x4, address: 0x80A4F2C0
static class Symbol _s; // size: 0x4, address: 0x80A4F2C8
static class Symbol _s; // size: 0x4, address: 0x80A4F2D0
static class Symbol _s; // size: 0x4, address: 0x80A4F2D8
static class Symbol _s; // size: 0x4, address: 0x80A4F2E0
static class Symbol _s; // size: 0x4, address: 0x80A4F2E8
static class Symbol _s; // size: 0x4, address: 0x80A4F2F0
// Range: 0x80262518 -> 0x80262F18
unsigned char BandStreakDisplay::SyncProperty(class BandStreakDisplay * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A4F2F8
static class Symbol _s; // size: 0x4, address: 0x80A4F300
// Range: 0x80262F18 -> 0x80263410
class DataNode BandStreakDisplay::Handle(class BandStreakDisplay * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x80263410 -> 0x80263668
void BandStreakDisplay::PreLoad(class BandStreakDisplay * const this /* r30 */, class BinStream & s /* r31 */) {
    // Local variables
    int rev; // r1+0x1C
    int tmp; // r1+0x18
    int player; // r1+0x14

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sRevs;
    // -> unsigned char gLoadingProxyFromDisk;
    // -> class Debug TheDebug;
}

// Range: 0x80263668 -> 0x802637BC
void BandStreakDisplay::PostLoad(class BandStreakDisplay * const this /* r29 */, class BinStream & s /* r30 */) {
    // Local variables
    int tmp; // r1+0x18

    // References
    // -> class list sRevs;
}

// Range: 0x802637BC -> 0x80263800
void BandStreakDisplay::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80263800 -> 0x80264054
void BandStreakDisplay::Copy(class BandStreakDisplay * const this /* r28 */, const class Object * o /* r26 */, enum CopyType type /* r25 */) {
    // Local variables
    const class BandStreakDisplay * bsd; // r0

    // References
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__17BandStreakDisplay;
}

struct {
    // total size: 0x21C
} __vt__17BandStreakDisplay; // size: 0x21C, address: 0x808B7204
struct {
    // total size: 0x8
} __RTTI__17BandStreakDisplay; // size: 0x8, address: 0x808B7488

