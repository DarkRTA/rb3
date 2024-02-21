#ifndef RNDOBJ_DOFPROC_H
#define RNDOBJ_DOFPROC_H
#include "math/Color.h"
#include "obj/Object.h"

class RndCam;

class DOFProc : public Hmx::Object {
public:
    DOFProc();
    virtual ~DOFProc();
    OBJ_CLASSNAME(DOFProc);
    OBJ_SET_TYPE(DOFProc);
    virtual void SetTint(bool, Hmx::Color){ }
    virtual void Set(RndCam*, float, float, float, float){}
    virtual void UnSet(){ }
    virtual int Enabled() const { return 0; }
    virtual int Blur(){ return 0; }
    virtual float FocalPlane(){ return 1.0f; }
    virtual float BlurDepth(){ return 1.0f; }
    virtual float MaxBlur(){ return 0.0f; }
    virtual float MinBlur(){ return 0.0f; }
    
    static void Init();
    static void Terminate();
    static DOFProc& Params();
};

#endif
