/*
    Compile unit: C:\rockband2\band2\src\bandtrack\VocalTrack.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8002DAF8 -> 0x800389EC
*/
class Symbol name; // size: 0x4, address: 0x80A4913C
class DebugFailer {
    // total size: 0x1
};
// Range: 0x8002DAF8 -> 0x8002DB7C
void VocalTrack::InvalidateTimedMeshes(class VocalTrack * const this /* r30 */, class deque & l /* r31 */, float ms /* f31 */) {}

// Range: 0x8002DB7C -> 0x8002DBE0
void VocalTrack::ClearTimedMeshList(class VocalTrack * const this /* r30 */, class deque & l /* r31 */) {}

// Range: 0x8002DBE0 -> 0x8002DC64
void VocalTrack::InvalidateNoteTubes(class VocalTrack * const this /* r30 */, class deque & l /* r31 */, float ms /* f31 */) {}

// Range: 0x8002DC64 -> 0x8002DCC8
void VocalTrack::ClearNoteTubes(class VocalTrack * const this /* r30 */, class deque & l /* r31 */) {}

static unsigned char gDebugSpew; // size: 0x1, address: 0x80A49140
// Range: 0x8002DCC8 -> 0x8002DCE8
static class DataNode ToggleDebugSpew() {
    // References
    // -> static unsigned char gDebugSpew;
}

// Range: 0x8002DCE8 -> 0x8002DFA4
void * VocalTrack::VocalTrack(class VocalTrack * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__34ObjPtr<13VocalTrackDir,9ObjectDir>;
    // -> struct [anonymous] __vt__10VocalTrack;
}

struct pair {
    // total size: 0x10
    int first; // offset 0x0, size 0x4
    class vector second; // offset 0x4, size 0xC
};
struct pair {
    // total size: 0xC
    class Symbol first; // offset 0x0, size 0x4
    class list second; // offset 0x4, size 0x8
};
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
// Range: 0x8002DFA4 -> 0x8002E188
void * VocalTrack::~VocalTrack(class VocalTrack * const this /* r29 */) {
    // Local variables
    struct _Rb_tree_iterator it; // r1+0x1C
    struct _Rb_tree_iterator it; // r1+0x18

    // References
    // -> struct [anonymous] __vt__10VocalTrack;
}

