/*
    Compile unit: C:\rockband2\system\src\bandobj\TrackPanelDirBase.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802BAC68 -> 0x802BDE7C
*/
class DataArray * types; // size: 0x4, address: 0x80A50260
class Symbol name; // size: 0x4, address: 0x80A50268
// Range: 0x802BAC68 -> 0x802BAE74
void * TrackPanelDirBase::TrackPanelDirBase(class TrackPanelDirBase * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__24ObjPtr<4Task,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndDir,9ObjectDir>;
    // -> struct [anonymous] __vt__41ObjPtrList<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__17TrackPanelDirBase;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x802BAE74 -> 0x802BAF2C
void TrackPanelDirBase::PostLoad(class TrackPanelDirBase * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> class list sRevs;
}

// Range: 0x802BAF2C -> 0x802BB2B8
void TrackPanelDirBase::Copy(class TrackPanelDirBase * const this /* r29 */, const class Object * o /* r27 */) {
    // Local variables
    const class TrackPanelDirBase * p; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__17TrackPanelDirBase;
}

static class DebugWarner _dw; // size: 0x100, address: 0x8097D608
static class Message apply; // size: 0x8, address: 0x8097D718
// Range: 0x802BB2B8 -> 0x802BB454
void TrackPanelDirBase::SetConfiguration(class TrackPanelDirBase * const this /* r30 */, class Object * config /* r31 */) {
    // References
    // -> static class Message apply;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x802BB454 -> 0x802BB4F4
void TrackPanelDirBase::Enter(class TrackPanelDirBase * const this /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> class LoadMgr TheLoadMgr;
}

static class Symbol mod_doublespeed; // size: 0x4, address: 0x80A50270
// Range: 0x802BB4F4 -> 0x802BB724
void TrackPanelDirBase::UpdateTrackSpeed(class TrackPanelDirBase * const this /* r29 */) {
    // Local variables
    float avgDiff; // f31
    int numLocalTracks; // [invalid]
    int ii; // r31
    int numRelevantTracks; // r30
    int ii; // r31
    float viewTime; // f31
    int ii; // r28

    // References
    // -> static class Symbol mod_doublespeed;
}

// Range: 0x802BB724 -> 0x802BB8A4
void TrackPanelDirBase::SetShowing(class TrackPanelDirBase * const this /* r28 */, unsigned char visible /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

// Range: 0x802BB8A4 -> 0x802BB978
unsigned char TrackPanelDirBase::Showing(class TrackPanelDirBase * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

// Range: 0x802BB978 -> 0x802BB9D4
void TrackPanelDirBase::ToggleSurface() {
    // Local variables
    int ii; // r6
}

// Range: 0x802BB9D4 -> 0x802BBAF4
void TrackPanelDirBase::ToggleNowbar(class TrackPanelDirBase * const this /* r30 */) {
    // Local variables
    int ii; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

// Range: 0x802BBAF4 -> 0x802BBB10
void TrackPanelDirBase::SetPlayerLocal(class TrackPanelDirBase * const this /* r5 */) {}

static class DebugWarner _dw; // size: 0x100, address: 0x8097D720
// Range: 0x802BBB10 -> 0x802BBB8C
void TrackPanelDirBase::CodaSuccess() {
    // References
    // -> class Debug TheDebug;
    // -> static class DebugWarner _dw;
}

static class DebugWarner _dw; // size: 0x100, address: 0x8097D820
// Range: 0x802BBB8C -> 0x802BBC08
void TrackPanelDirBase::H2HCodaSuccess() {
    // References
    // -> class Debug TheDebug;
    // -> static class DebugWarner _dw;
}

static class DebugWarner _dw; // size: 0x100, address: 0x8097D920
// Range: 0x802BBC08 -> 0x802BBC88
class EndingBonus * TrackPanelDirBase::GetIndivEndingBonus() {
    // References
    // -> class Debug TheDebug;
    // -> static class DebugWarner _dw;
}

static class Message set_score_diff; // size: 0x8, address: 0x8097DA30
static class Message set_winning_glow; // size: 0x8, address: 0x8097DA48
// Range: 0x802BBC88 -> 0x802BC1FC
void TrackPanelDirBase::SetScoreDiff(class TrackPanelDirBase * const this /* r26 */, int val /* r27 */, int * trendIn /* r28 */) {
    // Local variables
    int lastWinner; // r0

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> static class Message set_winning_glow;
    // -> static class Message set_score_diff;
    // -> struct [anonymous] __vt__7Message;
}

static class Message active; // size: 0x8, address: 0x8097DA60
// Range: 0x802BC1FC -> 0x802BC450
unsigned char TrackPanelDirBase::ModifierActive(class Symbol & mod /* r30 */) {
    // Local variables
    class Object * modifier_mgr; // r31

    // References
    // -> static class Message active;
    // -> struct [anonymous] __vt__7Message;
}

static class Symbol mod_nohud; // size: 0x4, address: 0x80A50278
// Range: 0x802BC450 -> 0x802BC56C
void TrackPanelDirBase::HandleNoHudModifier(class TrackPanelDirBase * const this /* r29 */) {
    // Local variables
    class Object * game_mode; // r30

    // References
    // -> static class Symbol mod_nohud;
}

static class Symbol _s; // size: 0x4, address: 0x80A50280
static class Symbol _s; // size: 0x4, address: 0x80A50288
static class Symbol _s; // size: 0x4, address: 0x80A50290
static class Symbol _s; // size: 0x4, address: 0x80A50298
static class Symbol _s; // size: 0x4, address: 0x80A502A0
static class Symbol _s; // size: 0x4, address: 0x80A502A8
static class Symbol _s; // size: 0x4, address: 0x80A502B0
static class Symbol _s; // size: 0x4, address: 0x80A502B8
static class Symbol _s; // size: 0x4, address: 0x80A502C0
static class Symbol _s; // size: 0x4, address: 0x80A502C8
static class Symbol _s; // size: 0x4, address: 0x80A502D0
static class Symbol _s; // size: 0x4, address: 0x80A502D8
static class Symbol _s; // size: 0x4, address: 0x80A502E0
static class Symbol _s; // size: 0x4, address: 0x80A502E8
static class Symbol _s; // size: 0x4, address: 0x80A502F0
static class Symbol _s; // size: 0x4, address: 0x80A502F8
static class Symbol _s; // size: 0x4, address: 0x80A50300
// Range: 0x802BC56C -> 0x802BD8D4
class DataNode TrackPanelDirBase::Handle(class TrackPanelDirBase * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x64
    class MessageTimer _mt; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode _n; // r1+0x68

    // References
    // -> class Debug TheDebug;
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
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A50308
static class Symbol _s; // size: 0x4, address: 0x80A50310
static class Symbol _s; // size: 0x4, address: 0x80A50318
static class Symbol _s; // size: 0x4, address: 0x80A50320
static class Symbol _s; // size: 0x4, address: 0x80A50328
// Range: 0x802BD8D4 -> 0x802BDCCC
unsigned char TrackPanelDirBase::SyncProperty(class TrackPanelDirBase * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x802BDCCC -> 0x802BDE7C
class DataNode TrackPanelDirBase::DataForEachConfigObj(class TrackPanelDirBase * const this /* r28 */, class DataArray * array /* r30 */) {
    // Local variables
    class DataNode * var; // r31
    class DataNode val; // r1+0x30
    class iterator it; // r1+0x18
    int j; // r28
}

struct {
    // total size: 0x2A0
} __vt__17TrackPanelDirBase; // size: 0x2A0, address: 0x808C4D08

