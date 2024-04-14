#include "rndobj/PropKeys.h"

unsigned short PropKeys::gRev = 0;

PropKeys::PropKeys(Hmx::Object* o1, Hmx::Object* o2) : mTarget(o1, o2), mProp(0), mTrans(0),
    mKeysType(kFloat), mInterpolation(kStep), mPropExceptionID(kNoException), 
    mInterpHandler(), mLastKeyFrameIndex(-2) {
    
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

void PropKeys::ChangeFrame(int i, float f, bool b){
    switch(mKeysType){
        case kFloat:
            AsFloatKeys();
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
