#include "track/TrackDir.h"
#include "obj/ObjMacros.h"
#include "ui/PanelDir.h"
#include "utl/Loader.h"
#include "rndobj/Group.h"
#include "track/TrackTest.h"
#include "track/TrackWidget.h"
#include "utl/Symbols.h"

TrackDir::TrackDir() : mRunning(!TheLoadMgr.EditMode()), mDrawGroup(this, 0), mAnimGroup(this, 0), mYPerSecond(10.0f), 
    mTopY(10.0f), mBottomY(-3.0f), mWarnOnResort(false), unk218(this, 0), unk224(this, 0), unk230(this, 0), 
    unk23c(this, 0), unk248(this, 0), unk254(this, 0), unk260(this, 0), unk26c(this, 0), unk278(this, 0), 
    unk284(this, 0), unk290(this, 0),  unk29c(this, 0), unk2a8(this, 0), unk2b4(this, 0), unk2c0(this, 0), 
    unk2cc(this, 0), unk368(1.0f), mTest(new TrackTest(this)) {
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
    if(!unk2c0) unk2c0 = Find<RndEnviron>("track.env", false);
    if(!unk2cc) unk2cc = Find<RndEnviron>("track_gems.env", false);
    if(!unk218) unk218 = Find<RndGroup>("showing_when_enabled.grp", false);
    if(!unk224) unk224 = Find<RndGroup>("stationary_back.grp", false);
    if(!unk230) unk230 = Find<RndGroup>("key_shift_stationary_back.grp", false);
    if(!unk23c) unk23c = Find<RndGroup>("stationary_back_after_key_shift.grp", false);
    if(!unk248) unk248 = Find<RndGroup>("moving_back.grp", false);
    if(!unk254) unk254 = Find<RndGroup>("key_shift_moving_back.grp", false);
    if(!unk260) unk260 = Find<RndGroup>("key_shift_stationary_middle.grp", false);
    if(!unk26c) unk26c = Find<RndGroup>("stationary_middle.grp", false);
    if(!unk278) unk278 = Find<RndGroup>("moving_front.grp", false);
    if(!unk284) unk284 = Find<RndGroup>("key_shift_moving_front.grp", false);
    if(!unk290) unk290 = Find<RndGroup>("key_shift_stationary_front.grp", false);
    if(!unk29c) unk29c = Find<RndGroup>("stationary_front.grp", false);
    if(!unk2a8) unk2a8 = Find<RndGroup>("always_showing.grp", false);
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
