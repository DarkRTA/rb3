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
    switch(mKeysType){
        case kFloat:
            (*AsFloatKeys())[i].frame = f;
            break;
        case kColor:
            (*AsColorKeys())[i].frame = f;
            break;
        case kObject:
            (*AsObjectKeys())[i].frame = f;
            break;
        case kBool:
            (*AsBoolKeys())[i].frame = f;
            break;
        case kSymbol:
            (*AsSymbolKeys())[i].frame = f;
            break;
        case kVector3:
            (*AsVector3Keys())[i].frame = f;
            break;
        case kQuat:
            (*AsQuatKeys())[i].frame = f;
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
    if(f < 1.0f) &stage2 = &stage1;
    obj = stage2.Ptr();
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
            mKeysType = kSymbol;
            mInterpolation = kStep;
        }
        else mInterpolation = iVal;

        if(gRev > 9){
            Symbol sym;
            bs >> sym;
            if(!sym.IsNull()){
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
    mInterpHandler = keys->mInterpHandler;
    mKeysType = keys->mKeysType;
    mLastKeyFrameIndex = keys->mLastKeyFrameIndex;
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
                ts << (*AsFloatKeys())[i].value;
                break;
            case kColor:
                ts << (*AsColorKeys())[i].value;
                break;
            case kObject:
                ts << (Hmx::Object*)((*AsObjectKeys())[i].value);
                break;
            case kBool:
                ts << (*AsBoolKeys())[i].value;
                break;
            case kQuat:
                ts << (*AsQuatKeys())[i].value;
                break;
            case kVector3:
                ts << (*AsVector3Keys())[i].value;
                break;
            case kSymbol:
                ts << (*AsSymbolKeys())[i].value;
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
    if(!mInterpHandler.IsNull()) mPropExceptionID = kHandleInterp;
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

void SymbolKeys::Load(BinStream& bs){
    PropKeys::Load(bs);
    bs >> *this;
}

void SymbolKeys::Save(BinStream& bs){
    PropKeys::Save(bs);
    bs << *this;
}

int SymbolKeys::SymbolAt(float f, Symbol& sym){
    MILO_ASSERT(size(), 0x322);
    return AtFrame(f, sym);
}

int FloatKeys::SetKey(float frame){
    int retVal;
    if(!mProp || !mTarget.Ptr()) retVal = -1;
    else {
        retVal = PropKeys::SetKey(frame);
        // some vector method that takes in frame, a label that = 0, and 0
        SetToCurrentVal(retVal);
    }
    return retVal;
}

void FloatKeys::SetToCurrentVal(int i){
    (*this)[i].value = mTarget->Property(mProp, true)->Float(0);
}

void SymbolKeys::SetToCurrentVal(int i){
    if(mPropExceptionID == kMacro){
        if(0 < i){
            (*this)[i].value = (*this)[i - 1].value;
        }
    }
    else (*this)[i].value = mTarget->Property(mProp, true)->Sym(0);
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

void FloatKeys::Load(BinStream& bs){
    PropKeys::Load(bs);
    bs >> *this;
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
        return front().frame;
    }
    else return 0.0f;
}

float FloatKeys::EndFrame(){
    if(size() != 0){
        return back().frame;
    }
    else return 0.0f;
}

bool FloatKeys::FrameFromIndex(int idx, float& f){
    if(idx >= size()) return false;
    else f = (*this)[idx].frame;
    return true;
}

int FloatKeys::NumKeys(){ return size(); }
