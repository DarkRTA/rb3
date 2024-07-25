#include "rndobj/PropKeys.h"
#include "obj/ObjectStage.h"
#include "obj/Utl.h"
#include "obj/DataUtl.h"
#include "math/Rot.h"

unsigned short PropKeys::gRev = 0;
Hmx::Object* ObjectStage::sOwner = 0;
Message PropKeys::sInterpMessage(Symbol(), DataNode(0), DataNode(0), DataNode(0), DataNode(0), DataNode(0));

void SetPropKeysRev(int rev){
    PropKeys::gRev = rev;
}

BinStream& operator>>(BinStream& bs, ObjectStage& stage){
    ObjectDir* dir = 0;
    if(PropKeys::gRev > 8){
        ObjPtr<ObjectDir, ObjectDir> dirPtr(stage.Owner(), 0);
        dirPtr.Load(bs, true, dir);
        dir = dirPtr.Ptr();
    }
    stage.Load(bs, true, dir);
    return bs;
}

BinStream& operator<<(BinStream& bs, const ObjectStage& stage){
    ObjPtr<ObjectDir, ObjectDir> dirPtr(stage.Owner(), (stage.Ptr()) ? stage.Ptr()->Dir() : 0);
    bs << dirPtr;
    bs << ObjPtr<Hmx::Object, ObjectDir>(stage.Owner(), stage.Ptr());
    return bs;
}

PropKeys::PropKeys(Hmx::Object* o1, Hmx::Object* o2) : mTarget(o1, o2), mProp(0), mTrans(0), mInterpHandler(),
    mLastKeyFrameIndex(-2), mKeysType(kFloat), mInterpolation(kLinear), mPropExceptionID(kNoException), unk18lastbit(0) {
    
}

PropKeys::~PropKeys(){
    if(mProp){
        mProp->Release();
        mProp = 0;
    }
}

void PropKeys::SetProp(DataNode& node){
    if(node.Type() == kDataArray){
        DataArray* nodeArr = node.Array(0);
        if(mProp){
            mProp->Release();
            mProp = 0;
        }
        mProp = nodeArr->Clone(true, false, 0);

    }
    else MILO_WARN("unknown prop set type");
    SetPropExceptionID();
}

int PropKeys::SetKey(float frame){
    float f = 0.0f;
    for(int i = 0; i < NumKeys(); i++){
        if(FrameFromIndex(i, f)){
            float fabsFloat = __fabs(frame - f);
            if(fabsFloat < 0.000099999997f)
                return i;
        }
    }
    return -1;
}

void PropKeys::SetTarget(Hmx::Object* o){
    if(mTarget.Ptr() != o){
        bool b2 = true;
        bool b1 = false;
        if(mProp && GetPropertyVal(o, mProp, false) != 0) b1 = true;
        if(!b1 && !(mPropExceptionID == kTransQuat || mPropExceptionID == kTransScale || mPropExceptionID == kTransPos || mPropExceptionID == kDirEvent)) b2 = false;
        if(!o || !b2){
            if(mProp){
                mProp->Release();
                mProp = 0;
            }
        }
        mTarget = o;
        SetPropExceptionID();
    }
}

void PropKeys::ChangeFrame(int i, float f, bool b){
    switch(mKeysType){
        case kFloat:
            (AsFloatKeys())[i].frame = f;
            break;
        case kColor:
            (AsColorKeys())[i].frame = f;
            break;
        case kObject:
            (AsObjectKeys())[i].frame = f;
            break;
        case kBool:
            (AsBoolKeys())[i].frame = f;
            break;
        case kSymbol:
            (AsSymbolKeys())[i].frame = f;
            break;
        case kVector3:
            (AsVector3Keys())[i].frame = f;
            break;
        case kQuat:
            (AsQuatKeys())[i].frame = f;
            break;
        default:
            MILO_WARN("can not replace frame, unknown type");
            break;
    }
    if(b) ReSort();
}

// 80627a64 in retail
void PropKeys::ReSort(){
    switch(mKeysType){
        case kFloat:
            AsFloatKeys();
            // mystery vector method - fn_806280C0 in retail, scratch: https://decomp.me/scratch/5Vpiu
            break;
        case kColor:
            AsColorKeys();
            // mystery vector method - fn_80627FEC in retail
            break;
        case kObject:
            AsObjectKeys();
            // mystery vector method - fn_80627F0C in retail
            break;
        case kBool:
            AsBoolKeys();
            // mystery vector method - fn_80627E24 in retail
            break;
        case kSymbol:
            AsSymbolKeys();
            // mystery vector method - fn_80627D50 in retail
            break;
        case kVector3:
            AsVector3Keys();
            // mystery vector method - fn_80627C7C in retail
            break;
        case kQuat:
            AsQuatKeys();
            // mystery vector method - fn_80627B64 in retail
            break;
    }
}

void Interp(const ObjectStage& stage1, const ObjectStage& stage2, float f, Hmx::Object*& obj){
    const ObjectStage& out = f < 1.0f ? stage1 : stage2;
    obj = out.Ptr();
}

SAVE_OBJ(PropKeys, 0xCF);

void PropKeys::Load(BinStream& bs){
    if(gRev < 7) MILO_FAIL("PropKeys::Load should not be called before version 7");
    else {
        int iVal;
        bs >> iVal;
        mKeysType = iVal;
        bs >> mTarget;
        bs >> mProp;

        if(gRev >= 8) bs >> iVal;
        else iVal = (mKeysType == kObject || mKeysType == kBool) == 0;

        if(gRev < 0xB && iVal == 4){
            mPropExceptionID = kMacro;
            mInterpolation = kStep;
        }
        else mInterpolation = iVal;

        if(gRev > 9){
            Symbol sym;
            bs >> sym;
            if(!sym.Null()){
                SetInterpHandler(sym);
            }
        }

        if(gRev > 10){
            bs >> iVal;
            mPropExceptionID = iVal;
        }

        if(gRev > 0xC){
            bool b;
            bs >> b;
            unk18lastbit = b;
        }
        SetPropExceptionID();
    }
}

void PropKeys::Copy(const PropKeys* keys){
    mInterpolation = keys->mInterpolation;
    mPropExceptionID = keys->mPropExceptionID;
    mInterpHandler = keys->mInterpHandler;
    unk18lastbit = keys->unk18lastbit;
}

void PropKeys::Print(){
    TextStream& ts = TheDebug;
    ts << "      target: " << mTarget.Ptr() << "\n";
    ts << "      property: " << mProp << "\n";
    ts << "      interpolation: " << (int)mInterpolation << "\n";

    for(int i = 0; i < NumKeys(); i++){
        float frame = 0.0f;
        FrameFromIndex(i, frame);
        ts << "      " << frame << " -> ";
        switch(mKeysType){
            case kFloat:
                ts << (AsFloatKeys())[i].value;
                break;
            case kColor:
                ts << (AsColorKeys())[i].value;
                break;
            case kObject:
                ts << (Hmx::Object*)((AsObjectKeys())[i].value);
                break;
            case kBool:
                ts << (AsBoolKeys())[i].value;
                break;
            case kQuat:
                ts << (AsQuatKeys())[i].value;
                break;
            case kVector3:
                ts << (AsVector3Keys())[i].value;
                break;
            case kSymbol:
                ts << (AsSymbolKeys())[i].value;
                break;
        }
        ts << "\n";
    }
}

unsigned int PropKeys::PropExceptionID(Hmx::Object* o, DataArray* arr){
    if(!o || !arr) return kNoException;
    String propString;
    arr->Print(propString, kDataArray, true);
    propString = propString.substr(1, strlen(propString.c_str()) - 2);
    bool b1 = false;
    if(propString == "rotation"){
        if(IsASubclass(o->ClassName(), "Trans")) b1 = true;
        if(b1) return kTransQuat;
    }
    b1 = false;
    if(propString == "scale"){
        if(IsASubclass(o->ClassName(), "Trans")) b1 = true;
        if(b1) return kTransScale;
    }
    b1 = false;
    if(propString == "position"){
        if(IsASubclass(o->ClassName(), "Trans")) b1 = true;
        if(b1) return kTransPos;
    }
    b1 = false;
    if(propString == "event"){
        if(IsASubclass(o->ClassName(), "ObjectDir")) b1 = true;
        if(b1) return kDirEvent;
    }
    return kNoException;
}

