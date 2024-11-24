#include "rndobj/PropKeys.h"
#include "math/Utl.h"
#include "obj/ObjectStage.h"
#include "obj/Utl.h"
#include "obj/DataUtl.h"
#include "math/Rot.h"
#include "os/System.h"

unsigned short PropKeys::gRev = 0;
Hmx::Object* ObjectStage::sOwner = 0;
Message PropKeys::sInterpMessage(gNullStr, 0, 0, 0, 0, 0);

void SetPropKeysRev(int rev){
    PropKeys::gRev = rev;
}

float CalcSpline(float, float*){
    
}

BinStream& operator>>(BinStream& bs, ObjectStage& stage){
    ObjectDir* dir = nullptr;
    if(PropKeys::gRev > 8){
        ObjPtr<ObjectDir, ObjectDir> dirPtr(stage.Owner(), nullptr);
        dirPtr.Load(bs, true, dir);
        dir = dirPtr.Ptr();
    }
    stage.Load(bs, true, dir);
    return bs;
}

BinStream& operator<<(BinStream& bs, const ObjectStage& stage){
    ObjPtr<ObjectDir, ObjectDir> dirPtr(stage.Owner(), (stage.Ptr()) ? stage.Ptr()->Dir() : nullptr);
    bs << dirPtr;
    bs << ObjPtr<Hmx::Object, ObjectDir>(stage.Owner(), stage.Ptr());
    return bs;
}

PropKeys::PropKeys(Hmx::Object* targetOwner, Hmx::Object* target) : mTarget(targetOwner, target), mProp(0), mTrans(0), mInterpHandler(),
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
        DataArray* nodeArr = node.Array();
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
            if(IsFabsZero(frame - f))
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

void PropKeys::ChangeFrame(int idx, float new_frame, bool sort){
    switch(mKeysType){
        case kFloat:
            AsFloatKeys()[idx].frame = new_frame;
            break;
        case kColor:
            AsColorKeys()[idx].frame = new_frame;
            break;
        case kObject:
            AsObjectKeys()[idx].frame = new_frame;
            break;
        case kBool:
            AsBoolKeys()[idx].frame = new_frame;
            break;
        case kSymbol:
            AsSymbolKeys()[idx].frame = new_frame;
            break;
        case kVector3:
            AsVector3Keys()[idx].frame = new_frame;
            break;
        case kQuat:
            AsQuatKeys()[idx].frame = new_frame;
            break;
        default:
            MILO_WARN("can not replace frame, unknown type");
            break;
    }
    if(sort) ReSort();
}

// 80627a64 in retail
void PropKeys::ReSort(){
    switch(mKeysType){
        case kFloat:
            // mystery vector method - fn_806280C0 in retail, scratch: https://decomp.me/scratch/5Vpiu
            AsFloatKeys().Sort();
            break;
        case kColor:
            // mystery vector method - fn_80627FEC in retail
            AsColorKeys().Sort();
            break;
        case kObject:
            // mystery vector method - fn_80627F0C in retail
            AsObjectKeys().Sort();
            break;
        case kBool:
            // mystery vector method - fn_80627E24 in retail, scratch: https://decomp.me/scratch/7TOeo
            AsBoolKeys().Sort();
            break;
        case kSymbol:
            // mystery vector method - fn_80627D50 in retail
            AsSymbolKeys().Sort();
            break;
        case kVector3:
            // mystery vector method - fn_80627C7C in retail
            AsVector3Keys().Sort();
            break;
        case kQuat:
            // mystery vector method - fn_80627B64 in retail
            AsQuatKeys().Sort();
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
                ts << AsFloatKeys()[i].value;
                break;
            case kColor:
                ts << AsColorKeys()[i].value;
                break;
            case kObject:
                ts << AsObjectKeys()[i].value;
                break;
            case kBool:
                ts << AsBoolKeys()[i].value;
                break;
            case kQuat:
                ts << AsQuatKeys()[i].value;
                break;
            case kVector3:
                ts << AsVector3Keys()[i].value;
                break;
            case kSymbol:
                ts << AsSymbolKeys()[i].value;
                break;
        }
        ts << "\n";
    }
}

