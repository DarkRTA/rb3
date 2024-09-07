#include "bandobj/BandCamShot.h"
#include "char/Character.h"
#include "char/CharDriver.h"
#include "obj/Msg.h"
#include "obj/Utl.h"
#include "world/EventAnim.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

INIT_REVS(BandCamShot)

std::list<BandCamShot::TargetCache> BandCamShot::sCache;
BandCamShot* gBandCamShotOwner;

std::list<BandCamShot::TargetCache>::iterator BandCamShot::CreateTargetCache(Symbol s){
    sCache.push_back(TargetCache());
    sCache.back().unk4 = FindTarget(s, true);
    return sCache.begin();
}

void BandCamShot::DeleteTargetCache(std::list<TargetCache>::iterator it){
    sCache.erase(it);
}

BandCamShot::BandCamShot() : mTargets(this), mMinTime(0), mMaxTime(0), mZeroTime(0), mNextShots(this, kObjListNoNull), mCurShot(this, 0),
    unk15c(0), unk160(0), unk164(0), unk168(0), unk169(0), unk16a(0), mAnimsDuringNextShots(0) {
    SetNear(10.0f);
    SetFar(10000.0f);
    mShotIter = mNextShots.end();
}

RndTransformable* BandCamShot::FindTarget(Symbol s, bool b){
    static Message msg("find_target", DataNode(0), DataNode(1));
    msg[0] = DataNode(s);
    msg[1] = DataNode(b);
    DataNode handled = HandleType(msg);
    RndTransformable* ret = 0;
    if(handled.Type() != kDataUnhandled){
        ret = handled.Obj<RndTransformable>(0);
    }
    if(!ret){
        if(Dir()) ret = Dir()->Find<RndTransformable>(s.Str(), false);
    }
    return ret;
}

BinStream& operator>>(BinStream& bs, BandCamShot::Target& tgt){
    bs >> tgt.mTarget;
    if(BandCamShot::gRev > 0xA){
        char b; bs >> b;
        tgt.mTeleport = b;
    }
    else {
        tgt.mTeleport = true;
    }
    bs >> tgt.mXfm;
    if(BandCamShot::gRev == 0){
        Transform tf;
        bs >> tf;
    }
    bs >> tgt.mAnimGroup;
    char ret;
    bs >> ret;
    tgt.mReturn = ret;
    if(BandCamShot::gRev > 2){
        if(BandCamShot::gRev < 0x1D){
            bool b; int i; bs >> b; bs >> i;
        }
        if(BandCamShot::gRev < 0xC){
            int i; bs >> i;
        }
    }
    if(BandCamShot::gRev > 3) bs >> tgt.mFastForward;
    else tgt.mFastForward = 0;
    if(BandCamShot::gRev > 0xA) bs >> tgt.mForwardEvent;
    else tgt.mForwardEvent = Symbol();
    if(BandCamShot::gRev > 5){
        char b; bs >> b;
        tgt.mSelfShadow = b;
    }
    else tgt.mSelfShadow = 1;
    if(BandCamShot::gRev > 6){
        char b; bs >> b;
        tgt.unk1 = b;
        char b2; bs >> b2;
        tgt.unk2 = b2;
        if(BandCamShot::gRev > 0x1F){
            char bhide; bs >> bhide;
            tgt.mHide = bhide;
        }
        else tgt.mHide = 0;
    }
    else {
        tgt.unk1 = 0;
        tgt.unk2 = 1;
    }
    if(
        BandCamShot::gRev == 8 || BandCamShot::gRev == 9 || BandCamShot::gRev == 10 || BandCamShot::gRev == 11 || BandCamShot::gRev == 12 || BandCamShot::gRev == 13 ||
        BandCamShot::gRev == 14 || BandCamShot::gRev == 15 || BandCamShot::gRev == 16 || BandCamShot::gRev == 17 || BandCamShot::gRev == 18 || BandCamShot::gRev == 19 ||
        BandCamShot::gRev == 20 || BandCamShot::gRev == 21 || BandCamShot::gRev == 22 || BandCamShot::gRev == 23 || BandCamShot::gRev == 24 || BandCamShot::gRev == 25 ||
        BandCamShot::gRev == 26 || BandCamShot::gRev == 27 || BandCamShot::gRev == 28
    ){
        Symbol s;
        bs >> s; bs >> s;
        if(BandCamShot::gRev > 8){
            bs >> s; bs >> s;
        }
    }
    if(BandCamShot::gRev > 9) bs >> tgt.mEnvOverride;
    if(
        BandCamShot::gRev == 17 || BandCamShot::gRev == 18 || BandCamShot::gRev == 19 || BandCamShot::gRev == 20 ||
        BandCamShot::gRev == 21 || BandCamShot::gRev == 22 || BandCamShot::gRev == 23 || BandCamShot::gRev == 24 ||
        BandCamShot::gRev == 25 || BandCamShot::gRev == 26 || BandCamShot::gRev == 27 || BandCamShot::gRev == 28
    ){
        bool b; bs >> b;
    }
    if(BandCamShot::gRev > 0x14){
        if(BandCamShot::gRev < 0x1E){
            int b; bs >> b;
            tgt.mForceLod = b;
        }
        else {
            char b; bs >> b;
            tgt.mForceLod = b;
        }
        if(BandCamShot::gRev < 0x19){
            if(tgt.mForceLod <= 0){
                tgt.mForceLod = -1;
            }
        }
        if(BandCamShot::gRev < 0x1B && tgt.mForceLod < 0){
            tgt.mForceLod = -1;
        }
    }
    if(
        BandCamShot::gRev == 22 || BandCamShot::gRev == 23 || BandCamShot::gRev == 24 || BandCamShot::gRev == 25 ||
        BandCamShot::gRev == 26 || BandCamShot::gRev == 27 || BandCamShot::gRev == 28
    ){
        String s48; int i;
        bs >> s48; bs >> s48;
        bs >> i; bs >> i;
        if(BandCamShot::gRev > 0x17){
            bs >> i; bs >> i; bs >> i;
        }
    }
    return bs;
}

