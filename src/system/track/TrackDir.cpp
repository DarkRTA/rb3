#include "track/TrackDir.h"
#include "utl/Loader.h"
#include "rndobj/Group.h"
#include "track/TrackTest.h"

TrackDir::TrackDir() : mRunning(!TheLoadMgr.EditMode()), mDrawGroup(this, 0), mAnimGroup(this, 0), mYPerSecond(10.0f), mTopY(10.0f), mBottomY(-3.0f),
    unk218(this, 0), unk224(this, 0), unk230(this, 0), unk23c(this, 0), unk248(this, 0), unk254(this, 0), unk260(this, 0), unk26c(this, 0), unk278(this, 0),
    unk284(this, 0), unk290(this, 0), unk29c(this, 0), unk2a8(this, 0), unk2b4(this, 0), unk2c0(this, 0), unk2cc(this, 0), unk368(1.0f), mTest(new TrackTest(this)) {
    vec3.reserve(0x32);
    unk2d8.Reset();
    unk308.Reset();
    unk338.Reset();
}

TrackDir::~TrackDir(){
    
}