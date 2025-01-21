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
#include "char/ClipDistMap.h"
#include "char/Waypoint.h"
#include "decomp.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "rndobj/Cam.h"
#include "rndobj/Utl.h"
#include "obj/DirLoader.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

Hmx::Object* gClick;
INIT_REVS(CharacterTest)

CharacterTest::CharacterTest(class Character* thechar) : mMe(thechar), mDriver(thechar), mClip1(thechar), mClip2(thechar), mFilterGroup(thechar),
    mTeleportTo(thechar), mWalkPath(thechar), mShowDistMap(), mTransition(0), mCycleTransition(1), mMetronome(0), mZeroTravel(0),
    mShowScreenSize(0), mShowFootExtents(0), unk68(0), unk6c(0), mOverlay(RndOverlay::Find("char_test", true)) {
    mShowDistMap = none;
}

CharacterTest::~CharacterTest(){
    mOverlay = RndOverlay::Find("char_test", false);
    if(mOverlay){
        if(mOverlay->GetCallback() == this){
            mOverlay->SetCallback(nullptr);
            mOverlay->SetOverlay(false);
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
    if(Clips() && mClip1){
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
            Transform xfm = mMe->LocalXfm();
            xfm.v.Zero();
            mMe->SetLocalXfm(xfm);
            if(mMe->BoneServo()){
                mMe->BoneServo()->SetRegulateWaypoint(nullptr);
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
                ltwist->SetProperty(hand, lhand);
                ltwist->SetProperty(twist2, ltwist2);
                ltwist->SetProperty(offset, 90);
            }
        }
    }
    if(!mMe->Find<CharForeTwist>("foreTwist_R.ik", false)){
        RndTransformable* rhand = CharUtlFindBoneTrans("bone_R-hand", mMe);
        if(rhand){
            RndTransformable* rtwist2 = CharUtlFindBoneTrans("bone_R-foreTwist2", mMe);
            if(rtwist2){
                CharForeTwist* rtwist = mMe->New<CharForeTwist>("foreTwist_R.ik");
                rtwist->SetProperty(hand, rhand);
                rtwist->SetProperty(twist2, rtwist2);
                rtwist->SetProperty(offset, -90);
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
                    ltwist->SetProperty(twist1, lutwist1);
                    ltwist->SetProperty(twist2, lutwist2);
                    ltwist->SetProperty(upper_arm, luarm);
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
                    rtwist->SetProperty(twist1, rutwist1);
                    rtwist->SetProperty(twist2, rutwist2);
                    rtwist->SetProperty(upper_arm, ruarm);
                }
            }
        }
    }
}

void CharacterTest::SetDistMap(Symbol s){
    mShowDistMap = s;
    RELEASE(unk6c);
    if(mShowDistMap != none){
        mOverlay->SetCallback(this);
        mOverlay->SetOverlay(true);
        if(mClip1 && mClip2 && Clips()){
    //     if (*param_1.mStr == raw) {
    //       this_00 = operator_new(0x4c);
    //       if (this_00 != 0x0) {
    //         this_00 = ClipDistMap::ClipDistMap(this_00,*(this + 0x1c),*(this + 0x28),1.0,1.0,3,0x0 );
    //       }
    //       *(this + 0x6c) = this_00;
    //       ClipDistMap::FindDists(this_00,0.0,0x0);
    //     }
    //     else {
    //       ClipGraphGenerator::ClipGraphGenerator(aCStack_48);
    //       uVar2 = ClipGraphGenerator::GeneratePair(aCStack_48,*(this + 0x1c),*(this + 0x28),0x0,0x 0)
    //       ;
    //       *(this + 0x6c) = uVar2;
    //       ClipGraphGenerator::~ClipGraphGenerator(aCStack_48);
    //     }
        }
    }
}