SAVE_OBJ(BandCamShot, 0x14A)

BinStream& operator>>(BinStream& bs, OldTrigger& o){
    bs >> o.frame;
    bs >> o.trigger;
    return bs;
}

EventAnim* MakeEventAnim(BandCamShot* shot){
    EventAnim* anim = Hmx::Object::New<EventAnim>();
    anim->SetName(MakeString("%s_trigs.evntanm", FileGetBase(shot->Name(), 0)), shot->Dir());
    return anim;
}

BEGIN_LOADS(BandCamShot)
    LOAD_REVS(bs)
    ASSERT_REVS(0x20, 0)
    if(gRev > 4) LOAD_SUPERCLASS(CamShot)
    bs >> mTargets;
    if(
        BandCamShot::gRev == 2 || BandCamShot::gRev == 3 || BandCamShot::gRev == 4 || BandCamShot::gRev == 5 || BandCamShot::gRev == 6 || BandCamShot::gRev == 7 ||
        BandCamShot::gRev == 8 || BandCamShot::gRev == 9 || BandCamShot::gRev == 10 || BandCamShot::gRev == 11 || BandCamShot::gRev == 12 || BandCamShot::gRev == 13 ||
        BandCamShot::gRev == 14 || BandCamShot::gRev == 15 || BandCamShot::gRev == 16 || BandCamShot::gRev == 17 || BandCamShot::gRev == 18
    ){
        ObjPtr<BandCamShot, ObjectDir> shotPtr(this, 0);
        bs >> shotPtr;
        if(shotPtr) mNextShots.push_back(shotPtr);
    }
    if(gRev > 3) bs >> mZeroTime;
    if(gRev <= 4) LOAD_SUPERCLASS(CamShot)
    if(gRev == 0xD){
        bool b; bs >> b;
        mPS3PerPixel = b;
    }
    EventAnim* anim = 0;
    if(gRev - 0xF <= 0xDU){
        std::vector<OldTrigger> trigs;
        bs >> trigs;
        if(!trigs.empty()){
            anim = MakeEventAnim(this);
        }
    }
    if(gRev - 0x10 <= 0xCU){
        ObjPtr<EventTrigger, ObjectDir> trig1(this, 0);
        ObjPtr<EventTrigger, ObjectDir> trig2(this, 0);
        bs >> trig1;
        bs >> trig2;
    }
    if(gRev > 0x11){
        bs >> mMinTime;
        bs >> mMaxTime;
    }
    if(gRev > 0x12) bs >> mNextShots;
    if(gRev - 0x14 < 0xBU){
        int i; bs >> i;
    }
    if(gRev - 0x17 < 6){
        bs >> anim->mResetStart;
    }
    if(gRev == 0x1C) bs >> mAnims;
    if(anim) mAnims.push_back(anim);
    ResetNextShot();
END_LOADS

BEGIN_COPYS(BandCamShot)
    COPY_SUPERCLASS(CamShot)
    CREATE_COPY(BandCamShot)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mTargets)
        COPY_MEMBER(mZeroTime)
        COPY_MEMBER(mMinTime)
        COPY_MEMBER(mMaxTime)
        COPY_MEMBER(mNextShots)
        ResetNextShot();
    END_COPYING_MEMBERS
END_COPYS

