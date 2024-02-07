/*
    Compile unit: C:\rockband2\band2\src\bandtrack\Gem.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80016748 -> 0x800174E0
*/
class TrackWidget : public RndDrawable, public RndPollable {
    // total size: 0xB0
    class ObjPtrList mMeshes; // offset 0x3C, size 0x14
    class ObjPtr mEnv; // offset 0x50, size 0xC
    float mBaseLength; // offset 0x5C, size 0x4
    unsigned char mUseMulti; // offset 0x60, size 0x1
    unsigned char mAllowRotation; // offset 0x61, size 0x1
    int mMaxMeshes; // offset 0x64, size 0x4
    class TrackDir * mTrackDir; // offset 0x68, size 0x4
    class TrackWidgetImp * mImp; // offset 0x6C, size 0x4
};
struct SlotPosition {
    // total size: 0x8
    float x; // offset 0x0, size 0x4
    float z; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct SlotPosition * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct SlotPosition * _M_start; // offset 0x0, size 0x4
    struct SlotPosition * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class TrackDir : public PanelDir {
    // total size: 0x2C0
    unsigned char mRunning; // offset 0x249, size 0x1
    class ObjPtr mDrawGroup; // offset 0x24C, size 0xC
    class ObjPtr mAnimGroup; // offset 0x258, size 0xC
    float mYPerSecond; // offset 0x264, size 0x4
    float mTopY; // offset 0x268, size 0x4
    float mBottomY; // offset 0x26C, size 0x4
    class vector mSlots; // offset 0x270, size 0xC
    unsigned char mWarnOnResort; // offset 0x27C, size 0x1
    class TrackTest * mTest; // offset 0x280, size 0x4
};
class TrackConfig {
    // total size: 0x2C
    int kPlayer; // offset 0x0, size 0x4
    class Symbol kType; // offset 0x4, size 0x4
    unsigned char kDualPerspective; // offset 0x8, size 0x1
    int mTrackNum; // offset 0xC, size 0x4
    int mNumSlots; // offset 0x10, size 0x4
    class Symbol mName; // offset 0x14, size 0x4
    unsigned char mLefty; // offset 0x18, size 0x1
    int mGemTrackCount; // offset 0x1C, size 0x4
    class vector mSlotSpacing; // offset 0x20, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Gem * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Gem * _M_start; // offset 0x0, size 0x4
    class Gem * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct HitGem {
    // total size: 0x8
    float startTime; // offset 0x0, size 0x4
    int gem_id; // offset 0x4, size 0x4
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class RndMesh * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class RndMesh * * _M_start; // offset 0x0, size 0x4
    class RndMesh * * _M_finish; // offset 0x4, size 0x4
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
    class RndGroup * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class RndGroup * * _M_start; // offset 0x0, size 0x4
    class RndGroup * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct GemRepTemplate {
    // total size: 0xB4
    class vector mTails; // offset 0x0, size 0xC
    class ObjectDir * objectDir; // offset 0xC, size 0x4
    class vector gemGroups; // offset 0x10, size 0xC
    class RndMat * slotMats[2][5]; // offset 0x1C, size 0x28
    class RndMat * tailMiss; // offset 0x44, size 0x4
    class RndMat * tailStar; // offset 0x48, size 0x4
    class RndMat * tailBonus; // offset 0x4C, size 0x4
    class RndMat * tailGlowStar; // offset 0x50, size 0x4
    class RndMat * tailGlowWhammy; // offset 0x54, size 0x4
    class RndMat * tailGlowBonus; // offset 0x58, size 0x4
    class RndMat * tailGlowTight; // offset 0x5C, size 0x4
    class RndParticleSys * tailStarPS; // offset 0x60, size 0x4
    const class DataArray * mConfig; // offset 0x64, size 0x4
    float kTailGlowWidth; // offset 0x68, size 0x4
    float kTailGlowTightWidth; // offset 0x6C, size 0x4
    float kTailPulseRate; // offset 0x70, size 0x4
    float kTailPulseSmoothing; // offset 0x74, size 0x4
    float kTailOffsetX; // offset 0x78, size 0x4
    float kTailMinAlpha; // offset 0x7C, size 0x4
    float kTailMaxAlpha; // offset 0x80, size 0x4
    float kTailAlphaSmoothing; // offset 0x84, size 0x4
    float kTailFadeDistance; // offset 0x88, size 0x4
    class Vector2 kTailFrequencyRange; // offset 0x8C, size 0x8
    class Vector2 kTailAmplitudeRange; // offset 0x94, size 0x8
    int num_tail_sections; // offset 0x9C, size 0x4
    float tail_section_length; // offset 0xA0, size 0x4
    class VertVector tailVerts; // offset 0xA4, size 0x8
    float mBonusStartTime; // offset 0xAC, size 0x4
    const class TrackConfig & mTrackCfg; // offset 0xB0, size 0x4
};
class GemManager {
    // total size: 0x128
public:
    class TrackDir * mTrackDir; // offset 0x0, size 0x4
    const class TrackConfig & mTrackCfg; // offset 0x4, size 0x4
private:
    class vector mGems; // offset 0x8, size 0xC
    class DataArray * mGemData; // offset 0x14, size 0x4
    float mGemsEnabledStart; // offset 0x18, size 0x4
    class vector mMissedPhrases; // offset 0x1C, size 0xC
    class list mHitGems; // offset 0x28, size 0x8
    int mBegin; // offset 0x30, size 0x4
    int mEnd; // offset 0x34, size 0x4
    struct GemRepTemplate mTemplate; // offset 0x38, size 0xB4
    class DataArray * mConfig; // offset 0xEC, size 0x4
    class NowBar * mNowBar; // offset 0xF0, size 0x4
    unsigned char mBonusGems; // offset 0xF4, size 0x1
    unsigned char mInCoda; // offset 0xF5, size 0x1
    float mWhammyActive; // offset 0xF8, size 0x4
    float kHorizonY; // offset 0xFC, size 0x4
    float kRemoveY; // offset 0x100, size 0x4
    float kNowBarTailClip; // offset 0x104, size 0x4
    class list mDisabledSlotsList; // offset 0x108, size 0x8
    class map mSlotRolls; // offset 0x110, size 0x18
};
class set {
    // total size: 0x18
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
class Gem {
    // total size: 0x40
    class GemManager * mGemManager; // offset 0x0, size 0x4
    const class GameGem & mGameGem; // offset 0x4, size 0x4
    class set mWidgets; // offset 0x8, size 0x18
    float mStart; // offset 0x20, size 0x4
    float mEnd; // offset 0x24, size 0x4
    float mTailStart; // offset 0x28, size 0x4
    unsigned char mHit; // offset 0x2C, size 0x1
    unsigned char mMissed; // offset 0x2D, size 0x1
    unsigned char mReleased; // offset 0x2E, size 0x1
    unsigned char mHopo; // offset 0x2F, size 0x1
    unsigned char mInvisible; // offset 0x30, size 0x1
    unsigned char mSlots; // offset 0x31, size 0x1
    class vector mTails; // offset 0x34, size 0xC
};
// Range: 0x80016748 -> 0x800167CC
void * Gem::Gem() {}

class StlNodeAlloc {
    // total size: 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x10
public:
    struct _Rb_tree_node_base _M_data; // offset 0x0, size 0x10
};
struct _Rb_tree_base {
    // total size: 0x10
protected:
    class _STLP_alloc_proxy _M_header; // offset 0x0, size 0x10
};
struct binary_function {
    // total size: 0x1
};
struct __stlport_class {
    // total size: 0x1
};
struct less : public binary_function, public __stlport_class {
    // total size: 0x1
};
class _Rb_tree : public _Rb_tree_base {
    // total size: 0x18
protected:
    unsigned long _M_node_count; // offset 0x10, size 0x4
    struct less _M_key_compare; // offset 0x14, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class DelayLine {
    // total size: 0x4B4
    float mData[300]; // offset 0x0, size 0x4B0
    int mCur; // offset 0x4B0, size 0x4
};
enum State {
    kFuture = 0,
    kMissed = 1,
    kHit = 2,
    kReleased = 3,
};
class Tail {
    // total size: 0x4F4
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    class RndGroup * mGroup; // offset 0x4, size 0x4
    class RndLine * mTailGlow; // offset 0x8, size 0x4
    class RndMesh * mTail1; // offset 0xC, size 0x4
    class RndMesh * mTail2; // offset 0x10, size 0x4
    class RndParticleSys * mTailPS; // offset 0x14, size 0x4
    float mTailBegin; // offset 0x18, size 0x4
    float mTailEnd; // offset 0x1C, size 0x4
    class DelayLine mWhammy; // offset 0x20, size 0x4B4
    float mFilteredTailWidth; // offset 0x4D4, size 0x4
    float mWaveTime; // offset 0x4D8, size 0x4
    float mLastWhammyVal; // offset 0x4DC, size 0x4
    float mLastWhammyAlpha; // offset 0x4E0, size 0x4
    class Symbol mType; // offset 0x4E4, size 0x4
    enum State mState; // offset 0x4E8, size 0x4
    int mSlot; // offset 0x4EC, size 0x4
    struct GemRepTemplate & mTemplate; // offset 0x4F0, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Tail * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Tail * * _M_start; // offset 0x0, size 0x4
    class Tail * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x800167CC -> 0x8001691C
void * Gem::~Gem(class Gem * const this /* r30 */) {}

// Range: 0x8001691C -> 0x80016980
unsigned char Gem::OnScreen(class Gem * const this /* r31 */, float ms /* f31 */) {}

// Range: 0x80016980 -> 0x80016AFC
void Gem::Poll(class Gem * const this /* r30 */, float ms /* f27 */, float whammy /* f28 */, float whammyActive /* f29 */) {
    // Local variables
    float topSeconds; // f31
    float cutoffSeconds; // f3
    float tail_end; // f1
    float tail_start; // f30
    int i; // r31
}

static class Symbol invisible; // size: 0x4, address: 0x80A48F04
// Range: 0x80016AFC -> 0x80016CE0
void Gem::AddRep(class Gem * const this /* r26 */, struct GemRepTemplate & gemTemplate /* r27 */, class RndGroup * parent /* r28 */, class Symbol & type /* r29 */) {
    // Local variables
    float t; // f31
    class Tail * firstTail; // r31
    int i; // r30
    class Tail * tail; // r1+0x14

    // References
    // -> static class Symbol invisible;
}

// Range: 0x80016CE0 -> 0x80016DAC
void Gem::RemoveRep(class Gem * const this /* r29 */) {
    // Local variables
    int i; // r30
}

// Range: 0x80016DAC -> 0x80016FE8
void Gem::AddInstance(class Gem * const this /* r27 */, class Symbol & state /* r30 */, int slot /* r28 */) {
    // Local variables
    class TrackDir * trackDir; // r29
    class Symbol widgetName; // r1+0x24
    class Symbol hopoStateName; // r1+0x20
    class TrackWidget * widget; // r1+0x1C
    class Transform t; // r1+0x40

    // References
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11TrackWidget;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
// Range: 0x80016FE8 -> 0x800170D8
void Gem::RemoveAllInstances(class Gem * const this /* r30 */) {
    // Local variables
    int i; // r31
    struct _Rb_tree_iterator it; // r1+0x10
}

static class Symbol invisible; // size: 0x4, address: 0x80A48F0C
// Range: 0x800170D8 -> 0x80017214
void Gem::SetType(class Gem * const this /* r30 */, class Symbol & type /* r31 */) {
    // Local variables
    int i; // r28
    int i; // r28

    // References
    // -> static class Symbol invisible;
}

static class Symbol miss; // size: 0x4, address: 0x80A48F14
// Range: 0x80017214 -> 0x800172FC
void Gem::Miss(class Gem * const this /* r31 */) {
    // Local variables
    int i; // r30
    int i; // r29

    // References
    // -> static class Symbol miss;
}

// Range: 0x800172FC -> 0x80017370
void Gem::Hit(class Gem * const this /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x80017370 -> 0x800173DC
void Gem::Release(class Gem * const this /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x800173DC -> 0x80017460
void Gem::ApplyDuration(class Gem * const this /* r30 */, float start_y /* f30 */, float end_y /* f31 */) {
    // Local variables
    int i; // r31
}

// Range: 0x80017460 -> 0x800174C4
void Gem::KillDuration(class Gem * const this /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x800174C4 -> 0x800174E0
void Gem::Reset() {}

struct {
    // total size: 0x8
} __RTTI__11TrackWidget; // size: 0x8, address: 0x8086D8C8
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct {
    // total size: 0x8
} __RTTI__PP4Tail; // size: 0x8, address: 0x8086D990
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std29_Rb_tree_node<P11TrackWidget>; // size: 0x8, address: 0x8086D9C8

