#ifndef RNDOBJ_WIIDOFPROC_H
#define RNDOBJ_WIIDOFPROC_H
#include "rndobj/DOFProc.h"
#include "rndobj/PostProc.h"

class WiiDOFProc : public DOFProc, public PostProcessor {
public:
    WiiDOFProc();
    virtual ~WiiDOFProc();
    OBJ_CLASSNAME(DOFProc);
    OBJ_SET_TYPE(WiiDOFProc);
    virtual void SetTint(bool, Hmx::Color);
    virtual void Set(RndCam*, float, float, float, float);
    virtual void UnSet();
    virtual bool Enabled() const { return mEnabled; }
    virtual int Blur(){ return 0; }
    virtual float FocalPlane(){ return mFocalPlane; }
    virtual float BlurDepth(){ return mBlurDepth; }
    virtual float MaxBlur(){ return mMaxBlur; }
    virtual float MinBlur(){ return mMinBlur; }
    virtual void EndWorld();
    virtual void OnGPHangRecover();
    virtual void DoPost(){}
    virtual float Priority(){ return 1.1f; }

    bool mEnabled; // 0x20
    int unk24; // 0x24
    float mFocalPlane; // 0x28
    float mBlurDepth; // 0x2c
    float mMinBlur; // 0x30
    float mMaxBlur; // 0x34
    int unk38; // 0x38
    int unk3c; // 0x3c
    int unk40; // 0x40
    bool unk44;
    Hmx::Color color; // 0x48
};

#endif
