/*
    Compile unit: C:\rockband2\system\src\bandobj\H2HTrackPanelDir.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802C4B8C -> 0x802C78E0
*/
class DataArray * types; // size: 0x4, address: 0x80A503C8
// Range: 0x802C4B8C -> 0x802C4CCC
void * H2HTrackPanelDir::H2HTrackPanelDir(class H2HTrackPanelDir * const this /* r30 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__16H2HTrackPanelDir;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x802C4CCC -> 0x802C4D6C
void H2HTrackPanelDir::PostLoad(class H2HTrackPanelDir * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> class list sRevs;
}

// Range: 0x802C4D6C -> 0x802C4DD4
void H2HTrackPanelDir::Copy(class H2HTrackPanelDir * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class H2HTrackPanelDir * p; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16H2HTrackPanelDir;
}

static class Object * gamemode; // size: 0x4, address: 0x80A503D0
static class Symbol drum; // size: 0x4, address: 0x80A503D8
static class Symbol bass; // size: 0x4, address: 0x80A503E0
static class Symbol vocals; // size: 0x4, address: 0x80A503E8
// Range: 0x802C4DD4 -> 0x802C5B78
void H2HTrackPanelDir::ConfigureTracks(class H2HTrackPanelDir * const this /* r27 */) {
    // Local variables
    int ii; // r29
    class GemTrackDir * trackDir; // r28
    class ObjPtr tmp; // r1+0x3C
    int ii; // r23
    class VocalTrackDir * trackDir; // r25

    // References
    // -> class Rnd & TheRnd;
    // -> struct [anonymous] __RTTI__13VocalTrackDir;
    // -> static class Symbol vocals;
    // -> static class Symbol bass;
    // -> static class Symbol drum;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> struct [anonymous] __vt__32ObjPtr<11GemTrackDir,9ObjectDir>;
    // -> struct [anonymous] __RTTI__9BandTrack;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11GemTrackDir;
    // -> static class Object * gamemode;
}

static class Message reset; // size: 0x8, address: 0x8097DAA8
// Range: 0x802C5B78 -> 0x802C61FC
void H2HTrackPanelDir::Reset(class H2HTrackPanelDir * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__7UILabel;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __RTTI__11EndingBonus;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> static class Message reset;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x802C61FC -> 0x802C6358
void H2HTrackPanelDir::ResetAll(class H2HTrackPanelDir * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x802C6358 -> 0x802C6474
void H2HTrackPanelDir::PlayIntro(class H2HTrackPanelDir * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

static class Message arrow_hide; // size: 0x8, address: 0x8097DAC0
static class Message set_icon; // size: 0x8, address: 0x8097DAD8
static class Message set_glowing; // size: 0x8, address: 0x8097DAF0
// Range: 0x802C6474 -> 0x802C6924
void H2HTrackPanelDir::SetupH2HIcons(class BandTrack * track /* r27 */, class RndDir * icon /* r28 */, class UILabel * label /* r29 */) {
    // References
    // -> static class Message set_glowing;
    // -> static class Message set_icon;
    // -> static class Message arrow_hide;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x802C6924 -> 0x802C6A5C
void H2HTrackPanelDir::Coda(class H2HTrackPanelDir * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x802C6A5C -> 0x802C6AA0
void H2HTrackPanelDir::CodaEnd(class H2HTrackPanelDir * const this /* r31 */) {}

static class DebugWarner _dw; // size: 0x100, address: 0x8097DAF8
// Range: 0x802C6AA0 -> 0x802C6CB0
void H2HTrackPanelDir::H2HCodaSuccess(class H2HTrackPanelDir * const this /* r29 */) {
    // References
    // -> static class DebugWarner _dw;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

static class DebugWarner _dw; // size: 0x100, address: 0x8097DBF8
// Range: 0x802C6CB0 -> 0x802C6D6C
class EndingBonus * H2HTrackPanelDir::GetIndivEndingBonus() {
    // References
    // -> class Debug TheDebug;
    // -> static class DebugWarner _dw;
}

// Range: 0x802C6D6C -> 0x802C6E5C
void H2HTrackPanelDir::SoloEnd(class H2HTrackPanelDir * const this /* r28 */, class BandTrack * track /* r29 */, int points /* r30 */, class Symbol & result /* r31 */) {}

// Range: 0x802C6E5C -> 0x802C6F60
void H2HTrackPanelDir::GameOver(class H2HTrackPanelDir * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x802C6F60 -> 0x802C7224
class DataNode H2HTrackPanelDir::Handle(class H2HTrackPanelDir * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
    // Local variables
    class Symbol _type; // r1+0x20
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A503F4
static class Symbol _s; // size: 0x4, address: 0x80A503FC
static class Symbol _s; // size: 0x4, address: 0x80A50404
static class Symbol _s; // size: 0x4, address: 0x80A5040C
static class Symbol _s; // size: 0x4, address: 0x80A50414
static class Symbol _s; // size: 0x4, address: 0x80A5041C
// Range: 0x802C7224 -> 0x802C78E0
unsigned char H2HTrackPanelDir::SyncProperty(class H2HTrackPanelDir * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // Local variables
    unsigned char tmp; // r1+0x8

    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x2A0
} __vt__16H2HTrackPanelDir; // size: 0x2A0, address: 0x808C70D0
struct {
    // total size: 0x8
} __RTTI__16H2HTrackPanelDir; // size: 0x8, address: 0x808C73E8

