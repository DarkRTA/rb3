/*
    Compile unit: C:\rockband2\system\src\bandobj\BandLeadMeter.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802512D0 -> 0x80252814
*/
class DataArray * types; // size: 0x4, address: 0x80A4EF40
// Range: 0x802512D0 -> 0x802515CC
void * BandLeadMeter::BandLeadMeter(class BandLeadMeter * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__34ObjPtr<13RndAnimatable,9ObjectDir>;
    // -> struct [anonymous] __vt__13BandLeadMeter;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x802515CC -> 0x802515EC
enum Color BandLeadMeter::GetColor() {}

// Range: 0x802515EC -> 0x802517B8
void BandLeadMeter::SyncScores(class BandLeadMeter * const this /* r31 */) {
    // Local variables
    enum Color color; // r0
    class RndMat * mat; // r4
    int diff; // r4
    float lead; // f1
    float frame; // f1
}

// Range: 0x802517B8 -> 0x802517EC
void BandLeadMeter::Enter(class BandLeadMeter * const this /* r31 */) {}

// Range: 0x802517EC -> 0x802518A8
void BandLeadMeter::Poll() {
    // References
    // -> class TaskMgr TheTaskMgr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4EF48
// Range: 0x802518A8 -> 0x80251C4C
class DataNode BandLeadMeter::Handle(class BandLeadMeter * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A4EF50
static class Symbol _s; // size: 0x4, address: 0x80A4EF58
static class Symbol _s; // size: 0x4, address: 0x80A4EF60
static class Symbol _s; // size: 0x4, address: 0x80A4EF68
static class Symbol _s; // size: 0x4, address: 0x80A4EF70
static class Symbol _s; // size: 0x4, address: 0x80A4EF78
static class Symbol _s; // size: 0x4, address: 0x80A4EF80
static class Symbol _s; // size: 0x4, address: 0x80A4EF88
static class Symbol _s; // size: 0x4, address: 0x80A4EF90
static class Symbol _s; // size: 0x4, address: 0x80A4EF98
static class Symbol _s; // size: 0x4, address: 0x80A4EFA0
// Range: 0x80251C4C -> 0x802520D8
unsigned char BandLeadMeter::SyncProperty(class BandLeadMeter * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
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
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x802520D8 -> 0x80252228
unsigned char PropSync(class ObjPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80252228 -> 0x8025226C
void BandLeadMeter::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8025226C -> 0x80252420
void BandLeadMeter::PreLoad(class BandLeadMeter * const this /* r30 */, class BinStream & s /* r31 */) {
    // Local variables
    int rev; // r1+0x14
    int tmp; // r1+0x10

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sRevs;
    // -> unsigned char gLoadingProxyFromDisk;
    // -> class Debug TheDebug;
    // -> class Symbol name;
}

// Range: 0x80252420 -> 0x80252530
void BandLeadMeter::PostLoad(class BandLeadMeter * const this /* r29 */, class BinStream & s /* r30 */) {
    // References
    // -> class list sRevs;
}

// Range: 0x80252530 -> 0x80252814
void BandLeadMeter::Copy(class BandLeadMeter * const this /* r31 */, const class Object * o /* r30 */, enum CopyType type /* r29 */) {
    // Local variables
    const class BandLeadMeter * blm; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13BandLeadMeter;
}

struct {
    // total size: 0x21C
} __vt__13BandLeadMeter; // size: 0x21C, address: 0x808B3A70
struct {
    // total size: 0x8
} __RTTI__13BandLeadMeter; // size: 0x8, address: 0x808B3CF0
struct {
    // total size: 0x18
} __vt__34ObjPtr<13RndAnimatable,9ObjectDir>; // size: 0x18, address: 0x808B3D88
struct {
    // total size: 0x8
} __RTTI__34ObjPtr<13RndAnimatable,9ObjectDir>; // size: 0x8, address: 0x808B3DD0