unsigned int PropKeys::PropExceptionID(Hmx::Object* o, DataArray* arr){
    if(!o || !arr) return kNoException;
    String propString;
    arr->Print(propString, kDataArray, true);
    propString = propString.substr(1, propString.length() - 2);
    if(propString == "rotation" && IsASubclass(o->ClassName(), "Trans")){
        return kTransQuat;
    }
    if(propString == "scale" && IsASubclass(o->ClassName(), "Trans")){
        return kTransScale;
    }
    if(propString == "position" && IsASubclass(o->ClassName(), "Trans")){
        return kTransPos;
    }
    if(propString == "event" && IsASubclass(o->ClassName(), "ObjectDir")){
        return kDirEvent;
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

// retail scratch work: https://decomp.me/scratch/a1wwv
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
                float points[4];
                points[1] = prev->value;
                points[2] = next->value;
                int idx = prev->value == begin()->value;
                if(idx == 0){
                    points[0] = prev->value;
                }
                else {
                    points[0] = this->at(idx - 1).value;
                }
                if(idx == size() - 1){
                    points[3] = next->value;
                }
                else {
                    points[3] = this->at(idx + 1).value;
                }
                fl = CalcSpline(ref, points);
            }
            break;
        case kHermite:
            Interp(prev->value, next->value, ref * ref * (ref * -2.0f + 3.0f), fl);
            break;
        case kEaseIn:
            Interp(prev->value, next->value, ref * ref * ref, fl);
            break;
        case kEaseOut:
            ref = 1.0f - ref;
            Interp(prev->value, next->value, -(ref * ref * ref - 1.0f), fl);
            break;
    }
    return at;
}

void FloatKeys::SetFrame(float frame, float blend){
    if(!mProp || !mTarget || !size()) return;
    int idx;
    if(mPropExceptionID == kHandleInterp){
        const Key<float>* prev;
        const Key<float>* next;
        float ref = 0.0f;
        idx = AtFrame(frame, prev, next, ref);
        sInterpMessage.SetType(mInterpHandler);
        sInterpMessage[0] = prev->value;
        sInterpMessage[1] = next->value;
        sInterpMessage[2] = ref;
        sInterpMessage[3] = next->frame;
        if(idx >= 1) sInterpMessage[4] = (*this)[idx - 1].value;
        else sInterpMessage[4] = 0;
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
    switch(mInterpolation){
        case kStep:
            const Key<Hmx::Color>* prevstep;
            const Key<Hmx::Color>* nextstep;
            float refstep;
            at = AtFrame(frame, prevstep, nextstep, refstep);
            color = prevstep->value;
            break;
        case kLinear:
            at = AtFrame(frame, color);
            break;
        case kEaseIn:
            const Key<Hmx::Color>* prev5;
            const Key<Hmx::Color>* next5;
            float ref5;
            AtFrame(frame, prev5, next5, ref5);
            if(prev5) Interp(prev5->value, next5->value, ref5 * ref5 * ref5, color);
            break;
        case kEaseOut:
            const Key<Hmx::Color>* prev;
            const Key<Hmx::Color>* next;
            float ref;
            AtFrame(frame, prev, next, ref);
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
        case kHandleInterp: {
            const Key<ObjectStage>* prev;
            const Key<ObjectStage>* next;
            float ref = 0.0f;
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
        }
        default: {
            Hmx::Object* obj;
            idx = ObjectAt(frame, obj);
            if(mInterpolation != kStep || mLastKeyFrameIndex != idx){
                mTarget->SetProperty(mProp, DataNode(obj));
            }
            break;
        }
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
    const Key<Hmx::Quat>* prev;
    const Key<Hmx::Quat>* next;
    float ref = 0.0f;
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
        case kEaseIn:
            FastInterp(prev->value, next->value, ref * ref * ref, quat);
            break;
        case kEaseOut:
            ref = 1.0f - ref;
            FastInterp(prev->value, next->value, -(ref * ref * ref - 1.0f), quat);
            break;
    }
    return at;
}

inline bool CheckVectorDiff(const Vector3& v1, const Vector3& v2, float f){
    return std::fabs(v1.x - v2.x) < f && std::fabs(v1.y - v2.y) < f && std::fabs(v1.z - v2.z) < f;
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
        if(CheckVectorDiff(mVec, v48, 0.001f)){
            v48 = mVec;
        }
        else mVec = v48;
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
            Interp(prev->value, next->value, ref * ref * (ref * -2.0f + 3.0f), vec);
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
        case kTransScale: {
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
        }
        case kTransPos: {
            if(mTrans != mTarget) mTrans = dynamic_cast<RndTransformable*>(mTarget.Ptr());
            Vector3 v88;
            idx = Vector3At(frame, v88);
            mTrans->SetLocalPos(v88.x, v88.y, v88.z);
            break;
        }
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
        case kHandleInterp: {
            const Key<Symbol>* prev;
            const Key<Symbol>* next;
            float ref = 0.0f;
            idx = AtFrame(frame, prev, next, ref);
            sInterpMessage.SetType(mInterpHandler);
            sInterpMessage[0] = prev->value;
            sInterpMessage[1] = next->value;
            sInterpMessage[2] = ref;
            sInterpMessage[3] = next->frame;
            if(idx >= 1) sInterpMessage[4] = (*this)[idx - 1].value;
            else sInterpMessage[4] = 0;
            mTarget->Handle(sInterpMessage, true);
            break;
        }
        case kMacro: {
            Symbol s;
            idx = SymbolAt(frame, s);
            if(mInterpolation != kStep || mLastKeyFrameIndex != idx){
                mTarget->SetProperty(mProp, DataNode(DataGetMacro(s)->Int(0)));
            }
            break;
        }
        default:
            break;
    }
    switch(mInterpolation){
        case kStep: {
            int loc8c = -1;
            int loc90 = -1;
            std::vector<Symbol> vec;
            KeysLessEq(frame, loc8c, loc90);
            if(loc8c != -1){
                int i = loc8c;
                if(unk30){
                    MinEq(loc8c, unk2c + 1);
                    i = loc8c;
                }
                for(; i <= loc90; i++){
                    Key<Symbol>& cur = (*this)[i];
                    if(i < unk28 || i > unk2c){
                        mTarget->SetProperty(mProp, cur.value);
                    }
                }
            }
            unk28 = loc8c;
            unk2c = loc90;
            break;
        }
        case kLinear: {
            Symbol s;
            idx = SymbolAt(frame, s);
            mTarget->SetProperty(mProp, DataNode(s));
            break;
        }
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
        if(retVal < 0) retVal = Add(Hmx::Quat(0,0,0,0), frame, false);
        SetToCurrentVal(retVal);
        return retVal;
    }
}

