/*
    Compile unit: C:\rockband2\system\src\char\Char.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8030974C -> 0x8030B3F0
*/
class Symbol name; // size: 0x4, address: 0x80A507C4
class Symbol name; // size: 0x4, address: 0x80A507CC
class Symbol name; // size: 0x4, address: 0x80A507D4
class Symbol name; // size: 0x4, address: 0x80A507DC
class Symbol name; // size: 0x4, address: 0x80A507E4
class Symbol name; // size: 0x4, address: 0x80A507EC
class Symbol name; // size: 0x4, address: 0x80A507F4
class Symbol name; // size: 0x4, address: 0x80A507FC
class Symbol name; // size: 0x4, address: 0x80A50804
class Symbol name; // size: 0x4, address: 0x80A5080C
class Symbol name; // size: 0x4, address: 0x80A50814
class Symbol name; // size: 0x4, address: 0x80A5081C
class Symbol name; // size: 0x4, address: 0x80A50824
class Symbol name; // size: 0x4, address: 0x80A5082C
class Symbol name; // size: 0x4, address: 0x80A50834
class Symbol name; // size: 0x4, address: 0x80A5083C
class Symbol name; // size: 0x4, address: 0x80A50844
class Symbol name; // size: 0x4, address: 0x80A5084C
class Symbol name; // size: 0x4, address: 0x80A50854
class Symbol name; // size: 0x4, address: 0x80A5085C
class Symbol name; // size: 0x4, address: 0x80A50864
class Symbol name; // size: 0x4, address: 0x80A5086C
class Symbol name; // size: 0x4, address: 0x80A50874
class Symbol name; // size: 0x4, address: 0x80A5087C
class Symbol name; // size: 0x4, address: 0x80A50884
class Symbol name; // size: 0x4, address: 0x80A5088C
class Symbol name; // size: 0x4, address: 0x80A50894
class Symbol name; // size: 0x4, address: 0x80A5089C
class Symbol name; // size: 0x4, address: 0x80A508A4
class Symbol name; // size: 0x4, address: 0x80A508AC
class Symbol name; // size: 0x4, address: 0x80A508B4
class Symbol name; // size: 0x4, address: 0x80A508BC
class Symbol name; // size: 0x4, address: 0x80A508C4
class Symbol name; // size: 0x4, address: 0x80A508CC
class Symbol name; // size: 0x4, address: 0x80A508D4
class Symbol name; // size: 0x4, address: 0x80A508DC
class Symbol name; // size: 0x4, address: 0x80A508E4
class Symbol once; // size: 0x4, address: 0x80A508EC
class CharDebug : public Callback {
    // total size: 0x30
    class ObjPtrList mObjects; // offset 0x4, size 0x14
    class ObjPtrList mOnce; // offset 0x18, size 0x14
    class RndOverlay * mOverlay; // offset 0x2C, size 0x4
};
static class CharDebug TheCharDebug; // size: 0x30, address: 0x8097DDC0
// Range: 0x8030974C -> 0x8030A1F8
class DataNode CharDebug::OnSetObjects(class DataArray * msg /* r28 */) {
    // References
    // -> class Symbol once;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class CharDebug TheCharDebug;
}

// Range: 0x8030A1F8 -> 0x8030A364
void CharDebugOnce(class Object * o /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class CharDebug TheCharDebug;
}

// Range: 0x8030A364 -> 0x8030ACE4
void CharInit() {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std17_List_node<PFv_v>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> static class CharDebug TheCharDebug;
}

