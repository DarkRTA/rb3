#ifndef RNDOBJ_PROPKEYS_H
#define RNDOBJ_PROPKEYS_H
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "math/Color.h"
#include "math/Mtx.h"
#include "os/Debug.h"
#include "obj/ObjectStage.h"
#include "math/Key.h"
#include "obj/Msg.h"

class ObjKeys : public Keys<ObjectStage, Hmx::Object*> {
public:
    ObjKeys(Hmx::Object* o) : mOwner(o) {}
    Hmx::Object* mOwner; // 0x8

    // fn_80632140
    ObjKeys& operator=(const ObjKeys& keys){
        Hmx::Object* oldowner = ObjectStage::sOwner;
        if(this != &keys){
            resize(keys.size());
            ObjKeys::const_iterator keysit = keys.begin();
            for(ObjKeys::iterator it = begin(); it != end(); it++, keysit++){
                *it = *keysit;
            }
        }
        ObjectStage::sOwner = oldowner;
    }

    int Add(Hmx::Object* obj, float f, bool b){
        Hmx::Object* oldOwner = ObjectStage::sOwner;
        ObjectStage::sOwner = mOwner;
        int add = Keys<ObjectStage, Hmx::Object*>::Add(ObjectStage(obj), f, b);
        ObjectStage::sOwner = oldOwner;
        return add;
    }
};

class PropKeys : public ObjRef {
public:
    enum AnimKeysType {
        kFloat,
        kColor,
        kObject,
        kBool,
        kQuat,
        kVector3,
        kSymbol
    };

    enum Interpolation {
        kStep,
        kLinear,
        kSpline,
        kSlerp,
        kHermite,
        kInterp5,
        kInterp6
    };

    enum ExceptionID {
        kNoException,
        kTransQuat,
        kTransScale,
        kTransPos,
        kDirEvent,
        kHandleInterp,
        kMacro
    };

    PropKeys(Hmx::Object*, Hmx::Object*);
    virtual ~PropKeys();
    virtual Hmx::Object* RefOwner(){ return 0; }
    virtual void Replace(Hmx::Object*, Hmx::Object*){}
    virtual float StartFrame(){ return 0.0f; }
    virtual float EndFrame(){ return 0.0f; }
    virtual bool FrameFromIndex(int, float&){ return 0; }
    virtual void SetFrame(float f1, float f2){}
    virtual void CloneKey(int){}
    virtual int SetKey(float);
    virtual int RemoveKey(int){ return 0; }
    virtual int NumKeys(){ return 0; }
    virtual void SetToCurrentVal(int){}
    virtual int SetFrameException(float){ return 0; }
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);
    virtual void Copy(const PropKeys*);
    virtual Keys<float, float>& AsFloatKeys(){ MILO_ASSERT(false, 0xA7); return *(Keys<float, float>*)0; }
    virtual Keys<Hmx::Color, Hmx::Color>& AsColorKeys(){ MILO_ASSERT(false, 0xA9); return *(Keys<Hmx::Color, Hmx::Color>*)0; }
    virtual ObjKeys& AsObjectKeys(){ MILO_ASSERT(false, 0xAB); return *(ObjKeys*)0; }
    virtual Keys<bool, bool>& AsBoolKeys(){ MILO_ASSERT(false, 0xAD); return *(Keys<bool, bool>*)0; }
    virtual Keys<Hmx::Quat, Hmx::Quat>& AsQuatKeys(){ MILO_ASSERT(false, 0xAF); return *(Keys<Hmx::Quat, Hmx::Quat>*)0; }
    virtual Keys<Vector3, Vector3>& AsVector3Keys(){ MILO_ASSERT(false, 0xB1); return *(Keys<Vector3, Vector3>*)0; }
    virtual Keys<Symbol, Symbol>& AsSymbolKeys(){ MILO_ASSERT(false, 0xB3); return *(Keys<Symbol, Symbol>*)0; }
    virtual int FloatAt(float, float&){ MILO_ASSERT(false, 0xB6); return -1; }
    virtual int ColorAt(float, Hmx::Color&){ MILO_ASSERT(false, 0xB8); return -1; }
    virtual int ObjectAt(float, Hmx::Object*&){ MILO_ASSERT(false, 0xBA); return -1; }
    virtual int BoolAt(float, bool&){ MILO_ASSERT(false, 0xBC); return -1; }
    virtual int QuatAt(float, Hmx::Quat&){ MILO_ASSERT(false, 0xBE); return -1; }
    virtual int Vector3At(float, Vector3&){ MILO_ASSERT(false, 0xC0); return -1; }
    virtual int SymbolAt(float, Symbol&){ MILO_ASSERT(false, 0xC2); return -1; }

    void SetProp(DataNode&);
    void SetTarget(Hmx::Object*);
    void SetPropExceptionID();
    void ChangeFrame(int, float, bool);
    void ReSort();
    void SetInterpHandler(Symbol);
    void Print();
    void ResetLastKeyFrameIndex(){ mLastKeyFrameIndex = -2; }
    Symbol InterpHandler() const { return mInterpHandler; }
    static unsigned int PropExceptionID(Hmx::Object*, DataArray*);

    static unsigned short gRev;
    static Message sInterpMessage;

    ObjOwnerPtr<Hmx::Object, ObjectDir> mTarget; // 0x4
    DataArray* mProp; // 0x10
    RndTransformable* mTrans; // 0x14
    Symbol mInterpHandler; // 0x18
    
    // presumably, bits 10-31 of 0x1C would be mlastKeyFrameIndex?
    // mKeysType: bits 7-9 of 0x1C
    // interpolation: bits 4-6 of 0x1C
    // exception id is bits 1-3 of 0x1C
    // unknown is bit 0 of 0x1C
    unsigned int mLastKeyFrameIndex : 22;
    unsigned int mKeysType : 3; // represents the enum AnimKeysType
    unsigned int mInterpolation : 3; // represents the enum Interpolation
    unsigned int mPropExceptionID : 3; // represents the enum ExceptionID
    unsigned int unk18lastbit : 1;
};

