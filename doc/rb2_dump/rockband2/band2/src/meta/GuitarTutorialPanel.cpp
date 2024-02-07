/*
    Compile unit: C:\rockband2\band2\src\meta\GuitarTutorialPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800ECB24 -> 0x800EF9C4
*/
class DataArray * types; // size: 0x4, address: 0x80A4B078
class Symbol name; // size: 0x4, address: 0x80A4B080
class GuitarTutorialPanel * TheGuitarTutorialPanel; // size: 0x4, address: 0x80A4B084
// Range: 0x800ECB24 -> 0x800ECB60
static unsigned char StrumBarPressed() {}

class GuitarTutorialPanel : public TutorialPanel {
    // total size: 0x1C8
    unsigned char mFretPressed[5]; // offset 0xC0, size 0x5
    unsigned char mStrum; // offset 0xC5, size 0x1
    class RndMesh * mFretChecks[5]; // offset 0xC8, size 0x14
    class RndMesh * mFrets[5]; // offset 0xDC, size 0x14
    unsigned char mAllFretsOff[5]; // offset 0xF0, size 0x5
    unsigned char mInTuningMode; // offset 0xF5, size 0x1
    int mFretTuneCount[5]; // offset 0xF8, size 0x14
    class Object * mTuneCallback; // offset 0x10C, size 0x4
    class vector mTuneSfx; // offset 0x110, size 0xC
    unsigned char mFretChecksFading[5]; // offset 0x11C, size 0x5
    unsigned char mInHopoTraining; // offset 0x121, size 0x1
    unsigned char mInHopo; // offset 0x122, size 0x1
    unsigned char mInValidHopo; // offset 0x123, size 0x1
    int mHighFret; // offset 0x124, size 0x4
    int mHopoSteps; // offset 0x128, size 0x4
    int mHoposHit; // offset 0x12C, size 0x4
    class Timer mLastHitMs; // offset 0x130, size 0x38
    class RndMatAnim * mFretCheckAnims[5]; // offset 0x168, size 0x14
    class vector mHopoSfx; // offset 0x17C, size 0xC
    class Object * mHopoCallback; // offset 0x188, size 0x4
    class ObjDirPtr mBank; // offset 0x18C, size 0xC
};
// Range: 0x800ECB60 -> 0x800ECC88
void * GuitarTutorialPanel::GuitarTutorialPanel(class GuitarTutorialPanel * const this /* r31 */) {
    // Local variables
    int i; // r5

    // References
    // -> class GuitarTutorialPanel * TheGuitarTutorialPanel;
    // -> struct [anonymous] __vt__21ObjDirPtr<9ObjectDir>;
    // -> struct [anonymous] __vt__19GuitarTutorialPanel;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Sfx * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Sfx * * _M_start; // offset 0x0, size 0x4
    class Sfx * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x800ECC88 -> 0x800ECF50
void * GuitarTutorialPanel::~GuitarTutorialPanel(class GuitarTutorialPanel * const this /* r30 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__21ObjDirPtr<9ObjectDir>;
}

// Range: 0x800ECF50 -> 0x800EDD04
void GuitarTutorialPanel::Enter(class GuitarTutorialPanel * const this /* r30 */) {
    // Local variables
    char * tune_strums[15]; // r1+0x5C
    char * hopo_strums[5]; // r1+0x48
    int i; // r31

    // References
    // -> struct [anonymous] __RTTI__3Sfx;
    // -> class Synth * TheSynth;
    // -> struct [anonymous] __RTTI__10RndMatAnim;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class GuitarTutorialPanel * TheGuitarTutorialPanel;
}

// Range: 0x800EDD04 -> 0x800EDD14
void GuitarTutorialPanel::Exit() {}

// Range: 0x800EDD14 -> 0x800EDDBC
void GuitarTutorialPanel::Poll(class GuitarTutorialPanel * const this /* r31 */) {
    // Local variables
    unsigned char done; // r1+0x8
}

// Range: 0x800EDDBC -> 0x800EDFDC
void GuitarTutorialPanel::PollTune(class GuitarTutorialPanel * const this /* r29 */, class JoypadData * joyData /* r31 */, class VoiceMgr * voiceMgr /* r28 */, unsigned char & done /* r30 */) {
    // Local variables
    int fret; // r1+0x14
    int count; // r1+0x10
    unsigned char newStrum; // r0
    class Message miss_tune_msg; // r1+0x28
    int i; // r4

    // References
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x800EDFDC -> 0x800EE32C
unsigned char GuitarTutorialPanel::PollHopos(class GuitarTutorialPanel * const this /* r29 */, class JoypadData * joyData /* r27 */, class VoiceMgr * voiceMgr /* r30 */) {
    // Local variables
    int fret; // r1+0x14
    int count; // r1+0x10
    unsigned char newStrum; // r0
    unsigned char fretChange; // r27
    class Message hopo_hit_msg; // r1+0x28

    // References
    // -> struct [anonymous] __vt__7Message;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

// Range: 0x800EE32C -> 0x800EE34C
void GuitarTutorialPanel::FretOff() {}

// Range: 0x800EE34C -> 0x800EE36C
void GuitarTutorialPanel::FretOn() {}

// Range: 0x800EE36C -> 0x800EE3E4
void GuitarTutorialPanel::ForceFrets(class GuitarTutorialPanel * const this /* r29 */, unsigned char * fretPressed /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x800EE3E4 -> 0x800EE3EC
void GuitarTutorialPanel::OnAllFretsOff() {}

// Range: 0x800EE3EC -> 0x800EE498
void GuitarTutorialPanel::AnimateFrets(class GuitarTutorialPanel * const this /* r27 */, class JoypadData * joyData /* r28 */, int & fretPressed /* r29 */, int & numFretsPressed /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x800EE498 -> 0x800EE514
void GuitarTutorialPanel::AddCheck(class GuitarTutorialPanel * const this /* r29 */, int fret /* r30 */) {}

// Range: 0x800EE514 -> 0x800EE550
void GuitarTutorialPanel::RemoveChecks() {
    // Local variables
    int i; // r5
}

// Range: 0x800EE550 -> 0x800EE60C
void GuitarTutorialPanel::FadeChecks(class GuitarTutorialPanel * const this /* r30 */) {
    // Local variables
    int i; // r31
    float animFrame; // f1
}

// Range: 0x800EE60C -> 0x800EE6A4
void GuitarTutorialPanel::Init(class GuitarTutorialPanel * const this /* r30 */) {
    // Local variables
    int i; // r6
    class JoypadData * joyData; // r0
}

// Range: 0x800EE6A4 -> 0x800EE6A8
void GuitarTutorialPanel::InitTuningMode() {}

// Range: 0x800EE6A8 -> 0x800EE708
void GuitarTutorialPanel::SetTuningMode(class GuitarTutorialPanel * const this /* r29 */, unsigned char inTuningMode /* r30 */, class Object * callback /* r31 */) {}

// Range: 0x800EE708 -> 0x800EE710
unsigned char GuitarTutorialPanel::IsTuning() {}

// Range: 0x800EE710 -> 0x800EE794
class DataNode GuitarTutorialPanel::OnStartTuningMode(class GuitarTutorialPanel * const this /* r30 */, class DataArray * msg /* r31 */) {
    // Local variables
    class Object * callback; // r6
}

// Range: 0x800EE794 -> 0x800EE894
void GuitarTutorialPanel::PlayTuneSfx(class GuitarTutorialPanel * const this /* r27 */) {
    // Local variables
    int fretIdx; // r29
    int i; // r28
    int fretSfxId; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static int kMaxTuningCount;
}

// Range: 0x800EE894 -> 0x800EEAA0
void GuitarTutorialPanel::StringTuned(class GuitarTutorialPanel * const this /* r29 */, int fret /* r28 */) {
    // Local variables
    class Message msg; // r1+0x28

    // References
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x800EEAA0 -> 0x800EEAA4
void GuitarTutorialPanel::InitHopoMode() {}

// Range: 0x800EEAA4 -> 0x800EEB20
void GuitarTutorialPanel::SetHopoTraining(class GuitarTutorialPanel * const this /* r29 */, unsigned char inHopoTraining /* r30 */, class Object * callback /* r31 */) {}

// Range: 0x800EEB20 -> 0x800EEB28
unsigned char GuitarTutorialPanel::IsHopoTraining() {}

// Range: 0x800EEB28 -> 0x800EEBAC
class DataNode GuitarTutorialPanel::OnSetHopoTraining(class GuitarTutorialPanel * const this /* r30 */, class DataArray * msg /* r31 */) {
    // Local variables
    class Object * callback; // r6
}

// Range: 0x800EEBAC -> 0x800EEDBC
void GuitarTutorialPanel::PlayFret(class GuitarTutorialPanel * const this /* r30 */, int fret /* r31 */) {
    // Local variables
    class Message msg; // r1+0x28
    int i; // r28

    // References
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x800EEDBC -> 0x800EEE30
void GuitarTutorialPanel::UpdateHopoFret(class GuitarTutorialPanel * const this /* r30 */, int highFret /* r31 */) {}

// Range: 0x800EEE30 -> 0x800EEE3C
void GuitarTutorialPanel::InvalidateHopo() {}

// Range: 0x800EEE3C -> 0x800EEE40
void GuitarTutorialPanel::HopoHit() {}

// Range: 0x800EEE40 -> 0x800EEE94
void GuitarTutorialPanel::StopNotes(class GuitarTutorialPanel * const this /* r30 */) {
    // Local variables
    int i; // r31
}

static class Symbol _s; // size: 0x4, address: 0x80A4B08C
static class Symbol _s; // size: 0x4, address: 0x80A4B094
static class Symbol _s; // size: 0x4, address: 0x80A4B09C
static class Symbol _s; // size: 0x4, address: 0x80A4B0A4
static class Symbol _s; // size: 0x4, address: 0x80A4B0AC
static class Symbol _s; // size: 0x4, address: 0x80A4B0B4
static class Symbol _s; // size: 0x4, address: 0x80A4B0BC
// Range: 0x800EEE94 -> 0x800EF9C4
class DataNode GuitarTutorialPanel::Handle(class GuitarTutorialPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x40
    class MessageTimer _mt; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode _n; // r1+0x50
    class DataNode _n; // r1+0x48

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

struct {
    // total size: 0x8
} __RTTI__10RndMatAnim; // size: 0x8, address: 0x80886DD8
struct {
    // total size: 0xE4
} __vt__19GuitarTutorialPanel; // size: 0xE4, address: 0x80886EE8
struct {
    // total size: 0x8
} __RTTI__19GuitarTutorialPanel; // size: 0x8, address: 0x80887010
struct {
    // total size: 0x8
} __RTTI__3Sfx; // size: 0x8, address: 0x808870E8
struct {
    // total size: 0x8
} __RTTI__PP3Sfx; // size: 0x8, address: 0x808871F8
struct _OKToMemCpy {
    // total size: 0x1
};
static int kMaxTuningCount; // size: 0x4, address: 0x80A56534

