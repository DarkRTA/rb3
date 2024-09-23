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

void BandList::AdjustTrans(Transform& tf, const UIListElementDrawState& state){
    int showing = state.mShowing;
    UpdateRevealConcealState(state.mDisplay, tf);
    if(mFocusAnim){
        Transform tf40;
        AnimState astate = mAnimStates[showing];
        if(state.mElementState != 0 && (astate == kGoingOut || astate == kOut)){
            StartFocusAnim(showing, kIn);
        }
        else if(state.mElementState == kUIListWidgetActive && (astate == kGoingIn || astate == kIn)){
            StartFocusAnim(showing, kOut);
        }
        UpdateFocusAndPulseAnims(showing, tf40);
        Multiply(tf, tf40, tf);
    }
}

void BandList::UpdateRevealConcealState(int i, Transform& tf){
    switch(mBandListState){
        case kReveal:
            UpdateRevealState(i, tf);
            break;
        case kConceal:
        case kImmediateConceal:
            UpdateConcealState(i, tf);
            break;
        default:
            MILO_FAIL("Unknown state: %d", mBandListState);
            break;
    }
}

void BandList::UpdateRevealState(int i, Transform& tf){
    RevealState rstate = mRevealStates[i];
    if(rstate != kRevealed){
        if(!SupportsRevealConcealAnim()){
            mRevealStates[i] = kRevealed;
        }
        else if(RevealTimedOut()){
            mRevealStates[i] = kRevealed;
        }
        else {
            if(rstate != kRevealing) StartRevealAnim(i, tf);
            RevealAnimPoll(i, tf);
        }
    }
}

void BandList::UpdateConcealState(int i, Transform& tf){
    if(!SupportsRevealConcealAnim()){
        mRevealStates[i] = kConcealed;
        UpdateShowingState();
    }
    else if(mBandListState == kImmediateConceal){
        ForceConcealed(i, tf);
    }
    else if(ConcealTimedOut()){
        ForceConcealed(i, tf);
    }
    else {
        RevealState rstate = mRevealStates[i];
        if(rstate == kConcealed){
            ForceConcealed(i, tf);
        }
        else {
            if(rstate != kConcealing){
                StartConcealAnim(i, tf);
            }
            ConcealAnimPoll(i, tf);
        }
    }
}

void BandList::ForceConcealedStateOnAllEntries(){
    for(std::map<int, RevealState>::iterator it = mRevealStates.begin(); it != mRevealStates.end(); ++it){
        it->second = kConcealed;
    }
}

void BandList::ForceConcealed(int i, Transform& tf){
    mRevealStates[i] = kConcealed;
    UpdateShowingState();
    Transform tf40;
    MakeConcealTransform(GetConcealEndFrame(), tf40);
    Multiply(tf, tf40, tf);
}

