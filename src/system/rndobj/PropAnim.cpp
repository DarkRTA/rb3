#include "rndobj/PropAnim.h"
#include "math/Color.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "obj/ObjectStage.h"
#include "os/System.h"
#include "rndobj/EventTrigger.h"
#include "rndobj/PropKeys.h"
#include "utl/Std.h"
#include "obj/Utl.h"
#include "utl/Symbols.h"

INIT_REVS(RndPropAnim)
DataNode sKeyReplace;
float sFrameReplace;
bool sReplaceKey;
bool sReplaceFrame;

RndPropAnim::RndPropAnim() : mLastFrame(0.0f), mInSetFrame(0), mLoop(0) {}

RndPropAnim::~RndPropAnim() { RemoveKeys(); }

void RndPropAnim::Replace(Hmx::Object *from, Hmx::Object *to) {
    Hmx::Object::Replace(from, to);
    for (std::vector<PropKeys *>::iterator it = mPropKeys.begin(); it != mPropKeys.end();
         it) {
        PropKeys *cur = *it;
        if (cur->mTarget == from) {
            if (!to) {
                it = mPropKeys.erase(it);
                delete cur;
            } else {
                cur->SetTarget(to);
                it++;
            }
        } else
            it++;
    }
}

SAVE_OBJ(RndPropAnim, 0x43);

BEGIN_LOADS(RndPropAnim)
    LOAD_REVS(bs)
    ASSERT_REVS(0xD, 0)
    SetPropKeysRev(gRev);
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndAnimatable)
    ObjOwnerPtr<Hmx::Object> pPtr(this);
    mLastFrame = GetFrame();
    RemoveKeys();
    if (gRev < 7) {
        LoadPre7(bs);
        return;
    } else {
        int count;
        bs >> count;
        for (int i = 0; i < count; i++) {
            int num;
            bs >> num;
            AddKeys(0, 0, (PropKeys::AnimKeysType)num)->Load(bs);
        }
        if (gRev > 0xB)
            bs >> mLoop;
    }
END_LOADS

