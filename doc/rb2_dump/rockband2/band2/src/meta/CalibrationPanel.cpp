/*
    Compile unit: C:\rockband2\band2\src\meta\CalibrationPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800C1D78 -> 0x800C8088
*/
class Symbol t; // size: 0x4, address: 0x80A4A8CC
class DataArray * types; // size: 0x4, address: 0x80A4A8D0
class Symbol name; // size: 0x4, address: 0x80A4A8D8
float kAnimPerceptualOffset; // size: 0x4, address: 0x80A58AA0
float kLoopPerceptualOffset; // size: 0x4, address: 0x80A56440
enum TestState {
    tsIdle = 0,
    tsPreRoll = 1,
    tsTesting = 2,
    tsPostTest = 3,
};
class CalibrationPanel : public UIPanel {
    // total size: 0x110
    float mCycleTime; // offset 0x30, size 0x4
    class Stream * mStream; // offset 0x34, size 0x4
    class Fader * mFader; // offset 0x38, size 0x4
    unsigned char mStartASAP; // offset 0x3C, size 0x1
    class vector mTestSamples; // offset 0x40, size 0xC
    unsigned char mHalfOffAnim; // offset 0x4C, size 0x1
    unsigned char mEnableVideo; // offset 0x4D, size 0x1
    int mNumHits; // offset 0x50, size 0x4
    unsigned char mEnableAudio; // offset 0x54, size 0x1
    float mLastStreamMs; // offset 0x58, size 0x4
    enum TestState mTestState; // offset 0x5C, size 0x4
    float mPrevFrame; // offset 0x60, size 0x4
    unsigned char mHardwareMode; // offset 0x64, size 0x1
    float mAnimCycleFrames; // offset 0x68, size 0x4
    int mAnimNumCycles; // offset 0x6C, size 0x4
    int mMaxSlack; // offset 0x70, size 0x4
    float mRestingFrame; // offset 0x74, size 0x4
    int mStartRep; // offset 0x78, size 0x4
    float mPostTestStartTime; // offset 0x7C, size 0x4
    float mVolDb; // offset 0x80, size 0x4
    int mShowNumTimes; // offset 0x84, size 0x4
    float mAccel; // offset 0x88, size 0x4
    int mTimeOutRep; // offset 0x8C, size 0x4
    float mPrevLX; // offset 0x90, size 0x4
    float mPrevLY; // offset 0x94, size 0x4
    int mPad; // offset 0x98, size 0x4
    int mUserNum; // offset 0x9C, size 0x4
    unsigned char mAllowGreenButton; // offset 0xA0, size 0x1
    float mXV[5]; // offset 0xA4, size 0x14
    float mYV[5]; // offset 0xB8, size 0x14
    unsigned char mVibrationEnabled; // offset 0xCC, size 0x1
    float mLastTime; // offset 0xD0, size 0x4
    float mSensorSigma; // offset 0xD4, size 0x4
    float mSensorDeltaPeakFollow; // offset 0xD8, size 0x4
    int mTopOutliers; // offset 0xDC, size 0x4
    int mBottomOutliers; // offset 0xE0, size 0x4
};
// Range: 0x800C1D78 -> 0x800C1E90
void * CalibrationPanel::CalibrationPanel(class CalibrationPanel * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__16CalibrationPanel;
}

// Range: 0x800C1E90 -> 0x800C1FC0
void * CalibrationPanel::~CalibrationPanel(class CalibrationPanel * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__16CalibrationPanel;
}

// Range: 0x800C1FC0 -> 0x800C2080
void CalibrationPanel::Poll(class CalibrationPanel * const this /* r31 */) {}