class CharBoneOffset : public CharPollable {
    // total size: 0x60
protected:
    class ObjPtr mDest; // offset 0x8, size 0xC
    class Vector3 mOffset; // offset 0x20, size 0x10
};
class BoneEntry {
    // total size: 0x10
public:
    class ObjOwnerPtr bone; // offset 0x0, size 0xC
    float weight; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class BoneEntry * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class BoneEntry * _M_start; // offset 0x0, size 0x4
    class BoneEntry * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class CharBlendBone : public CharPollable {
    // total size: 0x54
protected:
    class ObjPtr mDest; // offset 0x8, size 0xC
    class ObjVector mBones; // offset 0x14, size 0x10
    unsigned char mPos; // offset 0x24, size 0x1
};
class CharBonesBlender : public CharPollable, public CharBonesAlloc {
    // total size: 0x98
protected:
    class ObjPtr mDest; // offset 0x60, size 0xC
};
class CharClipFilter : public virtual Object {
    // total size: 0x34
public:
    void * __vptr$; // offset 0x4, size 0x4
};
struct Shape {
    // total size: 0x8
    float offset; // offset 0x0, size 0x4
    float radius; // offset 0x4, size 0x4
};
class CharCuff : public RndTransformable {
    // total size: 0x140
protected:
    struct Shape mShape[3]; // offset 0xB8, size 0x18
    float mOuterRadius; // offset 0xD0, size 0x4
    unsigned char mOpenEnd; // offset 0xD4, size 0x1
    class ObjPtrList mIgnore; // offset 0xD8, size 0x14
    class ObjPtr mBone; // offset 0xEC, size 0xC
    float mEccentricity; // offset 0xF8, size 0x4
    class Symbol mCategory; // offset 0xFC, size 0x4
};
class CharDriverMidi : public CharDriver {
    // total size: 0xB0
protected:
    class ObjPtr mInactiveClip; // offset 0x70, size 0xC
    unsigned char mActive; // offset 0x7C, size 0x1
    class Symbol mParser; // offset 0x80, size 0x4
};
class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class CharLookAt * mPtr; // offset 0x8, size 0x4
};
struct EyeDesc {
    // total size: 0x24
    class ObjOwnerPtr eye; // offset 0x0, size 0xC
    class ObjPtr upperLid; // offset 0xC, size 0xC
    class ObjPtr lowerLid; // offset 0x18, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct EyeDesc * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct EyeDesc * _M_start; // offset 0x0, size 0x4
    struct EyeDesc * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
struct Interest {
    // total size: 0x10
    float radius; // offset 0x0, size 0x4
    class ObjOwnerPtr trans; // offset 0x4, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Interest * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Interest * _M_start; // offset 0x0, size 0x4
    struct Interest * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class CharFaceServo * mPtr; // offset 0x8, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class CharWeightSetter * mPtr; // offset 0x8, size 0x4
};
class CharEyes : public RndHighlightable, public CharWeightable, public CharPollable {
    // total size: 0xD0
protected:
    class ObjVector mEyes; // offset 0x28, size 0x10
    class ObjVector mInterests; // offset 0x38, size 0x10
    class ObjPtr mFaceServo; // offset 0x48, size 0xC
    class ObjPtr mCamWeight; // offset 0x54, size 0xC
    class Vector3 mTarget; // offset 0x60, size 0x10
    class Vector3 mLastFacing; // offset 0x70, size 0x10
    float mLastCang; // offset 0x80, size 0x4
    float mLastLook; // offset 0x84, size 0x4
    float mMaxEyeCang; // offset 0x88, size 0x4
    float mAvDelta; // offset 0x8C, size 0x4
    float mLastBlinkWeight; // offset 0x90, size 0x4
    unsigned char mBlinkDetect; // offset 0x94, size 0x1
};
class CharFaceServo : public CharPollable, public CharBonesMeshes {
    // total size: 0xCC
protected:
    class ObjPtr mClips; // offset 0x74, size 0xC
    class ObjPtr mBaseClip; // offset 0x80, size 0xC
    class ObjPtr mBlinkClip; // offset 0x8C, size 0xC
    float mBlinkWeight; // offset 0x98, size 0x4
    float mRefWeight; // offset 0x9C, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class CharIKFoot * mPtr; // offset 0x8, size 0x4
};
class CharIKFoot : public CharIKHand {
    // total size: 0xE0
protected:
    class ObjPtr mOther; // offset 0x80, size 0xC
    class ObjPtr mToe; // offset 0x8C, size 0xC
    float mStep; // offset 0x98, size 0x4
    class Vector3 mBase; // offset 0xA0, size 0x10
    class RndTransformable * mDummy; // offset 0xB0, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class CharWeightable * mPtr; // offset 0x8, size 0x4
};
class CharIKMidi : public RndHighlightable, public CharPollable {
    // total size: 0x110
protected:
    class ObjPtr mBone; // offset 0x10, size 0xC
    class ObjPtr mCurSpot; // offset 0x1C, size 0xC
    class ObjPtr mNewSpot; // offset 0x28, size 0xC
    class Transform mLocalXfm; // offset 0x40, size 0x40
    class Transform mOldLocalXfm; // offset 0x80, size 0x40
    float mFrac; // offset 0xC0, size 0x4
    float mFracPerBeat; // offset 0xC4, size 0x4
    unsigned char mSpotChanged; // offset 0xC8, size 0x1
    class ObjPtr mAnimBlender; // offset 0xCC, size 0xC
    float mMaxAnimBlend; // offset 0xD8, size 0x4
    float mAnimFracPerBeat; // offset 0xDC, size 0x4
    float mAnimFrac; // offset 0xE0, size 0x4
};
class CharIKRod : public CharPollable {
    // total size: 0xB0
protected:
    class ObjPtr mLeftEnd; // offset 0x8, size 0xC
    class ObjPtr mRightEnd; // offset 0x14, size 0xC
    float mDestPos; // offset 0x20, size 0x4
    class ObjPtr mSideAxis; // offset 0x24, size 0xC
    unsigned char mVertical; // offset 0x30, size 0x1
    class ObjPtr mDest; // offset 0x34, size 0xC
    class Transform mXfm; // offset 0x40, size 0x40
};
class CharLipSync : public Object {
    // total size: 0x44
protected:
    class vector mVisemes; // offset 0x28, size 0xC
    int mFrames; // offset 0x34, size 0x4
    class vector mData; // offset 0x38, size 0xC
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class CharLipSyncDriver * mPtr; // offset 0x8, size 0x4
};
struct Weight {
    // total size: 0x10
    class CharClip * clip; // offset 0x0, size 0x4
    float last; // offset 0x4, size 0x4
    float next; // offset 0x8, size 0x4
    float current; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Weight * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Weight * _M_start; // offset 0x0, size 0x4
    struct Weight * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class PlayBack {
    // total size: 0x20
protected:
    class vector mWeights; // offset 0x0, size 0xC
    class CharLipSync * mLipSync; // offset 0xC, size 0x4
    class CharClipSet * mClips; // offset 0x10, size 0x4
    int mIndex; // offset 0x14, size 0x4
    int mOldIndex; // offset 0x18, size 0x4
    int mFrame; // offset 0x1C, size 0x4
};
class CharLipSyncDriver : public CharWeightable, public CharPollable {
    // total size: 0xA0
protected:
    class ObjDirPtr mSong; // offset 0x20, size 0xC
    class String mPart; // offset 0x2C, size 0xC
    class ObjPtr mClips; // offset 0x38, size 0xC
    class ObjPtr mBlinkClip; // offset 0x44, size 0xC
    class ObjPtr mSongOwner; // offset 0x50, size 0xC
    float mSongOffset; // offset 0x5C, size 0x4
    unsigned char mLoop; // offset 0x60, size 0x1
    class PlayBack * mSongPlayer; // offset 0x64, size 0x4
    class ObjPtr mBones; // offset 0x68, size 0xC
};
class CharLookAt : public RndHighlightable, public CharWeightable, public CharPollable {
    // total size: 0xE0
protected:
    class ObjPtr mSource; // offset 0x28, size 0xC
    class ObjPtr mPivot; // offset 0x34, size 0xC
    class ObjPtr mDest; // offset 0x40, size 0xC
    float mHalfTime; // offset 0x4C, size 0x4
    float mMinYaw; // offset 0x50, size 0x4
    float mMaxYaw; // offset 0x54, size 0x4
    float mMinPitch; // offset 0x58, size 0x4
    float mMaxPitch; // offset 0x5C, size 0x4
    float mMinWeightYaw; // offset 0x60, size 0x4
    float mMaxWeightYaw; // offset 0x64, size 0x4
    float mWeightYawSpeed; // offset 0x68, size 0x4
    class Vector3 mLastLocal; // offset 0x70, size 0x10
    float mLastYawWeight; // offset 0x80, size 0x4
    class Box mBounds; // offset 0x90, size 0x20
    unsigned char mShowRange; // offset 0xB0, size 0x1
    unsigned char mAllowRoll; // offset 0xB1, size 0x1
    unsigned char mClamped; // offset 0xB2, size 0x1
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class CharServoBone * mPtr; // offset 0x8, size 0x4
};
struct MirrorOp {
    // total size: 0x8
    void * ptr; // offset 0x0, size 0x4
    class Symbol op; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct MirrorOp * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct MirrorOp * _M_start; // offset 0x0, size 0x4
    struct MirrorOp * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class CharMirror : public CharWeightable, public CharPollable {
    // total size: 0xF4
protected:
    class ObjPtr mServo; // offset 0x20, size 0xC
    class ObjPtr mMirrorServo; // offset 0x2C, size 0xC
    class CharBonesAlloc mBones; // offset 0x38, size 0x84
    class vector mOps; // offset 0xBC, size 0xC
};
class CharNeckTwist : public CharPollable {
    // total size: 0x4C
protected:
    class ObjPtr mTwist; // offset 0x8, size 0xC
    class ObjPtr mHead; // offset 0x14, size 0xC
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
class CharPollGroup : public CharPollable {
    // total size: 0x48
protected:
    class ObjPtrList mPolls; // offset 0x8, size 0x14
};
class CharPosConstraint : public CharPollable {
    // total size: 0x80
protected:
    class ObjPtr mSrc; // offset 0x8, size 0xC
    class ObjPtrList mTargets; // offset 0x14, size 0x14
    class Box mBox; // offset 0x30, size 0x20
};
class CharTransCopy : public CharPollable {
    // total size: 0x4C
protected:
    class ObjPtr mSrc; // offset 0x8, size 0xC
    class ObjPtr mDest; // offset 0x14, size 0xC
};
class CharUpperTwist : public CharPollable {
    // total size: 0x58
protected:
    class ObjPtr mTwist1; // offset 0x8, size 0xC
    class ObjPtr mTwist2; // offset 0x14, size 0xC
    class ObjPtr mUpperArm; // offset 0x20, size 0xC
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class CharDriver * mPtr; // offset 0x8, size 0x4
};
class CharWeightSetter : public CharWeightable, public CharPollable {
    // total size: 0x84
protected:
    class ObjPtr mBase; // offset 0x20, size 0xC
    class ObjPtr mDriver; // offset 0x2C, size 0xC
    class ObjPtr mMinWeightable; // offset 0x38, size 0xC
    int mFlags; // offset 0x44, size 0x4
    float mOffset; // offset 0x48, size 0x4
    float mScale; // offset 0x4C, size 0x4
    float mBaseWeight; // offset 0x50, size 0x4
    float mBeatPerWeight; // offset 0x54, size 0x4
};
class CharGuitarString : public CharPollable {
    // total size: 0x68
protected:
    unsigned char mOpen; // offset 0x8, size 0x1
    class ObjPtr mNut; // offset 0xC, size 0xC
    class ObjPtr mBridge; // offset 0x18, size 0xC
    class ObjPtr mBend; // offset 0x24, size 0xC
    class ObjPtr mTarget; // offset 0x30, size 0xC
};
struct Report {
    // total size: 0x160
    char name[32]; // offset 0x0, size 0x20
    char charPath[256]; // offset 0x20, size 0x100
    char clip[32]; // offset 0x120, size 0x20
    class Waypoint * waypoint; // offset 0x140, size 0x4
    class Symbol position; // offset 0x144, size 0x4
    class Vector3 pos; // offset 0x150, size 0x10
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Report * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Report * _M_start; // offset 0x0, size 0x4
    struct Report * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ClipCollide : public Object {
    // total size: 0x80
protected:
    class vector mReports; // offset 0x28, size 0xC
    class RndGraph * mGraph; // offset 0x34, size 0x4
    class ObjPtr mChar; // offset 0x38, size 0xC
    class String mCharPath; // offset 0x44, size 0xC
    class ObjPtr mWaypoint; // offset 0x50, size 0xC
    class Symbol mPosition; // offset 0x5C, size 0x4
    class ObjPtr mClip; // offset 0x60, size 0xC
    class String mReportString; // offset 0x6C, size 0xC
    unsigned char mWorldLines; // offset 0x78, size 0x1
    unsigned char mMoveCamera; // offset 0x79, size 0x1
    class Symbol mMode; // offset 0x7C, size 0x4
};
// Range: 0x8030ACE4 -> 0x8030AD18
void CharTerminate() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8030AD18 -> 0x8030B08C
float CharDebug::UpdateOverlay(class CharDebug * const this /* r29 */, class RndOverlay * o /* r30 */, float y /* f31 */) {
    // Local variables
    class iterator it; // r1+0x2C
    class CharDriver * d; // r0
    class CharIKMidi * m; // r0
    class RndHighlightable * h; // r0
    class iterator it; // r1+0x28
    class CharDriver * d; // r0
    class CharIKMidi * m; // r0
    class RndHighlightable * h; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__16RndHighlightable;
    // -> struct [anonymous] __RTTI__10CharIKMidi;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10CharDriver;
}

// Range: 0x8030B08C -> 0x8030B394
void * CharDebug::~CharDebug(class CharDebug * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<Q23Hmx6Object,9ObjectDir>;
}

struct {
    // total size: 0x10
} __vt__9CharDebug; // size: 0x10, address: 0x808CE730
struct {
    // total size: 0x8
} __RTTI__9CharDebug; // size: 0x8, address: 0x808CE758
struct {
    // total size: 0x8
} __RTTI__10CharIKMidi; // size: 0x8, address: 0x808CE798
// Range: 0x8030B394 -> 0x8030B3F0
static void __sinit_\Char_cpp() {
    // References
    // -> struct [anonymous] __vt__36ObjPtrList<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__9CharDebug;
    // -> static class CharDebug TheCharDebug;
}


