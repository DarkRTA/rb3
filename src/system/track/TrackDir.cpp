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
    mTrackGems(this, 0), unk368(1.0f), mTest(new TrackTest(this)) {
    vec3.reserve(0x32);
    unk2d8.Reset();
    unk308.Reset();
    unk338.Reset();
}

TrackDir::~TrackDir(){
    delete mTest;
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
        COPY_MEMBER(mTest->mWidget)
        COPY_MEMBER(mTest->mSlot)
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
        if(gRev > 3){
            bs >> mTest->mWidget >> mTest->mSlot;
        }
    }
    for(ObjDirItr<TrackWidget> it(this, true); it != 0; ++it){
        it->SetTrackDir(this);
    }
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
