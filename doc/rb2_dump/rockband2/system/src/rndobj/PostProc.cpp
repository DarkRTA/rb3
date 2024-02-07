/*
    Compile unit: C:\rockband2\system\src\rndobj\PostProc.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804E3A70 -> 0x804E70D4
*/
class DataArray * types; // size: 0x4, address: 0x80A535E8
class RndPostProc * sCurrent; // size: 0x4, address: 0x80A535F0
class DOFOverrideParams sDOFOverride; // size: 0x1C, address: 0x80980430
// Range: 0x804E3A70 -> 0x804E3BE4
void * RndPostProc::RndPostProc(class RndPostProc * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> struct [anonymous] __vt__11RndPostProc;
}

static class Message msg; // size: 0x8, address: 0x80980458
// Range: 0x804E3BE4 -> 0x804E3DF4
void * RndPostProc::~RndPostProc(class RndPostProc * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Rnd & TheRnd;
    // -> class RndPostProc * sCurrent;
    // -> struct [anonymous] __vt__11RndPostProc;
}

static class Message msg; // size: 0x8, address: 0x80980470
static class Message msg; // size: 0x8, address: 0x80980488
// Range: 0x804E3DF4 -> 0x804E409C
void RndPostProc::Select(class RndPostProc * const this /* r30 */) {
    // References
    // -> static class Message msg;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Rnd & TheRnd;
    // -> class RndPostProc * sCurrent;
}

static class Message msg; // size: 0x8, address: 0x809804A0
// Range: 0x804E409C -> 0x804E4208
void RndPostProc::Reset() {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Rnd & TheRnd;
    // -> class RndPostProc * sCurrent;
}

// Range: 0x804E4208 -> 0x804E4210
class RndPostProc * RndPostProc::Current() {
    // References
    // -> class RndPostProc * sCurrent;
}

// Range: 0x804E4210 -> 0x804E4214
void RndPostProc::EndWorld() {}

// Range: 0x804E4214 -> 0x804E4288
void RndPostProc::UpdateTimeDelta(class RndPostProc * const this /* r31 */) {
    // Local variables
    float secs; // f0

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x804E4288 -> 0x804E42C4
void RndPostProc::DoPost(class RndPostProc * const this /* r31 */) {}

// Range: 0x804E42C4 -> 0x804E43E0
void RndPostProc::UpdateModulation(class RndPostProc * const this /* r31 */) {
    // Local variables
    float parm; // f0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804E43E0 -> 0x804E4410
unsigned char RndPostProc::BlendPrevious() {}

// Range: 0x804E4410 -> 0x804E44A0
void RndPostProc::UpdateBlendPrevious(class RndPostProc * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804E44A0 -> 0x804E44BC
unsigned char RndPostProc::HallOfTime() {}

// Range: 0x804E44BC -> 0x804E46A4
unsigned char RndPostProc::ColorXfmEnabled() {}

// Range: 0x804E46A4 -> 0x804E46DC
unsigned char RndPostProc::Distort() {}

// Range: 0x804E46DC -> 0x804E4720
void RndPostProc::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x804E4720 -> 0x804E4A14
void RndPostProc::Copy(class RndPostProc * const this /* r30 */, const class Object * o /* r29 */) {
    // Local variables
    const class RndPostProc * m; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndPostProc;
}

// Range: 0x804E4A14 -> 0x804E4BA0
void RndPostProc::Load(class RndPostProc * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int rev; // r1+0x20
    int dRev; // r1+0x1C
    class Sphere sphere; // r1+0x30
    float order; // r1+0x18

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x804E4BA0 -> 0x804E52D4
void RndPostProc::LoadRev(class RndPostProc * const this /* r28 */, class BinStream & d /* r29 */, int rev /* r30 */) {
    // Local variables
    class Color thresholds; // r1+0x30
    float minchan; // f1
    float kernelMultiplier; // r1+0x1C
    float glint; // r1+0x18
    class ObjPtr draw; // r1+0x20

    // References
    // -> struct [anonymous] __vt__32ObjPtr<11RndDrawable,9ObjectDir>;
    // -> class Debug TheDebug;
}

static class Symbol _s; // size: 0x4, address: 0x80A535FC
// Range: 0x804E52D4 -> 0x804E5668
class DataNode RndPostProc::Handle(class RndPostProc * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A53604
static class Symbol _s; // size: 0x4, address: 0x80A5360C
static class Symbol _s; // size: 0x4, address: 0x80A53614
static class Symbol _s; // size: 0x4, address: 0x80A5361C
static class Symbol _s; // size: 0x4, address: 0x80A53624
static class Symbol _s; // size: 0x4, address: 0x80A5362C
static class Symbol _s; // size: 0x4, address: 0x80A53634
static class Symbol _s; // size: 0x4, address: 0x80A5363C
static class Symbol _s; // size: 0x4, address: 0x80A53644
static class Symbol _s; // size: 0x4, address: 0x80A5364C
static class Symbol _s; // size: 0x4, address: 0x80A53654
static class Symbol _s; // size: 0x4, address: 0x80A5365C
static class Symbol _s; // size: 0x4, address: 0x80A53664
static class Symbol _s; // size: 0x4, address: 0x80A5366C
static class Symbol _s; // size: 0x4, address: 0x80A53674
static class Symbol _s; // size: 0x4, address: 0x80A5367C
static class Symbol _s; // size: 0x4, address: 0x80A53684
static class Symbol _s; // size: 0x4, address: 0x80A5368C
static class Symbol _s; // size: 0x4, address: 0x80A53694
static class Symbol _s; // size: 0x4, address: 0x80A5369C
static class Symbol _s; // size: 0x4, address: 0x80A536A4
static class Symbol _s; // size: 0x4, address: 0x80A536AC
static class Symbol _s; // size: 0x4, address: 0x80A536B4
static class Symbol _s; // size: 0x4, address: 0x80A536BC
static class Symbol _s; // size: 0x4, address: 0x80A536C4
static class Symbol _s; // size: 0x4, address: 0x80A536CC
static class Symbol _s; // size: 0x4, address: 0x80A536D4
static class Symbol _s; // size: 0x4, address: 0x80A536DC
static class Symbol _s; // size: 0x4, address: 0x80A536E4
static class Symbol _s; // size: 0x4, address: 0x80A536EC
static class Symbol _s; // size: 0x4, address: 0x80A536F4
static class Symbol _s; // size: 0x4, address: 0x80A536FC
// Range: 0x804E5668 -> 0x804E6F7C
unsigned char RndPostProc::SyncProperty(class RndPostProc * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
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
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x804E6F7C -> 0x804E6FA0
void * ProcCounter::ProcCounter() {}

// Range: 0x804E6FA0 -> 0x804E6FB0
void ProcCounter::SetProcAndLock() {}

// Range: 0x804E6FB0 -> 0x804E7088
enum ProcessCmd ProcCounter::ProcCommands() {
    // Local variables
    enum ProcessCmd cmds; // r5
}

// Range: 0x804E7088 -> 0x804E70B0
void * DOFOverrideParams::DOFOverrideParams() {}

struct {
    // total size: 0x80
} __vt__11RndPostProc; // size: 0x80, address: 0x808FE0B0
// Range: 0x804E70B0 -> 0x804E70BC
static void __sinit_\PostProc_cpp() {
    // References
    // -> class DOFOverrideParams sDOFOverride;
}


