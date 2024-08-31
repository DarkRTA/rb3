#include "char/CharIKFingers.h"
#include "utl/Symbols.h"

INIT_REVS(CharIKFingers)

CharIKFingers::CharIKFingers() : mHand(0, 0), mForeArm(0, 0), mUpperArm(0, 0), mBlendInFrames(0), mBlendOutFrames(0), mResetHandDest(1), mResetCurHandTrans(1),
    mFingerCurledLength(0.85f), mHandMoveForward(1.0f), mHandPinkyRotation(-0.06f), mHandThumbRotation(0.23f), mHandDestOffset(-0.4f),
    mIsRightHand(1), mMoveHand(0), mIsSetup(0), mOutputTrans(this, 0), mKeyboardRefBone(this, 0) {
    mFingers.resize(5, FingerDesc());
    mCurHandTrans.Zero();
    mDestHandTrans.Zero();
    mHandKeyboardOffset = Vector3(0.3f, -6.0f, 0.4f);
    mtx = Hmx::Matrix3();
}

CharIKFingers::~CharIKFingers(){

}

void CharIKFingers::SetFinger(Vector3 v1, Vector3 v2, CharIKFingers::FingerNum fingerNum){
    MILO_ASSERT(fingerNum >= 0 && fingerNum < kFingerNone, 0x37);
    FingerDesc& finger = mFingers[fingerNum];
    finger.unk8 = v1;
    finger.unk14 = v2;
    finger.unk0 = true;
    finger.unk84 = true;
    Transform tf48;
    Multiply(finger.mFinger01->LocalXfm(), mCurHandTrans, tf48);
    // some xfm math
    mBlendInFrames = 5;
    finger.unk60 = 5;
    finger.unk64 = 0;
}

void CharIKFingers::ReleaseFinger(FingerNum finger){
    MILO_ASSERT(finger >= 0 && finger < kFingerNone, 0x57);
    mFingers[finger].unk0 = false;
    mFingers[finger].unk84 = true;
    mFingers[finger].unk64 = 0;
    mFingers[finger].unk60 = 5;
}

#pragma push
#pragma dont_inline on
void CharIKFingers::SetName(const char* name, ObjectDir* dir){
    Hmx::Object::SetName(name, dir);
    if(dir){
        for(int i = 0; i < 5; i++){
            mFingers[i] = FingerDesc();
        }
        if(mIsRightHand){
            mHand = dir->Find<RndTransformable>("bone_R-hand.mesh", false);
            mForeArm = dir->Find<RndTransformable>("bone_R-foreArm.mesh", false);
            mUpperArm = dir->Find<RndTransformable>("bone_R-upperArm.mesh", false);
            mFingers[kFingerThumb].mFinger01 = dir->Find<RndTransformable>("bone_R-thumb01.mesh", false);
            mFingers[kFingerThumb].mFinger02 = dir->Find<RndTransformable>("bone_R-thumb02.mesh", false);
            mFingers[kFingerThumb].mFinger03 = dir->Find<RndTransformable>("bone_R-thumb03.mesh", false);
            mFingers[kFingerThumb].mFingertip = dir->Find<RndTransformable>("spot_R-thumb_tip.mesh", false);
            mFingers[kFingerIndex].mFinger01 = dir->Find<RndTransformable>("bone_R-index01.mesh", false);
            mFingers[kFingerIndex].mFinger02 = dir->Find<RndTransformable>("bone_R-index02.mesh", false);
            mFingers[kFingerIndex].mFinger03 = dir->Find<RndTransformable>("bone_R-index03.mesh", false);
            mFingers[kFingerIndex].mFingertip = dir->Find<RndTransformable>("spot_R-index_tip.mesh", false);
            mFingers[kFingerMiddle].mFinger01 = dir->Find<RndTransformable>("bone_R-middlefinger01.mesh", false);
            mFingers[kFingerMiddle].mFinger02 = dir->Find<RndTransformable>("bone_R-middlefinger02.mesh", false);
            mFingers[kFingerMiddle].mFinger03 = dir->Find<RndTransformable>("bone_R-middlefinger03.mesh", false);
            mFingers[kFingerMiddle].mFingertip = dir->Find<RndTransformable>("spot_R-middlefinger_tip.mesh", false);
            mFingers[kFingerRing].mFinger01 = dir->Find<RndTransformable>("bone_R-ringfinger01.mesh", false);
            mFingers[kFingerRing].mFinger02 = dir->Find<RndTransformable>("bone_R-ringfinger02.mesh", false);
            mFingers[kFingerRing].mFinger03 = dir->Find<RndTransformable>("bone_R-ringfinger03.mesh", false);
            mFingers[kFingerRing].mFingertip = dir->Find<RndTransformable>("spot_R-ringfinger_tip.mesh", false);
            mFingers[kFingerPinky].mFinger01 = dir->Find<RndTransformable>("bone_R-pinky01.mesh", false);
            mFingers[kFingerPinky].mFinger02 = dir->Find<RndTransformable>("bone_R-pinky02.mesh", false);
            mFingers[kFingerPinky].mFinger03 = dir->Find<RndTransformable>("bone_R-pinky03.mesh", false);
            mFingers[kFingerPinky].mFingertip = dir->Find<RndTransformable>("spot_R-pinky_tip.mesh", false);
            mtx = Hmx::Matrix3(-0.023f, 0.97899997f, 0.201f, -0.228f, 0.191f, -0.95499998f, -0.972, -0.068f, 0.21799999f);
            Normalize(mtx, mtx);
            mIsSetup = true;
        }
        else {
            mHand = dir->Find<RndTransformable>("bone_L-hand.mesh", false);
            mForeArm = dir->Find<RndTransformable>("bone_L-foreArm.mesh", false);
            mUpperArm = dir->Find<RndTransformable>("bone_L-upperArm.mesh", false);
            mFingers[kFingerThumb].mFinger01 = dir->Find<RndTransformable>("bone_L-thumb01.mesh", false);
            mFingers[kFingerThumb].mFinger02 = dir->Find<RndTransformable>("bone_L-thumb02.mesh", false);
            mFingers[kFingerThumb].mFinger03 = dir->Find<RndTransformable>("bone_L-thumb03.mesh", false);
            mFingers[kFingerThumb].mFingertip = dir->Find<RndTransformable>("spot_L-thumb_tip.mesh", false);
            mFingers[kFingerIndex].mFinger01 = dir->Find<RndTransformable>("bone_L-index01.mesh", false);
            mFingers[kFingerIndex].mFinger02 = dir->Find<RndTransformable>("bone_L-index02.mesh", false);
            mFingers[kFingerIndex].mFinger03 = dir->Find<RndTransformable>("bone_L-index03.mesh", false);
            mFingers[kFingerIndex].mFingertip = dir->Find<RndTransformable>("spot_L-index_tip.mesh", false);
            mFingers[kFingerMiddle].mFinger01 = dir->Find<RndTransformable>("bone_L-middlefinger01.mesh", false);
            mFingers[kFingerMiddle].mFinger02 = dir->Find<RndTransformable>("bone_L-middlefinger02.mesh", false);
            mFingers[kFingerMiddle].mFinger03 = dir->Find<RndTransformable>("bone_L-middlefinger03.mesh", false);
            mFingers[kFingerMiddle].mFingertip = dir->Find<RndTransformable>("spot_L-middlefinger_tip.mesh", false);
            mFingers[kFingerRing].mFinger01 = dir->Find<RndTransformable>("bone_L-ringfinger01.mesh", false);
            mFingers[kFingerRing].mFinger02 = dir->Find<RndTransformable>("bone_L-ringfinger02.mesh", false);
            mFingers[kFingerRing].mFinger03 = dir->Find<RndTransformable>("bone_L-ringfinger03.mesh", false);
            mFingers[kFingerRing].mFingertip = dir->Find<RndTransformable>("spot_L-ringfinger_tip.mesh", false);
            mFingers[kFingerPinky].mFinger01 = dir->Find<RndTransformable>("bone_L-pinky01.mesh", false);
            mFingers[kFingerPinky].mFinger02 = dir->Find<RndTransformable>("bone_L-pinky02.mesh", false);
            mFingers[kFingerPinky].mFinger03 = dir->Find<RndTransformable>("bone_L-pinky03.mesh", false);
            mFingers[kFingerPinky].mFingertip = dir->Find<RndTransformable>("spot_L-pinky_tip.mesh", false);
            mtx = Hmx::Matrix3(-0.067f, 0.985f, 0.156f, 0.224f, 0.167f, -0.95999998f, -0.972f, -0.028999999f, -0.23199999f);
            Normalize(mtx, mtx);
            mIsSetup = true;
        }
        for(int i = 0; i < 5; i++){
            FingerDesc cur = mFingers[i];
            if(!cur.mFinger01 || !cur.mFinger02 || !cur.mFinger03 || !cur.mFingertip){
                mIsSetup = false;
                break;
            }
        }
    }
    MeasureLengths();
}
#pragma pop

