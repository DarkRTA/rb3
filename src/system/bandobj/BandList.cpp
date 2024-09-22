#include "bandobj/BandList.h"
#include "ui/UIListDir.h"
#include "ui/UI.h"
#include "utl/Symbols.h"

INIT_REVS(BandList);
int HighlightObject::sRev;

HighlightObject::HighlightObject(Hmx::Object* o) : mTargetObj(o, 0), mXOffset(0), mYOffset(0), mZOffset(0) {

}

BinStream& operator>>(BinStream& bs, HighlightObject& o){
    o.Load(bs);
    return bs;
}

void HighlightObject::Load(BinStream& bs){
    bs >> mTargetObj;
    bs >> mXOffset;
    bs >> mYOffset;
    bs >> mZOffset;
}

BandList::BandList() : mFocusAnim(this, 0), mPulseAnim(this, 0), mRevealAnim(this, 0), mConcealAnim(this, 0), mRevealSound(this, 0), mConcealSound(this, 0),
    mRevealSoundDelay(0), mConcealSoundDelay(0), mRevealStartDelay(0), mRevealEntryDelay(0), mRevealScale(1.0f), mConcealStartDelay(0), mConcealEntryDelay(0),
    mConcealScale(1.0f), mAutoReveal(0), mBandListState((BandListState)1), mShouldbeRevealedTimeStamp(0), mHighlightObjects(this) {

}

BandList::~BandList(){

}

DECOMP_FORCEACTIVE(BandList, "ObjPtr_p.h", "f.Owner()", "")

void BandList::Init(){
    TheUI->InitResources("BandList");
    Register();
}

SAVE_OBJ(BandList, 0x72);

BEGIN_LOADS(BandList)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void BandList::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0x16, 0);
    mBandListRev = gRev;
    if(mBandListRev <= 0x11) UIList::PreLoadWithRev(bs, mBandListRev);
    else UIList::PreLoad(bs);
}

void BandList::PostLoad(BinStream& bs){
    UIList::PostLoad(bs);
    if(mBandListRev >= 0x12){
        bs >> mFocusAnim;
        bs >> mPulseAnim;
    }
    if(mBandListRev >= 0x13){
        bs >> mRevealAnim;
        bs >> mRevealStartDelay;
        bs >> mRevealEntryDelay;
        bs >> mConcealAnim;
        bs >> mConcealStartDelay;
        bs >> mConcealEntryDelay;
    }
    if(mBandListRev >= 0x14){
        bs >> mRevealScale;
        bs >> mConcealScale;
        bs >> mAutoReveal;
    }
    if(mBandListRev >= 0x15){
        bs >> mRevealSound;
        bs >> mConcealSound;
        bs >> mRevealSoundDelay;
        bs >> mConcealSoundDelay;
    }
    if(mBandListRev >= 0x16){
        HighlightObject::sRev = mBandListRev;
        bs >> mHighlightObjects;
    }
}

BEGIN_COPYS(BandList)
    CREATE_COPY_AS(BandList, list)
    MILO_ASSERT(list, 0xD1);
    COPY_SUPERCLASS(UIList)
    COPY_MEMBER_FROM(list, mFocusAnim)
    COPY_MEMBER_FROM(list, mPulseAnim)
    COPY_MEMBER_FROM(list, mRevealAnim)
    COPY_MEMBER_FROM(list, mRevealStartDelay)
    COPY_MEMBER_FROM(list, mRevealEntryDelay)
    COPY_MEMBER_FROM(list, mConcealAnim)
    COPY_MEMBER_FROM(list, mConcealStartDelay)
    COPY_MEMBER_FROM(list, mConcealEntryDelay)
    COPY_MEMBER_FROM(list, mRevealScale)
    COPY_MEMBER_FROM(list, mConcealScale)
    COPY_MEMBER_FROM(list, mAutoReveal)
    COPY_MEMBER_FROM(list, mRevealSound)
    COPY_MEMBER_FROM(list, mConcealSound)
    COPY_MEMBER_FROM(list, mRevealSoundDelay)
    COPY_MEMBER_FROM(list, mConcealSoundDelay)
    COPY_MEMBER_FROM(list, mHighlightObjects)
END_COPYS

void BandList::Enter(){
    UIList::Enter();
    if(!SupportsRevealConcealAnim() || mAutoReveal){
        Reveal();
        mShouldbeRevealedTimeStamp = 0;
    }
}

void BandList::Exit(){ UIComponent::Exit(); }

void BandList::AdjustTransSelected(Transform& tf){
    UpdateRevealConcealState(Selected() - FirstShowing(), tf);
}