void BandList::ForceRevealed(int i, Transform& tf){
    mRevealStates[i] = kRevealed;
    Transform tf40;
    MakeRevealTransform(GetRevealEndFrame(), tf40);
    Multiply(tf, tf40, tf);
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

void BandList::StartRevealAnim(int i, Transform& tf){
    MILO_ASSERT(SupportsRevealConcealAnim(), 0x1EA);
    if(mRevealStates[i] == kConcealed) mRevealStates[i] = kRevealing;
    else ForceRevealed(i, tf);
    int numdisp = NumDisplay();
    int i7 = 0;
    for(int i = 0; i < numdisp; i++){
        RevealState rstate = mRevealStates[i];
        if(rstate == kConcealing || rstate == kRevealed) i7++;
    }
    float f1 = 0;
    if(i7 > 0) f1 = (float)i7 * mRevealEntryDelay + mRevealStartDelay;
    mRevealStartTimes[i] = TheTaskMgr.UISeconds() - f1;
    unk264[i] = false;
}

void BandList::StartConcealAnim(int i, Transform& tf){
    MILO_ASSERT(SupportsRevealConcealAnim(), 0x212);
    if(mRevealStates[i] == kRevealed) mRevealStates[i] = kConcealing;
    else ForceConcealed(i, tf);
    int numdisp = NumDisplay();
    int i7 = 0;
    for(int i = 0; i < numdisp; i++){
        RevealState rstate = mRevealStates[i];
        if(rstate == kConcealed || rstate == kRevealing) i7++;
    }
    float f1 = 0;
    if(i7 > 0) f1 = (float)i7 * mConcealEntryDelay + mConcealStartDelay;
    mRevealStartTimes[i] = TheTaskMgr.UISeconds() - f1;
    unk264[i] = false;
}

void BandList::RevealAnimPoll(int i, Transform& tf){
    MILO_ASSERT(SupportsRevealConcealAnim(), 0x23D);
    if(mRevealStates[i] == kRevealing){
        float f1 = TheTaskMgr.UISeconds() - mRevealStartTimes[i];
        float f3 = mRevealSoundDelay;
        float frame = 0;
        float f4 = mRevealEntryDelay * (float)i + mRevealStartDelay;
        if(f1 > f4) frame = (f1 - f4) * GetRevealFramesPerSecond();
        if(!unk264[i] && (f1 > f4 + f3)){
            if(mRevealSound) mRevealSound->Play(0,0,0);
            unk264[i] = true;
        }
        float curframe = GetCurrentRevealFrame(frame);
        if(IsRevealAnimFinished(curframe)){
            curframe = GetRevealEndFrame();
            mRevealStates[i] = kRevealed;
        }
        Transform tf90;
        MakeRevealTransform(curframe, tf90);
        Multiply(tf, tf90, tf);
    }
}

void BandList::ConcealAnimPoll(int i, Transform& tf){
    MILO_ASSERT(SupportsRevealConcealAnim(), 0x270);
    if(mRevealStates[i] == kConcealing){
        float f1 = TheTaskMgr.UISeconds() - mRevealStartTimes[i];
        int numdisp = NumDisplay();
        numdisp = (numdisp - i) - 1;
        float f3 = mConcealSoundDelay;
        float frame = 0;
        float f4 = mConcealEntryDelay * (float)numdisp + mConcealStartDelay;
        if(f1 > f4) frame = (f1 - f4) * GetConcealFramesPerSecond();
        if(!unk264[i] && (f1 > f4 + f3)){
            if(mConcealSound) mConcealSound->Play(0,0,0);
            unk264[i] = true;
        }
        float curframe = GetCurrentConcealFrame(frame);
        if(IsConcealAnimFinished(curframe)){
            curframe = GetConcealEndFrame();
            mRevealStates[i] = kConcealed;
            UpdateShowingState();
        }
        Transform tf90;
        MakeConcealTransform(curframe, tf90);
        Multiply(tf, tf90, tf);
    }
}

void BandList::StartFocusAnim(int i, BandList::AnimState astate){
    float f8 = TheTaskMgr.UISeconds();
    float f9 = mFocusAnim->StartFrame();
    float f10 = mFocusAnim->EndFrame();
    AnimState curastate = mAnimStates[i];
    if(astate != kOut && astate != kIn){
        MILO_WARN("bad goal parameter to StartAnim()!\n");
    }
    if(astate == kOut && (curastate == kOut || curastate == kGoingOut) || (astate == kIn && (curastate == kGoingIn || curastate == kIn))){
        MILO_WARN("StartAnim() called while already in or going to goal state!\n");
    }
    bool b = false;
    if(curastate == kGoingOut || curastate == kOut) b = true;
    if(b) f10 = f9;
    if(curastate != kOut && curastate != kIn){
        float curframe = mFrames[i];
        float f11 = Abs(f10 - curframe);
        f8 = (f8 - (f11 / mFocusAnim->FramesPerUnit()));
        f10 = curframe;
    }
    mAnimStates[i] = astate == kIn ? kGoingIn : kGoingOut;
    mStartTimes[i] = f8;
    mFrames[i] = f10;
}

void BandList::UpdateFocusAndPulseAnims(int i, Transform& tf){
    float starttime = mStartTimes[i];
    float time = TheTaskMgr.UISeconds();
    float startframe = mFocusAnim->StartFrame();
    float endframe = mFocusAnim->EndFrame();
    float defaulttime = 0;
    time = (time - starttime) * mFocusAnim->FramesPerUnit();
    AnimState astate = mAnimStates[i];
    switch(astate){
        case kGoingIn:
            time = startframe + time;
            if(time >= endframe){
                mAnimStates[i] = kIn;
                time = endframe;
                if(mPulseAnim) StartPulseAnim(i);
            }
            break;
        case kGoingOut:
            time = endframe - time;
            if(time <= startframe){
                mAnimStates[i] = kOut;
                time = startframe;
            }
            break;
        case kIn:
            time = endframe;
            if(mPulseAnim){
                UpdatePulseAnim(i, tf);
                return;
            }
            break;
        case kOut:
            time = startframe;
            break;
        default:
            time = defaulttime;
            break;
    }
    mFrames[i] = time;
    mFocusAnim->MakeTransform(time, tf, true, 1.0f);
}

void BandList::StartPulseAnim(int idx){
    float uisecs = TheTaskMgr.UISeconds();
    float start = mPulseAnim->StartFrame();
    mAnimStates[idx] = kIn;
    mStartTimes[idx] = uisecs;
    mFrames[idx] = start;
}

void BandList::UpdatePulseAnim(int i, Transform& tf){
    if(mAnimStates[i] == kIn){
        mStartTimes[i];
        float f5 = TheTaskMgr.UISeconds();
        float f6 = mPulseAnim->StartFrame();
        float f7 = mPulseAnim->EndFrame();
        float f8 = mPulseAnim->FramesPerUnit();
        f5 = f6 + (f5 - mStartTimes[i]) * f8;
        if(f5 > f7) f5 = ModRange(f6, f7, f5);
        mFrames[i] = f5;
        mPulseAnim->MakeTransform(f5, tf, true, 1.0f);
    }
}

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

bool BandList::IsAnimating(){
    int max = mListState.NumDisplayWithData();
    for(int i = 0; i < max; i++){
        if(mBandListState == kReveal && mRevealStates[i] != kRevealed && !RevealTimedOut()) return true;
        if((mBandListState == kConceal || mBandListState == kImmediateConceal) && mRevealStates[i] != kConcealed && !ConcealTimedOut()) return true;
    }
    return false;
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

void BandList::UpdateShowingState(){
    if(SupportsRevealConcealAnim()){
        if(mBandListState == kReveal) SetShowing(true);
        else {
            for(int i = 0; i < NumDisplay(); i++){
                if(mRevealStates[i] != kConcealed){
                    SetShowing(true);
                    return;
                }
            }
            SetShowing(false);
        }
    }
}

void BandList::DrawShowing(){
    UIList::DrawShowing();
    for(ObjVector<HighlightObject>::iterator it = mHighlightObjects.begin(); it != mHighlightObjects.end(); ++it){
        RndTransformable* obj = it->mTargetObj;
        if(obj){
            obj->SetTransParent(this, false);
            float z = it->mZOffset;
            if(mListDir){
                float space = mListDir->ElementSpacing();
                z = -(space * (float)SelectedDisplay() - z);
            }
            Vector3 v(it->mXOffset, it->mYOffset, z);
            obj->SetLocalPos(v);
        }
    }
}

BEGIN_HANDLERS(BandList)
    HANDLE_ACTION(reveal, Reveal())
    HANDLE_ACTION(conceal, Conceal())
    HANDLE_ACTION(conceal_now, ConcealNow())
    HANDLE_ACTION(is_animating, IsAnimating())
    HANDLE_EXPR(is_revealed, IsRevealed())
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