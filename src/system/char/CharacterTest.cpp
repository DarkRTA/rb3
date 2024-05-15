#include "char/CharacterTest.h"
#include "char/Character.h"
#include "char/CharDriver.h"
#include "char/CharClip.h"
#include "char/CharClipGroup.h"
#include "char/Waypoint.h"
#include "utl/Symbols.h"

CharacterTest::CharacterTest(class Character* thechar) : mMe(thechar), mDriver(thechar, 0), mClip1(thechar, 0), mClip2(thechar, 0), mFilterGroup(thechar, 0), 
    mTeleportTo(thechar, 0), mWalkPath(thechar, kObjListNoNull), mShowDistMap(), mTransition(0), unk5c(1), unk5d(0), unk5e(0), unk5f(0), unk60(0), unk68(0), unk6c(0), 
    mOverlay(RndOverlay::Find("char_test", true)) {
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