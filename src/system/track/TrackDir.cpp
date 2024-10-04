#include "track/TrackDir.h"
#include "obj/ObjMacros.h"
#include "ui/PanelDir.h"
#include "utl/Loader.h"
#include "rndobj/Group.h"
#include "track/TrackTest.h"
#include "track/TrackWidget.h"
#include "obj/ObjVersion.h"
#include "utl/Symbols.h"

INIT_REVS(TrackDir)

TrackDir::TrackDir() : mRunning(!TheLoadMgr.EditMode()), mDrawGroup(this, 0), mAnimGroup(this, 0), mYPerSecond(10.0f), 
    mTopY(10.0f), mBottomY(-3.0f), mWarnOnResort(false), mShowingWhenEnabled(this, 0), mStationaryBack(this, 0), mKeyShiftStationaryBack(this, 0), 
    mStationaryBackAfterKeyShift(this, 0), mMovingBack(this, 0), mKeyShiftMovingBack(this, 0), mKeyShiftStationaryMiddle(this, 0),
    mStationaryMiddle(this, 0), mMovingFront(this, 0), mKeyShiftMovingFront(this, 0), mKeyShiftStationaryFront(this, 0),
    mStationaryFront(this, 0), mAlwaysShowing(this, 0), mRotatorCam(this, 0), mTrack(this, 0), 
    mTrackGems(this, 0), unk368(1.0f)
#ifdef MILO_DEBUG
        , mTest(new TrackTest(this))
#endif
{
    mActiveWidgets.reserve(0x32);
    unk2d8.Reset();
    unk308.Reset();
    unk338.Reset();
}

TrackDir::~TrackDir(){
#ifdef MILO_DEBUG
    delete mTest;
#endif
}

// fn_8053E7D4
void TrackDir::SyncObjects() {
    PanelDir::SyncObjects();
    for(ObjDirItr<TrackWidget> it(this, true); it != 0; ++it){
        it->Init();
        it->Clear();
    }
    if(!mTrack) mTrack = Find<RndEnviron>("track.env", false);
    if(!mTrackGems) mTrackGems = Find<RndEnviron>("track_gems.env", false);
    if(!mShowingWhenEnabled) mShowingWhenEnabled = Find<RndGroup>("showing_when_enabled.grp", false);
    if(!mStationaryBack) mStationaryBack = Find<RndGroup>("stationary_back.grp", false);
    if(!mKeyShiftStationaryBack) mKeyShiftStationaryBack = Find<RndGroup>("key_shift_stationary_back.grp", false);
    if(!mStationaryBackAfterKeyShift) mStationaryBackAfterKeyShift = Find<RndGroup>("stationary_back_after_key_shift.grp", false);
    if(!mMovingBack) mMovingBack = Find<RndGroup>("moving_back.grp", false);
    if(!mKeyShiftMovingBack) mKeyShiftMovingBack = Find<RndGroup>("key_shift_moving_back.grp", false);
    if(!mKeyShiftStationaryMiddle) mKeyShiftStationaryMiddle = Find<RndGroup>("key_shift_stationary_middle.grp", false);
    if(!mStationaryMiddle) mStationaryMiddle = Find<RndGroup>("stationary_middle.grp", false);
    if(!mMovingFront) mMovingFront = Find<RndGroup>("moving_front.grp", false);
    if(!mKeyShiftMovingFront) mKeyShiftMovingFront = Find<RndGroup>("key_shift_moving_front.grp", false);
    if(!mKeyShiftStationaryFront) mKeyShiftStationaryFront = Find<RndGroup>("key_shift_stationary_front.grp", false);
    if(!mStationaryFront) mStationaryFront = Find<RndGroup>("stationary_front.grp", false);
    if(!mAlwaysShowing) mAlwaysShowing = Find<RndGroup>("always_showing.grp", false);
}

void TrackDir::SetupKeyShifting(RndDir* rnddir){
    mRotatorCam = rnddir->Find<RndTransformable>("rotator_cam.trans", true);
    unk2d8.Reset();
    Vector3 v38(1.0f / rnddir->mOrder, 1.0f, 1.0f);
    Scale(unk2d8.m, v38, unk2d8.m);
    unk308.Reset();
    unk308.v = mRotatorCam->WorldXfm().v;
    unk338.Reset();
    Invert(unk338, unk338);
}

