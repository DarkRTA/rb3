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
    kHermite
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

class PropKeys : public ObjRef {
public:
    PropKeys(Hmx::Object*, Hmx::Object*);
    virtual ~PropKeys();
    virtual Hmx::Object* RefOwner(){ return 0; }
    virtual void Replace(Hmx::Object*, Hmx::Object*){}
    virtual float StartFrame(){ return 0.0f; }
    virtual float EndFrame(){ return 0.0f; }
    virtual bool FrameFromIndex(int, float&){ return 0; }
    virtual float SetFrame(float f1, float f2){ return f1; }
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
    virtual Keys<ObjectStage, Hmx::Object*>& AsObjectKeys(){ MILO_ASSERT(false, 0xAB); return *(Keys<ObjectStage, Hmx::Object*>*)0; }
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
    static unsigned int PropExceptionID(Hmx::Object*, DataArray*);

    static unsigned short gRev;
    static Message sInterpMessage;

    ObjOwnerPtr<Hmx::Object, ObjectDir> mTarget;
    DataArray* mProp;
    RndTransformable* mTrans;
    Symbol mInterpHandler;
    
    // presumably, bits 10-31 of 0x1C would be mlastKeyFrameIndex?
    // mKeysType: bits 7-9 of 0x1C
    // interpolation: bits 4-6 of 0x1C
    // exception id is bits 1-3 of 0x1C
    // unknown is bit 0 of 0x1C
    int mLastKeyFrameIndex : 22;
    unsigned int mKeysType : 3; // represents the enum AnimKeysType
    unsigned int mInterpolation : 3; // represents the enum Interpolation
    unsigned int mPropExceptionID : 3; // represents the enum ExceptionID
    int unk18lastbit : 1;
};

void SetPropKeysRev(int);
float CalcSpline(float, float*); // putting this here for now, maybe it's better off in Key.h?

class FloatKeys : public PropKeys, public Keys<float, float> {
public:
    FloatKeys(Hmx::Object* o1, Hmx::Object* o2) : PropKeys(o1, o2) {}
    virtual ~FloatKeys(){}
    virtual float StartFrame();
    virtual float EndFrame();
    virtual bool FrameFromIndex(int, float&);
    virtual float SetFrame(float f1, float f2);
    virtual void CloneKey(int);
    virtual int SetKey(float);
    virtual int RemoveKey(int);
    virtual int NumKeys();
    virtual void SetToCurrentVal(int);
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);
    virtual void Copy(const PropKeys*);
    virtual Keys<float, float>& AsFloatKeys(){ if(this) return *this; }
    virtual int FloatAt(float, float&);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
};

class SymbolKeys : public PropKeys, public Keys<Symbol, Symbol> {
public:
    SymbolKeys(Hmx::Object* o1, Hmx::Object* o2) : PropKeys(o1, o2) {}
    virtual ~SymbolKeys(){}
    virtual float StartFrame();
    virtual float EndFrame();
    virtual bool FrameFromIndex(int, float&);
    virtual float SetFrame(float f1, float f2);
    virtual void CloneKey(int);
    virtual int SetKey(float);
    virtual int RemoveKey(int);
    virtual int NumKeys();
    virtual void SetToCurrentVal(int);
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);
    virtual void Copy(const PropKeys*);
    virtual Keys<Symbol, Symbol>& AsSymbolKeys(){ if(this) return *this; }
    virtual int SymbolAt(float, Symbol&);
};

#endif
