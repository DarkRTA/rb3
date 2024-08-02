#include "char/CharEyes.h"
#include "char/CharFaceServo.h"
#include "char/CharWeightSetter.h"
#include "char/CharLookAt.h"
#include "char/CharInterest.h"
#include "obj/DataUtl.h"
#include "obj/Task.h"
#include "utl/Symbols.h"

bool CharEyes::sDisableEyeDart;
bool CharEyes::sDisableEyeJitter;
bool CharEyes::sDisableInterestObjects;
bool CharEyes::sDisableProceduralBlink;
bool CharEyes::sDisableEyeClamping;

INIT_REVS(CharEyes)

CharEyes::EyeDesc::EyeDesc(Hmx::Object* o) : mEye(o, 0), mUpperLid(o, 0), mLowerLid(o, 0), mLowerLidBlink(o, 0), mUpperLidBlink(o, 0) {

}

CharEyes::EyeDesc::EyeDesc(const CharEyes::EyeDesc& desc) : mEye(desc.mEye), mUpperLid(desc.mUpperLid), mLowerLid(desc.mLowerLid),
    mLowerLidBlink(desc.mLowerLidBlink), mUpperLidBlink(desc.mUpperLidBlink) {

}

CharEyes::EyeDesc& CharEyes::EyeDesc::operator=(const CharEyes::EyeDesc& desc){
    mEye = desc.mEye;
    mUpperLid = desc.mUpperLid;
    mLowerLid = desc.mLowerLid;
    mUpperLidBlink = desc.mUpperLidBlink;
    mLowerLidBlink = desc.mLowerLidBlink;
    return *this;
}

void CharEyes::CharInterestState::ResetState(){ unkc = -1.0f; }

CharEyes::CharInterestState::CharInterestState(Hmx::Object* o) : mInterest(o, 0) {
    ResetState();
}

CharEyes::CharInterestState::CharInterestState(const CharEyes::CharInterestState& state) : mInterest(state.mInterest) {
    ResetState();
}

CharEyes::CharInterestState& CharEyes::CharInterestState::operator=(const CharEyes::CharInterestState& state){
    mInterest = state.mInterest;
    return *this;
}

void CharEyes::CharInterestState::BeginRefractoryPeriod(){
    unkc = TheTaskMgr.Seconds(TaskMgr::b);
}

bool CharEyes::CharInterestState::IsInRefractoryPeriod(){
    if(!mInterest || unkc < 0.0) return false;
    else {
        float secs = TheTaskMgr.Seconds(TaskMgr::b) - unkc;
        if(secs < mInterest->mRefractoryPeriod) return true;
        else return false;
    }
}

float CharEyes::CharInterestState::RefractoryTimeRemaining(){
    if(!mInterest || unkc < 0.0) return 0.0f;
    else {
        float secs = TheTaskMgr.Seconds(TaskMgr::b) - unkc;
        if(secs < mInterest->mRefractoryPeriod) return mInterest->mRefractoryPeriod - secs;
        else return 0.0f;
    }
}

CharEyes::CharEyes() : mEyes(this), mInterests(this), mFaceServo(this, 0), mCamWeight(this, 0), mViewDirection(this, 0), mHeadLookAt(this, 0),
    unkc8(this, 0), unkd4(this, 0) {

}

CharEyes::~CharEyes(){

}

void CharEyes::Exit(){
    unkd4 = 0;
    unke0 = -1;
    mInterests.clear();
    for(ObjVector<EyeDesc>::iterator it = mEyes.begin(); it != mEyes.end(); ++it){
        it->mEye->Exit();
    }
    RndPollable::Exit();
}

void CharEyes::ClearAllInterestObjects(){ mInterests.clear(); }

// fn_804CCF70
RndTransformable* CharEyes::GetHead(){
    if(mViewDirection) return mViewDirection;
    else if(!mEyes.empty() && mEyes[0].mEye){
        RndTransformable* src = mEyes[0].mEye->GetSource();
        if(src) return src->TransParent();
    }
    return 0;
}

CharInterest* CharEyes::GetCurrentInterest(){
    if(unkd4) return unkd4;
    if(unkc8) return unkc8;
    return 0;
}

void CharEyes::ForceBlink(){
    unk13c = true;
    unk140 = TheTaskMgr.Seconds(TaskMgr::b);
    unk144++;
}

void CharEyes::ListPollChildren(std::list<RndPollable*>& plist) const {
    for(ObjVector<EyeDesc>::const_iterator it = mEyes.begin(); it != mEyes.end(); ++it){
        plist.push_back((*it).mEye);
    }
}

