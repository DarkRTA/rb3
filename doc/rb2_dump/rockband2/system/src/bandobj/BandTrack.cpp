/*
    Compile unit: C:\rockband2\system\src\bandobj\BandTrack.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802B5218 -> 0x802BA12C
*/
class Symbol name; // size: 0x4, address: 0x80A5020C
// Range: 0x802B5218 -> 0x802B54C4
void * BandTrack::~BandTrack(class BandTrack * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__35ObjPtr<14BandPowerMeter,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11StreakMeter,9ObjectDir>;
    // -> struct [anonymous] __vt__35ObjPtr<14TrackInterface,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndDir,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> struct [anonymous] __vt__24ObjPtr<4Task,9ObjectDir>;
}

// Range: 0x802B54C4 -> 0x802B57A0
void BandTrack::CopyTrack(class BandTrack * const this /* r30 */, const class BandTrack * rhs /* r31 */) {}

// Range: 0x802B57A0 -> 0x802B5848
void BandTrack::Init(class BandTrack * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14TrackInterface;
}

static class Message resetMsg; // size: 0x8, address: 0x8097D450
static class Symbol no_saving; // size: 0x4, address: 0x80A50214
// Range: 0x802B5848 -> 0x802B5D58
void BandTrack::Reset(class BandTrack * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> static class Symbol no_saving;
    // -> static class Message resetMsg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x802B5D58 -> 0x802B5D70
void BandTrack::SetMaxMultiplier() {}

static class Message resetMsg; // size: 0x8, address: 0x8097D468
static class Message setupPlayer; // size: 0x8, address: 0x8097D480
// Range: 0x802B5D70 -> 0x802B6164
void BandTrack::SetupPlayerIntro(class BandTrack * const this /* r30 */) {
    // References
    // -> static class Message setupPlayer;
    // -> static class Message resetMsg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x802B6164 -> 0x802B623C
void BandTrack::SetupCrowdMeter(class BandTrack * const this /* r29 */) {
    // Local variables
    class BandCrowdMeter * bcm; // r0
}

static class Message resetMsg; // size: 0x8, address: 0x8097D498
// Range: 0x802B623C -> 0x802B64D4
void BandTrack::Retract(class BandTrack * const this /* r31 */, unsigned char immediately /* r29 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> static class Message resetMsg;
    // -> struct [anonymous] __vt__7Message;
}

static class Message finale_start; // size: 0x8, address: 0x8097D4B0
// Range: 0x802B64D4 -> 0x802B6700
void BandTrack::StartFinale(class BandTrack * const this /* r31 */) {
    // References
    // -> static class Message finale_start;
    // -> struct [anonymous] __vt__7Message;
}

static float kMinFinaleHelpTime; // size: 0x4, address: 0x80A5021C
static class Message msg; // size: 0x8, address: 0x8097D4C8
// Range: 0x802B6700 -> 0x802B699C
void BandTrack::ClearFinaleHelp(class BandTrack * const this /* r31 */) {
    // Local variables
    float elapsed; // f31
    float delay; // f30

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> static float kMinFinaleHelpTime;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

static class Message resetMsg; // size: 0x8, address: 0x8097D4E0
// Range: 0x802B699C -> 0x802B6B00
void BandTrack::GameWon(class BandTrack * const this /* r31 */) {
    // References
    // -> static class Message resetMsg;
    // -> struct [anonymous] __vt__7Message;
}

static class Message resetMsg; // size: 0x8, address: 0x8097D4F8
// Range: 0x802B6B00 -> 0x802B6D00
void BandTrack::GameOver(class BandTrack * const this /* r31 */) {
    // References
    // -> static class Message resetMsg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x802B6D00 -> 0x802B6DE0
void BandTrack::SpotlightFail() {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x802B6DE0 -> 0x802B6E70
void BandTrack::SpotlightPhraseSuccess(class BandTrack * const this /* r30 */) {}

// Range: 0x802B6E70 -> 0x802B6EEC
void BandTrack::FillReset() {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x802B6EEC -> 0x802B6F54
void BandTrack::SetStreak(class BandTrack * const this /* r30 */, int mult /* r31 */) {}

// Range: 0x802B6F54 -> 0x802B6FB4
void BandTrack::BreakStreak(class BandTrack * const this /* r31 */) {}

static class Symbol update_crowd_meter; // size: 0x4, address: 0x80A50228
static class Object * gameMode; // size: 0x4, address: 0x80A5022C
// Range: 0x802B6FB4 -> 0x802B70A4
class BandCrowdMeter * BandTrack::GetCrowdMeter(class BandTrack * const this /* r30 */) {
    // References
    // -> static class Object * gameMode;
    // -> static class Symbol update_crowd_meter;
}

// Range: 0x802B70A4 -> 0x802B725C
void BandTrack::SetCrowdRating(class BandTrack * const this /* r27 */, float val /* f31 */, enum CrowdMeterState state /* r28 */) {
    // Local variables
    class BandCrowdMeter * bcm; // r29
    enum TrackInstrument inst; // r30
    unsigned char warning; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x802B725C -> 0x802B7354
void BandTrack::EnablePlayer(class BandTrack * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

static class Message resetMsg; // size: 0x8, address: 0x8097D510
static class Message disconnected; // size: 0x8, address: 0x8097D528
static class Message failed; // size: 0x8, address: 0x8097D540
// Range: 0x802B7354 -> 0x802B7A5C
void BandTrack::DisablePlayer(class BandTrack * const this /* r27 */, int strikes /* r28 */) {
    // Local variables
    float delay; // f0

    // References
    // -> static class Message failed;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> class TaskMgr TheTaskMgr;
    // -> static class Message disconnected;
    // -> static class Message resetMsg;
    // -> struct [anonymous] __vt__7Message;
}

static class Symbol vocals; // size: 0x4, address: 0x80A50238
static class Message intro; // size: 0x8, address: 0x8097D558
static class Message discon; // size: 0x8, address: 0x8097D570
static class Message failed; // size: 0x8, address: 0x8097D588
// Range: 0x802B7A5C -> 0x802B7EDC
void BandTrack::FailedTask(class BandTrack * const this /* r27 */, unsigned char disconnected /* r28 */, int strikes /* r29 */) {
    // References
    // -> static class Message failed;
    // -> static class Message discon;
    // -> static class Message intro;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol vocals;
}

// Range: 0x802B7EDC -> 0x802B824C
void BandTrack::SavePlayer(class BandTrack * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__7Message;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

static class Message resetMsg; // size: 0x8, address: 0x8097D5A0
// Range: 0x802B824C -> 0x802B8490
void BandTrack::EnterCoda(class BandTrack * const this /* r31 */) {
    // References
    // -> static class Message resetMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x802B8490 -> 0x802B84F0
void BandTrack::CodaFail(class BandTrack * const this /* r30 */, unsigned char guilty /* r31 */) {}

static class Symbol coop; // size: 0x4, address: 0x80A50244
// Range: 0x802B84F0 -> 0x802B86B8
void BandTrack::CodaSuccess(class BandTrack * const this /* r30 */) {
    // Local variables
    class TrackPanelDirBase * panelDir; // r31
    class EndingBonus * eb; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> class LoadMgr TheLoadMgr;
    // -> static class Symbol coop;
}

static class Message msg; // size: 0x8, address: 0x8097D5B8
// Range: 0x802B86B8 -> 0x802B8A94
void BandTrack::PopupHelp(class BandTrack * const this /* r29 */, class Symbol & key /* r30 */, unsigned char state /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x802B8A94 -> 0x802B8BD0
void BandTrack::ResetPopup(class BandTrack * const this /* r28 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x802B8BD0 -> 0x802B8BF4
void BandTrack::PlayerDisabled() {}

// Range: 0x802B8BF4 -> 0x802B8C18
void BandTrack::PlayerSaved() {}

// Range: 0x802B8C18 -> 0x802B8C74
void BandTrack::SuperStreak(class BandTrack * const this /* r30 */, unsigned char val /* r31 */) {}

// Range: 0x802B8C74 -> 0x802B8C90
void BandTrack::SetMultiplier() {}

// Range: 0x802B8C90 -> 0x802B8CA4
void BandTrack::CombineStreakMultipliers() {}

static class Message fade; // size: 0x8, address: 0x8097D5D0
static class Message hide; // size: 0x8, address: 0x8097D5E8
static class Message intro; // size: 0x8, address: 0x8097D600
// Range: 0x802B8CA4 -> 0x802B9190
void BandTrack::PlayIntro(class BandTrack * const this /* r29 */) {
    // Local variables
    class Object * gamemode; // r28

    // References
    // -> static class Message intro;
    // -> class TaskMgr TheTaskMgr;
    // -> static class Message hide;
    // -> static class Message fade;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x802B9190 -> 0x802B9268
void BandTrack::Deploy(class BandTrack * const this /* r30 */) {
    // Local variables
    class BandCrowdMeter * bcm; // r31
}

// Range: 0x802B9268 -> 0x802B9340
void BandTrack::StopDeploy(class BandTrack * const this /* r30 */) {
    // Local variables
    class BandCrowdMeter * bcm; // r31
}

// Range: 0x802B9340 -> 0x802B935C
void BandTrack::SetNoOverdrive() {}

// Range: 0x802B935C -> 0x802B93B0
class TrackPanelDirBase * BandTrack::MyTrackPanelDir() {
    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__17TrackPanelDirBase;
}

// Range: 0x802B93B0 -> 0x802B9404
unsigned char BandTrack::HasNetPlayer() {}

// Range: 0x802B9404 -> 0x802B9458
unsigned char BandTrack::HasLocalPlayer() {}

// Range: 0x802B9458 -> 0x802B947C
int BandTrack::GetPlayerDifficulty() {}

// Range: 0x802B947C -> 0x802B948C
char * BandTrack::ThisName() {}

// Range: 0x802B948C -> 0x802B94DC
char * BandTrack::GetUserName() {}

// Range: 0x802B94DC -> 0x802B952C
char * BandTrack::GetTrackIcon() {}

// Range: 0x802B952C -> 0x802B9954
void BandTrack::SoloStart(class BandTrack * const this /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__12RndTransAnim;
    // -> struct [anonymous] __RTTI__7RndText;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x802B9954 -> 0x802B9C08
void BandTrack::SoloEnd(class BandTrack * const this /* r25 */, int points /* r26 */, class Symbol & result /* r27 */) {
    // References
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> struct [anonymous] __RTTI__7RndText;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9BandLabel;
}

// Range: 0x802B9C08 -> 0x802B9EA0
void BandTrack::SoloHit(class BandTrack * const this /* r26 */, int percent /* r27 */) {
    // References
    // -> struct [anonymous] __RTTI__12RndTransAnim;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndText;
}

// Range: 0x802B9EA0 -> 0x802B9FA8
void BandTrack::SoloHide() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndPropAnim;
}

// Range: 0x802B9FA8 -> 0x802BA038
void BandTrack::RefreshStreakMeter(class BandTrack * const this /* r28 */, int streak /* r29 */, int multiplier /* r30 */, int notesPerStreak /* r31 */) {}

static class Symbol ready; // size: 0x4, address: 0x80A50250
static class Symbol none; // size: 0x4, address: 0x80A50258
// Range: 0x802BA038 -> 0x802BA12C
void BandTrack::RefreshOverdrive(class BandTrack * const this /* r30 */, float energy /* f31 */, unsigned char canDeploy /* r31 */) {
    // References
    // -> static class Symbol none;
    // -> static class Symbol ready;
}

struct {
    // total size: 0x60
} __vt__9BandTrack; // size: 0x60, address: 0x808C40D8
struct {
    // total size: 0x18
} __vt__35ObjPtr<14TrackInterface,9ObjectDir>; // size: 0x18, address: 0x808C4150
struct {
    // total size: 0x8
} __RTTI__35ObjPtr<14TrackInterface,9ObjectDir>; // size: 0x8, address: 0x808C4198
struct {
    // total size: 0x18
} __vt__32ObjPtr<11StreakMeter,9ObjectDir>; // size: 0x18, address: 0x808C41A0
struct {
    // total size: 0x8
} __RTTI__32ObjPtr<11StreakMeter,9ObjectDir>; // size: 0x8, address: 0x808C41E8
struct {
    // total size: 0x18
} __vt__35ObjPtr<14BandPowerMeter,9ObjectDir>; // size: 0x18, address: 0x808C41F0
struct {
    // total size: 0x8
} __RTTI__35ObjPtr<14BandPowerMeter,9ObjectDir>; // size: 0x8, address: 0x808C4238