bool BandCamShot::IterateNextShot(){
    bool ret = true;
    MILO_ASSERT(!mNextShots.empty(), 0x278);
    if(mShotIter == mNextShots.end()){
        mShotIter = mNextShots.begin();
    }
    else {
        ObjPtrList<BandCamShot, ObjectDir>::iterator curItr = mShotIter;
        ++mShotIter;
        if(mShotIter == mNextShots.end()){
            ret = false;
            mShotIter = curItr;
        }
    }
    return ret;
}

void BandCamShot::ResetNextShot(){
    mShotIter = mNextShots.end();
    mCurShot = this;
    unk15c = 0;
    unk160 = 0;
}

void BandCamShot::SetFrameEx(float frame, float blend){
    unk168 = true;
    SetFrame(frame, blend);
    unk168 = false;
}

void BandCamShot::AnimateShot(float frame, float blend){
    for(ObjVector<Target>::iterator it = mTargets.begin(); it != mTargets.end(); ++it);
    CamShot::SetFrame(frame, blend);
}

void BandCamShot::Store(){
    for(ObjVector<Target>::iterator it = mTargets.begin(); it != mTargets.end(); ++it){
        (*it).Store(this);
    }
}

void BandCamShot::FreezeChar(Character* c, bool b){
    c->mFrozen = b;
}

DataNode BandCamShot::AddTarget(DataArray* target){
    MILO_ASSERT(target->Size() != 2, 0x3AD);
    mTargets.push_back(Target(this));
    mTargets.back().mTarget = target->Sym(2);
    mTargets.back().Store(this);
    return DataNode(0);
}

float BandCamShot::GetTotalDuration(){
    float sum = Duration();
    std::list<BandCamShot*> shots;
    ListNextShots(shots);
    for(std::list<BandCamShot*>::iterator it = shots.begin(); it != shots.end(); ++it){
        sum += (*it)->Duration();
    }
    return sum;
}

int BandCamShot::GetNumShots(){
    int size;
    {
        std::list<BandCamShot*> shots;
        ListNextShots(shots);
        size = shots.size();
    }
    return size + 1;
}

float BandCamShot::GetTotalDurationSeconds(){
    float secs = CamShot::GetDurationSeconds();
    std::list<BandCamShot*> shots;
    ListNextShots(shots);
    for(std::list<BandCamShot*>::iterator it = shots.begin(); it != shots.end(); ++it){
        secs += (*it)->CamShot::GetDurationSeconds();
    }
    return secs;
}

void BandCamShot::CheckNextShots(){
    std::list<BandCamShot*> shots;
    ListNextShots(shots);
}

float BandCamShot::EndFrame(){ return GetTotalDuration(); }

bool BandCamShot::CheckShotStarted(){
    return !unk168 && CamShot::CheckShotStarted();
}

bool BandCamShot::CheckShotOver(float f){
    return !unk168 && f >= unk164 && CamShot::CheckShotOver(f);
}

void BandCamShot::Target::Store(BandCamShot* shot){
    if(!mTarget.Null()){
        std::list<BandCamShot::TargetCache>::iterator it = shot->CreateTargetCache(mTarget);
        if(it->unk4){
            mXfm.Set(it->unkc);
            shot->DeleteTargetCache(it);
        }
    }
}

void BandCamShot::Target::UpdateTarget(Symbol s, BandCamShot* shot){
    if(mTarget != s){
        mTarget = s;
        mAnimGroup = Symbol("");
    }
    Store(shot);
}

#pragma push
#pragma pool_data off
BEGIN_CUSTOM_PROPSYNC(BandCamShot::Target)
    SYNC_PROP_SET(target, o.mTarget, o.UpdateTarget(_val.Sym(0), gBandCamShotOwner))
    SYNC_PROP_MODIFY(anim_group, o.mAnimGroup, gBandCamShotOwner->StartAnim())
    SYNC_PROP(fast_forward, o.mFastForward)
    SYNC_PROP(forward_event, o.mForwardEvent)
    {
        static Symbol _s("force_lod");
        if(sym == _s){
            if(_op == kPropSet) o.mForceLod = _val.Int(0);
            else _val = DataNode(o.mForceLod);
            return true;
        }
    }
    {
        static Symbol _s("teleport");
        if(sym == _s){
            if(_op == kPropSet) o.mTeleport = _val.Int(0);
            else _val = DataNode(o.mTeleport);
            return true;
        }
    }
    {
        static Symbol _s("return");
        if(sym == _s){
            if(_op == kPropSet) o.mReturn = _val.Int(0);
            else _val = DataNode(o.mReturn);
            return true;
        }
    }
    {
        static Symbol _s("self_shadow");
        if(sym == _s){
            if(_op == kPropSet) o.mSelfShadow = _val.Int(0);
            else _val = DataNode(o.mSelfShadow);
            return true;
        }
    }
    {
        static Symbol _s("hide");
        if(sym == _s){
            if(_op == kPropSet) o.mHide = _val.Int(0);
            else _val = DataNode(o.mHide);
            return true;
        }
    }
    SYNC_PROP(env_override, o.mEnvOverride)
    SYNC_PROP_SET(target_ptr, gBandCamShotOwner->FindTarget(o.mTarget, false), )