class TambourineGemPool {
    // total size: 0x5C
    class deque mFreeGems; // offset 0x0, size 0x28
    class deque mUsedGems; // offset 0x28, size 0x28
    class vector mHitIds; // offset 0x50, size 0xC
};
// Range: 0x8002E188 -> 0x8002E4E8
void * TambourineGemPool::~TambourineGemPool(class TambourineGemPool * const this /* r29 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
class list : public _List_base {
    // total size: 0x8
};
// Range: 0x8002E4E8 -> 0x8002EC30
void VocalTrack::Init(class VocalTrack * const this /* r28 */) {
    // Local variables
    int trackNum; // r0
    class list textVec; // r1+0x50
    int i; // r27
    int i; // r29
    class BandUser * user; // r0
    class GameplayOptions * options; // r0

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std21_List_node<P7RndText>;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> class GameConfig * TheGameConfig;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class RndText * _M_data; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std21_List_node<P7RndText>; // size: 0x8, address: 0x80870740
// Range: 0x8002EC30 -> 0x8002EE30
class RndLine * VocalTrack::FindNoteTube() {
    // Local variables
    int i; // r7
}

class Ray {
    // total size: 0x10
public:
    class Vector2 base; // offset 0x0, size 0x8
    class Vector2 dir; // offset 0x8, size 0x8
};
// Range: 0x8002EE30 -> 0x8002F148
unsigned char VocalTrack::CheckOverlap(class RndLine * line /* r30 */) {
    // Local variables
    class Vector2 highPoint; // r1+0x40
    class Vector2 lowPoint; // r1+0x38
    float angle; // f31
    class Vector2 thisPoint; // r1+0x30
    class Vector2 nextPoint; // r1+0x28
    int i; // r31
    class Vector3 p; // r1+0x80
    float lastAngle; // f29
    float radius; // f0
    float bisect; // f28
    class Ray highRay; // r1+0x68
    class Ray pointRay; // r1+0x58
    class Vector2 intersect; // r1+0x20
    class Ray lowRay; // r1+0x48
}

// Range: 0x8002F164 -> 0x8002F3E0
void VocalTrack::FixupNoteTube(class VocalTrack * const this /* r30 */, class RndLine * line /* r31 */) {
    // Local variables
    int lastIndex; // r29
    class Vector3 start; // r1+0x40
    class Vector3 end; // r1+0x30
    float xLen; // f31
    int count; // r28
    int i; // r27
    class Vector3 p; // r1+0x20
    class Vector3 avg; // r1+0x10
}

class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x8002F3E0 -> 0x8002F984
class RndLine * VocalTrack::CreateNoteTube(class VocalTrack * const this /* r29 */, int numPoints /* r30 */) {
    // Local variables
    class RndLine * line; // r26
    class vector v; // r1+0xC8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Symbol name;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PP7RndLine;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndLine;
}

struct _OKToMemCpy {
    // total size: 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__PP7RndLine; // size: 0x8, address: 0x80870758
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class RndLine * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class RndLine * * _M_start; // offset 0x0, size 0x4
    class RndLine * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
// Range: 0x8002F984 -> 0x8002FE74
void VocalTrack::ReturnNoteTube(class VocalTrack * const this /* r30 */, class RndLine * line /* r1+0x8 */) {
    // Local variables
    class vector v; // r1+0xC0

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PP7RndLine;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8002FE74 -> 0x800306F0
class RndText * VocalTrack::CreateText(class VocalTrack * const this /* r28 */, class Symbol & srcName /* r29 */) {
    // Local variables
    class RndText * text; // r30
    class list v; // r1+0x1D8

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std21_List_node<P7RndText>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndText;
}

// Range: 0x800306F0 -> 0x80030B80
void VocalTrack::ReturnText(class VocalTrack * const this /* r29 */, class Symbol & srcName /* r30 */, class RndText * text /* r31 */) {
    // Local variables
    class list v; // r1+0x100

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std21_List_node<P7RndText>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80030B80 -> 0x80030D54
class RndMesh * VocalTrack::CreateMesh(class VocalTrack * const this /* r28 */) {
    // Local variables
    class RndMesh * mesh; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
}

// Range: 0x80030D54 -> 0x80030E00
void VocalTrack::ReturnMesh(class RndMesh * mesh /* r1+0x8 */) {}

// Range: 0x80030E00 -> 0x80030EA4
void VocalTrack::SetDir(class VocalTrack * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> struct [anonymous] __RTTI__13VocalTrackDir;
}

// Range: 0x80030EA4 -> 0x80030F14
unsigned char VocalTrack::WantBeatLines(int tick /* r31 */) {
    // Local variables
    const class vector & phrases; // r0
    const class VocalPhrase * p; // r5

    // References
    // -> class SongDB * TheSongDB;
}

class VocalNoteList {
    // total size: 0x30
    class vector mPhrases; // offset 0x0, size 0xC
    class vector mNotes; // offset 0xC, size 0xC
    class vector mTambourineGems; // offset 0x18, size 0xC
    class String mSongName; // offset 0x24, size 0xC
};
// Range: 0x80030F14 -> 0x80030F9C
unsigned char VocalTrack::MasksVisible(class VocalTrack * const this /* r29 */) {}

// Range: 0x80030F9C -> 0x80030FA8
void VocalTrack::SetStaticVocals() {}

// Range: 0x80030FA8 -> 0x8003109C
void VocalTrack::SetVocalStyle(class VocalTrack * const this /* r31 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x8003109C -> 0x80031158
void TambourineGemPool::ReleaseGemsBefore(class TambourineGemPool * const this /* r31 */, float time /* f31 */) {}

// Range: 0x80031158 -> 0x800313CC
void VocalTrack::RebuildHUD(class VocalTrack * const this /* r31 */) {
    // Local variables
    class vector & phrases; // r0
    const class VocalPhrase * const & thisPhrase; // r0
    const class VocalPhrase * nextPhrase; // r0
    const class VocalPhrase * lastPhrase; // r1+0xC
    float from; // f31
    float to; // f0

    // References
    // -> class SongDB * TheSongDB;
}

enum MatchType {
    kPitchMatching = 0,
    kPhonemeMatching = 1,
    kTambourineMatching = 2,
    kFreestyleMatching = 3,
};
struct SpeechAnalysis {
    // total size: 0x22
    unsigned char logEnergy; // offset 0x0, size 0x1
    unsigned char peakMagnitudes[32]; // offset 0x1, size 0x20
    unsigned char sequentialError; // offset 0x21, size 0x1
};
class PhoneCloud {
    // total size: 0x114
protected:
    int mCount; // offset 0x0, size 0x4
    struct SpeechAnalysis mAnalyses[8]; // offset 0x4, size 0x110
};
struct _Deque_iterator_base {
    // total size: 0x10
    class PhoneCloud * * _M_cur; // offset 0x0, size 0x4
    class PhoneCloud * * _M_first; // offset 0x4, size 0x4
    class PhoneCloud * * _M_last; // offset 0x8, size 0x4
    class PhoneCloud * * * _M_node; // offset 0xC, size 0x4
};
struct _Deque_iterator : public _Deque_iterator_base {
    // total size: 0x10
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class PhoneCloud * * * _M_data; // offset 0x0, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    unsigned long _M_data; // offset 0x0, size 0x4
};
class _Deque_base {
    // total size: 0x28
protected:
    struct _Deque_iterator _M_start; // offset 0x0, size 0x10
    struct _Deque_iterator _M_finish; // offset 0x10, size 0x10
    class _STLP_alloc_proxy _M_map; // offset 0x20, size 0x4
    class _STLP_alloc_proxy _M_map_size; // offset 0x24, size 0x4
};
class deque : protected _Deque_base {
    // total size: 0x28
};
struct _Deque_iterator_base {
    // total size: 0x10
    int * _M_cur; // offset 0x0, size 0x4
    int * _M_first; // offset 0x4, size 0x4
    int * _M_last; // offset 0x8, size 0x4
    int * * _M_node; // offset 0xC, size 0x4
};
struct _Deque_iterator : public _Deque_iterator_base {
    // total size: 0x10
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    int * * _M_data; // offset 0x0, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    unsigned long _M_data; // offset 0x0, size 0x4
};
class _Deque_base {
    // total size: 0x28
protected:
    struct _Deque_iterator _M_start; // offset 0x0, size 0x10
    struct _Deque_iterator _M_finish; // offset 0x10, size 0x10
    class _STLP_alloc_proxy _M_map; // offset 0x20, size 0x4
    class _STLP_alloc_proxy _M_map_size; // offset 0x24, size 0x4
};
class deque : protected _Deque_base {
    // total size: 0x28
};
class SaytrState {
    // total size: 0x54
protected:
    int mHistoryTime; // offset 0x0, size 0x4
    class deque mPhoneClouds; // offset 0x4, size 0x28
    class deque mPhoneTimes; // offset 0x2C, size 0x28
};
struct ComplexSample {
    // total size: 0x4
    signed short real; // offset 0x0, size 0x2
    signed short imag; // offset 0x2, size 0x2
};
class VocalInterpreter {
    // total size: 0x824
protected:
    int inputSampleRate; // offset 0x0, size 0x4
    int afterSampleRate; // offset 0x4, size 0x4
    signed short mLowpassFIR[12]; // offset 0x8, size 0x18
    int mBufferSize; // offset 0x20, size 0x4
    struct ComplexSample mTwiddleValues[256]; // offset 0x24, size 0x400
    signed short mBuffer[256]; // offset 0x424, size 0x200
    signed short mSavedBuffer[256]; // offset 0x624, size 0x200
};
class VocalEvaluator {
    // total size: 0x10
protected:
    class BinStream * mPanStream; // offset 0x0, size 0x4
    float mCurrentTime; // offset 0x4, size 0x4
    float mMsPerFrame; // offset 0x8, size 0x4
    unsigned char mLastSize; // offset 0xC, size 0x1
};
class VocalScorer {
    // total size: 0xF8
protected:
    float mNonPitchTimingScale; // offset 0x0, size 0x4
    float mNonPitchSimilarScale; // offset 0x4, size 0x4
    float mNonPitchMatchWeight; // offset 0x8, size 0x4
    float mNonPitchWarpWeight; // offset 0xC, size 0x4
    float mNonPitchTransitWeight; // offset 0x10, size 0x4
    class SaytrState mMicHistory; // offset 0x14, size 0x54
    class SaytrState mRefHistory; // offset 0x68, size 0x54
    class deque mHistoryCorresponds; // offset 0xBC, size 0x28
    class VocalEvaluator mVocalEvaluator; // offset 0xE4, size 0x10
    class FileStream * mOutputStream; // offset 0xF4, size 0x4
};
class DelayLine {
    // total size: 0x194
    float mData[100]; // offset 0x0, size 0x190
    int mCur; // offset 0x190, size 0x4
};
class VocalPlayer : public Player {
    // total size: 0x590
public:
    unsigned char mTutorialArrow; // offset 0x109, size 0x1
private:
    class Performer * mBandPerformer; // offset 0x10C, size 0x4
    unsigned char mSpoofed; // offset 0x110, size 0x1
    class VocalTrack * mTrack; // offset 0x114, size 0x4
    class SaytrMic * mMic; // offset 0x118, size 0x4
    class BeatMaster * mBeatMaster; // offset 0x11C, size 0x4
    unsigned char mAutoPlay; // offset 0x120, size 0x1
    class VocalNoteList * mVocalNoteList; // offset 0x124, size 0x4
    class vector mNoteWeights; // offset 0x128, size 0xC
    int mPhraseRatingTotal; // offset 0x134, size 0x4
    int mTotalPhrases; // offset 0x138, size 0x4
    unsigned char * mWeightData; // offset 0x13C, size 0x4
    int mNumWeights; // offset 0x140, size 0x4
    int mTotalTambourinePoints; // offset 0x144, size 0x4
    int mBonusTambourinePoints; // offset 0x148, size 0x4
    int mSinging; // offset 0x14C, size 0x4
    float mDetune; // offset 0x150, size 0x4
    float mNextPacketSendTime; // offset 0x154, size 0x4
    float mMaxDetune; // offset 0x158, size 0x4
    float mPacketPeriodMs; // offset 0x15C, size 0x4
    float mRemotePhraseMeterFrac; // offset 0x160, size 0x4
    float mPhraseScoreMax; // offset 0x164, size 0x4
    float mPhraseScoreCap; // offset 0x168, size 0x4
    int mPhraseScoreCapNote; // offset 0x16C, size 0x4
    float mPhraseScore; // offset 0x170, size 0x4
    float mPhraseBonusScore; // offset 0x174, size 0x4
    float mLastMs; // offset 0x178, size 0x4
    int mLastBeginNote; // offset 0x17C, size 0x4
    const class VocalPhrase * mThisPhrase; // offset 0x180, size 0x4
    unsigned char mIgnorePhrase; // offset 0x184, size 0x1
    float mSmoothPhraseScore; // offset 0x188, size 0x4
    unsigned char mSmoothUpdate; // offset 0x18C, size 0x1
    int mPhraseValue; // offset 0x190, size 0x4
    float mSlop; // offset 0x194, size 0x4
    float mPitchSigma; // offset 0x198, size 0x4
    float mPitchHitMultiplier; // offset 0x19C, size 0x4
    float mNonPitchHitMultiplier; // offset 0x1A0, size 0x4
    float mShortNoteThresh; // offset 0x1A4, size 0x4
    float mShortNoteMult; // offset 0x1A8, size 0x4
    float mNoteLengthFactor; // offset 0x1AC, size 0x4
    float mRatingThresholds[4]; // offset 0x1B0, size 0x10
    float mScreamStart; // offset 0x1C0, size 0x4
    float mScreamEnergyThreshold; // offset 0x1C4, size 0x4
    float mScreamTime; // offset 0x1C8, size 0x4
    float mCurBestHit; // offset 0x1CC, size 0x4
    int mCurNoteMatched; // offset 0x1D0, size 0x4
    int mSpotlightPhraseID; // offset 0x1D4, size 0x4
    float mMaxPhraseWeight; // offset 0x1D8, size 0x4
    float mPitchCorrect; // offset 0x1DC, size 0x4
    float mNonPitchEasyMultiplier; // offset 0x1E0, size 0x4
    float mPhraseScoreCapGrowth; // offset 0x1E4, size 0x4
    enum MatchType mFrameMatchType; // offset 0x1E8, size 0x4
    float mFrameJudgmentTime; // offset 0x1EC, size 0x4
    float mFrameMicPitch; // offset 0x1F0, size 0x4
    float mFrameMicEnergy; // offset 0x1F4, size 0x4
    float mFrameMicPhonemeAccuracy; // offset 0x1F8, size 0x4
    unsigned char mFrameRefVoiced; // offset 0x1FC, size 0x1
    float mFrameTargetPitch; // offset 0x200, size 0x4
    float mFrameBestHit; // offset 0x204, size 0x4
    class VocalScorer mVocalScorer; // offset 0x208, size 0xF8
    float mMinSongPitch; // offset 0x300, size 0x4
    float mMaxSongPitch; // offset 0x304, size 0x4
    float mMinPitch; // offset 0x308, size 0x4
    float mMaxPitch; // offset 0x30C, size 0x4
    unsigned char mInFreestyleSection; // offset 0x310, size 0x1
    unsigned char mInDeployedFreeStyleSection; // offset 0x311, size 0x1
    unsigned char mCouldChat; // offset 0x312, size 0x1
    float mLastOctaveCorrect; // offset 0x314, size 0x4
    float mCodaEndMs; // offset 0x318, size 0x4
    unsigned char mCodaResolved; // offset 0x31C, size 0x1
    class DelayLine mScoreDeltaHistory; // offset 0x320, size 0x194
    class VibratoDetector * mVibrato; // offset 0x4B4, size 0x4
    float mVibratoBonus; // offset 0x4B8, size 0x4
    unsigned char mMicFxOn; // offset 0x4BC, size 0x1
    unsigned char mReverbOn; // offset 0x4BD, size 0x1
    float mGhostScorePerPhrase; // offset 0x4C0, size 0x4
    float mFirstPhraseMsToScore; // offset 0x4C4, size 0x4
    class ObjDirPtr mMicFx; // offset 0x4C8, size 0xC
    float mLastTimeVocalEnergySent; // offset 0x4D4, size 0x4
    float mVocalEnergyPeriodMs; // offset 0x4D8, size 0x4
    class Sequence * mTambourineSequence; // offset 0x4DC, size 0x4
    class Fader * mTambourineFader; // offset 0x4E0, size 0x4
    class MidiParser * mTambourineParser; // offset 0x4E4, size 0x4
    class vector mTambourineEvents; // offset 0x4E8, size 0xC
    int mTambourineIdx; // offset 0x4F4, size 0x4
    unsigned char mTambourineSwinging; // offset 0x4F8, size 0x1
    unsigned char mTambourineSucceeding; // offset 0x4F9, size 0x1
    int mNumTambourinePassed; // offset 0x4FC, size 0x4
    float mTambourineEnergyDropThreshold; // offset 0x500, size 0x4
    float mTambourineEnergyRiseThreshold; // offset 0x504, size 0x4
    float mTambourineApex; // offset 0x508, size 0x4
    float mTambourineNadir; // offset 0x50C, size 0x4
    int mTambourineWindowTicks; // offset 0x510, size 0x4
    int mTambourineMsOffset; // offset 0x514, size 0x4
    int mTambourineMsOffsetUSB; // offset 0x518, size 0x4
    unsigned char mTambourineWiiSwinging; // offset 0x51C, size 0x1
    int mTambourineAccelerationMinimum; // offset 0x520, size 0x4
    int mTambourineAccelerationRiseThreshold; // offset 0x524, size 0x4
    int mTambourineAccelerationDropThreshold; // offset 0x528, size 0x4
    int mTambourineAccelerationApex; // offset 0x52C, size 0x4
    int mTambourineAccelerationNadir; // offset 0x530, size 0x4
    float mTambourineCrowdSuccess; // offset 0x534, size 0x4
    float mTambourineCrowdFailure; // offset 0x538, size 0x4
    unsigned char mTambourineActive; // offset 0x53C, size 0x1
    int mNumTambGems; // offset 0x540, size 0x4
    float mTambourinePoints; // offset 0x544, size 0x4
    int mTambGemsHit; // offset 0x548, size 0x4
    class vector mTambourineGems; // offset 0x54C, size 0xC
    float mTempoVal; // offset 0x558, size 0x4
    float mRunningTime; // offset 0x55C, size 0x4
    unsigned char mIsJukeboxMode; // offset 0x560, size 0x1
};
// Range: 0x800313CC -> 0x800313D8
void VocalTrack::ClearPlayer() {}

static class Symbol scrolling_normal; // size: 0x4, address: 0x80A49144
static class Symbol scrolling_now; // size: 0x4, address: 0x80A4914C
static class Symbol scrolling_past; // size: 0x4, address: 0x80A49154
static class Symbol scrolling_style; // size: 0x4, address: 0x80A4915C
static class Symbol scrolling_style_now; // size: 0x4, address: 0x80A49164
static class Symbol scrolling_style_past; // size: 0x4, address: 0x80A4916C
static class Symbol phonome_tube_width; // size: 0x4, address: 0x80A49174
// Range: 0x800313D8 -> 0x80032740
void VocalTrack::UpdateScrolling(class VocalTrack * const this /* r23 */, float ms /* f22 */) {
    // Local variables
    const class VocalNoteList * noteList; // r24
    float updateEnd; // f22
    int endNote; // r25
    const class VocalNote & note; // r0
    class RndTransformable * scroller; // r29
    float absX; // f1
    float updateEnd; // f31
    float invalidateMs; // f23
    const class VocalNoteList * noteList; // r28
    int endNote; // r1+0x4C
    const class VocalNote & note; // r0
    class RndGroup * group; // r31
    class RndMesh * maskSrc; // r27
    int i; // r24
    int tick; // r25
    float beatMs; // r1+0x48
    class RndMesh * marker; // r1+0x44
    class Vector3 v; // r1+0x190
    const class vector & phrases; // r26
    int itP; // r25
    float phraseTime; // f30
    int last; // r24
    class RndMesh * marker; // r1+0x40
    float endMs; // r1+0x3C
    class Vector3 v; // r1+0x180
    float freestyleEnd; // f29
    float freestyleStart; // f28
    float duration; // f23
    class RndMesh * mask; // r1+0x38
    float originalWidth; // f27
    float newWidth; // f26
    int maskSegmentCount; // r24
    float maskTiles; // f25
    float maskCurrentX; // f24
    float maskCurrentU; // f23
    int vertIndex; // r22
    class VertVector & maskVerts; // r21
    class Vector3 v; // r1+0x170
    class VertVector & maskVerts; // r21
    class Vector3 v; // r1+0x160
    const class vector & events; // r21
    int endTick; // r22
    const int * itT; // r24
    float ms; // f22
    unsigned char splitParts; // r0
    const class vector & noteVec; // r24
    class RndGroup * wordGroup; // r25
    const class VocalNote * it; // r26
    int startLyricIdx; // [invalid]
    class String str; // r1+0x150
    class RndText * textObj; // r21
    class Lyric * newLyric; // r1+0x34
    const class VocalNote * j; // r1+0x30
    float lastEndX; // r1+0x2C
    class Color normalColor; // r1+0x140
    class Color currentColor; // r1+0x130
    class Color pastColor; // r1+0x120
    class Color normalColorStyle; // r1+0x110
    class Color currentColorStyle; // r1+0x100
    class Color pastColorStyle; // r1+0xF0
    float phonomeTubeWidth; // f0
    int i; // r27
    class Lyric & lyric; // r21
    unsigned char spotlight; // r22
    class Color normal; // r1+0xE0
    class Color current; // r1+0xD0
    class Color past; // r1+0xC0
    float startMs; // f0
    float tick; // f23
    class Vector3 v; // r1+0xB0
    class Color c; // r1+0xA0
    float shift; // f22
    class RndLine * noteTube; // r22
    class Vector3 p0; // r1+0x90
    class Vector3 p1; // r1+0x80
    float lyricWidth; // f0

    // References
    // -> static class Symbol phonome_tube_width;
    // -> static class Symbol scrolling_style_past;
    // -> static class Symbol scrolling_style_now;
    // -> static class Symbol scrolling_style;
    // -> static class Symbol scrolling_past;
    // -> static class Symbol scrolling_now;
    // -> static class Symbol scrolling_normal;
    // -> class GameMode * TheGameMode;
    // -> class DebugFailer TheDebugFailer;
    // -> const char * kAssertStr;
    // -> class BeatMap * TheBeatMap;
    // -> class SongDB * TheSongDB;
}

class VocalNote {
    // total size: 0x30
    int mPhrase; // offset 0x0, size 0x4
    int mBeginPitch; // offset 0x4, size 0x4
    int mEndPitch; // offset 0x8, size 0x4
    float mMs; // offset 0xC, size 0x4
    int mTick; // offset 0x10, size 0x4
    float mDurationMs; // offset 0x14, size 0x4
    unsigned short mDurationTicks; // offset 0x18, size 0x2
    class String mText; // offset 0x1C, size 0xC
    unsigned char mPhraseEnd; // offset 0x28, size 0x1
    unsigned char mUnpitchedPhrase; // offset 0x29, size 0x1
    unsigned char mUnpitchedNote; // offset 0x2A, size 0x1
    unsigned char mUnpitchedEasy; // offset 0x2B, size 0x1
    unsigned char mPitchRangeEnd; // offset 0x2C, size 0x1
    unsigned char mPlayerMask; // offset 0x2D, size 0x1
};
// Range: 0x80032740 -> 0x8003296C
class TambourineGem * TambourineGemPool::NewGem(class TambourineGemPool * const this /* r31 */, float time /* f31 */, int index /* r1+0x8 */) {
    // Local variables
    int i; // r30
    class TambourineGem * gem; // r1+0x14

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class VocalNote * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class VocalNote * _M_start; // offset 0x0, size 0x4
    class VocalNote * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class VocalPhrase {
    // total size: 0x30
public:
    float mStartMs; // offset 0x0, size 0x4
    float mDurationMs; // offset 0x4, size 0x4
    int mStartTick; // offset 0x8, size 0x4
    int mDurationTicks; // offset 0xC, size 0x4
    int mNoteStart; // offset 0x10, size 0x4
    int mNoteEnd; // offset 0x14, size 0x4
    unsigned char mPitchRangeEnd; // offset 0x18, size 0x1
    float mMinPitch; // offset 0x1C, size 0x4
    float mMaxPitch; // offset 0x20, size 0x4
    unsigned char mPlayerMask; // offset 0x24, size 0x1
    unsigned char mTambourinePhrase; // offset 0x25, size 0x1
    float mFreeStyleStartMs; // offset 0x28, size 0x4
    float mFreeStyleEndMs; // offset 0x2C, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class VocalPhrase * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class VocalPhrase * _M_start; // offset 0x0, size 0x4
    class VocalPhrase * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
enum TambourineGemState {
    kTambourineGemActive = 0,
    kTambourineGemHit = 1,
    kTambourineGemMissed = 2,
    kTambourineGemOff = 3,
    kTambourinePreview = 4,
};
// Range: 0x8003296C -> 0x80033744
void VocalTrack::UpdateTambourineGems(class VocalTrack * const this /* r22 */) {
    // Local variables
    class RndMultiMesh * gemsMM; // r0
    class RndMultiMesh * missedGemsMM; // r0
    class RndMultiMesh * previewGemsMM; // r0
    class RndTransformable * parent; // r24
    class deque & gemList; // r0
    class Transform t; // r1+0x100
    float duration_ms; // f30
    const class VocalPhrase * curPhrase; // r1+0x1C
    const class VocalPhrase * pm; // r0
    float next_phrase_duration; // f0
    unsigned int i; // r23
    enum TambourineGemState state; // r0
    float x_frac; // f2
    class Transform world; // r1+0xC0
    float transitionMs; // f30
    float previewFrame; // f31
    float nowMs; // f1

    // References
    // -> struct [anonymous] __RTTI__13RndAnimatable;
    // -> class TaskMgr TheTaskMgr;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<9Transform>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class SongDB * TheSongDB;
    // -> struct [anonymous] __RTTI__11RndPropAnim;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12RndMultiMesh;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std22_List_node<9Transform>; // size: 0x8, address: 0x80870A88
// Range: 0x80033744 -> 0x800338A8
float VocalTrack::PitchToZ(class VocalTrack * const this /* r30 */, float pitch /* f30 */, unsigned char clamped /* r31 */) {
    // Local variables
    float minPitch; // f31
    float maxPitch; // f2
    float extra; // f1
    float raw_z; // f2
}

// Range: 0x800338A8 -> 0x800339B8
unsigned char VocalTrack::InPhonemePhrase(float ms /* f31 */) {
    // Local variables
    const class VocalNote * nextNote; // r0
    int nextNoteIndex; // r0
    int lastNoteIndex; // r30

    // References
    // -> class SongDB * TheSongDB;
}

static class Symbol hit; // size: 0x4, address: 0x80A4917C
// Range: 0x800339B8 -> 0x80033CB0
void VocalTrack::HitTambourineGem(class VocalTrack * const this /* r30 */) {
    // References
    // -> static class Symbol hit;
}

static class Symbol miss; // size: 0x4, address: 0x80A49184
// Range: 0x80033CB0 -> 0x80033F60
void VocalTrack::MissTambourineGem(class VocalTrack * const this /* r30 */, int index /* r31 */) {
    // References
    // -> static class Symbol miss;
}

// Range: 0x80033F60 -> 0x80034030
class Color VocalTrack::GetColor() {}

// Range: 0x80034030 -> 0x800340F4
class Color VocalTrack::GetColor() {}

// Range: 0x800340F4 -> 0x8003420C
void VocalTrack::OnPhraseComplete(class VocalTrack * const this /* r29 */, int lastPhraseScore /* r28 */) {
    // Local variables
    const char * score; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndText;
}

// Range: 0x8003420C -> 0x800342CC
void VocalTrack::ClearLyrics(class VocalTrack * const this /* r29 */) {
    // Local variables
    class Lyric * l; // r30
}

// Range: 0x800342CC -> 0x80034D74
void VocalTrack::BuildPhrase(class VocalTrack * const this /* r20 */, float newPhraseEndMs /* f26 */, float nextPhraseEndMs /* f25 */) {
    // Local variables
    const class vector & noteList; // r0
    float phraseDurationMs; // f2
    int noteEnd; // r1+0x1C
    class RndGroup * wordGroup; // r26
    int lyricStartIndex; // [invalid]
    float phraseTick; // f28
    float nextPhraseTick; // f27
    float nextPhraseEndTick; // f0
    float phraseWidth; // f30
    float previewWidth; // f26
    unsigned char splitParts; // r0
    float previewLeft; // f25
    float previewRight; // f31
    int firstOutOfBoundsLyric; // r25
    int i; // r24
    class String str; // r1+0x8C
    class RndText * textObj; // r23
    class Lyric * newLyric; // r1+0x18
    int j; // r22
    float textWidth; // f0
    float lyricPos; // f25
    float previewPos; // f26
    float displayedDurationMs; // f0
    float introTick; // f1
    int i; // r21
    class Lyric & lyric; // r23
    float lyricWidth; // f0
    float phraseStartOffsetMs; // f0
    float pitch; // f0
    unsigned char spotlight; // r3
    float prevAlpha; // f1
    struct LyricSetupInfo setup; // r1+0x98

    // References
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> class GameMode * TheGameMode;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> class SongDB * TheSongDB;
}

static class Color previewColor; // size: 0x10, address: 0x80976C60
static class Color normalColor; // size: 0x10, address: 0x80976C70
static class Color currentColor; // size: 0x10, address: 0x80976C80
static class Color pastColor; // size: 0x10, address: 0x80976C90
// Range: 0x80034D74 -> 0x80035254
void VocalTrack::SetupKeyframes(const class VocalTrack * const this /* r26 */, class Lyric & lyric /* r27 */, const struct LyricSetupInfo & setup /* r28 */, int x_offset /* r29 */) {
    // Local variables
    float lineHeight; // f31
    float tick; // f30
    class Vector3 v; // r1+0x110

    // References
    // -> static class Color pastColor;
    // -> static class Color currentColor;
    // -> static class Color normalColor;
    // -> static class Color previewColor;
}

// Range: 0x80035254 -> 0x800358DC
void VocalTrack::BuildMasks(class VocalTrack * const this /* r31 */) {
    // Local variables
    float start; // f31
    float width; // f30
    float curPhraseDurMs; // f3
    float duration; // f4
    float curPhraseDurMs; // f30
    float maskStartMs; // f2
    float maskEndMs; // f0
    float originalWidth; // f29
    class Vector3 v; // r1+0x30

    // References
    // -> const char * kAssertStr;
    // -> class Symbol name;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> class Game * TheGame;
    // -> class SongDB * TheSongDB;
}

// Range: 0x800358DC -> 0x80035E98
void VocalTrack::BuildBeatMarkers(class VocalTrack * const this /* r26 */) {
    // Local variables
    class RndGroup * group; // r30
    float phraseStartTick; // f28
    float phraseEndTick; // f29
    int startBeat; // [invalid]
    int endBeat; // r29
    unsigned char downbeatsOnly; // r28
    float phraseDurationMs; // f30
    int i; // [invalid]
    class RndMesh * marker; // r25
    float beatMs; // f0
    class Vector3 v; // r1+0x40
    const class VocalPhrase * nextPhrase; // r0
    float startMs; // f0
    float endMs; // f0
    int i; // r27
    class RndMesh * marker; // r24
    float beatMs; // f0
    class Vector3 v; // r1+0x30

    // References
    // -> class SongDB * TheSongDB;
    // -> class BeatMap * TheBeatMap;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

// Range: 0x80035E98 -> 0x80036044
void VocalTrack::PreparePhonemeLine(class VocalTrack * const this /* r31 */) {
    // Local variables
    class RndLine * line; // r28
    int i; // r29
    class Vector3 point; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndLine;
}

// Range: 0x80036044 -> 0x8003636C
void VocalTrack::UpdatePhonemeLine(class VocalTrack * const this /* r30 */, float ms /* f29 */, float phraseStart /* f30 */, float phraseWindow /* f31 */) {
    // Local variables
    float accuracy; // r1+0x18
    class Color goodColor; // r1+0x50
    class Color badColor; // r1+0x40
    class RndLine * line; // r31
    int endIndex; // r1+0x14
    int startIndex; // [invalid]
    int i; // r28
    class Vector3 point; // r1+0x30
    class Color c; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndLine;
}

// Range: 0x8003636C -> 0x80036BE4
void VocalTrack::PrepareTambourine(class VocalTrack * const this /* r26 */) {
    // Local variables
    float duration_ms; // f0
    const class vector & events; // r0
    int start_tick; // r1+0x44
    int end_tick; // r28
    const int * it; // r27
    float ms; // f0
    const class VocalPhrase * nextPhrase; // r0
    float ms; // f0

    // References
    // -> class SongDB * TheSongDB;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct __less_2 {
    // total size: 0x1
};
// Range: 0x80036BE4 -> 0x800373B8
void VocalTrack::PrepareNoteTubes(class VocalTrack * const this /* r19 */, float startMs /* f25 */, float windowDurationMs /* f26 */, int startNote /* r20 */, int & endNote /* r21 */) {
    // Local variables
    unsigned char separateParts; // r0
    const class VocalNoteList * noteList; // r0
    class RndTransformable * scroller; // r26
    class RndGroup * group; // r25
    float phonomeTubeWidth; // f30
    float offset; // f0
    int i; // [invalid]
    const class VocalNote & note; // r0
    unsigned char spotlight; // r22
    class Symbol srcName; // r1+0x44
    const class VocalNote * last; // r3
    float last_x; // f29
    int j; // r24
    float x; // f0
    class RndLine * tube; // r23
    float tubeWidth; // f28
    float ms; // f27
    int k; // r22
    float z; // f0
    float x; // r1+0x40
    float z; // f0
    float x; // f2
    class Vector3 v; // r1+0x70

    // References
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> class SongDB * TheSongDB;
    // -> class GameMode * TheGameMode;
}

// Range: 0x800373B8 -> 0x800374B8
void VocalTrack::ToggleScoreDebug(class VocalTrack * const this /* r28 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

// Range: 0x800374B8 -> 0x800375A4
void VocalTrack::UpdatePressToTalk(class VocalTrack * const this /* r30 */, unsigned char newState /* r31 */) {
    // Local variables
    class EventTrigger * trig; // r5

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x800375A4 -> 0x800375B8
void VocalTrack::SetScreamThresholds() {}

// Range: 0x800375B8 -> 0x800375F8
unsigned char VocalTrack::InTambourinePhrase() {
    // Local variables
    class Player * p; // r0
}

class DebugWarner {
    // total size: 0x100
    char mStr[256]; // offset 0x0, size 0x100
};
static class DebugWarner _dw; // size: 0x100, address: 0x80976CA0
// Range: 0x800375F8 -> 0x80037798
int VocalTrack::IncrementVolume(class VocalTrack * const this /* r31 */, int val /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static class DebugWarner _dw;
    // -> class ProfileMgr TheProfileMgr;
}

// Range: 0x80037798 -> 0x800377D4
void VocalTrack::PushGameplayOptions(class VocalTrack * const this /* r30 */, enum VocalParam param /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A49190
static class Symbol _s; // size: 0x4, address: 0x80A49198
static class Symbol _s; // size: 0x4, address: 0x80A491A0
// Range: 0x800377D4 -> 0x80037D34
class DataNode VocalTrack::Handle(class VocalTrack * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x80037D34 -> 0x800385E0
unsigned char Lyric::Poll(class Lyric * const this /* r31 */) {
    // Local variables
    float tick; // f0
    class Color c; // r1+0x20
    class Vector3 pos; // r1+0x10
}

// Range: 0x800385E0 -> 0x800386F8
void * Lyric::Lyric(class Lyric * const this /* r30 */, class RndText * textObj /* r31 */, const class VocalNote * note /* r1+0x8 */) {
    // References
    // -> struct [anonymous] __vt__27ObjPtr<7RndLine,9ObjectDir>;
    // -> struct [anonymous] __vt__27ObjPtr<7RndText,9ObjectDir>;
    // -> struct [anonymous] __vt__5Lyric;
}

// Range: 0x800386F8 -> 0x80038950
void * Lyric::~Lyric(class Lyric * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__27ObjPtr<7RndText,9ObjectDir>;
    // -> struct [anonymous] __vt__27ObjPtr<7RndLine,9ObjectDir>;
}

// Range: 0x80038950 -> 0x80038960
int Lyric::StartTick() {}

// Range: 0x80038960 -> 0x80038978
int Lyric::EndTick() {}

// Range: 0x80038978 -> 0x80038988
int Lyric::Pitch() {}

// Range: 0x80038988 -> 0x800389A0
float Lyric::Width() {}

// Range: 0x800389A0 -> 0x800389D4
float Lyric::EndPos() {}

// Range: 0x800389D4 -> 0x800389EC
unsigned char Lyric::PitchNote() {}

struct {
    // total size: 0x8
} __RTTI__12RndMultiMesh; // size: 0x8, address: 0x80870EE8
struct {
    // total size: 0x120
} __vt__10VocalTrack; // size: 0x120, address: 0x80870EF0
struct {
    // total size: 0x18
} __vt__34ObjPtr<13VocalTrackDir,9ObjectDir>; // size: 0x18, address: 0x80871048
struct {
    // total size: 0x8
} __RTTI__34ObjPtr<13VocalTrackDir,9ObjectDir>; // size: 0x8, address: 0x80871090
struct {
    // total size: 0x54
} __vt__5Lyric; // size: 0x54, address: 0x80871098
struct {
    // total size: 0x8
} __RTTI__5Lyric; // size: 0x8, address: 0x80871108
struct {
    // total size: 0x8
} __RTTI__13VocalTrackDir; // size: 0x8, address: 0x80871180
struct {
    // total size: 0x18
} __vt__27ObjPtr<7RndLine,9ObjectDir>; // size: 0x18, address: 0x80871188
struct {
    // total size: 0x8
} __RTTI__27ObjPtr<7RndLine,9ObjectDir>; // size: 0x8, address: 0x808711C8
struct {
    // total size: 0x8
} __RTTI__11RndPropAnim; // size: 0x8, address: 0x80871258
struct {
    // total size: 0x18
} __vt__27ObjPtr<7RndText,9ObjectDir>; // size: 0x18, address: 0x80871260
struct {
    // total size: 0x8
} __RTTI__27ObjPtr<7RndText,9ObjectDir>; // size: 0x8, address: 0x808712A0
struct {
    // total size: 0x8
} __RTTI__12EventTrigger; // size: 0x8, address: 0x808712D0
struct {
    // total size: 0x8
} __RTTI__7RndText; // size: 0x8, address: 0x80871450
class TambourineGem {
    // total size: 0xC
    float mTime; // offset 0x0, size 0x4
    int mIndex; // offset 0x4, size 0x4
    enum TambourineGemState mState; // offset 0x8, size 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct {
    // total size: 0x8
} __RTTI__PPP13TambourineGem; // size: 0x8, address: 0x80871600
struct {
    // total size: 0x8
} __RTTI__PP13TambourineGem; // size: 0x8, address: 0x80871620
struct {
    // total size: 0x8
} __RTTI__PPQ211stlpmtx_std17pair<P7RndMesh,f>; // size: 0x8, address: 0x80871650
struct {
    // total size: 0x8
} __RTTI__PPQ211stlpmtx_std17pair<P7RndLine,f>; // size: 0x8, address: 0x80871698
struct {
    // total size: 0x8
} __RTTI__PPP5Lyric; // size: 0x8, address: 0x808716B0
struct {
    // total size: 0x8
} __RTTI__PP5Lyric; // size: 0x8, address: 0x808716C8
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std17pair<P7RndLine,f>; // size: 0x8, address: 0x808716F8
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std17pair<P7RndMesh,f>; // size: 0x8, address: 0x80871728
struct {
    // total size: 0x8
} __RTTI__PPC9VocalNote; // size: 0x8, address: 0x80871748
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
class _List_global {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__P13Key<7Vector3>; // size: 0x8, address: 0x80871780
struct {
    // total size: 0x8
} __RTTI__P6Key<f>; // size: 0x8, address: 0x80871798
struct {
    // total size: 0x8
} __RTTI__P17Key<Q23Hmx5Color>; // size: 0x8, address: 0x808717B8
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std116_Rb_tree_node<Q211stlpmtx_std84pair<Ci,Q211stlpmtx_std58vector<P7RndLine,Q211stlpmtx_std23StlNodeAlloc<P7RndLine>>>>; // size: 0x8, address: 0x80871848
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std120_Rb_tree_node<Q211stlpmtx_std88pair<C6Symbol,Q211stlpmtx_std56list<P7RndText,Q211stlpmtx_std23StlNodeAlloc<P7RndText>>>>; // size: 0x8, address: 0x808718D8
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Profile * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Profile * _M_start; // offset 0x0, size 0x4
    class Profile * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class SigninChangedMsg : public Message {
    // total size: 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Profile * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Profile * * _M_start; // offset 0x0, size 0x4
    class Profile * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ProfileMgr : public MsgSource {
    // total size: 0x278
public:
    float kPlatformAudioLatency; // offset 0x1C, size 0x4
    float kPlatformVideoLatency; // offset 0x20, size 0x4
    float kInGameExtraVideoLatency; // offset 0x24, size 0x4
    float kInGameSyncOffsetAdjustment; // offset 0x28, size 0x4
private:
    unsigned char mHasInactiveProfile; // offset 0x2C, size 0x1
    class GameplayOptions mGuitarOptions[2]; // offset 0x30, size 0x90
    class GameplayOptions mDrumsOptions[2]; // offset 0xC0, size 0x90
    class GameplayOptions mVocalsOptions[2]; // offset 0x150, size 0x90
    enum ProfileSaveState mGlobalOptionsSaveState; // offset 0x1E0, size 0x4
    unsigned char mGlobalOptionsDirty; // offset 0x1E4, size 0x1
    unsigned char mHasPlayedBefore; // offset 0x1E5, size 0x1
    unsigned char mHasPlayedGuitarBefore; // offset 0x1E6, size 0x1
    unsigned char mHasPlayedDrumBefore; // offset 0x1E7, size 0x1
    unsigned char mHasPlayedVocalsBefore; // offset 0x1E8, size 0x1
    int mBackgroundVolume; // offset 0x1EC, size 0x4
    int mForegroundVolume; // offset 0x1F0, size 0x4
    int mFxVolume; // offset 0x1F4, size 0x4
    int mCrowdVolume; // offset 0x1F8, size 0x4
    int mVocalCueVolume; // offset 0x1FC, size 0x4
    unsigned char mMono; // offset 0x200, size 0x1
    float mSyncOffset; // offset 0x204, size 0x4
    float mSongToTaskMgrMs; // offset 0x208, size 0x4
    unsigned char mBassBoost; // offset 0x20C, size 0x1
    unsigned char mDolby; // offset 0x20D, size 0x1
    unsigned char mMuteFx; // offset 0x20E, size 0x1
    int mSyncPresetIx; // offset 0x210, size 0x4
    unsigned char mOverscan; // offset 0x214, size 0x1
    class String mUsername; // offset 0x218, size 0xC
    class DataArray * mSliderConfig; // offset 0x224, size 0x4
    class DataArray * mSliderRatioConfig; // offset 0x228, size 0x4
    class vector mProfiles; // offset 0x22C, size 0xC
    unsigned char mAllUnlocked; // offset 0x238, size 0x1
    int mMaxChars; // offset 0x23C, size 0x4
    int mMaxBands; // offset 0x240, size 0x4
    int mMaxRemoteBands; // offset 0x244, size 0x4
    unsigned char mAllowSigninActivation; // offset 0x248, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    char * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    char * _M_start; // offset 0x0, size 0x4
    char * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class MemStream : public BinStream {
    // total size: 0x20
    unsigned char mFail; // offset 0xC, size 0x1
    int mTell; // offset 0x10, size 0x4
    class vector mBuffer; // offset 0x14, size 0xC
};

