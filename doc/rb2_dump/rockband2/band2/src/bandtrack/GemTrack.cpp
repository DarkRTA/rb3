/*
    Compile unit: C:\rockband2\band2\src\bandtrack\GemTrack.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8001F9D0 -> 0x80022388
*/
class GemTrack : public Track {
    // total size: 0xB0
    unsigned char mResetFills; // offset 0x64, size 0x1
    class ObjPtr mTrackDir; // offset 0x68, size 0xC
    int mLastTick; // offset 0x74, size 0x4
    class GemManager * mGemManager; // offset 0x78, size 0x4
    struct PlayerState mPlayerState; // offset 0x7C, size 0x18
    struct PlayerState mLastPlayerState; // offset 0x94, size 0x18
    signed short mKickPassCounter; // offset 0xAC, size 0x2
};
// Range: 0x8001F9D0 -> 0x8001FA8C
void * GemTrack::GemTrack(class GemTrack * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__32ObjPtr<11GemTrackDir,9ObjectDir>;
    // -> struct [anonymous] __vt__8GemTrack;
}

class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class GemTrackDir * mPtr; // offset 0x8, size 0x4
};
// Range: 0x8001FB34 -> 0x8001FC30
void * GemTrack::~GemTrack(class GemTrack * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__32ObjPtr<11GemTrackDir,9ObjectDir>;
    // -> struct [anonymous] __vt__8GemTrack;
}

// Range: 0x8001FC30 -> 0x8001FC38
void GemTrack::ResetFills() {}

