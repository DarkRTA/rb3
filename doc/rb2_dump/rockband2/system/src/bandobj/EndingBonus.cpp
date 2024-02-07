/*
    Compile unit: C:\rockband2\system\src\bandobj\EndingBonus.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802798B8 -> 0x8027BDAC
*/
class DataArray * types; // size: 0x4, address: 0x80A4F680
// Range: 0x802798B8 -> 0x80279A1C
void * EndingBonus::EndingBonus(class EndingBonus * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__24ObjPtr<4Task,9ObjectDir>;
    // -> struct [anonymous] __vt__11EndingBonus;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

static class Object * gameMode; // size: 0x4, address: 0x80A4F688
// Range: 0x80279A1C -> 0x80279FF8
void EndingBonus::Reset(class EndingBonus * const this /* r29 */) {
    // Local variables
    int ii; // r4
    int ii; // r30

    // References
    // -> struct [anonymous] __RTTI__9BandLabel;
    // -> static class Object * gameMode;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x80279FF8 -> 0x8027A018
void EndingBonus::SetIconText() {}

// Range: 0x8027A018 -> 0x8027A104
void EndingBonus::Success(class EndingBonus * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x8027A104 -> 0x8027A418
void EndingBonus::PlayerSuccess(class EndingBonus * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndPropAnim;
}

static class Message coda_end; // size: 0x8, address: 0x8097D1A0
// Range: 0x8027A418 -> 0x8027A5A4
void EndingBonus::CodaEnd(class EndingBonus * const this /* r30 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
    // -> static class Message coda_end;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8027A5A4 -> 0x8027A754
void EndingBonus::UnisonStart(class EndingBonus * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x8027A754 -> 0x8027A84C
void EndingBonus::UnisonEnd(class EndingBonus * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x8027A84C -> 0x8027A938
void EndingBonus::UnisonSucceed(class EndingBonus * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x8027A938 -> 0x8027AA54
void EndingBonus::SetScore(class EndingBonus * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndText;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x8027AA54 -> 0x8027AA98
void EndingBonus::HideIcons() {
    // Local variables
    int ii; // r5
}

static class Object * gameMode; // size: 0x4, address: 0x80A4F690
// Range: 0x8027AA98 -> 0x8027AB44
void EndingBonus::SetupEnding(class EndingBonus * const this /* r31 */) {
    // References
    // -> static class Object * gameMode;
}

// Range: 0x8027AB44 -> 0x8027AB4C
void EndingBonus::SetupUnison() {}

// Range: 0x8027AB4C -> 0x8027ADB8
void EndingBonus::SetIconOrder(class EndingBonus * const this /* r30 */, unsigned char forBRE /* r31 */) {
    // Local variables
    class vector iconsToShow; // r1+0x40
    int ii; // r29
    int ii; // r31
}

static class Symbol _s; // size: 0x4, address: 0x80A4F698
static class Symbol _s; // size: 0x4, address: 0x80A4F6A0
static class Symbol _s; // size: 0x4, address: 0x80A4F6A8
static class Symbol _s; // size: 0x4, address: 0x80A4F6B0
static class Symbol _s; // size: 0x4, address: 0x80A4F6B8
static class Symbol _s; // size: 0x4, address: 0x80A4F6C0
static class Symbol _s; // size: 0x4, address: 0x80A4F6C8
static class Symbol _s; // size: 0x4, address: 0x80A4F6D0
static class Symbol _s; // size: 0x4, address: 0x80A4F6D8
// Range: 0x8027ADB8 -> 0x8027B97C
class DataNode EndingBonus::Handle(class EndingBonus * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x44
    class MessageTimer _mt; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode _n; // r1+0x48

    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A4F6E0
// Range: 0x8027B97C -> 0x8027BAFC
unsigned char EndingBonus::SyncProperty(class EndingBonus * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x8027BAFC -> 0x8027BB00
void EndingBonus::Save() {}

// Range: 0x8027BB00 -> 0x8027BB04
void EndingBonus::PreLoad() {}

// Range: 0x8027BB04 -> 0x8027BB08
void EndingBonus::PostLoad() {}

// Range: 0x8027BB08 -> 0x8027BB0C
void EndingBonus::Copy() {}

// Range: 0x8027BB0C -> 0x8027BDAC
class DataNode EndingBonus::OnReset(class EndingBonus * const this /* r31 */) {}

struct {
    // total size: 0x21C
} __vt__11EndingBonus; // size: 0x21C, address: 0x808BA8E0
struct {
    // total size: 0x8
} __RTTI__PP9BandLabel; // size: 0x8, address: 0x808BB020