void SetPropKeysRev(int);
float CalcSpline(float, float*); // putting this here for now, maybe it's better off in Key.h?

class FloatKeys : public PropKeys, public Keys<float, float> {
public:
    FloatKeys(Hmx::Object* o1, Hmx::Object* o2) : PropKeys(o1, o2) { mKeysType = kFloat; }
    virtual ~FloatKeys(){}
    virtual Keys<float, float>& AsFloatKeys(){ if(this) return *this; }
    virtual float StartFrame(){ return FirstFrame(); }
    virtual float EndFrame(){ return LastFrame(); }
    virtual bool FrameFromIndex(int idx, float& f){
        if(idx >= size()) return false;
        else f = (*this)[idx].frame;
        return true;
    }
    virtual void SetFrame(float f1, float f2);
    virtual void CloneKey(int idx){
        if(!mProp || !mTarget) return;
        if(idx >= 0 && idx < size()){
            Add((*this)[idx].value, (*this)[idx].frame, false);
        }
    }
    virtual int SetKey(float);
    virtual int RemoveKey(int idx){
        Remove(idx);
        return size();
    }
    virtual int NumKeys(){ return size(); }
    virtual void SetToCurrentVal(int);
    virtual void Save(BinStream& bs){
        PropKeys::Save(bs);
        bs << *this;
    }
    virtual void Load(BinStream& bs){
        PropKeys::Load(bs);
        bs >> *this;
    }
    virtual void Copy(const PropKeys*);
    virtual int FloatAt(float, float&);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
};

class ColorKeys : public PropKeys, public Keys<Hmx::Color, Hmx::Color> {
public:
    ColorKeys(Hmx::Object* o1, Hmx::Object* o2) : PropKeys(o1, o2) { mKeysType = kColor; }
    virtual ~ColorKeys(){}
    virtual Keys<Hmx::Color, Hmx::Color>& AsColorKeys(){ if(this) return *this; }
    virtual float StartFrame(){ return FirstFrame(); }
    virtual float EndFrame(){ return LastFrame(); }
    virtual bool FrameFromIndex(int idx, float& f){
        if(idx >= size()) return false;
        else f = (*this)[idx].frame;
        return true;
    }
    virtual void SetFrame(float f1, float f2);
    virtual void CloneKey(int idx){
        if(!mProp || !mTarget) return;
        if(idx >= 0 && idx < size()){
            Add((*this)[idx].value, (*this)[idx].frame, false);
        }
    }
    virtual int SetKey(float);
    virtual int RemoveKey(int idx){
        Remove(idx);
        return size();
    }
    virtual int NumKeys(){ return size(); }
    virtual void SetToCurrentVal(int);
    virtual void Save(BinStream& bs){
        PropKeys::Save(bs);
        bs << *this;
    }
    virtual void Load(BinStream& bs){
        PropKeys::Load(bs);
        bs >> *this;
    }
    virtual void Copy(const PropKeys*);
    virtual int ColorAt(float, Hmx::Color&);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
};

