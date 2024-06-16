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
    virtual void Set(RndCam*, float, float, float, float){}
    virtual void UnSet();
    virtual bool Enabled() const { return mEnabled; }
    virtual int Blur();
    virtual float FocalPlane();
    virtual float BlurDepth();
    virtual float MaxBlur();
    virtual float MinBlur();
    virtual void EndWorld();
    virtual void OnGPHangRecover();
    virtual void DoPost();
    virtual float Priority();

    bool mEnabled; // 0x20
    char filler[0x24];
    bool unk44;
    float unk48;
    float unk4c;
    float unk50;
    float unk54;
};

#endif
