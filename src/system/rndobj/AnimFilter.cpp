#include "rndobj/AnimFilter.h"
#include "math/Rand.h"
#include "math/Utl.h"
#include "obj/Object.h"
#include "rndobj/Anim.h"
#include "rndobj/Utl.h"
#include "utl/Symbols.h"

INIT_REVS(RndAnimFilter);

void RndAnimFilter::SetAnim(RndAnimatable* anim){
    mAnim = anim;
    if(mAnim.operator->()){
        SetRate(mAnim->GetRate());
        mStart = mAnim->StartFrame();
        mEnd = mAnim->EndFrame();
    }
}

void RndAnimFilter::ListAnimChildren(std::list<RndAnimatable*>& theList) const {
    if(mAnim) theList.push_back(mAnim);
}

BEGIN_COPYS(RndAnimFilter)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    CREATE_COPY(RndAnimFilter)
    BEGIN_COPYING_MEMBERS
        if(ty != kCopyFromMax){
            COPY_MEMBER(mScale)
            COPY_MEMBER(mOffset)
            COPY_MEMBER(mStart)
            COPY_MEMBER(mEnd)
            COPY_MEMBER(mType)
            COPY_MEMBER(mAnim)
            COPY_MEMBER(mPeriod)
            COPY_MEMBER(mSnap)
            COPY_MEMBER(mJitter)
        }
    END_COPYING_MEMBERS
END_COPYS

RndAnimFilter::RndAnimFilter() : mAnim(this, 0), mPeriod(0.0f), mStart(0.0f), mEnd(0.0f), mScale(1.0f), mOffset(0.0f), mSnap(0.0f), mJitter(0.0f), mJitterFrame(0.0f), mType(kRange) {

}

SAVE_OBJ(RndAnimFilter, 0x4A)

void RndAnimFilter::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    Hmx::Object::Load(bs);
    RndAnimatable::Load(bs);
    bs >> mAnim >> mScale >> mOffset >> mStart >> mEnd;
    if(gRev != 0){
        bs >> (int&)mType;
        bs >> mPeriod;
    }
    else {
        unsigned char c;
        bs >> c;
        mType = (RndAnimFilter::Type)(c != 0);
    }
    if(gRev > 1){
        bs >> mSnap >> mJitter;
    }
}

float RndAnimFilter::Scale(){
    float ret;
    if(mPeriod){
        ret = (mEnd - mStart) / (mPeriod * FramesPerUnit());
    }
    else {
        if(mEnd >= mStart) ret = mScale;
        else ret = -mScale;
    }
    return ret;
}

void RndAnimFilter::SetFrame(float frame, float blend){
    RndAnimatable::SetFrame(frame, blend);
    if(mAnim){
        float offset = FrameOffset();
        frame = frame * Scale() + offset;
        if(mSnap){
            frame = mSnap * (int)(frame / mSnap + 0.5f);
        }
        if(mJitter && frame != mJitterFrame){
            mJitterFrame = frame;
            frame += RandomFloat(-mJitter, mJitter);
        }
        float start, end;
        if(mEnd >= mStart){
            start = mStart;
            end = mEnd;
        }
        else {
            start = mEnd;
            end = mStart;
        }
        Type ty = mType;
        if(ty == 1){
            frame = ModRange(start, end, frame);
        }
        else if(ty == 0){
            frame = Clamp(start, end, frame);
        }
        else if(ty == 2){
            int iref;
            float limit = Limit(start, end, frame, iref);
            if(iref & 1){
                frame = mEnd - limit - mStart;
            }
        }
        mAnim->SetFrame(frame, blend);
    }
}

float RndAnimFilter::StartFrame(){
    if(!mAnim) return 0.0f;
    else {
        float denom = Scale();
        if(denom == 0.0f) denom = 1.0f;

        return (mStart - FrameOffset()) / denom;
    }
}

float RndAnimFilter::EndFrame(){
    if(!mAnim) return 0.0f;
    else {
        float denom = Scale();
        if(denom == 0.0f) denom = 1.0f;

        float ret = (mEnd - FrameOffset()) / denom;
        if(mType == kShuttle){
            ret *= 2.0f;
        }
        return ret;
    }
}

BEGIN_HANDLERS(RndAnimFilter)
    HANDLE(safe_anims, OnSafeAnims)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xE3)
END_HANDLERS

DataNode RndAnimFilter::OnSafeAnims(DataArray* da){
    ObjectDir* dir = da->Obj<ObjectDir>(2);
    int containsCount = 0;
    for(ObjDirItr<RndAnimatable> it(dir, true); it != 0; ++it){
        if(!AnimContains(it, this)) containsCount++;
    }
    DataArrayPtr ptr(new DataArray(containsCount + 1));
    containsCount = 0;
    for(ObjDirItr<RndAnimatable> it(dir, true); it != 0; ++it){
        if(!AnimContains(it, this)){
            ptr->Node(containsCount++) = DataNode(it);
        }
    }
    ptr->Node(containsCount) = NULL_OBJ;
    return ptr;
}

BEGIN_PROPSYNCS(RndAnimFilter)
    SYNC_PROP_SET(anim, mAnim, SetAnim(_val.Obj<RndAnimatable>()))
    SYNC_PROP_SET(scale, mScale, mScale = std::fabs(_val.Float()))
    SYNC_PROP(offset, mOffset)
    SYNC_PROP(period, mPeriod)
    SYNC_PROP(start, mStart)
    SYNC_PROP(end, mEnd)
    SYNC_PROP(snap, mSnap)
    SYNC_PROP_MODIFY(jitter, mJitter, mJitterFrame = 0.0f)
    SYNC_PROP(type, (int&)mType)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS
