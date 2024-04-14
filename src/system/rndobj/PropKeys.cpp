#include "rndobj/PropKeys.h"
#include "obj/ObjectStage.h"
#include "math/Rot.h"

unsigned short PropKeys::gRev = 0;
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
    switch((unsigned int)(mKeysType)){
        case kFloat:
            Keys<float, float>* fKeys = AsFloatKeys();
            fKeys->operator[](i).frame = f;
            break;
        case kColor:
            AsColorKeys()->operator[](i).frame = f;
            break;
        case kObject:
            AsObjectKeys()->operator[](i).frame = f;
            break;
        case kBool:
            AsBoolKeys()->operator[](i).frame = f;
            break;
        case kSymbol:
            AsSymbolKeys()->operator[](i).frame = f;
            break;
        case kVector3:
            AsVector3Keys()->operator[](i).frame = f;
            break;
        case kQuat:
            AsQuatKeys()->operator[](i).frame = f;
            break;
        default:
            MILO_WARN("can not replace frame, unknown type");
            break;
    }
    if(b) ReSort();
}

void PropKeys::ReSort(){
    switch((unsigned int)mKeysType){
        case kFloat:
        case kColor:
        case kObject:
        case kBool:
        case kSymbol:
        case kVector3:
        case kQuat:
            break;
    }
}

void Interp(const ObjectStage& stage1, const ObjectStage& stage2, float f, Hmx::Object*& obj){
    if(f < 1.0f) &stage2 = &stage1;
    obj = stage2.Ptr();
}

SAVE_OBJ(PropKeys, 0xCF);

void PropKeys::Load(BinStream& bs){
    if(gRev < 7) MILO_FAIL("PropKeys::Load should not be called before version 7");
    else {
        int animType;
        bs >> animType;
        mKeysType = (AnimKeysType)animType;
        bs >> mTarget;
        bs >> mProp;

        int anotherVal;
        if(gRev >= 8) bs >> anotherVal;
        else anotherVal = (mKeysType == (unsigned int)kObject || mKeysType == (unsigned int)kBool) == 0;

        if(gRev < 0xB && anotherVal == 4){
            mKeysType = kSymbol;
            mInterpolation = kStep;
        }
        else mInterpolation = (Interpolation)anotherVal;

        if(gRev > 9){
            Symbol sym;
            bs >> sym;
            if(!sym.IsNull()){
                SetInterpHandler(sym);
            }
        }

        if(gRev > 10){
            int exceptID;
            bs >> exceptID;
            mPropExceptionID = (ExceptionID)exceptID;
        }

        if(gRev > 0xC){
            bool b;
            bs >> b;
            unk18lastbit = b;
        }
        SetPropExceptionID();
    }
}

void PropKeys::Print(){
    TextStream& ts = TheDebug;
    ts << "      target: " << mTarget.Ptr() << "\n";
    ts << "      property: " << mProp << "\n";
    ts << "      interpolation: " << mInterpolation << "\n";

    for(int i = 0; i < NumKeys(); i++){
        float frame = 0.0f;
        FrameFromIndex(i, frame);
        ts << "      " << frame << " -> ";
        switch((unsigned int)mKeysType){
            case kFloat:
                Keys<float, float>* fKeys = AsFloatKeys();
                ts << fKeys->operator[](i).value;
                break;
            case kColor:
                Keys<Hmx::Color, Hmx::Color>* cKeys = AsColorKeys();
                ts << cKeys->operator[](i).value;
                break;
            case kObject:
                Keys<ObjectStage, Hmx::Object*>* oKeys = AsObjectKeys();
                ts << (Hmx::Object*)oKeys->operator[](i).value;
                break;
            case kBool:
                Keys<bool, bool>* bKeys = AsBoolKeys();
                ts << bKeys->operator[](i).value;
                break;
            case kQuat:
                Keys<Hmx::Quat, Hmx::Quat>* qKeys = AsQuatKeys();
                ts << qKeys->operator[](i).value;
                break;
            case kVector3:
                Keys<Vector3, Vector3>* vKeys = AsVector3Keys();
                ts << vKeys->operator[](i).value;
                break;
            case kSymbol:
                Keys<Symbol, Symbol>* sKeys = AsSymbolKeys();
                ts << sKeys->operator[](i).value;
                break;
        }
        ts << "\n";
    }
}

ExceptionID PropKeys::PropExceptionID(Hmx::Object* o, DataArray* arr){
    if(!this || !o) return kNoException;
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
    if(!mInterpHandler.IsNull()) mPropExceptionID = kNoException;
    else {
        if(mPropExceptionID != (unsigned int)kMacro){
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

// disabled the reading from binstream for now because vector::resize is broken lol
void SymbolKeys::Load(BinStream& bs){
    PropKeys::Load(bs);
    // bs >> *this;
}

void SymbolKeys::Save(BinStream& bs){
    PropKeys::Save(bs);
    bs << *this;
}

void FloatKeys::Load(BinStream& bs){
    PropKeys::Load(bs);
    // bs >> *this;
}

void FloatKeys::Save(BinStream& bs){
    PropKeys::Save(bs);
    bs << *this;
}

int FloatKeys::RemoveKey(int i){
    erase(begin() + i);
    return size();
}

float FloatKeys::StartFrame(){
    if(size() != 0){
        return (*this)[0].frame;
    }
    else return 0.0f;
}

float FloatKeys::EndFrame(){
    if(size() != 0){
        return this->back().frame;
    }
    else return 0.0f;
}

bool FloatKeys::FrameFromIndex(int idx, float& f){
    if(idx >= size()) return false;
    else f = (*this)[idx].frame;
    return true;
}

int FloatKeys::NumKeys(){ return size(); }