void CharacterTest::Walk(){
    if(!mWalkPath.empty()){
        std::vector<Waypoint*> vec;
        for(ObjPtrList<Waypoint>::iterator it = mWalkPath.begin(); it != mWalkPath.end(); ++it){
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

DECOMP_FORCEACTIVE(CharacterTest, __FILE__, "0")

void CharacterTest::Recenter(){
    Transform xfm;
    xfm.Reset();
    mMe->SetLocalXfm(xfm);
    if(mMe->BoneServo()){
        mMe->BoneServo()->SetRegulateWaypoint(nullptr);
    }
}

void CharacterTest::SetMoveSelf(bool b){
    if(mMe->BoneServo()){
        mMe->BoneServo()->SetMoveSelf(b);
    }
}

DataNode CharacterTest::OnGetFilteredClips(DataArray* arr){
    int count = 0;
    ObjectDir* clipDir = Clips();
    if(clipDir){
        for(ObjDirItr<CharClip> it(clipDir, true); it != nullptr; ++it){
            count++;
        }
    }
    DataArrayPtr ptr;
    ptr->Resize(count + 1);
    ptr->Node(0) = NULL_OBJ;
    if(clipDir){
        int idx = 1;
        for(ObjDirItr<CharClip> it(clipDir, true); it != nullptr; ++it){
            if(!mFilterGroup || mFilterGroup->FindClip(it->Name())){
                ptr->Node(idx++) = &*it;
            }
        }
        ptr->Resize(idx);
        ptr->SortNodes();
    }
    return ptr;
}

BEGIN_LOADS(CharacterTest)
    LOAD_REVS(bs)
#ifdef MILO_DEBUG
    if(gRev > 0xF){
        MILO_FAIL("%s can't load new %s version %d > %d", PathName(mMe), "CharacterTesting", gRev, (unsigned short)0xF);
    }
    if(gAltRev != 0){
        MILO_FAIL("%s can't load new %s alt version %d > %d", PathName(mMe), "CharacterTesting", gAltRev, (unsigned short)0);
    }
#endif
    if(gRev != 0xD) mDriver.Load(bs, false, mMe);
    
    if(Clips()){
        mClip1.Load(bs, true, Clips());
        mClip2.Load(bs, true, Clips());
    }
    else {
        Symbol s;
        bs >> s;
        bs >> s;
        mClip1 = nullptr;
        mClip2 = nullptr;
    }
    bs >> mTeleportTo;
    mWalkPath.Load(bs, false);
    bs >> mShowDistMap;
    bs >> mTransition;
    bs >> mCycleTransition;
    bs >> unk68;
    if(gRev < 10){
        int i; bs >> i;
    }
    bs >> mMetronome;
    bs >> mZeroTravel;
    bs >> mShowScreenSize;
    if(gRev < 0xC){
        Symbol ss; bs >> ss;
    }
    bs >> mShowFootExtents;
    if(gRev < 0xF){
        bool b; int i;
        bs >> b; bs >> i;
    }
    if(gRev >= 7 && gRev <= 10){
        Symbol ss; int i;
        bs >> ss; bs >> i;
    }
    if(gRev >= 9 && gRev <= 10){
        Symbol ss; bs >> ss;
    }
    if(!mDriver){
        mDriver = mMe->Find<CharDriver>("main.drv", false);
    }
END_LOADS

DataNode CharacterTest::Handle(DataArray* _msg, bool _warn){
    Symbol sym = _msg->Sym(1); 
    MessageTimer timer((MessageTimer::Active()) ? dynamic_cast<Hmx::Object*>(this) : 0, sym);
    HANDLE_ACTION(add_defaults, AddDefaults())
    HANDLE_ACTION(test_walk, Walk())
    HANDLE_ACTION(recenter, Recenter())
    HANDLE(get_filtered_clips, OnGetFilteredClips)
    HANDLE_ACTION(sync, Sync())
    if(_warn) MILO_WARN("%s(%d): %s unhandled msg: %s", __FILE__, 0x27D, PathName(dynamic_cast<Hmx::Object*>(this)), sym);
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(CharacterTest)
    SYNC_PROP(show_screen_size, o.mShowScreenSize)
    SYNC_PROP(driver, o.mDriver)
    SYNC_PROP_SET(clips, o.Clips(), )
    SYNC_PROP(clip1, o.mClip1)
    SYNC_PROP(clip2, o.mClip2)
    SYNC_PROP(filter_group, o.mFilterGroup)
    SYNC_PROP(transition, o.mTransition)
    SYNC_PROP(cycle_transition, o.mCycleTransition)
    SYNC_PROP_SET(move_self, o.mMe->BoneServo() ? o.mMe->BoneServo()->mMoveSelf : false, o.SetMoveSelf(_val.Int()))
    SYNC_PROP_SET(teleport_to, o.mTeleportTo, o.TeleportTo(_val.Obj<Waypoint>()))
    SYNC_PROP(walk_path, o.mWalkPath)
    SYNC_PROP_SET(dist_map, o.mShowDistMap, o.SetDistMap(_val.Sym()))
    SYNC_PROP(zero_travel, o.mZeroTravel)
    SYNC_PROP(metronome, o.mMetronome)
    SYNC_PROP(show_footextents, o.mShowFootExtents)
END_CUSTOM_PROPSYNC