// fn_80631D38
void RndPropAnim::LoadPre7(BinStream &bs) {
    ObjOwnerPtr<Hmx::Object> objPtr(this);
    if (gRev < 2)
        bs >> objPtr;
    int count;
    bs >> count;
    for (int i = 0; i < count; i++) {
        DataArray *arr = nullptr;
        PropKeys::AnimKeysType ty = PropKeys::kFloat;
        Keys<float, float> floatKeys;
        Keys<Hmx::Color, Hmx::Color> colorKeys;
        ObjKeys objKeys(this);
        Keys<bool, bool> boolKeys;
        Keys<Hmx::Quat, Hmx::Quat> quatKeys;
        if (gRev >= 2)
            bs >> objPtr;
        if (gRev < 1) {
            Symbol sym;
            bs >> sym;
            arr = DataArrayPtr(sym);
        } else
            bs >> arr;
        if (gRev < 3)
            bs >> floatKeys;
        else {
            int animtype;
            bs >> animtype;
            ty = (PropKeys::AnimKeysType)animtype;
            bs >> floatKeys;
            bs >> colorKeys;
            Hmx::Object *oldowner = ObjectStage::sOwner;
            if (gRev > 3) {
                ObjectStage::sOwner = this;
                bs >> objKeys;
            }
            ObjectStage::sOwner = oldowner;
            if (gRev > 4)
                bs >> boolKeys;
            if (gRev > 5)
                bs >> quatKeys;
        }
        PropKeys *addedKeys = AddKeys(objPtr.Ptr(), arr, ty);
        if (arr)
            arr->Release();
        switch (ty) {
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
        default:
            break;
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
        for (std::vector<PropKeys *>::const_iterator it = c->mPropKeys.begin();
             it != c->mPropKeys.end();
             ++it) {
            PropKeys *cur = *it;
            PropKeys *added =
                AddKeys(cur->mTarget, cur->mProp, (PropKeys::AnimKeysType)cur->mKeysType);
            added->Copy(*it);
        }
        COPY_MEMBER(mLoop)
    END_COPYING_MEMBERS
END_COPYS

float RndPropAnim::StartFrame() {
    float frame = 0.0f;
    for (std::vector<PropKeys *>::iterator it = mPropKeys.begin(); it != mPropKeys.end();
         it++) {
#ifdef MILO_DEBUG
        MinEq(frame, (*it)->StartFrame());
#else
        frame = Min(frame, (*it)->StartFrame());
#endif
    }
    return frame;
}

float RndPropAnim::EndFrame() {
    float frame = 0.0f;
    for (std::vector<PropKeys *>::iterator it = mPropKeys.begin(); it != mPropKeys.end();
         it++) {
#ifdef MILO_DEBUG
        MaxEq(frame, (*it)->EndFrame());
#else
        frame = Max(frame, (*it)->EndFrame());
#endif
    }
    return frame;
}

// fn_806326EC
void RndPropAnim::AdvanceFrame(float frame) {
    if (mLoop) {
        frame = ModRange(StartFrame(), EndFrame(), frame);
    }
    RndAnimatable::SetFrame(frame, 1.0f);
}

// fn_80632790
void RndPropAnim::SetFrame(float frame, float blend) {
    if (!mInSetFrame) {
        mInSetFrame = true;
        AdvanceFrame(frame);
        float theframe = mFrame;
        for (std::vector<PropKeys *>::iterator it = mPropKeys.begin();
             it != mPropKeys.end();
             it++) {
            if ((*it)->mPropExceptionID == PropKeys::kDirEvent) {
                ObjKeys &objkeys = (*it)->AsObjectKeys();
                for (int i = 0; i < objkeys.size(); i++) {
                    float objFrame = objkeys[i].frame;
                    if (objFrame > theframe)
                        break;
                    if (objFrame >= mLastFrame && mLastFrame != theframe) {
                        EventTrigger *trig =
                            dynamic_cast<EventTrigger *>(objkeys[i].value.Ptr());
                        if (trig)
                            trig->Trigger();
                    }
                }
            }
            (*it)->SetFrame(theframe, blend);
        }
        mLastFrame = theframe;
        mInSetFrame = false;
    }
}

void RndPropAnim::SetKey(float frame) {
    for (std::vector<PropKeys *>::iterator it = mPropKeys.begin(); it != mPropKeys.end();
         it++) {
        (*it)->SetKey(frame);
    }
}

void RndPropAnim::StartAnim() {
    for (std::vector<PropKeys *>::iterator it = mPropKeys.begin(); it != mPropKeys.end();
         it++) {
        (*it)->ResetLastKeyFrameIndex();
    }
}

PropKeys *RndPropAnim::GetKeys(const Hmx::Object *obj, DataArray *prop) {
    if (!prop || !obj)
        return 0;
    for (std::vector<PropKeys *>::iterator it = mPropKeys.begin(); it != mPropKeys.end();
         it++) {
        PropKeys *cur = *it;
        if (cur->mTarget.Ptr() == obj && PathCompare(prop, cur->mProp))
            return cur;
    }
    return 0;
}

PropKeys *
RndPropAnim::AddKeys(Hmx::Object *obj, DataArray *prop, PropKeys::AnimKeysType ty) {
    PropKeys *theKeys = GetKeys(obj, prop);
    if (theKeys)
        return theKeys;
    else {
        switch (ty) {
        case PropKeys::kFloat:
            theKeys = new FloatKeys(this, obj);
            break;
        case PropKeys::kColor:
            theKeys = new ColorKeys(this, obj);
            break;
        case PropKeys::kObject:
            theKeys = new ObjectKeys(this, obj);
            break;
        case PropKeys::kBool:
            theKeys = new BoolKeys(this, obj);
            break;
        case PropKeys::kQuat:
            theKeys = new QuatKeys(this, obj);
            break;
        case PropKeys::kVector3:
            theKeys = new Vector3Keys(this, obj);
            break;
        case PropKeys::kSymbol:
            theKeys = new SymbolKeys(this, obj);
            break;
        default:
            MILO_WARN("Unable to create animation for keysType");
            return 0;
        }
        if (prop) {
            DataNode node(prop, kDataArray);
            theKeys->SetProp(node);
        }
        mPropKeys.push_back(theKeys);
    }
    return theKeys;
}

bool RndPropAnim::ChangePropPath(Hmx::Object *o, DataArray *a1, DataArray *a2) {
    if (!a2 || a2->Size() == 0)
        return RemoveKeys(o, a1);
    else {
        std::vector<PropKeys *>::iterator keys = FindKeys(o, a1);
        if (keys != mPropKeys.end()) {
            DataNode node(a2, kDataArray);
            (*keys)->SetProp(node);
            return true;
        } else
            return false;
    }
}

void RndPropAnim::RemoveKeys() { DeleteAll(mPropKeys); }

std::vector<PropKeys *>::iterator RndPropAnim::FindKeys(Hmx::Object *o, DataArray *da) {
    for (std::vector<PropKeys *>::iterator it = mPropKeys.begin(); it != mPropKeys.end();
         ++it) {
        PropKeys *cur = *it;
        if (!da && !(cur)->mProp)
            return it;
        if ((cur->mTarget.Ptr() == o && PathCompare(da, cur->mProp)))
            return it;
    }
    return mPropKeys.end();
}

bool RndPropAnim::RemoveKeys(Hmx::Object *o, DataArray *da) {
    std::vector<PropKeys *>::iterator keys = FindKeys(o, da);
    if (keys == mPropKeys.end())
        return false;
    else {
        PropKeys *cur = *keys;
        mPropKeys.erase(keys);
        delete cur;
        return true;
    }
}

bool RndPropAnim::HasKeys(Hmx::Object *o, DataArray *da) {
    return FindKeys(o, da) != mPropKeys.end();
}

void RndPropAnim::SetKey(Hmx::Object *o, DataArray *da, float f) {
    std::vector<PropKeys *>::iterator keys = FindKeys(o, da);
    if (keys != mPropKeys.end()) {
        PropKeys *cur = *keys;
        cur->SetKey(f);
    }
}

void RndPropAnim::SetKeyVal(
    Hmx::Object *o, DataArray *da, float frame, const DataNode &node, bool unique
) {
    std::vector<PropKeys *>::iterator keys = FindKeys(o, da);
    if (keys != mPropKeys.end()) {
        PropKeys *cur = *keys;
        switch (cur->mKeysType) {
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
                Vector3(
                    node.Array()->Float(0), node.Array()->Float(1), node.Array()->Float(2)
                ),
                frame,
                unique
            );
            break;
        case PropKeys::kQuat:
            cur->AsQuatKeys().Add(
                Hmx::Quat(
                    node.Array()->Float(0),
                    node.Array()->Float(1),
                    node.Array()->Float(2),
                    node.Array()->Float(3)
                ),
                frame,
                unique
            );
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

PropKeys::AnimKeysType RndPropAnim::AnimKeysType(Hmx::Object *o, DataArray *da) {
    std::vector<PropKeys *>::iterator keys = FindKeys(o, da);
    if (keys != mPropKeys.end()) {
        PropKeys *cur = *keys;
        return (PropKeys::AnimKeysType)cur->mKeysType;
    } else
        return PropKeys::kFloat;
}

PropKeys::Interpolation RndPropAnim::InterpType(Hmx::Object *o, DataArray *da) {
    std::vector<PropKeys *>::iterator keys = FindKeys(o, da);
    if (keys != mPropKeys.end()) {
        PropKeys *cur = *keys;
        return (PropKeys::Interpolation)cur->mInterpolation;
    } else
        return PropKeys::kStep;
}

void RndPropAnim::SetInterpType(
    Hmx::Object *obj, DataArray *prop, PropKeys::Interpolation iter
) {
    std::vector<PropKeys *>::iterator keys = FindKeys(obj, prop);
    if (keys != mPropKeys.end()) {
        PropKeys *cur = *keys;
        cur->mInterpolation = iter;
    }
}

Symbol RndPropAnim::InterpHandler(Hmx::Object *obj, DataArray *prop) {
    std::vector<PropKeys *>::iterator keys = FindKeys(obj, prop);
    if (keys != mPropKeys.end()) {
        PropKeys *cur = *keys;
        if (cur->mPropExceptionID == PropKeys::kHandleInterp)
            return cur->InterpHandler();
    }
    return Symbol();
}

void RndPropAnim::SetInterpHandler(Hmx::Object *obj, DataArray *prop, Symbol handler) {
    std::vector<PropKeys *>::iterator keys = FindKeys(obj, prop);
    if (keys != mPropKeys.end()) {
        (*keys)->SetInterpHandler(handler);
    }
}

void RndPropAnim::Print() {
    TextStream &ts = TheDebug;
    int idx = 0;
    for (std::vector<PropKeys *>::iterator it = mPropKeys.begin(); it != mPropKeys.end();
         it++) {
        ts << "   Keys " << idx << "\n";
        (*it)->Print();
        idx++;
    }
}

DataNode RndPropAnim::ForEachTarget(const DataArray *da) {
    ObjPtrList<Hmx::Object, ObjectDir> objList(this, kObjListNoNull);
    const char *arrstr = da->Str(2);
    for (std::vector<PropKeys *>::iterator it = mPropKeys.begin(); it != mPropKeys.end();
         ++it) {
        PropKeys *cur = *it;
        if (arrstr == gNullStr || cur->mTarget->ClassName() == arrstr) {
            objList.push_back(cur->mTarget);
        }
    }
    DataNode *var = da->Var(3);
    DataNode node(*var);
    for (ObjPtrList<Hmx::Object, ObjectDir>::iterator it = objList.begin();
         it != objList.end();
         ++it) {
        *var = DataNode(*it);
        for (int i = 4; i < da->Size(); i++) {
            da->Command(i)->Execute();
        }
    }
    *var = node;
    return 0;
}

// retail scratch: https://decomp.me/scratch/F7QSe
DataNode RndPropAnim::ForeachKeyframe(const DataArray *da) {
    Hmx::Object *obj2 = da->Obj<Hmx::Object>(2);
    DataArray *arr3 = da->Array(3);
    DataNode *var4 = da->Var(4);
    DataNode *var5 = da->Var(5);
    PropKeys *theKeys = GetKeys(obj2, arr3);
    if (!theKeys)
        return 0;
    else {
        std::map<int, float> theMap;
        for (int i = 0; i < theKeys->NumKeys(); i++) {
            float frame = 0;
            theKeys->FrameFromIndex(i, frame);
            *var4 = frame;
            int keyIdx = i;
            switch (theKeys->mKeysType) {
            case PropKeys::kFloat: {
                *var5 = theKeys->AsFloatKeys()[keyIdx].value;
            } break;
            case PropKeys::kColor: {
                *var5 = theKeys->AsColorKeys()[keyIdx].value.Pack();
            } break;
            case PropKeys::kObject:
                *var5 = theKeys->AsObjectKeys()[keyIdx].value.Ptr();
                break;
            case PropKeys::kBool: {
                Key<bool> &curBool = theKeys->AsBoolKeys()[keyIdx];
                *var5 = curBool.value;
            } break;
            case PropKeys::kQuat: {
                Hmx::Quat curQuat = theKeys->AsQuatKeys()[keyIdx].value;
                *var5 = DataArrayPtr(curQuat.x, curQuat.y, curQuat.z, curQuat.w);
            } break;
            case PropKeys::kVector3: {
                Vector3 curVector = theKeys->AsVector3Keys()[keyIdx].value;
                *var5 = DataArrayPtr(curVector.x, curVector.y, curVector.z);
            } break;
            case PropKeys::kSymbol: {
                *var5 = theKeys->AsSymbolKeys()[keyIdx].value;
            } break;
            default:
                *var5 = 0;
                break;
            }
            sReplaceKey = false;
            sReplaceFrame = false;
            for (int j = 6; j < da->Size(); j++) {
                da->Command(j)->Execute();
            }
            if (sReplaceKey) {
                sReplaceKey = false;
                switch (theKeys->mKeysType) {
                case PropKeys::kFloat: {
                    Key<float> &curFloatKey = theKeys->AsFloatKeys()[keyIdx];
                    curFloatKey.value = sKeyReplace.Float();
                } break;
                case PropKeys::kColor: {
                    Key<Hmx::Color> &curColorKey = theKeys->AsColorKeys()[keyIdx];
                    curColorKey.value.Unpack(sKeyReplace.Int());
                } break;
                case PropKeys::kObject: {
                    ObjectStage objStage(sKeyReplace.GetObj());
                    Key<ObjectStage> &curObjKeys = theKeys->AsObjectKeys()[keyIdx];
                    curObjKeys.value = objStage;
                } break;
                case PropKeys::kBool: {
                    Key<bool> &curBoolKey = theKeys->AsBoolKeys()[keyIdx];
                    curBoolKey.value = sKeyReplace.Int();
                } break;
                case PropKeys::kSymbol: {
                    Symbol *replaceSym = &sKeyReplace.Sym();
                    Key<Symbol> &curSymKey = theKeys->AsSymbolKeys()[i];
                    curSymKey.value = *replaceSym;
                } break;
                default:
                    MILO_WARN("%s can not replace key, unknown type", PathName(this));
                    break;
                }
            }
            if (sReplaceFrame) {
                theMap[i] = sFrameReplace;
                sReplaceFrame = false;
            }
        }
        for (std::map<int, float>::const_iterator it = theMap.begin(); it != theMap.end();
             ++it) {
            const float &mapF = it->second;
            theKeys->ChangeFrame(it->first, mapF, false);
        }
        if (theMap.size() != 0) {
            theKeys->ReSort();
        }
        return 0;
    }
}

DataNode RndPropAnim::ForeachFrame(const DataArray *da) {
    Hmx::Object *obj2 = da->Obj<Hmx::Object>(2);
    DataArray *arr3 = da->Array(3);
    float f4 = da->Float(4);
    float f5 = da->Float(5);
    float f6 = da->Float(6);
    DataNode *var7 = da->Var(7);
    PropKeys *theKeys = GetKeys(obj2, arr3);
    if (!theKeys)
        return 0;
    else {
        for (float fIt = f4; fIt < f5; fIt += f6) {
            ValueFromFrame(theKeys, fIt, var7);
            for (int i = 8; i < da->Size(); i++) {
                da->Command(i)->Execute();
            }
        }
        return 1;
    }
}

DataNode RndPropAnim::ForAllKeyframes(const DataArray *da) {
    // TODO: maybe there's a custom alloc func for DataArrayPtr that adds a ref?
    std::vector<DataArrayPtr> ptrs;
    for (std::vector<PropKeys *>::iterator it = mPropKeys.begin(); it != mPropKeys.end();
         ++it) {
        PropKeys *cur = *it;
        if (cur->mTarget && cur->mProp) {
            for (int i = 0; i < cur->NumKeys(); i++) {
                float frame = 0;
                cur->FrameFromIndex(i, frame);
                DataArrayPtr ptr(nullptr);
                ptr->Resize(4);
                ptr->Node(0) = cur->mTarget.Ptr();
                ptr->Node(1) = DataNode(cur->mProp, kDataArray);
                ptr->Node(2) = frame;
                ValueFromIndex(cur, i, &ptr->Node(3));
                ptrs.push_back(ptr);
            }
        }
    }
    std::sort(ptrs.begin(), ptrs.end(), ForAllKeyframesSorter());
    DataNode *var2 = da->Var(2);
    DataNode *var3 = da->Var(3);
    DataNode *var4 = da->Var(4);
    DataNode *var5 = da->Var(5);
    for (int i = 0; i < ptrs.size(); i++) {
        DataArray *curPtr = ptrs[i];
        *var2 = curPtr->Node(0);
        *var3 = curPtr->Node(1);
        *var4 = curPtr->Node(2);
        *var5 = curPtr->Node(3);
        for (int j = 6; j < da->Size(); j++) {
            da->Command(j)->Execute();
        }
    }
    return 0;
}

DataNode RndPropAnim::OnReplaceKeyframe(DataArray *da) {
    sReplaceKey = true;
    sKeyReplace = da->Evaluate(2);
    return 0;
}

DataNode RndPropAnim::OnReplaceFrame(DataArray *da) {
    sReplaceFrame = true;
    sFrameReplace = da->Float(2);
    return 0;
}

DataNode RndPropAnim::OnGetIndexFromFrame(const DataArray *da) {
    Hmx::Object *obj = da->GetObj(2);
    DataArray *prop = da->Array(3);
    float f = da->Float(4);
    PropKeys *keys = GetKeys(obj, prop);
    if (!keys)
        return -1;
    else
        return ValueFromFrame(keys, f, &DataNode(0));
}

DataNode RndPropAnim::OnGetFrameFromIndex(const DataArray *da) {
    Hmx::Object *obj = da->GetObj(2);
    DataArray *prop = da->Array(3);
    int i = da->Int(4);
    float frame = -1.0f;
    PropKeys *keys = GetKeys(obj, prop);
    if (!keys)
        return frame;
    else {
        keys->FrameFromIndex(i, frame);
        return frame;
    }
}

DataNode RndPropAnim::OnGetValueFromIndex(const DataArray *da) {
    Hmx::Object *obj = da->GetObj(2);
    DataArray *prop = da->Array(3);
    PropKeys *keys = GetKeys(obj, prop);
    if (!keys)
        return -1;
    else
        return ValueFromIndex(keys, da->Int(4), da->Var(5));
}

DataNode RndPropAnim::OnGetValueFromFrame(const DataArray *da) {
    Hmx::Object *obj = da->GetObj(2);
    DataArray *prop = da->Array(3);
    float f = da->Float(4);
    PropKeys *keys = GetKeys(obj, prop);
    if (!keys)
        return -1;
    else {
        DataNode node(0);
        ValueFromFrame(keys, f, &node);
        return node;
    }
}

int RndPropAnim::ValueFromFrame(PropKeys *keys, float frame, DataNode *node) {
    int ret = -1;
    if (!keys)
        return -1;
    else {
        switch (keys->mKeysType) {
        case PropKeys::kFloat: {
            float fval = 0.0f;
            ret = keys->FloatAt(frame, fval);
            *node = fval;
            break;
        }
        case PropKeys::kColor: {
            Hmx::Color col;
            ret = keys->ColorAt(frame, col);
            *node = col.Pack();
            break;
        }
        case PropKeys::kObject: {
            Hmx::Object *obj = 0;
            ret = keys->ObjectAt(frame, obj);
            *node = obj;
            break;
        }
        case PropKeys::kBool: {
            bool bval = false;
            ret = keys->BoolAt(frame, bval);
            *node = bval;
            break;
        }
        case PropKeys::kQuat: {
            Hmx::Quat quatval;
            ret = keys->QuatAt(frame, quatval);
            *node = DataArrayPtr(quatval.x, quatval.y, quatval.z, quatval.w);
            break;
        }
        case PropKeys::kVector3: {
            Vector3 vecval;
            ret = keys->Vector3At(frame, vecval);
            *node = DataArrayPtr(vecval.x, vecval.y, vecval.z);
            break;
        }
        case PropKeys::kSymbol: {
            Symbol symval;
            ret = keys->SymbolAt(frame, symval);
            *node = symval;
            break;
        }
        default: {
            *node = 0;
            break;
        }
        }
        return ret;
    }
}

// fn_80636048
bool RndPropAnim::ValueFromIndex(PropKeys *keys, int index, DataNode *node) {
    if (index < 0 || index >= keys->NumKeys())
        return false;
    switch (keys->mKeysType) {
    case PropKeys::kFloat: {
        *node = keys->AsFloatKeys()[index].value;
        break;
    }
    case PropKeys::kColor: {
        *node = keys->AsColorKeys()[index].value.Pack();
        break;
    }
    case PropKeys::kObject: {
        *node = keys->AsObjectKeys()[index].value.Ptr();
        break;
    }
    case PropKeys::kBool: {
        *node = keys->AsBoolKeys()[index].value;
        break;
    }
    case PropKeys::kQuat: {
        Hmx::Quat q(keys->AsQuatKeys()[index].value);
        *node = DataArrayPtr(q.x, q.y, q.z, q.w);
        break;
    }
    case PropKeys::kVector3: {
        Vector3 vec(keys->AsVector3Keys()[index].value);
        *node = DataArrayPtr(vec.x, vec.y, vec.z);
        break;
    }
    case PropKeys::kSymbol: {
        *node = keys->AsSymbolKeys()[index].value;
        break;
    }
    default: {
        *node = 0;
        break;
    }
    }
    return true;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(RndPropAnim)
    HANDLE_EXPR(remove_keys, RemoveKeys(_msg->Obj<Hmx::Object>(2), _msg->Array(3)))
    HANDLE_EXPR(has_keys, HasKeys(_msg->Obj<Hmx::Object>(2), _msg->Array(3)))
    HANDLE_ACTION(
        add_keys,
        AddKeys(
            _msg->Obj<Hmx::Object>(2), _msg->Array(3), (PropKeys::AnimKeysType)_msg->Int(4)
        )
    )
    HANDLE_ACTION(
        set_key, SetKey(_msg->Obj<Hmx::Object>(2), _msg->Array(3), _msg->Float(4))
    )
    HANDLE_ACTION(
        set_key_val,
        SetKeyVal(
            _msg->Obj<Hmx::Object>(2),
            _msg->Array(3),
            _msg->Float(4),
            _msg->Node(5),
            _msg->Size() > 6 ? _msg->Int(6) : true
        )
    )
    HANDLE_EXPR(keys_type, AnimKeysType(_msg->Obj<Hmx::Object>(2), _msg->Array(3)))
    HANDLE_EXPR(interp_type, InterpType(_msg->Obj<Hmx::Object>(2), _msg->Array(3)))
    HANDLE_ACTION(
        set_interp_type,
        SetInterpType(
            _msg->Obj<Hmx::Object>(2),
            _msg->Array(3),
            (PropKeys::Interpolation)_msg->Int(4)
        )
    )
    HANDLE_EXPR(interp_handler, InterpHandler(_msg->Obj<Hmx::Object>(2), _msg->Array(3)))
    HANDLE_ACTION(
        set_interp_handler,
        SetInterpHandler(_msg->Obj<Hmx::Object>(2), _msg->Array(3), _msg->Sym(4))
    )
    HANDLE_ACTION(
        replace_target, Replace(_msg->Obj<Hmx::Object>(2), _msg->Obj<Hmx::Object>(3))
    )
    HANDLE_EXPR(foreach_target, ForEachTarget(_msg))
    HANDLE(forall_keyframes, ForAllKeyframes)
    HANDLE(foreach_keyframe, ForeachKeyframe)
    HANDLE(foreach_frame, ForeachFrame)
    HANDLE_EXPR(
        change_prop_path,
        ChangePropPath(_msg->Obj<Hmx::Object>(2), _msg->Array(3), _msg->Array(4))
    )
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
