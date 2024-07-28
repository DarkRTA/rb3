#include "rndobj/PropAnim.h"
#include "utl/STLHelpers.h"
#include "obj/Utl.h"

INIT_REVS(RndPropAnim)

RndPropAnim::RndPropAnim() : mLastFrame(0.0f), mInSetFrame(0), mLoop(0) {

}

RndPropAnim::~RndPropAnim(){
    RemoveKeys();
}

void RndPropAnim::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    for(std::vector<PropKeys*>::iterator it = mPropKeys.begin(); it != mPropKeys.end(); it){
        PropKeys* cur = *it;
        if(this == from){
            if(!to){
                it = mPropKeys.erase(it);
                delete cur;
            }
            else {
                cur->SetTarget(to);
                it++;
            }
        }
        else it++;
    }
}

SAVE_OBJ(RndPropAnim, 0x43);

BEGIN_LOADS(RndPropAnim)
    LOAD_REVS(bs)
    ASSERT_REVS(0xD, 0)
    SetPropKeysRev(gRev);
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndAnimatable)
    ObjOwnerPtr<Hmx::Object, ObjectDir> pPtr(this, 0);
    mLastFrame = mFrame;
    RemoveKeys();
    if(gRev < 7){
        LoadPre7(bs);
        return;
    }
    else {
        int count;
        bs >> count;
        for(int i = 0; i < count; i++){
            int num;
            bs >> num;
            AddKeys(0, 0, (PropKeys::AnimKeysType)num)->Load(bs);
        }
        if(gRev > 0xB) bs >> mLoop;
    }
END_LOADS

BEGIN_COPYS(RndPropAnim)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    mLastFrame = mFrame;
    RemoveKeys();
    CREATE_COPY(RndPropAnim)
    BEGIN_COPYING_MEMBERS
        for(std::vector<PropKeys*>::iterator it = mPropKeys.begin(); it != mPropKeys.end(); it++){
            PropKeys* cur = *it;
            AddKeys(cur->mTarget.Ptr(), cur->mProp, (PropKeys::AnimKeysType)cur->mKeysType)->Copy(cur);
        }
        COPY_MEMBER(mLoop)
    END_COPYING_MEMBERS
END_COPYS

float RndPropAnim::StartFrame(){
    float frame = 0.0f;
    for(std::vector<PropKeys*>::iterator it = mPropKeys.begin(); it != mPropKeys.end(); it++){
        MinEq(frame, (*it)->StartFrame());
    }
    return frame;
}

float RndPropAnim::EndFrame(){
    float frame = 0.0f;
    for(std::vector<PropKeys*>::iterator it = mPropKeys.begin(); it != mPropKeys.end(); it++){
        MaxEq(frame, (*it)->EndFrame());
    }
    return frame;
}

void RndPropAnim::AdvanceFrame(float frame){
    if(mLoop){
        float diff = EndFrame() - StartFrame();
        float f1 = 0.0f;
    }
}

void RndPropAnim::SetKey(float frame){
    for(std::vector<PropKeys*>::iterator it = mPropKeys.begin(); it != mPropKeys.end(); it++){
        (*it)->SetKey(frame);
    }
}

void RndPropAnim::StartAnim(){
    for(std::vector<PropKeys*>::iterator it = mPropKeys.begin(); it != mPropKeys.end(); it++){
        (*it)->mLastKeyFrameIndex = -2;
    }
}

PropKeys* RndPropAnim::GetKeys(const Hmx::Object* o, DataArray* da){
    if(!da || !o) return 0;
    for(std::vector<PropKeys*>::iterator it = mPropKeys.begin(); it != mPropKeys.end(); it++){
        PropKeys* cur = *it;
        if(cur->mTarget.Ptr() == o && PathCompare(da, cur->mProp)) return cur;
    }
    return 0;
}

PropKeys* RndPropAnim::AddKeys(Hmx::Object* o, DataArray* da, PropKeys::AnimKeysType ty){
    PropKeys* theKeys = GetKeys(o, da);
    if(theKeys){
        switch(ty){
            case PropKeys::kFloat:
                theKeys = new FloatKeys(this, o);
                break;
            case PropKeys::kColor:
                theKeys = new ColorKeys(this, o);
                break;
            case PropKeys::kObject:
                theKeys = new ObjectKeys(this, o);
                break;
            case PropKeys::kBool:
                theKeys = new BoolKeys(this, o);
                break;
            case PropKeys::kQuat:
                theKeys = new QuatKeys(this, o);
                break;
            case PropKeys::kVector3:
                theKeys = new Vector3Keys(this, o);
                break;
            case PropKeys::kSymbol:
                theKeys = new SymbolKeys(this, o);
                break;
            default:
                MILO_WARN("Unable to create animation for keysType");
                return 0;
        }
        if(da){
            DataNode node(da, kDataArray);
            theKeys->SetProp(node);
        }
        mPropKeys.push_back(theKeys);
    }
    return theKeys;
}

bool RndPropAnim::ChangePropPath(Hmx::Object* o, DataArray* a1, DataArray* a2){
    if(!a2 || a2->Size() == 0) return RemoveKeys(o, a1);
    else {
        PropKeys** keys = FindKeys(o, a1);
        if(keys != mPropKeys.end()) {
            DataNode node(a2, kDataArray);
            (*keys)->SetProp(node);
            return true;
        }
        else return false;
    }
}

void RndPropAnim::RemoveKeys(){
    DeleteRange(mPropKeys.begin(), mPropKeys.end());
    mPropKeys.clear();
}

PropKeys** RndPropAnim::FindKeys(Hmx::Object* o, DataArray* da){
    std::vector<PropKeys*>::iterator it = mPropKeys.begin();
    for(; it != mPropKeys.end(); it++){
        if(!da && !(*it)->mProp || (*it)->mTarget.Ptr() == o && PathCompare(da, (*it)->mProp)) return it;
    }
    return it;
}

bool RndPropAnim::RemoveKeys(Hmx::Object* o, DataArray* da){
    PropKeys** keys = FindKeys(o, da);
    if(keys == mPropKeys.end()) return false;
    else {
        PropKeys* cur = *keys;
        mPropKeys.erase(keys);
        delete cur;
        return true;
    }
}

bool RndPropAnim::HasKeys(Hmx::Object* o, DataArray* da){
    return FindKeys(o, da) != mPropKeys.end();
}

void RndPropAnim::SetKey(Hmx::Object* o, DataArray* da, float f){
    PropKeys** keys = FindKeys(o, da);
    if(keys != mPropKeys.end()){
        PropKeys* cur = *keys;
        cur->SetKey(f);
    }
}

    // std::vector<PropKeys*> mPropKeys; // 0x10
    // float mLastFrame; // 0x18
    // bool mInSetFrame; // 0x1c
    // bool mLoop; // 0x1d