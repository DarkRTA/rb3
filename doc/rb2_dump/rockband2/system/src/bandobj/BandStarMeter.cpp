/*
    Compile unit: C:\rockband2\system\src\bandobj\BandStarMeter.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8025F234 -> 0x80260EF0
*/
class DataArray * types; // size: 0x4, address: 0x80A4F1D8
static float gSpeed; // size: 0x4, address: 0x80A46AA8
// Range: 0x8025F234 -> 0x8025F48C
void * BandStarMeter::BandStarMeter(class BandStarMeter * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__34ObjPtr<13RndAnimatable,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
    // -> struct [anonymous] __vt__13BandStarMeter;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x8025F48C -> 0x8025F900
void * BandStarMeter::~BandStarMeter(class BandStarMeter * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<11RndPollable,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10RndEnviron,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
    // -> struct [anonymous] __vt__34ObjPtr<13RndAnimatable,9ObjectDir>;
}

static class Symbol sp_engage; // size: 0x4, address: 0x80A4F1E0
// Range: 0x8025F900 -> 0x8025F9CC
void BandStarMeter::Enter(class BandStarMeter * const this /* r30 */) {
    // Local variables
    class RndDir * dir; // r0

    // References
    // -> const char * gNullStr;
    // -> static class Symbol sp_engage;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
}

// Range: 0x8025F9CC -> 0x8025FA58
void BandStarMeter::Exit(class BandStarMeter * const this /* r31 */) {
    // Local variables
    class RndDir * dir; // r0

    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
}

// Range: 0x8025FA58 -> 0x8025FC9C
void BandStarMeter::Poll(class BandStarMeter * const this /* r30 */) {
    // Local variables
    float ms; // f31
    float dt; // f30
    float frame; // f29
    unsigned char chasing; // r31

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x8025FC9C -> 0x8025FD0C
void BandStarMeter::PollReadyGroup() {}

// Range: 0x8025FD0C -> 0x8025FD98
void BandStarMeter::ChaseValue(float target /* r1+0x8 */) {
    // Local variables
    float delta; // f3

    // References
    // -> static float gSpeed;
}

// Range: 0x8025FD98 -> 0x8025FE38
class DataNode BandStarMeter::OnEngage(class BandStarMeter * const this /* r29 */, class DataArray * msg /* r30 */) {
    // Local variables
    unsigned char engage; // r0
}

static class Symbol _s; // size: 0x4, address: 0x80A4F1E8
// Range: 0x8025FE38 -> 0x80260254
class DataNode BandStarMeter::Handle(class BandStarMeter * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x38
    class DataNode r; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A4F1F0
static class Symbol _s; // size: 0x4, address: 0x80A4F1F8
static class Symbol _s; // size: 0x4, address: 0x80A4F200
static class Symbol _s; // size: 0x4, address: 0x80A4F208
static class Symbol _s; // size: 0x4, address: 0x80A4F210
static class Symbol _s; // size: 0x4, address: 0x80A4F218
static class Symbol _s; // size: 0x4, address: 0x80A4F220
static class Symbol _s; // size: 0x4, address: 0x80A4F228
static class Symbol _s; // size: 0x4, address: 0x80A4F230
static class Symbol _s; // size: 0x4, address: 0x80A4F238
static class Symbol _s; // size: 0x4, address: 0x80A4F240
// Range: 0x80260254 -> 0x80260990
unsigned char BandStarMeter::SyncProperty(class BandStarMeter * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
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
}

// Range: 0x80260990 -> 0x80260B90
void BandStarMeter::Copy(class BandStarMeter * const this /* r31 */, const class Object * o /* r30 */, enum CopyType type /* r29 */) {
    // Local variables
    const class BandStarMeter * sm; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13BandStarMeter;
}

// Range: 0x80260B90 -> 0x80260BD4
void BandStarMeter::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80260BD4 -> 0x80260E6C
void BandStarMeter::PreLoad(class BandStarMeter * const this /* r30 */, class BinStream & s /* r31 */) {
    // Local variables
    int rev; // r1+0x20
    float val; // r1+0x1C
    int tmp; // r1+0x18
    int tmp; // r1+0x14

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sRevs;
    // -> unsigned char gLoadingProxyFromDisk;
    // -> class Debug TheDebug;
}

// Range: 0x80260E6C -> 0x80260EF0
void BandStarMeter::PostLoad(class BandStarMeter * const this /* r29 */, class BinStream & s /* r30 */) {
    // References
    // -> class list sRevs;
}

struct {
    // total size: 0x21C
} __vt__13BandStarMeter; // size: 0x21C, address: 0x808B67CC
struct {
    // total size: 0x8
} __RTTI__13BandStarMeter; // size: 0x8, address: 0x808B6A50

