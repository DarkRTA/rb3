/*
    Compile unit: C:\rockband2\band2\src\bandtrack\Track.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800250EC -> 0x80026224
*/
// Range: 0x800250EC -> 0x80025158
void * Track::Track(class Track * const this /* r29 */, int player /* r30 */, class Symbol & type /* r31 */) {
    // References
    // -> struct [anonymous] __vt__5Track;
}

// Range: 0x80025158 -> 0x80025160
int Track::GetPlayerNum() {}

// Range: 0x80025160 -> 0x80025198
int Track::GetPlayerDifficulty() {
    // Local variables
    class Player * p; // r0
}

// Range: 0x80025198 -> 0x800251EC
class Object * Track::GetObj(class Symbol & name /* r31 */) {
    // Local variables
    class RndDir * dir; // r0
}

// Range: 0x800251EC -> 0x800251F4
class Symbol Track::GetType() {}

// Range: 0x800251F4 -> 0x80025224
class Player * Track::GetPlayer() {
    // References
    // -> class GameConfig * TheGameConfig;
}

// Range: 0x80025224 -> 0x80025298
unsigned char Track::ShouldDisablePopupHelp() {
    // Local variables
    class Player * p; // r30
}

// Range: 0x80025298 -> 0x800252AC
unsigned char Track::InGame() {
    // References
    // -> class Game * TheGame;
}

// Range: 0x800252AC -> 0x800252D8
unsigned char Track::HasPlayer() {}

// Range: 0x800252D8 -> 0x80025348
char * Track::GetTrackIcon() {
    // Local variables
    class Player * player; // r0
}

// Range: 0x80025348 -> 0x80025380
char * Track::GetPlayerName() {
    // Local variables
    class Player * player; // r0
}

// Range: 0x80025380 -> 0x800253B8
char * Track::GetUserName() {
    // Local variables
    class Player * player; // r0
}

// Range: 0x800253B8 -> 0x800253FC
unsigned char Track::PlayerDisconnected() {
    // Local variables
    class Player * p; // r0
}

// Range: 0x800253FC -> 0x80025430
unsigned char Track::PlayerDisconnectedAtStart() {
    // Local variables
    class Player * p; // r0
}

// Range: 0x80025430 -> 0x80025478
unsigned char Track::HasLocalPlayer() {
    // Local variables
    class Player * p; // r0
}

// Range: 0x80025478 -> 0x800254B8
unsigned char Track::PlayerDisabled() {
    // Local variables
    class Player * p; // r0
}

static class Symbol deploy_to_save; // size: 0x4, address: 0x80A4903C
// Range: 0x800254B8 -> 0x80025648
void Track::DTSPopup(unsigned char show /* r31 */) {
    // Local variables
    const class vector & players; // r0
    class Player * const * it; // r28
    class Player * const * end; // r27
    class Player * player; // r26
    unsigned char showForPlayer; // r25

    // References
    // -> static class Symbol deploy_to_save;
    // -> class Game * TheGame;
}