void TrackDir::ResetKeyShifting(){
    mRotatorCam = 0;
    unk2d8.Reset();
    unk308.Reset();
    unk338.Reset();
}

BEGIN_COPYS(TrackDir)
    COPY_SUPERCLASS(PanelDir)
    CREATE_COPY(TrackDir)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mDrawGroup)
        COPY_MEMBER(mAnimGroup)
        COPY_MEMBER(mYPerSecond)
        COPY_MEMBER(mTopY)
        COPY_MEMBER(mBottomY)
        COPY_MEMBER(mSlots)
        COPY_MEMBER(mWarnOnResort)
#ifdef MILO_DEBUG
        COPY_MEMBER(mTest->mWidget)
        COPY_MEMBER(mTest->mSlot)
#endif
    END_COPYING_MEMBERS
END_COPYS

SAVE_OBJ(TrackDir, 0x90)

BEGIN_LOADS(TrackDir)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void TrackDir::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(6, 0);
    PushRev(packRevs(gAltRev, gRev), this);
    PanelDir::PreLoad(bs);
}

void TrackDir::PostLoad(BinStream& bs){
    PanelDir::PostLoad(bs);
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    if(!IsProxy()){
        if(gRev != 0){
            bs >> mDrawGroup;
            if(gRev > 1) bs >> mAnimGroup;
            bs >> mYPerSecond >> mTopY >> mBottomY;
        }
        if(gRev > 2){
            if(gRev > 5) bs >> mSlots;
            else {
                unsigned int num = 0;
                bs >> num;
                mSlots.resize(num, Transform());
                for(int i = 0; i < num; i++){
                    mSlots[i].Reset();
                    bs >> mSlots[i].v.x >> mSlots[i].v.z;
                }
            }
        }
        if(gRev > 4) bs >> mWarnOnResort;
#ifdef MILO_DEBUG
        if(gRev > 3){
            bs >> mTest->mWidget >> mTest->mSlot;
        }
#endif
    }
    for(ObjDirItr<TrackWidget> it(this, true); it != 0; ++it){
        it->SetTrackDir(this);
    }
}

void TrackDir::DrawShowing(){
    MILO_ASSERT(TheLoadMgr.EditMode(), 0x109);
}

void TrackDir::Poll(){
    bool b = false;
    if(IsActiveInSession() || mShowingWhenEnabled->Showing()){
        b = true;
    }
    if(b){
        RndDir::Poll();
        float secs = mYPerSecond * TheTaskMgr.Seconds(TaskMgr::b);
        if(mAnimGroup && mRunning){
            mAnimGroup->SetFrame(secs, 1.0f);
        }
        PollActiveWidgets();
    }
}

void TrackDir::PollActiveWidgets(){
    int count = 0;
    for(int i = 0; i < mActiveWidgets.size(); i++){
        TrackWidget* widget = mActiveWidgets[i];
        MILO_ASSERT(widget, 0x1B3);
        if(!widget->Empty()) widget->Poll();
        if(widget->Empty()){
            widget->SetInactive();
            count++;
            mActiveWidgets[i] = 0;
        }
        else {
            if(count > 0){
                mActiveWidgets[i - count] = widget;
                mActiveWidgets[i] = 0;
            }
        }
    }
    if(count > 0){
        mActiveWidgets.resize(mActiveWidgets.size() - count);
    }
}

float TrackDir::TopSeconds() const {
    return mTopY / mYPerSecond;
}

float TrackDir::BottomSeconds() const {
    return mBottomY / mYPerSecond;
}

float TrackDir::SecondsToY(float f) const {
    return f * mYPerSecond;
}

float TrackDir::YToSeconds(float f) const {
    return f / mYPerSecond;
}

float TrackDir::CutOffY() const {
    if(TheLoadMgr.EditMode()){
        return mBottomY;
    } else {
        float secs = TheTaskMgr.Seconds(TaskMgr::b);
        float bias = secs * mYPerSecond;
        return mBottomY + bias;
    }
}

// fn_8053FC48
void TrackDir::SetSlotXfm(int i, const Transform& tf){
    if(i >= mSlots.size()){
        Transform t48;
        t48.Reset();
        while(i >= mSlots.size()) mSlots.push_back(t48);
    }
    else {
        if(i >= vec2.size()){
            Transform t78;
            t78.Reset();
            while(i >= vec2.size()) vec2.push_back(t78);
        }
        vec2[i] = mSlots[i];
    }
    mSlots[i] = tf;
}

