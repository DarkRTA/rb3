#include "track/TrackDir.h"
#include "obj/ObjMacros.h"
#include "ui/PanelDir.h"
#include "utl/Loader.h"
#include "rndobj/Group.h"
#include "track/TrackTest.h"
#include "track/TrackWidget.h"
#include "utl/Symbols.h"

TrackDir::TrackDir() : mRunning(!TheLoadMgr.EditMode()), mDrawGroup(this, 0), mAnimGroup(this, 0), mYPerSecond(10.0f), 
    mTopY(10.0f), mBottomY(-3.0f), mWarnOnResort(false), mShowingWhenEnabled(this, 0), mStationaryBack(this, 0), mKeyShiftStationaryBack(this, 0), 
    mStationaryBackAfterKeyShift(this, 0), mMovingBack(this, 0), mKeyShiftMovingBack(this, 0), mKeyShiftStationaryMiddle(this, 0),
    mStationaryMiddle(this, 0), mMovingFront(this, 0), mKeyShiftMovingFront(this, 0), mKeyShiftStationaryFront(this, 0),
    mStationaryFront(this, 0), mAlwaysShowing(this, 0), mRotatorCam(this, 0), mTrack(this, 0), 
    mTrackGems(this, 0), unk368(1.0f), mTest(new TrackTest(this)) {
    vec3.reserve(0x32);
    unk2d8.Reset();
    unk308.Reset();
    unk338.Reset();
}

TrackDir::~TrackDir(){
    
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
}

void TrackDir::ResetKeyShifting(){
    mRotatorCam = 0;
    unk2d8.Reset();
    unk308.Reset();
    unk338.Reset();
}

BEGIN_HANDLERS(TrackDir)
    HANDLE_ACTION(toggle_running, ToggleRunning())
    HANDLE_ACTION(add_test_widget, AddTestWidget(_msg->Obj<TrackWidget>(2), _msg->Int(3)))
    HANDLE_ACTION(clear_all, ClearAllWidgets())
    HANDLE_SUPERCLASS(PanelDir)
    HANDLE_CHECK(699)
END_HANDLERS

BEGIN_PROPSYNCS(TrackDir)

END_PROPSYNCS
