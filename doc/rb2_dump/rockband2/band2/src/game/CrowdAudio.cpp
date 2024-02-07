/*
    Compile unit: C:\rockband2\band2\src\game\CrowdAudio.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8004B29C -> 0x8004D224
*/
class Symbol name; // size: 0x4, address: 0x80A493A4
class DataArray * types; // size: 0x4, address: 0x80A493A8
class Symbol name; // size: 0x4, address: 0x80A493B0
class SampleInst : public Object {
    // total size: 0x4C
    float mVolume; // offset 0x28, size 0x4
    float mBankVolume; // offset 0x2C, size 0x4
    float mPan; // offset 0x30, size 0x4
    float mBankPan; // offset 0x34, size 0x4
    float mSpeed; // offset 0x38, size 0x4
    float mBankSpeed; // offset 0x3C, size 0x4
    class ObjPtr mSend; // offset 0x40, size 0xC
};
class SynthSampleWii : public SynthSample {
    // total size: 0x54
};
class SampleInstWii : public SampleInst {
    // total size: 0xA0
    void * mStartAddr; // offset 0x4C, size 0x4
    int mBytes; // offset 0x50, size 0x4
    unsigned char mIsLooped; // offset 0x54, size 0x1
    int mLoopSamp; // offset 0x58, size 0x4
    int mSampleRate; // offset 0x5C, size 0x4
    class Voice * mVoice; // offset 0x60, size 0x4
    float mVolume; // offset 0x64, size 0x4
    float mPan; // offset 0x68, size 0x4
    float mSpeed; // offset 0x6C, size 0x4
    class ADSR mADSR; // offset 0x70, size 0x28
    float mStartProgress; // offset 0x98, size 0x4
    enum Format mFormat; // offset 0x9C, size 0x4
};
class CrowdAudio : public Object {
    // total size: 0x80
    float mStreamVol; // offset 0x28, size 0x4
    float mMasterVol; // offset 0x2C, size 0x4
    float mCrowdVol; // offset 0x30, size 0x4
    unsigned char mEnabled; // offset 0x34, size 0x1
    unsigned char mInIntro; // offset 0x35, size 0x1
    unsigned char mDone; // offset 0x36, size 0x1
    class SampleInstWii * mSampleInst; // offset 0x38, size 0x4
    class SampleInstWii * mOldSampleInst; // offset 0x3C, size 0x4
    unsigned char mWantDuck; // offset 0x40, size 0x1
    class Fader * mResultsFader; // offset 0x44, size 0x4
    enum ExcitementLevel mLevel; // offset 0x48, size 0x4
    class String mStreamdir; // offset 0x4C, size 0xC
    float mLoopChangeTime; // offset 0x58, size 0x4
    const class DataArray * mIntro; // offset 0x5C, size 0x4
    const class DataArray * mLevels; // offset 0x60, size 0x4
    unsigned char mCrowdReacts; // offset 0x64, size 0x1
    int mLastClapBeat; // offset 0x68, size 0x4
    float mClapOffsetMs; // offset 0x6C, size 0x4
    unsigned char mMusicOver; // offset 0x70, size 0x1
    unsigned char mClapAllowed; // offset 0x71, size 0x1
    class vector mLoops; // offset 0x74, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct ExcitementLoop * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct ExcitementLoop * _M_start; // offset 0x0, size 0x4
    struct ExcitementLoop * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x8004B29C -> 0x8004B45C
void * CrowdAudio::~CrowdAudio(class CrowdAudio * const this /* r30 */) {
    // References
    // -> class GamePanel * TheGamePanel;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__10CrowdAudio;
}

static class DataNode & world; // size: 0x4, address: 0x80A493B8
// Range: 0x8004B45C -> 0x8004B4EC
class ObjectDir * CrowdAudio::DataDir(class CrowdAudio * const this /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> static class DataNode & world;
}

// Range: 0x8004B4EC -> 0x8004B5AC
void CrowdAudio::Poll(class CrowdAudio * const this /* r30 */) {
    // Local variables
    float seconds; // f0
    float ms; // f31

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x8004B5AC -> 0x8004B63C
void CrowdAudio::SetPaused(class CrowdAudio * const this /* r30 */, unsigned char paused /* r31 */) {}

// Range: 0x8004B63C -> 0x8004B6C8
void CrowdAudio::SetExcitement(class CrowdAudio * const this /* r30 */, int level /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8004B6C8 -> 0x8004B834
void CrowdAudio::SetExcitement(class CrowdAudio * const this /* r30 */, enum ExcitementLevel level /* r31 */) {
    // Local variables
    char * upSfx[5]; // r1+0x1C
    char * downSfx[5]; // r1+0x8

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Sequence;
}

// Range: 0x8004B834 -> 0x8004B8AC
void CrowdAudio::PlayLoop(class CrowdAudio * const this /* r29 */, const class DataArray * d /* r30 */) {}

// Range: 0x8004B8AC -> 0x8004B95C
void CrowdAudio::KillStream(class CrowdAudio * const this /* r31 */) {}

// Range: 0x8004B95C -> 0x8004B9E4
void CrowdAudio::PlayLoop(class CrowdAudio * const this /* r30 */, const struct ExcitementLoop & loop /* r31 */, float vol /* f31 */) {
    // References
    // -> struct [anonymous] __RTTI__10SampleInst;
    // -> struct [anonymous] __RTTI__13SampleInstWii;
}

// Range: 0x8004B9E4 -> 0x8004B9E8
void CrowdAudio::PlayStream() {}

// Range: 0x8004B9E8 -> 0x8004BA34
void CrowdAudio::SetupStream(class CrowdAudio * const this /* r31 */) {}

// Range: 0x8004BA34 -> 0x8004BA94
void CrowdAudio::UpdateVolume(class CrowdAudio * const this /* r31 */) {
    // References
    // -> class ProfileMgr TheProfileMgr;
}

// Range: 0x8004BA94 -> 0x8004BB14
void CrowdAudio::TurnOff(class CrowdAudio * const this /* r31 */) {}

// Range: 0x8004BB14 -> 0x8004BB1C
void CrowdAudio::SetMasterVolume() {}

// Range: 0x8004BB1C -> 0x8004BBC4
void CrowdAudio::SetEnabled(class CrowdAudio * const this /* r30 */, unsigned char enabled /* r31 */) {
    // References
    // -> class GamePanel * TheGamePanel;
    // -> const char * gNullStr;
}

static class Message want_intro; // size: 0x8, address: 0x80976E10
static class Message want_outro_duck; // size: 0x8, address: 0x80976E28
// Range: 0x8004BBC4 -> 0x8004BEAC
void CrowdAudio::OnIntro(class CrowdAudio * const this /* r30 */) {
    // References
    // -> static class Message want_outro_duck;
    // -> static class Message want_intro;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8004BEAC -> 0x8004BED8
void CrowdAudio::OnMusicStart() {
    // References
    // -> class GamePanel * TheGamePanel;
}

// Range: 0x8004BED8 -> 0x8004BF38
void CrowdAudio::OnWin(class CrowdAudio * const this /* r31 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x8004BF38 -> 0x8004BF3C
void CrowdAudio::PostLoad() {}

// Range: 0x8004BF3C -> 0x8004BF4C
void CrowdAudio::OnLose() {}

// Range: 0x8004BF4C -> 0x8004BFF8
void CrowdAudio::OnOutro(class CrowdAudio * const this /* r31 */) {
    // Local variables
    float db; // f31
    float ms; // f2
}

// Range: 0x8004BFF8 -> 0x8004C11C
void CrowdAudio::MaybeClap(class CrowdAudio * const this /* r30 */) {
    // Local variables
    enum ExcitementLevel excitement; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Sequence;
    // -> class Synth * TheSynth;
    // -> class GamePanel * TheGamePanel;
}

static class Symbol _s; // size: 0x4, address: 0x80A493C0
static class Symbol _s; // size: 0x4, address: 0x80A493C8
static class Symbol _s; // size: 0x4, address: 0x80A493D0
static class Symbol _s; // size: 0x4, address: 0x80A493D8
static class Symbol _s; // size: 0x4, address: 0x80A493E0
static class Symbol _s; // size: 0x4, address: 0x80A493E8
static class Symbol _s; // size: 0x4, address: 0x80A493F0
static class Symbol _s; // size: 0x4, address: 0x80A493F8
static class Symbol _s; // size: 0x4, address: 0x80A49400
static class Symbol _s; // size: 0x4, address: 0x80A49408
static class Symbol _s; // size: 0x4, address: 0x80A49410
static class Symbol _s; // size: 0x4, address: 0x80A49418
static class Symbol _s; // size: 0x4, address: 0x80A49420
static class Symbol _s; // size: 0x4, address: 0x80A49428
static class Symbol _s; // size: 0x4, address: 0x80A49430
static class Symbol _s; // size: 0x4, address: 0x80A49438
// Range: 0x8004C11C -> 0x8004D224
class DataNode CrowdAudio::Handle(class CrowdAudio * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x60
    class MessageTimer _mt; // r1+0x70
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
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x54
} __vt__10CrowdAudio; // size: 0x54, address: 0x808732BC
struct {
    // total size: 0x8
} __RTTI__10CrowdAudio; // size: 0x8, address: 0x80873330
struct {
    // total size: 0x8
} __RTTI__13SampleInstWii; // size: 0x8, address: 0x80873368
struct {
    // total size: 0x8
} __RTTI__10SampleInst; // size: 0x8, address: 0x80873390
struct {
    // total size: 0x8
} __RTTI__8Sequence; // size: 0x8, address: 0x808733C0
struct {
    // total size: 0x8
} __RTTI__5Fader; // size: 0x8, address: 0x808733E8
struct {
    // total size: 0x8
} __RTTI__13SynthPollable; // size: 0x8, address: 0x80873400
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std20_List_node<P6ObjRef>; // size: 0x8, address: 0x80873530
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class ObjRef * _M_data; // offset 0x8, size 0x4
};
struct ExcitementLoop {
    // total size: 0x54
    class SynthSampleWii mSample; // offset 0x0, size 0x54
};
struct {
    // total size: 0x8
} __RTTI__PQ210CrowdAudio14ExcitementLoop; // size: 0x8, address: 0x80873558
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class ObjectDir * _M_data; // offset 0x8, size 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class Stream {
    // total size: 0x8
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    class FaderGroup * mFaders; // offset 0x4, size 0x4
};

