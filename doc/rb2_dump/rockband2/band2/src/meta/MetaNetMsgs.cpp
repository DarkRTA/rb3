/*
    Compile unit: C:\rockband2\band2\src\meta\MetaNetMsgs.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80114E04 -> 0x801154D8
*/
class CoattailsAchievementMsg : public NetMessage {
    // total size: 0x4
};
// Range: 0x80114E04 -> 0x80114E08
void CoattailsAchievementMsg::Dispatch() {}

class BandEventPreviewMsg : public NetMessage {
    // total size: 0x8
    unsigned char mOn; // offset 0x4, size 0x1
};
// Range: 0x80114E08 -> 0x80114E40
void BandEventPreviewMsg::Save(const class BandEventPreviewMsg * const this /* r5 */) {}

// Range: 0x80114E40 -> 0x80114E8C
void BandEventPreviewMsg::Load(class BandEventPreviewMsg * const this /* r31 */) {}

static class Symbol play_preview; // size: 0x4, address: 0x80A4B7DC
static class Message playMsg; // size: 0x8, address: 0x80978FD8
// Range: 0x80114E8C -> 0x80115168
void BandEventPreviewMsg::Dispatch(class BandEventPreviewMsg * const this /* r30 */) {
    // References
    // -> static class Message playMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol play_preview;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UIPanel;
    // -> class ObjectDir * sMainDir;
}

static class Symbol synth; // size: 0x4, address: 0x80A4B7E4
static class Symbol play; // size: 0x4, address: 0x80A4B7EC
class TriggerBackSoundMsg : public NetMessage {
    // total size: 0x4
};
// Range: 0x80115168 -> 0x8011536C
void TriggerBackSoundMsg::Dispatch() {
    // Local variables
    class DataArrayPtr backSound; // r1+0x30

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol play;
    // -> static class Symbol synth;
}

// Range: 0x8011536C -> 0x801153DC
void * VerifyBuildVersionMsg::VerifyBuildVersionMsg(class VerifyBuildVersionMsg * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__21VerifyBuildVersionMsg;
}

// Range: 0x801153DC -> 0x801153EC
void VerifyBuildVersionMsg::Save(const class VerifyBuildVersionMsg * const this /* r5 */) {}

// Range: 0x801153EC -> 0x801153FC
void VerifyBuildVersionMsg::Load(class VerifyBuildVersionMsg * const this /* r5 */) {}

// Range: 0x801153FC -> 0x801154D8
void VerifyBuildVersionMsg::Dispatch(class VerifyBuildVersionMsg * const this /* r30 */) {
    // Local variables
    class String localVersion; // r1+0x24

    // References
    // -> class Debug TheDebug;
}

struct {
    // total size: 0x28
} __vt__21VerifyBuildVersionMsg; // size: 0x28, address: 0x8088C580
struct {
    // total size: 0x8
} __RTTI__21VerifyBuildVersionMsg; // size: 0x8, address: 0x8088C5D0
struct {
    // total size: 0x28
} __vt__19TriggerBackSoundMsg; // size: 0x28, address: 0x8088C5D8
struct {
    // total size: 0x8
} __RTTI__19TriggerBackSoundMsg; // size: 0x8, address: 0x8088C620
struct {
    // total size: 0x28
} __vt__19BandEventPreviewMsg; // size: 0x28, address: 0x8088C628
struct {
    // total size: 0x8
} __RTTI__19BandEventPreviewMsg; // size: 0x8, address: 0x8088C670
struct {
    // total size: 0x28
} __vt__23CoattailsAchievementMsg; // size: 0x28, address: 0x8088C678
struct {
    // total size: 0x8
} __RTTI__23CoattailsAchievementMsg; // size: 0x8, address: 0x8088C6C8

