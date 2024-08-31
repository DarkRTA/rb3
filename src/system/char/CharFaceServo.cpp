#include "char/CharFaceServo.h"
#include "char/CharClip.h"
#include "char/CharBoneDir.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

INIT_REVS(CharFaceServo)

CharFaceServo::CharFaceServo() : mClips(this, 0), mBaseClip(this, 0), mBlinkClipLeft(this, 0), mBlinkClipLeft2(this, 0), mBlinkClipRight(this, 0), mBlinkClipRight2(this, 0),
    mBlinkWeightLeft(0.0f), mBlinkWeightRight(0.0f), mNeedScaleDown(0), mProceduralBlinkWeight(0.0f), mAppliedProceduralBlink(0) {

}

CharFaceServo::~CharFaceServo(){

}

void CharFaceServo::Enter(){
    RndPollable::Enter();
    mNeedScaleDown = true;
    mProceduralBlinkWeight = 0.0f;
}

void CharFaceServo::TryScaleDown(){
    if(mNeedScaleDown){
        mNeedScaleDown = false;
        if(mBaseClip && !mClipType.Null()){
            mBaseClip->ScaleDown(*this, 0.0f);
        }
        mBlinkWeightRight = 0.0f;
        mBlinkWeightLeft = 0.0f;
    }
}

void CharFaceServo::SetClips(ObjectDir* dir){
    mClips = dir;
    if(mClips){
        mBaseClip = mClips->Find<CharClip>("Base", false);
        mBlinkClipLeft = mClips->Find<CharClip>(mBlinkClipLeftName.mStr, false);
        mBlinkClipLeft2 = mClips->Find<CharClip>(mBlinkClipLeftName2.mStr, false);
        mBlinkClipRight = mClips->Find<CharClip>(mBlinkClipRightName.mStr, false);
        mBlinkClipRight2 = mClips->Find<CharClip>(mBlinkClipRightName2.mStr, false);
    }
}

void CharFaceServo::SetClipType(Symbol s){
    if(s != mClipType){
        mClipType = s;
        ClearBones();
        CharBoneDir::StuffBones(*this, mClipType);
        mNeedScaleDown = true;
    }
}

void CharFaceServo::ReallocateInternal(){ CharBonesMeshes::ReallocateInternal(); }

void CharFaceServo::Poll(){
    START_AUTO_TIMER("faceservo");
    if(mBaseClip){
        TryScaleDown();
        ScaleAddIdentity();
        mBaseClip->RotateBy(*this, mBaseClip->StartBeat());
        PoseMeshes();
    }
    mNeedScaleDown = true;
    mAppliedProceduralBlink = false;
}

// fn_804D35EC
void CharFaceServo::ScaleAdd(CharClip* clip, float weight, float f2, float f3){
    if(!clip->mRelative){
        MILO_NOTIFY_ONCE("%s playing non-relative clip %s, cut it out!", PathName(this), PathName(clip));
    }
    else {
        MILO_ASSERT(weight >= 0, 0x88);
        TryScaleDown();
        if(clip == mBlinkClipLeft || clip == mBlinkClipLeft2){
            mBlinkWeightLeft += weight;
            mBlinkWeightLeft = Clamp(0.0f, 1.0f, mBlinkWeightLeft);
        }
        else if(clip == mBlinkClipRight || clip == mBlinkClipRight2){
            mBlinkWeightRight += weight;
            mBlinkWeightRight = Clamp(0.0f, 1.0f, mBlinkWeightRight);
        }
        clip->ScaleAdd(*this, weight, f2, f3);
    }
}

float CharFaceServo::BlinkWeightLeft() const { return mBlinkWeightLeft; }

void CharFaceServo::ApplyProceduralWeights(){
    if(mProceduralBlinkWeight > 0.0f && !mAppliedProceduralBlink){
        TryScaleDown();
        if(mBlinkClipLeft){
            mBlinkClipLeft->ScaleAdd(*this, Interp(0.0f, 1.0f - mBlinkWeightLeft, mProceduralBlinkWeight), mBlinkClipLeft->StartBeat(), 0.0f);
        }
        if(mBlinkClipRight && mBlinkClipRight != mBlinkClipLeft){
            mBlinkClipRight->ScaleAdd(*this, Interp(0.0f, 1.0f - mBlinkWeightRight, mProceduralBlinkWeight), mBlinkClipRight->StartBeat(), 0.0f);
        }
        mAppliedProceduralBlink = true;
    }
}

void CharFaceServo::PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>& change){
    StuffMeshes(change);
}

SAVE_OBJ(CharFaceServo, 0xCE);

// fn_804D38A4
BEGIN_LOADS(CharFaceServo)
    LOAD_REVS(bs)
    ASSERT_REVS(4, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    ObjPtr<ObjectDir, ObjectDir> oDirPtr(this, 0);
    bs >> oDirPtr;
    Symbol sym;
    if(gRev > 3) bs >> sym;
    else if(oDirPtr){
        sym = oDirPtr->Type();
        if(sym.Null()){
            ObjDirItr<CharClip> it(oDirPtr, true);
            if(it != 0) sym = it->Type();
        }
    }
    if(gRev != 0) bs >> mBlinkClipLeftName;
    if(gRev > 1) bs >> mBlinkClipRightName;
    if(gRev > 2){
        bs >> mBlinkClipLeftName2;
        bs >> mBlinkClipRightName2;
    }
    SetClips(oDirPtr);
    SetClipType(sym);
END_LOADS

BEGIN_COPYS(CharFaceServo)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharFaceServo)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mBlinkWeightLeft)
        COPY_MEMBER(mBlinkWeightRight)
        COPY_MEMBER(mBlinkClipLeftName)
        COPY_MEMBER(mBlinkClipRightName)
        COPY_MEMBER(mBlinkClipLeftName2)
        COPY_MEMBER(mBlinkClipRightName2)
        SetClips(c->mClips);
        SetClipType(c->mClipType);
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharFaceServo)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x119)
END_HANDLERS

BEGIN_PROPSYNCS(CharFaceServo)
    SYNC_PROP_SET(clips, mClips, SetClips(_val.Obj<ObjectDir>(0)))
    SYNC_PROP_SET(clip_type, mClipType, SetClipType(_val.Sym(0)))
    SYNC_PROP(blink_clip_left, mBlinkClipLeftName)
    SYNC_PROP(blink_clip_left2, mBlinkClipLeftName2)
    SYNC_PROP(blink_clip_right, mBlinkClipRightName)
    SYNC_PROP(blink_clip_right2, mBlinkClipRightName2)
    SYNC_SUPERCLASS(CharBonesMeshes)
END_PROPSYNCS