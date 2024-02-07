/*
    Compile unit: C:\rockband2\system\src\bandobj\GemTrackDir.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802A0648 -> 0x802A7AB4
*/
class DataArray * types; // size: 0x4, address: 0x80A4FA68
// Range: 0x802A0648 -> 0x802A0E54
void * GemTrackDir::GemTrackDir(class GemTrackDir * const this /* r31 */) {
    // Local variables
    class ObjPtr nullAnimPtr; // r1+0x2C
    int ii; // r30
    class ObjPtr nullTrigPtr; // r1+0x20
    int ii; // r30

    // References
    // -> struct [anonymous] __vt__24ObjPtr<4Task,9ObjectDir>;
    // -> struct [anonymous] __vt__36ObjPtrList<11TrackWidget,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11RndPropAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndCam,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10RndEnviron,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndDir,9ObjectDir>;
    // -> struct [anonymous] __vt__11GemTrackDir;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x802A0E54 -> 0x802A1614
void GemTrackDir::Copy(class GemTrackDir * const this /* r29 */, const class Object * o /* r27 */) {
    // Local variables
    const class GemTrackDir * d; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11GemTrackDir;
}

// Range: 0x802A1614 -> 0x802A1670
void GemTrackDir::Load(class GemTrackDir * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x802A1670 -> 0x802A16DC
void GemTrackDir::PostLoad(class GemTrackDir * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> class list sRevs;
}

// Range: 0x802A16DC -> 0x802A1710
void GemTrackDir::SetFade() {
    // Local variables
    float horizon; // f2
}

// Range: 0x802A1710 -> 0x802A1738
void GemTrackDir::SetFOV(float val /* f3 */) {}

// Range: 0x802A1738 -> 0x802A17A4
void GemTrackDir::SetCamPos() {}

// Range: 0x802A17A4 -> 0x802A1864
void GemTrackDir::SetScreenRectX() {
    // Local variables
    class Rect rect; // r1+0x8
}

// Range: 0x802A1864 -> 0x802A192C
void GemTrackDir::SetTrackOffset() {
    // Local variables
    class Vector3 pos; // r1+0x10
}

// Range: 0x802A192C -> 0x802A1A6C
void GemTrackDir::SetSideAngle(class GemTrackDir * const this /* r31 */, float val /* f31 */) {
    // Local variables
    class Vector3 e; // r1+0x10
    class Matrix3 m; // r1+0x20
}

// Range: 0x802A1A6C -> 0x802A1AF0
void GemTrackDir::UpdateSurfaceTexture() {}

static class Message hide; // size: 0x8, address: 0x8097D2B8
// Range: 0x802A1AF0 -> 0x802A1DD8
void GemTrackDir::OnUpdateFx(class GemTrackDir * const this /* r31 */, int effect /* r28 */) {
    // Local variables
    int ii; // r29

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> static class Message hide;
    // -> struct [anonymous] __vt__7Message;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9BandLabel;
    // -> const char * gNullStr;
}

static class Symbol coop; // size: 0x4, address: 0x80A4FA70
static class Message trigger; // size: 0x8, address: 0x8097D2D0
// Range: 0x802A1DD8 -> 0x802A208C
void GemTrackDir::PlayIntro(class GemTrackDir * const this /* r30 */) {
    // Local variables
    float delay; // f31

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> static class Message trigger;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol coop;
}

static class Message kResetMsg; // size: 0x8, address: 0x8097D2E8
static class Message setup_draworder; // size: 0x8, address: 0x8097D300
// Range: 0x802A208C -> 0x802A2914
void GemTrackDir::TrackReset(class GemTrackDir * const this /* r28 */) {
    // Local variables
    int ii; // r25
    class RndPropAnim * instrumentSetupAnim; // r29
    class RndDir * otherSmasherPlate; // r29
    float frame; // f0

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> class LoadMgr TheLoadMgr;
    // -> static class Message setup_draworder;
    // -> const char * gNullStr;
    // -> static class Message kResetMsg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x802A2914 -> 0x802A2A00
void GemTrackDir::GameWon(class GemTrackDir * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x802A2A00 -> 0x802A2AF4
void GemTrackDir::PracticeReset(class GemTrackDir * const this /* r29 */) {
    // Local variables
    class RndGroup * anim; // r30
    class TrackWidget * wid; // r0
}

static class Message clear; // size: 0x8, address: 0x8097D318
// Range: 0x802A2AF4 -> 0x802A2CA8
void GemTrackDir::Retract(class GemTrackDir * const this /* r31 */, unsigned char immediately /* r30 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
    // -> static class Message clear;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x802A2CA8 -> 0x802A2D64
void GemTrackDir::SetStreak(class GemTrackDir * const this /* r28 */, int streak /* r29 */, int mult /* r30 */, int notesPerStreak /* r31 */) {
    // Local variables
    float pct; // f1
}

// Range: 0x802A2D64 -> 0x802A2F88
void GemTrackDir::RefreshStreakMeter(class GemTrackDir * const this /* r31 */, int streak /* r28 */, int multiplier /* r29 */, int notesPerStreak /* r30 */) {
    // Local variables
    float pct; // f0
    class Message set_wipe; // r1+0x20

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> struct [anonymous] __vt__7Message;
}

static class Symbol bass; // size: 0x4, address: 0x80A4FA7C
// Range: 0x802A2F88 -> 0x802A3170
void GemTrackDir::SuperStreak(class GemTrackDir * const this /* r30 */, unsigned char val /* r31 */) {
    // Local variables
    class Message msg; // r1+0x20

    // References
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol bass;
}

static class Message updateGems; // size: 0x8, address: 0x8097D330
// Range: 0x802A3170 -> 0x802A333C
void GemTrackDir::Deploy(class GemTrackDir * const this /* r31 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
    // -> static class Message updateGems;
    // -> struct [anonymous] __vt__7Message;
    // -> const char * gNullStr;
}

static class Message kResetMsg; // size: 0x8, address: 0x8097D348
// Range: 0x802A333C -> 0x802A3524
void GemTrackDir::EnterCoda(class GemTrackDir * const this /* r30 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
    // -> static class Message kResetMsg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x802A3524 -> 0x802A3598
void GemTrackDir::DisablePlayer(class GemTrackDir * const this /* r30 */, int strikes /* r31 */) {}

// Range: 0x802A3598 -> 0x802A35AC
void GemTrackDir::PracticeTrackOut() {}

static class Symbol drum; // size: 0x4, address: 0x80A4FA84
static class Symbol kick; // size: 0x4, address: 0x80A4FA8C
// Range: 0x802A35AC -> 0x802A36DC
void GemTrackDir::GemPass(class GemTrackDir * const this /* r31 */, int lanesMask /* r30 */) {
    // Local variables
    float nextKick; // f0

    // References
    // -> static class Symbol kick;
    // -> static class Symbol drum;
}

// Range: 0x802A36DC -> 0x802A36F0
void GemTrackDir::KickHit() {}

static class Message msg; // size: 0x8, address: 0x8097D360
// Range: 0x802A36F0 -> 0x802A384C
void GemTrackDir::SeeKick(class GemTrackDir * const this /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

static class Symbol kick; // size: 0x4, address: 0x80A4FA94
// Range: 0x802A384C -> 0x802A38B8
void GemTrackDir::KickSwing(class GemTrackDir * const this /* r31 */) {
    // References
    // -> static class Symbol kick;
}

// Range: 0x802A38B8 -> 0x802A390C
void GemTrackDir::SpotlightPhraseSuccess(class GemTrackDir * const this /* r31 */) {}

static class Message hit_fill_3p; // size: 0x8, address: 0x8097D378
static class Message hit_fill; // size: 0x8, address: 0x8097D390
// Range: 0x802A390C -> 0x802A3D3C
void GemTrackDir::FillNote(class GemTrackDir * const this /* r28 */, int slot /* r29 */, int velocity /* r30 */) {
    // References
    // -> static class Message hit_fill;
    // -> static class Message hit_fill_3p;
    // -> struct [anonymous] __vt__7Message;
}

static class Symbol drum; // size: 0x4, address: 0x80A4FA9C
// Range: 0x802A3D3C -> 0x802A3E10
void GemTrackDir::Mash(class GemTrackDir * const this /* r30 */, int slot /* r31 */) {
    // Local variables
    class RndPropAnim * anim; // r3

    // References
    // -> static class Symbol drum;
}

// Range: 0x802A3E10 -> 0x802A3EE0
void GemTrackDir::FillHit(class GemTrackDir * const this /* r30 */, int numNotes /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol loop; // size: 0x4, address: 0x80A4FAA4
// Range: 0x802A3EE0 -> 0x802A3FD8
void GemTrackDir::ResetDrumFill(class GemTrackDir * const this /* r30 */) {
    // Local variables
    float timeTillNext; // f31

    // References
    // -> static class Symbol loop;
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x802A3FD8 -> 0x802A4068
void GemTrackDir::ResetCoda(class GemTrackDir * const this /* r30 */) {}

static class Message drum_fill_complete_3p; // size: 0x8, address: 0x8097D3A8
static class Message drum_fill_complete; // size: 0x8, address: 0x8097D3C0
// Range: 0x802A4068 -> 0x802A431C
void GemTrackDir::CrashFill(class GemTrackDir * const this /* r30 */) {
    // References
    // -> static class Message drum_fill_complete;
    // -> static class Message drum_fill_complete_3p;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x802A431C -> 0x802A43E4
void GemTrackDir::SetupWidgetLOD(class GemTrackDir * const this /* r30 */) {
    // Local variables
    unsigned char glowVisible; // r31
    class iterator it; // r1+0x18

    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x802A43E4 -> 0x802A4400
void GemTrackDir::SetWidgetGlow() {}

// Range: 0x802A4400 -> 0x802A4408
unsigned char GemTrackDir::GetCrashAppeared() {}

// Range: 0x802A4408 -> 0x802A4470
void GemTrackDir::ClearCrashAppeared(class GemTrackDir * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol fade_max; // size: 0x4, address: 0x80A4FAAC
// Range: 0x802A4470 -> 0x802A469C
void GemTrackDir::SetPlayerLocal(class GemTrackDir * const this /* r29 */, float netTrackAlpha /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10RndEnviron;
    // -> static class Symbol fade_max;
}

static class Symbol _s; // size: 0x4, address: 0x80A4FAB4
static class Symbol _s; // size: 0x4, address: 0x80A4FABC
static class Symbol _s; // size: 0x4, address: 0x80A4FAC4
static class Symbol _s; // size: 0x4, address: 0x80A4FACC
static class Symbol _s; // size: 0x4, address: 0x80A4FAD4
static class Symbol _s; // size: 0x4, address: 0x80A4FADC
static class Symbol _s; // size: 0x4, address: 0x80A4FAE4
static class Symbol _s; // size: 0x4, address: 0x80A4FAEC
static class Symbol _s; // size: 0x4, address: 0x80A4FAF4
static class Symbol _s; // size: 0x4, address: 0x80A4FAFC
static class Symbol _s; // size: 0x4, address: 0x80A4FB04
static class Symbol _s; // size: 0x4, address: 0x80A4FB0C
static class Symbol _s; // size: 0x4, address: 0x80A4FB14
static class Symbol _s; // size: 0x4, address: 0x80A4FB1C
static class Symbol _s; // size: 0x4, address: 0x80A4FB24
static class Symbol _s; // size: 0x4, address: 0x80A4FB2C
static class Symbol _s; // size: 0x4, address: 0x80A4FB34
static class Symbol _s; // size: 0x4, address: 0x80A4FB3C
static class Symbol _s; // size: 0x4, address: 0x80A4FB44
static class Symbol _s; // size: 0x4, address: 0x80A4FB4C
static class Symbol _s; // size: 0x4, address: 0x80A4FB54
static class Symbol _s; // size: 0x4, address: 0x80A4FB5C
static class Symbol _s; // size: 0x4, address: 0x80A4FB64
static class Symbol _s; // size: 0x4, address: 0x80A4FB6C
static class Symbol _s; // size: 0x4, address: 0x80A4FB74
static class Symbol _s; // size: 0x4, address: 0x80A4FB7C
static class Symbol _s; // size: 0x4, address: 0x80A4FB84
static class Symbol _s; // size: 0x4, address: 0x80A4FB8C
static class Symbol _s; // size: 0x4, address: 0x80A4FB94
static class Symbol _s; // size: 0x4, address: 0x80A4FB9C
static class Symbol _s; // size: 0x4, address: 0x80A4FBA4
static class Symbol _s; // size: 0x4, address: 0x80A4FBAC
static class Symbol _s; // size: 0x4, address: 0x80A4FBB4
static class Symbol _s; // size: 0x4, address: 0x80A4FBBC
static class Symbol _s; // size: 0x4, address: 0x80A4FBC4
static class Symbol _s; // size: 0x4, address: 0x80A4FBCC
static class Symbol _s; // size: 0x4, address: 0x80A4FBD4
static class Symbol _s; // size: 0x4, address: 0x80A4FBDC
static class Symbol _s; // size: 0x4, address: 0x80A4FBE4
static class Symbol _s; // size: 0x4, address: 0x80A4FBEC
static class Symbol _s; // size: 0x4, address: 0x80A4FBF4
static class Symbol _s; // size: 0x4, address: 0x80A4FBFC
static class Symbol _s; // size: 0x4, address: 0x80A4FC04
static class Symbol _s; // size: 0x4, address: 0x80A4FC0C
static class Symbol _s; // size: 0x4, address: 0x80A4FC14
static class Symbol _s; // size: 0x4, address: 0x80A4FC1C
static class Symbol _s; // size: 0x4, address: 0x80A4FC24
static class Symbol _s; // size: 0x4, address: 0x80A4FC2C
// Range: 0x802A469C -> 0x802A5BD4
class DataNode GemTrackDir::Handle(class GemTrackDir * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x18
    class MessageTimer _mt; // r1+0x28
    class DataNode _n; // r1+0x20

    // References
    // -> class DebugNotifier TheDebugNotifier;
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
}

static class Symbol _s; // size: 0x4, address: 0x80A4FC34
static class Symbol _s; // size: 0x4, address: 0x80A4FC3C
static class Symbol _s; // size: 0x4, address: 0x80A4FC44
static class Symbol _s; // size: 0x4, address: 0x80A4FC4C
static class Symbol _s; // size: 0x4, address: 0x80A4FC54
static class Symbol _s; // size: 0x4, address: 0x80A4FC5C
static class Symbol _s; // size: 0x4, address: 0x80A4FC64
static class Symbol _s; // size: 0x4, address: 0x80A4FC6C
static class Symbol _s; // size: 0x4, address: 0x80A4FC74
static class Symbol _s; // size: 0x4, address: 0x80A4FC7C
static class Symbol _s; // size: 0x4, address: 0x80A4FC84
static class Symbol _s; // size: 0x4, address: 0x80A4FC8C
static class Symbol _s; // size: 0x4, address: 0x80A4FC94
static class Symbol _s; // size: 0x4, address: 0x80A4FC9C
static class Symbol _s; // size: 0x4, address: 0x80A4FCA4
static class Symbol _s; // size: 0x4, address: 0x80A4FCAC
static class Symbol _s; // size: 0x4, address: 0x80A4FCB4
static class Symbol _s; // size: 0x4, address: 0x80A4FCBC
static class Symbol _s; // size: 0x4, address: 0x80A4FCC4
static class Symbol _s; // size: 0x4, address: 0x80A4FCCC
static class Symbol _s; // size: 0x4, address: 0x80A4FCD4
static class Symbol _s; // size: 0x4, address: 0x80A4FCDC
static class Symbol _s; // size: 0x4, address: 0x80A4FCE4
static class Symbol _s; // size: 0x4, address: 0x80A4FCEC
static class Symbol _s; // size: 0x4, address: 0x80A4FCF4
static class Symbol _s; // size: 0x4, address: 0x80A4FCFC
static class Symbol _s; // size: 0x4, address: 0x80A4FD04
static class Symbol _s; // size: 0x4, address: 0x80A4FD0C
static class Symbol _s; // size: 0x4, address: 0x80A4FD14
static class Symbol _s; // size: 0x4, address: 0x80A4FD1C
static class Symbol _s; // size: 0x4, address: 0x80A4FD24
static class Symbol _s; // size: 0x4, address: 0x80A4FD2C
static class Symbol _s; // size: 0x4, address: 0x80A4FD34
static class Symbol _s; // size: 0x4, address: 0x80A4FD3C
static class Symbol _s; // size: 0x4, address: 0x80A4FD44
static class Symbol _s; // size: 0x4, address: 0x80A4FD4C
static class Symbol _s; // size: 0x4, address: 0x80A4FD54
static class Symbol _s; // size: 0x4, address: 0x80A4FD5C
static class Symbol _s; // size: 0x4, address: 0x80A4FD64
static class Symbol _s; // size: 0x4, address: 0x80A4FD6C
static class Symbol _s; // size: 0x4, address: 0x80A4FD74
static class Symbol _s; // size: 0x4, address: 0x80A4FD7C
static class Symbol _s; // size: 0x4, address: 0x80A4FD84
static class Symbol _s; // size: 0x4, address: 0x80A4FD8C
static class Symbol _s; // size: 0x4, address: 0x80A4FD94
static class Symbol _s; // size: 0x4, address: 0x80A4FD9C
static class Symbol _s; // size: 0x4, address: 0x80A4FDA4
static class Symbol _s; // size: 0x4, address: 0x80A4FDAC
static class Symbol _s; // size: 0x4, address: 0x80A4FDB4
static class Symbol _s; // size: 0x4, address: 0x80A4FDBC
static class Symbol _s; // size: 0x4, address: 0x80A4FDC4
static class Symbol _s; // size: 0x4, address: 0x80A4FDCC
// Range: 0x802A5BD4 -> 0x802A72AC
unsigned char GemTrackDir::SyncProperty(class GemTrackDir * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
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
}

// Range: 0x802A72AC -> 0x802A73FC
unsigned char PropSync(class ObjPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14TrackInterface;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802A73FC -> 0x802A7AB4
unsigned char PropSync(class ObjPtrList & l /* r26 */, class DataNode & n /* r27 */, class DataArray * prop /* r28 */, int i /* r29 */, enum PropOp op /* r30 */) {
    // Local variables
    class iterator it; // r1+0x1C
    int which; // r3
    class TrackWidget * obj; // r31
    class TrackWidget * obj; // r31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11TrackWidget;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x2D8
} __vt__11GemTrackDir; // size: 0x2D8, address: 0x808C0E20
struct {
    // total size: 0x18
} __vt__36ObjPtrList<11TrackWidget,9ObjectDir>; // size: 0x18, address: 0x808C1178
struct {
    // total size: 0x8
} __RTTI__36ObjPtrList<11TrackWidget,9ObjectDir>; // size: 0x8, address: 0x808C11C0
struct {
    // total size: 0x18
} __vt__26ObjPtr<6RndCam,9ObjectDir>; // size: 0x18, address: 0x808C1370
struct {
    // total size: 0x8
} __RTTI__26ObjPtr<6RndCam,9ObjectDir>; // size: 0x8, address: 0x808C13B0
struct {
    // total size: 0x8
} __RTTI__P33ObjPtr<12EventTrigger,9ObjectDir>; // size: 0x8, address: 0x808C1B68
struct {
    // total size: 0x8
} __RTTI__P32ObjPtr<11RndPropAnim,9ObjectDir>; // size: 0x8, address: 0x808C1B98

