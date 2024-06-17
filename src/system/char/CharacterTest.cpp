#include "char/CharacterTest.h"
#include "char/Character.h"
#include "char/CharDriver.h"
#include "char/CharClip.h"
#include "char/CharClipGroup.h"
#include "char/Waypoint.h"
#include "utl/Symbols.h"

INIT_REVS(CharacterTest)

CharacterTest::CharacterTest(class Character* thechar) : mMe(thechar), mDriver(thechar, 0), mClip1(thechar, 0), mClip2(thechar, 0), mFilterGroup(thechar, 0), 
    mTeleportTo(thechar, 0), mWalkPath(thechar, kObjListNoNull), mShowDistMap(), mTransition(0), mCycleTransition(1), mMetronome(0), mZeroTravel(0), 
    mShowScreenSize(0), mShowFootExtents(0), unk68(0), unk6c(0), mOverlay(RndOverlay::Find("char_test", true)) {
    mShowDistMap = none;
}

CharacterTest::~CharacterTest(){
    mOverlay = RndOverlay::Find("char_test", false);
    if(mOverlay){
        if(mOverlay->mCallback == this){
            mOverlay->mCallback = 0;
            RndOverlay* over = mOverlay;
            over->mShowing = 0;
            over->mTimer.Restart();
        }
    }
}

BEGIN_LOADS(CharacterTest)
    LOAD_REVS(bs)
    if(gRev > 0xF){
        TheDebugFailer << MakeString("%s can't load new %s version %d > %d", PathName(mMe), "CharacterTesting", gRev, (unsigned short)0xF);
    }
    if(gAltRev != 0){
        TheDebugFailer << MakeString("%s can't load new %s alt version %d > %d", PathName(mMe), "CharacterTesting", gAltRev, (unsigned short)0);
    }
    if(gRev != 0xD) mDriver.Load(bs, false, mMe);
END_LOADS