int Vector3Keys::SetKey(float frame){
    if(!mProp || !mTarget.Ptr()) return -1;
    else {
        int retVal = PropKeys::SetKey(frame);
        if(retVal < 0) retVal = Add(Vector3(0,0,0), frame, false);
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
    (*this)[i].value = mTarget->Property(mProp, true)->Float();
}

void ColorKeys::SetToCurrentVal(int i){
    Key<Hmx::Color>& cur = (*this)[i];
    cur.value = Hmx::Color(mTarget->Property(mProp, true)->Int());
}

void ObjectKeys::SetToCurrentVal(int i){
    if(mPropExceptionID != kDirEvent){
        (*this)[i].value = ObjectStage(mTarget->Property(mProp, true)->GetObj());
    }
}

void BoolKeys::SetToCurrentVal(int i){
    (*this)[i].value = mTarget->Property(mProp, true)->Int();
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
        case kTransScale: {
            if(mTrans != mTarget){
                mTrans = dynamic_cast<RndTransformable*>(mTarget.Ptr());
            }
            Vector3 v28;
            MakeScale(mTrans->LocalXfm().m, v28);
            (*this)[i].value = v28;
            break;
        }
        case kTransPos: {
            if(mTrans != mTarget){
                mTrans = dynamic_cast<RndTransformable*>(mTarget.Ptr());
            }
            (*this)[i].value = mTrans->LocalXfm().v;
            break;
        }
    }
}

void SymbolKeys::SetToCurrentVal(int i){
    if(mPropExceptionID == kMacro){
        if(0 < i){
            (*this)[i].value = (*this)[i - 1].value;
        }
    }
    else (*this)[i].value = mTarget->Property(mProp, true)->Sym();
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

void ColorKeys::Copy(const PropKeys* keys){
    PropKeys::Copy(keys);
    clear();
    if(keys->mKeysType == mKeysType){
        const ColorKeys* newKeys = dynamic_cast<const ColorKeys*>(keys);
        insert(begin(), newKeys->begin(), newKeys->end());
    }
}

void ObjectKeys::Copy(const PropKeys* keys){
    PropKeys::Copy(keys);
    clear();
    if(keys->mKeysType == mKeysType){
        const ObjectKeys* newKeys = dynamic_cast<const ObjectKeys*>(keys);
        insert(begin(), newKeys->begin(), newKeys->end());
    }
}

void BoolKeys::Copy(const PropKeys* keys){
    PropKeys::Copy(keys);
    clear();
    if(keys->mKeysType == mKeysType){
        const BoolKeys* newKeys = dynamic_cast<const BoolKeys*>(keys);
        insert(begin(), newKeys->begin(), newKeys->end());
    }
}

void QuatKeys::Copy(const PropKeys* keys){
    PropKeys::Copy(keys);
    clear();
    if(keys->mKeysType == mKeysType){
        const QuatKeys* newKeys = dynamic_cast<const QuatKeys*>(keys);
        insert(begin(), newKeys->begin(), newKeys->end());
    }
}

void Vector3Keys::Copy(const PropKeys* keys){
    PropKeys::Copy(keys);
    clear();
    if(keys->mKeysType == mKeysType){
        const Vector3Keys* newKeys = dynamic_cast<const Vector3Keys*>(keys);
        insert(begin(), newKeys->begin(), newKeys->end());
    }
}

void SymbolKeys::Copy(const PropKeys* keys){
    PropKeys::Copy(keys);
    clear();
    if(keys->mKeysType == mKeysType){
        const SymbolKeys* newKeys = dynamic_cast<const SymbolKeys*>(keys);
        insert(begin(), newKeys->begin(), newKeys->end());
    }
}