void TrackDir::MakeSecondsXfm(float f, Transform& tf) const {
    tf.Reset();
    tf.v.y = f * mYPerSecond;
}

void TrackDir::MakeWidgetXfm(int i, float f, Transform& tf) const {
    MakeSlotXfm(i, tf);
    tf.v.y = f * mYPerSecond;
}

void TrackDir::MakeSlotXfm(int slot, Transform& tf) const {
    MILO_ASSERT(slot < mSlots.size(), 0x220);
    tf = mSlots[slot];
}

DECOMP_FORCEACTIVE(TrackDir, "gem_mash", "drum_mash")

void TrackDir::SetScrollSpeed(float f){
    if(f > 0) mYPerSecond = mTopY / f;
}

float TrackDir::ViewTimeSeconds() const {
    if(mYPerSecond > 0) return mTopY / mYPerSecond;
    else return 0;
}

void TrackDir::ClearAllWidgets(){
    for(ObjDirItr<TrackWidget> it(this, true); it != 0; ++it){
        it->Clear();
    }
}

// fn_8053FED4
void TrackDir::ClearAllGemWidgets(){
    for(ObjDirItr<TrackWidget> it(this, true); it != 0; ++it){
        if(strncmp(it->Name(), "gem_", 4) == 0) it->Clear();
        else if(strncmp(it->Name(), "drum_", 5) == 0) it->Clear();
        else if(strncmp(it->Name(), "rg_", 3) == 0) it->Clear();
        else if(strncmp(it->Name(), "real_", 5) == 0) it->Clear();
        else if(strncmp(it->Name(), "fret_", 5) == 0) it->Clear();
        else if(strncmp(it->Name(), "chord_", 5) == 0) it->Clear();
    }
}

void TrackDir::ToggleRunning(){
    SetRunning(mRunning == 0);
}

void TrackDir::SetRunning(bool b){
    if(mRunning && !b){
        mAnimGroup->SetFrame(0.0f, 1.0f);
    }
    mRunning = b;
}

void TrackDir::AddTestWidget(TrackWidget* widget, int i){
    if(!mRunning) MILO_WARN("Track is not running");
    else if(!widget) MILO_WARN("No test widget selected");
    else if(i >= mSlots.size()) MILO_WARN("Can't add widget on slot %i, only %i slots", i, mSlots.size());
    else {
        Transform tf;
        MakeWidgetXfm(i, TheTaskMgr.Seconds(TaskMgr::b), tf);
        tf.v.y += mTopY;
        widget->AddInstance(tf, 0.0f);
    }
}

void TrackDir::AddActiveWidget(TrackWidget* widget){
    std::vector<TrackWidget*>::iterator it = std::find(mActiveWidgets.begin(), mActiveWidgets.end(), widget);
    MILO_ASSERT(it == mActiveWidgets.end(), 0x2A5);
    if(mActiveWidgets.size() == mActiveWidgets.capacity() && mActiveWidgets.size() == mActiveWidgets.capacity()){
        MILO_FAIL("Number of active widgets exceeds capacity %d", mActiveWidgets.capacity());
    }
    mActiveWidgets.push_back(widget);
}

BEGIN_HANDLERS(TrackDir)
    HANDLE_ACTION(toggle_running, ToggleRunning())
    HANDLE_ACTION(add_test_widget, AddTestWidget(_msg->Obj<TrackWidget>(2), _msg->Int(3)))
    HANDLE_ACTION(clear_all, ClearAllWidgets())
    HANDLE_SUPERCLASS(PanelDir)
    HANDLE_CHECK(699)
END_HANDLERS

#include "utl/ClassSymbols.h"

BEGIN_PROPSYNCS(TrackDir)
    SYNC_PROP(draw_group, mDrawGroup)
    SYNC_PROP(anim_group, mAnimGroup)
    SYNC_PROP(y_per_second, mYPerSecond)
    SYNC_PROP(top_y, mTopY)
    SYNC_PROP(bottom_y, mBottomY)
    SYNC_PROP(slots, mSlots)
    SYNC_PROP(warn_on_resort, mWarnOnResort)
#ifdef MILO_DEBUG
    SYNC_PROP(TrackTesting, *mTest)
#endif
    SYNC_SUPERCLASS(PanelDir)
END_PROPSYNCS