void PropKeys::SetPropExceptionID(){
    if(!mInterpHandler.Null()) mPropExceptionID = kHandleInterp;
    else {
        if(mPropExceptionID != kMacro){
            mPropExceptionID = PropExceptionID(mTarget.Ptr(), mProp);
            if(mPropExceptionID == kTransQuat || mPropExceptionID == kTransScale || mPropExceptionID == kTransPos){
                if((Hmx::Object*)mTrans != mTarget.Ptr()){
                    mTrans = dynamic_cast<RndTransformable*>(mTarget.Ptr());
                }
            }
        }
    }
}

void PropKeys::SetInterpHandler(Symbol sym){
    mInterpHandler = sym;
    SetPropExceptionID();
}

int FloatKeys::FloatAt(float frame, float& fl){
    MILO_ASSERT(size(), 0x188);
    fl = 0.0f;
    float ref = 0.0f;
    const Key<float>* prev;
    const Key<float>* next;
    int at = AtFrame(frame, prev, next, ref);
    switch(mInterpolation){
        case kStep:
            fl = prev->value;
            break;
        case kLinear:
            Interp(prev->value, next->value, ref, fl);
            break;
        case kSpline:
            if(size() < 3 || prev == next){
                Interp(prev->value, next->value, ref, fl);
            }
            else {
                // more stuff happens here
            }
            break;
        case kHermite:
            Interp(prev->value, next->value, (ref * -2.0f + 3.0f) * ref * ref, fl);
            break;
        case kInterp5:
            Interp(prev->value, next->value, ref * ref * ref, fl);
            break;
        case kInterp6:
            Interp(prev->value, next->value, -(ref * ref * ref - 1.0f), fl);
            break;
    }
    return at;
}

void FloatKeys::SetFrame(float frame, float blend){
    if(!mProp || !mTarget || !size()) return;
    int idx;
    if(mPropExceptionID == kHandleInterp){
        float ref = 0.0f;
        const Key<float>* prev;
        const Key<float>* next;
        idx = AtFrame(frame, prev, next, ref);
        sInterpMessage.SetType(mInterpHandler);
        sInterpMessage[0] = DataNode(prev->value);
        sInterpMessage[1] = DataNode(next->value);
        sInterpMessage[2] = DataNode(ref);
        sInterpMessage[3] = DataNode(next->frame);
        if(idx >= 1) sInterpMessage[4] = DataNode((*this)[idx - 1].value);
        else sInterpMessage[4] = DataNode(0);
        mTarget->Handle(sInterpMessage, true);
    }
    else {
        float val;
        idx = FloatAt(frame, val);
        mTarget->SetProperty(mProp, DataNode(val));
    }
    mLastKeyFrameIndex = idx;
}

int ColorKeys::ColorAt(float frame, Hmx::Color& color){
    MILO_ASSERT(size(), 0x1E8);
    color.Set(0,0,0);
    int at = 0;
    const Key<Hmx::Color>* prev;
    const Key<Hmx::Color>* next;
    float ref;
    switch(mInterpolation){
        case kStep:
            at = AtFrame(frame, prev, next, ref);
            color = prev->value;
            break;
        case kLinear:
            at = AtFrame(frame, color);
            break;
        case kInterp5:
            at = AtFrame(frame, prev, next, ref);
            if(prev) Interp(prev->value, next->value, ref * ref * ref, color);
            break;
        case kInterp6:
            at = AtFrame(frame, prev, next, ref);
            ref = 1.0f - ref;
            if(prev) Interp(prev->value, next->value, -(ref * ref * ref - 1.0f), color);
            break;
        default: break;
    }
    return at;
}

void ColorKeys::SetFrame(float frame, float blend){
    if(!mProp || !mTarget || !size()) return;
    Hmx::Color col;
    int idx = ColorAt(frame, col);
    mTarget->SetProperty(mProp, DataNode(col.Pack()));
    mLastKeyFrameIndex = idx;
}

int ObjectKeys::ObjectAt(float frame, Hmx::Object*& obj){
    MILO_ASSERT(size(), 0x22A);
    return AtFrame(frame, obj);
}

