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

    static void SetDepthOfFieldTint(bool b, Hmx::Color c){
        Params().SetTint(b, c);
    }
    
    static void Init();
    static void Terminate();
    static DOFProc& Params();
    NEW_OBJ(DOFProc);

    static void Register(){
        REGISTER_OBJ_FACTORY(DOFProc)
    }
};

extern DOFProc* TheDOFProc;

class DOFOverrideParams {
public:
    DOFOverrideParams();
    void SetDepthScale(float f){ mDepthScale = f; }
    void SetDepthOffset(float f){ mDepthOffset = f; }
    void SetMinBlurScale(float f){ mMinBlurScale = f; }
    void SetMinBlurOffset(float f){ mMinBlurOffset = f; }
    void SetMaxBlurScale(float f){ mMaxBlurScale = f; }
    void SetMaxBlurOffset(float f){ mMaxBlurOffset = f; }
    void SetBlurWidthScale(float f){ mBlurWidthScale = f; }

    float mDepthScale;
    float mDepthOffset;
    float mMinBlurScale;
    float mMinBlurOffset;
    float mMaxBlurScale;
    float mMaxBlurOffset;
    float mBlurWidthScale;
};

#endif