void CharIKFingers::Poll(){
    Hmx::Matrix3 m;
    Vector3 v;
    mCurHandTrans.Set(m, v);
}

SAVE_OBJ(CharIKFingers, 0x36A)

BEGIN_LOADS(CharIKFingers)
    LOAD_REVS(bs)
    ASSERT_REVS(5, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(CharWeightable)
    if(gRev > 1) bs >> mIsRightHand;
    if(gRev > 2) bs >> mOutputTrans;
    if(gRev > 3) bs >> mKeyboardRefBone;
    if(gRev > 4){
        bs >> mHandKeyboardOffset;
        bs >> mHandThumbRotation;
        bs >> mHandPinkyRotation;
        bs >> mHandMoveForward;
        bs >> mHandDestOffset;
    }
END_LOADS

BEGIN_COPYS(CharIKFingers)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(CharWeightable)
    CREATE_COPY(CharIKFingers)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mIsRightHand)
        COPY_MEMBER(mOutputTrans)
        COPY_MEMBER(mKeyboardRefBone)
        COPY_MEMBER(mHandKeyboardOffset)
        COPY_MEMBER(mHandThumbRotation)
        COPY_MEMBER(mHandPinkyRotation)
        COPY_MEMBER(mHandMoveForward)
        COPY_MEMBER(mHandDestOffset)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharIKFingers)
    HANDLE_SUPERCLASS(CharWeightable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x3AB)
END_HANDLERS

BEGIN_PROPSYNCS(CharIKFingers)
    SYNC_PROP(is_right_hand, mIsRightHand)
    SYNC_PROP(output_trans, mOutputTrans)
    SYNC_PROP(keyboard_ref_bone, mKeyboardRefBone)
    SYNC_PROP(hand_keyboard_offset, mHandKeyboardOffset)
    SYNC_PROP(hand_thumb_rotation, mHandThumbRotation)
    SYNC_PROP(hand_pinky_rotation, mHandPinkyRotation)
    SYNC_PROP(hand_move_forward, mHandMoveForward)
    SYNC_PROP(hand_dest_offset, mHandDestOffset)
    SYNC_SUPERCLASS(CharWeightable)
END_PROPSYNCS