END_CUSTOM_PROPSYNC
#pragma pop

BEGIN_PROPSYNCS(BandCamShot)
    gBandCamShotOwner = this;
    SYNC_PROP(targets, mTargets)
    SYNC_PROP(zero_time, mZeroTime)
    SYNC_PROP(min_time, mMinTime)
    SYNC_PROP(max_time, mMaxTime)
    SYNC_PROP_MODIFY_ALT(next_shots, mNextShots, CheckNextShots(); ResetNextShot(); )
    SYNC_PROP(anims_during_nextshots, mAnimsDuringNextShots)
    SYNC_PROP_SET(total_duration, GetTotalDuration(), )
    SYNC_SUPERCLASS(CamShot)
END_PROPSYNCS

BEGIN_HANDLERS(BandCamShot)
    HANDLE(test_delta, OnTestDelta)
    HANDLE_EXPR(total_duration_seconds, GetTotalDurationSeconds())
    HANDLE_ACTION(store, Store())
    HANDLE_ACTION(view, View())
    HANDLE_ACTION(freeze, Freeze())
    HANDLE_ACTION(view_freeze, ViewFreeze())
    HANDLE(add_target, AddTarget)
    HANDLE_EXPR(initial_shot, InitialShot())
    HANDLE_EXPR(num_shots, GetNumShots())
    HANDLE(allowable_next_shots, OnAllowableNextShots)
    HANDLE(list_all_next_shots, OnListAllNextShots)
    HANDLE(list_targets, OnListTargets)
    HANDLE(list_anim_groups, OnListAnimGroups)
    HANDLE_SUPERCLASS(CamShot)
    HANDLE_CHECK(0x4A4)
END_HANDLERS

DataNode BandCamShot::OnListTargets(const DataArray* da){
    DataNode handled = HandleType(list_targets_msg);
    if(handled.Type() != kDataUnhandled){
        return DataNode(handled.Array(0), kDataArray);
    }
    else return ObjectList(Dir(), "Trans", true);
}

DataNode BandCamShot::OnListAnimGroups(const DataArray* da){
    Symbol sym = da->Sym(2);
    static Message m("list_anim_groups", DataNode(0));
    m[0] = DataNode(sym);
    DataNode handled = HandleType(m);
    if(handled.Type() != kDataUnhandled){
        return DataNode(handled.Array(0), kDataArray);
    }
    else {
        Character* c = dynamic_cast<Character*>(FindTarget(sym, false));
        if(c){
            bool usechardir = false;
            if(c->GetDriver() && c->GetDriver()->ClipDir()) usechardir = true;
            ObjectDir* thedir;
            if(usechardir){
                thedir = c->GetDriver()->ClipDir();
            }
            else thedir = Dir();
            return ObjectList(thedir, "CharClipGroup", true);
        }
        else {
            handled = DataNode(new DataArray(1), kDataArray);
            handled.Array(0)->Node(0) = DataNode(Symbol());
            return DataNode(handled);
        }
    }
}

DataNode BandCamShot::OnAllowableNextShots(const DataArray* da){
    DataArrayPtr ptr;
    for(ObjDirItr<BandCamShot> it(Dir(), true); it != 0; ++it){
        if(mNextShots.find(it) != mNextShots.end()){
            std::list<BandCamShot*> shots;
            ListNextShots(shots);
            // more
        }
    }
    static DataNode& milo_prop_path = DataVariable("milo_prop_path");
    if(milo_prop_path.Type() == kDataArray){
        if(milo_prop_path.Array(0)->Size() == 2){
            ObjPtrList<BandCamShot, ObjectDir>::iterator it = mNextShots.begin();
            it += milo_prop_path.Array(0)->Int(1);
            ptr->Insert(ptr->Size(), DataNode(*it));
        }
    }
    return DataNode(ptr);
}

DataNode BandCamShot::OnListAllNextShots(const DataArray* da){
    std::list<BandCamShot*> shots;
    ListNextShots(shots);
    DataArrayPtr ptr;
    for(std::list<BandCamShot*>::iterator it = shots.begin(); it != shots.end(); ++it){
        ptr->Insert(ptr->Size(), DataNode(*it));
    }
    return DataNode(ptr);
}