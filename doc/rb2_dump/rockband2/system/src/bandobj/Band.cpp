/*
    Compile unit: C:\rockband2\system\src\bandobj\Band.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80235954 -> 0x80235994
*/
class Symbol name; // size: 0x4, address: 0x80A4EB6C
class Symbol name; // size: 0x4, address: 0x80A4EB74
class Symbol name; // size: 0x4, address: 0x80A4EB7C
class Symbol name; // size: 0x4, address: 0x80A4EB84
class Symbol name; // size: 0x4, address: 0x80A4EB8C
class Symbol name; // size: 0x4, address: 0x80A4EB94
class Symbol name; // size: 0x4, address: 0x80A4EB9C
class Symbol name; // size: 0x4, address: 0x80A4EBA4
class Symbol name; // size: 0x4, address: 0x80A4EBAC
class Symbol name; // size: 0x4, address: 0x80A4EBB4
class Symbol name; // size: 0x4, address: 0x80A4EBBC
class Symbol name; // size: 0x4, address: 0x80A4EBC4
class Symbol name; // size: 0x4, address: 0x80A4EBCC
class Symbol name; // size: 0x4, address: 0x80A4EBD4
class Symbol name; // size: 0x4, address: 0x80A4EBDC
class Symbol name; // size: 0x4, address: 0x80A4EBE4
class Symbol name; // size: 0x4, address: 0x80A4EBEC
class Symbol name; // size: 0x4, address: 0x80A4EBF4
class Symbol name; // size: 0x4, address: 0x80A4EBFC
enum Color {
    kNone = -1,
    kNeutral = 0,
    kPlayer0 = 1,
    kPlayer1 = 2,
};
class BandLeadMeter : public RndDir {
    // total size: 0x2B0
    class ObjPtr mNeedle; // offset 0x1F4, size 0xC
    class ObjPtr mLogoGlow; // offset 0x200, size 0xC
    class ObjPtr mGlow0; // offset 0x20C, size 0xC
    class ObjPtr mGlow1; // offset 0x218, size 0xC
    class ObjPtr mPegged0; // offset 0x224, size 0xC
    class ObjPtr mPegged1; // offset 0x230, size 0xC
    class ObjPtr mLens; // offset 0x23C, size 0xC
    class ObjPtr mLensMatNeutral; // offset 0x248, size 0xC
    class ObjPtr mLensMat0; // offset 0x254, size 0xC
    class ObjPtr mLensMat1; // offset 0x260, size 0xC
    int mMaxLead; // offset 0x26C, size 0x4
    int mScoreDiff; // offset 0x270, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndMultiMesh * mPtr; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct MeshInstance {
    // total size: 0x1C
    class ObjPtr path; // offset 0x0, size 0xC
    class ObjPtr parentTrans; // offset 0xC, size 0xC
    float frame; // offset 0x18, size 0x4
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndParticleSys * mPtr; // offset 0x8, size 0x4
};
class BandMeshLauncher : public RndPollable {
    // total size: 0xF0
protected:
    class ObjPtr mMultiMesh; // offset 0x8, size 0xC
    class list mInstances; // offset 0x14, size 0x8
    class ObjPtr mPart; // offset 0x1C, size 0xC
    class ObjPtr mTrans; // offset 0x28, size 0xC
    int mNumParts; // offset 0x34, size 0x4
    unsigned char mUseLife; // offset 0x38, size 0x1
    float mLife; // offset 0x3C, size 0x4
    unsigned char mUseSpeed; // offset 0x40, size 0x1
    float mSpeed; // offset 0x44, size 0x4
    unsigned char mUseSize; // offset 0x48, size 0x1
    float mSize; // offset 0x4C, size 0x4
    unsigned char mUseDeltaSize; // offset 0x50, size 0x1
    float mDeltaSize; // offset 0x54, size 0x4
    unsigned char mUseStartColor; // offset 0x58, size 0x1
    class Color mStartColor; // offset 0x60, size 0x10
    unsigned char mUseMidColor; // offset 0x70, size 0x1
    class Color mMidColor; // offset 0x80, size 0x10
    unsigned char mUseEndColor; // offset 0x90, size 0x1
    class Color mEndColor; // offset 0xA0, size 0x10
    unsigned char mUseEmitDirection; // offset 0xB0, size 0x1
    class Vector2 mPitch; // offset 0xB4, size 0x8
    class Vector2 mYaw; // offset 0xBC, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ObjPtr * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ObjPtr * _M_start; // offset 0x0, size 0x4
    class ObjPtr * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ObjPtr * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ObjPtr * _M_start; // offset 0x0, size 0x4
    class ObjPtr * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
enum PlayerSetting {
    kPlayerShared = -2,
    kPlayerNone = -1,
    kPlayer1 = 0,
    kPlayer2 = 1,
};
class BandScoreDisplay : public RndDir {
    // total size: 0x260
    int mScore; // offset 0x1F4, size 0x4
    class ObjVector mDigitMeshs; // offset 0x1F8, size 0x10
    class ObjVector mDigitMats; // offset 0x208, size 0x10
    class ObjPtr mBlankMat; // offset 0x218, size 0xC
    enum PlayerSetting mPlayer; // offset 0x224, size 0x4
};
class BandStarMeter : public RndDir {
    // total size: 0x290
    float mValue; // offset 0x1F4, size 0x4
    float mDisplayValue; // offset 0x1F8, size 0x4
    unsigned char mUsing; // offset 0x1FC, size 0x1
    class ObjPtr mGroup; // offset 0x200, size 0xC
    class ObjPtr mFillGroup; // offset 0x20C, size 0xC
    class ObjPtr mReadyGroup; // offset 0x218, size 0xC
    class ObjPtr mAnimGroup; // offset 0x224, size 0xC
    class ObjPtr mEngageAnim0; // offset 0x230, size 0xC
    class ObjPtr mEngageAnim1; // offset 0x23C, size 0xC
    unsigned char mEngage0; // offset 0x248, size 0x1
    unsigned char mEngage1; // offset 0x249, size 0x1
    float mReadyLevel; // offset 0x24C, size 0x4
    enum PlayerSetting mPlayer; // offset 0x250, size 0x4
};
enum StreakColor {
    kColorNone = 0,
    kColor2x = 1,
    kColor3x = 2,
    kColor4x = 3,
    kColorStar = 4,
    kNumStreakColors = 5,
};
class BandStreakDisplay : public RndDir {
    // total size: 0x320
    class ObjVector mLedMats; // offset 0x1F4, size 0x10
    int mStreak; // offset 0x204, size 0x4
    int mMultiplier; // offset 0x208, size 0x4
    unsigned char mStarMode; // offset 0x20C, size 0x1
    class ObjVector mStreakLeds; // offset 0x210, size 0x10
    class ObjPtr mScoreFrame; // offset 0x220, size 0xC
    class ObjPtr mMultFrame; // offset 0x22C, size 0xC
    class ObjPtr mMultGlow; // offset 0x238, size 0xC
    class ObjPtr mColors; // offset 0x244, size 0xC
    class ObjPtr mShakeAnim; // offset 0x250, size 0xC
    class ObjVector mDigitMats; // offset 0x25C, size 0x10
    class ObjPtr mMultMesh; // offset 0x26C, size 0xC
    class ObjPtr mXMesh; // offset 0x278, size 0xC
    class ObjPtr mMatBlank; // offset 0x284, size 0xC
    class ObjPtr mMatX; // offset 0x290, size 0xC
    enum PlayerSetting mPlayer; // offset 0x29C, size 0x4
    float mHideTime[2]; // offset 0x2A0, size 0x8
    class ObjPtr mBlown0; // offset 0x2A8, size 0xC
    class ObjPtr mBlown1; // offset 0x2B4, size 0xC
    class ObjPtr mBlownMat; // offset 0x2C0, size 0xC
    float mBlownDisplayTime; // offset 0x2CC, size 0x4
    class ObjPtr mTextX; // offset 0x2D0, size 0xC
    class ObjPtr mTextMult; // offset 0x2DC, size 0xC
};
class H2HTrackPanelDir : public TrackPanelDirBase {
    // total size: 0x320
protected:
    int mTestScore; // offset 0x2B0, size 0x4
    class BandTrack * mTrack0; // offset 0x2B4, size 0x4
    class BandTrack * mTrack1; // offset 0x2B8, size 0x4
    unsigned char mScoreDuel; // offset 0x2BC, size 0x1
    class Symbol mInstrument; // offset 0x2C0, size 0x4
    unsigned char mVocalGame; // offset 0x2C4, size 0x1
    class BandTrack * mFirstSoloTrack; // offset 0x2C8, size 0x4
    class Symbol mFirstSoloResult; // offset 0x2CC, size 0x4
    int mFirstSoloPoints; // offset 0x2D0, size 0x4
    class EndingBonus * mEndingBonus0; // offset 0x2D4, size 0x4
    class EndingBonus * mEndingBonus1; // offset 0x2D8, size 0x4
};
class Label3d : public RndTransformable, private RndDrawable {
    // total size: 0x180
    class String mText; // offset 0xF4, size 0xC
    class RndTransformable * mTrans; // offset 0x100, size 0x4
    class FilePath mResourceFile; // offset 0x104, size 0xC
    float mMaxWidth; // offset 0x110, size 0x4
    unsigned char mAllCaps; // offset 0x114, size 0x1
    class ObjDirPtr mResource; // offset 0x118, size 0xC
    float mJitterDepth; // offset 0x124, size 0x4
    float mJitterHeight; // offset 0x128, size 0x4
    class ObjPtrList mText3d; // offset 0x12C, size 0x14
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class CharClipSet * mPtr; // offset 0x8, size 0x4
};
class LoadingPanelDir : public WorldDir {
    // total size: 0x510
protected:
    class FilePath mClipPath; // offset 0x414, size 0xC
    class ObjPtr mClipSet; // offset 0x420, size 0xC
    class CompositeCharacter * mEditChar; // offset 0x42C, size 0x4
    class ObjPtr mVocalPose; // offset 0x430, size 0xC
    class ObjPtr mGuitarPose; // offset 0x43C, size 0xC
    class ObjPtr mBassPose; // offset 0x448, size 0xC
    class ObjPtr mDrumPose; // offset 0x454, size 0xC
    class ObjDirPtr mStoredVocalClips; // offset 0x460, size 0xC
    class ObjDirPtr mStoredGuitarClips; // offset 0x46C, size 0xC
    class ObjDirPtr mStoredBassClips; // offset 0x478, size 0xC
    class ObjDirPtr mStoredDrumClips; // offset 0x484, size 0xC
    class ObjPtr mH2hPose0; // offset 0x490, size 0xC
    class ObjPtr mH2hPose1; // offset 0x49C, size 0xC
    class ObjDirPtr mStoredH2h0Clips; // offset 0x4A8, size 0xC
    class ObjDirPtr mStoredH2h1Clips; // offset 0x4B4, size 0xC
    class String mH2hCharType; // offset 0x4C0, size 0xC
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class BandCrowdMeter * mPtr; // offset 0x8, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class EndingBonus * mPtr; // offset 0x8, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class Scoreboard * mPtr; // offset 0x8, size 0x4
};
class TrackPanelDir : public TrackPanelDirBase {
    // total size: 0x370
    int mMultiplier; // offset 0x2B0, size 0x4
    int mTestMultiplier; // offset 0x2B4, size 0x4
    int mBass; // offset 0x2B8, size 0x4
    int mDrum; // offset 0x2BC, size 0x4
    int mGuitar; // offset 0x2C0, size 0x4
    int mVocals; // offset 0x2C4, size 0x4
    class ObjPtr mVocalTrack; // offset 0x2C8, size 0xC
    class ObjPtr mGuitarTrack; // offset 0x2D4, size 0xC
    class ObjPtr mDrumTrack; // offset 0x2E0, size 0xC
    class ObjPtr mBassTrack; // offset 0x2EC, size 0xC
    class ObjPtr mCrowdMeter; // offset 0x2F8, size 0xC
    class ObjPtr mBandScoreMultiplier; // offset 0x304, size 0xC
    class ObjPtr mBandScoreMultiplierTrig; // offset 0x310, size 0xC
    class ObjPtr mEndingBonus; // offset 0x31C, size 0xC
    class ObjPtr mScoreboard; // offset 0x328, size 0xC
    unsigned char mShowScoreMultiplier; // offset 0x334, size 0x1
};
// Range: 0x80235954 -> 0x80235994
void BandTerminate() {}