class ObjectKeys : public PropKeys, public ObjKeys {
public:
    ObjectKeys(Hmx::Object* o1, Hmx::Object* o2) : PropKeys(o1, o2), ObjKeys(o1) {
        mKeysType = kObject; mInterpolation = kStep;
    }
    virtual ~ObjectKeys(){}
    virtual ObjKeys& AsObjectKeys(){ if(this) return *this; }
    virtual float StartFrame(){ return FirstFrame(); }
    virtual float EndFrame(){ return LastFrame(); }
    virtual bool FrameFromIndex(int idx, float& f){
        if(idx >= size()) return false;
        else f = (*this)[idx].frame;
        return true;
    }
    virtual void SetFrame(float f1, float f2);
    virtual void CloneKey(int idx){
        if(!mProp || !mTarget) return;
        if(idx >= 0 && idx < size()){
            ObjKeys::Add((*this)[idx].value.Ptr(), (*this)[idx].frame, false);
        }
    }
    virtual int SetKey(float);
    virtual int RemoveKey(int idx){
        Remove(idx);
        return size();
    }
    virtual int NumKeys(){ return size(); }
    virtual void SetToCurrentVal(int);
    virtual void Save(BinStream& bs){
        PropKeys::Save(bs);
        bs << *this;
    }
    virtual void Load(BinStream& bs){
        PropKeys::Load(bs);
        Hmx::Object* oldOwner = ObjectStage::sOwner;
        ObjectStage::sOwner = mOwner;
        bs >> *this;
        ObjectStage::sOwner = oldOwner;

    }
    virtual void Copy(const PropKeys*);
    virtual int ObjectAt(float, Hmx::Object*&);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
};

class BoolKeys : public PropKeys, public Keys<bool, bool> {
public:
    BoolKeys(Hmx::Object* o1, Hmx::Object* o2) : PropKeys(o1, o2) {
        mKeysType = kBool; mInterpolation = kStep;
    }
    virtual ~BoolKeys(){}
    virtual Keys<bool, bool>& AsBoolKeys(){ if(this) return *this; }
    virtual float StartFrame(){ return FirstFrame(); }
    virtual float EndFrame(){ return LastFrame(); }
    virtual bool FrameFromIndex(int idx, float& f){
        if(idx >= size()) return false;
        else f = (*this)[idx].frame;
        return true;
    }
    virtual void SetFrame(float f1, float f2);
    virtual void CloneKey(int idx){
        if(!mProp || !mTarget) return;
        if(idx >= 0 && idx < size()){
            Add((*this)[idx].value, (*this)[idx].frame, false);
        }
    }
    virtual int SetKey(float);
    virtual int RemoveKey(int idx){
        Remove(idx);
        return size();
    }
    virtual int NumKeys(){ return size(); }
    virtual void SetToCurrentVal(int);
    virtual void Save(BinStream& bs){
        PropKeys::Save(bs);
        bs << *this;
    }
    virtual void Load(BinStream& bs){
        PropKeys::Load(bs);
        bs >> *this;
    }
    virtual void Copy(const PropKeys*);
    virtual int BoolAt(float, bool&);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
};

