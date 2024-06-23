#include "track/TrackDir.h"
#include "obj/ObjMacros.h"
#include "ui/PanelDir.h"
#include "utl/Loader.h"
#include "rndobj/Group.h"
#include "track/TrackTest.h"
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

void TrackDir::SyncObjects() {
    PanelDir::SyncObjects();
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
