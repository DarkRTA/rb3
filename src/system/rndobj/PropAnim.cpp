#include "rndobj/PropAnim.h"
#include "rndobj/EventTrigger.h"
#include "utl/STLHelpers.h"
#include "obj/Utl.h"
#include "utl/Symbols.h"

INIT_REVS(RndPropAnim)
DataNode sKeyReplace;
float sFrameReplace;
bool sReplaceKey;
bool sReplaceFrame;

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

// fn_80631D38
void RndPropAnim::LoadPre7(BinStream& bs){
    ObjOwnerPtr<Hmx::Object, ObjectDir> objPtr(this, 0);
    if(gRev < 2) bs >> objPtr;
    int count;
    bs >> count;
    for(int i = 0; i < count; i++){
        DataArray* arr = 0;
        PropKeys::AnimKeysType ty = PropKeys::kFloat;
        Keys<float, float> floatKeys;
        Keys<Hmx::Color, Hmx::Color> colorKeys;
        ObjKeys objKeys(this);
        Keys<bool, bool> boolKeys;
        Keys<Hmx::Quat, Hmx::Quat> quatKeys;
        if(gRev >= 2) bs >> objPtr;
        if(gRev < 1){
            Symbol sym;
            bs >> sym;
            arr = DataArrayPtr(DataNode(sym));
        }
        else bs >> arr;
        if(gRev < 3) bs >> floatKeys;
        else {
            int animtype;
            bs >> animtype;
            ty = (PropKeys::AnimKeysType)animtype;
            bs >> floatKeys;
            bs >> colorKeys;
            Hmx::Object* oldowner = ObjectStage::sOwner;
            if(gRev > 3){
                ObjectStage::sOwner = this;
                bs >> objKeys;
            }
            ObjectStage::sOwner = oldowner;
            if(gRev > 4) bs >> boolKeys;
            if(gRev > 5) bs >> quatKeys;
        }
        PropKeys* addedKeys = AddKeys(objPtr.Ptr(), arr, ty);
        if(arr) arr->Release();
        switch(ty){
            case PropKeys::kFloat:
                addedKeys->AsFloatKeys() = floatKeys;
                break;
            case PropKeys::kColor:
                addedKeys->AsColorKeys() = colorKeys;
                break;
            case PropKeys::kObject:
                addedKeys->AsObjectKeys() = objKeys;
                break;
            case PropKeys::kBool:
                addedKeys->AsBoolKeys() = boolKeys;
                break;
            case PropKeys::kQuat:
                addedKeys->AsQuatKeys() = quatKeys;
                break;
            default: break;
        }
    }
}