void BandList::UpdateRevealConcealState(int i, Transform& tf){
    if(mBandListState - 1 < 2){
        UpdateConcealState(i, tf);
    }
    else if(mBandListState == 0){
        UpdateRevealState(i, tf);
    }
    else MILO_FAIL("Unknown state: %d", mBandListState);
}

void BandList::ForceConcealedStateOnAllEntries(){
    for(std::map<int, RevealState>::iterator it = mRevealStates.begin(); it != mRevealStates.end(); ++it){
        it->second = kConcealed;
    }
}

bool BandList::RevealTimedOut(){
    MILO_ASSERT(mBandListState == kReveal, 0x1BF);
    if(mShouldbeRevealedTimeStamp == 0) return false;
    else {
        float timePassed = TheTaskMgr.UISeconds() - mShouldbeRevealedTimeStamp;
        MILO_ASSERT(timePassed >= 0, 0x1CA);
        int numdisp = NumDisplay();
        MILO_ASSERT(SupportsRevealConcealAnim(), 0x1CE);
        float numframes = GetRevealNumFrames();
        float fps = GetRevealFramesPerSecond();
        return timePassed >= (numframes / fps) + numdisp * mRevealEntryDelay + mRevealStartDelay;
    }
}

bool BandList::ConcealTimedOut(){
    MILO_ASSERT(mBandListState == kConceal || mBandListState == kImmediateConceal, 0x1D8);
    float timePassed = TheTaskMgr.UISeconds() - mShouldbeRevealedTimeStamp;
    MILO_ASSERT(timePassed >= 0, 0x1DC);
    int numdisp = NumDisplay();
    MILO_ASSERT(SupportsRevealConcealAnim(), 0x1E0);
    float numframes = GetConcealNumFrames();
    float fps = GetConcealFramesPerSecond();
    return (numframes / fps) + numdisp * mConcealEntryDelay + mConcealStartDelay <= timePassed;
}

DECOMP_FORCEACTIVE(BandList, "bad goal parameter to StartAnim()!\n", "StartAnim() called while already in or going to goal state!\n")

void BandList::Reveal(){
    mBandListState = kReveal;
    mShouldbeRevealedTimeStamp = TheTaskMgr.UISeconds();
    UpdateShowingState();
}

void BandList::Conceal(){
    if(mBandListState != kImmediateConceal){
        mBandListState = kConceal;
        mShouldbeRevealedTimeStamp = TheTaskMgr.UISeconds();
    }
}

void BandList::ConcealNow(){
    mBandListState = kImmediateConceal;
    mShouldbeRevealedTimeStamp = TheTaskMgr.UISeconds();
}

float BandList::GetRevealFramesPerSecond() const {
    MILO_ASSERT(SupportsRevealConcealAnim(), 0x355);
    if(!mRevealAnim){
        MILO_ASSERT(mConcealAnim, 0x35A);
        return mRevealScale * mConcealAnim->FramesPerUnit();
    }
    else return mRevealScale * mRevealAnim->FramesPerUnit();
}

float BandList::GetRevealStartFrame() const {
    MILO_ASSERT(SupportsRevealConcealAnim(), 0x363);
    if(!mRevealAnim){
        MILO_ASSERT(mConcealAnim, 0x368);
        return mConcealAnim->EndFrame();
    }
    else return mRevealAnim->StartFrame();
}

float BandList::GetRevealEndFrame() const {
    MILO_ASSERT(SupportsRevealConcealAnim(), 0x371);
    if(!mRevealAnim){
        MILO_ASSERT(mConcealAnim, 0x376);
        return mConcealAnim->StartFrame();
    }
    else return mRevealAnim->EndFrame();
}

float BandList::GetConcealFramesPerSecond() const {
    MILO_ASSERT(SupportsRevealConcealAnim(), 0x37F);
    if(!mConcealAnim){
        MILO_ASSERT(mRevealAnim, 900);
        return mConcealScale * mRevealAnim->FramesPerUnit();
    }
    else return mConcealScale * mConcealAnim->FramesPerUnit();
}

float BandList::GetConcealStartFrame() const {
    MILO_ASSERT(SupportsRevealConcealAnim(), 0x38D);
    if(!mConcealAnim){
        MILO_ASSERT(mRevealAnim, 0x392);
        return mRevealAnim->EndFrame();
    }
    else return mConcealAnim->StartFrame();
}

float BandList::GetConcealEndFrame() const {
    MILO_ASSERT(SupportsRevealConcealAnim(), 0x39B);
    if(!mConcealAnim){
        MILO_ASSERT(mRevealAnim, 0x3A0);
        return mRevealAnim->StartFrame();
    }
    else return mConcealAnim->EndFrame();
}

void BandList::MakeRevealTransform(float f, Transform& tf){
    MILO_ASSERT(SupportsRevealConcealAnim(), 0x3A9);
    if(!mRevealAnim){
        MILO_ASSERT(mConcealAnim, 0x3AE);
        mConcealAnim->MakeTransform(f, tf, true, 1.0f);
    }
    else mRevealAnim->MakeTransform(f, tf, true, 1.0f);
}

void BandList::MakeConcealTransform(float f, Transform& tf){
    MILO_ASSERT(SupportsRevealConcealAnim(), 0x3B9);
    if(!mConcealAnim){
        MILO_ASSERT(mRevealAnim, 0x3BE);
        mRevealAnim->MakeTransform(f, tf, true, 1.0f);
    }
    else mConcealAnim->MakeTransform(f, tf, true, 1.0f);
}

float BandList::GetRevealNumFrames() const {
    MILO_ASSERT(SupportsRevealConcealAnim(), 0x3C9);
    if(!mRevealAnim){
        MILO_ASSERT(mConcealAnim, 0x3CE);
        return mConcealAnim->EndFrame() - mConcealAnim->StartFrame();
    }
    else return mRevealAnim->EndFrame() - mRevealAnim->StartFrame();
}

float BandList::GetConcealNumFrames() const {
    MILO_ASSERT(SupportsRevealConcealAnim(), 0x3D7);
    if(!mConcealAnim){
        MILO_ASSERT(mRevealAnim, 0x3DC);
        return mRevealAnim->EndFrame() - mRevealAnim->StartFrame();
    }
    else return mConcealAnim->EndFrame() - mConcealAnim->StartFrame();
}

float BandList::GetCurrentRevealFrame(float f) const {
    MILO_ASSERT(SupportsRevealConcealAnim(), 0x3E5);
    float frame = GetRevealStartFrame();
    if(!mRevealAnim) frame -= f;
    else frame += f;
    return frame;
}

float BandList::GetCurrentConcealFrame(float f) const {
    MILO_ASSERT(SupportsRevealConcealAnim(), 0x3F4);
    float frame = GetConcealStartFrame();
    if(!mConcealAnim) frame -= f;
    else frame += f;
    return frame;
}

bool BandList::IsRevealAnimFinished(float f) const {
    MILO_ASSERT(SupportsRevealConcealAnim(), 0x403);
    float frame = GetRevealEndFrame();
    if(!mRevealAnim) return f <= frame;
    else return f >= frame;
}

bool BandList::IsConcealAnimFinished(float f) const {
    MILO_ASSERT(SupportsRevealConcealAnim(), 0x411);
    float frame = GetConcealEndFrame();
    if(!mConcealAnim) return f <= frame;
    else return f >= frame;
}

BEGIN_HANDLERS(BandList)
    HANDLE_ACTION(reveal, Reveal())
    HANDLE_ACTION(conceal, Conceal())
    HANDLE_ACTION(conceal_now, ConcealNow())
    HANDLE_ACTION(is_animating, IsAnimating())
    HANDLE_EXPR(is_revealed, !mBandListState && !IsAnimating())
    HANDLE_ACTION(restart_highlight_matanim, mListDir->ListEntered())
    HANDLE_SUPERCLASS(UIList)
    HANDLE_CHECK(0x468)
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(HighlightObject)
    SYNC_PROP(target_object, o.mTargetObj)
    SYNC_PROP(x_offset, o.mXOffset)
    SYNC_PROP(y_offset, o.mYOffset)
    SYNC_PROP(z_offset, o.mZOffset)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(BandList)
    SYNC_PROP(focus_anim, mFocusAnim)
    SYNC_PROP(pulse_anim, mPulseAnim)
    SYNC_PROP(reveal_anim, mRevealAnim)
    SYNC_PROP(reveal_start_delay, mRevealStartDelay)
    SYNC_PROP(reveal_entry_delay, mRevealEntryDelay)
    SYNC_PROP(reveal_scale, mRevealScale)
    SYNC_PROP(reveal_sound, mRevealSound)
    SYNC_PROP(reveal_sound_delay, mRevealSoundDelay)
    SYNC_PROP(conceal_anim, mConcealAnim)
    SYNC_PROP(conceal_start_delay, mConcealStartDelay)
    SYNC_PROP(conceal_entry_delay, mConcealEntryDelay)
    SYNC_PROP(conceal_scale, mConcealScale)
    SYNC_PROP(conceal_sound, mConcealSound)
    SYNC_PROP(conceal_sound_delay, mConcealSoundDelay)
    SYNC_PROP(auto_reveal, mAutoReveal)
    SYNC_PROP(highlight_objects, mHighlightObjects)
    SYNC_SUPERCLASS(UIList)
END_PROPSYNCS