void CharEyes::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    for(ObjVector<CharInterestState>::iterator it = mInterests.begin(); it != mInterests.end(); ++it){
        ObjectDir* dir = (*it).mInterest->Dir();
        if(dir == Dir()){
            changedBy.push_back((*it).mInterest);
        }
    }
    if(!mEyes.empty()){
        changedBy.push_back(GetHead());
        change.push_back(GetTarget());
    }
    if(mHeadLookAt) changedBy.push_back(mHeadLookAt);
    if(mFaceServo) changedBy.push_back(mFaceServo);
}

SAVE_OBJ(CharEyes, 0x575)

BinStream& operator>>(BinStream& bs, CharEyes::EyeDesc& desc){
    bs >> desc.mEye;
    bs >> desc.mUpperLid;
    if(CharEyes::gRev > 6) bs >> desc.mLowerLid;
    if(CharEyes::gRev > 0xF){
        bs >> desc.mUpperLidBlink;
        bs >> desc.mLowerLidBlink;
    }
    return bs;
}

BinStream& operator>>(BinStream& bs, CharEyes::CharInterestState& state){
    bs >> state.mInterest;
    return bs;
}

BEGIN_LOADS(CharEyes)
    LOAD_REVS(bs)
    ASSERT_REVS(0x12, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    if(gRev > 5) LOAD_SUPERCLASS(CharWeightable)
    if(gRev > 4) bs >> mEyes;
    else {
        ObjPtrList<CharLookAt, ObjectDir> pList(this, kObjListNoNull);
        bs >> pList;
        mEyes.resize(pList.size());
        int idx = 0;
        for(ObjPtrList<CharLookAt, ObjectDir>::iterator it = pList.begin(); it != pList.end(); ++it){
            mEyes[idx].mEye = *it;
            mEyes[idx].mUpperLid = 0;
            mEyes[idx].mLowerLid = 0;
            mEyes[idx].mLowerLidBlink = 0;
            mEyes[idx].mUpperLidBlink = 0;
            idx++;
        }
    }
    if(gRev - 3 <= 1U){
        ObjPtr<RndTransformable, ObjectDir> tPtr(this, 0);
        bs >> tPtr;
    }
    mInterests.clear();
    if(gRev - 4 < 5U){
        ObjPtr<RndTransformable, ObjectDir> tPtr(this, 0);
        int cnt;
        bs >> cnt;
        for(int i = 0; i < cnt; i++){
            bs >> tPtr;
            bs.ReadInt();
        }
    }
    else if(gRev > 8) bs >> mInterests;
    if(gRev > 4) bs >> mFaceServo;
    else mFaceServo = 0;
    if(gRev > 7) bs >> mCamWeight;
    if(gRev > 9) bs >> mDefaultFilterFlags;
    if(gRev > 10) bs >> mViewDirection;
    if(gRev > 0xB) bs >> mHeadLookAt;
    if(gRev > 0xC) bs >> mMaxExtrapolation;
    if(gRev > 0xD) bs >> mMinTargetDist;
    if(gRev > 0xE){
        bs >> mUpperLidTrackUp;
        bs >> mUpperLidTrackDown;
        bs >> mLowerLidTrackUp;
        if(gRev < 0x11){
            bs.ReadInt();
            bs >> mLowerLidTrackDown;
            bs.ReadInt();
        }
        else bs >> mLowerLidTrackDown;
    }
    if(gRev > 0x11) bs >> mLowerLidTrackRotate;
END_LOADS

BEGIN_COPYS(CharEyes)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(CharWeightable)
    CREATE_COPY(CharEyes)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mEyes)
        COPY_MEMBER(mInterests)
        COPY_MEMBER(mFaceServo)
        COPY_MEMBER(unka4)
        COPY_MEMBER(unka8)
        COPY_MEMBER(unkac)
        COPY_MEMBER(unkb4)
        COPY_MEMBER(mCamWeight)
        COPY_MEMBER(mDefaultFilterFlags)
        COPY_MEMBER(mViewDirection)
        COPY_MEMBER(mHeadLookAt)
        COPY_MEMBER(mMaxExtrapolation)
        COPY_MEMBER(mMinTargetDist)
        COPY_MEMBER(mUpperLidTrackUp)
        COPY_MEMBER(mUpperLidTrackDown)
        COPY_MEMBER(mLowerLidTrackUp)
        COPY_MEMBER(mLowerLidTrackDown)
        COPY_MEMBER(mLowerLidTrackRotate)
    END_COPYING_MEMBERS
END_COPYS

DataNode CharEyes::OnToggleForceFocus(DataArray* da){
    if(unkd4) SetFocusInterest(0, 0);
    else SetFocusInterest(unkc8, 0);
    return DataNode(0);
}

DataNode CharEyes::OnToggleInterestOverlay(DataArray* da){
    ToggleInterestsDebugOverlay();
    return DataNode(0);
}

void CharEyes::ToggleInterestsDebugOverlay(){
    RndOverlay* o = unk9c;
    if(!o) return;
    o->mShowing = o->mShowing == false;
    o->mTimer.Restart();
}

