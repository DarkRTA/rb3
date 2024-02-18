#ifndef RB3_DOFPROC_HPP
#define RB3_DOFPROC_HPP
#include "math/Color.h"
#include "obj/Object.h"
#include "obj/Utl.h"
#include "os/System.h"
#include "Rnd/rndcam.hpp"

class DOFProc : public Hmx::Object {
public:
    DOFProc();
    virtual ~DOFProc();
    virtual Symbol ClassName() const { return StaticClassName(); }
    virtual void SetType(Symbol s){
        static DataArray* types = SystemConfig("objects", StaticClassName(), "types");
        if(s.IsNull()){
            SetTypeDef(0);
        }
        else {
            DataArray* found = types->FindArray(s, false);
            if(found){
                SetTypeDef(found);
            }
            else {
                PathName(this);
                ClassName();
                SetTypeDef(0);
            }
        }
    }

    virtual void Set(RndCam*, float, float, float, float){}
    virtual void SetTint(bool, Hmx::Color){ }
    virtual void UnSet(){ }
    virtual int Enabled() const { return 0; }
    virtual int Blur(){ return 0; }
    virtual float FocalPlane(){ return 1.0f; }
    virtual float BlurDepth(){ return 1.0f; }
    virtual float MaxBlur(){ return 0.0f; }
    virtual float MinBlur(){ return 0.0f; }

    static Symbol StaticClassName(){
        static Symbol name("DOFProc");
        return name;
    }
    static DOFProc* Params();
    static void Terminate();
    static DOFProc* NewDOFProc();
    static void Init();
};

#endif