class CrowdRating {
    // total size: 0x48
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    const class DataArray * mConfig; // offset 0x4, size 0x4
    unsigned char mActive; // offset 0x8, size 0x1
    float mRawValue; // offset 0xC, size 0x4
    float mValue; // offset 0x10, size 0x4
    float mRunningMin; // offset 0x14, size 0x4
    float mSongFraction; // offset 0x18, size 0x4
    float mLoseLevel; // offset 0x1C, size 0x4
    float kMin; // offset 0x20, size 0x4
    float kMax; // offset 0x24, size 0x4
    float kNoteWeight; // offset 0x28, size 0x4
    float kPhraseWeight; // offset 0x2C, size 0x4
    float kInitialDisplayLevel; // offset 0x30, size 0x4
    float kGreatLevel; // offset 0x34, size 0x4
    float kOkayLevel; // offset 0x38, size 0x4
    float kBadLevel; // offset 0x3C, size 0x4
    float kWarningLevel; // offset 0x40, size 0x4
    float kFreeRide; // offset 0x44, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndLine * mPtr; // offset 0x8, size 0x4
};
struct Node {
    // total size: 0xC
    class RndTransformable * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
class iterator {
    // total size: 0x4
    struct Node * mNode; // offset 0x0, size 0x4
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
class VocalTrackDir : public RndDir, public BandTrack {
    // total size: 0x5C0
    unsigned char mTestArrowVisible; // offset 0x2DC, size 0x1
    unsigned char mTestPitched; // offset 0x2DD, size 0x1
    unsigned char mStaticVocals; // offset 0x2DE, size 0x1
    unsigned char mEnableVocalsOptions; // offset 0x2DF, size 0x1
    unsigned char mTop; // offset 0x2E0, size 0x1
    int mFeedbackState; // offset 0x2E4, size 0x4
    class vector mFeedbackColors; // offset 0x2E8, size 0xC
    int mPhraseChangeDurationTicks; // offset 0x2F4, size 0x4
    int mTimeBeforePhraseToSpaceTicks; // offset 0x2F8, size 0x4
    float mNextPhraseAnimationRatio; // offset 0x2FC, size 0x4
    int mNextPhraseFadeInBefore; // offset 0x300, size 0x4
    float mPhraseMeterVal; // offset 0x304, size 0x4
    float mTestPhraseMeter; // offset 0x308, size 0x4
    class Color mScrollingNormal; // offset 0x310, size 0x10
    class Color mScrollingNow; // offset 0x320, size 0x10
    class Color mScrollingPast; // offset 0x330, size 0x10
    class Color mScrollingStyle; // offset 0x340, size 0x10
    class Color mScrollingStyleNow; // offset 0x350, size 0x10
    class Color mScrollingStylePast; // offset 0x360, size 0x10
    class Color mStaticPreview; // offset 0x370, size 0x10
    class Color mStaticNormal; // offset 0x380, size 0x10
    class Color mStaticNow; // offset 0x390, size 0x10
    class Color mStaticPast; // offset 0x3A0, size 0x10
    class Color mStaticPreviewStyle; // offset 0x3B0, size 0x10
    class Color mStaticNormalStyle; // offset 0x3C0, size 0x10
    class Color mStaticNowStyle; // offset 0x3D0, size 0x10
    class Color mStaticPastStyle; // offset 0x3E0, size 0x10
    class ObjPtr mScrollingPitchedTube; // offset 0x3F0, size 0xC
    class ObjPtr mScrollingUnpitchedTube; // offset 0x3FC, size 0xC
    class ObjPtr mScrollingPitchedStyleTube; // offset 0x408, size 0xC
    class ObjPtr mScrollingUnpitchedStyleTube; // offset 0x414, size 0xC
    class ObjPtr mStaticPitchedTube; // offset 0x420, size 0xC
    class ObjPtr mStaticUnpitchedTube; // offset 0x42C, size 0xC
    class ObjPtr mStaticPitchedStyleTube; // offset 0x438, size 0xC
    class ObjPtr mStaticUnpitchedStyleTube; // offset 0x444, size 0xC
    class Color mBackground; // offset 0x450, size 0x10
    class Color mBackgroundSpotlight; // offset 0x460, size 0x10
    float mPreviewZ; // offset 0x470, size 0x4
    float mCurrentZ; // offset 0x474, size 0x4
    class vector mTubeWidths; // offset 0x478, size 0xC
    float mPhonemeTubeWidth; // offset 0x484, size 0x4
    class ObjPtr mVocalistVolume; // offset 0x488, size 0xC
    unsigned char mLastFrameScoring; // offset 0x494, size 0x1
    float mMinPitchRange; // offset 0x498, size 0x4
    float mArrowSmoothing; // offset 0x49C, size 0x4
    float mDeployMaskScrollRate; // offset 0x4A0, size 0x4
    class ObjPtrList mConfigurableObjects; // offset 0x4A4, size 0x14
    float mSideFadeLength; // offset 0x4B8, size 0x4
    unsigned char mArrowVisible; // offset 0x4BC, size 0x1
    unsigned char mPitchMatching; // offset 0x4BD, size 0x1
    class ObjPtr mVoxConfig; // offset 0x4C0, size 0xC
    class ObjPtr mTambourineSmasher; // offset 0x4CC, size 0xC
    class ObjPtr mTambourineNowShowTrig; // offset 0x4D8, size 0xC
    class ObjPtr mTambourineNowHideTrig; // offset 0x4E4, size 0xC
    class ObjPtr mPitchArrowGrp; // offset 0x4F0, size 0xC
    class ObjPtr mArrowVisibleAnim; // offset 0x4FC, size 0xC
    class ObjPtr mPitchArrowSplitCloseTrig; // offset 0x508, size 0xC
    class ObjPtr mPitchArrowSplitOpenTrig; // offset 0x514, size 0xC
    class ObjPtr mPhraseFeedbackTxt; // offset 0x520, size 0xC
    class ObjPtr mPhraseFeedbackTrig; // offset 0x52C, size 0xC
    class ObjPtr mSpotlightSparklesOnlyTrig; // offset 0x538, size 0xC
    class ObjPtr mSpotlightPhraseSuccessTrig; // offset 0x544, size 0xC
    class ObjPtr mNewPhraseTrig; // offset 0x550, size 0xC
    class ObjPtr mFlareTrig; // offset 0x55C, size 0xC
    class ObjPtr mScoringTrig; // offset 0x568, size 0xC
    class ObjPtr mScoringStopTrig; // offset 0x574, size 0xC
};
// Range: 0x80025648 -> 0x800256BC
unsigned char Track::HasNetPlayer() {
    // Local variables
    class Player * p; // r30
}

// Range: 0x800256BC -> 0x800256E4
int Track::GetBandMultiplier() {}

// Range: 0x800256E4 -> 0x80025730
void Track::PushGameplayOptions(class Track * const this /* r31 */) {
    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80025730 -> 0x80025788
void Track::SetNoOverdrive(class Track * const this /* r31 */) {}

// Range: 0x80025788 -> 0x800257B8
unsigned char Track::GetNoBackFromBrink() {}

// Range: 0x800257B8 -> 0x800258C0
void Track::RefreshPlayerHUD(class Track * const this /* r28 */) {
    // Local variables
    class BandTrack * trackDir; // r29
    class Player * player; // r28
}

// Range: 0x800258C0 -> 0x80025908
unsigned char Track::FailedAtStart(class Track * const this /* r31 */) {}

// Range: 0x80025908 -> 0x80025950
unsigned char Track::IsDeployingOverdrive(const class Track * const this /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A49044
static class Symbol _s; // size: 0x4, address: 0x80A4904C
static class Symbol _s; // size: 0x4, address: 0x80A49054
static class Symbol _s; // size: 0x4, address: 0x80A4905C
static class Symbol _s; // size: 0x4, address: 0x80A49064
// Range: 0x80025950 -> 0x80026224
class DataNode Track::Handle(class Track * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x40
    class MessageTimer _mt; // r1+0x58
    class DataNode _n; // r1+0x50
    class DataNode _n; // r1+0x48

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x11C
} __vt__5Track; // size: 0x11C, address: 0x8086F604
struct {
    // total size: 0xDC
} __vt__14TrackInterface; // size: 0xDC, address: 0x8086F750