BEGIN_HANDLERS(CharEyes)
    HANDLE(add_interest, OnAddInterest)
    HANDLE_ACTION(force_blink, ForceBlink())
    HANDLE(toggle_force_focus, OnToggleForceFocus)
    HANDLE(toggle_interest_overlay, OnToggleInterestOverlay)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x660)
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(CharEyes::EyeDesc)
    SYNC_PROP(eye, o.mEye)
    SYNC_PROP(upper_lid, o.mUpperLid)
    SYNC_PROP(lower_lid, o.mLowerLid)
    SYNC_PROP(upper_lid_blink, o.mUpperLidBlink)
    SYNC_PROP(lower_lid_blink, o.mLowerLidBlink)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(CharEyes::CharInterestState)
    SYNC_PROP(interest, o.mInterest)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(CharEyes)
    SYNC_PROP(eyes, mEyes)
    SYNC_PROP(view_direction, mViewDirection)
    SYNC_PROP(interests, mInterests)
    SYNC_PROP(face_servo, mFaceServo)
    SYNC_PROP(camera_weight, mCamWeight)
    {
        static Symbol _s("default_interest_categories");
        if(sym == _s){
            if(++_i < _prop->Size()){
                DataNode& node = _prop->Node(_i);
                int res = 0;
                switch(node.Type()){
                    case kDataInt:
                        res = node.Int(0);
                        break;
                    case kDataSymbol:
                        const char* bitstr = node.Sym(0).Str();
                        if(strncmp("BIT_", bitstr, 4) != 0){
                            MILO_FAIL("%s does not begin with BIT_", bitstr);
                        }
                        Symbol bitsym(bitstr + 4);
                        DataArray* macro = DataGetMacro(bitsym);
                        if(!macro){
                            MILO_FAIL("PROPERTY_BITFIELD %s could not find macro %s", _s, bitsym);
                        }
                        res = macro->Int(0);
                        break;
                    default:
                        MILO_ASSERT(0, 0x67B);
                        break;
                }
                MILO_ASSERT(_op <= kPropInsert, 0x67B);
                if(_op == kPropGet){
                    int final = mDefaultFilterFlags & res;
                    _val = DataNode(final > 0);
                }
                else {
                    if(_val.Int(0) != 0) mDefaultFilterFlags |= res;
                    else mDefaultFilterFlags &= ~res;
                }
                return true;
            }
            return PropSync(mDefaultFilterFlags, _val, _prop, _i, _op);
        }
    }
    SYNC_PROP(head_lookat, mHeadLookAt)
    SYNC_PROP(max_extrapolation, mMaxExtrapolation)
    SYNC_PROP(disable_eye_dart, sDisableEyeDart)
    SYNC_PROP(disable_eye_jitter, sDisableEyeJitter)
    SYNC_PROP(disable_interest_objects, sDisableInterestObjects)
    SYNC_PROP(disable_procedural_blink, sDisableProceduralBlink)
    SYNC_PROP(disable_eye_clamping, sDisableEyeClamping)
    {
        static Symbol _s("interest_filter_testing");
        if(sym == _s){
            if(++_i < _prop->Size()){
                DataNode& node = _prop->Node(_i);
                int res = 0;
                switch(node.Type()){
                    case kDataInt:
                        res = node.Int(0);
                        break;
                    case kDataSymbol:
                        const char* bitstr = node.Sym(0).Str();
                        if(strncmp("BIT_", bitstr, 4) != 0){
                            MILO_FAIL("%s does not begin with BIT_", bitstr);
                        }
                        Symbol bitsym(bitstr + 4);
                        DataArray* macro = DataGetMacro(bitsym);
                        if(!macro){
                            MILO_FAIL("PROPERTY_BITFIELD %s could not find macro %s", _s, bitsym);
                        }
                        res = macro->Int(0);
                        break;
                    default:
                        MILO_ASSERT(0, 0x684);
                        break;
                }
                MILO_ASSERT(_op <= kPropInsert, 0x684);
                if(_op == kPropGet){
                    int final = mInterestFilterFlags & res;
                    _val = DataNode(final > 0);
                }
                else {
                    if(_val.Int(0) != 0) mInterestFilterFlags |= res;
                    else mInterestFilterFlags &= ~res;
                }
                return true;
            }
            return PropSync(mInterestFilterFlags, _val, _prop, _i, _op);
        }
    }
    SYNC_PROP(min_target_dist, mMinTargetDist)
    SYNC_PROP(ulid_track_up, mUpperLidTrackUp)
    SYNC_PROP(ulid_track_down, mUpperLidTrackDown)
    SYNC_PROP(llid_track_up, mLowerLidTrackUp)
    SYNC_PROP(llid_track_down, mLowerLidTrackDown)
    SYNC_PROP(llid_track_rotate, mLowerLidTrackRotate)
    SYNC_SUPERCLASS(CharWeightable)
END_PROPSYNCS