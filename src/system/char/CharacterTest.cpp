#include "char/CharacterTest.h"
#include "char/Character.h"
#include "char/CharDriver.h"
#include "char/CharClip.h"
#include "char/CharClipDriver.h"
#include "char/CharClipGroup.h"
#include "char/CharForeTwist.h"
#include "char/CharServoBone.h"
#include "char/CharUpperTwist.h"
#include "char/CharUtl.h"
#include "char/Waypoint.h"
#include "rndobj/Cam.h"
#include "rndobj/Utl.h"
#include "obj/DirLoader.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

Hmx::Object* gClick;
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

void CharacterTest::Draw(){
    if(mDriver && (mClip1 || mClip2)) mDriver->Highlight();
    RndTransformable* trans = CharUtlFindBoneTrans("bone_head", mMe);
    if(!trans) trans = mMe;
    if(mShowScreenSize){
        UtilDrawString(MakeString("lod %d %.3f", mMe->LastLod(), mMe->ComputeScreenSize(RndCam::sCurrent)), trans->WorldXfm().v, Hmx::Color(1.0f, 1.0f, 1.0f));
    }
}

void CharacterTest::Poll(){
    ObjectDir* clipdir = mDriver ? mDriver->ClipDir() : 0;
    if(clipdir && mClip1){
        Hmx::Object* tmp = gClick;
        if(!gClick){
            ObjectDir* clickdir = DirLoader::LoadObjects(FilePath(MakeString("%s/char/chartest.milo", FileSystemRoot())), 0, 0);
            gClick = clickdir->Find<Hmx::Object>("click_hi.cue", true);
        }
        gClick = tmp;
        float beat = TheTaskMgr.Beat();
        float deltabeat = TheTaskMgr.DeltaBeat();
        if(mMetronome){
            if(std::floor(beat - deltabeat) + 1.0f == std::floor(beat)){
                gClick->Handle(play_msg, true);
            }
        }
        CharClipDriver* drivs = mDriver->mFirst;
        if(!drivs) PlayNew();
        else if(mClip2){
            CharClip* drivclip = drivs->mClip;
            if(drivclip != mClip1 && drivclip != mClip2 || (drivclip == mClip2 && unk64 < drivs->mBeat)) PlayNew();
        }
        else if(drivs->mClip != mClip1) PlayNew();
        if(mZeroTravel){
            // some Transform operation
            if(mMe->BoneServo()){
                mMe->BoneServo()->mRegulate = 0;
            }
            Recenter();
        }
    }
}

void CharacterTest::AddDefaults(){
    if(!mMe->mDriver) mMe->New<CharDriver>("main.drv");
    if(!mMe->BoneServo()){
        if(!mMe->Find<CharServoBone>("bone.servo", false)){
            mMe->New<CharServoBone>("bone.servo");
        }
        mMe->mDriver->SetBones(mMe->Find<CharBonesObject>("bone.servo", true));
    }
    if(!mMe->Find<CharForeTwist>("foreTwist_L.ik", false)){
        RndTransformable* lhand = CharUtlFindBoneTrans("bone_L-hand", mMe);
        if(lhand){
            RndTransformable* ltwist2 = CharUtlFindBoneTrans("bone_L-foreTwist2", mMe);
            if(ltwist2){
                CharForeTwist* ltwist = mMe->New<CharForeTwist>("foreTwist_L.ik");
                ltwist->SetProperty(hand, DataNode(lhand));
                ltwist->SetProperty(twist2, DataNode(ltwist2));
                ltwist->SetProperty(offset, DataNode(90));
            }
        }
    }
    if(!mMe->Find<CharForeTwist>("foreTwist_R.ik", false)){
        RndTransformable* rhand = CharUtlFindBoneTrans("bone_R-hand", mMe);
        if(rhand){
            RndTransformable* rtwist2 = CharUtlFindBoneTrans("bone_R-foreTwist2", mMe);
            if(rtwist2){
                CharForeTwist* rtwist = mMe->New<CharForeTwist>("foreTwist_R.ik");
                rtwist->SetProperty(hand, DataNode(rhand));
                rtwist->SetProperty(twist2, DataNode(rtwist2));
                rtwist->SetProperty(offset, DataNode(-90));
            }
        }
    }
    if(!mMe->Find<CharUpperTwist>("upperTwist_L.ik", false)){
        RndTransformable* lutwist1 = CharUtlFindBoneTrans("bone_L-upperTwist1", mMe);
        if(lutwist1){
            RndTransformable* lutwist2 = CharUtlFindBoneTrans("bone_L-upperTwist2", mMe);
            if(lutwist2){
                RndTransformable* luarm = CharUtlFindBoneTrans("bone_L-upperArm", mMe);
                if(luarm){
                    CharUpperTwist* ltwist = mMe->New<CharUpperTwist>("upperTwist_L.ik");
                    ltwist->SetProperty(twist1, DataNode(lutwist1));
                    ltwist->SetProperty(twist2, DataNode(lutwist2));
                    ltwist->SetProperty(upper_arm, DataNode(luarm));
                }
            }
        }
    }
    if(!mMe->Find<CharUpperTwist>("upperTwist_R.ik", false)){
        RndTransformable* rutwist1 = CharUtlFindBoneTrans("bone_R-upperTwist1", mMe);
        if(rutwist1){
            RndTransformable* rutwist2 = CharUtlFindBoneTrans("bone_R-upperTwist2", mMe);
            if(rutwist2){
                RndTransformable* ruarm = CharUtlFindBoneTrans("bone_R-upperArm", mMe);
                if(ruarm){
                    CharUpperTwist* rtwist = mMe->New<CharUpperTwist>("upperTwist_R.ik");
                    rtwist->SetProperty(twist1, DataNode(rutwist1));
                    rtwist->SetProperty(twist2, DataNode(rutwist2));
                    rtwist->SetProperty(upper_arm, DataNode(ruarm));
                }
            }
        }
    }
}

void CharacterTest::Walk(){
    if(!mWalkPath.empty()){
        std::vector<Waypoint*> vec;
        for(ObjPtrList<Waypoint, ObjectDir>::iterator it = mWalkPath.begin(); it != mWalkPath.end(); ++it){
            vec.push_back(*it);
        }
    }
}

void CharacterTest::TeleportTo(Waypoint* wp){
    if(wp) mMe->Teleport(wp);
}

void CharacterTest::SetStartEndBeat(float f1, float f2, int bpm){
    Hmx::Object* miloObj = ObjectDir::Main()->FindObject("milo", false);
    if(miloObj){
        DataNode milohandled = miloObj->Handle(Message("cur_anim"), true);
        if(milohandled.Type() == kDataObject){
            Hmx::Object* handledObj = milohandled.GetObj();
            if(handledObj == mMe){
                mMe->mFrozen = 0; // i know this is wrong, just can't figure out the right member atm
                miloObj->SetProperty("bpm", DataNode(bpm));
                miloObj->Handle(Message("set_anim_frame", DataNode((f1 * 30.0f) / (bpm / 60.0f)), DataNode((f2 * 30.0f) / (bpm / 60.0f)), DataNode((float)bpm)), true);
            }
        }
    }
}

void CharacterTest::SetMoveSelf(bool b){
    if(mMe->BoneServo()){
        mMe->BoneServo()->SetMoveSelf(b);
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