BEGIN_COPYS(RndPropAnim)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    mLastFrame = GetFrame();
    RemoveKeys();
    CREATE_COPY(RndPropAnim)
    BEGIN_COPYING_MEMBERS
        for(std::vector<PropKeys*>::iterator it = mPropKeys.begin(); it != mPropKeys.end(); it++){
            PropKeys* cur = *it;
            AddKeys(cur->mTarget.Ptr(), cur->mProp, (PropKeys::AnimKeysType)cur->mKeysType)->Copy(*it);
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

// fn_806326EC
void RndPropAnim::AdvanceFrame(float frame){
    if(mLoop){
        frame = ModRange(StartFrame(), EndFrame(), frame);
    }
    RndAnimatable::SetFrame(frame, 1.0f);
}

// fn_80632790
void RndPropAnim::SetFrame(float frame, float blend){
    if(!mInSetFrame){
        mInSetFrame = true;
        AdvanceFrame(frame);
        float theframe = mFrame;
        for(std::vector<PropKeys*>::iterator it = mPropKeys.begin(); it != mPropKeys.end(); it++){
            if((*it)->mPropExceptionID == PropKeys::kDirEvent){
                ObjKeys& objkeys = (*it)->AsObjectKeys();
                for(int i = 0; i < objkeys.size(); i++){
                    if(objkeys[i].frame > theframe) break;
                    if(objkeys[i].frame >= mLastFrame && mLastFrame != theframe){
                        EventTrigger* trig = dynamic_cast<EventTrigger*>(objkeys[i].value.Ptr());
                        if(trig) trig->Trigger();
                    }
                }
            }
            (*it)->SetFrame(theframe, blend);
        }
        mLastFrame = theframe;
        mInSetFrame = false;
    }
}

void RndPropAnim::SetKey(float frame){
    for(std::vector<PropKeys*>::iterator it = mPropKeys.begin(); it != mPropKeys.end(); it++){
        (*it)->SetKey(frame);
    }
}

void RndPropAnim::StartAnim(){
    for(std::vector<PropKeys*>::iterator it = mPropKeys.begin(); it != mPropKeys.end(); it++){
        (*it)->ResetLastKeyFrameIndex();
    }
}

PropKeys* RndPropAnim::GetKeys(const Hmx::Object* obj, DataArray* prop){
    if(!prop || !obj) return 0;
    for(std::vector<PropKeys*>::iterator it = mPropKeys.begin(); it != mPropKeys.end(); it++){
        PropKeys* cur = *it;
        if(cur->mTarget.Ptr() == obj && PathCompare(prop, cur->mProp)) return cur;
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
    DeleteAll(mPropKeys);
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

void RndPropAnim::SetKeyVal(Hmx::Object* o, DataArray* da, float frame, const DataNode& node, bool unique){
    PropKeys** keys = FindKeys(o, da);
    if(keys != mPropKeys.end()){
        PropKeys* cur = *keys;
        switch(cur->mKeysType){
            case PropKeys::kFloat:
                cur->AsFloatKeys().Add(node.Float(), frame, unique);
                break;
            case PropKeys::kColor:
                cur->AsColorKeys().Add(Hmx::Color(node.Int()), frame, unique);
                break;
            case PropKeys::kObject:
                cur->AsObjectKeys().Add(node.GetObj(), frame, unique);
                break;
            case PropKeys::kBool:
                cur->AsBoolKeys().Add(node.Int(), frame, unique);
                break;
            case PropKeys::kSymbol:
                cur->AsSymbolKeys().Add(node.Sym(), frame, unique);
                break;
            case PropKeys::kVector3:
                cur->AsVector3Keys().Add(
                    Vector3(node.Array()->Float(0), node.Array()->Float(1), node.Array()->Float(2)),
                    frame, unique);
                break;
            case PropKeys::kQuat:
                cur->AsQuatKeys().Add(
                    Hmx::Quat(node.Array()->Float(0), node.Array()->Float(1), node.Array()->Float(2), node.Array()->Float(3)),
                    frame, unique);
                break;
            default:
                String text;
                text << "Unable to set key value pair for ";
                da->Print(text, kDataArray, true);
                text << " value is ";
                node.Print(text, true);
                MILO_WARN(text.c_str());
                break;
        }
    }
}

PropKeys::AnimKeysType RndPropAnim::AnimKeysType(Hmx::Object* o, DataArray* da){
    PropKeys** keys = FindKeys(o, da);
    if(keys != mPropKeys.end()){
        PropKeys* cur = *keys;
        return (PropKeys::AnimKeysType)cur->mKeysType;
    }
    else return PropKeys::kFloat;
}

PropKeys::Interpolation RndPropAnim::InterpType(Hmx::Object* o, DataArray* da){
    PropKeys** keys = FindKeys(o, da);
    if(keys != mPropKeys.end()){
        PropKeys* cur = *keys;
        return (PropKeys::Interpolation)cur->mInterpolation;
    }
    else return PropKeys::kStep;
}

void RndPropAnim::SetInterpType(Hmx::Object* obj, DataArray* prop, PropKeys::Interpolation iter){
    PropKeys** keys = FindKeys(obj, prop);
    if(keys != mPropKeys.end()){
        PropKeys* cur = *keys;
        cur->mInterpolation = iter;
    }
}

Symbol RndPropAnim::InterpHandler(Hmx::Object* obj, DataArray* prop){
    PropKeys** keys = FindKeys(obj, prop);
    if(keys != mPropKeys.end()){
        PropKeys* cur = *keys;
        if(cur->mPropExceptionID == PropKeys::kHandleInterp)
        return cur->InterpHandler();
    }
    return Symbol();
}

void RndPropAnim::SetInterpHandler(Hmx::Object* obj, DataArray* prop, Symbol handler){
    PropKeys** keys = FindKeys(obj, prop);
    if(keys != mPropKeys.end()){
        (*keys)->SetInterpHandler(handler);
    }
}

void RndPropAnim::Print(){
    TextStream& ts = TheDebug;
    int idx = 0;
    for(std::vector<PropKeys*>::iterator it = mPropKeys.begin(); it != mPropKeys.end(); it++){
        ts << "   Keys " << idx << "\n";
        (*it)->Print();
        idx++;
    }
}

DataNode RndPropAnim::ForEachTarget(const DataArray* da){
    ObjPtrList<Hmx::Object, ObjectDir> objList(this, kObjListNoNull);
    const char* arrstr = da->Str(2);
    for(std::vector<PropKeys*>::iterator it = mPropKeys.begin(); it != mPropKeys.end(); ++it){
        bool b = true;
        PropKeys* cur = *it;
        if(arrstr != gNullStr){
            if(cur->mTarget->ClassName() != arrstr) b = false;
        }
        if(b){
            objList.push_back(cur->mTarget);
        }
    }
    DataNode* var = da->Var(3);
    DataNode node(*var);
    for(ObjPtrList<Hmx::Object, ObjectDir>::iterator it = objList.begin(); it != objList.end(); ++it){
        *var = DataNode(*it);
        for(int i = 4; i < da->Size(); i++){
            da->Command(i)->Execute();
        }
    }
    *var = node;
    return DataNode(0);
}

DataNode RndPropAnim::OnReplaceKeyframe(DataArray* da){
    sReplaceKey = true;
    sKeyReplace = da->Evaluate(2);
    return DataNode(0);
}

DataNode RndPropAnim::OnReplaceFrame(DataArray* da){
    sReplaceFrame = true;
    sFrameReplace = da->Float(2);
    return DataNode(0);
}

DataNode RndPropAnim::OnGetIndexFromFrame(const DataArray* da){
    Hmx::Object* obj = da->GetObj(2);
    DataArray* prop = da->Array(3);
    float f = da->Float(4);
    PropKeys* keys = GetKeys(obj, prop);
    if(!keys) return DataNode(-1);
    else return ValueFromFrame(keys, f, &DataNode(0));
}

DataNode RndPropAnim::OnGetFrameFromIndex(const DataArray* da){
    Hmx::Object* obj = da->GetObj(2);
    DataArray* prop = da->Array(3);
    int i = da->Int(4);
    float frame = -1.0f;
    PropKeys* keys = GetKeys(obj, prop);
    if(!keys) return DataNode(frame);
    else {
        keys->FrameFromIndex(i, frame);
        return DataNode(frame);
    }
}

DataNode RndPropAnim::OnGetValueFromIndex(const DataArray* da){
    Hmx::Object* obj = da->GetObj(2);
    DataArray* prop = da->Array(3);
    PropKeys* keys = GetKeys(obj, prop);
    if(!keys) return DataNode(-1);
    else return DataNode(ValueFromIndex(keys, da->Int(4), da->Var(5)));
}

DataNode RndPropAnim::OnGetValueFromFrame(const DataArray* da){
    Hmx::Object* obj = da->GetObj(2);
    DataArray* prop = da->Array(3);
    float f = da->Float(4);
    PropKeys* keys = GetKeys(obj, prop);
    if(!keys) return DataNode(-1);
    else {
        DataNode node(0);
        ValueFromFrame(keys, f, &node);
        return DataNode(node);
    }
}

int RndPropAnim::ValueFromFrame(PropKeys* keys, float frame, DataNode* node){
    int ret = -1;
    if(!keys) return -1;
    else {
        switch(keys->mKeysType){
            case PropKeys::kFloat:
                float fval = 0.0f;
                ret = keys->FloatAt(frame, fval);
                *node = DataNode(fval);
                break;
            case PropKeys::kColor:
                Hmx::Color col;
                ret = keys->ColorAt(frame, col);
                *node = DataNode(col.Pack());
                break;
            case PropKeys::kObject:
                Hmx::Object* obj = 0;
                ret = keys->ObjectAt(frame, obj);
                *node = DataNode(obj);
                break;
            case PropKeys::kBool:
                bool bval = false;
                ret = keys->BoolAt(frame, bval);
                *node = DataNode(bval);
                break;
            case PropKeys::kQuat:
                Hmx::Quat quatval;
                ret = keys->QuatAt(frame, quatval);
                *node = DataNode(DataArrayPtr(DataNode(quatval.x), DataNode(quatval.y), DataNode(quatval.z), DataNode(quatval.w)));
                break;
            case PropKeys::kVector3:
                Vector3 vecval;
                ret = keys->Vector3At(frame, vecval);
                *node = DataNode(DataArrayPtr(DataNode(vecval.x), DataNode(vecval.y), DataNode(vecval.z)));
                break;
            case PropKeys::kSymbol:
                Symbol symval;
                ret = keys->SymbolAt(frame, symval);
                *node = DataNode(symval);
                break;
            default:
                *node = DataNode(0);
                break;
        }
        return ret;
    }
}

// fn_80636048
bool RndPropAnim::ValueFromIndex(PropKeys* keys, int index, DataNode* node){
    if(index < 0 || index >= keys->NumKeys()) return false;
    switch(keys->mKeysType){
        case PropKeys::kFloat:
            *node = DataNode(keys->AsFloatKeys()[index].value);
            break;
        case PropKeys::kColor:
            *node = DataNode(keys->AsColorKeys()[index].value.Pack());
            break;
        case PropKeys::kObject:
            *node = DataNode(keys->AsObjectKeys()[index].value.Ptr());
            break;
        case PropKeys::kBool:
            *node = DataNode(keys->AsBoolKeys()[index].value);
            break;
        case PropKeys::kQuat:
            Hmx::Quat q(keys->AsQuatKeys()[index].value);
            *node = DataNode(DataArrayPtr(DataNode(q.x), DataNode(q.y), DataNode(q.z), DataNode(q.w)));
            break;
        case PropKeys::kVector3:
            Vector3 vec(keys->AsVector3Keys()[index].value);
            *node = DataNode(DataArrayPtr(DataNode(vec.x), DataNode(vec.y), DataNode(vec.z)));
            break;
        case PropKeys::kSymbol:
            *node = DataNode(keys->AsSymbolKeys()[index].value);
            break;
        default:
            *node = DataNode(0);
            break;
    }
    return true;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(RndPropAnim)
    HANDLE_EXPR(remove_keys, RemoveKeys(_msg->Obj<Hmx::Object>(2), _msg->Array(3)))
    HANDLE_EXPR(has_keys, HasKeys(_msg->Obj<Hmx::Object>(2), _msg->Array(3)))
    HANDLE_ACTION(add_keys, AddKeys(_msg->Obj<Hmx::Object>(2), _msg->Array(3), (PropKeys::AnimKeysType)_msg->Int(4)))
    HANDLE_ACTION(set_key, SetKey(_msg->Obj<Hmx::Object>(2), _msg->Array(3), _msg->Float(4)))
    HANDLE_ACTION(set_key_val, SetKeyVal(_msg->Obj<Hmx::Object>(2), _msg->Array(3), _msg->Float(4), _msg->Node(5), _msg->Size() > 6 ? _msg->Int(6) : true))
    HANDLE_EXPR(keys_type, AnimKeysType(_msg->Obj<Hmx::Object>(2), _msg->Array(3)))
    HANDLE_EXPR(interp_type, InterpType(_msg->Obj<Hmx::Object>(2), _msg->Array(3)))
    HANDLE_ACTION(set_interp_type, SetInterpType(_msg->Obj<Hmx::Object>(2), _msg->Array(3), (PropKeys::Interpolation)_msg->Int(4)))
    HANDLE_EXPR(interp_handler, InterpHandler(_msg->Obj<Hmx::Object>(2), _msg->Array(3)))
    HANDLE_ACTION(set_interp_handler, SetInterpHandler(_msg->Obj<Hmx::Object>(2), _msg->Array(3), _msg->Sym(4)))
    HANDLE_ACTION(replace_target, Replace(_msg->Obj<Hmx::Object>(2), _msg->Obj<Hmx::Object>(3)))
    HANDLE_EXPR(foreach_target, ForEachTarget(_msg))
    HANDLE(forall_keyframes, ForAllKeyframes)
    HANDLE(foreach_keyframe, ForeachKeyframe)
    HANDLE(foreach_frame, ForeachFrame)
    HANDLE_EXPR(change_prop_path, ChangePropPath(_msg->Obj<Hmx::Object>(2), _msg->Array(3), _msg->Array(4)))
    HANDLE(replace_keyframe, OnReplaceKeyframe)
    HANDLE(replace_frame, OnReplaceFrame)
    HANDLE(index_from_frame, OnGetIndexFromFrame)
    HANDLE(frame_from_index, OnGetFrameFromIndex)
    HANDLE(value_from_index, OnGetValueFromIndex)
    HANDLE(value_from_frame, OnGetValueFromFrame)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x43C)
END_HANDLERS
#pragma pop

BEGIN_PROPSYNCS(RndPropAnim)
    SYNC_PROP(loop, mLoop)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS
