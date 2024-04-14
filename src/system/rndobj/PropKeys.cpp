#include "rndobj/PropKeys.h"
#include "obj/ObjectStage.h"
#include "math/Rot.h"

unsigned short PropKeys::gRev = 0;
Message PropKeys::sInterpMessage(Symbol(), DataNode(0), DataNode(0), DataNode(0), DataNode(0), DataNode(0));

void SetPropKeysRev(int rev){
    PropKeys::gRev = rev;
}

static const char* filler = "a;oweifjaoweiaoweuihf";

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

void PropKeys::ChangeFrame(int i, float f, bool b){
    unsigned int keyType = mKeysType;
    switch((keyType)){
        case kFloat:
            Keys<float, float>* fKeys = AsFloatKeys();
            fKeys->operator[](i).frame = f;
            break;
        case kColor:
            AsColorKeys();
            break;
        case kObject:
            AsObjectKeys();
            break;
        case kBool:
            AsBoolKeys();
            break;
        case kSymbol:
            AsSymbolKeys();
            break;
        case kVector3:
            AsVector3Keys();
            break;
        case kQuat:
            AsQuatKeys();
            break;
        default:
            MILO_WARN("can not replace frame, unknown type");
            break;
    }
    if(b) ReSort();
}

void Interp(const ObjectStage& stage1, const ObjectStage& stage2, float f, Hmx::Object*& obj){
    if(f < 1.0f) &stage2 = &stage1;
    obj = (Hmx::Object*)stage2;
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
    TextStream* ts = &TheDebug;
    *ts << "      target: " << mTarget.Ptr() << "\n";
    *ts << "      property: " << mProp << "\n";
    *ts << "      interpolation: " << mInterpolation << "\n";

    float theFloat = 0.0f;
    for(int i = 0; i < NumKeys(); i++){
        FrameFromIndex(i, theFloat);
        *ts << "      " << theFloat << " -> ";
        switch((unsigned int)mKeysType){
            case kFloat:
                Keys<float, float>* fKeys = AsFloatKeys();
                *ts << fKeys->operator[](i).value;
                break;
            case kColor:
                Keys<Hmx::Color, Hmx::Color>* cKeys = AsColorKeys();
                *ts << cKeys->operator[](i).value;
                break;
            case kObject:
                Keys<ObjectStage, Hmx::Object*>* oKeys = AsObjectKeys();
                *ts << (Hmx::Object*)oKeys->operator[](i).value;
                break;
            case kBool:
                Keys<bool, bool>* bKeys = AsBoolKeys();
                *ts << bKeys->operator[](i).value;
                break;
            case kQuat:
                Keys<Hmx::Quat, Hmx::Quat>* qKeys = AsQuatKeys();
                *ts << qKeys->operator[](i).value;
                break;
            case kVector3:
                Keys<Vector3, Vector3>* vKeys = AsVector3Keys();
                *ts << vKeys->operator[](i).value;
                break;
            case kSymbol:
                Keys<Symbol, Symbol>* sKeys = AsSymbolKeys();
                *ts << sKeys->operator[](i).value;
                break;
        }
        *ts << "\n";
    }
}

ExceptionID PropKeys::PropExceptionID(Hmx::Object* o, DataArray* arr){
    if(!this || !o) return kNoException;
    String str;
    arr->Print(str, kDataArray, true);
    str = str.substr(1, strlen(str.c_str()) - 2);
    bool b1 = false;
    if(str == "rotation"){
        if(IsASubclass(o->ClassName(), "Trans")) b1 = true;
        if(b1) return kTransQuat;
    }
    b1 = false;
    if(str == "scale"){
        if(IsASubclass(o->ClassName(), "Trans")) b1 = true;
        if(b1) return kTransScale;
    }
    b1 = false;
    if(str == "position"){
        if(IsASubclass(o->ClassName(), "Trans")) b1 = true;
        if(b1) return kTransPos;
    }
    b1 = false;
    if(str == "event"){
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
                    // const objType* c = dynamic_cast<const objType*>(o);
                }
            }
        }
    }
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

void PropKeys::SetInterpHandler(Symbol sym){
    mInterpHandler = sym;
    SetPropExceptionID();
}