// Range: 0x8001FC38 -> 0x8001FCAC
void GemTrack::RebuildBeats(class GemTrack * const this /* r31 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x8001FCAC -> 0x8001FD80
void GemTrack::UpdateLeftyFlip(class GemTrack * const this /* r29 */) {
    // Local variables
    unsigned char lefty; // r31
    class BandUser * user; // r0
    class GameplayOptions * options; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

static class Symbol mash; // size: 0x4, address: 0x80A48F74
static class Symbol crash; // size: 0x4, address: 0x80A48F7C
// Range: 0x8001FD80 -> 0x8001FFD0
void GemTrack::UpdateFills(class GemTrack * const this /* r27 */) {
    // Local variables
    class Player * player; // r0
    class Symbol widName; // r1+0x10
    int lane; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11TrackWidget;
    // -> const char * gNullStr;
    // -> static class Symbol crash;
    // -> static class Symbol mash;
    // -> class GameConfig * TheGameConfig;
}

// Range: 0x8001FFD0 -> 0x8002000C
void GemTrack::SetPlayerState() {}

static class Symbol mash; // size: 0x4, address: 0x80A48F84
static class Symbol crash; // size: 0x4, address: 0x80A48F8C
// Range: 0x8002000C -> 0x800204F4
void GemTrack::DrawFill(class GemTrack * const this /* r25 */, class FillInfo * fill /* r26 */, int tick /* r27 */, int duration_ticks /* r21 */) {
    // Local variables
    struct FillExtent fillExtent; // r1+0x28
    class Player * player; // r22
    class Transform xform; // r1+0x40
    unsigned char drums; // r0
    unsigned char inCoda; // r0
    float fillStartTime; // f31
    float fillEndTime; // f30
    float fillDuration; // f29
    class EventTrigger * trig; // r0
    int laneMask; // r0
    int lane; // r21
    class Symbol widName; // r1+0x20
    class Symbol widName; // r1+0x1C

    // References
    // -> static class Symbol crash;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11TrackWidget;
    // -> const char * gNullStr;
    // -> static class Symbol mash;
    // -> class GameMode * TheGameMode;
    // -> class SongDB * TheSongDB;
    // -> class GameConfig * TheGameConfig;
}

static int res; // size: 0x4, address: 0x80A46298
// Range: 0x800204F4 -> 0x80020EB8
void GemTrack::Poll(class GemTrack * const this /* r27 */, float ms /* f29 */) {
    // Local variables
    int track; // r29
    int tick; // r0
    class TrackWidget * widgets; // r24
    class Transform xform; // r1+0x40
    int i; // r28
    struct MBT mbt; // r1+0x28
    float time; // f31
    class FillInfo * fill; // r23
    int start_tick; // r1+0x24
    int end_tick; // r1+0x20
    unsigned char inGuitarSolo; // r0
    float startTime; // f30
    float duration; // f29
    float codaTime; // f0
    int startSection; // r1+0x1C
    int endSection; // r1+0x18
    float start; // r1+0x14
    float end; // r1+0x10

    // References
    // -> class GamePanel * TheGamePanel;
    // -> class GameMode * TheGameMode;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11TrackWidget;
    // -> class SongDB * TheSongDB;
    // -> static int res;
    // -> class GameConfig * TheGameConfig;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80020EB8 -> 0x80020FB4
void GemTrack::SetDir(class GemTrack * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> struct [anonymous] __RTTI__11GemTrackDir;
}

// Range: 0x80020FB4 -> 0x80021094
void GemTrack::EnableSlot(class GemTrack * const this /* r30 */, int slot /* r29 */) {
    // Local variables
    int trackNum; // r0
    class vector & vec; // r0
    class GameGem * i; // r30

    // References
    // -> class Debug TheDebug;
    // -> class SongDB * TheSongDB;
    // -> class GameConfig * TheGameConfig;
}

// Range: 0x80021094 -> 0x80021174
void GemTrack::DisableSlot(class GemTrack * const this /* r30 */, int slot /* r29 */) {
    // Local variables
    int trackNum; // r0
    class vector & vec; // r0
    class GameGem * i; // r30

    // References
    // -> class Debug TheDebug;
    // -> class SongDB * TheSongDB;
    // -> class GameConfig * TheGameConfig;
}

// Range: 0x80021174 -> 0x800211D4
void GemTrack::HandleNewSong(class GemTrack * const this /* r31 */) {}

// Range: 0x800211D4 -> 0x80021234
void GemTrack::See(class GemTrack * const this /* r30 */) {
    // Local variables
    int slots; // r0
}

// Range: 0x80021234 -> 0x800212A0
void GemTrack::Hit(class GemTrack * const this /* r30 */, int gem_id /* r31 */) {
    // Local variables
    int slots; // r0
}

// Range: 0x800212A0 -> 0x800212A8
void GemTrack::Miss() {}

// Range: 0x800212A8 -> 0x80021300
void GemTrack::Pass(class GemTrack * const this /* r30 */, int gem_id /* r31 */) {
    // Local variables
    int lanes; // r0
}

// Range: 0x80021300 -> 0x80021308
void GemTrack::Ignore() {}

// Range: 0x80021308 -> 0x80021310
void GemTrack::SetFretButtonPressed() {}

// Range: 0x80021310 -> 0x80021318
void GemTrack::ReleaseGem() {}

// Range: 0x80021318 -> 0x800213C4
void GemTrack::Jump(class GemTrack * const this /* r31 */, float ms /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800213C4 -> 0x800213CC
class GemManager * GemTrack::GetGemManager() {}

// Range: 0x800213CC -> 0x80021434
void GemTrack::OnMissPhrase(class GemTrack * const this /* r31 */) {}

// Range: 0x80021434 -> 0x80021514
float GemTrack::NextKickNoteMs(const class GemTrack * const this /* r31 */) {
    // Local variables
    float nowMs; // f31
    int trackNum; // r0
    const class vector & gameGems; // r0
    int i; // r5

    // References
    // -> class SongDB * TheSongDB;
    // -> class GameConfig * TheGameConfig;
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x80021514 -> 0x80021608
void GemTrack::SetBonusGems(class GemTrack * const this /* r27 */, unsigned char bonus /* r28 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11TrackWidget;
}

// Range: 0x80021608 -> 0x80021610
void GemTrack::SetInCoda() {}

// Range: 0x80021610 -> 0x80021688
void GemTrack::UpdateEffects(class GemTrack * const this /* r30 */, int ixEffect /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80021688 -> 0x80021690
void GemTrack::SetSmasherGlowing() {}

// Range: 0x80021690 -> 0x80021698
void GemTrack::PopSmasher() {}

// Range: 0x80021698 -> 0x800216AC
void GemTrack::SetGemsEnabled() {}

// Range: 0x800216AC -> 0x800216F0
void GemTrack::SetGemsEnabledByPlayer(class GemTrack * const this /* r31 */) {}

// Range: 0x800216F0 -> 0x80021730
void GemTrack::UpdateGems(class GemTrack * const this /* r31 */) {}

// Range: 0x80021730 -> 0x80021748
class Object * GemTrack::GetSmasher() {}

static class Symbol _s; // size: 0x4, address: 0x80A48F94
static class Symbol _s; // size: 0x4, address: 0x80A48F9C
static class Symbol _s; // size: 0x4, address: 0x80A48FA4
static class Symbol _s; // size: 0x4, address: 0x80A48FAC
static class Symbol _s; // size: 0x4, address: 0x80A48FB4
static class Symbol _s; // size: 0x4, address: 0x80A48FBC
static class Symbol _s; // size: 0x4, address: 0x80A48FC4
static class Symbol _s; // size: 0x4, address: 0x80A48FCC
static class Symbol _s; // size: 0x4, address: 0x80A48FD4
static class Symbol _s; // size: 0x4, address: 0x80A48FDC
// Range: 0x80021748 -> 0x80022388
class DataNode GemTrack::Handle(class GemTrack * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x48
    class MessageTimer _mt; // r1+0x58
    class DataNode _n; // r1+0x50

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
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct Node {
    // total size: 0xC
    class RndPollable * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
class iterator {
    // total size: 0x4
    struct Node * mNode; // offset 0x0, size 0x4
};
enum VocalParam {
    kVocalParamAny = 0,
    kVocalParamMicVolume = 1,
    kVocalParamMicGain = 2,
    kVocalParamCueVolume = 3,
};
class TrackInterface : public Object {
    // total size: 0x28
};
enum CrowdMeterState {
    kNormal = 0,
    kWarning = 1,
    kFailed = 2,
    kInvalidState = 3,
};
class PlayerBehavior {
    // total size: 0x10
    unsigned char mCanDeployStarPower; // offset 0x0, size 0x1
    unsigned char mTiltDeploysBandEnergy; // offset 0x1, size 0x1
    unsigned char mFillsDeployBandEnergy; // offset 0x2, size 0x1
    unsigned char mRequireAllCodaLanes; // offset 0x3, size 0x1
    unsigned char mCanFreestyleBeforeGems; // offset 0x4, size 0x1
    unsigned char mHasSolos; // offset 0x5, size 0x1
    class Symbol mStreakType; // offset 0x8, size 0x4
    int mMaxMultiplier; // offset 0xC, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class Task * mPtr; // offset 0x8, size 0x4
};
class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndMatAnim * mPtr; // offset 0x8, size 0x4
};
class Key {
    // total size: 0x20
public:
    class Color value; // offset 0x0, size 0x10
    float frame; // offset 0x10, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Key * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Key * _M_start; // offset 0x0, size 0x4
    class Key * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class Keys : public vector {
    // total size: 0xC
};
class Key {
    // total size: 0x8
public:
    float value; // offset 0x0, size 0x4
    float frame; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Key * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Key * _M_start; // offset 0x0, size 0x4
    class Key * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class Keys : public vector {
    // total size: 0xC
};
class Key {
    // total size: 0x20
public:
    class Vector3 value; // offset 0x0, size 0x10
    float frame; // offset 0x10, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Key * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Key * _M_start; // offset 0x0, size 0x4
    class Key * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class TexPtr : public ObjPtr {
    // total size: 0xC
};
class Keys : public vector {
    // total size: 0xC
};
class TexKeys : public Keys {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class RndMatAnim : public RndAnimatable {
    // total size: 0xA0
protected:
    class ObjPtr mMat; // offset 0x10, size 0xC
    class ObjOwnerPtr mKeysOwner; // offset 0x1C, size 0xC
    class Keys mColorKeys; // offset 0x28, size 0xC
    class Keys mAlphaKeys; // offset 0x34, size 0xC
    class Keys mTransKeys; // offset 0x40, size 0xC
    class Keys mScaleKeys; // offset 0x4C, size 0xC
    class Keys mRotKeys; // offset 0x58, size 0xC
    class TexKeys mTexKeys; // offset 0x64, size 0x10
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndMatAnim * mPtr; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class Object * mPtr; // offset 0x8, size 0x4
};
enum AnimKeysType {
    kFloat = 0,
    kColor = 1,
    kObject = 2,
    kBool = 3,
    kQuat = 4,
    kVector3 = 5,
};
enum Interpolation {
    kStep = 0,
    kLinear = 1,
    kSpline = 2,
    kSlerp = 3,
};
class Key {
    // total size: 0x20
public:
    class Quat value; // offset 0x0, size 0x10
    float frame; // offset 0x10, size 0x4
};
class Key {
    // total size: 0x8
public:
    unsigned char value; // offset 0x0, size 0x1
    float frame; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Key * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Key * _M_start; // offset 0x0, size 0x4
    class Key * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class Keys : public vector {
    // total size: 0xC
};
class ObjectStage : public ObjPtr {
    // total size: 0xC
};
class Key {
    // total size: 0x10
public:
    class ObjectStage value; // offset 0x0, size 0xC
    float frame; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Key * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Key * _M_start; // offset 0x0, size 0x4
    class Key * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class Keys : public vector {
    // total size: 0xC
};
class ObjKeys : public Keys {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
enum ExceptionID {
    kNoException = 0,
    kTransQuat = 1,
    kTransScale = 2,
    kTransPos = 3,
    kDirEvent = 4,
};
class PropKeys {
    // total size: 0x24
public:
    void * __vptr$; // offset 0x0, size 0x4
    class ObjOwnerPtr mTarget; // offset 0x4, size 0xC
    class DataArray * mProp; // offset 0x10, size 0x4
    enum AnimKeysType mKeysType; // offset 0x14, size 0x4
    enum Interpolation mInterpolation; // offset 0x18, size 0x4
    int mPropExceptionID; // offset 0x1C, size 0x4
    class RndTransformable * mTrans; // offset 0x20, size 0x4
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class RndPropAnim : public RndAnimatable {
    // total size: 0x48
protected:
    class list mPropKeys; // offset 0x10, size 0x8
    float mLastFrame; // offset 0x18, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndPropAnim * mPtr; // offset 0x8, size 0x4
};
enum Format {
    kPCM = 0,
    kBigEndPCM = 1,
    kVAG = 2,
    kXMA = 3,
    kATRAC = 4,
    kNintendoADPCM = 5,
};
class SampleData {
    // total size: 0x14
    int mNumSamples; // offset 0x0, size 0x4
    int mSampleRate; // offset 0x4, size 0x4
    int mSizeBytes; // offset 0x8, size 0x4
    enum Format mFormat; // offset 0xC, size 0x4
    void * mData; // offset 0x10, size 0x4
};
class SynthSample : public Object {
    // total size: 0x54
protected:
    class FilePath mFile; // offset 0x28, size 0xC
    unsigned char mIsLooped; // offset 0x34, size 0x1
    int mLoopStartSamp; // offset 0x38, size 0x4
    int mLoopEndSamp; // offset 0x3C, size 0x4
    class SampleData mSampleData; // offset 0x40, size 0x14
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class SynthSample * mPtr; // offset 0x8, size 0x4
};
enum AttackMode {
    kAttackLinear = 0,
    kAttackExp = 1,
};
enum SustainMode {
    kSustainLinInc = 0,
    kSustainLinDec = 2,
    kSustainExpInc = 4,
    kSustainExpDec = 6,
};
enum ReleaseMode {
    kReleaseLinear = 0,
    kReleaseExp = 1,
};
class Ps2ADSR {
    // total size: 0x4
    unsigned short mReg1; // offset 0x0, size 0x2
    unsigned short mReg2; // offset 0x2, size 0x2
};
class ADSR {
    // total size: 0x28
    float mAttackRate; // offset 0x0, size 0x4
    float mDecayRate; // offset 0x4, size 0x4
    float mSustainRate; // offset 0x8, size 0x4
    float mReleaseRate; // offset 0xC, size 0x4
    float mSustainLevel; // offset 0x10, size 0x4
    enum AttackMode mAttackMode; // offset 0x14, size 0x4
    enum SustainMode mSustainMode; // offset 0x18, size 0x4
    enum ReleaseMode mReleaseMode; // offset 0x1C, size 0x4
    class Ps2ADSR mPacked; // offset 0x20, size 0x4
    unsigned char mSynced; // offset 0x24, size 0x1
};
class SfxMap {
    // total size: 0x44
public:
    class ObjPtr mSample; // offset 0x0, size 0xC
    float mVolume; // offset 0xC, size 0x4
    float mPan; // offset 0x10, size 0x4
    float mTranspose; // offset 0x14, size 0x4
    enum FXCore mFX; // offset 0x18, size 0x4
    class ADSR mADSR; // offset 0x1C, size 0x28
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class SfxMap * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class SfxMap * _M_start; // offset 0x0, size 0x4
    class SfxMap * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class FxSend * mPtr; // offset 0x8, size 0x4
};
enum SendChannels {
    kSendAll = 0,
    kSendCenter = 1,
    kSendStereo = 2,
};
class FxSend : public Object {
    // total size: 0x50
protected:
    class ObjOwnerPtr mNextSend; // offset 0x28, size 0xC
    int mStage; // offset 0x34, size 0x4
    unsigned char mBypass; // offset 0x38, size 0x1
    float mDryGain; // offset 0x3C, size 0x4
    float mWetGain; // offset 0x40, size 0x4
    float mInputGain; // offset 0x44, size 0x4
    unsigned char mEnableUpdates; // offset 0x48, size 0x1
    enum SendChannels mChannels; // offset 0x4C, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class FxSend * mPtr; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class SampleInst * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class SampleInst * * _M_start; // offset 0x0, size 0x4
    class SampleInst * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class SfxInst : public SeqInst {
    // total size: 0x50
    class vector mSamples; // offset 0x40, size 0xC
    float mStartProgress; // offset 0x4C, size 0x4
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
class Sfx : public Sequence {
    // total size: 0xA8
    class ObjVector mMaps; // offset 0x78, size 0x10
    class ObjPtr mSend; // offset 0x88, size 0xC
    class ObjPtrList mSfxInsts; // offset 0x94, size 0x14
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class Sfx * mPtr; // offset 0x8, size 0x4
};
class BandPowerMeter : public RndDir {
    // total size: 0x2F0
    float mTestEnergy; // offset 0x1F4, size 0x4
    float mEnergy; // offset 0x1F8, size 0x4
    class Symbol mState; // offset 0x1FC, size 0x4
    unsigned char mVocalMeter; // offset 0x200, size 0x1
    class ObjPtr mBeatTask; // offset 0x204, size 0xC
    class ObjPtr mBandMeterFillMatAnim; // offset 0x210, size 0xC
    class ObjPtr mBandMeterFillAnim; // offset 0x21C, size 0xC
    class ObjPtr mExtendAnimGroup; // offset 0x228, size 0xC
    class ObjPtr mResetTrigger; // offset 0x234, size 0xC
    class ObjPtr mBeReadyTrigger; // offset 0x240, size 0xC
    class ObjPtr mBeDeployingTrigger; // offset 0x24C, size 0xC
    class ObjPtr mBeFillingTrigger; // offset 0x258, size 0xC
    class ObjPtr mSpotlightPhraseSuccessTrigger; // offset 0x264, size 0xC
    class ObjPtr mNoOverdriveTrigger; // offset 0x270, size 0xC
    class ObjPtr mAvailableGuitarSfx; // offset 0x27C, size 0xC
    class ObjPtr mAvailableBassSfx; // offset 0x288, size 0xC
    class ObjPtr mAvailableDrumSfx; // offset 0x294, size 0xC
    class ObjPtr mAvailableVocalsSfx; // offset 0x2A0, size 0xC
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class BandPowerMeter * mPtr; // offset 0x8, size 0x4
};
class Style {
    // total size: 0x30
public:
    float size; // offset 0x0, size 0x4
    float italics; // offset 0x4, size 0x4
    class Color color; // offset 0x10, size 0x10
    unsigned char hyphen; // offset 0x20, size 0x1
    unsigned char brk; // offset 0x21, size 0x1
};
class Line {
    // total size: 0x50
public:
    class Style style; // offset 0x0, size 0x30
    const char * start; // offset 0x30, size 0x4
    const char * end; // offset 0x34, size 0x4
    float z; // offset 0x38, size 0x4
    float x; // offset 0x3C, size 0x4
    float width; // offset 0x40, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Line * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Line * _M_start; // offset 0x0, size 0x4
    class Line * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class CharInfo {
    // total size: 0x10
public:
    float normX; // offset 0x0, size 0x4
    float normY; // offset 0x4, size 0x4
    float charWidth; // offset 0x8, size 0x4
    float charAdvance; // offset 0xC, size 0x4
};
class RndFont : public Object {
    // total size: 0x1070
protected:
    class ObjPtr mMat; // offset 0x28, size 0xC
    class ObjOwnerPtr mTextureOwner; // offset 0x34, size 0xC
    class CharInfo mCharInfos[256]; // offset 0x40, size 0x1000
    class KerningTable * mKerning; // offset 0x1040, size 0x4
    float mBaseKerning; // offset 0x1044, size 0x4
    class Vector2 mCellSize; // offset 0x1048, size 0x8
    float mDeprecatedSize; // offset 0x1050, size 0x4
    class String mChars; // offset 0x1054, size 0xC
    unsigned char mMonospace; // offset 0x1060, size 0x1
    class Vector2 mNormCellSize; // offset 0x1064, size 0x8
    unsigned char mPacked; // offset 0x106C, size 0x1
};
class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndFont * mPtr; // offset 0x8, size 0x4
};
enum Alignment {
    kTopLeft = 17,
    kTopCenter = 18,
    kTopRight = 20,
    kMiddleLeft = 33,
    kMiddleCenter = 34,
    kMiddleRight = 36,
    kBottomLeft = 65,
    kBottomCenter = 66,
    kBottomRight = 68,
};
enum CapsMode {
    kCapsModeNone = 0,
    kForceLower = 1,
    kForceUpper = 2,
};
class JitterCallback {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class RndText : public RndDrawable, public RndTransformable {
    // total size: 0x1E0
protected:
    class vector mLines; // offset 0xF8, size 0xC
    int mDisplayableChars; // offset 0x104, size 0x4
    class ObjOwnerPtr mFont; // offset 0x108, size 0xC
    float mWrapWidth; // offset 0x114, size 0x4
    enum Alignment mAlignment; // offset 0x118, size 0x4
    enum CapsMode mCapsMode; // offset 0x11C, size 0x4
    float mLeading; // offset 0x120, size 0x4
    class String mText; // offset 0x124, size 0xC
    int mFixedLength; // offset 0x130, size 0x4
    class Style mStyle; // offset 0x140, size 0x30
    unsigned char mMarkup; // offset 0x170, size 0x1
    unsigned char mUseAutoHyph; // offset 0x171, size 0x1
    int mMinHyphWordLength; // offset 0x174, size 0x4
    int mMinHyphPrefix; // offset 0x178, size 0x4
    int mMinHyphSuffix; // offset 0x17C, size 0x4
    class RndMesh * mMesh; // offset 0x180, size 0x4
    class JitterCallback * mJitter; // offset 0x184, size 0x4
    class String mMissingChars; // offset 0x188, size 0xC
    unsigned char mMissingNotify; // offset 0x194, size 0x1
    class String mNegChars; // offset 0x198, size 0xC
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndText * mPtr; // offset 0x8, size 0x4
};
class StreakMeter : public RndDir {
    // total size: 0x2C0
    int mStreakMultiplier; // offset 0x1F4, size 0x4
    int mBandMultiplier; // offset 0x1F8, size 0x4
    int mMaxMultiplier; // offset 0x1FC, size 0x4
    unsigned char mShowBandMult; // offset 0x200, size 0x1
    class ObjPtr mBuildStreakTrig; // offset 0x204, size 0xC
    class ObjPtr mEndStreakTrig; // offset 0x210, size 0xC
    class ObjPtr mSuperStreakTrig; // offset 0x21C, size 0xC
    class ObjPtr mBreakOverdriveTrig; // offset 0x228, size 0xC
    class ObjPtr mMultMeterAnim; // offset 0x234, size 0xC
    class ObjPtr mMultMeterText; // offset 0x240, size 0xC
    class ObjPtr mMeterWipeAnim; // offset 0x24C, size 0xC
    class ObjPtr mOverdriveTrig; // offset 0x258, size 0xC
    class ObjPtr mEndOverdriveTrig; // offset 0x264, size 0xC
    class ObjPtr mStopDepoyTrig; // offset 0x270, size 0xC
    class ObjPtr mResetTrig; // offset 0x27C, size 0xC
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class StreakMeter * mPtr; // offset 0x8, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class TrackInterface * mPtr; // offset 0x8, size 0x4
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
struct Node {
    // total size: 0xC
    class TrackWidget * object; // offset 0x0, size 0x4
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
class GemTrackDir : public TrackDir, public BandTrack {
    // total size: 0x510
    int mIndex; // offset 0x36C, size 0x4
    int mNumTracks; // offset 0x370, size 0x4
    int mMultiplier; // offset 0x374, size 0x4
    int mKickPassCounter; // offset 0x378, size 0x4
    float mStreakOffset; // offset 0x37C, size 0x4
    float mStreakMeterTilt; // offset 0x380, size 0x4
    float mTrackPitch; // offset 0x384, size 0x4
    int mGemTrackCount; // offset 0x388, size 0x4
    class ObjPtr mEffectSelector; // offset 0x38C, size 0xC
    class ObjPtr mRotater; // offset 0x398, size 0xC
    class ObjPtr mSurfaceTexture; // offset 0x3A4, size 0xC
    class ObjPtr mSurfaceMesh; // offset 0x3B0, size 0xC
    class ObjPtr mSurfaceMat; // offset 0x3BC, size 0xC
    class ObjPtr mTrackEnv; // offset 0x3C8, size 0xC
    class ObjPtr mGameCam; // offset 0x3D4, size 0xC
    class ObjPtr mBassSuperStreakOnTrig; // offset 0x3E0, size 0xC
    class ObjPtr mBassSuperStreakOffTrig; // offset 0x3EC, size 0xC
    class ObjPtr mKickDrummerTrig; // offset 0x3F8, size 0xC
    class ObjPtr mSpotlightPhraseSuccessTrig; // offset 0x404, size 0xC
    class ObjPtr mSoloHitTrig; // offset 0x410, size 0xC
    class vector mGemMashAnims; // offset 0x41C, size 0xC
    class vector mDrumMashAnims; // offset 0x428, size 0xC
    class vector mFillHitTrigs; // offset 0x434, size 0xC
    class ObjPtr mDrumFillResetTrig; // offset 0x440, size 0xC
    class ObjPtr mDrumMash2ndPassActivateAnim; // offset 0x44C, size 0xC
    class ObjPtr mDrumMashHitAnimGrp; // offset 0x458, size 0xC
    class ObjPtr mFillColorsGrp; // offset 0x464, size 0xC
    class ObjPtr mLODAnim; // offset 0x470, size 0xC
    class ObjPtr mSmasherPlate; // offset 0x47C, size 0xC
    class ObjPtrList mGlowWidgets; // offset 0x488, size 0x14
    class ObjPtr mFxHiderTask; // offset 0x49C, size 0xC
    class ObjPtr mClearAllWidgetsTask; // offset 0x4A8, size 0xC
    class ObjPtr mUpdateGemsTask; // offset 0x4B4, size 0xC
    class ObjPtr mPlayIntroTask; // offset 0x4C0, size 0xC
    unsigned char mCrashAppeared; // offset 0x4CC, size 0x1
};
class BandTrack {
    // total size: 0xE8
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    unsigned char mDisabled; // offset 0x4, size 0x1
    unsigned char mSimulatedNet; // offset 0x5, size 0x1
    class Symbol mInstrument; // offset 0x8, size 0x4
    int mMaxMultiplier; // offset 0xC, size 0x4
    unsigned char mSuperStreak; // offset 0x10, size 0x1
    unsigned char mNoOverdrive; // offset 0x11, size 0x1
    unsigned char mWarning; // offset 0x12, size 0x1
    unsigned char mActive; // offset 0x13, size 0x1
    class ObjPtr mPlayerIntro; // offset 0x14, size 0xC
    class ObjPtr mOverdriveMeter; // offset 0x20, size 0xC
    class ObjPtr mStreakMeter; // offset 0x2C, size 0xC
    class ObjPtr mPopupObject; // offset 0x38, size 0xC
    class ObjPtr mPlayerFeedback; // offset 0x44, size 0xC
    class ObjPtr mFailedFeedback; // offset 0x50, size 0xC
    class Symbol mLastPopup; // offset 0x5C, size 0x4
    unsigned char mPopupActive; // offset 0x60, size 0x1
    class RndDir * mFinaleFeedback; // offset 0x64, size 0x4
    unsigned int mFinaleStartCycle; // offset 0x68, size 0x4
    unsigned char mFinaleHelpActive; // offset 0x6C, size 0x1
    class ObjPtr mTrack; // offset 0x70, size 0xC
    class ObjPtr mDir; // offset 0x7C, size 0xC
    class ObjPtr mRetractTrig; // offset 0x88, size 0xC
    class ObjPtr mResetTrig; // offset 0x94, size 0xC
    class ObjPtr mDeploy; // offset 0xA0, size 0xC
    class ObjPtr mStopDeploy; // offset 0xAC, size 0xC
    class ObjPtr mIntro; // offset 0xB8, size 0xC
    class ObjPtr mDisconnectTask; // offset 0xC4, size 0xC
    class ObjPtr mHideIntroTask; // offset 0xD0, size 0xC
    class ObjPtr mDelayedFailTask; // offset 0xDC, size 0xC
};
class Track : public TrackInterface {
    // total size: 0x64
protected:
    class TrackConfig mTrackConfig; // offset 0x28, size 0x2C
    float mLastRating; // offset 0x54, size 0x4
    enum CrowdMeterState mLastRatingState; // offset 0x58, size 0x4
    int mLastStreakCount; // offset 0x5C, size 0x4
    class GameplayOptions * mGameplayOptions; // offset 0x60, size 0x4
};
struct {
    // total size: 0x120
} __vt__8GemTrack; // size: 0x120, address: 0x8086E7E0
struct {
    // total size: 0x8
} __RTTI__8GemTrack; // size: 0x8, address: 0x8086E930
struct {
    // total size: 0x18
} __vt__32ObjPtr<11GemTrackDir,9ObjectDir>; // size: 0x18, address: 0x8086E938
struct {
    // total size: 0x8
} __RTTI__32ObjPtr<11GemTrackDir,9ObjectDir>; // size: 0x8, address: 0x8086E980
struct {
    // total size: 0x8
} __RTTI__11GemTrackDir; // size: 0x8, address: 0x8086EA00
struct {
    // total size: 0x8
} __RTTI__9BandTrack; // size: 0x8, address: 0x8086EA18
struct {
    // total size: 0x8
} __RTTI__5Track; // size: 0x8, address: 0x8086EA48
struct {
    // total size: 0x8
} __RTTI__14TrackInterface; // size: 0x8, address: 0x8086EA78
struct {
    // total size: 0x8
} __RTTI__8TrackDir; // size: 0x8, address: 0x8086EB28
struct {
    // total size: 0x8
} __RTTI__8PanelDir; // size: 0x8, address: 0x8086EB90