void ObjectKeys::SetFrame(float frame, float blend){
    if(!mProp || !mTarget || !size()) return;
    int idx = 0;
    switch(mPropExceptionID){
        case kDirEvent:
            break;
        case kHandleInterp:
            float ref = 0.0f;
            const Key<ObjectStage>* prev;
            const Key<ObjectStage>* next;
            idx = AtFrame(frame, prev, next, ref);
            sInterpMessage.SetType(mInterpHandler);
            sInterpMessage[0] = DataNode(prev->value.Ptr());
            sInterpMessage[1] = DataNode(next->value.Ptr());
            sInterpMessage[2] = DataNode(ref);
            sInterpMessage[3] = DataNode(next->frame);
            if(idx >= 1) sInterpMessage[4] = DataNode((*this)[idx - 1].value.Ptr());
            else sInterpMessage[4] = DataNode(0);
            mTarget->Handle(sInterpMessage, true);
            break;
        default:
            Hmx::Object* obj;
            idx = ObjectAt(frame, obj);
            if(mInterpolation != kStep || mLastKeyFrameIndex != idx){
                mTarget->SetProperty(mProp, DataNode(obj));
            }
            break;
    }
    mLastKeyFrameIndex = idx;
}

int BoolKeys::BoolAt(float frame, bool& b){
    MILO_ASSERT(size(), 0x25C);
    return AtFrame(frame, b);
}

void BoolKeys::SetFrame(float frame, float blend){
    if(!mProp || !mTarget || !size()) return;
    int idx = 0;
    if(mPropExceptionID == kNoException){
        bool b;
        idx = BoolAt(frame, b);
        if(mInterpolation != kStep || mLastKeyFrameIndex != idx){
            mTarget->SetProperty(mProp, DataNode(b));
        }
    }
    else if(mPropExceptionID == kHandleInterp) {
        bool b;
        idx = BoolAt(frame, b);
        if(mLastKeyFrameIndex != idx){
            sInterpMessage.SetType(mInterpHandler);
            sInterpMessage[0] = DataNode(b);
            sInterpMessage[1] = DataNode(frame);
            mTarget->Handle(sInterpMessage, true);
        }
    }
    mLastKeyFrameIndex = idx;
}

int QuatKeys::QuatAt(float frame, Hmx::Quat& quat){
    MILO_ASSERT(size(), 0x281);
    float ref = 0.0f;
    const Key<Hmx::Quat>* prev;
    const Key<Hmx::Quat>* next;
    int at = AtFrame(frame, prev, next, ref);
    if(mInterpolation == kSpline) QuatSpline(*this, prev, next, ref, quat);
    else switch(mInterpolation){
        case kStep:
            quat = prev->value;
            break;
        case kLinear:
            FastInterp(prev->value, next->value, ref, quat);
            break;
        case kSlerp:
            Interp(prev->value, next->value, ref, quat);
            break;
        case kInterp5:
            FastInterp(prev->value, next->value, ref * ref * ref, quat);
            break;
        case kInterp6:
            FastInterp(prev->value, next->value, -(ref * ref * ref - 1.0f), quat);
            break;
    }
    return at;
}

void QuatKeys::SetFrame(float frame, float blend){
    if(!mProp || !mTarget || !size()) return;
    int idx = 0;
    if(mPropExceptionID == kTransQuat){
        if(mTrans != mTarget){
            mTrans = dynamic_cast<RndTransformable*>(mTarget.Ptr());
        }
        Vector3 v48;
        MakeScale(mTrans->LocalXfm().m, v48);
        if(v48.x){ // FIXME: this condition is wrong
            mVec = v48;
        }
        else v48 = mVec;
        Hmx::Quat quat;
        Hmx::Matrix3 mtx;
        idx = QuatAt(frame, quat);
        MakeRotMatrix(quat, mtx);
        Scale(v48, mtx, mtx);
        mTrans->SetLocalRot(mtx);
    }
    mLastKeyFrameIndex = idx;
}