class QuatKeys : public PropKeys, public Keys<Hmx::Quat, Hmx::Quat> {
public:
    QuatKeys(Hmx::Object* o1, Hmx::Object* o2) : PropKeys(o1, o2), mVec(Vector3::sZero) { mKeysType = kQuat; }
    virtual ~QuatKeys(){}
    virtual Keys<Hmx::Quat, Hmx::Quat>& AsQuatKeys(){ if(this) return *this; }
    virtual float StartFrame(){ return FirstFrame(); }
    virtual float EndFrame(){ return LastFrame(); }
    virtual bool FrameFromIndex(int idx, float& f){
        if(idx >= size()) return false;
        else f = (*this)[idx].frame;
        return true;
    }
    virtual void SetFrame(float f1, float f2);
    virtual void CloneKey(int idx){
        if(!mProp || !mTarget) return;
        if(idx >= 0 && idx < size()){
            Add((*this)[idx].value, (*this)[idx].frame, false);
        }
    }
    virtual int SetKey(float);
    virtual int RemoveKey(int idx){
        Remove(idx);
        return size();
    }
    virtual int NumKeys(){ return size(); }
    virtual void SetToCurrentVal(int);
    virtual void Save(BinStream& bs){
        PropKeys::Save(bs);
        bs << *this;
    }
    virtual void Load(BinStream& bs){
        PropKeys::Load(bs);
        bs >> *this;
    }
    virtual void Copy(const PropKeys*);
    virtual int QuatAt(float, Hmx::Quat&);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    Vector3 mVec; // 0x28
};

class Vector3Keys : public PropKeys, public Keys<Vector3, Vector3> {
public:
    Vector3Keys(Hmx::Object* o1, Hmx::Object* o2) : PropKeys(o1, o2) { mKeysType = kVector3; }
    virtual ~Vector3Keys(){}
    virtual Keys<Vector3, Vector3>& AsVector3Keys(){ if(this) return *this; }
    virtual float StartFrame(){ return FirstFrame(); }
    virtual float EndFrame(){ return LastFrame(); }
    virtual bool FrameFromIndex(int idx, float& f){
        if(idx >= size()) return false;
        else f = (*this)[idx].frame;
        return true;
    }
    virtual void SetFrame(float f1, float f2);
    virtual void CloneKey(int idx){
        if(!mProp || !mTarget) return;
        if(idx >= 0 && idx < size()){
            Add((*this)[idx].value, (*this)[idx].frame, false);
        }
    }
    virtual int SetKey(float);
    virtual int RemoveKey(int idx){
        Remove(idx);
        return size();
    }
    virtual int NumKeys(){ return size(); }
    virtual void SetToCurrentVal(int);
    virtual void Save(BinStream& bs){
        PropKeys::Save(bs);
        bs << *this;
    }
    virtual void Load(BinStream& bs){
        PropKeys::Load(bs);
        bs >> *this;
    }
    virtual void Copy(const PropKeys*);
    virtual int Vector3At(float, Vector3&);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
};

class SymbolKeys : public PropKeys, public Keys<Symbol, Symbol> {
public:
    SymbolKeys(Hmx::Object* o1, Hmx::Object* o2) : PropKeys(o1, o2) {
        mKeysType = kSymbol; mInterpolation = kStep; unk28 = -1; unk2c = -1; unk30 = 0;
    }
    virtual ~SymbolKeys(){}
    virtual Keys<Symbol, Symbol>& AsSymbolKeys(){ if(this) return *this; }
    virtual float StartFrame(){ return FirstFrame(); }
    virtual float EndFrame(){ return LastFrame(); }
    virtual bool FrameFromIndex(int idx, float& f){
        if(idx >= size()) return false;
        else f = (*this)[idx].frame;
        return true;
    }
    virtual void SetFrame(float f1, float f2);
    virtual void CloneKey(int idx){
        if(!mProp || !mTarget) return;
        if(idx >= 0 && idx < size()){
            Add((*this)[idx].value, (*this)[idx].frame, false);
        }
    }
    virtual int SetKey(float);
    virtual int RemoveKey(int idx){
        Remove(idx);
        return size();
    }
    virtual int NumKeys(){ return size(); }
    virtual void SetToCurrentVal(int);
    virtual void Save(BinStream& bs){
        PropKeys::Save(bs);
        bs << *this;
    }
    virtual void Load(BinStream& bs){
        PropKeys::Load(bs);
        bs >> *this;
    }
    virtual void Copy(const PropKeys*);
    virtual int SymbolAt(float, Symbol&);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    int unk28; // 0x28
    int unk2c; // 0x2c
    bool unk30; // 0x30
};

#endif
