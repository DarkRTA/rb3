#ifndef RNDOBJ_PROPKEYS_H
#define RNDOBJ_PROPKEYS_H
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Env.h"
#include "math/Color.h"
#include "math/Mtx.h"
#include "os/Debug.h"
#include <vector>

// what on earth?!?!
template <class T> class Keys : public std::vector<T> {
public:
};

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
    virtual Hmx::Object* RefOwner();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual float StartFrame(){ return 0.0f; }
    virtual float EndFrame(){ return 0.0f; }
    virtual int FrameFromIndex(int, float&){ return 0; }
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
    virtual int AsFloatKeys(){ MILO_ASSERT(false, 0xA7); return 0; }
    virtual int AsColorKeys(){ MILO_ASSERT(false, 0xA9); return 0; }
    virtual int AsObjectKeys(){ MILO_ASSERT(false, 0xAB); return 0; }
    virtual int AsBoolKeys(){ MILO_ASSERT(false, 0xAD); return 0; }
    virtual int AsQuatKeys(){ MILO_ASSERT(false, 0xAF); return 0; }
    virtual int AsVector3Keys(){ MILO_ASSERT(false, 0xB1); return 0; }
    virtual int AsSymbolKeys(){ MILO_ASSERT(false, 0xB3); return 0; }
    virtual int FloatAt(float, float&){ MILO_ASSERT(false, 0xB6); return -1; }
    virtual int ColorAt(float, Hmx::Color&){ MILO_ASSERT(false, 0xB8); return -1; }
    virtual int ObjectAt(float, Hmx::Object*&){ MILO_ASSERT(false, 0xBA); return -1; }
    virtual int BoolAt(float, bool&){ MILO_ASSERT(false, 0xBC); return -1; }
    virtual int QuatAt(float, Hmx::Quat&){ MILO_ASSERT(false, 0xBE); return -1; }
    virtual int Vector3At(float, Vector3&){ MILO_ASSERT(false, 0xC0); return -1; }
    virtual int SymbolAt(float, Symbol&){ MILO_ASSERT(false, 0xC2); return -1; }

    static unsigned short gRev;

    ObjOwnerPtr<Hmx::Object, ObjectDir> mTarget;
    DataArray* mProp;

    // only one word here - could be any one or a combo of these
    AnimKeysType mKeysType;
    // Interpolation mInterpolation;
    // ExceptionID mPropExceptionID;
    // RndEnviron* mTrans;

    Symbol mInterpHandler;
    int mLastKeyFrameIndex;
};

#endif
