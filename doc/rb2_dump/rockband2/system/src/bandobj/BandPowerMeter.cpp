/*
    Compile unit: C:\rockband2\system\src\bandobj\BandPowerMeter.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8025897C -> 0x8025B1D4
*/
class DataArray * types; // size: 0x4, address: 0x80A4F100
static class Symbol uninitialized; // size: 0x4, address: 0x80A4F108
// Range: 0x8025897C -> 0x80258D6C
void * BandPowerMeter::BandPowerMeter(class BandPowerMeter * const this /* r31 */) {
    // References
    // -> static class Symbol uninitialized;
    // -> struct [anonymous] __vt__23ObjPtr<3Sfx,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11RndPropAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10RndMatAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__24ObjPtr<4Task,9ObjectDir>;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__14BandPowerMeter;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x80258D6C -> 0x802592F4
void * BandPowerMeter::~BandPowerMeter(class BandPowerMeter * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<11RndPollable,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10RndEnviron,9ObjectDir>;
    // -> struct [anonymous] __vt__24ObjPtr<4Task,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10RndMatAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11RndPropAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> struct [anonymous] __vt__23ObjPtr<3Sfx,9ObjectDir>;
}

// Range: 0x802592F4 -> 0x80259A54
void BandPowerMeter::SyncObjects(class BandPowerMeter * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__3Sfx;
    // -> class Synth * TheSynth;
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> struct [anonymous] __RTTI__11RndPropAnim;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10RndMatAnim;
}

static class Symbol none; // size: 0x4, address: 0x80A4F110
static class Symbol guitar; // size: 0x4, address: 0x80A4F118
// Range: 0x80259A54 -> 0x80259B04
void BandPowerMeter::Reset(class BandPowerMeter * const this /* r31 */) {
    // References
    // -> static class Symbol guitar;
    // -> static class Symbol none;
}

static class Symbol none; // size: 0x4, address: 0x80A4F120
static class Symbol ready; // size: 0x4, address: 0x80A4F128
static class Symbol deploying; // size: 0x4, address: 0x80A4F130
// Range: 0x80259B04 -> 0x80259C9C
void BandPowerMeter::SetEnergy(class BandPowerMeter * const this /* r29 */, float energy /* f31 */, class Symbol & state /* r30 */, class Symbol & instrument /* r31 */) {
    // References
    // -> static class Symbol deploying;
    // -> static class Symbol ready;
    // -> static class Symbol none;
}

static class Symbol guitar; // size: 0x4, address: 0x80A4F138
static class Symbol bass; // size: 0x4, address: 0x80A4F140
static class Symbol drum; // size: 0x4, address: 0x80A4F148
static class Symbol vocals; // size: 0x4, address: 0x80A4F150
// Range: 0x80259C9C -> 0x8025A150
void BandPowerMeter::EnergyReady(class BandPowerMeter * const this /* r27 */, class Symbol & instrument /* r28 */) {
    // Local variables
    float timeTilNext; // r31
    float fraction; // f31
    float slop; // f30
    float bf; // f29
    float til; // f29

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> static class Symbol vocals;
    // -> static class Symbol drum;
    // -> static class Symbol bass;
    // -> static class Symbol guitar;
}

// Range: 0x8025A150 -> 0x8025A170
void BandPowerMeter::EnergyAdded() {}

// Range: 0x8025A170 -> 0x8025A1B8
void BandPowerMeter::Deploy(class BandPowerMeter * const this /* r31 */) {}

// Range: 0x8025A1B8 -> 0x8025A224
void BandPowerMeter::StopDeploy(class BandPowerMeter * const this /* r31 */) {}

// Range: 0x8025A224 -> 0x8025A2A4
void BandPowerMeter::KillBeatTask(class BandPowerMeter * const this /* r31 */) {}

// Range: 0x8025A300 -> 0x8025A320
void BandPowerMeter::SetNoOverdrive() {}

static class Symbol _s; // size: 0x4, address: 0x80A4F158
static class Symbol _s; // size: 0x4, address: 0x80A4F160
static class Symbol _s; // size: 0x4, address: 0x80A4F168
static class Symbol _s; // size: 0x4, address: 0x80A4F170
static class Symbol _s; // size: 0x4, address: 0x80A4F178
static class Symbol _s; // size: 0x4, address: 0x80A4F180
static class Symbol _s; // size: 0x4, address: 0x80A4F188
// Range: 0x8025A320 -> 0x8025AC60
class DataNode BandPowerMeter::Handle(class BandPowerMeter * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x54
    class MessageTimer _mt; // r1+0x60
    class DataNode _n; // r1+0x58

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A4F190
static class Symbol _s; // size: 0x4, address: 0x80A4F198
static class Symbol _s; // size: 0x4, address: 0x80A4F1A0
// Range: 0x8025AC60 -> 0x8025AFE8
unsigned char BandPowerMeter::SyncProperty(class BandPowerMeter * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x8025AFE8 -> 0x8025B02C
void BandPowerMeter::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8025B02C -> 0x8025B13C
void BandPowerMeter::PreLoad(class BandPowerMeter * const this /* r29 */, class BinStream & s /* r30 */) {
    // Local variables
    int rev; // r1+0x10

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8025B13C -> 0x8025B140
void BandPowerMeter::PostLoad() {}

// Range: 0x8025B140 -> 0x8025B1D4
void BandPowerMeter::Copy(class BandPowerMeter * const this /* r29 */, const class Object * o /* r30 */, enum CopyType ct /* r31 */) {
    // Local variables
    const class BandPowerMeter * bpm; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14BandPowerMeter;
}

struct {
    // total size: 0x21C
} __vt__14BandPowerMeter; // size: 0x21C, address: 0x808B53A0
struct {
    // total size: 0x8
} __RTTI__14BandPowerMeter; // size: 0x8, address: 0x808B5620
struct {
    // total size: 0x18
} __vt__23ObjPtr<3Sfx,9ObjectDir>; // size: 0x18, address: 0x808B5628
struct {
    // total size: 0x8
} __RTTI__23ObjPtr<3Sfx,9ObjectDir>; // size: 0x8, address: 0x808B5668
struct {
    // total size: 0x18
} __vt__32ObjPtr<11RndPropAnim,9ObjectDir>; // size: 0x18, address: 0x808B5708
struct {
    // total size: 0x8
} __RTTI__32ObjPtr<11RndPropAnim,9ObjectDir>; // size: 0x8, address: 0x808B5750
struct {
    // total size: 0x18
} __vt__24ObjPtr<4Task,9ObjectDir>; // size: 0x18, address: 0x808B57A8
struct {
    // total size: 0x8
} __RTTI__24ObjPtr<4Task,9ObjectDir>; // size: 0x8, address: 0x808B57E8
struct {
    // total size: 0x8
} __RTTI__4Task; // size: 0x8, address: 0x808B5B58

