/*
    Compile unit: C:\rockband2\band2\src\bandtrack\GemRepTemplate.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8001B418 -> 0x8001BE5C
*/
class Symbol name; // size: 0x4, address: 0x80A48F5C
class Symbol name; // size: 0x4, address: 0x80A48F64
enum Type {
    kBasic = 0,
    kFancy = 1,
};
class RndParticle {
    // total size: 0x60
public:
    class Color col; // offset 0x0, size 0x10
    class Color colVel; // offset 0x10, size 0x10
    class Vector4 pos; // offset 0x20, size 0x10
    class Vector4 vel; // offset 0x30, size 0x10
    float deathFrame; // offset 0x40, size 0x4
    float birthFrame; // offset 0x44, size 0x4
    float size; // offset 0x48, size 0x4
    float sizeVel; // offset 0x4C, size 0x4
    float angle; // offset 0x50, size 0x4
    float swingArm; // offset 0x54, size 0x4
    class RndParticle * prev; // offset 0x58, size 0x4
    class RndParticle * next; // offset 0x5C, size 0x4
};
class Burst {
    // total size: 0x10
protected:
    float mPeak; // offset 0x0, size 0x4
    float mHalfLength; // offset 0x4, size 0x4
    float mNorm; // offset 0x8, size 0x4
    float mTimeToLive; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Burst * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Burst * _M_start; // offset 0x0, size 0x4
    class Burst * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class RndParticleSys : public RndAnimatable, public RndPollable, public RndTransformable, public RndDrawable {
    // total size: 0x390
protected:
    enum Type mType; // offset 0x114, size 0x4
    int mMaxParticles; // offset 0x118, size 0x4
    class RndParticle * mActiveParticles; // offset 0x11C, size 0x4
    int mNumActive; // offset 0x120, size 0x4
    float mEmitCount; // offset 0x124, size 0x4
    unsigned char mFrameDrive; // offset 0x128, size 0x1
    float mLastFrame; // offset 0x12C, size 0x4
    int mPollsSinceDraw; // offset 0x130, size 0x4
    unsigned char mPauseOffscreen; // offset 0x134, size 0x1
    float mSleepTime; // offset 0x138, size 0x4
    class Vector2 mLife; // offset 0x13C, size 0x8
    class Vector3 mPosLow; // offset 0x150, size 0x10
    class Vector3 mPosHigh; // offset 0x160, size 0x10
    class Vector2 mSpeed; // offset 0x170, size 0x8
    class Vector2 mPitch; // offset 0x178, size 0x8
    class Vector2 mYaw; // offset 0x180, size 0x8
    class Vector2 mEmitRate; // offset 0x188, size 0x8
    class Vector2 mStartSize; // offset 0x190, size 0x8
    class Vector2 mDeltaSize; // offset 0x198, size 0x8
    class Color mStartColorLow; // offset 0x1A0, size 0x10
    class Color mStartColorHigh; // offset 0x1B0, size 0x10
    class Color mEndColorLow; // offset 0x1C0, size 0x10
    class Color mEndColorHigh; // offset 0x1D0, size 0x10
    class ObjPtr mMesh; // offset 0x1E0, size 0xC
    class ObjPtr mMat; // offset 0x1EC, size 0xC
    unsigned char mPreserveParticles; // offset 0x1F8, size 0x1
    class Transform mRelativeXfm; // offset 0x200, size 0x40
    class Transform mLastWorldXfm; // offset 0x240, size 0x40
    float mRelativeMotion; // offset 0x280, size 0x4
    class ObjOwnerPtr mRelativeParent; // offset 0x284, size 0xC
    class ObjPtr mBounce; // offset 0x290, size 0xC
    class Vector3 mForce; // offset 0x2A0, size 0x10
    unsigned char mFastForward; // offset 0x2B0, size 0x1
    unsigned char mNeedForward; // offset 0x2B1, size 0x1
    unsigned char mRotate; // offset 0x2B2, size 0x1
    class Vector2 mRotSpeed; // offset 0x2B4, size 0x8
    float mRotDrag; // offset 0x2BC, size 0x4
    unsigned char mRotRandomDir; // offset 0x2C0, size 0x1
    class Vector2 mSwingArmStart; // offset 0x2C4, size 0x8
    class Vector2 mSwingArmEnd; // offset 0x2CC, size 0x8
    float mHeightRatio; // offset 0x2D4, size 0x4
    int mSubSamples; // offset 0x2D8, size 0x4
    class Transform mSubSampleXfm; // offset 0x2E0, size 0x40
    class vector mBursts; // offset 0x320, size 0xC
    int mMaxBursts; // offset 0x32C, size 0x4
    float mTimeTillBurst; // offset 0x330, size 0x4
    class Vector2 mBurstInterval; // offset 0x334, size 0x8
    class Vector2 mBurstPeak; // offset 0x33C, size 0x8
    class Vector2 mBurstLength; // offset 0x344, size 0x8
    int mExplicitParts; // offset 0x34C, size 0x4
};
// Range: 0x8001B418 -> 0x8001B5F8
void * GemRepTemplate::~GemRepTemplate(struct GemRepTemplate * const this /* r30 */) {}

// Range: 0x8001B938 -> 0x8001B98C
class RndMesh * GemRepTemplate::GetTail() {
    // Local variables
    class RndMesh * tail; // r5
}

// Range: 0x8001B98C -> 0x8001BA24
void GemRepTemplate::ReturnTail(struct GemRepTemplate * const this /* r31 */, class RndMesh * tail /* r1+0x8 */) {}

// Range: 0x8001BA24 -> 0x8001BE14
class RndMesh * GemRepTemplate::CreateTail(struct GemRepTemplate * const this /* r25 */) {
    // Local variables
    int num_sections; // r27
    int quads_per_section; // r26
    int s; // r5
    int v; // r6
    int i; // r7
    int f; // r7
    unsigned short vb; // r8
    unsigned short vt; // r9
    int i; // r10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Symbol name;
}

// Range: 0x8001BE14 -> 0x8001BE5C
static unsigned char VertLess() {}

class PlayerTrackConfig {
    // total size: 0x1C
    unsigned char mActive; // offset 0x0, size 0x1
    int mTrackNum; // offset 0x4, size 0x4
    class Symbol mInstrument; // offset 0x8, size 0x4
    int mDifficulty; // offset 0xC, size 0x4
    int mSlot; // offset 0x10, size 0x4
    unsigned char mRemote; // offset 0x14, size 0x1
    int mRealTrack; // offset 0x18, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class PlayerTrackConfig * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class PlayerTrackConfig * _M_start; // offset 0x0, size 0x4
    class PlayerTrackConfig * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class PlayerTrackConfigList {
    // total size: 0x2C
    class vector mTrackDiffs; // offset 0x0, size 0xC
    class vector mTrackNums; // offset 0xC, size 0xC
    class vector mConfigs; // offset 0x18, size 0xC
    int mDefaultDifficulty; // offset 0x24, size 0x4
    unsigned char mNeedsProcessing; // offset 0x28, size 0x1
    unsigned char mProcessed; // offset 0x29, size 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__14RndParticleSys; // size: 0x8, address: 0x8086E1E0
struct {
    // total size: 0x18
} __vt__32ObjPtr<11RndDrawable,9ObjectDir>; // size: 0x18, address: 0x8086E258
struct {
    // total size: 0x8
} __RTTI__32ObjPtr<11RndDrawable,9ObjectDir>; // size: 0x8, address: 0x8086E2A0
struct {
    // total size: 0x18
} __vt__31ObjPtr<10RndEnviron,9ObjectDir>; // size: 0x18, address: 0x8086E2A8
struct {
    // total size: 0x8
} __RTTI__31ObjPtr<10RndEnviron,9ObjectDir>; // size: 0x8, address: 0x8086E2F0
struct {
    // total size: 0x8
} __RTTI__7RndMesh; // size: 0x8, address: 0x8086E360
struct {
    // total size: 0x8
} __RTTI__6RndMat; // size: 0x8, address: 0x8086E388
struct {
    // total size: 0x18
} __vt__36ObjPtrList<Q23Hmx6Object,9ObjectDir>; // size: 0x18, address: 0x8086E428
struct {
    // total size: 0x8
} __RTTI__36ObjPtrList<Q23Hmx6Object,9ObjectDir>; // size: 0x8, address: 0x8086E470
struct {
    // total size: 0x8
} __RTTI__PP8RndGroup; // size: 0x8, address: 0x8086E4C0
struct {
    // total size: 0x8
} __RTTI__PP7RndMesh; // size: 0x8, address: 0x8086E4D8
struct _OKToMemCpy {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__10RndEnviron; // size: 0x8, address: 0x8086E500
struct {
    // total size: 0x8
} __RTTI__PQ27RndMesh4Face; // size: 0x8, address: 0x8086E518