int Vector3Keys::Vector3At(float frame, Vector3& vec){
    MILO_ASSERT(size(), 0x2D8);
    float ref = 0.0f;
    const Key<Vector3>* prev;
    const Key<Vector3>* next;
    int idx = AtFrame(frame, prev, next, ref);
    switch(mInterpolation){
        case kNoException:
            vec = prev->value;
            break;
        case kTransQuat:
            Interp(prev->value, next->value, ref, vec);
            break;
        case kTransScale:
            InterpVector(*this, prev, next, ref, true, vec, 0);
            break;
        case kDirEvent:
            Interp(prev->value, next->value, (ref * -2.0f + 3.0f) * ref * ref, vec);
            break;
        case kHandleInterp:
            Interp(prev->value, next->value, ref * ref * ref, vec);
            break;
        case kMacro:
            ref = 1.0f - ref;
            Interp(prev->value, next->value, -(ref * ref * ref - 1.0f), vec);
            break;
    }
    return idx;
}

void Vector3Keys::SetFrame(float frame, float blend){
    if(!mProp || !mTarget || !size()) return;
    int idx = 0;
    switch(mPropExceptionID){
        case kTransScale:
            if(mTrans != mTarget) mTrans = dynamic_cast<RndTransformable*>(mTarget.Ptr());
            Vector3 v70;
            Hmx::Matrix3 m40;
            Normalize(mTrans->LocalXfm().m, m40);
            MakeEuler(m40, v70);
            Hmx::Matrix3 m64;
            MakeRotMatrix(v70, m64, false);
            Vector3 v7c;
            idx = Vector3At(frame, v7c);
            Scale(v7c, m64, m64);
            mTrans->SetLocalRot(m64);
            break;
        case kTransPos:
            if(mTrans != mTarget) mTrans = dynamic_cast<RndTransformable*>(mTarget.Ptr());
            Vector3 v88;
            idx = Vector3At(frame, v88);
            mTrans->SetLocalPos(v88.x, v88.y, v88.z);
            break;
        default: break;
    }
    mLastKeyFrameIndex = idx;
}

int SymbolKeys::SymbolAt(float frame, Symbol& sym){
    MILO_ASSERT(size(), 0x322);
    return AtFrame(frame, sym);
}

void SymbolKeys::SetFrame(float frame, float blend){
    if(!mProp || !mTarget || !size()) return;
    int idx = 0;
    switch(mPropExceptionID){
        case kHandleInterp:
            float ref = 0.0f;
            const Key<Symbol>* prev;
            const Key<Symbol>* next;
            idx = AtFrame(frame, prev, next, ref);
            sInterpMessage.SetType(mInterpHandler);
            sInterpMessage[0] = DataNode(prev->value);
            sInterpMessage[1] = DataNode(next->value);
            sInterpMessage[2] = DataNode(ref);
            sInterpMessage[3] = DataNode(next->frame);
            if(idx >= 1) sInterpMessage[4] = DataNode((*this)[idx - 1].value);
            else sInterpMessage[4] = DataNode(0);
            mTarget->Handle(sInterpMessage, true);
            break;
        case kMacro:
            Symbol s;
            idx = SymbolAt(frame, s);
            if(mInterpolation != kStep || mLastKeyFrameIndex != idx){
                mTarget->SetProperty(mProp, DataNode(DataGetMacro(s)->Int(0)));
            }
            break;
        default: break;
    }
    switch(mInterpolation){
        case kStep:
            // more happens here
            break;
        case kLinear:
            Symbol s;
            idx = SymbolAt(frame, s);
            mTarget->SetProperty(mProp, DataNode(s));
            break;
        default: break;
    }
    mLastKeyFrameIndex = idx;
}

int FloatKeys::SetKey(float frame){
    if(!mProp || !mTarget.Ptr()) return -1;
    else {
        int retVal = PropKeys::SetKey(frame);
        if(retVal < 0) retVal = Add(0, frame, false);
        SetToCurrentVal(retVal);
        return retVal;
    }
}

int ColorKeys::SetKey(float frame){
    if(!mProp || !mTarget.Ptr()) return -1;
    else {
        int retVal = PropKeys::SetKey(frame);
        if(retVal < 0) retVal = Add(Hmx::Color(0), frame, false);
        SetToCurrentVal(retVal);
        return retVal;
    }
}

int ObjectKeys::SetKey(float frame){
    if(!mProp || !mTarget.Ptr()) return -1;
    else {
        int retVal = PropKeys::SetKey(frame);
        if(retVal < 0) retVal = ObjKeys::Add(0, frame, false);
        SetToCurrentVal(retVal);
        return retVal;
    }
}

