/*
    Compile unit: C:\rockband2\system\src\bandobj\StreakMeter.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8029D51C -> 0x8029EFA8
*/
class DataArray * types; // size: 0x4, address: 0x80A4FA08
// Range: 0x8029D51C -> 0x8029D850
void * StreakMeter::StreakMeter(class StreakMeter * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__31ObjPtr<10RndMatAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__27ObjPtr<7RndText,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12RndTransAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> struct [anonymous] __vt__11StreakMeter;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x8029D850 -> 0x8029D8B0
void StreakMeter::SetBandMultiplier(class StreakMeter * const this /* r31 */) {}

// Range: 0x8029D8B0 -> 0x8029D918
void StreakMeter::SetMultiplier(class StreakMeter * const this /* r31 */) {}

static class DebugWarner _dw; // size: 0x100, address: 0x8097D1A8
// Range: 0x8029D918 -> 0x8029DA60
float StringToFrame(const char * str /* r28 */) {
    // Local variables
    float ret; // f31
    const char * c; // r29

    // References
    // -> class Debug TheDebug;
    // -> static class DebugWarner _dw;
}

// Range: 0x8029DA60 -> 0x8029DA84
int StreakMeter::GetMultiplierToShow() {}

// Range: 0x8029DA84 -> 0x8029DAC4
void StreakMeter::MultiplierChanged(class StreakMeter * const this /* r31 */) {
    // Local variables
    int mult; // r4
}

// Range: 0x8029DAC4 -> 0x8029DB94
void StreakMeter::UpdateMultiplierText(class StreakMeter * const this /* r29 */) {
    // Local variables
    const char * multText; // r30
    float newFrame; // f30
    float oldFrame; // f0
}

// Range: 0x8029DB94 -> 0x8029DC14
void StreakMeter::BreakStreak(class StreakMeter * const this /* r30 */) {
    // Local variables
    int mult; // r31
}

// Range: 0x8029DC14 -> 0x8029DC28
void StreakMeter::GlowBlue() {}

// Range: 0x8029DC28 -> 0x8029DC3C
void StreakMeter::Overdrive() {}

// Range: 0x8029DC3C -> 0x8029DC70
void StreakMeter::EndOverdrive() {}

// Range: 0x8029DC70 -> 0x8029DC84
void StreakMeter::Reset() {}

// Range: 0x8029DC84 -> 0x8029DC9C
void StreakMeter::SetWipe() {}

static class Symbol _s; // size: 0x4, address: 0x80A4FA10
static class Symbol _s; // size: 0x4, address: 0x80A4FA18
static class Symbol _s; // size: 0x4, address: 0x80A4FA20
static class Symbol _s; // size: 0x4, address: 0x80A4FA28
static class Symbol _s; // size: 0x4, address: 0x80A4FA30
static class Symbol _s; // size: 0x4, address: 0x80A4FA38
static class Symbol _s; // size: 0x4, address: 0x80A4FA40
static class Symbol _s; // size: 0x4, address: 0x80A4FA48
// Range: 0x8029DC9C -> 0x8029E688
class DataNode StreakMeter::Handle(class StreakMeter * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x40
    class MessageTimer _mt; // r1+0x50
    class DataNode _n; // r1+0x48

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
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

static class Symbol _s; // size: 0x4, address: 0x80A4FA50
static class Symbol _s; // size: 0x4, address: 0x80A4FA58
static class Symbol _s; // size: 0x4, address: 0x80A4FA60
// Range: 0x8029E688 -> 0x8029E9F4
unsigned char StreakMeter::SyncProperty(class StreakMeter * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x8029E9F4 -> 0x8029EA38
void StreakMeter::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8029EA38 -> 0x8029EBA4
void StreakMeter::PreLoad(class StreakMeter * const this /* r29 */, class BinStream & s /* r30 */) {
    // Local variables
    int rev; // r1+0xC

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8029EBA4 -> 0x8029EBA8
void StreakMeter::PostLoad() {}

// Range: 0x8029EBA8 -> 0x8029EE38
void StreakMeter::Copy(class StreakMeter * const this /* r31 */, const class Object * o /* r29 */) {
    // Local variables
    const class StreakMeter * sm; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11StreakMeter;
}

// Range: 0x8029EE38 -> 0x8029EFA8
void StreakMeter::SetPitch(class StreakMeter * const this /* r31 */, float pitch /* f31 */) {
    // Local variables
    class Vector3 e; // r1+0x20
    class Vector3 s; // r1+0x10
    class Matrix3 m; // r1+0x30
}

struct {
    // total size: 0x21C
} __vt__11StreakMeter; // size: 0x21C, address: 0x808BF9D4
struct {
    // total size: 0x8
} __RTTI__11StreakMeter; // size: 0x8, address: 0x808BFC50