// Range: 0x800C2080 -> 0x800C243C
void CalibrationPanel::UpdateAnimation(class CalibrationPanel * const this /* r31 */) {
    // Local variables
    float fAudioSyncTime; // f0
    float fAudioSyncTime; // f0
    float frame; // f31

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

// Range: 0x800C243C -> 0x800C25D8
float CalibrationPanel::HandlePreAndPostTestAnim(class CalibrationPanel * const this /* r31 */, float frame /* f31 */) {
    // Local variables
    int i; // r5
    float stopFrame; // f2
}

// Range: 0x800C25D8 -> 0x800C2C94
void CalibrationPanel::UpdateLabel(class CalibrationPanel * const this /* r29 */) {
    // Local variables
    float audioCycleTime; // f0
    int nRep; // r0
    char str[512]; // r1+0x28
    int countoff; // r0

    // References
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UILabel;
}

// Range: 0x800C2C94 -> 0x800C2F90
void CalibrationPanel::UpdateProgress(class CalibrationPanel * const this /* r31 */, unsigned char bFilter /* r25 */) {
    // Local variables
    float progress; // r31
    float fFilterOut; // f31

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12RndTransAnim;
}

// Range: 0x800C2F90 -> 0x800C2F94
void CalibrationPanel::Draw() {}

// Range: 0x800C2F94 -> 0x800C3048
void CalibrationPanel::UpdateStream(class CalibrationPanel * const this /* r31 */) {}

static class Symbol G; // size: 0x4, address: 0x80A4A8E0
static class Symbol A; // size: 0x4, address: 0x80A4A8E8
static class Symbol cal_video_desc_guitar; // size: 0x4, address: 0x80A4A8F0
static class Symbol cal_video_desc_drum; // size: 0x4, address: 0x80A4A8F8
static class Symbol cal_video_desc_pad; // size: 0x4, address: 0x80A4A900
static class Symbol cal_video_desc_calbert; // size: 0x4, address: 0x80A4A908
static class Symbol cal_audio_desc_guitar; // size: 0x4, address: 0x80A4A910
static class Symbol cal_audio_desc_drum; // size: 0x4, address: 0x80A4A918
static class Symbol cal_audio_desc_pad; // size: 0x4, address: 0x80A4A920
static class Symbol cal_audio_desc_calbert; // size: 0x4, address: 0x80A4A928
static class Symbol cal_hw_audio_title; // size: 0x4, address: 0x80A4A930
static class Symbol cal_hw_video_title; // size: 0x4, address: 0x80A4A938
static class Symbol cal_audio_title; // size: 0x4, address: 0x80A4A940
static class Symbol cal_video_title; // size: 0x4, address: 0x80A4A948
static class Symbol one; // size: 0x4, address: 0x80A4A950
// Range: 0x800C3048 -> 0x800C4514
class DataNode CalibrationPanel::OnInitializeContent(class CalibrationPanel * const this /* r29 */) {
    // Local variables
    class BandUser * user; // r0
    enum ControllerType controllerType; // r30
    const char * streamFile; // r25

    // References
    // -> class Synth * TheSynth;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__5Fader;
    // -> class Symbol name;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> struct [anonymous] __RTTI__7UILabel;
    // -> static class Symbol one;
    // -> static class Symbol cal_video_title;
    // -> static class Symbol cal_audio_title;
    // -> static class Symbol cal_hw_video_title;
    // -> static class Symbol cal_hw_audio_title;
    // -> static class Symbol cal_audio_desc_calbert;
    // -> static class Symbol cal_audio_desc_pad;
    // -> static class Symbol cal_audio_desc_drum;
    // -> static class Symbol cal_audio_desc_guitar;
    // -> static class Symbol cal_video_desc_calbert;
    // -> static class Symbol cal_video_desc_pad;
    // -> static class Symbol cal_video_desc_drum;
    // -> static class Symbol cal_video_desc_guitar;
    // -> static class Symbol A;
    // -> static class Symbol G;
    // -> class InputMgr * TheInputMgr;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12RndTransAnim;
}

// Range: 0x800C4514 -> 0x800C45BC
void CalibrationPanel::StartAudio(class CalibrationPanel * const this /* r31 */) {}

// Range: 0x800C45BC -> 0x800C45E4
void CalibrationPanel::StopAudio() {}

static class DataNode & cal_num_hits; // size: 0x4, address: 0x80A4A958
static class DataNode & cal_num_outliers; // size: 0x4, address: 0x80A4A960
// Range: 0x800C45E4 -> 0x800C4910
class DataNode CalibrationPanel::OnStartTest(class CalibrationPanel * const this /* r31 */, class DataArray * msg /* r26 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> static class DataNode & cal_num_outliers;
    // -> static class DataNode & cal_num_hits;
}

// Range: 0x800C4910 -> 0x800C494C
void CalibrationPanel::PrepareHwCalibrationState() {}

// Range: 0x800C494C -> 0x800C4994
void CalibrationPanel::TerminateHwCalibrationState(class CalibrationPanel * const this /* r31 */) {}

// Range: 0x800C4994 -> 0x800C59C0
void CalibrationPanel::InitializeVisuals(class CalibrationPanel * const this /* r29 */) {
    // Local variables
    class BandUser * user; // r0
    enum ControllerType controllerType; // r30

    // References
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class InputMgr * TheInputMgr;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

// Range: 0x800C59C0 -> 0x800C5B48
void CalibrationPanel::EndTest(class CalibrationPanel * const this /* r31 */) {
    // Local variables
    int i; // r30
    int i; // r30

    // References
    // -> class Debug TheDebug;
}

// Range: 0x800C5B48 -> 0x800C5C20
class RndGroup * CalibrationPanel::GetAnimation() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

// Range: 0x800C5C20 -> 0x800C5CB0
float CalibrationPanel::GetAudioTimeMs(const class CalibrationPanel * const this /* r31 */) {
    // Local variables
    float offset; // f31

    // References
    // -> class ProfileMgr TheProfileMgr;
}

// Range: 0x800C5CB0 -> 0x800C5D00
class DataNode CalibrationPanel::OnMsg(class CalibrationPanel * const this /* r31 */) {}

// Range: 0x800C5D00 -> 0x800C5EA8
class DataNode CalibrationPanel::OnMsg(class CalibrationPanel * const this /* r26 */, const class ButtonDownMsg & msg /* r27 */) {
    // Local variables
    unsigned char bTestButton; // r28
}

static class DataNode & trace_sensors; // size: 0x4, address: 0x80A4A968
// Range: 0x800C5EA8 -> 0x800C6064
void CalibrationPanel::ScanHardwareModeInputs(class CalibrationPanel * const this /* r30 */) {
    // Local variables
    float LX; // f31
    float sensorDelta; // f30
    float peakFollowDelta; // f0

    // References
    // -> static class DataNode & trace_sensors;
}

// Range: 0x800C6064 -> 0x800C62E4
void CalibrationPanel::TriggerCalibration(class CalibrationPanel * const this /* r31 */, int nPadNum /* r29 */) {
    // Local variables
    float fTime; // r1+0xC
    float fRawTime; // f0
    float fNeutral; // f31
    class BandUser * user; // r0
    enum ControllerType controllerType; // r4

    // References
    // -> float kLoopPerceptualOffset;
    // -> float kAnimPerceptualOffset;
    // -> class InputMgr * TheInputMgr;
    // -> class ProfileMgr TheProfileMgr;
}

// Range: 0x800C62E4 -> 0x800C64B8
int CalibrationPanel::GetAverageTestTime(class CalibrationPanel * const this /* r30 */) {
    // Local variables
    float fAvg; // f31
    int i; // r29
    float fResult; // f31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800C64B8 -> 0x800C6508
int CalibrationPanel::GetTestRep(const class CalibrationPanel * const this /* r31 */) {
    // Local variables
    int nRawRep; // r3
}

// Range: 0x800C6508 -> 0x800C65C4
float CalibrationPanel::GetSampleSpread(const class CalibrationPanel * const this /* r31 */) {
    // Local variables
    float fMin; // f0
    float fMax; // f1
    float fSpread; // f1

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800C65C4 -> 0x800C66BC
unsigned char CalibrationPanel::GetTestQuality(const class CalibrationPanel * const this /* r31 */) {
    // Local variables
    unsigned char bGoodQuality; // r30
    int i; // r29

    // References
    // -> class Debug TheDebug;
}

// Range: 0x800C66BC -> 0x800C66D0
unsigned char CalibrationPanel::GetIsProcessingInput() {}

// Range: 0x800C66D0 -> 0x800C6714
float CalibrationPanel::ReshapeTime() {
    // Local variables
    float x; // f3
    float y; // f3
}

// Range: 0x800C6714 -> 0x800C675C
void CalibrationPanel::Enter(class CalibrationPanel * const this /* r31 */) {
    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x800C675C -> 0x800C6818
void CalibrationPanel::Exit(class CalibrationPanel * const this /* r31 */) {
    // References
    // -> class Rnd & TheRnd;
}

static class Symbol _s; // size: 0x4, address: 0x80A4A970
static class Symbol _s; // size: 0x4, address: 0x80A4A978
static class Symbol _s; // size: 0x4, address: 0x80A4A980
static class Symbol _s; // size: 0x4, address: 0x80A4A988
static class Symbol _s; // size: 0x4, address: 0x80A4A990
// Range: 0x800C6818 -> 0x800C7374
class DataNode CalibrationPanel::Handle(class CalibrationPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x44
    class MessageTimer _mt; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode _n; // r1+0x58

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__13ButtonDownMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__19JoypadConnectionMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A4A998
static class Symbol _s; // size: 0x4, address: 0x80A4A9A0
static class Symbol _s; // size: 0x4, address: 0x80A4A9A8
static class Symbol _s; // size: 0x4, address: 0x80A4A9B0
static class Symbol _s; // size: 0x4, address: 0x80A4A9B8
static class Symbol _s; // size: 0x4, address: 0x80A4A9C0
static class Symbol _s; // size: 0x4, address: 0x80A4A9C8
static class Symbol _s; // size: 0x4, address: 0x80A4A9D0
static class Symbol _s; // size: 0x4, address: 0x80A4A9D8
static class Symbol _s; // size: 0x4, address: 0x80A4A9E0
static class Symbol _s; // size: 0x4, address: 0x80A4A9E8
static class Symbol _s; // size: 0x4, address: 0x80A4A9F0
static class Symbol _s; // size: 0x4, address: 0x80A4A9F8
// Range: 0x800C7374 -> 0x800C8088
unsigned char CalibrationPanel::SyncProperty(class CalibrationPanel * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
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
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x8
} __RTTI__12RndTransAnim; // size: 0x8, address: 0x80880AA0
struct {
    // total size: 0x8
} __RTTI__7UILabel; // size: 0x8, address: 0x80880AF0
struct {
    // total size: 0xB0
} __vt__16CalibrationPanel; // size: 0xB0, address: 0x80880CA0
struct {
    // total size: 0x8
} __RTTI__16CalibrationPanel; // size: 0x8, address: 0x80880D80
struct {
    // total size: 0xC
} __vt__19JoypadConnectionMsg; // size: 0xC, address: 0x80880D88
struct {
    // total size: 0x8
} __RTTI__19JoypadConnectionMsg; // size: 0x8, address: 0x80880DB8