int BoolKeys::SetKey(float frame){
    if(!mProp || !mTarget.Ptr()) return -1;
    else {
        int retVal = PropKeys::SetKey(frame);
        if(retVal < 0) retVal = Add(true, frame, false);
        SetToCurrentVal(retVal);
        return retVal;
    }
}

int QuatKeys::SetKey(float frame){
    if(!mProp || !mTarget.Ptr()) return -1;
    else {
        int retVal = PropKeys::SetKey(frame);
        if(retVal < 0) retVal = Add(Hmx::Quat(), frame, false);
        SetToCurrentVal(retVal);
        return retVal;
    }
}

int Vector3Keys::SetKey(float frame){
    if(!mProp || !mTarget.Ptr()) return -1;
    else {
        int retVal = PropKeys::SetKey(frame);
        if(retVal < 0) retVal = Add(Vector3(), frame, false);
        SetToCurrentVal(retVal);
        return retVal;
    }
}

int SymbolKeys::SetKey(float frame){
    if(!mProp || !mTarget.Ptr()) return -1;
    else {
        int retVal = PropKeys::SetKey(frame);
        if(retVal < 0) retVal = Add(Symbol(), frame, false);
        SetToCurrentVal(retVal);
        return retVal;
    }
}

void FloatKeys::SetToCurrentVal(int i){
    (*this)[i].value = mTarget->Property(mProp, true)->Float(0);
}

void ColorKeys::SetToCurrentVal(int i){
    (*this)[i].value = Hmx::Color(mTarget->Property(mProp, true)->Int(0));
}

void ObjectKeys::SetToCurrentVal(int i){
    if(mPropExceptionID != kDirEvent){
        (*this)[i].value = ObjectStage(mTarget->Property(mProp, true)->GetObj(0));
    }
}

void BoolKeys::SetToCurrentVal(int i){
    (*this)[i].value = mTarget->Property(mProp, true)->Int(0);
}

void QuatKeys::SetToCurrentVal(int i){
    if(mPropExceptionID == kTransQuat){
        if(mTrans != mTarget){
            mTrans = dynamic_cast<RndTransformable*>(mTarget.Ptr());
        }
        Hmx::Matrix3 m38;
        Normalize(mTrans->LocalXfm().m, m38);
        Hmx::Quat q48;
        Hmx::Quat q58(m38);
        Normalize(q58, q48);
        (*this)[i].value = q48;
    }
}

void Vector3Keys::SetToCurrentVal(int i){
    switch(mPropExceptionID){
        case kTransScale:
            if(mTrans != mTarget){
                mTrans = dynamic_cast<RndTransformable*>(mTarget.Ptr());
            }
            Vector3 v28;
            MakeScale(mTrans->LocalXfm().m, v28);
            (*this)[i].value = v28;
            break;
        case kTransPos:
            if(mTrans != mTarget){
                mTrans = dynamic_cast<RndTransformable*>(mTarget.Ptr());
            }
            (*this)[i].value = mTrans->LocalXfm().v;
            break;
    }
}

void SymbolKeys::SetToCurrentVal(int i){
    if(mPropExceptionID == kMacro){
        if(0 < i){
            (*this)[i].value = (*this)[i - 1].value;
        }
    }
    else (*this)[i].value = mTarget->Property(mProp, true)->Sym(0);
}

// then finally, Copys

void FloatKeys::Copy(const PropKeys* keys){
    PropKeys::Copy(keys);
    clear();
    if(keys->mKeysType == mKeysType){
        const FloatKeys* newKeys = dynamic_cast<const FloatKeys*>(keys);
        insert(begin(), newKeys->begin(), newKeys->end());
    }
}

void SymbolKeys::Copy(const PropKeys* keys){
    PropKeys::Copy(keys);
    clear();
    if(keys->mKeysType == mKeysType){
        const SymbolKeys* newKeys = dynamic_cast<const SymbolKeys*>(keys);
        // retail calls some function (this vector, this vector, newKeys' vector, newKeys' vector end)
        // not so sure that it's insert, or if it is, what its params are
        insert(begin(), newKeys->begin(), newKeys->end());
    }
}